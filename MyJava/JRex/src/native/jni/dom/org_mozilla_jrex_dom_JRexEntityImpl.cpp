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


#include "org_mozilla_jrex_dom_JRexEntityImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexEntity
enum JRexEntityEventTypes{		JREX_GET_NOT_NAME=0U,
								JREX_GET_PUBLIC_ID,
								JREX_GET_SYSTEM_ID};

static void* PR_CALLBACK HandleJRexEntityEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexEntityEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEntityImpl_GetNotationNameInternal(JNIEnv *env, nsIDOMEntity* dEntity){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dEntity){
		nsEmbedString retString;
		rv = dEntity->GetNotationName(retString);
		JREX_LOGLN("JRexEntityImpl_GetNotationNameInternal()--> **** GetNotationName rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEntityImpl_GetPublicIdInternal(JNIEnv *env, nsIDOMEntity* dEntity){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dEntity){
		nsEmbedString retString;
		rv = dEntity->GetPublicId(retString);
		JREX_LOGLN("JRexEntityImpl_GetPublicIdInternal()--> **** GetPublicId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEntityImpl_GetSystemIdInternal(JNIEnv *env, nsIDOMEntity* dEntity){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dEntity){
		nsEmbedString retString;
		rv = dEntity->GetSystemId(retString);
		JREX_LOGLN("JRexEntityImpl_GetSystemIdInternal()--> **** GetSystemId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexEntityImpl
 * Method:    GetNotationName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexEntityImpl_GetNotationName
  (JNIEnv * env,  jobject jenty){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEntity* thisEnty=(nsIDOMEntity*)NS_INT32_TO_PTR(env->GetIntField(jenty, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNotationName()--> **** thisEnty <"<<thisEnty<<"> ****")
	if(IS_NULL(thisEnty)){
		ThrowJRexException(env, "GetNotationName()--> **** thisEnty DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNotationName()--> **** IN EVT Q THREAD ****")
		jrv=JRexEntityImpl_GetNotationNameInternal(env, thisEnty);
	}else{
		nsresult rv=ExecInEventQDOM(thisEnty, JREX_GET_NOT_NAME, nsnull, PR_TRUE,
						HandleJRexEntityEvent, DestroyJRexEntityEvent, (void**)&jrv);
		JREX_LOGLN("GetNotationName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetNotationName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetNotationName()--> **** GetNotationName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetNotationName Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexEntityImpl
 * Method:    GetPublicId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexEntityImpl_GetPublicId
  (JNIEnv * env,  jobject jenty){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEntity* thisEnty=(nsIDOMEntity*)NS_INT32_TO_PTR(env->GetIntField(jenty, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetPublicId()--> **** thisEnty <"<<thisEnty<<"> ****")
	if(IS_NULL(thisEnty)){
		ThrowJRexException(env, "GetPublicId()--> **** thisEnty DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetPublicId()--> **** IN EVT Q THREAD ****")
		jrv=JRexEntityImpl_GetPublicIdInternal(env, thisEnty);
	}else{
		nsresult rv=ExecInEventQDOM(thisEnty, JREX_GET_PUBLIC_ID, nsnull, PR_TRUE,
						HandleJRexEntityEvent, DestroyJRexEntityEvent, (void**)&jrv);
		JREX_LOGLN("GetPublicId()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetPublicId()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetPublicId()--> **** GetPublicId NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetPublicId Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}
/*
 * Class:     org_mozilla_jrex_dom_JRexEntityImpl
 * Method:    GetSystemId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexEntityImpl_GetSystemId
  (JNIEnv * env,  jobject jenty){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEntity* thisEnty=(nsIDOMEntity*)NS_INT32_TO_PTR(env->GetIntField(jenty, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetSystemId()--> **** thisEnty <"<<thisEnty<<"> ****")
	if(IS_NULL(thisEnty)){
		ThrowJRexException(env, "GetSystemId()--> **** thisEnty DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetSystemId()--> **** IN EVT Q THREAD ****")
		jrv=JRexEntityImpl_GetSystemIdInternal(env, thisEnty);
	}else{
		nsresult rv=ExecInEventQDOM(thisEnty, JREX_GET_SYSTEM_ID, nsnull, PR_TRUE,
						HandleJRexEntityEvent, DestroyJRexEntityEvent, (void**)&jrv);
		JREX_LOGLN("GetSystemId()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetSystemId()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetSystemId()--> **** GetSystemId NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetSystemId Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

void* PR_CALLBACK HandleJRexEntityEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexEntityEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMEntity> dEntity(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_NOT_NAME:
		{
			JREX_LOGLN("HandleJRexEntityEvent JREX_GET_NOT_NAME EVENT!!!****")
			return (void*)JRexEntityImpl_GetNotationNameInternal(nsnull, dEntity.get());
		}
		case JREX_GET_PUBLIC_ID:
		{
			JREX_LOGLN("HandleJRexEntityEvent JREX_GET_PUBLIC_ID EVENT!!!****")
			return (void*)JRexEntityImpl_GetPublicIdInternal(nsnull, dEntity.get());
		}
		case JREX_GET_SYSTEM_ID:
		{
			JREX_LOGLN("HandleJRexEntityEvent JREX_GET_SYSTEM_ID EVENT!!!****")
			return (void*)JRexEntityImpl_GetSystemIdInternal(nsnull, dEntity.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexEntityEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexEntityEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexEntityEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexEntityEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

