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


#include "org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLOptGroupElement
enum JRexHTMLOptGroupElementEventTypes{	JREX_GET_DISABLED=0U,
										JREX_SET_DISABLED,
										JREX_GET_LABEL,
										JREX_SET_LABEL };

static void* PR_CALLBACK HandleJRexHTMLOptGroupElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLOptGroupElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl_GetDisabled
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLOptGroupElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl_SetDisabled
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLOptGroupElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl
 * Method:    GetLabel
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl_GetLabel
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLOptGroupElement, GetLabel, JREX_GET_LABEL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl
 * Method:    SetLabel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl_SetLabel
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLOptGroupElement, SetLabel, JREX_SET_LABEL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLOptGroupElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLOptGroupElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){

		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent JREX_SET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LABEL:
		{
			JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent JREX_GET_LABEL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLabel, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LABEL:
		{
			JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent JREX_SET_LABEL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLabel, jrv)
			return (void*)jrv;
		}

		default:
		{
			JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLOptGroupElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLOptGroupElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLOptGroupElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
