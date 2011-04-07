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


#include "org_mozilla_jrex_dom_JRexDOMImplementationImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDOMImplementation
enum JRexDOMImplementationEventTypes{	JREX_CREATE_INST=0U,
										JREX_CREATE_DOC,
										JREX_CREATE_DOC_TYP};

static void* PR_CALLBACK HandleJRexDOMImplementationEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDOMImplementationEvent(PLEvent* aEvent);

struct JRexDOMImplementationEventParam{
	PRUnichar *data1;
	PRUnichar *data2;
	void *data3;
};

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMImplementationImpl_CreateInstanceInternal(JNIEnv *env, jobject jdomImpl){
	if(IS_NULL(env))env=JRex_GetEnv(0);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsCOMPtr<nsIDOMDOMImplementation> tempDomImpl;
	nsresult rv=NS_NewDOMImplementation(getter_AddRefs(tempDomImpl));
	JREX_LOGLN("JRexDOMImplementationImpl_CreateInstanceInternal()--> **** NS_NewDOMImplementation rv<"<<rv<<"> ****")
	if(tempDomImpl){
		nsIDOMDOMImplementation *domImpl=nsnull;
		NS_IF_ADDREF(domImpl=tempDomImpl.get());
		JREX_LOGLN("JRexDOMImplementationImpl_CreateInstanceInternal()--> **** NS_NewDOMImplementation SUCCEEDED domImpl<"<<domImpl<<"> ****")
		env->SetIntField(jdomImpl, JRexDOMGlobals::domImplPeerID,(jint)NS_PTR_TO_INT32(domImpl));
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMImplementationImpl_CreateDocumentInternal(JNIEnv *env, nsIDOMDOMImplementation* domImpl, PRUnichar* namespaceURI,
												PRUnichar* qualifiedName, nsIDOMDocumentType* docType){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domImpl){
		nsCOMPtr<nsIDOMDocument> tmpDoc;
		nsEmbedString tnamespaceURI(namespaceURI);
		nsEmbedString tqualifiedName(qualifiedName);
		rv = domImpl->CreateDocument(tnamespaceURI,tqualifiedName, docType, getter_AddRefs(tmpDoc));
		JREX_LOGLN("JRexDOMImplementationImpl_CreateDocumentInternal()--> **** CreateDocument rv<"<<rv<<"> ****")
		if(tmpDoc)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDoc.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMImplementationImpl_CreateDocumentTypeInternal(JNIEnv *env, nsIDOMDOMImplementation* domImpl, PRUnichar* qualifiedName,
												PRUnichar* publicId, PRUnichar* systemId){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domImpl){
		nsCOMPtr<nsIDOMDocumentType> tmpDocTyp;
		nsEmbedString tqualifiedName(qualifiedName);
		nsEmbedString tpublicId(publicId);
		nsEmbedString tsystemId(systemId);
		rv = domImpl->CreateDocumentType(tqualifiedName,tpublicId, tsystemId,getter_AddRefs(tmpDocTyp));
		JREX_LOGLN("JRexDOMImplementationImpl_CreateDocumentTypeInternal()--> **** CreateDocumentType rv<"<<rv<<"> ****")
		if(tmpDocTyp)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocTyp.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_Initialize
  (JNIEnv *env, jclass cls){
	JREX_LOGLN("Initialize()--> **** Intializing DOM sIntialized<"<<JRexDOMGlobals::sIntialized<<"> ****")
	JREX_TRY
    if(!JRexDOMGlobals::sIntialized && JRexDOMGlobals::Intialize(env)==JNI_FALSE)
		ThrowJRexException(env, "**** JRexDOMImplementationImpl Initialize-->  JRexDOMGlobals Initialization failed ****",0);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    UnInitialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_UnInitialize
  (JNIEnv *env, jclass cls){
	JREX_TRY
	JREX_LOGLN("UnInitialize()--> **** UnIntializing DOM sIntialized<"<<JRexDOMGlobals::sIntialized<<"> ****")
    if(JRexDOMGlobals::sIntialized)
    	JRexDOMGlobals::UnIntialize(env);
    JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDOMImplementationImpl
 * Method:    CreateInstance
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_CreateInstance
  (JNIEnv * env, jobject jdomImpl){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateInstance()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMImplementationImpl_CreateInstanceInternal(env, jdomImpl);
	}else{
		nsresult rv=ExecInEventQDOM(nsnull, JREX_CREATE_INST, (void*)jdomImpl, PR_TRUE,
						HandleJRexDOMImplementationEvent, DestroyJRexDOMImplementationEvent, (void**)&jrv);
		JREX_LOGLN("CreateInstance()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateInstance()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("CreateInstance()--> **** CreateInstance NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CreateInstance Failed ****",rv);
		}
	}
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDOMImplementationImpl
 * Method:    CreateDocument
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/w3c/dom/DocumentType;)Lorg/w3c/dom/Document;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_CreateDocument
  (JNIEnv * env, jobject jdomImpl, jstring jnamespaceURI, jstring jqualifiedName, jobject jdocType){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDOMImplementation* thisDomImpl=(nsIDOMDOMImplementation*)NS_INT32_TO_PTR(env->GetIntField(jdomImpl, JRexDOMGlobals::domImplPeerID));
	JREX_LOGLN("CreateDocument()--> **** thisDomImpl <"<<thisDomImpl<<"> ****")
	if(IS_NULL(thisDomImpl)){
		ThrowJRexException(env, "CreateDocument()--> **** thisDomImpl DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	nsIDOMDocumentType* docType = nsnull;
	if(NOT_NULL(jdocType))
		docType=(nsIDOMDocumentType*)NS_INT32_TO_PTR(env->GetIntField(jdocType, JRexDOMGlobals::nodePeerID));

	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName) || IS_NULL(docType)){
		JREX_LOGLN("CreateDocument()--> **** jnamespaceURI/jqualifiedName/docType is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateDocument()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMImplementationImpl_CreateDocumentInternal(env, thisDomImpl, namespaceURI, qualifiedName, docType);
	}else{
		JRexDOMImplementationEventParam *param=new JRexDOMImplementationEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=namespaceURI;
		param->data2=qualifiedName;
		param->data3=docType;
		nsresult rv=ExecInEventQDOM(thisDomImpl, JREX_CREATE_DOC, param, PR_TRUE, HandleJRexDOMImplementationEvent, DestroyJRexDOMImplementationEvent, (void**)&jrv);
		JREX_LOGLN("CreateDocument()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateDocument()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateDocument()--> **** CreateDocument DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateDocument()--> **** CreateDocument NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateDocument Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDOMImplementationImpl
 * Method:    CreateDocumentType
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/DocumentType;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_CreateDocumentType
  (JNIEnv * env, jobject jdomImpl, jstring jqualifiedName , jstring jpublicId, jstring jsystemId){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDOMImplementation* thisDomImpl=(nsIDOMDOMImplementation*)NS_INT32_TO_PTR(env->GetIntField(jdomImpl, JRexDOMGlobals::domImplPeerID));
	JREX_LOGLN("CreateDocumentType()--> **** thisDomImpl <"<<thisDomImpl<<"> ****")
	if(IS_NULL(thisDomImpl)){
		ThrowJRexException(env, "CreateDocumentType()--> **** thisDomImpl DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jqualifiedName) || IS_NULL(jpublicId) || IS_NULL(jsystemId)){
		JREX_LOGLN("CreateDocumentType()--> **** jqualifiedName/jpublicId/jsystemId is NULL ****")
		return NULL;
	}

	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);
	PRUnichar* publicId=nsnull;
	JSTR_TO_NEW_PRUNI(env, jpublicId, publicId);
	PRUnichar* systemId=nsnull;
	JSTR_TO_NEW_PRUNI(env, jsystemId, systemId);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateDocumentType()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMImplementationImpl_CreateDocumentTypeInternal(env, thisDomImpl, qualifiedName, publicId, systemId);
	}else{
		JRexDOMImplementationEventParam *param=new JRexDOMImplementationEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=qualifiedName;
		param->data2=publicId;
		param->data3=(void*)systemId;
		nsresult rv=ExecInEventQDOM(thisDomImpl, JREX_CREATE_DOC_TYP, param, PR_TRUE, HandleJRexDOMImplementationEvent, DestroyJRexDOMImplementationEvent, (void**)&jrv);
		JREX_LOGLN("CreateDocumentType()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateDocumentType()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateDocumentType()--> **** CreateDocumentType DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateDocumentType()--> **** CreateDocumentType NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateDocumentType Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDOMImplementationImpl
 * Method:    HasFeature
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_HasFeature
  (JNIEnv * env, jobject jdomImpl, jstring jfeature, jstring jversion){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMDOMImplementation* thisDomImpl=(nsIDOMDOMImplementation*)NS_INT32_TO_PTR(env->GetIntField(jdomImpl, JRexDOMGlobals::domImplPeerID));
	JREX_LOGLN("HasFeature()--> **** thisDomImpl <"<<thisDomImpl<<"> ****")
	if(IS_NULL(thisDomImpl)){
		ThrowJRexException(env, "HasFeature()--> **** thisDomImpl DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRUnichar* feature=nsnull;
	JSTR_TO_NEW_PRUNI(env, jfeature, feature);
	PRUnichar* version=nsnull;
	JSTR_TO_NEW_PRUNI(env, jversion, version);

	nsEmbedString tfeature(feature);
	nsEmbedString tversion(version);

	PRBool retBool = PR_FALSE;
	nsresult rv = thisDomImpl->HasFeature(tfeature, tversion, &retBool);
	if(feature)nsMemory::Free(feature);
	if(version)nsMemory::Free(version);
	JREX_LOGLN("HasFeature()--> **** HasFeature rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("HasFeature()--> **** HasFeature NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** HasFeature Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}
/*
 * Class:     org_mozilla_jrex_dom_JRexDOMImplementationImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDOMImplementationImpl_Finalize
  (JNIEnv * env, jobject jdomImpl){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMDOMImplementation* thisDomImpl=(nsIDOMDOMImplementation*)NS_INT32_TO_PTR(env->GetIntField(jdomImpl, JRexDOMGlobals::domImplPeerID));
	JREX_LOGLN("JRexDOMImplementationImpl Finalize()--> **** thisDomImpl <"<<thisDomImpl<<"> ****")
	if(IS_NULL(thisDomImpl)){
		JREX_LOGLN("JRexDOMImplementationImpl Finalize()--> **** thisDomImpl DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisDomImpl)
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexDOMImplementationEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDOMImplementationEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMDOMImplementation> domImpl(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_CREATE_INST:
		{
			JREX_LOGLN("HandleJRexDOMImplementationEvent JREX_CREATE_INST EVENT!!!****")
			jobject docImpl = NS_REINTERPRET_CAST(jobject, event->eventData);
			return (void*)JRexDOMImplementationImpl_CreateInstanceInternal(nsnull, docImpl);
		}
		case JREX_CREATE_DOC:
		{
			JREX_LOGLN("HandleJRexDOMImplementationEvent JREX_CREATE_DOC EVENT!!!****")
			JRexDOMImplementationEventParam* param = NS_REINTERPRET_CAST(JRexDOMImplementationEventParam*, event->eventData);
			return (void*)JRexDOMImplementationImpl_CreateDocumentInternal(nsnull, domImpl.get(),
							param->data1, param->data2, NS_REINTERPRET_CAST(nsIDOMDocumentType*, param->data3));
		}
		case JREX_CREATE_DOC_TYP:
		{
			JREX_LOGLN("HandleJRexDOMImplementationEvent JREX_CREATE_DOC_TYP EVENT!!!****")
			JRexDOMImplementationEventParam* param = NS_REINTERPRET_CAST(JRexDOMImplementationEventParam*, event->eventData);
			return (void*)JRexDOMImplementationImpl_CreateDocumentTypeInternal(nsnull, domImpl.get(),
							param->data1, param->data2, NS_REINTERPRET_CAST(PRUnichar*, param->data3));
		}
		default:
		{
			JREX_LOGLN("HandleJRexDOMImplementationEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDOMImplementationEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDOMImplementationEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDOMImplementationEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
