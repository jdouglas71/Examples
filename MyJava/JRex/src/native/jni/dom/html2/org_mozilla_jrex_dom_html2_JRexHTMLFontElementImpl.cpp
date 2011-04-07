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


#include "org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLFontElement
enum JRexHTMLFontElementEventTypes{	JREX_GET_COLOR=0U,
									JREX_SET_COLOR,
									JREX_GET_FACE,
									JREX_SET_FACE,
									JREX_GET_SIZE,
									JREX_SET_SIZE};

static void* PR_CALLBACK HandleJRexHTMLFontElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLFontElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    GetColor
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_GetColor
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFontElement, GetColor, JREX_GET_COLOR, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    SetColor
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_SetColor
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFontElement, SetColor, JREX_SET_COLOR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    GetFace
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_GetFace
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFontElement, GetFace, JREX_GET_FACE, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    SetFace
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_SetFace
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFontElement, SetFace, JREX_SET_FACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    GetSize
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_GetSize
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFontElement, GetSize, JREX_GET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl
 * Method:    SetSize
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl_SetSize
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFontElement, SetSize, JREX_SET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLFontElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLFontElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLFontElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_COLOR:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_GET_COLOR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetColor, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COLOR:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_SET_COLOR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetColor, jrv)
			return (void*)jrv;
		}
		case JREX_GET_FACE:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_GET_FACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetFace, jrv)
			return (void*)jrv;
		}
		case JREX_SET_FACE:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_SET_FACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetFace, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_GET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetSize, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent JREX_SET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetSize, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLFontElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLFontElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLFontElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLFontElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
