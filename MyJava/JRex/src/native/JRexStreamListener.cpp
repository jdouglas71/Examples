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

#include "JRexStreamListener.h"
using namespace JREX_JNI_UTIL;

#define CNTNT_TYPE		"Content-Type"
#define CNTNT_CHARSET	"Content-CharSet"
#define CNTNT_LEN		"Content-Length"

JRexStreamListener::JRexStreamListener(jobject streamListener):mCurInStream(nsnull),mCurJInStream(NULL){
    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("JRexStreamListener()--> **** env<"<<env<<"> ****")
    if(env && streamListener)
		mStreamListener=env->NewGlobalRef(streamListener);
	else{
		JREX_LOGLN("JRexStreamListener()--> **** CREATION FAILED!!!!!!!!!****")
		throw NS_ERROR_NULL_POINTER;
	}
	JREX_LOGLN("JRexStreamListener()--> **** mStreamListener<"<<mStreamListener<<"> ****")
}

//Bill Filler <bfiller@pepper.com>: Added interface map
//so QueryInteface will work correctly
NS_INTERFACE_MAP_BEGIN(JRexStreamListener)
	NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, nsIStreamListener)
	NS_INTERFACE_MAP_ENTRY(nsIStreamListener)
	NS_INTERFACE_MAP_ENTRY(nsIRequestObserver)
NS_INTERFACE_MAP_END

NS_IMPL_THREADSAFE_ADDREF(JRexStreamListener)
NS_IMPL_THREADSAFE_RELEASE(JRexStreamListener)

JRexStreamListener::~JRexStreamListener(){
	JNIEnv *env = JRex_GetEnv(0);
    JREX_LOGLN("~JRexStreamListener()--> **** env<"<<env<<"> ****")
    if(env){
		if(mCurJInStream){
			env->CallVoidMethod(mCurJInStream,jrexInputCloseMID);
			JREX_LOGLN("~JRexStreamListener()--> **** deleting mCurJInStream global ref ****")
			env->DeleteGlobalRef(mCurJInStream);
			mCurJInStream=NULL;
		}
		if(mStreamListener){
			JREX_LOGLN("~JRexStreamListener()--> **** deleting mStreamListener global ref ****")
			env->DeleteGlobalRef(mStreamListener);
			mStreamListener=NULL;
		}
	}
	JREX_LOGLN("~JRexStreamListener()--> **** Done ****")
}


/**
* Called to signify the beginning of an asynchronous request.
*
* @param aRequest request being observed
* @param aContext user defined context
*
* An exception thrown from onStartRequest has the side-effect of
* causing the request to be canceled.
*/

NS_IMETHODIMP JRexStreamListener::OnStartRequest(nsIRequest *aRequest, nsISupports *aContext){
	JREX_LOGLN("OnStartRequest()--> *** I AM HERE ***")
	char* reqName=nsnull;
	nsresult reqStatus=0;
	PRBool isReqPending=PR_FALSE;

    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("OnStartRequest()--> **** env<"<<env<<"> ****")
    if(!env)
    	return NS_ERROR_FAILURE;

	jobject hashTableObj=NULL;
	if(NOT_NULL(aRequest)){
		JREX_LOGLN("OnStartRequest()--> *** NOT_NULL aRequest ***")
		nsEmbedCString temp;
		nsresult rv=aRequest->GetName(temp);
		if(NS_SUCCEEDED(rv))
			reqName=ToNewCString(temp);
		else
			reqName=nsnull;

		JREX_LOGLN("OnStartRequest()--> *** reqName<"<<(PRUint32)reqName<<"> ***")
		aRequest->GetStatus(&rv);
		reqStatus=rv;
		aRequest->IsPending(&isReqPending);

    	nsCOMPtr<nsIChannel> channel(do_QueryInterface(aRequest));
    	if(channel){
			hashTableObj = env->NewObject(JRexHeaderVisitor::hashTableCls, JRexHeaderVisitor::hashTableCID,10);
			JREX_LOGLN("OnStartRequest()--> **** hashTableObj<"<<hashTableObj<<"> ****")
			JNI_IF_EXP_DESC_CLR_RET("OnStartRequest()--> **** New hashTableObject Failed with Exception ****",NS_ERROR_FAILURE)

  			nsCOMPtr<nsIHttpChannel> httpChannel=nsnull;
			if(httpChannel=do_QueryInterface(channel)){
    			JRexHeaderVisitor *visitor = new JRexHeaderVisitor(hashTableObj);
    			if (visitor){
				    NS_ADDREF(visitor);
					rv=httpChannel->VisitRequestHeaders(visitor);
					JREX_LOGLN("OnStartRequest()--> **** VisitRequestHeaders rv<"<<rv<<">****")
					rv=httpChannel->VisitResponseHeaders(visitor);
					JREX_LOGLN("OnStartRequest()--> **** VisitResponseHeaders rv<"<<rv<<">****")
				    NS_RELEASE(visitor);
  				}
			}else{
				nsEmbedCString rval;
				rv=channel->GetContentType(rval);
				JREX_LOGLN("OnStartRequest()--> **** GetContentType rv<"<<rv<<"> Value="<<rval.get()<<" ****")
				if(NS_SUCCEEDED(rv) && rval.get()){
					env->CallObjectMethod(hashTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_TYPE),env->NewStringUTF(rval.get()));
				}
				rv=channel->GetContentCharset(rval);
				JREX_LOGLN("OnStartRequest()--> **** GetContentCharset rv<"<<rv<<"> Value="<<rval.get()<<" ****")
				if(NS_SUCCEEDED(rv) && rval.get()){
					env->CallObjectMethod(hashTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_CHARSET),env->NewStringUTF(rval.get()));
				}
				PRInt32 intRval=0;
				rv=channel->GetContentLength(&intRval);
				JREX_LOGLN("OnStartRequest()--> **** GetContentLength rv<"<<rv<<"> Value="<<intRval<<" ****")
				if(NS_SUCCEEDED(rv) && intRval){
					char strRval[128];
					sprintf(strRval,"%d",intRval);
					env->CallObjectMethod(hashTableObj,JRexHeaderVisitor::hashTablePutMID,
							env->NewStringUTF(CNTNT_LEN),env->NewStringUTF(strRval));
				}
			}
		}
	}else{
		JREX_LOGLN("OnStartRequest()--> *** NULL aRequest ***")
		reqName=nsnull;
		reqStatus=NS_OK;
		isReqPending=PR_FALSE;
	}

	jstring jreqName=NULL;
	if(NOT_NULL(reqName)){
		JREX_LOGLN("OnStartRequest()--> **** reqName<"<<reqName<<"> ****")
		jreqName=env->NewStringUTF(reqName);
		nsMemory::Free(reqName);
	}
	JREX_LOGLN("OnStartRequest()--> **** jreqName<"<<jreqName<<"> ****")

	jboolean jrval=env->CallBooleanMethod(mStreamListener,onStartMID,jreqName,(jint)reqStatus,
						isReqPending==PR_TRUE?JNI_TRUE:JNI_FALSE, NULL, hashTableObj);
	JNI_IF_EXP_DESC_CLR_RET("OnStartRequest()--> **** Failed with Exception ****",NS_ERROR_FAILURE)
	if(hashTableObj)env->DeleteLocalRef(hashTableObj);
	if(jreqName)env->DeleteLocalRef(jreqName);
	JREX_LOGLN("OnStartRequest()--> **** jrval<"<<jrval<<"> ****")
	return jrval==JNI_TRUE?NS_OK:NS_ERROR_FAILURE;
}


/**
* Called when the next chunk of data (corresponding to the request) may
* be read without blocking the calling thread.  The onDataAvailable impl
* must read exactly |aCount| bytes of data before returning.
*
* @param aRequest request corresponding to the source of the data
* @param aContext user defined context
* @param aInputStream input stream containing the data chunk
* @param aOffset current stream position
* @param aCount number of bytes available in the stream
*
* An exception thrown from onDataAvailable has the side-effect of
* causing the request to be canceled.
*/

NS_IMETHODIMP JRexStreamListener::OnDataAvailable(nsIRequest *aRequest, nsISupports *aContext, nsIInputStream *aInputStream, PRUint32 aOffset, PRUint32 aCount){
	JREX_LOGLN("OnDataAvailable()--> *** I AM HERE ***")
	char* reqName=nsnull;
	nsresult reqStatus=0;
	PRBool isReqPending=PR_FALSE;

	if(NOT_NULL(aRequest)){
		JREX_LOGLN("OnDataAvailable()--> *** NOT_NULL aRequest ***")
		nsEmbedCString temp;
		nsresult rv=aRequest->GetName(temp);
		if(NS_SUCCEEDED(rv))
			reqName=ToNewCString(temp);
		else
			reqName=nsnull;

		JREX_LOGLN("OnDataAvailable()--> *** reqName<"<<(PRUint32)reqName<<"> ***")
		aRequest->GetStatus(&rv);
		reqStatus=rv;
		aRequest->IsPending(&isReqPending);
	}else{
		JREX_LOGLN("OnDataAvailable()--> *** NULL aRequest ***")
		reqName=nsnull;
		reqStatus=NS_OK;
		isReqPending=PR_FALSE;
	}

    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("OnDataAvailable()--> **** env<"<<env<<"> ****")
    if(!env)
    	return NS_ERROR_FAILURE;

	jstring jreqName=NULL;
	if(NOT_NULL(reqName)){
		JREX_LOGLN("OnDataAvailable()--> **** reqName<"<<reqName<<"> ****")
		jreqName=env->NewStringUTF(reqName);
		nsMemory::Free(reqName);
	}
	JREX_LOGLN("OnDataAvailable()--> **** jreqName<"<<jreqName<<"> ****")
	if(mCurInStream==nsnull || mCurInStream!=aInputStream){
		NS_ADDREF(mCurInStream=aInputStream);
		if(mCurJInStream){
			env->CallVoidMethod(mCurJInStream,jrexInputCloseMID);
			JREX_LOGLN("OnDataAvailable()--> **** deleting mCurJInStream global ref ****")
			env->DeleteGlobalRef(mCurJInStream);
			mCurJInStream=NULL;
		}
	    jobject jrexInputStreamObj = env->NewObject(jrexInputStreamCls,jrexInputCID,(jint)NS_PTR_TO_INT32(mCurInStream));
	    JREX_LOGLN("OnDataAvailable()--> **** jrexInputStreamObj<"<<jrexInputStreamObj<<"> ****")
	    JNI_IF_EXP_DESC_CLR_RET("OnDataAvailable()--> **** NewObject Failed with Exception ****",NS_ERROR_FAILURE)
	    mCurJInStream=env->NewGlobalRef(jrexInputStreamObj);
	    env->DeleteLocalRef(jrexInputStreamObj);
	}
	jboolean jrval=env->CallBooleanMethod(mStreamListener,availableMID,jreqName,(jint)reqStatus,isReqPending==PR_TRUE?JNI_TRUE:JNI_FALSE
							, NULL, mCurJInStream, (jint)aOffset, (jint)aCount );
	JNI_IF_EXP_DESC_CLR_RET("OnDataAvailable()--> **** CallBooleanMethod Failed with Exception ****",NS_ERROR_FAILURE)
	if(jreqName)env->DeleteLocalRef(jreqName);
	JREX_LOGLN("OnDataAvailable()--> **** jrval<"<<jrval<<"> ****")
	return jrval==JNI_TRUE?NS_OK:NS_ERROR_FAILURE;
}

/**
* Called to signify the end of an asynchronous request.  This
* call is always preceded by a call to onStartRequest.
*
* @param aRequest request being observed
* @param aContext user defined context
* @param aStatusCode reason for stopping (NS_OK if completed successfully)
*
* An exception thrown from onStopRequest is generally ignored.
*/
NS_IMETHODIMP JRexStreamListener::OnStopRequest(nsIRequest *aRequest, nsISupports *aContext, nsresult aStatusCode){
	JREX_LOGLN("OnStopRequest()--> *** aStatusCode<"<<aStatusCode<<"> ***")
	char* reqName=nsnull;
	nsresult reqStatus=0;
	PRBool isReqPending=PR_FALSE;

	if(NOT_NULL(aRequest)){
		JREX_LOGLN("OnStopRequest()--> *** NOT_NULL aRequest ***")
		nsEmbedCString temp;
		nsresult rv=aRequest->GetName(temp);
		if(NS_SUCCEEDED(rv))
			reqName=ToNewCString(temp);
		else
			reqName=nsnull;

		JREX_LOGLN("OnStopRequest()--> *** reqName<"<<(PRUint32)reqName<<"> ***")
		aRequest->GetStatus(&rv);
		reqStatus=rv;
		aRequest->IsPending(&isReqPending);
	}else{
		JREX_LOGLN("OnStopRequest()--> *** NULL aRequest ***")
		reqName=nsnull;
		reqStatus=NS_OK;
		isReqPending=PR_FALSE;
	}

    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("OnStopRequest()--> **** env<"<<env<<"> ****")
    if(!env)
    	return NS_ERROR_FAILURE;

	jstring jreqName=NULL;
	if(NOT_NULL(reqName)){
		JREX_LOGLN("OnStopRequest()--> **** reqName<"<<reqName<<"> ****")
		jreqName=env->NewStringUTF(reqName);
		nsMemory::Free(reqName);
	}
	JREX_LOGLN("OnStopRequest()--> **** jreqName<"<<jreqName<<"> ****")

	env->CallVoidMethod(mStreamListener,onStopMID,jreqName,(jint)reqStatus,isReqPending==PR_TRUE?JNI_TRUE:JNI_FALSE
							, NULL,(jint)aStatusCode);
	JNI_IF_EXP_DESC_CLR_RET("OnStopRequest()--> **** CallVoidMethod Failed with Exception ****",NS_ERROR_FAILURE)
	if(jreqName)env->DeleteLocalRef(jreqName);
	return NS_OK;
}

