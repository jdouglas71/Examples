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

#include "JRex_JNI_HistoryEvent.h"
using namespace JRex_JNI_Event;
using namespace JRex_JNI_HistoryEvent;

	static inline jobject createHistoryCommonEventJavaObject(JNIEnv *env, BasicHistoryEventParam* param);
	static inline jobject createHistoryIntIndexEventJavaObject(JNIEnv *env, IntHistoryEventParam* param);

	jobject JRex_JNI_HistoryEvent::createJavaObject(JNIEnv *env, BasicHistoryEventParam* param){
		jobject jrv=NULL;
		jshort hisEventType=param->hisEventType;
		switch(hisEventType){
			case HIS_NEW_ENTRY_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** HIS_NEW_ENTRY_EVENT ****")
				jrv=createHistoryCommonEventJavaObject(env,param);
				break;
			}
			case HIS_GO_BACK_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** HIS_GO_BACK_EVENT ****")
				jrv=createHistoryCommonEventJavaObject(env,param);
				break;
			}
			case HIS_GO_FORWARD_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** HIS_GO_FORWARD_EVENT ****")
				jrv=createHistoryCommonEventJavaObject(env,param);
				break;
			}
			case HIS_RELOAD_EVENT:
			case HIS_GO_TO_INDEX_EVENT:
			case HIS_PURGE_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** HIS_RELOAD_EVENT | HIS_GO_TO_INDEX_EVENT |HIS_PURGE_EVENT ****")
				jrv=createHistoryIntIndexEventJavaObject(env,(IntHistoryEventParam*)param);
				break;
			}
			default:
			{
				JREX_LOGLN("createJavaObject()--> **** UNKNOW HISTORY EVENT TYPE ****")
			}
		}
		JNI_IF_EXP_DESC_CLR_RET("createJavaObject()--> **** HistoryEvent New jrv Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createJavaObject()--> **** jrv<"<<jrv<<"> ****")
		return jrv;
	}

	jobject createHistoryCommonEventJavaObject(JNIEnv *env, BasicHistoryEventParam* bhParam){
		jstring juri=NULL;
		if(NOT_NULL(bhParam->uri)){
			JREX_LOGLN("createHistoryCommonEventJavaObject()--> **** bhParam->uri<"<<bhParam->uri<<"> ****")
			juri=env->NewStringUTF(bhParam->uri);
			nsMemory::Free(bhParam->uri);
		}
		JREX_LOGLN("createHistoryCommonEventJavaObject()--> **** juri<"<<juri<<"> ****")
		jobject rObj= env->NewObject(HistoryEventFields::hisEvtCls,HistoryEventFields::cid,
								(jint)bhParam->target, (jint)bhParam->hisEventType, juri);
		if(juri)env->DeleteLocalRef(juri);
		return rObj;
	}

	jobject createHistoryIntIndexEventJavaObject(JNIEnv *env, IntHistoryEventParam* gtParam){
		jstring juri=NULL;
		if(NOT_NULL(gtParam->uri)){
			JREX_LOGLN("createHistoryIntIndexEventJavaObject()--> **** gtParam->uri<"<<gtParam->uri<<"> ****")
			juri=env->NewStringUTF(gtParam->uri);
			nsMemory::Free(gtParam->uri);
		}
		JREX_LOGLN("createHistoryIntIndexEventJavaObject()--> **** juri<"<<juri<<"> ****")

		jobject hisParamObj=env->NewObject(HistoryEventFields::hisIntPrmCls,HistoryEventFields::hisIntCID,
											(jint)gtParam->intData,juri);
		if(juri)env->DeleteLocalRef(juri);
		JREX_LOGLN("createHistoryIntIndexEventJavaObject()--> **** hisParamObj<"<<hisParamObj<<"> ****")

		jobject rObj= env->NewObject(HistoryEventFields::hisEvtCls,HistoryEventFields::cid,
								(jint)gtParam->target, (jint)gtParam->hisEventType, hisParamObj);
		if(hisParamObj)env->DeleteLocalRef(hisParamObj);
		return rObj;
	}

	nsresult JRex_JNI_HistoryEvent::getNativeData(JNIEnv *env, jobject jobj, BasicHistoryEventParam* hsParam, void** _result){
		nsresult rv=NS_OK;
		if(hsParam && (hsParam->hisEventType==HIS_GO_BACK_EVENT
					   || hsParam->hisEventType==HIS_GO_FORWARD_EVENT
					   || hsParam->hisEventType==HIS_RELOAD_EVENT
					   || hsParam->hisEventType==HIS_GO_TO_INDEX_EVENT
					   || hsParam->hisEventType==HIS_PURGE_EVENT)){
			JREX_LOGLN("getNativeData()--> **** hsParam->hisEventType <"<<hsParam->hisEventType<<"> ****")
			if(NOT_NULL(jobj)){
				jboolean canDo=env->CallBooleanMethod(jobj,HistoryEventFields::boolValueID);
				*_result=(void*)(canDo==JNI_TRUE?PR_TRUE:PR_FALSE);
			}else
				rv=NS_ERROR_NULL_POINTER;
		}
		return rv;
	}

	void JRex_JNI_HistoryEvent::deleteEventData(PRUint32  hisEventType, BasicHistoryEventParam* param){
		switch(hisEventType){
			case HIS_NEW_ENTRY_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** HIS_NEW_ENTRY_EVENT ****")
                                delete param;
				break;
			}
			case HIS_GO_BACK_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** HIS_GO_BACK_EVENT ****")
				delete param;
				break;
			}
			case HIS_GO_FORWARD_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** HIS_GO_FORWARD_EVENT ****")
				delete param;
				break;
			}
			case HIS_RELOAD_EVENT:
			case HIS_GO_TO_INDEX_EVENT:
			case HIS_PURGE_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** HIS_RELOAD_EVENT | HIS_GO_TO_INDEX_EVENT |HIS_PURGE_EVENT ****")
                                delete (IntHistoryEventParam*)param;
				break;
			}
			default:
			{
				JREX_LOGLN("deleteEventData()--> **** UNKNOW HISTORY EVENT TYPE ****")
			}
		}
	}

	nsresult JRex_JNI_HistoryEvent::fireEvent(BasicHistoryEventParam* hParam, PRBool isSync, void **_result){

		JREX_LOGLN("fireEvent()--> **** hParam <"<<hParam<<"> ****")
		if(isSync)
			NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

    	JRexJavaEvent* event = new JRexJavaEvent;
		if (event) {
			JREX_LOGLN("fireEvent()--> **** JRexJavaEvent Created ****")
			event->eventType=HISTORY_EVENT;
			event->eventData=hParam;
			void* result=nsnull;
			rv=isSync?postSyncJavaEvent(event,(void **)&result):postJavaEvent(event);
			JREX_LOGLN("fireEvent()--> **** postJavaEvent isSync<"<<isSync<<"> rv<"<<rv<<">****")
			if (NS_SUCCEEDED(rv) && isSync){
				*_result=result;
				JREX_LOGLN("fireEvent()--> **** postSyncJavaEvent _result<"<<*_result<<">****")
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

