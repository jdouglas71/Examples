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


#include "org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLAnchorElement
enum JRexHTMLAnchorElementEventTypes{JREX_GET_ACCESS_KEY=0U,
									JREX_SET_ACCESS_KEY,
									JREX_GET_CHARSET,
									JREX_SET_CHARSET,
									JREX_GET_COORDS,
									JREX_SET_COORDS,
									JREX_GET_HREF,
									JREX_SET_HREF,
									JREX_GET_HREFLANG,
									JREX_SET_HREFLANG,
									JREX_GET_NAME,
									JREX_SET_NAME,
									JREX_GET_REL,
									JREX_SET_REL,
									JREX_GET_REV,
									JREX_SET_REV,
									JREX_GET_SHAPE,
									JREX_SET_SHAPE,
									JREX_GET_TAB_INDEX,
									JREX_SET_TAB_INDEX,
									JREX_GET_TARGET,
									JREX_SET_TARGET,
									JREX_GET_TYPE,
									JREX_SET_TYPE,
									JREX_BLUR,
									JREX_FOCUS };

static void* PR_CALLBACK HandleJRexHTMLAnchorElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLAnchorElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetAccessKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetAccessKey
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetAccessKey, JREX_GET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetAccessKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetAccessKey
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetAccessKey, JREX_SET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetCharset
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetCharset
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetCharset, JREX_GET_CHARSET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetCharset
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetCharset
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetCharset, JREX_SET_CHARSET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetCoords
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetCoords
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetCoords, JREX_GET_COORDS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetCoords
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetCoords
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetCoords, JREX_SET_COORDS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetHref
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetHref
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetHref, JREX_GET_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetHref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetHref
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetHref, JREX_SET_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetHreflang
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetHreflang
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetHreflang, JREX_GET_HREFLANG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetHreflang
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetHreflang
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetHreflang, JREX_SET_HREFLANG, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetName
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetName
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetRel
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetRel
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetRel, JREX_GET_REL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetRel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetRel
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetRel, JREX_SET_REL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetRev
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetRev
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetRev, JREX_GET_REV, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetRev
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetRev
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetRev, JREX_SET_REV, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetShape
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetShape
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetShape, JREX_GET_SHAPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetShape
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetShape
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetShape, JREX_SET_SHAPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetTabIndex
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLAnchorElement,PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetTabIndex
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLAnchorElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetTarget
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetTarget
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetTarget, JREX_GET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetTarget
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetTarget
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetTarget, JREX_SET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_GetType
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAnchorElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    SetType
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_SetType
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAnchorElement, SetType, JREX_SET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    Blur
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_Blur
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLAnchorElement, Blur, JREX_BLUR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl
 * Method:    Focus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl_Focus
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLAnchorElement, Focus, JREX_FOCUS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLAnchorElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLAnchorElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLAnchorElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetType, jrv)
			return (void*)jrv;
		}

		case JREX_GET_CHARSET:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_CHARSET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCharset, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CHARSET:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_CHARSET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCharset, jrv)
			return (void*)jrv;

		}
		case JREX_GET_COORDS:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_COORDS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCoords, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COORDS:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_COORDS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCoords, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_HREF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHref, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_HREF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHref, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HREFLANG:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_HREFLANG EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHreflang, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HREFLANG:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_HREFLANG EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHreflang, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_REL:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_REL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetRel, jrv)
			return (void*)jrv;
		}
		case JREX_SET_REL:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_REL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetRel, jrv)
			return (void*)jrv;
		}
		case JREX_GET_REV:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_REV EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetRev, jrv)
			return (void*)jrv;
		}
		case JREX_SET_REV:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_REV EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetRev, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SHAPE:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_SHAPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetShape, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SHAPE:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_SHAPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetShape, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_TARGET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetTarget, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_TARGET EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetTarget, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccessKey, jrv)
			return (void*)jrv;
		}
        case JREX_SET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccessKey, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_GET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_SET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;
		}

		case JREX_BLUR:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_BLUR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Blur, jrv)
			return (void*)jrv;

		}
		case JREX_FOCUS:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent JREX_FOCUS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Focus, jrv)
			return (void*)jrv;

		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLAnchorElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLAnchorElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLAnchorElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLAnchorElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
