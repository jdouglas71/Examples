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


#include "org_mozilla_jrex_dom_JRexNodeImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexDOMUserDataHandler.h"

//event types for JRexNode
enum JRexNodeEventTypes{	JREX_APPEND_CHILD=0U,
							JREX_CLONE_NODE,
							JREX_GET_ATTRIBUTES,
							JREX_GET_CHILD_NODES,
 							JREX_GET_FIRST_CHILD,
 							JREX_GET_LAST_CHILD,
 							JREX_GET_NEXT_SIB,
 							JREX_GET_PREV_SIB,
 							JREX_GET_NODE_VALUE,
 							JREX_GET_OWNER_DOC,
 							JREX_GET_PARENT_NODE,
 							JREX_INST_BEFORE,
 							JREX_REMOVE_CHILD,
 							JREX_REPLACE_CHILD,
 							JREX_SET_NODE_VALUE,
 							JREX_GET_EVENT_TARGET,
 							//DOM3
 							JREX_GET_BASE_URI,
 							JREX_GET_TXT_CNT,
 							JREX_SET_TXT_CNT,
 							JREX_GET_FET,
 							JREX_GET_USR_DATA,
 							JREX_SET_USR_DATA};

static void* PR_CALLBACK HandleJRexNodeEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexNodeEvent(PLEvent* aEvent);

static void* PR_CALLBACK HandleJRex3NodeEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRex3NodeEvent(PLEvent* aEvent);

struct JRexNodeEventParam{
	nsIDOMNode *node1;
	nsIDOMNode *node2;
};

struct JRexUserDataEventParam{
	PRUnichar* key;
	PRUnichar* data;
	jobject juserDataHandler;
};


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_AppendChildInternal(JNIEnv *env, nsIDOMNode* node, nsIDOMNode* childNode){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->AppendChild(childNode, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_AppendChildInternal()--> **** AppendChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_CloneNodeInternal(JNIEnv *env, nsIDOMNode* node, PRBool deep){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->CloneNode(deep, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_CloneNodeInternal()--> **** CloneNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetAttributesInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNamedNodeMap> tmpNodeMap;
		rv = node->GetAttributes(getter_AddRefs(tmpNodeMap));
		JREX_LOGLN("JRexNodeImpl_GetAttributesInternal()--> **** GetAttributes rv<"<<rv<<"> ****")
		if(tmpNodeMap)
			jval=JRexDOMGlobals::CreateNodeMap(env, tmpNodeMap.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetChildNodesInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		rv = node->GetChildNodes(getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexNodeImpl_GetChildNodesInternal()--> **** GetChildNodes rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetFirstChildInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->GetFirstChild(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_GetFirstChildInternal()--> **** GetFirstChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetLastChildInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->GetLastChild(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_GetLastChildInternal()--> **** GetLastChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetNextSiblingInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->GetNextSibling(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_GetNextSiblingInternal()--> **** GetNextSibling rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetPreviousSiblingInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->GetPreviousSibling(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_GetPreviousSiblingInternal()--> **** GetPreviousSibling rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetNodeValueInternal(JNIEnv *env, nsIDOMNode* node){
	if(IS_NULL(env))env=JRex_GetEnv(0);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsEmbedString retString;
			rv=node->GetNodeValue(retString);
		if(NS_SUCCEEDED(rv))
			NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetOwnerDocumentInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMDocument> tmpDocNode;
		rv = node->GetOwnerDocument(getter_AddRefs(tmpDocNode));
		JREX_LOGLN("JRexNodeImpl_GetOwnerDocumentInternal()--> **** GetOwnerDocument rv<"<<rv<<"> ****")
		if(tmpDocNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetParentNodeInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->GetParentNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_GetParentNodeInternal()--> **** GetParentNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_InsertBeforeInternal(JNIEnv *env, nsIDOMNode* node, nsIDOMNode* insrtNode, nsIDOMNode* refNode ){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->InsertBefore(insrtNode, refNode, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_InsertBeforeInternal()--> **** InsertBefore rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_RemoveChildInternal(JNIEnv *env, nsIDOMNode* node, nsIDOMNode* childNode){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->RemoveChild(childNode, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_RemoveChildInternal()--> **** RemoveChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_ReplaceChildInternal(JNIEnv *env, nsIDOMNode* node, nsIDOMNode* newChildNode, nsIDOMNode* oldChildNode){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = node->ReplaceChild(newChildNode, oldChildNode, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeImpl_ReplaceChildInternal()--> **** ReplaceChild rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_SetNodeValueInternal(JNIEnv *env, nsIDOMNode* node, PRUnichar* nodeValue){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsEmbedString tNodeValue(nodeValue);
			rv=node->SetNodeValue(tNodeValue);
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_GetEventTargetInternal(JNIEnv *env, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (node){
		nsCOMPtr<nsIDOMEventTarget> evtTarget(do_QueryInterface(node,&rv));
		JREX_LOGLN("JRexNodeImpl_GetEventTargetInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(evtTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, evtTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeImpl_SetUserDataInternal(JNIEnv *env, nsIDOM3Node* node
										, PRUnichar* key, PRUnichar* data, jobject juserDataHandler){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	jobject jval=NULL;
	if (node){
		nsIDOMUserDataHandler* domDataHandl=new JRexDOMUserDataHandler(juserDataHandler);
		if(IS_NULL(domDataHandl)){
			JREX_LOGLN("JRexNodeImpl_SetUserDataInternal()--> **** nsIDOMUserDataHandler creation Failed ***")
			jrv->rv=NS_ERROR_OUT_OF_MEMORY;
			return jrv;
		}
		nsEmbedString tkey(key);
		nsCOMPtr<nsIWritableVariant> tdata;
		nsCOMPtr<nsIVariant> tdataTemp=do_CreateInstance(NS_VARIANT_CONTRACTID,&rv);
		if(tdataTemp){
		 	tdata=do_QueryInterface(tdataTemp, &rv);
		 	if(tdata){
				rv=tdata->SetWritable(PR_TRUE);
				if(NS_SUCCEEDED(rv))
					rv=tdata->SetAsWString(data);
			}
	 	}
		if(NS_FAILED(rv)){
			JREX_LOGLN("JRexNodeImpl_SetUserDataInternal()--> **** nsIVariant creation Failed ***")
			jrv->rv=rv;
			return jrv;
		}

		nsCOMPtr<nsIVariant> tmpData;
		rv =node->SetUserData(tkey,tdata, domDataHandl,getter_AddRefs(tmpData));
		JREX_LOGLN("JRexNodeImpl_SetUserDataInternal()--> **** SetUserData rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv) && tmpData){
			nsXPIDLString temp;
			rv=tmpData->GetAsWString(getter_Copies(temp));
			JREX_LOGLN("JRexNodeImpl_SetUserDataInternal()--> **** GetAsWString rv<"<<rv<<"> ****")
			if(NS_SUCCEEDED(rv)){
				NS_STR_TO_JSTR(env,temp,jval)
			}
		}
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}





 /*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    AppendChild
 * Signature: (Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_AppendChild
  (JNIEnv *env, jobject jnodeObj, jobject jchildNode){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("AppendChild()--> **** thisNode <"<<thisNode<<"> ****")

	nsIDOMNode* childNode=nsnull;
	if(NOT_NULL(jchildNode))
		childNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jchildNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("AppendChild()--> **** childNode <"<<childNode<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(childNode)){
		ThrowJRexException(env, "**** AppendChild()--> thisNode/childNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("AppendChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_AppendChildInternal(env, thisNode, childNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_APPEND_CHILD, childNode, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("AppendChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("AppendChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("AppendChild()--> **** AppendChild DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("AppendChild()--> **** AppendChild NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** AppendChild Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    CloneNode
 * Signature: (Z)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_CloneNode
  (JNIEnv *env, jobject jnodeObj, jboolean jdeep){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CloneNode()--> **** thisNode <"<<thisNode<<"> jdeep <"<<jdeep<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "CloneNode()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CloneNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_CloneNodeInternal(env, thisNode, (jdeep==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_CLONE_NODE, (void*)(jdeep==JNI_TRUE?PR_TRUE:PR_FALSE), PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("CloneNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CloneNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CloneNode()--> **** CloneNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CloneNode()--> **** CloneNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CloneNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetAttributes
 * Signature: ()Lorg/w3c/dom/NamedNodeMap;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetAttributes
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetAttributes()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetAttributes()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetAttributes()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetAttributesInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_ATTRIBUTES, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetAttributes()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetAttributes()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetAttributes()--> **** GetAttributes NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetAttributes Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetChildNodes
 * Signature: ()Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetChildNodes
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetChildNodes()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetChildNodes()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetChildNodes()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetChildNodesInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_CHILD_NODES, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetChildNodes()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetChildNodes()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetChildNodes()--> **** GetChildNodes NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetChildNodes Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetFirstChild
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetFirstChild
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetFirstChild()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetFirstChild()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetFirstChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetFirstChildInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_FIRST_CHILD, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetFirstChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetFirstChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetFirstChild()--> **** GetFirstChild NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetFirstChild Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetLastChild
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetLastChild
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetLastChild()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetLastChild()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetLastChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetLastChildInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_LAST_CHILD, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetLastChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetLastChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetLastChild()--> **** GetLastChild NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetLastChild Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetLocalName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetLocalName
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetLocalName()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetLocalName()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsEmbedString retString;
	nsresult rv = thisNode->GetLocalName(retString);
	JREX_LOGLN("GetLocalName()--> **** GetLocalName rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetLocalName()--> **** GetLocalName NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetLocalName Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetNamespaceURI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetNamespaceURI
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNamespaceURI()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetNamespaceURI()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsEmbedString retString;
	nsresult rv = thisNode->GetNamespaceURI(retString);
	JREX_LOGLN("GetNamespaceURI()--> **** GetNamespaceURI rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetNamespaceURI()--> **** GetNamespaceURI NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetNamespaceURI Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetNextSibling
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetNextSibling
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNextSibling()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetNextSibling()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNextSibling()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetNextSiblingInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_NEXT_SIB, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetNextSibling()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetNextSibling()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetNextSibling()--> **** GetNextSibling NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetNextSibling Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetNodeName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetNodeName
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNodeName()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetNodeName()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsEmbedString retString;
	nsresult rv = thisNode->GetNodeName(retString);
	JREX_LOGLN("GetNodeName()--> **** GetNodeName rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetNodeName()--> **** GetNodeName NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetNodeName Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetNodeType
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetNodeType
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNodeType()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetNodeType()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return 0;
	}

	PRUint16 type=0;
	nsresult rv = thisNode->GetNodeType(&type);
	JREX_LOGLN("GetNodeType()--> **** GetNodeType rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetNodeType()--> **** GetNodeType NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetNodeType Failed ****",rv);
		return 0;
	}
	return (jshort)type;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetNodeValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetNodeValue
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetNodeValue()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetNodeValue()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNodeValue()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetNodeValueInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_NODE_VALUE, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetNodeValue()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
		}
	JREX_LOGLN("GetNodeValue()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
	if(NS_FAILED(rv)){
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetNodeValue()--> **** InsertBefore DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
				JREX_LOGLN("GetNodeValue()--> **** InsertBefore NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** InsertBefore Failed ****",rv);
		}
		return NULL;
	}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetOwnerDocument
 * Signature: ()Lorg/w3c/dom/Document;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetOwnerDocument
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetOwnerDocument()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetOwnerDocument()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetOwnerDocument()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetOwnerDocumentInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_OWNER_DOC, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetOwnerDocument()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetOwnerDocument()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetOwnerDocument()--> **** GetOwnerDocument NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetOwnerDocument Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetParentNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetParentNode
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetParentNode()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetParentNode()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetParentNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetParentNodeInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_PARENT_NODE, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetParentNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetParentNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetParentNode()--> **** GetParentNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetParentNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetPrefix
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetPrefix
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetPrefix()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetPrefix()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	nsEmbedString retString;
	nsresult rv = thisNode->GetPrefix(retString);
	JREX_LOGLN("GetPrefix()--> **** GetPrefix rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetPrefix()--> **** GetPrefix NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetPrefix Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetPreviousSibling
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetPreviousSibling
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetPreviousSibling()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetPreviousSibling()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetPreviousSibling()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetPreviousSiblingInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_PREV_SIB, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetPreviousSibling()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetPreviousSibling()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetPreviousSibling()--> **** GetPreviousSibling NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetPreviousSibling Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    HasAttributes
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_HasAttributes
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("HasAttributes()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "HasAttributes()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->HasAttributes(&retBool);
	JREX_LOGLN("HasAttributes()--> **** HasAttributes rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("HasAttributes()--> **** HasAttributes NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** HasAttributes Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    HasChildNodes
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_HasChildNodes
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("HasChildNodes()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "HasChildNodes()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->HasChildNodes(&retBool);
	JREX_LOGLN("HasChildNodes()--> **** HasChildNodes rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("HasChildNodes()--> **** HasChildNodes NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** HasChildNodes Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    InsertBefore
 * Signature: (Lorg/w3c/dom/Node;Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_InsertBefore
  (JNIEnv *env, jobject jnodeObj, jobject jnewChild, jobject jrefChild){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertBefore()--> **** thisNode <"<<thisNode<<"> ****")

	nsIDOMNode* newChild=nsnull;
	if(NOT_NULL(jnewChild))
		newChild=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnewChild, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertBefore()--> **** newChild <"<<newChild<<"> ****")

	nsIDOMNode* refChildNode=nsnull;
	if(NOT_NULL(jrefChild))
		refChildNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jrefChild, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertBefore()--> **** refChildNode <"<<refChildNode<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(newChild) || IS_NULL(refChildNode)){
		ThrowJRexException(env, "**** InsertBefore()--> thisNode/newChild/refChildNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("InsertBefore()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_InsertBeforeInternal(env, thisNode, newChild, refChildNode);
	}else{
		JRexNodeEventParam* param=new JRexNodeEventParam;
		if(IS_NULL(param))return NULL;
		param->node1=newChild;
		param->node2=refChildNode;

		nsresult rv=ExecInEventQDOM(thisNode, JREX_INST_BEFORE, param, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("InsertBefore()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("InsertBefore()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("InsertBefore()--> **** InsertBefore DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("InsertBefore()--> **** InsertBefore NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** InsertBefore Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}
/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    IsSupported
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_IsSupported
  (JNIEnv *env, jobject jnodeObj, jstring jfeature, jstring jversion){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("IsSupported()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "IsSupported()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRUnichar* feature=nsnull;
	JSTR_TO_NEW_PRUNI(env, jfeature, feature);
	PRUnichar* version=nsnull;
	JSTR_TO_NEW_PRUNI(env, jversion, version);

	nsEmbedString tfeature(feature);
	nsEmbedString tversion(version);

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->IsSupported(tfeature, tversion, &retBool);
	if(feature)nsMemory::Free(feature);
	if(version)nsMemory::Free(version);
	JREX_LOGLN("IsSupported()--> **** IsSupported rv<"<<rv<<"> ****")

	if(NS_FAILED(rv)){
		JREX_LOGLN("IsSupported()--> **** IsSupported NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** IsSupported Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    Normalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_Normalize
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("Normalize()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "Normalize()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return;
	}

	nsresult rv = thisNode->Normalize();
	JREX_LOGLN("Normalize()--> **** Normalize rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("Normalize()--> **** Normalize NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** Normalize Failed ****",rv);
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    RemoveChild
 * Signature: (Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_RemoveChild
  (JNIEnv *env, jobject jnodeObj, jobject joldChild){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RemoveChild()--> **** thisNode <"<<thisNode<<"> ****")

	nsIDOMNode* oldChild=nsnull;
	if(NOT_NULL(joldChild))
		oldChild=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(joldChild, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RemoveChild()--> **** oldChild <"<<oldChild<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(oldChild)){
		ThrowJRexException(env, "**** RemoveChild()--> thisNode/oldChild DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_RemoveChildInternal(env, thisNode, oldChild);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_REMOVE_CHILD, oldChild, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("RemoveChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveChild()--> **** RemoveChild DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveChild()--> **** RemoveChild NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveChild Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    ReplaceChild
 * Signature: (Lorg/w3c/dom/Node;Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_ReplaceChild
  (JNIEnv *env, jobject jnodeObj, jobject jnewChild, jobject joldChild){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ReplaceChild()--> **** thisNode <"<<thisNode<<"> ****")

	nsIDOMNode* newChild=nsnull;
	if(NOT_NULL(jnewChild))
		newChild=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnewChild, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ReplaceChild()--> **** newChild <"<<newChild<<"> ****")

	nsIDOMNode* oldChild=nsnull;
	if(NOT_NULL(joldChild))
		oldChild=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(joldChild, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ReplaceChild()--> **** oldChild <"<<oldChild<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(newChild) || IS_NULL(oldChild)){
		ThrowJRexException(env, "**** ReplaceChild()--> thisNode/newChild/oldChild DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ReplaceChild()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_ReplaceChildInternal(env, thisNode, newChild, oldChild);
	}else{
		JRexNodeEventParam* param=new JRexNodeEventParam;
		if(IS_NULL(param))return NULL;
		param->node1=newChild;
		param->node2=oldChild;

		nsresult rv=ExecInEventQDOM(thisNode, JREX_REPLACE_CHILD, param, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("ReplaceChild()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ReplaceChild()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("ReplaceChild()--> **** ReplaceChild DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("ReplaceChild()--> **** ReplaceChild NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** ReplaceChild Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    SetNodeValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_SetNodeValue
  (JNIEnv *env, jobject jnodeObj, jstring jnodeValue){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetNodeValue()--> **** thisNode <"<<thisNode<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(jnodeValue)){
		ThrowJRexException(env, "SetNodeValue()--> **** thisNode/jnodeValue DOES NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* nodeValue=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnodeValue, nodeValue);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetNodeValue()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_SetNodeValueInternal(env, thisNode, nodeValue);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_SET_NODE_VALUE, (void*)nodeValue, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("SetNodeValue()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
		}
	JREX_LOGLN("SetNodeValue()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
	     if(NS_FAILED(rv)){
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("SetNodeValue()--> **** SetNodeValue DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
			JREX_LOGLN("SetNodeValue()--> **** SetNodeValue NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** SetNodeValue Failed ****",rv);
		}
	}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    SetPrefix
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_SetPrefix
  (JNIEnv *env, jobject jnodeObj, jstring jprefix){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetPrefix()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "SetPrefix()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* prefix=nsnull;
	JSTR_TO_NEW_PRUNI(env, jprefix, prefix);
	nsEmbedString tPrefix(prefix);

	nsresult rv =thisNode->SetPrefix(tPrefix);
	JREX_LOGLN("SetPrefix()--> **** SetPrefix rv<"<<rv<<"> ****")

	if(NS_FAILED(rv)){
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("SetPrefix()--> **** SetPrefix DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
			JREX_LOGLN("SetPrefix()--> **** SetPrefix NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** SetPrefix Failed ****",rv);
		}
	}
	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetEventTarget
 * Signature: (V)Lorg/w3c/dom/events/GetEventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetEventTarget
  (JNIEnv * env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetEventTarget()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetEventTarget()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetEventTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_GetEventTargetInternal(env, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisNode, JREX_GET_EVENT_TARGET, nsnull, PR_TRUE, HandleJRexNodeEvent, DestroyJRexNodeEvent, (void**)&jrv);
		JREX_LOGLN("GetEventTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetEventTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetEventTarget()--> **** GetEventTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetEventTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetBaseURI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetBaseURI
  (JNIEnv *env, jobject jnodeObj){
	GET_DOM_STRING_JNI(env , jnodeObj, 3Node, GetBaseURI, JREX_GET_BASE_URI, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    CompareDocumentPosition
 * Signature: (Lorg/w3c/dom/Node;)S
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_CompareDocumentPosition
  (JNIEnv *env, jobject jnodeObj, jobject jcmpNode){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	nsIDOMNode* cmpNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jcmpNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CompareDocumentPosition()--> **** thisNode <"<<thisNode<<"> cmpNode <"<<cmpNode<<"> ****")
	if(IS_NULL(thisNode)|| IS_NULL(cmpNode)){
		ThrowJRexException(env, "CompareDocumentPosition()--> **** thisNode/cmpNode DOES NOT EXIST!!! ****",0);
		return 0;
	}

	PRUint16 retVal =0;
	nsresult rv = thisNode->CompareDocumentPosition(cmpNode, &retVal);
	JREX_LOGLN("CompareDocumentPosition()--> **** CompareDocumentPosition rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("CompareDocumentPosition()--> **** CompareDocumentPosition DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
			JREX_LOGLN("CompareDocumentPosition()--> **** CompareDocumentPosition NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CompareDocumentPosition Failed ****",rv);
		}
		return 0;
	}
	return (jshort)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetTextContent
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetTextContent
  (JNIEnv *env, jobject jnodeObj){
	GET_DOM_STRING_JNI(env , jnodeObj, 3Node, GetTextContent, JREX_GET_TXT_CNT, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    SetTextContent
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_SetTextContent
  (JNIEnv *env, jobject jnodeObj, jstring jvalue){
	SET_DOM_STRING_JNI(env , jnodeObj, jvalue, 3Node, SetTextContent, JREX_SET_TXT_CNT, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    IsSameNode
 * Signature: (Lorg/w3c/dom/Node;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_IsSameNode
  (JNIEnv *env, jobject jnodeObj, jobject jcmpNode){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	nsIDOMNode* cmpNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jcmpNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("IsSameNode()--> **** thisNode <"<<thisNode<<"> cmpNode <"<<cmpNode<<"> ****")
	if(IS_NULL(thisNode)|| IS_NULL(cmpNode)){
		ThrowJRexException(env, "IsSameNode()--> **** thisNode/cmpNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->IsSameNode(cmpNode, &retBool);
	JREX_LOGLN("IsSameNode()--> **** IsSameNode rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("IsSameNode()--> **** IsSameNode NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** IsSameNode Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    LookupPrefix
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_LookupPrefix
  (JNIEnv *env, jobject jnodeObj, jstring jnamespaceURI){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("LookupPrefix()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "LookupPrefix()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	nsEmbedString tnamespaceURI(namespaceURI);

	nsEmbedString retString;
	nsresult rv = thisNode->LookupPrefix(tnamespaceURI, retString);
	JREX_LOGLN("LookupPrefix()--> **** LookupPrefix rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("LookupPrefix()--> **** LookupPrefix NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** LookupPrefix Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    IsDefaultNamespace
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_IsDefaultNamespace
  (JNIEnv *env, jobject jnodeObj, jstring jnameSpace){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("IsDefaultNamespace()--> **** thisNode <"<<thisNode<<">****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "IsDefaultNamespace()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRUnichar* nameSpace=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnameSpace, nameSpace);
	nsEmbedString tnameSpace(nameSpace);

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->IsDefaultNamespace(tnameSpace, &retBool);
	JREX_LOGLN("IsDefaultNamespace()--> **** IsDefaultNamespace rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("IsDefaultNamespace()--> **** IsDefaultNamespace NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** IsDefaultNamespace Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    LookupNamespaceURI
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_LookupNamespaceURI
  (JNIEnv *env, jobject jnodeObj, jstring jprefix){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("LookupNamespaceURI()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "LookupNamespaceURI()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	PRUnichar* prefix=nsnull;
	JSTR_TO_NEW_PRUNI(env, jprefix, prefix);
	nsEmbedString tprefix(prefix);

	nsEmbedString retString;
	nsresult rv = thisNode->LookupNamespaceURI(tprefix, retString);
	JREX_LOGLN("LookupNamespaceURI()--> **** LookupNamespaceURI rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("LookupNamespaceURI()--> **** LookupNamespaceURI NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** LookupNamespaceURI Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    IsEqualNode
 * Signature: (Lorg/w3c/dom/Node;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_IsEqualNode
  (JNIEnv *env, jobject jnodeObj, jobject jcmpNode){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	nsIDOMNode* cmpNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jcmpNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("IsEqualNode()--> **** thisNode <"<<thisNode<<"> cmpNode <"<<cmpNode<<"> ****")
	if(IS_NULL(thisNode)|| IS_NULL(cmpNode)){
		ThrowJRexException(env, "IsEqualNode()--> **** thisNode/cmpNode DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisNode->IsEqualNode(cmpNode, &retBool);
	JREX_LOGLN("IsEqualNode()--> **** IsEqualNode rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("IsEqualNode()--> **** IsEqualNode NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** IsEqualNode Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetFeature
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetFeature
  (JNIEnv *env, jobject jnodeObj, jstring jfeature, jstring jversion){
	  return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    SetUserData
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/w3c/dom/UserDataHandler;)Ljava/lang/Object;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_SetUserData
  (JNIEnv *env, jobject jnodeObj, jstring jkey, jstring jdata, jobject juserDataHandler){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetUserData()--> **** thisNode <"<<thisNode<<"> ****")

	if(IS_NULL(thisNode) || IS_NULL(jdata)){
		ThrowJRexException(env, "SetUserData()--> **** thisNode/jdata DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	PRUnichar* key=nsnull;
	JSTR_TO_NEW_PRUNI(env, jkey, key);
	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetUserData()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeImpl_SetUserDataInternal(env, thisNode, key, data, juserDataHandler);
	}else{
		JRexUserDataEventParam* param=new JRexUserDataEventParam;
		if(IS_NULL(param))return NULL;
		param->key=key;
		param->data=data;
		param->juserDataHandler=env->NewGlobalRef(juserDataHandler);
		nsresult rv=ExecInEventQDOM(thisNode, JREX_SET_USR_DATA, param, PR_TRUE, HandleJRex3NodeEvent, DestroyJRex3NodeEvent, (void**)&jrv);
		JREX_LOGLN("SetUserData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetUserData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
	    if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetUserData()--> **** SetUserData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetUserData()--> **** SetUserData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetUserData Failed ****",rv);
			}
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    GetUserData
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_GetUserData
  (JNIEnv *env, jobject jnodeObj, jstring jkey){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Node* thisNode=(nsIDOM3Node*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetUserData()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		ThrowJRexException(env, "GetUserData()--> **** thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	PRUnichar* key=nsnull;
	JSTR_TO_NEW_PRUNI(env, jkey, key);
	nsEmbedString tkey(key);

	nsIVariant *tmpData=nsnull;
	nsresult rv = thisNode->GetUserData(tkey, &tmpData);
	JREX_LOGLN("GetUserData()--> **** GetUserData rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetUserData()--> **** GetUserData NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetUserData Failed ****",rv);
		return NULL;
	}else
	if(tmpData){
		nsXPIDLString temp;
		rv=tmpData->GetAsWString(getter_Copies(temp));
		JREX_LOGLN("GetUserData()--> **** GetAsWString rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv)){
			NS_STR_TO_JSTR_RET(env,temp)
		}
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeImpl_Finalize
  (JNIEnv *env, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("JRexNodeImpl Finalize()--> **** thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode)){
		JREX_LOGLN("JRexNodeImpl Finalize()--> **** thisNode DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisNode)
	JREX_LOGLN("JRexNodeImpl Finalize()--> **** thisNode AFTER RELEASE <"<<thisNode<<"> ****");
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexNodeEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexNodeEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMNode> node(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_APPEND_CHILD:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_APPEND_CHILD EVENT!!!****")
			nsIDOMNode* childNode = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexNodeImpl_AppendChildInternal(nsnull, node.get(), childNode);
		}
		case JREX_CLONE_NODE:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_CLONE_NODE EVENT!!!****")
			return (void*)JRexNodeImpl_CloneNodeInternal(nsnull, node.get(), (PRBool)event->eventData);
		}
		case JREX_GET_ATTRIBUTES:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_ATTRIBUTES EVENT!!!****")
			return (void*)JRexNodeImpl_GetAttributesInternal(nsnull, node.get());
		}
		case JREX_GET_CHILD_NODES:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_CHILD_NODES EVENT!!!****")
			return (void*)JRexNodeImpl_GetChildNodesInternal(nsnull, node.get());
		}
		case JREX_GET_FIRST_CHILD:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_FIRST_CHILD EVENT!!!****")
			return (void*)JRexNodeImpl_GetFirstChildInternal(nsnull, node.get());
		}
		case JREX_GET_LAST_CHILD:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_LAST_CHILD EVENT!!!****")
			return (void*)JRexNodeImpl_GetLastChildInternal(nsnull, node.get());
		}
		case JREX_GET_NEXT_SIB:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_NEXT_SIB EVENT!!!****")
			return (void*)JRexNodeImpl_GetNextSiblingInternal(nsnull, node.get());
		}
		case JREX_GET_PREV_SIB:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_PREV_SIB EVENT!!!****")
			return (void*)JRexNodeImpl_GetPreviousSiblingInternal(nsnull, node.get());
		}
		case JREX_GET_NODE_VALUE:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_NODE_VALUE EVENT!!!****")
			return (void*)JRexNodeImpl_GetNodeValueInternal(nsnull, node.get());
		}
		case JREX_GET_OWNER_DOC:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_OWNER_DOC EVENT!!!****")
			return (void*)JRexNodeImpl_GetOwnerDocumentInternal(nsnull, node.get());
		}
		case JREX_GET_PARENT_NODE:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_PARENT_NODE EVENT!!!****")
			return (void*)JRexNodeImpl_GetParentNodeInternal(nsnull, node.get());
		}
		case JREX_INST_BEFORE:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_INST_BEFORE EVENT!!!****")
			JRexNodeEventParam* parm = NS_REINTERPRET_CAST(JRexNodeEventParam*, event->eventData);
			return (void*)JRexNodeImpl_InsertBeforeInternal(nsnull, node.get(), parm->node1, parm->node2);
		}
		case JREX_REMOVE_CHILD:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_REMOVE_CHILD EVENT!!!****")
			nsIDOMNode* childNode = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexNodeImpl_RemoveChildInternal(nsnull, node.get(), childNode);
		}
		case JREX_REPLACE_CHILD:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_REPLACE_CHILD EVENT!!!****")
			JRexNodeEventParam* parm = NS_REINTERPRET_CAST(JRexNodeEventParam*, event->eventData);
			return (void*)JRexNodeImpl_ReplaceChildInternal(nsnull, node.get(), parm->node1, parm->node2);
		}
		case JREX_SET_NODE_VALUE:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_SET_NODE_VALUE EVENT!!!****")
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexNodeImpl_SetNodeValueInternal(nsnull, node.get(),value);
		}
		case JREX_GET_EVENT_TARGET:
		{
			JREX_LOGLN("HandleJRexNodeEvent JREX_GET_EVENT_TARGET EVENT!!!****")
			return (void*)JRexNodeImpl_GetEventTargetInternal(nsnull, node.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexNodeEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexNodeEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexNodeEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexNodeEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData &&
			(event->eventType==JREX_INST_BEFORE
			|| event->eventType==JREX_REPLACE_CHILD)){
			JRexNodeEventParam* param = NS_REINTERPRET_CAST(JRexNodeEventParam*, event->eventData);
			delete param;
	}
	delete event;
}


void* PR_CALLBACK HandleJRex3NodeEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRex3NodeEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOM3Node> node(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_BASE_URI:
		{
			JREX_LOGLN("HandleJRex3NodeEvent JREX_GET_BASE_URI EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, node.get(), GetBaseURI, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TXT_CNT:
		{
			JREX_LOGLN("HandleJRex3NodeEvent JREX_GET_TXT_CNT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, node.get(), GetTextContent, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TXT_CNT:
		{
			JREX_LOGLN("HandleJRex3NodeEvent JREX_SET_TXT_CNT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, node.get(), SetTextContent, jrv)
			return (void*)jrv;
		}
		case JREX_SET_USR_DATA:
		{
			JREX_LOGLN("HandleJRex3NodeEvent JREX_SET_USR_DATA EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			JRexUserDataEventParam* param = NS_REINTERPRET_CAST(JRexUserDataEventParam*, event->eventData);
			return (void*)JRexNodeImpl_SetUserDataInternal(nsnull, node.get(),param->key,param->data,param->juserDataHandler);

		}
		default:
		{
			JREX_LOGLN("HandleJRex3NodeEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRex3NodeEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRex3NodeEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRex3NodeEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData
		&& event->eventType==JREX_SET_USR_DATA){
		JRexUserDataEventParam* param = NS_REINTERPRET_CAST(JRexUserDataEventParam*, event->eventData);
		delete param;
	}
	delete event;
}
