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

#include "JRex_JNI_WindowEvent.h"
using namespace JRex_JNI_Event;
using namespace JRex_JNI_WindowEvent;

	static inline jobject createWindowCreateEventJObj(JNIEnv *env, WindowCreateEventParam* wcParam);
	static inline jobject createWindowSetModalEventJObj(JNIEnv *env, WindowSetModalEventParam* smParam);
	static inline jobject createWindowReSizeEventJObj(JNIEnv *env, WindowReSizeEventParam* szParam);
	static inline jobject createWindowSetTitleEventJObj(JNIEnv *env, WindowTitleEventParam* ssParam);
	static inline jobject createWindowSetChromeFlagsEventJObj(JNIEnv *env, WindowChromeEventParam* ssParam);
	static inline jobject createMainWindowEventJObj(JNIEnv *env, BasicWindowEventParam* param, jobject winParamObj);


	jobject JRex_JNI_WindowEvent::createJavaObject(JNIEnv *env, BasicWindowEventParam* param){
		jobject jrv=NULL;
		jshort winEventType=param->winEventType;
		switch(winEventType){
			case WIN_CREATE_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_CREATE_EVENT ****")
				jrv=createWindowCreateEventJObj(env,(WindowCreateEventParam*)param);
				break;
			}
			case WIN_SETMODAL_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_SETMODAL_EVENT ****")
				jrv=createWindowSetModalEventJObj(env,(WindowSetModalEventParam*)param);
				break;
			}
			case WIN_RESIZE_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_RESIZE_EVENT ****")
				jrv=createWindowReSizeEventJObj(env,(WindowReSizeEventParam*)param);
				break;
			}
			case WIN_DESTROY_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_DESTROY_EVENT ****")
				jrv=env->NewObject(WindowEventFields::winEvtCls,WindowEventFields::cid,
										(jint)param->target, (jint)param->winEventType, NULL);
				break;
			}
			case WIN_SET_TITLE_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_SET_TITLE_EVENT ****")
				jrv=createWindowSetTitleEventJObj(env,(WindowTitleEventParam*)param);
				break;
			}
			case WIN_CHROME_FLAG_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_CHROME_FLAG_EVENT ****")
				jrv=createWindowSetChromeFlagsEventJObj(env,(WindowChromeEventParam*)param);
				break;
			}
			case WIN_REALIZED_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** WIN_REALIZED_EVENT ****")
				jrv=createMainWindowEventJObj(env,param,NULL);
				break;
			}
			default:
			{
				JREX_LOGLN("createJavaObject()--> **** UNKNOW WINDOW EVENT TYPE ****")
			}
		}
		JNI_IF_EXP_DESC_CLR_RET("createJavaObject()--> **** WindowEvent New jrv Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createWindowEventJObj()--> **** jrv<"<<jrv<<"> ****")
		return jrv;
	}

	jobject createMainWindowEventJObj(JNIEnv *env, BasicWindowEventParam* param, jobject winParamObj){
		JNI_IF_EXP_DESC_CLR_RET("createMainWindowEventJObj()--> **** New ParamObj Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createMainWindowEventJObj()--> **** winParamObj<"<<winParamObj<<"> ****")
		jint target=param->target;
		jint winEventType=param->winEventType;

		return env->NewObject(WindowEventFields::winEvtCls,WindowEventFields::cid,
								(jint)target, (jint)winEventType, winParamObj);
	}

	jobject createWindowCreateEventJObj(JNIEnv *env, WindowCreateEventParam* wcParam){
		jstring juri=NULL;
		if(NOT_NULL(wcParam->uri)){
			JREX_LOGLN("createWindowCreateEventJObj()--> **** wcParam->uri<"<<wcParam->uri<<"> ****")
			juri=env->NewStringUTF(wcParam->uri);
			nsMemory::Free(wcParam->uri);
		}
		JREX_LOGLN("createWindowCreateEventJObj()--> **** juri<"<<juri<<"> ****")
		jobject winParamObj=env->NewObject(WindowEventFields::winCrtPrmCls,
									WindowEventFields::winCrtCID, (jint)wcParam->parentWin,
									(jlong)wcParam->chromeFlags, (jint)wcParam->contextFlags, juri);
		if(juri)env->DeleteLocalRef(juri);
		jobject rObj= createMainWindowEventJObj(env,wcParam,winParamObj);
		if(winParamObj)env->DeleteLocalRef(winParamObj);
		return rObj;
	}

	jobject createWindowSetModalEventJObj(JNIEnv *env, WindowSetModalEventParam* smParam){

		jboolean modal=(jboolean)(smParam->isModal==PR_TRUE?JNI_TRUE:JNI_FALSE);
		JREX_LOGLN("createWindowSetModalEventJObj()--> **** modal<"<<modal<<"> ****")
		jobject winParamObj=env->NewObject(WindowEventFields::winBoolPrmCls,WindowEventFields::boolCID,modal);
		JREX_LOGLN("createMainWindowEventJObj()--> **** winParamObj<"<<winParamObj<<"> ****")
		jobject rObj= createMainWindowEventJObj(env,smParam,winParamObj);
		if(winParamObj)env->DeleteLocalRef(winParamObj);
		return rObj;
	}

	jobject createWindowReSizeEventJObj(JNIEnv *env, WindowReSizeEventParam* szParam){

		jobject winParamObj=env->NewObject(WindowEventFields::winDimPrmCls,WindowEventFields::dimCID,
											(jint)szParam->xSize,(jint)szParam->ySize);
		jobject rObj= createMainWindowEventJObj(env,szParam,winParamObj);
		if(winParamObj)env->DeleteLocalRef(winParamObj);
		return rObj;
	}


	jobject createWindowSetTitleEventJObj(JNIEnv *env, WindowTitleEventParam* stParam){
		jstring jtitle=NULL;
		if(NOT_NULL(stParam->title)){
			JREX_LOGLN("createWindowSetTitleEventJObj()--> **** stParam->title<"<<stParam->title<<"> ****")
			jtitle=env->NewStringUTF(stParam->title);
			nsMemory::Free(stParam->title);
		}
		JREX_LOGLN("createWindowSetTitleEventJObj()--> **** jtitle<"<<jtitle<<"> ****")
		jobject rObj=createMainWindowEventJObj(env,stParam,jtitle);
		if(jtitle)env->DeleteLocalRef(jtitle);
		return rObj;
	}


	jobject createWindowSetChromeFlagsEventJObj(JNIEnv *env, WindowChromeEventParam* wcParam){
		jint chromeFlags=(jint)wcParam->chromeFlags;
		JREX_LOGLN("createWindowSetChromeFlagsEventJObj()--> **** chromeFlags<"<<chromeFlags<<"> ****")
		jobject winParamObj=env->NewObject(WindowEventFields::winLongPrmCls,WindowEventFields::longCID,(jlong)chromeFlags);
		JREX_LOGLN("createWindowSetChromeFlagsEventJObj()--> **** winParamObj<"<<winParamObj<<"> ****")
		jobject rObj= createMainWindowEventJObj(env,wcParam,winParamObj);
		if(winParamObj)env->DeleteLocalRef(winParamObj);
		return rObj;
	}

	nsresult JRex_JNI_WindowEvent::getNativeData(JNIEnv *env, jobject jobj, BasicWindowEventParam* bwParam, void** _result){
		nsresult rv=NS_OK;
		if(bwParam && (bwParam->winEventType==WIN_CREATE_EVENT)){
			JREX_LOGLN("getNativeData()--> **** bwParam->winEventType WIN_CREATE_EVENT ****")
			if(NOT_NULL(jobj)){
				jint intVal=env->CallIntMethod(jobj,WindowEventFields::intValMID);
				*_result=(void*)intVal;
			}else
				rv=NS_ERROR_NULL_POINTER;
		}else
			rv=NS_ERROR_NOT_IMPLEMENTED;
		JREX_LOGLN("JRex_JNI_WindowEvent::getNativeData()--> **** rv<"<<rv<<"> *_result<"<<*_result<<"> ****")
		return rv;
	}

	void JRex_JNI_WindowEvent::deleteEventData(PRUint32  winEventType, BasicWindowEventParam* param){
		switch(winEventType){
			case WIN_CREATE_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_CREATE_EVENT ****")
				delete (WindowCreateEventParam*)param;
				break;
			}
			case WIN_SETMODAL_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_SETMODAL_EVENT ****")
				delete (WindowSetModalEventParam*)param;
				break;
			}
			case WIN_RESIZE_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_RESIZE_EVENT ****")
				delete (WindowReSizeEventParam*)param;
				break;
			}
			case WIN_DESTROY_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_DESTROY_EVENT ****")
				delete param;
				break;
			}
			case WIN_SET_TITLE_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_SET_TITLE_EVENT ****")
				delete (WindowTitleEventParam*)param;
				break;
			}
			case WIN_CHROME_FLAG_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_CHROME_FLAG_EVENT ****")
				delete (WindowChromeEventParam*)param;
				break;
			}
			case WIN_REALIZED_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** WIN_REALIZED_EVENT ****")
				delete param;
				break;
			}
			default:
			{
				JREX_LOGLN("createJavaObject()--> **** UNKNOW WINDOW EVENT TYPE ****")
			}
		}
	}

	nsresult JRex_JNI_WindowEvent::fireEvent(BasicWindowEventParam* wParam, PRBool isSync, void **_result){

		JREX_LOGLN("fireEvent()--> **** wParam <"<<wParam<<"> ****")
		if(isSync)
			NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

    	JRexJavaEvent* event = new JRexJavaEvent;
		if (event) {
			JREX_LOGLN("fireEvent()--> **** JRexJavaEvent Created ****")
			event->eventType=WINDOW_EVENT;
			event->eventData=wParam;
			void* result=nsnull;
			rv=isSync?postSyncJavaEvent(event,(void **)&result):postJavaEvent(event);
			JREX_LOGLN("fireEvent()--> **** postJavaEvent isSync<"<<isSync<<"> rv<"<<rv<<">****")
			if (NS_SUCCEEDED(rv) && isSync){
				*_result=result;
				JREX_LOGLN("fireEvent()--> **** postSyncJavaEvent _result<"<<*_result<<"****")
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

