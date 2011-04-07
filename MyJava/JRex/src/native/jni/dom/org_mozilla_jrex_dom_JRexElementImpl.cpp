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


#include "org_mozilla_jrex_dom_JRexElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexElement
enum JRexElementEventTypes{		JREX_GET_ATTR=0U,
								JREX_GET_ATTRNS,
								JREX_GET_ATTR_NODE,
								JREX_GET_ATTR_NODENS,
								JREX_GET_ELE_BY_TAG,
								JREX_GET_ELE_BY_TAGNS,
								JREX_GET_TAG_NAME,
								JREX_REMOVE_ATTR,
								JREX_REMOVE_ATTRNS,
								JREX_REMOVE_ATTR_NODE,
								JREX_SET_ATTR,
								JREX_SET_ATTRNS,
								JREX_SET_ATTR_NODE,
								JREX_SET_ATTR_NODENS};

static void* PR_CALLBACK HandleJRexElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexElementEvent(PLEvent* aEvent);

struct JRexElementEventParam{
	PRUnichar* nameSpace;
	PRUnichar* localName;
};

struct JRexSetAttrEventParam:JRexElementEventParam{
	PRUnichar* value;
};

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetAttributeInternal(JNIEnv *env, nsIDOMElement* ele, PRUnichar* name){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString retString;
		nsEmbedString tname(name);
		rv = ele->GetAttribute(tname, retString);
		JREX_LOGLN("JRexElementImpl_GetAttributeInternal()--> **** GetAttribute rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetAttributeNSInternal(JNIEnv *env, nsIDOMElement* ele,
								PRUnichar* nameSpace, PRUnichar* localName){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString retString;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);
		rv = ele->GetAttributeNS(tnameSpace, tlocalName,retString);
		JREX_LOGLN("JRexElementImpl_GetAttributeNSInternal()--> **** GetAttributeNS rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(localName)nsMemory::Free(localName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetAttributeNodeInternal(JNIEnv *env, nsIDOMElement* ele, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		nsEmbedString tname(name);
		rv = ele->GetAttributeNode(tname, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexElementImpl_GetAttributeNodeInternal()--> **** GetAttributeNode rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetAttributeNodeNSInternal(JNIEnv *env, nsIDOMElement* ele,
				PRUnichar* nameSpace, PRUnichar* localName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);
		rv = ele->GetAttributeNodeNS(tnameSpace, tlocalName, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexElementImpl_GetAttributeNodeNSInternal()--> **** GetAttributeNodeNS rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(localName)nsMemory::Free(localName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetElementsByTagNameInternal(JNIEnv *env, nsIDOMElement* ele, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		nsEmbedString tname(name);
		rv = ele->GetElementsByTagName(tname, getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexElementImpl_GetElementsByTagNameInternal()--> **** GetElementsByTagName rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetElementsByTagNameNSInternal(JNIEnv *env, nsIDOMElement* ele,
										PRUnichar* nameSpace, PRUnichar* localName) {
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);
		rv = ele->GetElementsByTagNameNS(tnameSpace, tlocalName, getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexElementImpl_GetElementsByTagNameNSInternal()--> **** GetElementsByTagNameNS rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(localName)nsMemory::Free(localName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_GetTagNameInternal(JNIEnv *env, nsIDOMElement* ele){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString retString;
		rv = ele->GetTagName(retString);
		JREX_LOGLN("JRexElementImpl_GetTagNameInternal()--> **** GetTagName rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_RemoveAttributeInternal(JNIEnv *env, nsIDOMElement* ele, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString tname(name);
		rv = ele->RemoveAttribute(tname);
		JREX_LOGLN("JRexElementImpl_RemoveAttributeInternal()--> **** RemoveAttribute rv<"<<rv<<"> ****")
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_RemoveAttributeNSInternal(JNIEnv *env, nsIDOMElement* ele,
										PRUnichar* nameSpace, PRUnichar* localName) {
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);
		rv = ele->RemoveAttributeNS(tnameSpace, tlocalName);
		JREX_LOGLN("JRexElementImpl_RemoveAttributeNSInternal()--> **** RemoveAttributeNS rv<"<<rv<<"> ****")
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(localName)nsMemory::Free(localName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_RemoveAttributeNodeInternal(JNIEnv *env, nsIDOMElement* ele, nsIDOMAttr* oldAttr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		rv = ele->RemoveAttributeNode(oldAttr, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexElementImpl_RemoveAttributeNodeInternal()--> **** RemoveAttributeNode rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_SetAttributeInternal(JNIEnv *env, nsIDOMElement* ele, PRUnichar* name, PRUnichar* value){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString tname(name);
		nsEmbedString tvalue(value);
		rv = ele->SetAttribute(tname,tvalue);
		JREX_LOGLN("JRexElementImpl_SetAttributeInternal()--> **** SetAttribute rv<"<<rv<<"> ****")
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_SetAttributeNSInternal(JNIEnv *env, nsIDOMElement* ele,
										PRUnichar* nameSpace, PRUnichar* localName, PRUnichar* value) {
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);
		nsEmbedString tvalue(value);
		rv = ele->SetAttributeNS(tnameSpace,tlocalName,tvalue);
		JREX_LOGLN("JRexElementImpl_SetAttributeNSInternal()--> **** SetAttributeNS rv<"<<rv<<"> ****")
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_SetAttributeNodeInternal(JNIEnv *env, nsIDOMElement* ele, nsIDOMAttr* newAttr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		rv = ele->SetAttributeNode(newAttr, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexElementImpl_SetAttributeNodeInternal()--> **** SetAttributeNode rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexElementImpl_SetAttributeNodeNSInternal(JNIEnv *env, nsIDOMElement* ele, nsIDOMAttr* newAttr){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		rv = ele->SetAttributeNodeNS(newAttr, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexElementImpl_SetAttributeNodeNSInternal()--> **** SetAttributeNodeNS rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetAttribute
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetAttribute
  (JNIEnv * env, jobject jele, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetAttribute()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetAttribute()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("GetAttribute()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetAttribute()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetAttributeInternal(env, thisEle, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ATTR, (void*)name, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetAttribute()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetAttribute()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetAttribute()--> **** GetAttribute NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetAttribute Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetAttributeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetAttributeNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI ,jstring jlocalName){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetAttributeNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetAttributeNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("GetAttributeNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetAttributeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetAttributeNSInternal(env, thisEle, namespaceURI, localName);
	}else{
		JRexElementEventParam *param=new JRexElementEventParam;
		if (IS_NULL(param))return NULL;
		param->nameSpace=namespaceURI;
		param->localName=localName;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ATTR_NODENS, param, PR_TRUE, HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetAttributeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetAttributeNS()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetAttributeNS()--> **** GetAttributeNS NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetAttributeNS Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetAttributeNode
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetAttributeNode
  (JNIEnv * env, jobject jele, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetAttributeNode()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetAttributeNode()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("GetAttributeNode()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetAttributeNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetAttributeNodeInternal(env, thisEle, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ATTR_NODE, (void*)name, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetAttributeNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetAttributeNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetAttributeNode()--> **** GetAttributeNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetAttributeNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetAttributeNodeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetAttributeNodeNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI ,jstring jlocalName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetAttributeNodeNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetAttributeNodeNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("GetAttributeNodeNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetAttributeNodeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetAttributeNodeNSInternal(env, thisEle, namespaceURI, localName);
	}else{
		JRexElementEventParam *param=new JRexElementEventParam;
		if (IS_NULL(param))return NULL;
		param->nameSpace=namespaceURI;
		param->localName=localName;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ATTR_NODENS, param, PR_TRUE, HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetAttributeNodeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetAttributeNodeNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetAttributeNodeNS()--> **** GetAttributeNodeNS NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetAttributeNodeNS Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;

}


/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetElementsByTagName
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetElementsByTagName
  (JNIEnv * env, jobject jele, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementsByTagName()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetElementsByTagName()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jname)){
		JREX_LOGLN("GetElementsByTagName()--> **** jname is NULL ****")
		return NULL;
	}
	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementsByTagName()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetElementsByTagNameInternal(env, thisEle, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ELE_BY_TAG, (void*)name, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetElementsByTagName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementsByTagName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetElementsByTagName()--> **** GetElementsByTagName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementsByTagName Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetElementsByTagNameNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetElementsByTagNameNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI ,jstring jlocalName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementsByTagNameNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetElementsByTagNameNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("GetElementsByTagNameNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementsByTagNameNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetElementsByTagNameNSInternal(env, thisEle, namespaceURI, localName);
	}else{
		JRexElementEventParam *param=new JRexElementEventParam;
		if (IS_NULL(param))return NULL;
		param->nameSpace=namespaceURI;
		param->localName=localName;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_ELE_BY_TAGNS, param, PR_TRUE, HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetElementsByTagNameNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementsByTagNameNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetElementsByTagNameNS()--> **** GetElementsByTagNameNS NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementsByTagNameNS Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    GetTagName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_GetTagName
  (JNIEnv * env, jobject jele){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetTagName()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetTagName()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetTagName()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_GetTagNameInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_TAG_NAME, nsnull, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("GetTagName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetTagName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetTagName()--> **** GetTagName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetTagName Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    HasAttribute
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_HasAttribute
  (JNIEnv * env, jobject jele, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("HasAttribute()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "HasAttribute()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	if (IS_NULL(jname)){
		JREX_LOGLN("HasAttribute()--> **** jname is NULL ****")
		return JNI_FALSE;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);
	nsEmbedString tname(name);

	PRBool retBool = PR_FALSE;
	nsresult rv = thisEle->HasAttribute(tname, &retBool);
	if(name)nsMemory::Free(name);
	JREX_LOGLN("HasAttribute()--> **** HasAttribute rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("HasAttribute()--> **** HasAttribute NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** HasAttribute Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    HasAttributeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_HasAttributeNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI ,jstring jlocalName){

	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("HasAttributeNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "HasAttributeNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("HasAttributeNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return JNI_FALSE;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	nsEmbedString tnamespaceURI(namespaceURI);
	nsEmbedString tlocalName(localName);

	PRBool retBool = PR_FALSE;
	nsresult rv = thisEle->HasAttributeNS(tnamespaceURI,tlocalName, &retBool);
	if(namespaceURI)nsMemory::Free(namespaceURI);
	if(localName)nsMemory::Free(localName);
	JREX_LOGLN("HasAttributeNS()--> **** HasAttributeNS rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("HasAttributeNS()--> **** HasAttributeNS NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** HasAttributeNS Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    RemoveAttribute
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_RemoveAttribute
  (JNIEnv * env, jobject jele, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RemoveAttribute()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "RemoveAttribute()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("RemoveAttribute()--> **** jname is NULL ****")
		return;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveAttribute()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_RemoveAttributeInternal(env, thisEle, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_REMOVE_ATTR, (void*)name, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("RemoveAttribute()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveAttribute()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveAttribute()--> **** RemoveAttribute DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveAttribute()--> **** RemoveAttribute NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveAttribute Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    RemoveAttributeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_RemoveAttributeNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI, jstring jlocalName){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RemoveAttributeNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "RemoveAttributeNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("RemoveAttributeNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveAttributeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_RemoveAttributeNSInternal(env, thisEle, namespaceURI, localName);
	}else{
		JRexElementEventParam *param=new JRexElementEventParam;
		if (IS_NULL(param))return;
		param->nameSpace=namespaceURI;
		param->localName=localName;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_REMOVE_ATTRNS, param, PR_TRUE, HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("RemoveAttributeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveAttributeNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveAttributeNS()--> **** RemoveAttributeNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveAttributeNS()--> **** RemoveAttributeNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveAttributeNS Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    RemoveAttributeNode
 * Signature: (Lorg/w3c/dom/Attr;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_RemoveAttributeNode
  (JNIEnv * env, jobject jele, jobject joldAttr){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY

	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	nsIDOMAttr* oldAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(joldAttr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RemoveAttributeNode()--> **** thisEle <"<<thisEle<<"> oldAttr <"<<oldAttr<<"> ****")

	if(IS_NULL(thisEle) || IS_NULL(oldAttr)){
		ThrowJRexException(env, "RemoveAttributeNode()--> **** thisEle/oldAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveAttributeNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_RemoveAttributeNodeInternal(env, thisEle, oldAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_REMOVE_ATTR_NODE, oldAttr, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("RemoveAttributeNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveAttributeNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RemoveAttributeNode()--> **** RemoveAttributeNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RemoveAttributeNode()--> **** RemoveAttributeNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RemoveAttributeNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    SetAttribute
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_SetAttribute
  (JNIEnv * env, jobject jele, jstring jname, jstring jvalue){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetAttribute()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "SetAttribute()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("SetAttribute()--> **** jname is NULL ****")
		return;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);
	PRUnichar* value=nsnull;
	JSTR_TO_NEW_PRUNI(env, jvalue, value);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetAttribute()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_SetAttributeInternal(env, thisEle, name, value);
	}else{
		JRexSetAttrEventParam *param=new JRexSetAttrEventParam;
		if (IS_NULL(param))return;
		param->nameSpace=name;
		param->value=value;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_SET_ATTR, param, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("SetAttribute()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetAttribute()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetAttribute()--> **** SetAttribute DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetAttribute()--> **** SetAttribute NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetAttribute Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    SetAttributeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_SetAttributeNS
  (JNIEnv * env, jobject jele, jstring jnamespaceURI ,jstring jlocalName, jstring jvalue){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetAttributeNS()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "SetAttributeNS()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("SetAttributeNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);
	PRUnichar* value=nsnull;
	JSTR_TO_NEW_PRUNI(env, jvalue, value);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetAttributeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_SetAttributeNSInternal(env, thisEle, namespaceURI, localName, value);
	}else{
		JRexSetAttrEventParam *param=new JRexSetAttrEventParam;
		if (IS_NULL(param))return;
		param->nameSpace=namespaceURI;
		param->localName=localName;
		param->value=value;

		nsresult rv=ExecInEventQDOM(thisEle, JREX_SET_ATTRNS, param, PR_TRUE, HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("SetAttributeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetAttributeNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetAttributeNS()--> **** SetAttributeNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetAttributeNS()--> **** SetAttributeNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetAttributeNS Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    SetAttributeNode
 * Signature: (Lorg/w3c/dom/Attr;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_SetAttributeNode
  (JNIEnv * env, jobject jele, jobject jnewAttr){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	nsIDOMAttr* newAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jnewAttr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetAttributeNode()--> **** thisEle <"<<thisEle<<"> newAttr <"<<newAttr<<"> ****")

	if(IS_NULL(thisEle) || IS_NULL(newAttr)){
		ThrowJRexException(env, "SetAttributeNode()--> **** thisEle/newAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetAttributeNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_SetAttributeNodeInternal(env, thisEle, newAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_SET_ATTR_NODE, newAttr, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("SetAttributeNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetAttributeNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetAttributeNode()--> **** SetAttributeNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetAttributeNode()--> **** SetAttributeNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetAttributeNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexElementImpl
 * Method:    SetAttributeNodeNS
 * Signature: (Lorg/w3c/dom/Attr;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexElementImpl_SetAttributeNodeNS
  (JNIEnv * env, jobject jele, jobject jnewAttr){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY

	nsIDOMElement* thisEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jele, JRexDOMGlobals::nodePeerID));
	nsIDOMAttr* newAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jnewAttr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetAttributeNodeNS()--> **** thisEle <"<<thisEle<<"> newAttr <"<<newAttr<<"> ****")

	if(IS_NULL(thisEle) || IS_NULL(newAttr)){
		ThrowJRexException(env, "SetAttributeNodeNS()--> **** thisEle/newAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetAttributeNodeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexElementImpl_SetAttributeNodeNSInternal(env, thisEle, newAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_SET_ATTR_NODENS, newAttr, PR_TRUE,
						HandleJRexElementEvent, DestroyJRexElementEvent, (void**)&jrv);
		JREX_LOGLN("SetAttributeNodeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetAttributeNodeNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetAttributeNodeNS()--> **** SetAttributeNodeNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetAttributeNodeNS()--> **** SetAttributeNodeNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetAttributeNodeNS Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


void* PR_CALLBACK HandleJRexElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ATTR:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ATTR EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexElementImpl_GetAttributeInternal(nsnull, ele.get(), name);
		}
		case JREX_GET_ATTRNS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ATTRNS EVENT!!!****")
			JRexElementEventParam* param = NS_REINTERPRET_CAST(JRexElementEventParam*, event->eventData);
			return (void*)JRexElementImpl_GetAttributeNSInternal(nsnull, ele.get(), param->nameSpace, param->localName);
		}
		case JREX_GET_ATTR_NODE:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ATTR_NODE EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexElementImpl_GetAttributeNodeInternal(nsnull, ele.get(), name);
		}
		case JREX_GET_ATTR_NODENS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ATTR_NODENS EVENT!!!****")
			JRexElementEventParam* param = NS_REINTERPRET_CAST(JRexElementEventParam*, event->eventData);
			return (void*)JRexElementImpl_GetAttributeNodeNSInternal(nsnull, ele.get(), param->nameSpace, param->localName);
		}
		case JREX_GET_ELE_BY_TAG:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ELE_BY_TAG EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexElementImpl_GetElementsByTagNameInternal(nsnull, ele.get(), name);
		}
		case JREX_GET_ELE_BY_TAGNS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_ELE_BY_TAGNS EVENT!!!****")
			JRexElementEventParam* param = NS_REINTERPRET_CAST(JRexElementEventParam*, event->eventData);
			return (void*)JRexElementImpl_GetElementsByTagNameNSInternal(nsnull, ele.get(), param->nameSpace, param->localName);
		}
		case JREX_GET_TAG_NAME:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_GET_TAG_NAME EVENT!!!****")
			return (void*)JRexElementImpl_GetTagNameInternal(nsnull, ele.get());
		}
		case JREX_REMOVE_ATTR:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_REMOVE_ATTR EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexElementImpl_RemoveAttributeInternal(nsnull, ele.get(), name);
		}
		case JREX_REMOVE_ATTRNS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_REMOVE_ATTRNS EVENT!!!****")
			JRexElementEventParam* param = NS_REINTERPRET_CAST(JRexElementEventParam*, event->eventData);
			return (void*)JRexElementImpl_RemoveAttributeNSInternal(nsnull, ele.get(), param->nameSpace, param->localName);
		}
		case JREX_REMOVE_ATTR_NODE:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_REMOVE_ATTR_NODE EVENT!!!****")
			nsIDOMAttr* oldAttr= NS_REINTERPRET_CAST(nsIDOMAttr*, event->eventData);
			return (void*)JRexElementImpl_RemoveAttributeNodeInternal(nsnull, ele.get(), oldAttr);
		}
		case JREX_SET_ATTR:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_SET_ATTR EVENT!!!****")
			JRexSetAttrEventParam* param = NS_REINTERPRET_CAST(JRexSetAttrEventParam*, event->eventData);
			return (void*)JRexElementImpl_SetAttributeInternal(nsnull, ele.get(), param->nameSpace, param->value);
		}
		case JREX_SET_ATTRNS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_SET_ATTRNS EVENT!!!****")
			JRexSetAttrEventParam* param = NS_REINTERPRET_CAST(JRexSetAttrEventParam*, event->eventData);
			return (void*)JRexElementImpl_SetAttributeNSInternal(nsnull, ele.get(), param->nameSpace, param->localName, param->value);
		}
		case JREX_SET_ATTR_NODE:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_SET_ATTR_NODE EVENT!!!****")
			nsIDOMAttr* newAttr= NS_REINTERPRET_CAST(nsIDOMAttr*, event->eventData);
			return (void*)JRexElementImpl_SetAttributeNodeInternal(nsnull, ele.get(), newAttr);
		}
		case JREX_SET_ATTR_NODENS:
		{
			JREX_LOGLN("HandleJRexElementEvent JREX_SET_ATTR_NODENS EVENT!!!****")
			nsIDOMAttr* newAttr= NS_REINTERPRET_CAST(nsIDOMAttr*, event->eventData);
			return (void*)JRexElementImpl_SetAttributeNodeNSInternal(nsnull, ele.get(), newAttr);
		}
		default:
		{
			JREX_LOGLN("HandleJRexElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexElementEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData){
		if(event->eventType==JREX_GET_ATTRNS || event->eventType==JREX_GET_ATTR_NODENS
		 || event->eventType==JREX_GET_ELE_BY_TAGNS || event->eventType==JREX_REMOVE_ATTRNS){
			JRexElementEventParam* param = NS_REINTERPRET_CAST(JRexElementEventParam*, event->eventData);
			delete param;
		}else
		if(event->eventType==JREX_SET_ATTR|| event->eventType==JREX_SET_ATTRNS){
			JRexSetAttrEventParam* param = NS_REINTERPRET_CAST(JRexSetAttrEventParam*, event->eventData);
			delete param;
		}
	}
	delete event;
}
