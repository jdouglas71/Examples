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


#include "org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLBRElement
enum JRexHTMLBRElementEventTypes{	JREX_GET_CLEAR=0U,
									JREX_SET_CLEAR};

static void* PR_CALLBACK HandleJRexHTMLBRElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLBRElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl
 * Method:    GetClear
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl_GetClear
  (JNIEnv *env, jobject jhtmlEle){


}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl
 * Method:    SetClear
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl_SetClear
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLBRElement, SetClear, JREX_SET_CLEAR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLBRElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLBRElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLBRElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_CLEAR:
		{
			JREX_LOGLN("HandleJRexHTMLBRElementEvent JREX_GET_CLEAR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetClear, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CLEAR:
		{
			JREX_LOGLN("HandleJRexHTMLBRElementEvent JREX_SET_CLEAR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetClear, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLBRElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLBRElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLBRElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLBRElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}