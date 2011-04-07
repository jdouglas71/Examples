/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Contributor(s):
 *   C.N Medappa <jrex_moz@yahoo.com><>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "JRex_JNI_Event.h"
#include "JRex_JNI_WindowEvent.h"
#include "JRex_JNI_HistoryEvent.h"
#include "JRex_JNI_ProgressEvent.h"
#include "JRex_JNI_ContextMenuEvent.h"
#include "JRex_JNI_TooltipEvent.h"
#include "JRex_JNI_ObserverEvent.h"
#include "JRex_JNI_URIContentEvent.h"

using namespace JRex_JNI_Event;
using namespace JRex_JNI_WindowEvent;
using namespace JRex_JNI_HistoryEvent;
using namespace JRex_JNI_ProgressEvent;
using namespace JRex_JNI_ContextMenuEvent;
using namespace JRex_JNI_TooltipEvent;
using namespace JRex_JNI_ObserverEvent;
using namespace JRex_JNI_URIContentEvent;

	static inline jobject createJavaEventObject(JNIEnv *env, jint eventType, void* eventData);
	static inline nsresult getNativeEventData(JNIEnv *env, jint eventType, jobject jobj,void* eventData, void** _result);
    static inline void deleteEventData(jint eventType, void* eventData);

	nsresult JRex_JNI_Event::postSyncJavaEvent(JRexJavaEvent* event, void** _result){
		if(!gXpcomRunning) return NS_ERROR_FAILURE;
		JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
		nsresult rv;
		jobject rvObj;
		jobject eventObj;
		void* temp=nsnull;

		JREX_LOGLN("postSyncJavaEvent()--> *** env <"<<env<<"> ***")
		if(IS_NULL(env)){
			JREX_LOGLN("postSyncJavaEvent()--> **** GETTING JAVA ENV Failed ****")
			rv=NS_ERROR_INVALID_POINTER;
			goto clean;
		}
		if (env->EnsureLocalCapacity(8) < 0) {
			JREX_LOGLN("postSyncJavaEvent()--> *** EnsureLocalCapacity Failed ****")
			rv= NS_ERROR_FAILURE;
			goto clean;
		}

		eventObj=createJavaEventObject(env, event->eventType, event->eventData);
		JREX_LOGLN("postSyncJavaEvent()--> *** createJavaEventObject eventObj<"<<eventObj<<">***")
		if(eventObj==NULL){
			JREX_LOGLN("postSyncJavaEvent()--> *** createJavaEventObject Failed ****")
			rv= NS_ERROR_FAILURE;
			goto clean;
		}

		JREX_LOGLN("postSyncJavaEvent()--> *** Sync Event ****")
		rvObj=env->CallStaticObjectMethod(EventManagerFields::eventMgrCls,EventManagerFields::postSyncEvtID,
																	event->eventType,eventObj);
		JREX_LOGLN("postSyncJavaEvent()--> *** CallObjectMethod  rvObj<"<<rvObj<<"> ****")
		rv=getNativeEventData(env, event->eventType, rvObj, event->eventData, &temp);
		JREX_LOGLN("postSyncJavaEvent()--> *** getNativeEventData   rv<"<<rv<<"> temp<"<<temp<<"> ****")
		if(NS_SUCCEEDED(rv))
			*_result=temp;
		env->DeleteLocalRef(eventObj);

		rv= env->ExceptionCheck()?NS_ERROR_FAILURE:rv;
		JNI_EXP_DESC_CLR("postSyncJavaEvent()--> *** Event firing failed ****");

clean : if(NOT_NULL(event->eventData))
			deleteEventData(event->eventType, event->eventData);
		delete event;
		return rv;
	}


	nsresult JRex_JNI_Event::postJavaEvent(JRexJavaEvent* event){
		if(!gXpcomRunning) return NS_ERROR_FAILURE;
		JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
		nsresult rv=NS_OK;
		jobject eventObj;
		JREX_LOGLN("postJavaEvent()--> *** env <"<<env<<"> ***")
		if(IS_NULL(env)){
			JREX_LOGLN("postJavaEvent()--> **** GETTING JAVA ENV Failed ****")
			rv= NS_ERROR_INVALID_POINTER;
			goto clean;
		}

		if (env->EnsureLocalCapacity(8) < 0) {
			JREX_LOGLN("postJavaEvent()--> *** EnsureLocalCapacity Failed ****")
			rv= NS_ERROR_FAILURE;
			goto clean;
		}
		eventObj=createJavaEventObject(env, event->eventType, event->eventData);
		JREX_LOGLN("postJavaEvent()--> *** createJavaEventObject eventObj<"<<eventObj<<">***")
		if(eventObj==NULL){
			JREX_LOGLN("postJavaEvent()--> *** createJavaEventObject Failed ****")
			rv= NS_ERROR_FAILURE;
			goto clean;
		}

		JREX_LOGLN("postJavaEvent()--> *** Non-Sync Event ****")
		env->CallStaticVoidMethod(EventManagerFields::eventMgrCls,EventManagerFields::postEvtID,
									event->eventType,eventObj);
		env->DeleteLocalRef(eventObj);

		rv= env->ExceptionCheck()?NS_ERROR_FAILURE:rv;
		JNI_EXP_DESC_CLR("postJavaEvent()--> *** Event firing failed ****");

clean : if(NOT_NULL(event->eventData))
                        deleteEventData(event->eventType, event->eventData);
		delete event;
		return rv;
	}


	nsresult JRex_JNI_Event::postJavaKeyEvent(jint target,jint eid, jint modifiers,jint keyCode, jchar keyChar){
		if(!gXpcomRunning) return NS_ERROR_FAILURE;
		static JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
		JREX_LOGLN("postJavaKeyEvent()--> *** env <"<<env<<"> ***")
		if(IS_NULL(env)){
			JREX_LOGLN("postJavaKeyEvent()--> **** GETTING JAVA ENV Failed ****")
			return NS_ERROR_INVALID_POINTER;
		}
		env->CallStaticVoidMethod(EventManagerFields::eventMgrCls,EventManagerFields::postKeyEventID,
									target,eid, modifiers,keyCode, keyChar);
		JNI_IF_EXP_DESC_CLR_RET("postJavaKeyEvent()--> *** Event firing failed ****",NS_ERROR_FAILURE);
			JREX_LOGLN("postJavaKeyEvent()--> *** done ****")
			return NS_OK;
		}


	nsresult JRex_JNI_Event::postJavaMouseEvent(jint target,jint eid, jint modifiers,jint x, jint y, jint clickCount,jint button){
		if(!gXpcomRunning) return NS_ERROR_FAILURE;
		static JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
		JREX_LOGLN("postJavaMouseEvent()--> *** env <"<<env<<"> ***")
		if(IS_NULL(env)){
			JREX_LOGLN("postJavaMouseEvent()--> **** GETTING JAVA ENV Failed ****")
			return NS_ERROR_INVALID_POINTER;
		}
		env->CallStaticVoidMethod(EventManagerFields::eventMgrCls,EventManagerFields::postMouseEventID,
									target,eid, modifiers, x, y, clickCount, button);
		JNI_IF_EXP_DESC_CLR_RET("postJavaMouseEvent()--> *** CallStaticVoidMethod failed ****",NS_ERROR_FAILURE);
		JREX_LOGLN("postJavaMouseEvent()--> *** done ****")
		return NS_OK;
	 }


	jobject createJavaEventObject(JNIEnv *env, jint eventType, void* eventData){
		JREX_LOGLN("createJavaEventObject()--> **** env<"<<env<<"> eventType<"<<eventType<<"> eventData<"<<eventData<<"> ****")
		jobject jrv=NULL;
		switch(eventType){
			case WINDOW_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** WINDOW_EVENT ****")
				BasicWindowEventParam* param=(BasicWindowEventParam*)eventData;
				jrv=JRex_JNI_WindowEvent::createJavaObject(env, param);
				break;
			}
			case HISTORY_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** HISTORY_EVENT ****")
				BasicHistoryEventParam* param=(BasicHistoryEventParam*)eventData;
				jrv=JRex_JNI_HistoryEvent::createJavaObject(env, param);
				break;
			}
			case PROGRESS_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** PROGRESS_EVENT ****")
				BasicProgressEventParam* param=(BasicProgressEventParam*)eventData;
				jrv=JRex_JNI_ProgressEvent::createJavaObject(env, param);
				break;
			}
			case CONTEXT_MENU_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** CONTEXT_MENU_EVENT ****")
				ContextMenuEventParam* param=(ContextMenuEventParam*)eventData;
				jrv=JRex_JNI_ContextMenuEvent::createJavaObject(env, param);
				break;
			}
			case TOOL_TIP_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** TOOL_TIP_EVENT ****")
				TooltipEventParam* param=(TooltipEventParam*)eventData;
				jrv=JRex_JNI_TooltipEvent::createJavaObject(env, param);
				break;
			}
			case OBSERVER_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** OBSERVER_EVENT ****")
				ObserverEventParam* param=(ObserverEventParam*)eventData;
				jrv=JRex_JNI_ObserverEvent::createJavaObject(env, param);
				break;
			}
			case URICONTENT_EVENT:
			{
				JREX_LOGLN("createJavaEventObject()--> **** URICONTENT_EVENT ****")
				BasicURIContentEventParam* param=(BasicURIContentEventParam*)eventData;
				jrv=JRex_JNI_URIContentEvent::createJavaObject(env, param);
				break;
			}
			default:
			{
				JREX_LOGLN("createJavaEventObject()--> ****UNKNOW EVENT TYPE ****")
				jrv=NULL;
			}
		};
		JREX_LOGLN("createJavaEventObject()--> **** jrv<"<<jrv<<"> ****")
		JNI_IF_EXP_DESC_CLR_RET("createJavaEventObject()--> *** failed ****",NULL);
		return jrv;
	}

	void deleteEventData(jint eventType, void* eventData){
		JREX_LOGLN("deleteEventData()--> **** eventType<"<<eventType<<"> eventData<"<<eventData<<"> ****")
		switch(eventType){
			case WINDOW_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WINDOW_EVENT ****")
				BasicWindowEventParam* param=(BasicWindowEventParam*)eventData;
				JRex_JNI_WindowEvent::deleteEventData(param->winEventType, param);
				break;
			}
			case HISTORY_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** HISTORY_EVENT ****")
				BasicHistoryEventParam* param=(BasicHistoryEventParam*)eventData;
				JRex_JNI_HistoryEvent::deleteEventData(param->hisEventType, param);
				break;
			}
			case PROGRESS_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** PROGRESS_EVENT ****")
				BasicProgressEventParam* param=(BasicProgressEventParam*)eventData;
				JRex_JNI_ProgressEvent::deleteEventData(param->progEventType,param);
				break;
			}
			case CONTEXT_MENU_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** CONTEXT_MENU_EVENT ****")
				ContextMenuEventParam* param=(ContextMenuEventParam*)eventData;
				delete param;
				break;
			}
			case TOOL_TIP_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** TOOL_TIP_EVENT ****")
				TooltipEventParam* param=(TooltipEventParam*)eventData;
				delete param;

				break;
			}
			case OBSERVER_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** OBSERVER_EVENT ****")
				ObserverEventParam* param=(ObserverEventParam*)eventData;
				delete param;
				break;
			}
			case URICONTENT_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** URICONTENT_EVENT ****")
				BasicURIContentEventParam* param=(BasicURIContentEventParam*)eventData;
				JRex_JNI_URIContentEvent::deleteEventData(param->uriEventType,param);
				break;
			}
			default:
			{
				JREX_LOGLN("deleteEventData()--> ****UNKNOW EVENT TYPE ****")
			}
		};
	}

	nsresult getNativeEventData(JNIEnv *env, jint eventType, jobject jobj, void* eventData, void** _result){
		NS_ENSURE_ARG_POINTER(_result);
		JREX_LOGLN("getNativeEventData()--> **** env<"<<env<<"> eventType<"<<eventType<<"> jobj<"<<jobj<<"> ****")
		nsresult rv=NS_OK;
		switch(eventType){
			case WINDOW_EVENT:
			{
				rv=JRex_JNI_WindowEvent::getNativeData(env,jobj,(BasicWindowEventParam*)eventData,_result);
				JREX_LOGLN("getNativeEventData()--> **** WINDOW_EVENT <"<<rv<<"> ****")
				break;
			}
			case HISTORY_EVENT:
			{
				rv=JRex_JNI_HistoryEvent::getNativeData(env,jobj,(BasicHistoryEventParam*)eventData,_result);
				JREX_LOGLN("getNativeEventData()--> **** HISTORY_EVENT <"<<rv<<"> ****")
				break;
			}
			case URICONTENT_EVENT:
			{
				rv=JRex_JNI_URIContentEvent::getNativeData(env,jobj,(BasicURIContentEventParam*)eventData,_result);
				JREX_LOGLN("getNativeEventData()--> **** URICONTENT_EVENT <"<<rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("getNativeEventData()--> ****UNKNOW EVENT TYPE ****")
				rv=NS_ERROR_FAILURE;
			}
			JREX_LOGLN("getNativeEventData()--> **** rv<"<<rv<<"> ****")
			JNI_IF_EXP_DESC_CLR_RET("getNativeEventData()--> *** failed ****",NS_ERROR_FAILURE);
		}
		return rv;
	}
