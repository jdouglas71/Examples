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


#include "org_mozilla_jrex_dom_events_JRexMouseEventImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexMouseEvent
enum JRexMouseEventEventTypes{JREX_GET_REL_TARGET=0U};

static void* PR_CALLBACK HandleJRexMouseEventEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexMouseEventEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexMouseEventImpl_GetRelatedTargetInternal(JNIEnv *env, nsIDOMMouseEvent* dMouseEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dMouseEvent){
		nsCOMPtr<nsIDOMEventTarget> tmpTarget;
		rv = dMouseEvent->GetRelatedTarget(getter_AddRefs(tmpTarget));
		JREX_LOGLN("JRexMouseEventImpl_GetRelatedTargetInternal()--> **** GetRelatedTarget rv<"<<rv<<"> ****")
		if(tmpTarget)
			jval=JRexDOMGlobals::CreateEventTarget(env, tmpTarget.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetScreenX
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetScreenX
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetScreenX()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetScreenX()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 retVal=0;
	nsresult rv = thisMouseEvent->GetScreenX(&retVal);
	JREX_LOGLN("GetScreenX()--> **** GetScreenX rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetScreenX()--> **** GetScreenX NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetScreenX Failed ****",rv);
		return 0;
	}
	return (jint)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetScreenY
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetScreenY
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetScreenY()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetScreenY()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 retVal=0;
	nsresult rv = thisMouseEvent->GetScreenY(&retVal);
	JREX_LOGLN("GetScreenY()--> **** GetScreenY rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetScreenY()--> **** GetScreenY NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetScreenY Failed ****",rv);
		return 0;
	}
	return (jint)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetClientX
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetClientX
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetClientX()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetClientX()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 retVal=0;
	nsresult rv = thisMouseEvent->GetClientX(&retVal);
	JREX_LOGLN("GetClientX()--> **** GetClientX rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetClientX()--> **** GetClientX NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetClientX Failed ****",rv);
		return 0;
	}
	return (jint)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetClientY
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetClientY
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetClientY()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetClientY()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 retVal=0;
	nsresult rv = thisMouseEvent->GetClientY(&retVal);
	JREX_LOGLN("GetClientY()--> **** GetClientY rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetClientY()--> **** GetClientY NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetClientY Failed ****",rv);
		return 0;
	}
	return (jint)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetCtrlKey
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetCtrlKey
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetCtrlKey()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetCtrlKey()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool boolRet=PR_FALSE;
	nsresult rv =thisMouseEvent->GetCtrlKey(&boolRet);
	JREX_LOGLN("GetCtrlKey()--> **** GetCtrlKey rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetCtrlKey()--> **** GetCtrlKey NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetCtrlKey Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetShiftKey
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetShiftKey
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetShiftKey()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetShiftKey()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool boolRet=PR_FALSE;
	nsresult rv =thisMouseEvent->GetShiftKey(&boolRet);
	JREX_LOGLN("GetShiftKey()--> **** GetShiftKey rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetShiftKey()--> **** GetShiftKey NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetShiftKey Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetAltKey
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetAltKey
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetAltKey()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetAltKey()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool boolRet=PR_FALSE;
	nsresult rv =thisMouseEvent->GetAltKey(&boolRet);
	JREX_LOGLN("GetAltKey()--> **** GetAltKey rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetAltKey()--> **** GetAltKey NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetAltKey Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetMetaKey
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetMetaKey
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetMetaKey()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetMetaKey()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool boolRet=PR_FALSE;
	nsresult rv =thisMouseEvent->GetMetaKey(&boolRet);
	JREX_LOGLN("GetMetaKey()--> **** GetMetaKey rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetMetaKey()--> **** GetMetaKey NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetMetaKey Failed ****",rv);
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetButton
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetButton
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetButton()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetButton()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint16 retVal=0;
	nsresult rv = thisMouseEvent->GetButton(&retVal);
	JREX_LOGLN("GetButton()--> **** GetButton rv<"<<rv<<"> retVal<"<<retVal<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetButton()--> **** GetButton NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetButton Failed ****",rv);
		return 0;
	}
	return (jshort)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    GetRelatedTarget
 * Signature: ()Lorg/w3c/dom/events/EventTarget;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_GetRelatedTarget
  (JNIEnv *env, jobject jdomMouseEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetRelatedTarget()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)){
		ThrowJRexException(env, "GetRelatedTarget()--> **** thisMouseEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetRelatedTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexMouseEventImpl_GetRelatedTargetInternal(env, thisMouseEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisMouseEvent, JREX_GET_REL_TARGET, nsnull, PR_TRUE,
						HandleJRexMouseEventEvent, DestroyJRexMouseEventEvent, (void**)&jrv);
		JREX_LOGLN("GetRelatedTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetRelatedTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetRelatedTarget()--> **** GetRelatedTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetRelatedTarget Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexMouseEventImpl
 * Method:    InitMouseEvent
 * Signature: (Ljava/lang/String;ZZLorg/w3c/dom/views/AbstractView;IIIIIZZZZSLorg/w3c/dom/events/EventTarget;)V
 */

JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexMouseEventImpl_InitMouseEvent
  (JNIEnv *env, jobject jdomMouseEvent, jstring jtype, jboolean jcanBubble, jboolean jcanCancel,
  	jobject jviewArg, jint jdetail, jint jscreenX, jint jscreenY, jint jclientX, jint jclientY,
  	jboolean jctrlKey, jboolean jaltKey, jboolean jshiftKey,
  				jboolean jmetaKey, jshort jbutton, jobject jevtTarget){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMMouseEvent* thisMouseEvent=(nsIDOMMouseEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomMouseEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("InitMouseEvent()--> **** thisMouseEvent <"<<thisMouseEvent<<"> ****")
	if(IS_NULL(thisMouseEvent)  || IS_NULL(jtype)){
		ThrowJRexException(env, "InitMouseEvent()--> **** thisMouseEvent/jtype DOES NOT EXIST!!! ****",0);
		return;
	}

	nsIDOMAbstractView* view=nsnull;
	if(NOT_NULL(jviewArg))
		view=(nsIDOMAbstractView*)NS_INT32_TO_PTR(env->GetIntField(jviewArg, JRexDOMGlobals::abstractViewPeerID));
	JREX_LOGLN("InitMouseEvent()--> **** view <"<<view<<"> ****")

	nsIDOMEventTarget* target=nsnull;
	if(NOT_NULL(jevtTarget))
		target=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	JREX_LOGLN("InitMouseEvent()--> **** view <"<<view<<"> ****")

	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);
	nsEmbedString ttype(type);

	nsresult rv = thisMouseEvent->InitMouseEvent(ttype,
					(jcanBubble==JNI_TRUE?PR_TRUE:PR_FALSE), (jcanCancel==JNI_TRUE?PR_TRUE:PR_FALSE),
					view,(PRInt32)jdetail,(PRInt32)jscreenX,(PRInt32)jscreenY,(PRInt32)jclientX,(PRInt32)jclientY,
					(jctrlKey==JNI_TRUE?PR_TRUE:PR_FALSE),(jaltKey==JNI_TRUE?PR_TRUE:PR_FALSE),(jshiftKey==JNI_TRUE?PR_TRUE:PR_FALSE),
					(jmetaKey==JNI_TRUE?PR_TRUE:PR_FALSE),(PRUint16)jbutton,target);

	JREX_LOGLN("InitMouseEvent()--> **** InitMouseEvent rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("InitMouseEvent()--> **** InitMouseEvent NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** InitMouseEvent Failed ****",rv);
	}
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexMouseEventEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexMouseEventEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_REL_TARGET:
		{
			JREX_LOGLN("HandleJRexMouseEventEvent JREX_GET_REL_TARGET EVENT!!!****")
			nsCOMPtr<nsIDOMMouseEvent> me(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexMouseEventImpl_GetRelatedTargetInternal(nsnull, me.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexMouseEventEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexMouseEventEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexMouseEventEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexMouseEventEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}


