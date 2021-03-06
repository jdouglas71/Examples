
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


#include "org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLUListElement
enum JRexHTMLUListElementEventTypes{JREX_GET_TYPE=0U,
									JREX_SET_TYPE,
									JREX_GET_COMPACT,
									JREX_SET_COMPACT};

static void* PR_CALLBACK HandleJRexHTMLUListElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLUListElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl
 * Method:    GetCompact
 * Signature: ()Z;
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl_GetCompact
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLUListElement, GetCompact, JREX_GET_COMPACT, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl
 * Method:    SetCompact
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl_SetCompact
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLUListElement, SetCompact, JREX_SET_COMPACT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl_GetType
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLUListElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl
 * Method:    SetType
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl_SetType
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLUListElement, SetType, JREX_SET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLUListElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLUListElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLUListElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_COMPACT:
		{
			JREX_LOGLN("HandleJRexHTMLUListElementEvent JREX_GET_COMPACT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetCompact, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COMPACT:
		{
			JREX_LOGLN("HandleJRexHTMLUListElementEvent JREX_SET_COMPACT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetCompact, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLUListElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLUListElementEvent JREX_SET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetType, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLUListElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLUListElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLUListElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLUListElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
