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


#include "org_mozilla_jrex_dom_views_JRexAbstractViewImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexAbsView
enum JRexAbsViewEventTypes{JREX_GET_DOC=0U};

static void* PR_CALLBACK HandleJRexAbsViewEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexAbsViewEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexAbstractViewImpl_GetDocumentInternal(JNIEnv *env, nsIDOMAbstractView* view){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (view){
		nsCOMPtr<nsIDOMDocumentView> tmpView;
		rv = view->GetDocument(getter_AddRefs(tmpView));
		JREX_LOGLN("JRexAbstractViewImpl_GetDocumentInternal()--> **** GetDocument rv<"<<rv<<"> ****")
		if(tmpView)
			jval=JRexDOMGlobals::CreateDocumentView(env, tmpView.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_views_JRexAbstractViewImpl
 * Method:    GetDocument
 * Signature: ()Lorg/w3c/dom/views/DocumentView;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_views_JRexAbstractViewImpl_GetDocument
  (JNIEnv *env, jobject jview){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMAbstractView* thisView=(nsIDOMAbstractView*)NS_INT32_TO_PTR(env->GetIntField(jview, JRexDOMGlobals::abstractViewPeerID));
	JREX_LOGLN("GetDocument()--> **** thisView <"<<thisView<<"> ****")
	if(IS_NULL(thisView)){
		ThrowJRexException(env, "GetDocument()--> **** thisView DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocument()--> **** IN EVT Q THREAD ****")
		jrv=JRexAbstractViewImpl_GetDocumentInternal(env, thisView);
	}else{
		nsresult rv=ExecInEventQDOM(thisView, JREX_GET_DOC, nsnull, PR_TRUE, HandleJRexAbsViewEvent, DestroyJRexAbsViewEvent, (void**)&jrv);
		JREX_LOGLN("GetDocument()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocument()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocument()--> **** GetDocument NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocument Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_views_JRexAbstractViewImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_views_JRexAbstractViewImpl_Finalize
  (JNIEnv *env, jobject jview){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMAbstractView* thisView=(nsIDOMAbstractView*)NS_INT32_TO_PTR(env->GetIntField(jview, JRexDOMGlobals::abstractViewPeerID));
	JREX_LOGLN("JRexAbstractViewImpl Finalize()--> **** thisView <"<<thisView<<"> ****")
	if(IS_NULL(thisView)){
		JREX_LOGLN("JRexAbstractViewImpl Finalize()--> **** thisView DOES NOT EXIST!!! ****");
		return;
	}
	SAFE_RELEASE(thisView)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexAbsViewEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexAbsViewEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_GET_DOC:
		{
			JREX_LOGLN("HandleJRexAbsViewEvent JREX_GET_DOC EVENT!!!****")
			nsCOMPtr<nsIDOMAbstractView> view(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexAbstractViewImpl_GetDocumentInternal(nsnull, view.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexAbsViewEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexAbsViewEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexAbsViewEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexAbsViewEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
