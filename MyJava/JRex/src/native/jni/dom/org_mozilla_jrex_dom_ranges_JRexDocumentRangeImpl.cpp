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


#include "org_mozilla_jrex_dom_ranges_JRexDocumentRangeImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDocRange
enum JRexDocRangeEventTypes{JREX_CREATE_RANGE=0U};

static void* PR_CALLBACK HandleJRexDocRangeEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocRangeEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexDocumentRangeImpl_CreateRangeInternal(JNIEnv *env, nsIDOMDocumentRange* docRange){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docRange){
		nsCOMPtr<nsIDOMRange> tmpRange;
		rv = docRange->CreateRange(getter_AddRefs(tmpRange));
		JREX_LOGLN("JRexDocumentRangeImpl_CreateRangeInternal()--> **** CreateRange rv<"<<rv<<"> ****")
		if(tmpRange)
			jval=JRexDOMGlobals::CreateRange(env, tmpRange.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDocumentRangeImpl
 * Method:    CreateRange
 * Signature: ()Lorg/w3c/dom/ranges/Range;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDocumentRangeImpl_CreateRange
  (JNIEnv * env, jobject jdocRangeImpl){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentRange* thisDocRange=(nsIDOMDocumentRange*)NS_INT32_TO_PTR(env->GetIntField(jdocRangeImpl, JRexDOMGlobals::docRangePeerID));
	JREX_LOGLN("CreateRange()--> **** thisDocRange <"<<thisDocRange<<"> ****")
	if(IS_NULL(thisDocRange)){
		ThrowJRexException(env, "CreateRange()--> **** thisDocRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateRange()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentRangeImpl_CreateRangeInternal(env, thisDocRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisDocRange, JREX_CREATE_RANGE, nsnull, PR_TRUE, HandleJRexDocRangeEvent, DestroyJRexDocRangeEvent, (void**)&jrv);
		JREX_LOGLN("CreateRange()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateRange()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateRange()--> **** CreateRange DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("CreateRange()--> **** CreateRange RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("CreateRange()--> **** CreateRange NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateRange Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentRangeImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentRangeImpl_Finalize
  (JNIEnv * env, jobject jdocRangeImpl){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMDocumentRange* thisDocRange=(nsIDOMDocumentRange*)NS_INT32_TO_PTR(env->GetIntField(jdocRangeImpl, JRexDOMGlobals::docRangePeerID));
	JREX_LOGLN("JRexDocumentRangeImpl Finalize()--> **** thisDocRange <"<<thisDocRange<<"> ****")
	if(IS_NULL(thisDocRange)){
		ThrowJRexException(env, "JRexDocumentRangeImpl Finalize()--> **** thisDocRange DOES NOT EXIST!!! ****",0);
		return;
	}
	SAFE_RELEASE(thisDocRange)
	JREX_CATCH(env)
}

void* PR_CALLBACK HandleJRexDocRangeEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocRangeEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_CREATE_RANGE:
		{
			JREX_LOGLN("HandleJRexDocRangeEvent JREX_CREATE_RANGE EVENT!!!****")
			nsCOMPtr<nsIDOMDocumentRange> docRange(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexDocumentRangeImpl_CreateRangeInternal(nsnull, docRange.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocRangeEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocRangeEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocRangeEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocRangeEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
