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


#include "org_mozilla_jrex_dom_events_JRexEventImpl.h"
#include "nsIDOMNSEvent.h"//Don't change the order
#include "JRexDOMGlobals.h"

//event types for JRexDOMEvent
enum JRexDOMEventEventTypes{JREX_GET_TARGET=0U,
							JREX_GET_CURR_TARGET,
							JREX_GET_ORIG_TARGET,
							JREX_GET_EXP_ORIG_TARGET};

static void* PR_CALLBACK HandleJRexDOMEventEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDOMEventEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventImpl_GetTargetInternal(JNIEnv *env, nsIDOMEvent* domEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domEvent){
		nsCOMPtr<nsIDOMEventTarget> tmpTarget;
		rv = domEvent->GetTarget(getter_AddRefs(tmpTarget));
		JREX_LOGLN("JRexEventImpl_GetTargetInternal()--> **** GetTarget rv<"<<rv<<"> ****")
		if(tmpTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, tmpTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventImpl_GetCurrentTargetInternal(JNIEnv *env, nsIDOMEvent* domEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domEvent){
		nsCOMPtr<nsIDOMEventTarget> tmpTarget;
		rv = domEvent->GetCurrentTarget(getter_AddRefs(tmpTarget));
		JREX_LOGLN("JRexEventImpl_GetCurrentTargetInternal()--> **** GetCurrentTarget rv<"<<rv<<"> ****")
		if(tmpTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, tmpTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventImpl_GetOriginalTargetInternal(JNIEnv *env, nsIDOMEvent* domEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	nsCOMPtr<nsIDOMNSEvent> nsevent;
	if (domEvent && (nsevent=do_QueryInterface(domEvent))){
		nsCOMPtr<nsIDOMEventTarget> tmpTarget;
		rv=nsevent->GetOriginalTarget(getter_AddRefs(tmpTarget));
		JREX_LOGLN("JRexEventImpl_GetOriginalTargetInternal()--> **** GetOriginalTarget rv<"<<rv<<"> ****")
		if(tmpTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, tmpTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventImpl_GetExplicitOriginalTargetInternal(JNIEnv *env, nsIDOMEvent* domEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	nsCOMPtr<nsIDOMNSEvent> nsevent;
	if (domEvent && (nsevent=do_QueryInterface(domEvent))){
		nsCOMPtr<nsIDOMEventTarget> tmpTarget;
		rv=nsevent->GetExplicitOriginalTarget(getter_AddRefs(tmpTarget));
		JREX_LOGLN("JRexEventImpl_GetExplicitOriginalTargetInternal()--> **** GetExplicitOriginalTarget rv<"<<rv<<"> ****")
		if(tmpTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, tmpTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetType
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetType()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetType()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsEmbedString retString;
	nsresult rv = thisEvent->GetType(retString);
	JREX_LOGLN("GetType()--> **** GetType rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetType()--> **** GetType NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetType Failed ****",rv);
		return NULL;
	}
	NS_STR_TO_JSTR_RET(env,retString)
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetTarget
 * Signature: ()Lorg/w3c/dom/events/EventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetTarget
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetTarget()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetTarget()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventImpl_GetTargetInternal(env, thisEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisEvent, JREX_GET_TARGET, nsnull, PR_TRUE,
						HandleJRexDOMEventEvent, DestroyJRexDOMEventEvent, (void**)&jrv);
		JREX_LOGLN("GetTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetTarget()--> **** GetTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetCurrentTarget
 * Signature: ()Lorg/w3c/dom/events/EventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetCurrentTarget
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetCurrentTarget()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetCurrentTarget()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetCurrentTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventImpl_GetCurrentTargetInternal(env, thisEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisEvent, JREX_GET_CURR_TARGET, nsnull, PR_TRUE,
						HandleJRexDOMEventEvent, DestroyJRexDOMEventEvent, (void**)&jrv);
		JREX_LOGLN("GetCurrentTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetCurrentTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetCurrentTarget()--> **** GetCurrentTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetCurrentTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetOriginalTarget
 * Signature: ()Lorg/w3c/dom/events/EventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetOriginalTarget
  (JNIEnv *env, jobject jdomEvent){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetOriginalTarget()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetOriginalTarget()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetOriginalTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventImpl_GetOriginalTargetInternal(env, thisEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisEvent, JREX_GET_ORIG_TARGET, nsnull, PR_TRUE,
						HandleJRexDOMEventEvent, DestroyJRexDOMEventEvent, (void**)&jrv);
		JREX_LOGLN("GetOriginalTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetOriginalTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetOriginalTarget()--> **** GetOriginalTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetOriginalTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetExplicitOriginalTarget
 * Signature: ()Lorg/w3c/dom/events/EventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetExplicitOriginalTarget
  (JNIEnv *env, jobject jdomEvent){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetExplicitOriginalTarget()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetExplicitOriginalTarget()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetExplicitOriginalTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventImpl_GetExplicitOriginalTargetInternal(env, thisEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisEvent, JREX_GET_EXP_ORIG_TARGET, nsnull, PR_TRUE,
						HandleJRexDOMEventEvent, DestroyJRexDOMEventEvent, (void**)&jrv);
		JREX_LOGLN("GetExplicitOriginalTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetExplicitOriginalTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetExplicitOriginalTarget()--> **** GetExplicitOriginalTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetExplicitOriginalTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetEventPhase
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetEventPhase
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetEventPhase()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetEventPhase()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint16 retVal=0;
	nsresult rv = thisEvent->GetEventPhase(&retVal);
	JREX_LOGLN("GetEventPhase()--> **** GetEventPhase rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetEventPhase()--> **** GetEventPhase NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetEventPhase Failed ****",rv);
		return 0;
	}
	return (jshort)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetBubbles
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetBubbles
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetBubbles()--> **** thisEvent <"<<thisEvent<<"> ****")

	if(IS_NULL(thisEvent)){
		JREX_LOGLN("GetBubbles()--> **** thisEvent DOES NOT EXIST!!! ****");
		return JNI_FALSE;
	}
	PRBool boolRet=PR_FALSE;
	nsresult rv =thisEvent->GetBubbles(&boolRet);
	JREX_LOGLN("GetBubbles()--> **** GetBubbles rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetBubbles()--> **** GetBubbles NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetBubbles Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetCancelable
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetCancelable
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetCancelable()--> **** thisEvent <"<<thisEvent<<"> ****")

	if(IS_NULL(thisEvent)){
		JREX_LOGLN("GetCancelable()--> **** thisEvent DOES NOT EXIST!!! ****");
		return JNI_FALSE;
	}
	PRBool boolRet=PR_FALSE;
	nsresult rv =thisEvent->GetCancelable(&boolRet);
	JREX_LOGLN("GetCancelable()--> **** GetCancelable rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetCancelable()--> **** GetCancelable NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetCancelable Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    GetTimeStamp
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_GetTimeStamp
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetTimeStamp()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "GetTimeStamp()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	DOMTimeStamp retVal=0;
	nsresult rv = thisEvent->GetTimeStamp(&retVal);
	JREX_LOGLN("GetTimeStamp()--> **** GetTimeStamp rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetTimeStamp()--> **** GetTimeStamp NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetTimeStamp Failed ****",rv);
		return 0;
	}
	return (jlong)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    StopPropagation
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_StopPropagation
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("StopPropagation()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "StopPropagation()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv = thisEvent->StopPropagation();
	JREX_LOGLN("StopPropagation()--> **** StopPropagation rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("StopPropagation()--> **** StopPropagation NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** StopPropagation Failed ****",rv);
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    PreventDefault
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_PreventDefault
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("PreventDefault()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "PreventDefault()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv = thisEvent->PreventDefault();
	JREX_LOGLN("PreventDefault()--> **** PreventDefault rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("PreventDefault()--> **** PreventDefault NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** PreventDefault Failed ****",rv);
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    InitEvent
 * Signature: (Ljava/lang/String;ZZ)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_InitEvent
  (JNIEnv *env, jobject jdomEvent, jstring jtype, jboolean jcanBubble, jboolean jcanCancel){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("InitEvent()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent) || IS_NULL(jtype)){
		ThrowJRexException(env, "InitEvent()--> **** thisEvent/jtype DOES NOT EXIST!!! ****",0);
		return;
	}
	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);
	nsEmbedString ttype(type);

	nsresult rv = thisEvent->InitEvent(ttype,
					(jcanBubble==JNI_TRUE?PR_TRUE:PR_FALSE), (jcanCancel==JNI_TRUE?PR_TRUE:PR_FALSE));
	JREX_LOGLN("InitEvent()--> **** InitEvent rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("InitEvent()--> **** InitEvent NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** InitEvent Failed ****",rv);
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventImpl_Finalize
  (JNIEnv *env, jobject jdomEvent){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEvent* thisEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("JRexEventImpl Finalize()--> **** thisEvent <"<<thisEvent<<"> ****")
	if(IS_NULL(thisEvent)){
		ThrowJRexException(env, "JRexEventImpl Finalize()--> **** thisEvent DOES NOT EXIST!!! ****",0);
		return;
	}
	SAFE_RELEASE(thisEvent)
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexDOMEventEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDOMEventEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMEvent> de(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_TARGET:
		{
			JREX_LOGLN("HandleJRexDOMEventEvent JREX_GET_TARGET EVENT!!!****")
			return (void*)JRexEventImpl_GetTargetInternal(nsnull, de.get());
		}
		case JREX_GET_CURR_TARGET:
		{
			JREX_LOGLN("HandleJRexDOMEventEvent JREX_GET_CURR_TARGET EVENT!!!****")
			return (void*)JRexEventImpl_GetCurrentTargetInternal(nsnull, de.get());
		}
		case JREX_GET_ORIG_TARGET:
		{
			JREX_LOGLN("HandleJRexDOMEventEvent JREX_GET_ORIG_TARGET EVENT!!!****")
			return (void*)JRexEventImpl_GetOriginalTargetInternal(nsnull, de.get());
		}
		case JREX_GET_EXP_ORIG_TARGET:
		{
			JREX_LOGLN("HandleJRexDOMEventEvent JREX_GET_EXP_ORIG_TARGET EVENT!!!****")
			return (void*)JRexEventImpl_GetExplicitOriginalTargetInternal(nsnull, de.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDOMEventEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDOMEventEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDOMEventEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDOMEventEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
