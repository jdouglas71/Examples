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


#include "org_mozilla_jrex_dom_views_JRexDocumentViewImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDocView
enum JRexDocViewEventTypes{JREX_GET_DEF_VIEW=0U};

static void* PR_CALLBACK HandleJRexDocViewEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocViewEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexDocumentViewImpl_GetDefaultViewInternal(JNIEnv *env, nsIDOMDocumentView* view){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (view){
		nsCOMPtr<nsIDOMAbstractView> tmpView;
		rv = view->GetDefaultView(getter_AddRefs(tmpView));
		JREX_LOGLN("JRexDocumentViewImpl_GetDefaultViewInternal()--> **** GetDefaultView rv<"<<rv<<"> ****")
		if(tmpView)
			jval=JRexDOMGlobals::CreateAbstractView(env, tmpView.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_views_JRexDocumentViewImpl
 * Method:    GetDefaultView
 * Signature: ()Lorg/w3c/dom/views/AbstractView;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_views_JRexDocumentViewImpl_GetDefaultView
  (JNIEnv *env, jobject jview){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentView* thisView=(nsIDOMDocumentView*)NS_INT32_TO_PTR(env->GetIntField(jview, JRexDOMGlobals::documentViewPeerID));
	JREX_LOGLN("GetDefaultView()--> **** thisView <"<<thisView<<"> ****")
	if(IS_NULL(thisView)){
		ThrowJRexException(env, "GetDefaultView()--> **** thisView DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDefaultView()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentViewImpl_GetDefaultViewInternal(env, thisView);
	}else{
		nsresult rv=ExecInEventQDOM(thisView, JREX_GET_DEF_VIEW, nsnull, PR_TRUE, HandleJRexDocViewEvent, DestroyJRexDocViewEvent, (void**)&jrv);
		JREX_LOGLN("GetDefaultView()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDefaultView()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDefaultView()--> **** GetDefaultView NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDefaultView Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_views_JRexDocumentViewImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_views_JRexDocumentViewImpl_Finalize
  (JNIEnv *env, jobject jview){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMDocumentView* thisView=(nsIDOMDocumentView*)NS_INT32_TO_PTR(env->GetIntField(jview, JRexDOMGlobals::documentViewPeerID));
	JREX_LOGLN("JRexDocumentViewImpl_ Finalize()--> **** thisView <"<<thisView<<"> ****")
	if(IS_NULL(thisView)){
		JREX_LOGLN("JRexDocumentViewImpl_ Finalize()--> **** thisView DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisView)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexDocViewEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocViewEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_DEF_VIEW:
		{
			JREX_LOGLN("HandleJRexDocViewEvent JREX_GET_DEF_VIEW EVENT!!!****")
			nsCOMPtr<nsIDOMDocumentView> view(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexDocumentViewImpl_GetDefaultViewInternal(nsnull, view.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocViewEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocViewEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocViewEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocViewEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
