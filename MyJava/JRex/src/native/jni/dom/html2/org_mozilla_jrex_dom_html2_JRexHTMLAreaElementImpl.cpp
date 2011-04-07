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


#include "org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLAreaElement
enum JRexHTMLAreaElementEventTypes{	JREX_GET_ACCESS_KEY=0U,
									JREX_SET_ACCESS_KEY,
									JREX_GET_ALT,
									JREX_SET_ALT,
									JREX_GET_COORDS,
									JREX_SET_COORDS,
									JREX_GET_HREF,
									JREX_SET_HREF,
									JREX_GET_NO_HREF,
									JREX_SET_NO_HREF,
									JREX_GET_SHAPE,
									JREX_SET_SHAPE,
									JREX_GET_TAB_INDEX,
									JREX_SET_TAB_INDEX,
									JREX_GET_TARGET,
									JREX_SET_TARGET};

static void* PR_CALLBACK HandleJRexHTMLAreaElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLAreaElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetAccessKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetAccessKey
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetAccessKey, JREX_GET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetAccessKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetAccessKey
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetAccessKey, JREX_SET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetAlt
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetAlt
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetAlt, JREX_GET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetAlt
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetAlt
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetAlt, JREX_SET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetCoords
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetCoords
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetCoords, JREX_GET_COORDS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetCoords
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetCoords
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetCoords, JREX_SET_COORDS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetHref
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetHref
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetHref, JREX_GET_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetHref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetHref
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetHref, JREX_SET_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetNoHref
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetNoHref
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLAreaElement, GetNoHref, JREX_GET_NO_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetNoHref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetNoHref
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetNoHref, JREX_SET_NO_HREF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetShape
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetShape
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetShape, JREX_GET_SHAPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetShape
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetShape
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetShape, JREX_SET_SHAPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetTabIndex
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLAreaElement,PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetTabIndex
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLAreaElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    GetTarget
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_GetTarget
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAreaElement, GetTarget, JREX_GET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl
 * Method:    SetTarget
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl_SetTarget
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAreaElement, SetTarget, JREX_SET_TARGET, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLAreaElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLAreaElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLAreaElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_ACCESS_KEY EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccessKey, jrv)
			return (void*)jrv;
		}
        case JREX_SET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_ACCESS_KEY EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccessKey, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_ALT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlt, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_ALT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlt, jrv)
			return (void*)jrv;

		}
		case JREX_GET_COORDS:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_COORDS EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCoords, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COORDS:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_COORDS EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCoords, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_HREF EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHref, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_HREF EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHref, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NO_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_NO_HREF EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetNoHref, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NO_HREF:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_NO_HREF EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetNoHref, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SHAPE:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_SHAPE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetShape, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SHAPE:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_SHAPE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetShape, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_TAB_INDEX EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_TAB_INDEX EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_GET_TARGET EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetTarget, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TARGET:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent JREX_SET_TARGET EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetTarget, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLAreaElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLAreaElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLAreaElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLAreaElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
