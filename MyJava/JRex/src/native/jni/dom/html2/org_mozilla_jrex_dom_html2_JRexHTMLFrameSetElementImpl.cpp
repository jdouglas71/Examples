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


#include "org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLFrameSetElement
enum JRexHTMLFrameSetElementEventTypes{	JREX_GET_COLS=0U,
										JREX_SET_COLS,
										JREX_GET_ROWS,
										JREX_SET_ROWS};

static void* PR_CALLBACK HandleJRexHTMLFrameSetElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLFrameSetElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl
 * Method:    GetCols
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl_GetCols
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameSetElement, GetCols, JREX_GET_COLS, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl
 * Method:    SetCols
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl_SetCols
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameSetElement, SetCols, JREX_SET_COLS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl
 * Method:    GetRows
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl_GetRows
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameSetElement, GetRows, JREX_GET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl
 * Method:    SetRows
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl_SetRows
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameSetElement, SetRows, JREX_SET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLFrameSetElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLFrameSetElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_COLS:
		{
			JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent JREX_GET_COLS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCols, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COLS:
		{
			JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent JREX_SET_COLS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCols, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent JREX_GET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetRows, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent JREX_SET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetRows, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLFrameSetElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLFrameSetElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLFrameSetElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

