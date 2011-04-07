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


#include "org_mozilla_jrex_dom_JRexNotationImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexNotation
enum JRexNotationEventTypes{	JREX_GET_PUBLIC_ID=0U,
								JREX_GET_SYSTEM_ID};

static void* PR_CALLBACK HandleJRexNotationEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexNotationEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNotationImpl_GetPublicIdInternal(JNIEnv *env, nsIDOMNotation* dNot){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dNot){
		nsEmbedString retString;
		rv = dNot->GetPublicId(retString);
		JREX_LOGLN("JRexNotationImpl_GetPublicIdInternal()--> **** GetPublicId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNotationImpl_GetSystemIdInternal(JNIEnv *env, nsIDOMNotation* dNot){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dNot){
		nsEmbedString retString;
		rv = dNot->GetSystemId(retString);
		JREX_LOGLN("JRexNotationImpl_GetSystemIdInternal()--> **** GetSystemId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNotationImpl
 * Method:    GetPublicId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNotationImpl_GetPublicId
  (JNIEnv * env,  jobject jnot){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNotation* thisNot=(nsIDOMNotation*)NS_INT32_TO_PTR(env->GetIntField(jnot, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetPublicId()--> **** thisNot <"<<thisNot<<"> ****")
	if(IS_NULL(thisNot)){
		ThrowJRexException(env, "GetPublicId()--> **** thisNot DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetPublicId()--> **** IN EVT Q THREAD ****")
		jrv=JRexNotationImpl_GetPublicIdInternal(env, thisNot);
	}else{
		nsresult rv=ExecInEventQDOM(thisNot, JREX_GET_PUBLIC_ID, nsnull, PR_TRUE,
						HandleJRexNotationEvent, DestroyJRexNotationEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_JRexNotationImpl
 * Method:    GetSystemId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNotationImpl_GetSystemId
  (JNIEnv * env,  jobject jnot){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNotation* thisNot=(nsIDOMNotation*)NS_INT32_TO_PTR(env->GetIntField(jnot, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetSystemId()--> **** thisNot <"<<thisNot<<"> ****")
	if(IS_NULL(thisNot)){
		ThrowJRexException(env, "GetSystemId()--> **** thisNot DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetSystemId()--> **** IN EVT Q THREAD ****")
		jrv=JRexNotationImpl_GetSystemIdInternal(env, thisNot);
	}else{
		nsresult rv=ExecInEventQDOM(thisNot, JREX_GET_SYSTEM_ID, nsnull, PR_TRUE,
						HandleJRexNotationEvent, DestroyJRexNotationEvent, (void**)&jrv);
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

void* PR_CALLBACK HandleJRexNotationEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexNotationEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMNotation> dNot(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_PUBLIC_ID:
		{
			JREX_LOGLN("HandleJRexNotationEvent JREX_GET_PUBLIC_ID EVENT!!!****")
			return (void*)JRexNotationImpl_GetPublicIdInternal(nsnull, dNot.get());
		}
		case JREX_GET_SYSTEM_ID:
		{
			JREX_LOGLN("HandleJRexNotationEvent JREX_GET_SYSTEM_ID EVENT!!!****")
			return (void*)JRexNotationImpl_GetSystemIdInternal(nsnull, dNot.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexNotationEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexNotationEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexNotationEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexNotationEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

