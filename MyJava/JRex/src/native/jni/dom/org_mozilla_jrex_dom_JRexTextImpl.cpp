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


#include "org_mozilla_jrex_dom_JRexTextImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexText
enum JRexTextEventTypes{JREX_SPLIT_TEXT=0U};

static void* PR_CALLBACK HandleJRexTextEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexTextEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV* JRexTextImpl_SplitTextInternal(JNIEnv *env, nsIDOMText* text, PRUint32 offset){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (text){
		nsCOMPtr<nsIDOMText> tmpText;
		rv = text->SplitText(offset, getter_AddRefs(tmpText));
		JREX_LOGLN("JRexTextImpl_SplitTextInternal()--> **** SplitText rv<"<<rv<<"> ****")
		if(tmpText)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpText.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexTextImpl
 * Method:    SplitText
 * Signature: (I)Lorg/w3c/dom/Text;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexTextImpl_SplitText
  (JNIEnv *env, jobject jtext, jint joffset){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMText* thisText=(nsIDOMText*)NS_INT32_TO_PTR(env->GetIntField(jtext, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SplitText()--> **** thisText <"<<thisText<<"> ****")
	if(IS_NULL(thisText)){
		ThrowJRexException(env, "SplitText()--> **** thisText DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SplitText()--> **** IN EVT Q THREAD ****")
		jrv=JRexTextImpl_SplitTextInternal(env, thisText, (PRUint32)joffset);
	}else{
		nsresult rv=ExecInEventQDOM(thisText, JREX_SPLIT_TEXT, (void*)joffset, PR_TRUE, HandleJRexTextEvent, DestroyJRexTextEvent, (void**)&jrv);
		JREX_LOGLN("SplitText()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SplitText()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SplitText()--> **** SplitText DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SplitText()--> **** SplitText NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SplitText Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

void* PR_CALLBACK HandleJRexTextEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexTextEvent()--> **** target <"<<event->target<<"> ****")
	switch(event->eventType){
		case JREX_SPLIT_TEXT:
		{
			JREX_LOGLN("HandleJRexTextEvent JREX_SPLIT_TEXT EVENT!!!****")
			nsCOMPtr<nsIDOMText> text(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
			return (void*)JRexTextImpl_SplitTextInternal(nsnull, text.get(), (PRUint32)event->eventData);
		}
		default:
		{
			JREX_LOGLN("HandleJRexTextEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexTextEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexTextEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexTextEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

