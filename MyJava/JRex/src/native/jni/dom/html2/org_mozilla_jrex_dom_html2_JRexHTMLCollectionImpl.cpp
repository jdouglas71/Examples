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


#include "org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLCollection
enum JRexHTMLCollectionEventTypes{	JREX_GET_LENGTH=0U,
									JREX_GET_ITEM,
									JREX_GET_NAMED_ITEM};

static void* PR_CALLBACK HandleJRexHTMLCollectionEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLCollectionEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLCollectionImpl_GetItemInternal(JNIEnv *env, nsIDOMHTMLCollection* htmlCol, PRUint32 index){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (htmlCol){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = htmlCol->Item(index, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexHTMLCollectionImpl_GetItemInternal()--> **** Item rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLCollectionImpl_GetNamedItemInternal(JNIEnv *env, nsIDOMHTMLCollection* htmlCol, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (htmlCol){
		nsCOMPtr<nsIDOMNode> tmpNode;
		nsEmbedString tname(name);
		rv = htmlCol->NamedItem(tname, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexHTMLCollectionImpl_GetNamedItemInternal()--> **** NamedItem rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl_GetLength
  (JNIEnv *env, jobject jhtmlCol){
	GET_DOM_INT_JNI(env , jhtmlCol, HTMLCollection, PRUint32, GetLength, JREX_GET_LENGTH, JRexDOMGlobals::colctElePeerID, PR_FALSE)}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl
 * Method:    Item
 * Signature: (I)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl_Item
  (JNIEnv *env, jobject jhtmlCol, jint jindex){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLCollection* thisCol=(nsIDOMHTMLCollection*)NS_INT32_TO_PTR(env->GetIntField(jhtmlCol, JRexDOMGlobals::colctElePeerID));
	JREX_LOGLN("Item()--> **** thisCol <"<<thisCol<<"> ****")
	if(IS_NULL(thisCol)){
		ThrowJRexException(env, "Item()--> **** thisCol DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (jindex<0){
		JREX_LOGLN("Item()--> **** jindex < 0 ****")
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Item()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLCollectionImpl_GetItemInternal(env, thisCol, (PRUint32)jindex);
	}else{
		nsresult rv=ExecInEventQDOM(thisCol, JREX_GET_ITEM, (void*)jindex, PR_TRUE, HandleJRexHTMLCollectionEvent, DestroyJRexHTMLCollectionEvent, (void**)&jrv);
		JREX_LOGLN("Item()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("Item()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("Item()--> **** Item NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** Item Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl
 * Method:    NamedItem
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl_NamedItem
  (JNIEnv *env, jobject jhtmlCol, jstring jname){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLCollection* thisCol=(nsIDOMHTMLCollection*)NS_INT32_TO_PTR(env->GetIntField(jhtmlCol, JRexDOMGlobals::colctElePeerID));
	JREX_LOGLN("NamedItem()--> **** thisCol <"<<thisCol<<"> ****")
	if(IS_NULL(thisCol)){
		ThrowJRexException(env, "NamedItem()--> **** thisCol DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("NamedItem()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("NamedItem()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLCollectionImpl_GetNamedItemInternal(env, thisCol, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisCol, JREX_GET_NAMED_ITEM, (void*)name, PR_TRUE, HandleJRexHTMLCollectionEvent, DestroyJRexHTMLCollectionEvent, (void**)&jrv);
		JREX_LOGLN("NamedItem()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("NamedItem()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("NamedItem()--> **** NamedItem NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** NamedItem Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl_Finalize
  (JNIEnv *env, jobject jhtmlCol){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMHTMLCollection* thisCol=(nsIDOMHTMLCollection*)NS_INT32_TO_PTR(env->GetIntField(jhtmlCol, JRexDOMGlobals::colctElePeerID));
	JREX_LOGLN("JRexHTMLCollectionImpl Finalize()--> **** thisCol <"<<thisCol<<"> ****")
	if(IS_NULL(thisCol)){
		JREX_LOGLN("JRexHTMLCollectionImpl Finalize()--> **** thisCol DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisCol)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexHTMLCollectionEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLCollectionEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLCollection> htmlCol(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLCollectionEvent JREX_GET_LENGTH EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, htmlCol.get(), PRUint32, GetLength, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ITEM:
		{
			JREX_LOGLN("HandleJRexHTMLCollectionEvent JREX_GET_ITEM EVENT!!!****")
			return (void*)JRexHTMLCollectionImpl_GetItemInternal(nsnull, htmlCol.get(), (PRUint32)event->eventData);
		}
		case JREX_GET_NAMED_ITEM:
		{
			JREX_LOGLN("HandleJRexHTMLCollectionEvent JREX_GET_NAMED_ITEM EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexHTMLCollectionImpl_GetNamedItemInternal(nsnull, htmlCol.get(), name);
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLCollectionEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexHTMLCollectionEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLCollectionEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLCollectionEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
