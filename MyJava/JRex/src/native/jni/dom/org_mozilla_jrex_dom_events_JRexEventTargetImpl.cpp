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


#include "org_mozilla_jrex_dom_events_JRexEventTargetImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexDOMEventListener.h"

//event types for JRexDOMEvent
enum JRexEventTargetEventTypes{JREX_GET_NODE=0U,
							JREX_ADD_EVT_LISTENER,
							JREX_REMOVE_EVT_LISTENER,
							JREX_DISPATCH_EVENT};

static void* PR_CALLBACK HandleJRexEventTargetEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexEventTargetEvent(PLEvent* aEvent);

struct JRexEventTargetParam{
	PRUnichar* type;
	jobject jeventLis;
	PRBool useCapture;
};



inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventTargetImpl_GetNodeInternal(JNIEnv *env, nsIDOMEventTarget* domEventTarget){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domEventTarget){
		nsCOMPtr<nsIDOMNode> tmpNode(do_QueryInterface(domEventTarget,&rv));
		JREX_LOGLN("JRexEventTargetImpl_GetNodeInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventTargetImpl_AddEventListenerInternal(JNIEnv *env, nsIDOMEventTarget* domEventTarget,
											PRUnichar* type, jobject jeventLis, PRBool useCapture){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domEventTarget){
		nsIDOMEventListener* domListn=new JRexDOMEventListener(jeventLis);
		if(IS_NULL(domListn)){
			JREX_LOGLN("JRexEventTargetImpl_AddEventListenerInternal()--> **** nsIDOMEventListener creation Failed ***")
			jrv->rv=NS_ERROR_OUT_OF_MEMORY;
			return jrv;
		}
		jval=(jobject)domListn;
		nsEmbedString ttype(type);
		rv =domEventTarget->AddEventListener(ttype,domListn,useCapture);
		JREX_LOGLN("JRexEventTargetImpl_AddEventListenerInternal()--> **** AddEventListener rv<"<<rv<<"> ****")
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexEventTargetImpl_RemoveEventListenerInternal(JNIEnv *env, nsIDOMEventTarget* domEventTarget,
											PRUnichar* type, nsIDOMEventListener* domListn, PRBool useCapture){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (domEventTarget){
		nsEmbedString ttype(type);
		rv =domEventTarget->RemoveEventListener(ttype,domListn,useCapture);
		JREX_LOGLN("JRexEventTargetImpl_RemoveEventListenerInternal()--> **** RemoveEventListener rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventTargetImpl
 * Method:    GetNode
 * Signature: ()V
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexEventTargetImpl_GetNode
  (JNIEnv * env, jobject jevtTarget){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMEventTarget* thisEvtTarget=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	JREX_LOGLN("GetNode()--> **** thisEvtTarget <"<<thisEvtTarget<<"> ****")
	if(IS_NULL(thisEvtTarget)){
		JREX_LOGLN("GetNode()--> **** thisEvtTarget DOES NOT EXIST!!! ****");
		return 0;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventTargetImpl_GetNodeInternal(env, thisEvtTarget);
	}else{
		nsresult rv=ExecInEventQDOM(thisEvtTarget, JREX_GET_NODE, nsnull, PR_TRUE, HandleJRexEventTargetEvent, DestroyJRexEventTargetEvent, (void**)&jrv);
		JREX_LOGLN("GetNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetNode()--> **** GetNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventTargetImpl
 * Method:    AddEventListener
 * Signature: (Ljava/lang/String;Lorg/w3c/dom/events/EventListener;Z)V
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexEventTargetImpl_AddEventListener
  (JNIEnv * env, jobject jevtTarget, jstring jtype, jobject jeventLis, jboolean juseCapture){

	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMEventTarget* thisEvtTarget=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	JREX_LOGLN("AddEventListener()--> **** thisEvtTarget <"<<thisEvtTarget<<"> ****")
	if(IS_NULL(thisEvtTarget) || IS_NULL(jeventLis) || IS_NULL(jtype)){
		JREX_LOGLN("AddEventListener()--> **** thisEvtTarget/jeventLis/jtype DOES NOT EXIST!!! ****");
		return 0;
	}
	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("AddEventListener()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventTargetImpl_AddEventListenerInternal(env, thisEvtTarget, type, jeventLis, (juseCapture==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		JRexEventTargetParam* param=new JRexEventTargetParam;
		if(IS_NULL(param))return 0;
		param->type=type;
		param->jeventLis=env->NewGlobalRef(jeventLis);
		param->useCapture=(juseCapture==JNI_TRUE?PR_TRUE:PR_FALSE);
		nsresult rv=ExecInEventQDOM(thisEvtTarget, JREX_ADD_EVT_LISTENER, param, PR_TRUE, HandleJRexEventTargetEvent, DestroyJRexEventTargetEvent, (void**)&jrv);
		JREX_LOGLN("AddEventListener()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("AddEventListener()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("AddEventListener()--> **** AddEventListener NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** AddEventListener Failed ****",rv);
			return 0;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventTargetImpl
 * Method:    RemoveEventListener
 * Signature: (Ljava/lang/String;Lorg/w3c/dom/events/EventListener;Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventTargetImpl_RemoveEventListener
  (JNIEnv * env, jobject jevtTarget, jstring jtype, jint jeventLisPeer, jboolean juseCapture){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEventTarget* thisEvtTarget=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	nsIDOMEventListener* domListn=(nsIDOMEventListener*)NS_INT32_TO_PTR(jeventLisPeer);
	JREX_LOGLN("RemoveEventListener()--> **** thisEvtTarget <"<<thisEvtTarget<<"> domListn<"<<domListn<<"> ****")
	if(IS_NULL(thisEvtTarget) || IS_NULL(domListn) || IS_NULL(jtype)){
		JREX_LOGLN("RemoveEventListener()--> **** thisEvtTarget/domListn/jtype DOES NOT EXIST!!! ****");
		return;
	}

	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RemoveEventListener()--> **** IN EVT Q THREAD ****")
		jrv=JRexEventTargetImpl_RemoveEventListenerInternal(env, thisEvtTarget, type, domListn, (juseCapture==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		JRexEventTargetParam* param=new JRexEventTargetParam;
		if(IS_NULL(param))return;
		param->type=type;
		param->jeventLis=(jobject)domListn;
		param->useCapture=(juseCapture==JNI_TRUE?PR_TRUE:PR_FALSE);
		nsresult rv=ExecInEventQDOM(thisEvtTarget, JREX_REMOVE_EVT_LISTENER, param, PR_TRUE, HandleJRexEventTargetEvent, DestroyJRexEventTargetEvent, (void**)&jrv);
		JREX_LOGLN("RemoveEventListener()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RemoveEventListener()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("RemoveEventListener()--> **** RemoveEventListener NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** RemoveEventListener Failed ****",rv);
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventTargetImpl
 * Method:    DispatchEvent
 * Signature: (Lorg/w3c/dom/events/Event;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_events_JRexEventTargetImpl_DispatchEvent
  (JNIEnv * env, jobject jevtTarget, jobject jevent){

	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMEventTarget* thisEvtTarget=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	nsIDOMEvent* domEvent=(nsIDOMEvent*)NS_INT32_TO_PTR(env->GetIntField(jevent, JRexDOMGlobals::domEventPeerID));

	JREX_LOGLN("DispatchEvent()--> **** thisEvtTarget <"<<thisEvtTarget<<"> domEvent <"<<domEvent<<"> ****")
	if(IS_NULL(thisEvtTarget) || IS_NULL(domEvent)){
		JREX_LOGLN("DispatchEvent()--> **** thisEvtTarget/domEvent DOES NOT EXIST!!! ****");
		return JNI_FALSE;
	}

	PRBool boolRet=PR_FALSE;
	nsresult rv;
	if(IS_EQT){
		JREX_LOGLN("DispatchEvent()--> **** IN EVT Q THREAD ****")
		rv =thisEvtTarget->DispatchEvent(domEvent,&boolRet);
	}else{
		//we can't use sync disptach as it leads to deadloack
		rv=ExecInEventQDOM(thisEvtTarget, JREX_DISPATCH_EVENT, domEvent, PR_FALSE, HandleJRexEventTargetEvent, DestroyJRexEventTargetEvent, nsnull);
		PRBool boolRet=NS_SUCCEEDED(rv);
		JREX_LOGLN("DispatchEvent()--> **** ExecInEventQDOM rv<"<<rv<<"> boolRet<"<<boolRet<<"> ****")
	}
	if(NS_FAILED(rv)){
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){//Should be EVENT but mozilla raises DOM
			JREX_LOGLN("DispatchEvent()--> **** DispatchEvent DOM EVENT ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowEventException(env, rv);
		}else{
			JREX_LOGLN("DispatchEvent()--> **** DispatchEvent NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** DispatchEvent Failed ****",rv);
		}
		return JNI_FALSE;
	}
	return boolRet==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexEventTargetImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexEventTargetImpl_Finalize
  (JNIEnv * env, jobject jevtTarget){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMEventTarget* thisEvtTarget=(nsIDOMEventTarget*)NS_INT32_TO_PTR(env->GetIntField(jevtTarget, JRexDOMGlobals::evtTargetPeerID));
	JREX_LOGLN("JRexEventTargetImpl Finalize()--> **** thisEvtTarget <"<<thisEvtTarget<<"> ****")
	if(IS_NULL(thisEvtTarget)){
		JREX_LOGLN("JRexEventTargetImpl Finalize()--> **** thisEvtTarget DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisEvtTarget)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexEventTargetEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexEventTargetEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMEventTarget> det(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_NODE:
		{
			JREX_LOGLN("HandleJRexEventTargetEvent JREX_GET_NODE EVENT!!!****")
			return (void*)JRexEventTargetImpl_GetNodeInternal(nsnull, det.get());
		}
		case JREX_ADD_EVT_LISTENER:
		{
			JREX_LOGLN("HandleJRexEventTargetEvent JREX_ADD_EVT_LISTENER EVENT!!!****")
			JRexEventTargetParam* parm = NS_REINTERPRET_CAST(JRexEventTargetParam*, event->eventData);
			return (void*)JRexEventTargetImpl_AddEventListenerInternal(nsnull, det.get(),parm->type,parm->jeventLis,parm->useCapture);
		}
		case JREX_REMOVE_EVT_LISTENER:
		{
			JREX_LOGLN("HandleJRexEventTargetEvent JREX_REMOVE_EVT_LISTENER EVENT!!!****")
			JRexEventTargetParam* parm = NS_REINTERPRET_CAST(JRexEventTargetParam*, event->eventData);
			return (void*)JRexEventTargetImpl_RemoveEventListenerInternal(nsnull, det.get(),parm->type,(nsIDOMEventListener*)parm->jeventLis,parm->useCapture);
		}
		case JREX_DISPATCH_EVENT:
		{
			JREX_LOGLN("HandleJRexEventTargetEvent JREX_DISPATCH_EVENT EVENT!!!****")
			nsIDOMEvent* domEvent = NS_REINTERPRET_CAST(nsIDOMEvent*, event->eventData);
			JREX_LOGLN("HandleJRexEventTargetEvent()--> **** GOT  thisEvtTarget<"<<det<<"> domEvent<"<<domEvent<<"> ****")
			PRBool boolRet=PR_FALSE;
			nsresult rv =det->DispatchEvent(domEvent,&boolRet);
								JREX_LOGLN("HandleJRexEventTargetEvent()--> **** DispatchEvent rv<"<<rv<<"> ****")
			return (void*)boolRet;
			break;
		}
		default:
		{
			JREX_LOGLN("HandleJRexEventTargetEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexEventTargetEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexEventTargetEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexEventTargetEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData &&
			(event->eventType==JREX_ADD_EVT_LISTENER
			|| event->eventType==JREX_REMOVE_EVT_LISTENER)){
			JRexEventTargetParam* param = NS_REINTERPRET_CAST(JRexEventTargetParam*, event->eventData);
			delete param;
	}
	delete event;
}
