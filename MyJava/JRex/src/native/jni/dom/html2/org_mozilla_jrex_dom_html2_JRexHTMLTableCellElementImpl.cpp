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


#include "org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLTableCellElement
enum JRexHTMLTableCellElementEventTypes{JREX_GET_CELL_INDEX=0U,
										JREX_GET_ABBR,
										JREX_SET_ABBR,
										JREX_GET_ALIGN,
										JREX_SET_ALIGN,
										JREX_GET_AXIS,
										JREX_SET_AXIS,
										JREX_GET_CH,
										JREX_SET_CH,
										JREX_GET_CH_OFF,
										JREX_SET_CH_OFF,
										JREX_GET_BG_COL,
										JREX_SET_BG_COL,
										JREX_GET_VALIGN,
										JREX_SET_VALIGN,
										JREX_GET_COL_SPAN,
										JREX_SET_COL_SPAN,
										JREX_GET_ROW_SPAN,
										JREX_SET_ROW_SPAN,
										JREX_GET_HDRS,
										JREX_SET_HDRS,
										JREX_GET_NO_WRP,
										JREX_SET_NO_WRP,
										JREX_GET_SCOPE,
										JREX_SET_SCOPE,
										JREX_GET_HEIGHT,
										JREX_SET_HEIGHT,
										JREX_GET_WIDTH,
										JREX_SET_WIDTH
										};

static void* PR_CALLBACK HandleJRexHTMLTableCellElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLTableCellElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetCellIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetCellIndex
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTableCellElement, PRInt32, GetCellIndex, JREX_GET_CELL_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetAbbr
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetAbbr
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetAbbr, JREX_GET_ABBR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetAbbr
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetAbbr
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetAbbr, JREX_SET_ABBR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetAlign
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetAxis
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetAxis
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetAxis, JREX_GET_AXIS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetAxis
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetAxis
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetAxis, JREX_SET_AXIS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetBgColor
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetBgColor
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetBgColor, JREX_GET_BG_COL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetBgColor
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetBgColor
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetBgColor, JREX_SET_BG_COL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetCh
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetCh
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetCh, JREX_GET_CH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetCh
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetCh
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetCh, JREX_SET_CH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetChOff
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetChOff
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetChOff, JREX_GET_CH_OFF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetChOff
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetChOff
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetChOff, JREX_SET_CH_OFF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetVAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetVAlign
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetVAlign, JREX_GET_VALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetVAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetVAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetVAlign, JREX_SET_VALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetColSpan
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetColSpan
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTableCellElement, PRInt32, GetColSpan, JREX_GET_COL_SPAN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetColSpan
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetColSpan
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLTableCellElement, SetColSpan, JREX_SET_COL_SPAN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetRowSpan
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetRowSpan
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTableCellElement, PRInt32, GetRowSpan, JREX_GET_ROW_SPAN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetRowSpan
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetRowSpan
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLTableCellElement, SetRowSpan, JREX_SET_ROW_SPAN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetHeaders
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetHeaders
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetHeaders, JREX_GET_HDRS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetHeaders
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetHeaders
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetHeaders, JREX_SET_HDRS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetHeight
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetHeight
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetHeight, JREX_GET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetHeight
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetHeight
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetHeight, JREX_SET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetNoWrap
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetNoWrap
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLTableCellElement, GetNoWrap, JREX_GET_NO_WRP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetNoWrap
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetNoWrap
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetNoWrap, JREX_SET_NO_WRP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetScope
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetScope
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetScope, JREX_GET_SCOPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetScope
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetScope
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetScope, JREX_SET_SCOPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    GetWidth
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_GetWidth
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableCellElement, GetWidth, JREX_GET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl
 * Method:    SetWidth
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl_SetWidth
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableCellElement, SetWidth, JREX_SET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLTableCellElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLTableCellElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLTableCellElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_CELL_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_CELL_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetCellIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ABBR:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_ABBR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAbbr, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ABBR:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_ABBR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAbbr, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_AXIS:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_AXIS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAxis, jrv)
			return (void*)jrv;
		}
		case JREX_SET_AXIS:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_AXIS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAxis, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BG_COL:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_BG_COL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BG_COL:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_BG_COL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CH:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_CH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCh, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CH:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_CH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCh, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CH_OFF:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_CHOFF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetChOff, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CH_OFF:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_CHOFF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetChOff, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_VALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetVAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_VALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetVAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ROW_SPAN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_ROW_SPAN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetRowSpan, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ROW_SPAN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_ROW_SPAN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetRowSpan, jrv)
			return (void*)jrv;
		}
		case JREX_GET_COL_SPAN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_COL_SPAN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetColSpan, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COL_SPAN:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_COL_SPAN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetColSpan, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HDRS:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_HDRS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHeaders, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HDRS:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_HDRS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHeaders, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NO_WRP:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_NO_WRP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetNoWrap, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NO_WRP:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_NO_WRP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetNoWrap, jrv)
			return (void*)jrv;

		}
		case JREX_GET_SCOPE:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_SCOPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetScope, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SCOPE:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_SCOPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetScope, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_GET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_GET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetWidth, jrv)
			return (void*)jrv;
		}
		case JREX_SET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent JREX_SET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetWidth, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLTableCellElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLTableCellElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLTableCellElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLTableCellElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
