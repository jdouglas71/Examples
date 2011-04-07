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

#include "JRex_JNI_ProgressEvent.h"
using namespace JRex_JNI_Event;
using namespace JRex_JNI_ProgressEvent;

#define CNTNT_TYPE		"Content-Type"
#define CNTNT_CHARSET	"Content-CharSet"
#define CNTNT_LEN		"Content-Length"

	static inline jobject createMainProgressEventJavaObject(JNIEnv *env, BasicProgressEventParam* param, jobject progParamObj);
	static inline jobject createStateChangeEventJavaObject(JNIEnv *env, StateChangeProgressEventParam* param);
	static inline jobject createProgressChangeEventJavaObject(JNIEnv *env, ProgressChangeProgressEventParam* param);
	static inline jobject createLocationChangeEventJavaObject(JNIEnv *env, LocationChangeProgressEventParam* param);
	static inline jobject createStatusChangeEventJavaObject(JNIEnv *env, StatusChangeProgressEventParam* param);
	static inline jobject createSecurityChangeEventJavaObject(JNIEnv *env, StateChangeProgressEventParam* param);


	jobject JRex_JNI_ProgressEvent::createJavaObject(JNIEnv *env, BasicProgressEventParam* param){
		jobject jrv=NULL;

		jshort progEventType=param->progEventType;
		switch(progEventType){
			case PROG_STATE_CHANGE:
			{
				JREX_LOGLN("createJavaObject()--> **** PROG_STATE_CHANGE ****")
				jrv=createStateChangeEventJavaObject(env,(StateChangeProgressEventParam*)param);
				break;
			}
			case PROG_PROGRESS_CHANGE:
			{
				JREX_LOGLN("createJavaObject()--> **** PROG_PROGRESS_CHANGE ****")
				jrv=createProgressChangeEventJavaObject(env,(ProgressChangeProgressEventParam*)param);
				break;
			}
			case PROG_LOC_CHANGE:
			{
				JREX_LOGLN("createJavaObject()--> **** PROG_LOC_CHANGE ****")
				jrv=createLocationChangeEventJavaObject(env,(LocationChangeProgressEventParam*)param);
				break;
			}
			case PROG_STATUS_CHANGE:
			case PROG_LINK_STATUS_CHANGE:
			{
				JREX_LOGLN("createJavaObject()--> **** PROG_STATUS_CHANGE || PROG_WIN_STATUS_CHANGE****")
				jrv=createStatusChangeEventJavaObject(env,(StatusChangeProgressEventParam*)param);
				break;
			}
			case PROG_SECURITY_CHANGE:
			{
				JREX_LOGLN("createJavaObject()--> **** PROG_SECURITY_CHANGE ****")
				jrv=createSecurityChangeEventJavaObject(env,(StateChangeProgressEventParam*)param);
				break;
			}
			default:
			{
				JREX_LOGLN("createJavaObject()--> **** UNKNOWN PROGRESSS EVENT ****")
			}
		}
		JNI_IF_EXP_DESC_CLR_RET("createJavaObject()--> **** ProgressEvent New jrv Failed with Exception ****", (jobject)NULL)
		JREX_LOGLN("createJavaObject()--> **** jrv<"<<jrv<<"> ****")
		return jrv;
	}


	jobject createMainProgressEventJavaObject(JNIEnv *env, BasicProgressEventParam* param, jobject progParamObj){
		JNI_IF_EXP_DESC_CLR_RET("createMainProgressEventJavaObject()--> **** ProgressEvent New ParamObj Failed with Exception ****", (jobject)NULL)
		jboolean isLoadingDoc=(param->isLoadingDoc==PR_TRUE?JNI_TRUE:JNI_FALSE);
		jstring jreqName=NULL;
		if(NOT_NULL(param->reqName)){
			JREX_LOGLN("createMainProgressEventJavaObject()--> **** param->reqName<"<<param->reqName<<"> ****")
			jreqName=env->NewStringUTF(param->reqName);
			nsMemory::Free(param->reqName);
		}
		JREX_LOGLN("createMainProgressEventJavaObject()--> **** jreqName<"<<jreqName<<"> ****")
		jint reqStatus=param->reqStatus;
		jboolean isReqPending=(param->isReqPending==PR_TRUE?JNI_TRUE:JNI_FALSE);

		jobject rObj=env->NewObject(ProgressEventFields::progEvtCls,ProgressEventFields::cid,
								(jint)param->target, (jint)param->progEventType, isLoadingDoc, jreqName,
										(jint)reqStatus,isReqPending, progParamObj);
		if(jreqName)env->DeleteLocalRef(jreqName);
		return rObj;
	}

	jobject createStateChangeEventJavaObject(JNIEnv *env, StateChangeProgressEventParam* param){
		jint  stateFlags=param->stateFlags;
		jint status=param->status;

		jobject hashReqTableObj=NULL;
		jobject hashRespTableObj=NULL;
    	nsCOMPtr<nsIChannel> channel;

    	if(param->request && (channel=do_QueryInterface(param->request))){
			hashRespTableObj = env->NewObject(JRexHeaderVisitor::hashTableCls, JRexHeaderVisitor::hashTableCID,10);
			JREX_LOGLN("createStateChangeEventJavaObject()--> **** hashRespTableObj<"<<hashRespTableObj<<"> ****")
			JNI_IF_EXP_DESC_CLR_RET("createStateChangeEventJavaObject()--> **** New hashTableObject Failed with Exception ****", (jobject)NULL)

  			nsCOMPtr<nsIHttpChannel> httpChannel=nsnull;
  			nsresult rv=NS_OK;
			if(httpChannel=do_QueryInterface(channel)){
    			JRexHeaderVisitor *visitor = new JRexHeaderVisitor(hashRespTableObj);
    			if (visitor){
				    NS_ADDREF(visitor);
					rv=httpChannel->VisitResponseHeaders(visitor);
					JREX_LOGLN("createStateChangeEventJavaObject()--> **** VisitResponseHeaders rv<"<<rv<<">****")
				    NS_RELEASE(visitor);
				}
				hashReqTableObj = env->NewObject(JRexHeaderVisitor::hashTableCls, JRexHeaderVisitor::hashTableCID,10);
				JREX_LOGLN("createStateChangeEventJavaObject()--> **** hashReqTableObj<"<<hashReqTableObj<<"> ****")
				JNI_IF_EXP_DESC_CLR_RET("createStateChangeEventJavaObject()--> **** New hashReqTableObj Failed with Exception ****", (jobject)NULL)
				visitor = new JRexHeaderVisitor(hashReqTableObj);
    			if (visitor){
				    NS_ADDREF(visitor);
					rv=httpChannel->VisitRequestHeaders(visitor);
					JREX_LOGLN("createStateChangeEventJavaObject()--> **** VisitRequestHeaders rv<"<<rv<<">****")
				    NS_RELEASE(visitor);
				}
			}else{
				nsEmbedCString rval;
				rv=channel->GetContentType(rval);
				JREX_LOGLN("createStateChangeEventJavaObject()--> **** GetContentType rv<"<<rv<<"> Value="<<rval.get()<<" ****")
				if(NS_SUCCEEDED(rv) && rval.get()){
					env->CallObjectMethod(hashRespTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_TYPE),env->NewStringUTF(rval.get()));
				}
				rv=channel->GetContentCharset(rval);
				JREX_LOGLN("createStateChangeEventJavaObject()--> **** GetContentCharset rv<"<<rv<<"> Value="<<rval.get()<<" ****")
				if(NS_SUCCEEDED(rv) && rval.get()){
					env->CallObjectMethod(hashRespTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_CHARSET),env->NewStringUTF(rval.get()));
				}
				PRInt32 intRval=0;
				rv=channel->GetContentLength(&intRval);
				JREX_LOGLN("createStateChangeEventJavaObject()--> **** GetContentLength rv<"<<rv<<"> Value="<<intRval<<" ****")
				if(NS_SUCCEEDED(rv) && intRval){
					char strRval[128];
					sprintf(strRval,"%d",intRval);
					env->CallObjectMethod(hashRespTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_LEN),env->NewStringUTF(strRval), hashReqTableObj, hashRespTableObj);
				}
			}
		}

		jobject progParamObj=env->NewObject(ProgressEventFields::stateChangePrmCls,ProgressEventFields::stateChangeCID,
											stateFlags, status, hashReqTableObj, hashRespTableObj);
		if(hashReqTableObj)env->DeleteLocalRef(hashReqTableObj);
		if(hashRespTableObj)env->DeleteLocalRef(hashRespTableObj);
		JREX_LOGLN("createStateChangeEventJavaObject()--> **** progParamObj<"<<progParamObj<<"> ****")
		jobject rObj= createMainProgressEventJavaObject(env,param,progParamObj);
		if(progParamObj)env->DeleteLocalRef(progParamObj);
		return rObj;
	}

	jobject createProgressChangeEventJavaObject(JNIEnv *env, ProgressChangeProgressEventParam* param){
		jint curSelfProgress=param->curSelfProgress;
		jint maxSelfProgress=param->maxSelfProgress;
		jint curTotalProgress=param->curTotalProgress;
		jint maxTotalProgress=param->maxTotalProgress;

		jobject progParamObj=env->NewObject(ProgressEventFields::progressChangePrmCls,ProgressEventFields::progressChangeCID,
											(jint)curSelfProgress, (jint)maxSelfProgress, (jint)curTotalProgress, (jint)maxTotalProgress);
		JREX_LOGLN("createProgressChangeEventJavaObject()--> **** progParamObj<"<<progParamObj<<"> ****")
		jobject rObj= createMainProgressEventJavaObject(env,param,progParamObj);
		if(progParamObj)env->DeleteLocalRef(progParamObj);
		return rObj;
	}

	jobject createLocationChangeEventJavaObject(JNIEnv *env, LocationChangeProgressEventParam* param){
		jstring jloc=NULL;
		if(NOT_NULL(param->loc)){
			JREX_LOGLN("createLocationChangeEventJavaObject()--> **** param->loc<"<<param->loc<<"> ****")
			jloc=env->NewStringUTF(param->loc);
			nsMemory::Free(param->loc);
		}
		JREX_LOGLN("createLocationChangeEventJavaObject()--> **** jloc<"<<jloc<<"> ****")
		jobject rObj= createMainProgressEventJavaObject(env,param,jloc);
		if(jloc)env->DeleteLocalRef(jloc);
		return rObj;
	}

	jobject createStatusChangeEventJavaObject(JNIEnv *env, StatusChangeProgressEventParam* param){
		jint status=param->status;
		jstring jmsg=NULL;
		if(NOT_NULL(param->statusMessage)){
			JREX_LOGLN("createStatusChangeEventJavaObject()--> **** param->statusMessage<"<<param->statusMessage<<"> ****")
			jmsg=env->NewStringUTF(param->statusMessage);
			nsMemory::Free(param->statusMessage);
		}
		JREX_LOGLN("createStatusChangeEventJavaObject()--> **** jmsg<"<<jmsg<<"> ****")
		jobject progParamObj=env->NewObject(ProgressEventFields::statusChangePrmCls,ProgressEventFields::statusChangeCID,
											(jint)status,jmsg);
		JREX_LOGLN("createStateChangeEventJavaObject()--> **** progParamObj<"<<progParamObj<<"> ****")
		if(jmsg)env->DeleteLocalRef(jmsg);
		jobject rObj= createMainProgressEventJavaObject(env,param,progParamObj);
		if(progParamObj)env->DeleteLocalRef(progParamObj);
		return rObj;
	}

	jobject createSecurityChangeEventJavaObject(JNIEnv *env, StateChangeProgressEventParam* param){
		jint stateFlags=param->stateFlags;
		jint status=param->status;
		jobject progParamObj=env->NewObject(ProgressEventFields::stateChangePrmCls,ProgressEventFields::stateChangeCID,
											(jint)stateFlags, (jint)status, NULL, NULL);
		JREX_LOGLN("createSecurityChangeEventJavaObject()--> **** progParamObj<"<<progParamObj<<"> ****")
		jobject rObj= createMainProgressEventJavaObject(env,param,progParamObj);
		if(progParamObj)env->DeleteLocalRef(progParamObj);
		return rObj;
	}


	nsresult JRex_JNI_ProgressEvent::getNativeData(JNIEnv *env, jobject jobj, BasicProgressEventParam* hsParam, void** _result){
		return NS_ERROR_NOT_IMPLEMENTED;
	}

	void JRex_JNI_ProgressEvent::deleteEventData(PRUint32  progEventType, BasicProgressEventParam* param){
		switch(progEventType){
			case PROG_STATE_CHANGE:
			{
				JREX_LOGLN("deleteEventData()--> **** PROG_STATE_CHANGE ****")
				delete (StateChangeProgressEventParam*)param;
				break;
			}
			case PROG_PROGRESS_CHANGE:
			{
				JREX_LOGLN("deleteEventData()--> **** PROG_PROGRESS_CHANGE ****")
				delete (ProgressChangeProgressEventParam*)param;
				break;
			}
			case PROG_LOC_CHANGE:
			{
				JREX_LOGLN("deleteEventData()--> **** PROG_LOC_CHANGE ****")
				delete (LocationChangeProgressEventParam*)param;
				break;
			}
			case PROG_STATUS_CHANGE:
			case PROG_LINK_STATUS_CHANGE:
			{
				JREX_LOGLN("deleteEventData()--> **** PROG_STATUS_CHANGE || PROG_WIN_STATUS_CHANGE****")
				delete (StatusChangeProgressEventParam*)param;
				break;
			}
			case PROG_SECURITY_CHANGE:
			{
				JREX_LOGLN("deleteEventData()--> **** PROG_SECURITY_CHANGE ****")
				delete (StateChangeProgressEventParam*)param;
				break;
			}
			default:
			{
				JREX_LOGLN("deleteEventData()--> **** UNKNOWN PROGRESSS EVENT ****")
			}
		}

	}

	nsresult JRex_JNI_ProgressEvent::fireEvent(BasicProgressEventParam* pParam, PRBool isSync, void **_result){

		JREX_LOGLN("fireEvent()--> **** pParam <"<<pParam<<"> ****")
		if(isSync)
			NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

    	JRexJavaEvent* event = new JRexJavaEvent;
		if (event) {
			JREX_LOGLN("fireEvent()--> **** JRexJavaEvent Created ****")
			event->eventType=PROGRESS_EVENT;
			event->eventData=pParam;
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


	void JRex_JNI_ProgressEvent::SetCommonParam(BasicProgressEventParam* sParm, nsIWebProgress *aWebProgress, nsIRequest *aRequest){
		if(NOT_NULL(aWebProgress)){
			PRBool temp=PR_FALSE;
			aWebProgress->GetIsLoadingDocument(&temp);
			sParm->isLoadingDoc=temp;
		}else
			sParm->isLoadingDoc=PR_FALSE;

		if(NOT_NULL(aRequest)){
			JREX_LOGLN("SetCommonParam()--> *** NOT_NULL aRequest ***")
			nsEmbedCString temp;
			nsresult rv=aRequest->GetName(temp);
			if(NS_SUCCEEDED(rv))
				sParm->reqName=ToNewCString(temp);
			else
				sParm->reqName=nsnull;

			JREX_LOGLN("SetCommonParam()--> ***  sParm->reqName<"<<(PRUint32)sParm->reqName<<"> ***")

			aRequest->GetStatus(&rv);
			sParm->reqStatus=rv;

			PRBool isReqPending=PR_FALSE;
			aRequest->IsPending(&isReqPending);
			sParm->isReqPending=isReqPending;
		}else{
			JREX_LOGLN("SetCommonParam()--> *** NULL aRequest ***")
			sParm->reqName=nsnull;
			sParm->reqStatus=NS_OK;
			sParm->isReqPending=PR_FALSE;
		}
	}
