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


#include "org_mozilla_jrex_dom_html2_JRexHTMLElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLElement
enum JRexHTMLElementEventTypes{	JREX_GET_ID=0U,
								JREX_SET_ID,
								JREX_GET_TITLE,
								JREX_SET_TITLE,
								JREX_GET_LANG,
								JREX_SET_LANG,
								JREX_GET_DIR,
								JREX_SET_DIR,
								JREX_GET_CLASS,
								JREX_SET_CLASS};

static void* PR_CALLBACK HandleJRexHTMLElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    GetId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_GetId
  (JNIEnv * env, jobject jhtmlEle){
  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLElement, GetId, JREX_GET_ID, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    SetId
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_SetId
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLElement, SetId, JREX_SET_ID, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    GetTitle
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_GetTitle
  (JNIEnv * env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLElement, GetTitle, JREX_GET_TITLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    SetTitle
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_SetTitle
  (JNIEnv * env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLElement, SetTitle, JREX_SET_TITLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    GetLang
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_GetLang
  (JNIEnv * env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLElement, GetLang, JREX_GET_LANG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    SetLang
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_SetLang
  (JNIEnv * env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLElement, SetLang, JREX_SET_LANG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    GetDir
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_GetDir
  (JNIEnv * env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLElement, GetDir, JREX_GET_DIR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}



/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    SetDir
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_SetDir
  (JNIEnv * env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLElement, SetDir, JREX_SET_DIR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    GetClassName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_GetClassName
  (JNIEnv * env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLElement, GetClassName, JREX_GET_CLASS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}



/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLElementImpl
 * Method:    SetClassName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLElementImpl_SetClassName
  (JNIEnv * env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLElement, SetClassName, JREX_SET_CLASS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ID:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_GET_ID EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetId, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ID:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_SET_ID EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetId, jrv)
			return (void*)jrv;

		}
		case JREX_GET_TITLE:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_GET_TITLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetTitle, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TITLE:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_SET_TITLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetTitle, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LANG:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_GET_LANG EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLang, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LANG:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_SET_LANG EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLang, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DIR:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_GET_DIR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetDir, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DIR:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_SET_DIR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetDir, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CLASS:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_GET_CLASS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetClassName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CLASS:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent JREX_SET_CLASS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetClassName, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
