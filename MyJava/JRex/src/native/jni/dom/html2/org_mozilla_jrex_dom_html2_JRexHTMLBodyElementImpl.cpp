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


#include "org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLBodyElement
enum JRexHTMLBodyElementEventTypes{	JREX_GET_ALINK=0U,
									JREX_SET_ALINK,
									JREX_GET_BG,
									JREX_SET_BG,
									JREX_GET_BG_CLR,
									JREX_SET_BG_CLR,
									JREX_GET_LINK,
									JREX_SET_LINK,
									JREX_GET_TEXT,
									JREX_SET_TEXT,
									JREX_GET_VLINK,
									JREX_SET_VLINK};

static void* PR_CALLBACK HandleJRexHTMLBodyElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLBodyElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetALink
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetALink
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetALink, JREX_GET_ALINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetALink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetALink
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetALink, JREX_SET_ALINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetBackground
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetBackground
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetBackground, JREX_GET_BG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetBackground
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetBackground
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetBackground, JREX_SET_BG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetBgColor
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetBgColor
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetBgColor, JREX_GET_BG_CLR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetBgColor
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetBgColor
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetBgColor, JREX_SET_BG_CLR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetLink
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetLink
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetLink, JREX_GET_LINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetLink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetLink
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetLink, JREX_SET_LINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetText
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetText
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetText, JREX_GET_TEXT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetText
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetText
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetText, JREX_SET_TEXT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    GetVLink
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_GetVLink
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLBodyElement, GetVLink, JREX_GET_VLINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl
 * Method:    SetVLink
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl_SetVLink
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBodyElement, SetVLink, JREX_SET_VLINK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLBodyElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLBodyElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLBodyElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ALINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_ALINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetALink, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_ALINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetALink, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BG:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_BG EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBackground, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BG:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_BG EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBackground, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BG_CLR:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_BG_CLR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BG_CLR:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_BG_CLR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_LINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLink, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_LINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLink, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TEXT:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_TEXT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetText, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TEXT:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_TEXT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetText, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VLINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_GET_VLINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetVLink, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VLINK:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent JREX_SET_VLINK EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetVLink, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLBodyElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLBodyElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLBodyElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLBodyElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
