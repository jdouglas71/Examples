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

#include "org_mozilla_jrex_io_JRexInputStream.h"
#include "JRex_JNI_Util.h"

using namespace JREX_JNI_UTIL;

static jfieldID streamPeerID=0;

//event types for InputStream
enum JRexInputStreamEventTypes{	JREX_AVAILABLE=0U,
								JREX_READ_INT,
								JREX_READ,
								JREX_CLOSE};

static void* PR_CALLBACK HandleJRexInputStreamEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexInputStreamEvent(PLEvent* aEvent);

struct JRexInputStreamEventParam{
	jbyteArray jbyteArr;
	jint offset;
	PRUint32 len;
};


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexInputStream_AvailableInternal(JNIEnv *env, nsIInputStream* in){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if(in){
		PRUint32 avail=0;
		rv=in->Available(&avail);
		JREX_LOGLN("JRexInputStream_Available()--> **** Available rv <"<<rv<<">  avail<"<<avail<<"> ****")
		if(NS_SUCCEEDED(rv))
			jval=(jobject)avail;
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexInputStream_Read__Internal(JNIEnv *env, nsIInputStream* in){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if(in){
	    jbyte *buff = (jbyte*)malloc(sizeof(jbyte));
	    if(buff){
			PRUint32 bytesRead=0;
			rv = in->Read((char*)buff,1,&bytesRead);
			JREX_LOGLN("JRexInputStream_Read__Internal()--> **** Read rv <"<<rv<<"> bytesRead<"<<bytesRead<<"> ****")
			if (NS_SUCCEEDED(rv)) {
				jval=(jobject)((jint)bytesRead>0?buff[0]:-1);
			}
			free(buff);
		}
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexInputStream_Read___3BIIInternal(JNIEnv *env, nsIInputStream* in, jbyteArray jbyteArr, jint offset, PRUint32 len){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if(in){
	    jbyte *buff = (jbyte*)malloc(sizeof(jbyte)*len);
	    if(buff){
			PRUint32 bytesRead=0;
			rv = in->Read((char*)buff ,len, &bytesRead);
			JREX_LOGLN("JRexInputStream_Read___3BIIInternal()--> **** Read rv <"<<rv<<"> bytesRead<"<<bytesRead<<"> ****")
			if (NS_SUCCEEDED(rv)) {
				env->SetByteArrayRegion(jbyteArr,offset,(jint)bytesRead,buff);
				jval=(jobject)bytesRead;
			}
			free(buff);
		}
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexInputStream_CloseInternal(JNIEnv *env, nsIInputStream* in){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if(in){
		rv=in->Close();
		JREX_LOGLN("JRexInputStream_CloseInternal()--> **** Close rv <"<<rv<<"> ****")
		NS_RELEASE(in);
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_event_creator_WindowEvent
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_io_JRexInputStream_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	streamPeerID	= env->GetFieldID(cls, "streamPeer","I");
	JREX_LOGLN("JRexInputStream_initIDs()--> **** streamPeerID <"<<streamPeerID<<"> ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_io_JRexInputStream
 * Method:    Available
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_io_JRexInputStream_Available
  (JNIEnv *env, jobject jinput){
	if(!gXpcomRunning)return -1;

	JREX_TRY
    nsIInputStream* in=(nsIInputStream*)NS_INT32_TO_PTR(env->GetIntField(jinput, streamPeerID));
    JREX_LOGLN("JRexInputStream_Available()--> **** in <"<<in<<"> ****")
	if (!in){
		ThrowJRexException(env, "**** JRexInputStream_Available Native Stream is Invalid!!!!****",0);
	    return -1;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("JRexInputStream_Available()--> **** IN EVT Q THREAD ****")
		jrv=JRexInputStream_AvailableInternal(env, in);
	}else{
		nsresult rv=ExecInEventQ(in, JREX_AVAILABLE, nsnull, PR_TRUE, HandleJRexInputStreamEvent, DestroyJRexInputStreamEvent, (void**)&jrv);
		JREX_LOGLN("JRexInputStream_Available()--> **** ExecInEventQ rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("JRexInputStream_Available()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("JRexInputStream_Available()--> **** Available ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** Available Failed ****",rv);
			return -1;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return -1;
}

/*
 * Class:     org_mozilla_jrex_io_JRexInputStream
 * Method:    Read
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_io_JRexInputStream_Read__
  (JNIEnv *env, jobject jinput){
	if(!gXpcomRunning)return -1;

	JREX_TRY
    nsIInputStream* in=(nsIInputStream*)NS_INT32_TO_PTR(env->GetIntField(jinput, streamPeerID));
    JREX_LOGLN("JRexInputStream_Read__()--> **** in <"<<in<<"> ****")
	if (!in){
		ThrowJRexException(env, "**** JRexInputStream_Read__ Native Stream is Invalid!!!!****",0);
	    return -1;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("JRexInputStream_Read__()--> **** IN EVT Q THREAD ****")
		jrv=JRexInputStream_Read__Internal(env, in);
	}else{
		nsresult rv=ExecInEventQ(in, JREX_READ_INT, nsnull, PR_TRUE, HandleJRexInputStreamEvent, DestroyJRexInputStreamEvent, (void**)&jrv);
		JREX_LOGLN("JRexInputStream_Read__()--> **** ExecInEventQ rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("JRexInputStream_Read__()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("JRexInputStream_Read__()--> **** Read__ ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** Read__ Failed ****",rv);
			return -1;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return -1;
}

/*
 * Class:     org_mozilla_jrex_io_JRexInputStream
 * Method:    Read
 * Signature: ([BII)I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_io_JRexInputStream_Read___3BII
  (JNIEnv *env, jobject jinput, jbyteArray jbyteArr, jint off, jint len){
	if(!gXpcomRunning)return -1;

	JREX_TRY
    nsIInputStream* in=(nsIInputStream*)NS_INT32_TO_PTR(env->GetIntField(jinput, streamPeerID));
    JREX_LOGLN("JRexInputStream_Read___3BII()--> **** in <"<<in<<"> ****")
	if (!in){
		ThrowJRexException(env, "**** JRexInputStream_Read___3BII Native Stream is Invalid!!!!****",0);
	    return -1;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("JRexInputStream_Read___3BII()--> **** IN EVT Q THREAD ****")
		jrv=JRexInputStream_Read___3BIIInternal(env, in, jbyteArr, off, (PRUint32)len);
	}else{
		JRexInputStreamEventParam* param=new JRexInputStreamEventParam;
		if(IS_NULL(param))return -1;
		param->jbyteArr=jbyteArr;
		param->offset=off;
		param->len=(PRUint32)len;
		nsresult rv=ExecInEventQ(in, JREX_READ, param, PR_TRUE, HandleJRexInputStreamEvent, DestroyJRexInputStreamEvent, (void**)&jrv);
		JREX_LOGLN("JRexInputStream_Read___3BII()--> **** ExecInEventQ rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("JRexInputStream_Read___3BII()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("JRexInputStream_Read___3BII()--> **** Read___3BII() ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** Read___3BII() Failed ****",rv);
			return -1;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return -1;
}

/*
 * Class:     org_mozilla_jrex_io_JRexInputStream
 * Method:    Close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_io_JRexInputStream_Close
  (JNIEnv *env, jobject jinput){
	if(!gXpcomRunning)return;

	JREX_TRY
    nsIInputStream* in=(nsIInputStream*)NS_INT32_TO_PTR(env->GetIntField(jinput, streamPeerID));
    JREX_LOGLN("JRexInputStream_Close()--> **** in <"<<in<<"> ****")
	if (!in){
		ThrowJRexException(env, "**** JRexInputStream_Close Native Stream is Invalid!!!!****",0);
	    return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("JRexInputStream_Close()--> **** IN EVT Q THREAD ****")
		jrv=JRexInputStream_CloseInternal(env, in);
	}else{
		nsresult rv=ExecInEventQ(in, JREX_CLOSE, nsnull, PR_TRUE, HandleJRexInputStreamEvent, DestroyJRexInputStreamEvent, (void**)&jrv);
		JREX_LOGLN("JRexInputStream_Close()--> **** ExecInEventQ rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("JRexInputStream_Close()--> **** jrv<"<<jrv<<"> ****")
	env->SetIntField(jinput, streamPeerID,0);
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("JRexInputStream_Close()--> **** Close ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** Close Failed ****",rv);
		}
	}
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexInputStreamEvent(PLEvent* aEvent){
	if(!gXpcomRunning)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexInputStreamEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIInputStream> in(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_AVAILABLE:
		{
			JREX_LOGLN("HandleJRexInputStreamEvent JREX_AVAILABLE EVENT!!!****")
			return (void*)JRexInputStream_AvailableInternal(nsnull, in.get());
		}
		case JREX_READ_INT:
		{
			JREX_LOGLN("HandleJRexInputStreamEvent JREX_READ_INT EVENT!!!****")
			return (void*)JRexInputStream_Read__Internal(nsnull, in.get());
		}
		case JREX_READ:
		{
			JREX_LOGLN("HandleJRexInputStreamEvent JREX_READ EVENT!!!****")
			JRexInputStreamEventParam* parm = NS_REINTERPRET_CAST(JRexInputStreamEventParam*, event->eventData);
			return (void*)JRexInputStream_Read___3BIIInternal(nsnull, in.get(),parm->jbyteArr, parm->offset, parm->len);
		}
		case JREX_CLOSE:
		{
			JREX_LOGLN("HandleJRexInputStreamEvent JREX_CLOSE EVENT!!!****")
			return (void*)JRexInputStream_CloseInternal(nsnull, in.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexInputStreamEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexInputStreamEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexInputStreamEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexInputStreamEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventType==JREX_READ && event->eventData){
		JRexInputStreamEventParam* param = NS_REINTERPRET_CAST(JRexInputStreamEventParam*, event->eventData);
		delete param;
	}
	delete event;
}


