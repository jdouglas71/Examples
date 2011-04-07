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


#include "org_mozilla_jrex_dom_events_JRexMutationEventImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexMutation
enum JRexMutationEventTypes{JREX_GET_REL_NODE=0U};

static void* PR_CALLBACK HandleJRexMutationEventEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexMutationEventEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexMutationEventImpl_GetRelatedNodeInternal(JNIEnv *env, nsIDOMMutationEvent* dMutation){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dMutation){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = dMutation->GetRelatedNode(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexMutationEventImpl_GetRelatedNodeInternal()--> **** GetRelatedNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    GetRelatedNode
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_GetRelatedNode
  (JNIEnv *env, jobject jdomMutatEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetRelatedNode()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent)){
		ThrowJRexException(env, "GetRelatedNode()--> **** thisMutatEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetRelatedNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexMutationEventImpl_GetRelatedNodeInternal(env, thisMutatEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisMutatEvent, JREX_GET_REL_NODE, nsnull, PR_TRUE,
						HandleJRexMutationEventEvent, DestroyJRexMutationEventEvent, (void**)&jrv);
		JREX_LOGLN("GetRelatedNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetRelatedNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetRelatedNode()--> **** GetRelatedNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetRelatedNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    GetPrevValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_GetPrevValue
  (JNIEnv *env, jobject jdomMutatEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetPrevValue()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent)){
		ThrowJRexException(env, "GetPrevValue()--> **** thisMutatEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	nsEmbedString retString;
	nsresult rv = thisMutatEvent->GetPrevValue(retString);
	JREX_LOGLN("GetPrevValue()--> **** GetPrevValue rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetPrevValue()--> **** GetPrevValue NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetPrevValue Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    GetNewValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_GetNewValue
  (JNIEnv *env, jobject jdomMutatEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetNewValue()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent)){
		ThrowJRexException(env, "GetNewValue()--> **** thisMutatEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	nsEmbedString retString;
	nsresult rv = thisMutatEvent->GetNewValue(retString);
	JREX_LOGLN("GetNewValue()--> **** GetNewValue rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetNewValue()--> **** GetNewValue NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetNewValue Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    GetAttrName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_GetAttrName
  (JNIEnv *env, jobject jdomMutatEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetAttrName()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent)){
		ThrowJRexException(env, "GetAttrName()--> **** thisMutatEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	nsEmbedString retString;
	nsresult rv = thisMutatEvent->GetAttrName(retString);
	JREX_LOGLN("GetAttrName()--> **** GetAttrName rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetAttrName()--> **** GetAttrName NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetAttrName Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    GetAttrChange
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_GetAttrChange
  (JNIEnv *env, jobject jdomMutatEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetAttrChange()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent)){
		ThrowJRexException(env, "GetAttrChange()--> **** thisMutatEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}

	PRUint16 retVal=0;
	nsresult rv = thisMutatEvent->GetAttrChange(&retVal);
	JREX_LOGLN("GetAttrChange()--> **** GetAttrChange rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetAttrChange()--> **** GetAttrChange NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetAttrChange Failed ****",rv);
		return 0;
	}
	return (jshort)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMutationEventImpl
 * Method:    InitMutationEvent
 * Signature: (Ljava/lang/String;ZZLorg/w3c/dom/Node;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;S)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexMutationEventImpl_InitMutationEvent
  (JNIEnv *env, jobject jdomMutatEvent, jstring jtype, jboolean jcanBubble, jboolean jcanCancel,
  	jobject jrelatedNode, jstring jpreValue, jstring jnewValue, jstring jattrName, jshort jattrChange){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMMutationEvent* thisMutatEvent=(nsIDOMMutationEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMutatEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("InitMutationEvent()--> **** thisMutatEvent <"<<thisMutatEvent<<"> ****")
	if(IS_NULL(thisMutatEvent) || IS_NULL(jtype)){
		ThrowJRexException(env, "InitMutationEvent()--> **** thisMutatEvent/jtype DOES NOT EXIST!!! ****",0);
		return;
	}

	nsIDOMNode* node=nsnull;
	if(NOT_NULL(jrelatedNode))
		node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jrelatedNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InitMutationEvent()--> **** node <"<<node<<"> ****")

	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);
	PRUnichar* preValue=nsnull;
	JSTR_TO_NEW_PRUNI(env, jpreValue, preValue);
	PRUnichar* newValue=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnewValue, newValue);
	PRUnichar* attrName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jattrName, attrName);

	nsEmbedString ttype(type);
	nsEmbedString tpreValue(preValue);
	nsEmbedString tnewValue(newValue);
	nsEmbedString tattrName(attrName);

	nsresult rv = thisMutatEvent->InitMutationEvent(ttype,
					(jcanBubble==JNI_TRUE?PR_TRUE:PR_FALSE), (jcanCancel==JNI_TRUE?PR_TRUE:PR_FALSE),
					node,tpreValue,tnewValue,
					tattrName,(PRUint16)jattrChange);
	JREX_LOGLN("InitMutationEvent()--> **** InitMutationEvent rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("InitMutationEvent()--> **** InitMutationEvent NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** InitMutationEvent Failed ****",rv);
	}
	JREX_CATCH(env)
	return;
}


void* PR_CALLBACK HandleJRexMutationEventEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexMutationEventEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_REL_NODE:
		{
			JREX_LOGLN("HandleJRexMutationEventEvent JREX_GET_REL_NODE EVENT!!!****")
			nsCOMPtr<nsIDOMMutationEvent> dme(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexMutationEventImpl_GetRelatedNodeInternal(nsnull, dme.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexMutationEventEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexMutationEventEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexMutationEventEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexMutationEventEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
