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


#include "org_mozilla_jrex_dom_events_JRexDocumentEventImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDocumentEvent
enum JRexDocumentEventEventTypes{JREX_CREATE_EVENT=0U};

static void* PR_CALLBACK HandleJRexDocumentEventEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocumentEventEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentEventImpl_CreateEventInternal(JNIEnv *env, nsIDOMDocumentEvent* docEvent, PRUnichar* type){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docEvent){
		nsCOMPtr<nsIDOMEvent> tmpEvent;
		nsEmbedString ttype(type);
		rv = docEvent->CreateEvent(ttype, getter_AddRefs(tmpEvent));
		JREX_LOGLN("JRexDocumentEventImpl_CreateEventInternal()--> **** CreateEvent rv<"<<rv<<"> ****")
		if(tmpEvent)
			jval=JRexDOMGlobals::CreateDOMEvent(env, tmpEvent.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_events_JRexDocumentEventImpl
 * Method:    CreateEvent
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/events/Event;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_events_JRexDocumentEventImpl_CreateEvent
  (JNIEnv *env, jobject jdocEvent, jstring jtype){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentEvent* thisDocEvent=(nsIDOMDocumentEvent*)NS_INT32_TO_PTR(env->GetIntField(jdocEvent, JRexDOMGlobals::docEventPeerID));
	JREX_LOGLN("CreateEvent()--> **** thisDocEvent <"<<thisDocEvent<<"> ****")
	if(IS_NULL(thisDocEvent) || IS_NULL(jtype)){
		JREX_LOGLN("CreateEvent()--> **** thisDocEvent/jtype DOES NOT EXIST!!! ****");
		return NULL;
	}

	PRUnichar* type=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtype, type);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateEvent()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentEventImpl_CreateEventInternal(env, thisDocEvent, type);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocEvent, JREX_CREATE_EVENT, (void*)type, PR_TRUE,
						HandleJRexDocumentEventEvent, DestroyJRexDocumentEventEvent, (void**)&jrv);
		JREX_LOGLN("CreateEvent()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateEvent()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateEvent()--> **** CreateEvent DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateEvent()--> **** CreateEvent NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateEvent Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_events_JRexDocumentEventImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_events_JRexDocumentEventImpl_Finalize
  (JNIEnv *env, jobject jdocEvent){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMDocumentEvent* thisDocEvent=(nsIDOMDocumentEvent*)NS_INT32_TO_PTR(env->GetIntField(jdocEvent, JRexDOMGlobals::docEventPeerID));
	JREX_LOGLN("JRexDocumentEventImpl Finalize()--> **** thisDocEvent <"<<thisDocEvent<<"> ****")
	if(IS_NULL(thisDocEvent)){
		JREX_LOGLN("JRexDocumentEventImpl Finalize()--> **** thisDocEvent DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisDocEvent)
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexDocumentEventEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocumentEventEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_CREATE_EVENT:
		{
			JREX_LOGLN("HandleJRexDocumentEventEvent JREX_CREATE_EVENT EVENT!!!****")
			nsCOMPtr<nsIDOMDocumentEvent> dde(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			PRUnichar* type = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentEventImpl_CreateEventInternal(nsnull, dde.get(),type);
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocumentEventEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocumentEventEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocumentEventEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocumentEventEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
