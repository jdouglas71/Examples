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


#include "org_mozilla_jrex_dom_JRexDocumentTypeImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDocumentType
enum JRexDocumentTypeEventTypes{JREX_GET_ENTITIES=0U,
								JREX_GET_INT_SUBSET,
								JREX_GET_NAME,
								JREX_GET_NOTATIONS,
								JREX_GET_PUBLIC_ID,
								JREX_GET_SYSTEM_ID};

static void* PR_CALLBACK HandleJRexDocumentTypeEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocumentTypeEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetEntitiesInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsCOMPtr<nsIDOMNamedNodeMap> tmpNodeMap;
		rv = docType->GetEntities(getter_AddRefs(tmpNodeMap));
		JREX_LOGLN("JRexDocumentTypeImpl_GetEntitiesInternal()--> **** GetEntities rv<"<<rv<<"> ****")
		if(tmpNodeMap)
			jval=JRexDOMGlobals::CreateNodeMap(env, tmpNodeMap.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetInternalSubsetInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsEmbedString retString;
		rv = docType->GetInternalSubset(retString);
		JREX_LOGLN("JRexDocumentTypeImpl_GetInternalSubsetInternal()--> **** GetInternalSubset rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetNameInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsEmbedString retString;
		rv = docType->GetName(retString);
		JREX_LOGLN("JRexDocumentTypeImpl_GetNameInternal()--> **** GetName rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetNotationsInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsCOMPtr<nsIDOMNamedNodeMap> tmpNodeMap;
		rv = docType->GetNotations(getter_AddRefs(tmpNodeMap));
		JREX_LOGLN("JRexDocumentTypeImpl_GetNotationsInternal()--> **** GetNotations rv<"<<rv<<"> ****")
		if(tmpNodeMap)
			jval=JRexDOMGlobals::CreateNodeMap(env, tmpNodeMap.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetPublicIdInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsEmbedString retString;
		rv = docType->GetPublicId(retString);
		JREX_LOGLN("JRexDocumentTypeImpl_GetPublicIdInternal()--> **** GetPublicId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentTypeImpl_GetSystemIdInternal(JNIEnv *env, nsIDOMDocumentType* docType){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docType){
		nsEmbedString retString;
		rv = docType->GetSystemId(retString);
		JREX_LOGLN("JRexDocumentTypeImpl_GetSystemIdInternal()--> **** GetSystemId rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetEntities
 * Signature: ()Lorg/w3c/dom/NamedNodeMap;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetEntities
  (JNIEnv * env, jobject jdocType){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetEntities()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetEntities()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetEntities()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetEntitiesInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_ENTITIES, nsnull, PR_TRUE, HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
		JREX_LOGLN("GetEntities()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetEntities()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetEntities()--> **** GetEntities NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetEntities Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetInternalSubset
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetInternalSubset
  (JNIEnv * env, jobject jdocType){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetInternalSubset()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetInternalSubset()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetInternalSubset()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetInternalSubsetInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_INT_SUBSET, nsnull, PR_TRUE,
						HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
		JREX_LOGLN("GetInternalSubset()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetInternalSubset()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetInternalSubset()--> **** GetInternalSubset NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetInternalSubset Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetName
  (JNIEnv * env, jobject jdocType){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetName()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetName()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetName()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetNameInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_NAME, nsnull, PR_TRUE,
						HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
		JREX_LOGLN("GetName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetName()--> **** GetName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetName Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetNotations
 * Signature: ()Lorg/w3c/dom/NamedNodeMap;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetNotations
  (JNIEnv * env, jobject jdocType){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNotations()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetNotations()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNotations()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetNotationsInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_NOTATIONS, nsnull, PR_TRUE, HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
		JREX_LOGLN("GetNotations()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetNotations()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetNotations()--> **** GetNotations NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetNotations Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetPublicId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetPublicId
  (JNIEnv * env, jobject jdocType){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetPublicId()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetPublicId()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetPublicId()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetPublicIdInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_PUBLIC_ID, nsnull, PR_TRUE,
						HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_JRexDocumentTypeImpl
 * Method:    GetSystemId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentTypeImpl_GetSystemId
  (JNIEnv * env, jobject jdocType){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentType* thisDocType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetSystemId()--> **** thisDocType <"<<thisDocType<<"> ****")
	if(IS_NULL(thisDocType)){
		ThrowJRexException(env, "GetSystemId()--> **** thisDocType DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetSystemId()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTypeImpl_GetSystemIdInternal(env, thisDocType);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocType, JREX_GET_SYSTEM_ID, nsnull, PR_TRUE,
						HandleJRexDocumentTypeEvent, DestroyJRexDocumentTypeEvent, (void**)&jrv);
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

void* PR_CALLBACK HandleJRexDocumentTypeEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocumentTypeEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMDocumentType> docType(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ENTITIES:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_ENTITIES EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetEntitiesInternal(nsnull, docType.get());
		}
		case JREX_GET_INT_SUBSET:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_INT_SUBSET EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetInternalSubsetInternal(nsnull, docType.get());
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_NAME EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetNameInternal(nsnull, docType.get());
		}
		case JREX_GET_NOTATIONS:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_NOTATIONS EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetNotationsInternal(nsnull, docType.get());
		}

		case JREX_GET_PUBLIC_ID:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_PUBLIC_ID EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetPublicIdInternal(nsnull, docType.get());
		}
		case JREX_GET_SYSTEM_ID:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent JREX_GET_SYSTEM_ID EVENT!!!****")
			return (void*)JRexDocumentTypeImpl_GetSystemIdInternal(nsnull, docType.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocumentTypeEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocumentTypeEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocumentTypeEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocumentTypeEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

