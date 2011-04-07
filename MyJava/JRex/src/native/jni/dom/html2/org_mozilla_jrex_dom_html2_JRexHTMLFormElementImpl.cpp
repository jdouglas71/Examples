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


#include "org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLFormElement
enum JRexHTMLFormElementEventTypes{	JREX_GET_ELES=0U,
									JREX_GET_LENGTH,
									JREX_GET_NAME,
									JREX_SET_NAME,
									JREX_GET_ACCEPT_CHARSET,
									JREX_SET_ACCEPT_CHARSET,
									JREX_GET_ACTION,
									JREX_SET_ACTION,
									JREX_GET_ENCTYPE,
									JREX_SET_ENCTYPE,
									JREX_GET_METHOD,
									JREX_SET_METHOD,
									JREX_GET_TARGET,
									JREX_SET_TARGET,
									JREX_SUBMIT,
									JREX_RESET};

static void* PR_CALLBACK HandleJRexHTMLFormElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLFormElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetElements
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetElements
  (JNIEnv *env, jobject jformEle){
	GET_DOM_HTML_COL_JNI(env , jformEle, HTMLFormElement, GetElements, JREX_GET_ELES, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetLength
  (JNIEnv *env, jobject jformEle){
	GET_DOM_INT_JNI(env , jformEle, HTMLFormElement, PRInt32, GetLength, JREX_GET_LENGTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetName
  (JNIEnv *env, jobject jformEle){
	  GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetName
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetAcceptCharset
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetAcceptCharset
  (JNIEnv *env, jobject jformEle){
	GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetAcceptCharset, JREX_GET_ACCEPT_CHARSET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetAcceptCharset
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetAcceptCharset
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetAcceptCharset, JREX_SET_ACCEPT_CHARSET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetAction
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetAction
  (JNIEnv *env, jobject jformEle){
	GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetAction, JREX_GET_ACTION, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetAction
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetAction
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetAction, JREX_SET_ACTION, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetEnctype
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetEnctype
  (JNIEnv *env, jobject jformEle){
	GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetEnctype, JREX_GET_ENCTYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetEnctype
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetEnctype
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetEnctype, JREX_SET_ENCTYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetMethod
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetMethod
  (JNIEnv *env, jobject jformEle){
	GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetMethod, JREX_GET_METHOD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetMethod
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetMethod
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetMethod, JREX_SET_METHOD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    GetTarget
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_GetTarget
  (JNIEnv *env, jobject jformEle){
	GET_DOM_STRING_JNI(env , jformEle, HTMLFormElement, GetTarget, JREX_GET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    SetTarget
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_SetTarget
  (JNIEnv *env, jobject jformEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jformEle, jvalue, HTMLFormElement, SetTarget, JREX_SET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    Submit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_Submit
  (JNIEnv *env, jobject jformEle){
	CALL_DOM_JNI(env , jformEle, HTMLFormElement, Submit, JREX_SUBMIT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl
 * Method:    Reset
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl_Reset
  (JNIEnv *env, jobject jformEle){
	CALL_DOM_JNI(env , jformEle, HTMLFormElement, Reset, JREX_RESET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLFormElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLFormElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLFormElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ELES:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_ELES EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetElements, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_LENGTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetLength, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ACCEPT_CHARSET:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_ACCEPT_CHARSET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAcceptCharset, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ACCEPT_CHARSET:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_ACCEPT_CHARSET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAcceptCharset, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ACTION:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_ACTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAction, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ACTION:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_ACTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAction, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ENCTYPE:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_ENCTYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetEnctype, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ENCTYPE:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_ENCTYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetEnctype, jrv)
			return (void*)jrv;

		}
		case JREX_GET_METHOD:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_METHOD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetMethod, jrv)
			return (void*)jrv;
		}
		case JREX_SET_METHOD:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_METHOD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetMethod, jrv)
			return (void*)jrv;

		}
		case JREX_GET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_GET_TARGET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetTarget, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SET_TARGET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetTarget, jrv)
			return (void*)jrv;

		}
		case JREX_SUBMIT:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_SUBMIT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Submit, jrv)
			return (void*)jrv;

		}
		case JREX_RESET:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent JREX_RESET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Reset, jrv)
			return (void*)jrv;

		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLFormElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLFormElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLFormElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLFormElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
