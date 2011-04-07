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


#include "org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexNodeFilter.h"

//event types for JRexNodeIterator
enum JRexNodeIteratorEventTypes{JREX_GET_ROOT=0U,
								JREX_GET_FILTER,
								JREX_PREV_NODE,
								JREX_NEXT_NODE};

static void* PR_CALLBACK HandleJRexNodeIteratorEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexNodeIteratorEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexNodeIteratorImpl_GetRootInternal(JNIEnv *env, nsIDOMNodeIterator* itr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (itr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = itr->GetRoot(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeIteratorImpl_GetRootInternal()--> **** GetRoot rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexNodeIteratorImpl_GetFilterInternal(JNIEnv *env, nsIDOMNodeIterator* itr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (itr){
		nsCOMPtr<nsIDOMNodeFilter> tmpFilter;
		rv = itr->GetFilter(getter_AddRefs(tmpFilter));
		JREX_LOGLN("JRexNodeIteratorImpl_GetFilterInternal()--> **** GetFilter rv<"<<rv<<"> ****")
		if(tmpFilter){
			JRexNodeFilter* retFilter=NS_REINTERPRET_CAST(JRexNodeFilter*, tmpFilter.get());
			jval=retFilter?retFilter->GetJFilter():NULL;
		}
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexNodeIteratorImpl_GetPreviousNodeInternal(JNIEnv *env, nsIDOMNodeIterator* itr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (itr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = itr->PreviousNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeIteratorImpl_GetPreviousNodeInternal()--> **** PreviousNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexNodeIteratorImpl_GetNextNodeInternal(JNIEnv *env, nsIDOMNodeIterator* itr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (itr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = itr->NextNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeIteratorImpl_GetNextNodeInternal()--> **** NextNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    GetRoot
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_GetRoot
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("GetRoot()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("GetRoot()--> **** thisItr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetRoot()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeIteratorImpl_GetRootInternal(env, thisItr);
	}else{
		nsresult rv=ExecInEventQDOM(thisItr, JREX_GET_ROOT, nsnull, PR_TRUE, HandleJRexNodeIteratorEvent, DestroyJRexNodeIteratorEvent, (void**)&jrv);
		JREX_LOGLN("GetRoot()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetRoot()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetRoot()--> **** GetRoot NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetRoot Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    GetWhatToShow
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_GetWhatToShow
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("GetWhatToShow()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("GetWhatToShow()--> **** thisItr DOES NOT EXIST!!! ****");
		return 0;
	}
	PRUint32 rVal=0;
	nsresult rv = thisItr->GetWhatToShow(&rVal);
	JREX_LOGLN("GetWhatToShow()--> **** GetWhatToShow rv<"<<rv<<"> rVal<"<<rVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetWhatToShow()--> **** GetWhatToShow NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetWhatToShow Failed ****",rv);
		return 0;
	}
	return (jint)rVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    GetFilter
 * Signature: ()Lorg/w3c/dom/traversal/NodeFilter;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_GetFilter
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("GetFilter()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("GetFilter()--> **** thisItr DOES NOT EXIST!!! ****");
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetFilter()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeIteratorImpl_GetFilterInternal(env, thisItr);
	}else{
		nsresult rv=ExecInEventQDOM(thisItr, JREX_GET_FILTER, nsnull, PR_TRUE, HandleJRexNodeIteratorEvent, DestroyJRexNodeIteratorEvent, (void**)&jrv);
		JREX_LOGLN("GetFilter()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetFilter()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetFilter()--> **** GetFilter NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetFilter Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    GetExpandEntityReferences
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_GetExpandEntityReferences
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("GetExpandEntityReferences()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("GetExpandEntityReferences()--> **** thisItr DOES NOT EXIST!!! ****");
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisItr->GetExpandEntityReferences(&retBool);
	JREX_LOGLN("GetExpandEntityReferences()--> **** GetExpandEntityReferences rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetExpandEntityReferences()--> **** GetExpandEntityReferences NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetExpandEntityReferences Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    NextNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_NextNode
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("NextNode()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("NextNode()--> **** thisItr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("NextNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeIteratorImpl_GetNextNodeInternal(env, thisItr);
	}else{
		nsresult rv=ExecInEventQDOM(thisItr, JREX_NEXT_NODE, nsnull, PR_TRUE, HandleJRexNodeIteratorEvent, DestroyJRexNodeIteratorEvent, (void**)&jrv);
		JREX_LOGLN("NextNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("NextNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("NextNode()--> **** NextNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("NextNode()--> **** NextNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** NextNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    PreviousNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_PreviousNode
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("PreviousNode()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("PreviousNode()--> **** thisItr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("PreviousNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeIteratorImpl_GetPreviousNodeInternal(env, thisItr);
	}else{
		nsresult rv=ExecInEventQDOM(thisItr, JREX_PREV_NODE, nsnull, PR_TRUE, HandleJRexNodeIteratorEvent, DestroyJRexNodeIteratorEvent, (void**)&jrv);
		JREX_LOGLN("PreviousNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("PreviousNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("PreviousNode()--> **** PreviousNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("PreviousNode()--> **** PreviousNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** PreviousNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    Detach
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_Detach
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("Detach()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("Detach()--> **** thisItr DOES NOT EXIST!!! ****");
		return;
	}

	nsresult rv = thisItr->Detach();
	JREX_LOGLN("Detach()--> **** Detach rv<"<<rv<<"> ****")
	if (NS_FAILED(rv)) {
		JREX_LOGLN("Detach()--> **** Detach NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** Detach Failed ****",rv);
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl_Finalize
  (JNIEnv *env, jobject jnodeItr){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNodeIterator* thisItr=(nsIDOMNodeIterator*)NS_INT32_TO_PTR(env->GetIntField(jnodeItr, JRexDOMGlobals::nodeItrPeerID));
	JREX_LOGLN("JRexNodeIteratorImpl Finalize()--> **** thisItr <"<<thisItr<<"> ****")
	if(IS_NULL(thisItr)){
		JREX_LOGLN("JRexNodeIteratorImpl Finalize()--> **** thisItr DOES NOT EXIST!!! ****");
		return;
	}
	nsresult rv=thisItr->Detach();
	JREX_LOGLN("JRexNodeIteratorImpl Finalize()--> **** Detach rv<"<<rv<<"> ****")
	SAFE_RELEASE(thisItr)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexNodeIteratorEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexNodeIteratorEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMNodeIterator> itr(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ROOT:
		{
			JREX_LOGLN("HandleJRexNodeIteratorEvent JREX_GET_ROOT EVENT!!!****")
			return (void*)JRexNodeIteratorImpl_GetRootInternal(nsnull, itr.get());
		}
		case JREX_GET_FILTER:
		{
			JREX_LOGLN("HandleJRexNodeIteratorEvent JREX_GET_FILTER EVENT!!!****")
			return (void*)JRexNodeIteratorImpl_GetFilterInternal(nsnull, itr.get());
		}
		case JREX_PREV_NODE:
		{
			JREX_LOGLN("HandleJRexNodeIteratorEvent JREX_PREV_NODE EVENT!!!****")
			return (void*)JRexNodeIteratorImpl_GetPreviousNodeInternal(nsnull, itr.get());
		}
		case JREX_NEXT_NODE:
		{
			JREX_LOGLN("HandleJRexNodeIteratorEvent JREX_NEXT_NODE EVENT!!!****")
			return (void*)JRexNodeIteratorImpl_GetNextNodeInternal(nsnull, itr.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexNodeIteratorEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexNodeIteratorEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexNodeIteratorEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexNodeIteratorEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
