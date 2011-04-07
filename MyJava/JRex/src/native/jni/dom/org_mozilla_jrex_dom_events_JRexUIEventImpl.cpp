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


#include "org_mozilla_jrex_dom_events_JRexUIEventImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexUIEvent
enum JRexUIEventEventTypes{JREX_GET_VIEW=0U};

static void* PR_CALLBACK HandleJRexUIEventEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexUIEventEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexUIEventImpl_GetViewInternal(JNIEnv *env, nsIDOMUIEvent* dUIEvent){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (dUIEvent){
		nsCOMPtr<nsIDOMAbstractView> tmpView;
		rv = dUIEvent->GetView(getter_AddRefs(tmpView));
		JREX_LOGLN("JRexUIEventImpl_GetViewInternal()--> **** GetView rv<"<<rv<<"> ****")
		if(tmpView)
			jval=JRexDOMGlobals::CreateAbstractView(env, tmpView.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_events_JRexUIEventImpl
 * Method:    GetView
 * Signature: ()Lorg/w3c/dom/views/AbstractView;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexUIEventImpl_GetView
  (JNIEnv *env, jobject jdomUIEvent){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMUIEvent* thisUIEvent=(nsIDOMUIEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomUIEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetView()--> **** thisUIEvent <"<<thisUIEvent<<"> ****")
	if(IS_NULL(thisUIEvent)){
		ThrowJRexException(env, "GetView()--> **** thisUIEvent DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetView()--> **** IN EVT Q THREAD ****")
		jrv=JRexUIEventImpl_GetViewInternal(env, thisUIEvent);
	}else{
		nsresult rv=ExecInEventQDOM(thisUIEvent, JREX_GET_VIEW, nsnull, PR_TRUE,
						HandleJRexUIEventEvent, DestroyJRexUIEventEvent, (void**)&jrv);
		JREX_LOGLN("GetView()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetView()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetView()--> **** GetView NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetView Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexUIEventImpl
 * Method:    GetDetail
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_events_JRexUIEventImpl_GetDetail
  (JNIEnv *env, jobject jdomUIEvent){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMUIEvent* thisUIEvent=(nsIDOMUIEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomUIEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("GetDetail()--> **** thisUIEvent <"<<thisUIEvent<<"> ****")
	if(IS_NULL(thisUIEvent)){
		ThrowJRexException(env, "GetDetail()--> **** thisUIEvent DOES NOT EXIST!!! ****",0);
		return 0;
	}

	PRInt32 retVal=0;
	nsresult rv = thisUIEvent->GetDetail(&retVal);
	JREX_LOGLN("GetDetail()--> **** GetDetail rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetDetail()--> **** GetDetail NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetDetail Failed ****",rv);
		return 0;
	}
	return (jint)retVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexUIEventImpl
 * Method:    InitUIEvent
 * Signature: (Ljava/lang/String;ZZLorg/w3c/dom/views/AbstractView;I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexUIEventImpl_InitUIEvent
  (JNIEnv *env, jobject jdomUIEvent, jstring jtype, jboolean jcanBubble,
  							jboolean jcanCancel, jobject jviewArg, jint jdetail){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMUIEvent* thisUIEvent=(nsIDOMUIEvent*)NS_INT32_TO_PTR(env->GetIntField(jdomUIEvent, JRexDOMGlobals::domEventPeerID));
	JREX_LOGLN("InitUIEvent()--> **** thisUIEvent <"<<thisUIEvent<<"> ****")
	if(IS_NULL(thisUIEvent) || IS_NULL(jtype)){
		ThrowJRexException(env, "InitUIEvent()--> **** thisUIEvent/jtype DOES NOT EXIST!!! ****",0);
		return;
	}
	nsIDOMAbstractView* view=nsnull;
	if(NOT_NULL(jviewArg))
		view=(nsIDOMAbstractView*)NS_INT32_TO_PTR(env->GetIntField(jviewArg, JRexDOMGlobals::abstractViewPeerID));
	JREX_LOGLN("InitUIEvent()--> **** view <"<<view<<"> ****")

	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);
	nsEmbedString ttype(type);

	nsresult rv = thisUIEvent->InitUIEvent(ttype,
					(jcanBubble==JNI_TRUE?PR_TRUE:PR_FALSE), (jcanCancel==JNI_TRUE?PR_TRUE:PR_FALSE),
					view, (PRInt32)jdetail);
	JREX_LOGLN("InitUIEvent()--> **** InitUIEvent rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("InitUIEvent()--> **** InitUIEvent NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** InitUIEvent Failed ****",rv);
	}
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexUIEventEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexUIEventEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_VIEW:
		{
			JREX_LOGLN("HandleJRexUIEventEvent JREX_GET_VIEW EVENT!!!****")
			nsCOMPtr<nsIDOMUIEvent> uie(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexUIEventImpl_GetViewInternal(nsnull, uie.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexUIEventEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexUIEventEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexUIEventEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexUIEventEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}


