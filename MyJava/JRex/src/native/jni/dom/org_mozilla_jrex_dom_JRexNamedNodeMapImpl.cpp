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


#include "org_mozilla_jrex_dom_JRexNamedNodeMapImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexNodeMap
enum JRexNodeMapEventTypes{	JREX_GET_NAMED_ITEM=0U,
							JREX_GET_NAMED_ITEMNS,
 							JREX_GET_ITEM,
 							JREX_REMOVE_NAMED_ITEM,
 							JREX_REMOVE_NAMED_ITEMNS,
 							JREX_SET_NAMED_ITEM,
 							JREX_SET_NAMED_ITEMNS};

static void* PR_CALLBACK HandleJRexNodeMapEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexNodeMapEvent(PLEvent* aEvent);

struct JRexNodeMapEventParam{
	PRUnichar* nameSpace;
	PRUnichar* qualifiedName;
};


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_GetNamedItemInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsEmbedString tname(name);
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->GetNamedItem(tname, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_GetNamedItemInternal()--> **** GetNamedItem rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_GetNamedItemNSInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap,
				PRUnichar* nameSpace, PRUnichar* qualifiedName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tqualifiedName(qualifiedName);
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->GetNamedItemNS(tnameSpace,tqualifiedName, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_GetNamedItemNSInternal()--> **** GetNamedItemNS rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(qualifiedName)nsMemory::Free(qualifiedName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_GetItemInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap, PRUint32 index){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->Item(index, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_GetItemInternal()--> **** Item rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_RemoveNamedItemInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsCOMPtr<nsIDOMNode> tmpNode;
		nsEmbedString tname(name);
		rv = nodeMap->RemoveNamedItem(tname, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_RemoveNamedItemInternal()--> **** RemoveNamedItem rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_RemoveNamedItemNSInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap,
				PRUnichar* nameSpace, PRUnichar* qualifiedName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tqualifiedName(qualifiedName);
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->RemoveNamedItemNS(tnameSpace,tqualifiedName, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_RemoveNamedItemNSInternal()--> **** RemoveNamedItemNS rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(qualifiedName)nsMemory::Free(qualifiedName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_SetNamedItemInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->SetNamedItem(node, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_SetNamedItemInternal()--> **** SetNamedItem rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNamedNodeMapImpl_SetNamedItemNSInternal(JNIEnv *env, nsIDOMNamedNodeMap* nodeMap, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeMap){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeMap->SetNamedItemNS(node, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNamedNodeMapImpl_SetNamedItemNSInternal()--> **** SetNamedItemNS rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_GetLength
  (JNIEnv * env, jobject jnodeMapObj){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("GetLength()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "GetLength()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return 0;
	}

	PRUint32 length=0;
	nsresult rv = thisNodeMap->GetLength(&length);
	JREX_LOGLN("GetLength()--> **** GetLength rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetLength()--> **** GetLength NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetLength Failed ****",rv);
		return 0;
	}
	return (jint)length;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    Item
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_GetNamedItem
  (JNIEnv * env, jobject jnodeMapObj, jstring jname){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("Item()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "Item()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return 0;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("Item()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Item()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_GetNamedItemInternal(env, thisNodeMap, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_GET_NAMED_ITEM, (void*)name, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    GetNamedItemNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_GetNamedItemNS
  (JNIEnv * env, jobject jnodeMapObj, jstring jnamespaceURI ,jstring jqualifiedName){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("GetNamedItemNS()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "GetNamedItemNS()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return 0;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName)){
		JREX_LOGLN("GetNamedItemNS()--> **** jnamespaceURI/jqualifiedName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNamedItemNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_GetNamedItemNSInternal(env, thisNodeMap, namespaceURI, qualifiedName);
	}else{
		JRexNodeMapEventParam *param=new JRexNodeMapEventParam;
		if (IS_NULL(param))return NULL;
		param->nameSpace=namespaceURI;
		param->qualifiedName=qualifiedName;

		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_GET_NAMED_ITEMNS, param, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
		JREX_LOGLN("GetNamedItemNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetNamedItemNS()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetNamedItemNS()--> **** GetNamedItemNS NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetNamedItemNS Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    Item
 * Signature: (I)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_Item
  (JNIEnv * env, jobject jnodeMapObj, jint jindex){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("Item()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "Item()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (jindex<0){
		JREX_LOGLN("Item()--> **** jindex < 0 ****")
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Item()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_GetItemInternal(env, thisNodeMap, (PRUint32)jindex);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_GET_ITEM, (void*)jindex, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    RemoveNamedItem
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_RemoveNamedItem
  (JNIEnv * env, jobject jnodeMapObj, jstring jname){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("RemoveNamedItem()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "RemoveNamedItem()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return 0;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("RemoveNamedItem()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveNamedItem()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_RemoveNamedItemInternal(env, thisNodeMap, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_REMOVE_NAMED_ITEM, (void*)name, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
		JREX_LOGLN("RemoveNamedItem()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveNamedItem()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveNamedItem()--> **** RemoveNamedItem DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveNamedItem()--> **** RemoveNamedItem NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveNamedItem Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    RemoveNamedItemNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_RemoveNamedItemNS
  (JNIEnv * env, jobject jnodeMapObj, jstring jnamespaceURI, jstring jqualifiedName){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("RemoveNamedItemNS()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		ThrowJRexException(env, "RemoveNamedItemNS()--> **** thisNodeMap DOES NOT EXIST!!! ****",0);
		return 0;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName)){
		JREX_LOGLN("RemoveNamedItemNS()--> **** jnamespaceURI/jqualifiedName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveNamedItemNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_RemoveNamedItemNSInternal(env, thisNodeMap, namespaceURI, qualifiedName);
	}else{
		JRexNodeMapEventParam *param=new JRexNodeMapEventParam;
		if (IS_NULL(param))return NULL;
		param->nameSpace=namespaceURI;
		param->qualifiedName=qualifiedName;

		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_REMOVE_NAMED_ITEMNS, param, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
		JREX_LOGLN("RemoveNamedItemNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveNamedItemNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveNamedItemNS()--> **** RemoveNamedItemNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveNamedItemNS()--> **** RemoveNamedItemNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveNamedItemNS Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    SetNamedItem
 * Signature: (Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_SetNamedItem
  (JNIEnv * env, jobject jnodeMapObj, jobject jnode){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	nsIDOMNode* node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetNamedItem()--> **** thisNodeMap <"<<thisNodeMap<<"> node <"<<node<<"> ****")

	if(IS_NULL(thisNodeMap) || IS_NULL(node)){
		ThrowJRexException(env, "SetNamedItem()--> **** thisNodeMap/node DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetNamedItem()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_SetNamedItemInternal(env, thisNodeMap, node);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_SET_NAMED_ITEM, node, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
		JREX_LOGLN("SetNamedItem()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetNamedItem()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetNamedItem()--> **** SetNamedItem DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetNamedItem()--> **** SetNamedItem NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetNamedItem Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    SetNamedItemNS
 * Signature: (Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_SetNamedItemNS
  (JNIEnv * env, jobject jnodeMapObj, jobject jnode){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	nsIDOMNode* node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetNamedItemNS()--> **** thisNodeMap <"<<thisNodeMap<<"> node <"<<node<<"> ****")

	if(IS_NULL(thisNodeMap) || IS_NULL(node)){
		ThrowJRexException(env, "SetNamedItemNS()--> **** thisNodeMap/node DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetNamedItemNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexNamedNodeMapImpl_SetNamedItemNSInternal(env, thisNodeMap, node);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeMap, JREX_SET_NAMED_ITEM, node, PR_TRUE, HandleJRexNodeMapEvent, DestroyJRexNodeMapEvent, (void**)&jrv);
		JREX_LOGLN("SetNamedItemNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetNamedItemNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetNamedItemNS()--> **** SetNamedItemNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetNamedItemNS()--> **** SetNamedItemNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetNamedItemNS Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNamedNodeMapImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNamedNodeMapImpl_Finalize
  (JNIEnv * env, jobject jnodeMapObj){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNamedNodeMap* thisNodeMap=(nsIDOMNamedNodeMap*)NS_INT32_TO_PTR(env->GetIntField(jnodeMapObj, JRexDOMGlobals::nodeMapPeerID));
	JREX_LOGLN("JRexNamedNodeMapImpl Finalize()--> **** thisNodeMap <"<<thisNodeMap<<"> ****")
	if(IS_NULL(thisNodeMap)){
		JREX_LOGLN("JRexNamedNodeMapImpl Finalize()--> **** thisNodeMap DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisNodeMap)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexNodeMapEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexNodeMapEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMNamedNodeMap> nodeMap(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_NAMED_ITEM:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_GET_NAMED_ITEM EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_GetNamedItemInternal(nsnull, nodeMap.get(), name);
		}
		case JREX_GET_NAMED_ITEMNS:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_GET_NAMED_ITEM EVENT!!!****")
			JRexNodeMapEventParam* param = NS_REINTERPRET_CAST(JRexNodeMapEventParam*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_GetNamedItemNSInternal(nsnull, nodeMap.get(), param->nameSpace, param->qualifiedName);
		}
		case JREX_GET_ITEM:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_GET_ITEM EVENT!!!****")
			return (void*)JRexNamedNodeMapImpl_GetItemInternal(nsnull, nodeMap.get(), (PRUint32)event->eventData);
		}
		case JREX_REMOVE_NAMED_ITEM:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_REMOVE_NAMED_ITEM EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_RemoveNamedItemInternal(nsnull, nodeMap.get(), name);
		}
		case JREX_REMOVE_NAMED_ITEMNS:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_REMOVE_NAMED_ITEMNS EVENT!!!****")
			JRexNodeMapEventParam* param = NS_REINTERPRET_CAST(JRexNodeMapEventParam*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_RemoveNamedItemNSInternal(nsnull, nodeMap.get(), param->nameSpace, param->qualifiedName);
		}
		case JREX_SET_NAMED_ITEM:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_SET_NAMED_ITEM EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_SetNamedItemInternal(nsnull, nodeMap.get(), node);
		}
		case JREX_SET_NAMED_ITEMNS:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent JREX_SET_NAMED_ITEMNS EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexNamedNodeMapImpl_SetNamedItemNSInternal(nsnull, nodeMap.get(), node);
		}
		default:
		{
			JREX_LOGLN("HandleJRexNodeMapEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexNodeMapEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexNodeMapEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexNodeMapEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData &&
			(event->eventType==JREX_GET_NAMED_ITEMNS
			|| event->eventType==JREX_REMOVE_NAMED_ITEMNS)){
			JRexNodeMapEventParam* param = NS_REINTERPRET_CAST(JRexNodeMapEventParam*, event->eventData);
			delete param;
	}
	delete event;
}
