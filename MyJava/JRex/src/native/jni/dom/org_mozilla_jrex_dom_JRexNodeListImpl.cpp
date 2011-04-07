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


#include "org_mozilla_jrex_dom_JRexNodeListImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexNodeList
enum JRexNodeListEventTypes{	JREX_GET_ITEM=0U, JREX_GET_LENGTH};

static void* PR_CALLBACK HandleJRexNodeListEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexNodeListEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeListImpl_GetItemInternal(JNIEnv *env, nsIDOMNodeList* nodeList, PRUint32 index){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (nodeList){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = nodeList->Item(index, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexNodeListImpl_GetItemInternal()--> **** Item rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexNodeListImpl_GetLengthInternal(JNIEnv *env, nsIDOMNodeList* nodeList){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if(nodeList){
		PRUint32 length=0;
		rv = nodeList->GetLength(&length);
		JREX_LOGLN("JRexNodeListImpl_GetLengthInternal()--> **** GetLength rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			jval=(jobject)length;
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeListImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_JRexNodeListImpl_GetLength
  (JNIEnv * env, jobject jnodeListObj){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMNodeList* thisNodeList=(nsIDOMNodeList*)NS_INT32_TO_PTR(env->GetIntField(jnodeListObj, JRexDOMGlobals::nodeListPeerID));
	JREX_LOGLN("GetLength()--> **** thisNodeList <"<<thisNodeList<<"> ****")
	if(IS_NULL(thisNodeList)){
		ThrowJRexException(env, "GetLength()--> **** thisNodeList DOES NOT EXIST!!! ****",0);
		return 0;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetLength()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeListImpl_GetLengthInternal(env, thisNodeList);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeList, JREX_GET_LENGTH, nsnull, PR_TRUE, HandleJRexNodeListEvent, DestroyJRexNodeListEvent, (void**)&jrv);
		JREX_LOGLN("GetLength()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetLength()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetLength()--> **** GetLength NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetLength Failed ****",rv);
		return 0;
	}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexNodeListImpl
 * Method:    Item
 * Signature: (I)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexNodeListImpl_Item
  (JNIEnv * env, jobject jnodeListObj, jint jindex){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMNodeList* thisNodeList=(nsIDOMNodeList*)NS_INT32_TO_PTR(env->GetIntField(jnodeListObj, JRexDOMGlobals::nodeListPeerID));
	JREX_LOGLN("Item()--> **** thisNodeList <"<<thisNodeList<<"> ****")
	if(IS_NULL(thisNodeList)){
		ThrowJRexException(env, "Item()--> **** thisNodeList DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (jindex<0){
		JREX_LOGLN("Item()--> **** jindex < 0 ****")
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Item()--> **** IN EVT Q THREAD ****")
		jrv=JRexNodeListImpl_GetItemInternal(env, thisNodeList, (PRUint32)jindex);
	}else{
		nsresult rv=ExecInEventQDOM(thisNodeList, JREX_GET_ITEM, (void*)jindex, PR_TRUE, HandleJRexNodeListEvent, DestroyJRexNodeListEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_JRexNodeListImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexNodeListImpl_Finalize
  (JNIEnv * env, jobject jnodeListObj){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMNodeList* thisNodeList=(nsIDOMNodeList*)NS_INT32_TO_PTR(env->GetIntField(jnodeListObj, JRexDOMGlobals::nodeListPeerID));
	JREX_LOGLN("JRexNodeListImpl Finalize()--> **** thisNodeList <"<<thisNodeList<<"> ****")
	if(IS_NULL(thisNodeList)){
		JREX_LOGLN("JRexNodeListImpl Finalize()--> **** thisNodeList DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisNodeList)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexNodeListEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexNodeListEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_ITEM:
		{
			JREX_LOGLN("HandleJRexNodeListEvent JREX_GET_ITEM EVENT!!!****")
			nsCOMPtr<nsIDOMNodeList> nodeList(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexNodeListImpl_GetItemInternal(nsnull, nodeList.get(), (PRUint32)event->eventData);
		}
		case JREX_GET_LENGTH:
		{
			JREX_LOGLN("HandleJRexNodeListEvent JREX_GET_LENGTH EVENT!!!****")
			nsCOMPtr<nsIDOMNodeList> nodeList(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexNodeListImpl_GetLengthInternal(nsnull, nodeList.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexNodeListEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexNodeListEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexNodeListEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexNodeListEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

