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


#include "org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexNodeFilter.h"

//event types for JRexTreeWalker
enum JRexTreeWalkerEventTypes{	JREX_GET_ROOT=0U,
								JREX_GET_FILTER,
								JREX_GET_CURR_NODE,
								JREX_SET_CURR_NODE,
								JREX_PARENT_NODE,
								JREX_FIRST_CHILD,
								JREX_LAST_CHILD,
								JREX_PREV_SIB,
								JREX_NEXT_SIB,
								JREX_PREV_NODE,
								JREX_NEXT_NODE};

static void* PR_CALLBACK HandleJRexTreeWalkerEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexTreeWalkerEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetRootInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->GetRoot(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetRootInternal()--> **** GetRoot rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetFilterInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNodeFilter> tmpFilter;
		rv = wkr->GetFilter(getter_AddRefs(tmpFilter));
		JREX_LOGLN("JRexTreeWalkerImpl_GetFilterInternal()--> **** GetFilter rv<"<<rv<<"> ****")
		if(tmpFilter){
			JRexNodeFilter* retFilter=NS_REINTERPRET_CAST(JRexNodeFilter*, tmpFilter.get());
			jval=retFilter?retFilter->GetJFilter():NULL;
		}
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetCurrentNodeInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->GetCurrentNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetCurrentNodeInternal()--> **** GetCurrentNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_SetCurrentNodeInternal(JNIEnv *env, nsIDOMTreeWalker* wkr, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		rv = wkr->SetCurrentNode(node);
		JREX_LOGLN("JRexTreeWalkerImpl_SetCurrentNodeInternal()--> **** SetCurrentNode rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetParentNodeInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->ParentNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetParentNodeInternal()--> **** ParentNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetFirstChildInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->FirstChild(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetFirstChildInternal()--> **** FirstChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetLastChildInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->LastChild(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetLastChildInternal()--> **** LastChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetPreviousSiblingInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->PreviousSibling(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetPreviousSiblingInternal()--> **** PreviousSibling rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetNextSiblingInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->NextSibling(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetNextSiblingInternal()--> **** NextSibling rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetPreviousNodeInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->PreviousNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetPreviousNodeInternal()--> **** PreviousNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTreeWalkerImpl_GetNextNodeInternal(JNIEnv *env, nsIDOMTreeWalker* wkr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (wkr){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = wkr->NextNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexTreeWalkerImpl_GetNextNodeInternal()--> **** NextNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    GetRoot
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_GetRoot
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("GetRoot()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("GetRoot()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetRoot()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetRootInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_GET_ROOT, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    GetWhatToShow
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_GetWhatToShow
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("GetWhatToShow()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("GetWhatToShow()--> **** thisWkr DOES NOT EXIST!!! ****");
		return 0;
	}
	PRUint32 rVal=0;
	nsresult rv = thisWkr->GetWhatToShow(&rVal);
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
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    GetFilter
 * Signature: ()Lorg/w3c/dom/traversal/NodeFilter;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_GetFilter
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("GetFilter()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("GetFilter()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetFilter()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetFilterInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_GET_FILTER, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    GetExpandEntityReferences
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_GetExpandEntityReferences
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("GetExpandEntityReferences()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("GetExpandEntityReferences()--> **** thisWkr DOES NOT EXIST!!! ****");
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisWkr->GetExpandEntityReferences(&retBool);
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
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    GetCurrentNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_GetCurrentNode
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("GetCurrentNode()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("GetCurrentNode()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetCurrentNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetCurrentNodeInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_GET_CURR_NODE, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("GetCurrentNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetCurrentNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetCurrentNode()--> **** GetCurrentNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetCurrentNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    SetCurrentNode
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_SetCurrentNode
  (JNIEnv *env, jobject jtreeWkr, jobject jnode){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("SetCurrentNode()--> **** thisWkr <"<<thisWkr<<"> ****")
	nsIDOMNode* node=nsnull;
	if(NOT_NULL(jnode))
		node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetCurrentNode()--> **** node <"<<node<<"> ****")

	if(IS_NULL(thisWkr) || IS_NULL(node)){
		ThrowJRexException(env, "**** SetCurrentNode()--> thisWkr/node DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetCurrentNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_SetCurrentNodeInternal(env, thisWkr, node);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_SET_CURR_NODE, node, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("SetCurrentNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetCurrentNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetCurrentNode()--> **** SetCurrentNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetCurrentNode()--> **** SetCurrentNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetCurrentNode Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    ParentNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_ParentNode
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("ParentNode()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("ParentNode()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ParentNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetParentNodeInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_PARENT_NODE, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("ParentNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ParentNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("ParentNode()--> **** ParentNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** ParentNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    FirstChild
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_FirstChild
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("FirstChild()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("FirstChild()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("FirstChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetFirstChildInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_FIRST_CHILD, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("FirstChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("FirstChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("FirstChild()--> **** FirstChild NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** FirstChild Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    LastChild
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_LastChild
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("LastChild()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("LastChild()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("LastChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetLastChildInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_LAST_CHILD, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("LastChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("LastChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("LastChild()--> **** LastChild NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** LastChild Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    PreviousSibling
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_PreviousSibling
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("PreviousSibling()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("PreviousSibling()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("PreviousSibling()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetPreviousSiblingInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_PREV_SIB, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("PreviousSibling()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("PreviousSibling()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("PreviousSibling()--> **** PreviousSibling NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** PreviousSibling Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    NextSibling
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_NextSibling
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("NextSibling()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("NextSibling()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("NextSibling()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetNextSiblingInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_NEXT_SIB, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("NextSibling()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("NextSibling()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("NextSibling()--> **** NextSibling NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** NextSibling Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    PreviousNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_PreviousNode
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("PreviousNode()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("PreviousNode()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("PreviousNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetPreviousNodeInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_PREV_NODE, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("PreviousNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("PreviousNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("PreviousNode()--> **** PreviousNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** PreviousNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    NextNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_NextNode
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("NextNode()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("NextNode()--> **** thisWkr DOES NOT EXIST!!! ****");
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("NextNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexTreeWalkerImpl_GetNextNodeInternal(env, thisWkr);
	}else{
		nsresult rv=ExecInEventQDOM(thisWkr, JREX_NEXT_NODE, nsnull, PR_TRUE, HandleJRexTreeWalkerEvent, DestroyJRexTreeWalkerEvent, (void**)&jrv);
		JREX_LOGLN("NextNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("NextNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("NextNode()--> **** NextNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** NextNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl_Finalize
  (JNIEnv *env, jobject jtreeWkr){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMTreeWalker* thisWkr=(nsIDOMTreeWalker*)NS_INT32_TO_PTR(env->GetIntField(jtreeWkr, JRexDOMGlobals::treeWkrPeerID));
	JREX_LOGLN("JRexTreeWalkerImpl Finalize()--> **** thisWkr <"<<thisWkr<<"> ****")
	if(IS_NULL(thisWkr)){
		JREX_LOGLN("JRexTreeWalkerImpl Finalize()--> **** thisWkr DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisWkr)
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexTreeWalkerEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexTreeWalkerEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMTreeWalker> wkr(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ROOT:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_GET_ROOT EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetRootInternal(nsnull, wkr.get());
		}
		case JREX_GET_FILTER:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_GET_FILTER EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetFilterInternal(nsnull, wkr.get());
		}
		case JREX_GET_CURR_NODE:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_GET_CURR_NODE EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetCurrentNodeInternal(nsnull, wkr.get());
		}
		case JREX_SET_CURR_NODE:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_SET_CURR_NODE EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexTreeWalkerImpl_SetCurrentNodeInternal(nsnull, wkr.get(), node);
		}
		case JREX_PARENT_NODE:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_PARENT_NODE EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetParentNodeInternal(nsnull, wkr.get());
		}
		case JREX_FIRST_CHILD:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_FIRST_CHILD EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetFirstChildInternal(nsnull, wkr.get());
		}
		case JREX_LAST_CHILD:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_LAST_CHILD EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetLastChildInternal(nsnull, wkr.get());
		}
		case JREX_PREV_SIB:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_PREV_SIB EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetPreviousSiblingInternal(nsnull, wkr.get());
		}
		case JREX_NEXT_SIB:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_NEXT_SIB EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetNextSiblingInternal(nsnull, wkr.get());
		}
		case JREX_PREV_NODE:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_PREV_NODE EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetPreviousNodeInternal(nsnull, wkr.get());
		}
		case JREX_NEXT_NODE:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent JREX_NEXT_NODE EVENT!!!****")
			return (void*)JRexTreeWalkerImpl_GetNextNodeInternal(nsnull, wkr.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexTreeWalkerEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexTreeWalkerEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexTreeWalkerEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexTreeWalkerEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
