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

#include "JRex_JNI_URIContentEvent.h"
#include "JRexStreamListener.h"

using namespace JRex_JNI_Event;
using namespace JRex_JNI_URIContentEvent;

	static inline jobject createMainURIContentEventJavaObject(JNIEnv *env, BasicURIContentEventParam* param, jobject uriParamObj);
	static inline jobject createURIStartEventJavaObject(JNIEnv *env, OnStartEventParam* param);
	static inline jobject createDoContentEventJavaObject(JNIEnv *env, DoContentEventParam* param);
	static inline jobject createIsPreferredEventJavaObject(JNIEnv *env, IsPreferredEventParam* param);
	static inline jobject createCanHandleContentEventJavaObject(JNIEnv *env, CanHandleEventParam* param);

	jobject JRex_JNI_URIContentEvent::createJavaObject(JNIEnv *env, BasicURIContentEventParam* param){

		jobject jrv=NULL;
		jshort uriEventType=param->uriEventType;

		switch(uriEventType){
			case URI_ON_START_EVENT:
			{
				JREX_LOGLN("createJavaObject()--> **** URI_ON_START_EVENT ****")
				jrv=createURIStartEventJavaObject(env,(OnStartEventParam*)param);
				break;
			}
			case URI_DO_CONTENT:
			{
				JREX_LOGLN("createJavaObject()--> **** URI_DO_CONTENT ****")
				jrv=createDoContentEventJavaObject(env,(DoContentEventParam*)param);
				break;
			}
			case URI_IS_PREFERRED:
			{
				JREX_LOGLN("createJavaObject()--> **** URI_IS_PREFERRED ****")
				jrv=createIsPreferredEventJavaObject(env,(IsPreferredEventParam*)param);
				break;
			}
			case URI_CAN_HANDLE_CONTENT:
			{
				JREX_LOGLN("createJavaObject()--> **** URI_CAN_HANDLE_CONTENT ****")
				jrv=createCanHandleContentEventJavaObject(env,(CanHandleEventParam*)param);
				break;
			}
			case URI_GET_LOAD_COOKIE:
			case URI_SET_LOAD_COOKIE:
			default:
			{
				JREX_LOGLN("createJavaObject()--> **** COOKIE/UNKNOWN URIContent EVENT ****")
			}
		}
		JNI_IF_EXP_DESC_CLR_RET("createJavaObject()--> **** URIContentEvent New jrv Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createJavaObject()--> **** jrv<"<<jrv<<"> ****")
		return jrv;
	}


	jobject createMainURIContentEventJavaObject(JNIEnv *env, BasicURIContentEventParam* param, jobject uriParamObj){
		JNI_IF_EXP_DESC_CLR_RET("createMainURIContentEventJavaObject()--> **** New ParamObj Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createMainURIContentEventJavaObject()--> **** I AM HERE ****")
		return env->NewObject(URIContentEventFields::uriContentEvtCls,URIContentEventFields::cid,
								(jint)param->target, (jint)param->uriEventType, uriParamObj);
	}


	jobject createURIStartEventJavaObject(JNIEnv *env, OnStartEventParam* param){
		jstring juri=NULL;
		if(NOT_NULL(param->uri)){
			JREX_LOGLN("createURIStartEventJavaObject()--> **** param->uri<"<<param->uri<<"> ****")
			juri=env->NewStringUTF(param->uri);
			nsMemory::Free(param->uri);
		}
		JREX_LOGLN("createURIStartEventJavaObject()--> **** juri<"<<juri<<"> ****")
		jobject rObj= createMainURIContentEventJavaObject(env,param,juri);
		if(juri)env->DeleteLocalRef(juri);
		return rObj;
	}


	jobject createDoContentEventJavaObject(JNIEnv *env, DoContentEventParam* param){
		jboolean isContentPreferred=(param->isContentPreferred==PR_TRUE?JNI_TRUE:JNI_FALSE);
		JREX_LOGLN("createDoContentEventJavaObject()--> **** isContentPreferred<"<<isContentPreferred<<"> ****")

		jstring jContType=NULL;
		if(NOT_NULL(param->contentType)){
			JREX_LOGLN("createDoContentEventJavaObject()--> **** param->contentType<"<<param->contentType<<"> ****")
			jContType=env->NewStringUTF(param->contentType);
			nsMemory::Free(param->contentType);
		}
		JREX_LOGLN("createDoContentEventJavaObject()--> **** jContType<"<<jContType<<"> ****")

		jstring jreqName=NULL;
		if(NOT_NULL(param->reqName)){
			JREX_LOGLN("createDoContentEventJavaObject()--> **** param->reqName<"<<param->reqName<<"> ****")
			jreqName=env->NewStringUTF(param->reqName);
			nsMemory::Free(param->reqName);
		}
		JREX_LOGLN("createDoContentEventJavaObject()--> **** jreqName<"<<jreqName<<"> ****")
		jint reqStatus=param->reqStatus;
		jboolean isReqPending=(param->isReqPending==PR_TRUE?JNI_TRUE:JNI_FALSE);

		JREX_LOGLN("createDoContentEventJavaObject()--> **** reqStatus<"<<reqStatus<<"> isReqPending<"<<isReqPending<<"> ****")

		jobject uriParamObj=env->NewObject(URIContentEventFields::doContentPrmCls,URIContentEventFields::doContentCID,
								isContentPreferred, jContType, jreqName,reqStatus, isReqPending);
		JREX_LOGLN("createDoContentEventJavaObject()--> **** uriParamObj<"<<uriParamObj<<"> ****")
		if(jContType)env->DeleteLocalRef(jContType);
		if(jreqName)env->DeleteLocalRef(jreqName);
		jobject rObj= createMainURIContentEventJavaObject(env,param,uriParamObj);
		if(uriParamObj)env->DeleteLocalRef(uriParamObj);
		return rObj;
	}


	jobject createIsPreferredEventJavaObject(JNIEnv *env, IsPreferredEventParam* param){
		jstring jContType=NULL;
		if(NOT_NULL(param->contentType)){
			JREX_LOGLN("createIsPreferredEventJavaObject()--> **** param->contentType<"<<param->contentType<<"> ****")
			jContType=env->NewStringUTF(param->contentType);
			nsMemory::Free(param->contentType);
		}
		JREX_LOGLN("createIsPreferredEventJavaObject()--> **** jContType<"<<jContType<<"> ****")
		jobject rObj =createMainURIContentEventJavaObject(env,param,jContType);
		if(jContType)env->DeleteLocalRef(jContType);
		return rObj;
	}


	jobject createCanHandleContentEventJavaObject(JNIEnv *env, CanHandleEventParam* param){

		jboolean isContentPreferred=(param->isContentPreferred==PR_TRUE?JNI_TRUE:JNI_FALSE);
		JREX_LOGLN("createCanHandleContentEventJavaObject()--> **** isContentPreferred<"<<isContentPreferred<<"> ****")

		jstring jContType=NULL;
		if(NOT_NULL(param->contentType)){
			JREX_LOGLN("createCanHandleContentEventJavaObject()--> **** param->contentType<"<<param->contentType<<"> ****")
			jContType=env->NewStringUTF(param->contentType);
			nsMemory::Free(param->contentType);
		}
		JREX_LOGLN("createCanHandleContentEventJavaObject()--> **** jContType<"<<jContType<<"> ****")
		jobject uriParamObj=env->NewObject(URIContentEventFields::canHandlePrmCls,URIContentEventFields::canHandleCID,
								isContentPreferred, jContType);
		JREX_LOGLN("createCanHandleContentEventJavaObject()--> **** uriParamObj<"<<uriParamObj<<"> ****")
		if(jContType)env->DeleteLocalRef(jContType);
		jobject rObj =createMainURIContentEventJavaObject(env,param,uriParamObj);
		if(uriParamObj)env->DeleteLocalRef(uriParamObj);
		return rObj;
	}

	nsresult JRex_JNI_URIContentEvent::getNativeData(JNIEnv *env, jobject jobj, BasicURIContentEventParam* uParam, void** _result){
		nsresult rv=NS_OK;
		if(IS_NULL(jobj)){
			JREX_LOGLN(" JRex_JNI_URIContentEvent getNativeData()--> **** jobj is NULL ****")
			return NS_ERROR_NULL_POINTER;
		}
		switch(uParam->uriEventType){
			case URI_ON_START_EVENT:
			{
				JREX_LOGLN("getNativeData()--> **** URI_ON_START_EVENT ****")
				jboolean canDo=env->CallBooleanMethod(jobj,URIContentEventFields::boolValueID);
				*_result=(void*)(canDo==JNI_TRUE?PR_TRUE:PR_FALSE);
				break;
			}
			case URI_DO_CONTENT:
			{
				JREX_LOGLN("getNativeData()--> **** URI_DO_CONTENT ****")
				jboolean boolRV=env->CallBooleanMethod(jobj,URIContentEventFields::getBoolRV);
				jobject objectRV=env->CallObjectMethod(jobj,URIContentEventFields::getObjectRV);

				URIContentRV* temp =new URIContentRV;
				if(IS_NULL(temp)){
					rv=NS_ERROR_OUT_OF_MEMORY;
					break;
				}
				temp->boolRV=(boolRV==JNI_TRUE?PR_TRUE:PR_FALSE);
				if(NOT_NULL(objectRV)){
					JRexStreamListener* myStrlis= new JRexStreamListener(objectRV);
					if(IS_NULL(myStrlis)){
						rv=NS_ERROR_OUT_OF_MEMORY;
						break;
					}
					temp->data=myStrlis;
				}else
					temp->data=nsnull;
				*_result=(void*)temp;
				break;
			}
			case URI_IS_PREFERRED:
			case URI_CAN_HANDLE_CONTENT:
			{
				JREX_LOGLN("getNativeData()--> **** URI_IS_PREFERRED ****")
				jboolean boolRV=env->CallBooleanMethod(jobj,URIContentEventFields::getBoolRV);
				jstring desiredContTyp=(jstring)env->CallObjectMethod(jobj,URIContentEventFields::getObjectRV);

				URIContentRV* temp =new URIContentRV;
				if(IS_NULL(temp))return NS_ERROR_OUT_OF_MEMORY;

				temp->boolRV=(boolRV==JNI_TRUE?PR_TRUE:PR_FALSE);
				if(NOT_NULL(desiredContTyp)){
					jboolean isCopy=JNI_FALSE;
					const char* cTemp=env->GetStringUTFChars(desiredContTyp,&isCopy);
					nsEmbedCString ecTemp(cTemp);
					temp->data=ToNewCString(ecTemp);
					env->ReleaseStringUTFChars(desiredContTyp,cTemp);
				}else
					temp->data=nsnull;
				*_result=(void*)temp;
				break;
			}
			default:
			{
				JREX_LOGLN("getNativeData()--> **** UNKNOWN URICONTENT EVENT ****")
				rv= NS_ERROR_FAILURE;
			}
		}

		return rv;
	}


	void JRex_JNI_URIContentEvent::deleteEventData(PRUint32  uriEventType, BasicURIContentEventParam* param){
		switch(uriEventType){
			case URI_ON_START_EVENT:
			{
				JREX_LOGLN("deleteEventData()--> **** URI_ON_START_EVENT ****")
                delete (OnStartEventParam*)param;
				break;
			}
			case URI_DO_CONTENT:
			{
				JREX_LOGLN("deleteEventData()--> **** URI_DO_CONTENT ****")
				delete (DoContentEventParam*)param;
				break;
			}
			case URI_IS_PREFERRED:
			{
				JREX_LOGLN("deleteEventData()--> **** URI_IS_PREFERRED ****")
                delete (IsPreferredEventParam*)param;
				break;
			}
			case URI_CAN_HANDLE_CONTENT:
			{
				JREX_LOGLN("deleteEventData()--> **** URI_CAN_HANDLE_CONTENT ****")
                delete (CanHandleEventParam*)param;
				break;
			}
			default:
			{
				JREX_LOGLN("deleteEventData()--> **** UNKNOWN URICONTENT EVENT ****")
			}
		}

	}

	nsresult JRex_JNI_URIContentEvent::fireEvent(BasicURIContentEventParam* hParam, PRBool isSync, void **_result){
		JREX_LOGLN("fireEvent()--> **** hParam <"<<hParam<<"> ****")
		if(isSync)
			NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

    	JRexJavaEvent* event = new JRexJavaEvent;
		if (event) {
			JREX_LOGLN("fireEvent()--> **** JRexJavaEvent Created ****")
			event->eventType=URICONTENT_EVENT;
			event->eventData=hParam;
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

