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


#include "org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLTableElement
enum JRexHTMLTableElementEventTypes{JREX_GET_CAPTION=0U,
									JREX_SET_CAPTION,
									JREX_GET_T_HEAD,
									JREX_SET_T_HEAD,
									JREX_GET_T_FOOT,
									JREX_SET_T_FOOT,
									JREX_GET_ROWS,
									JREX_GET_T_BODIES,
									JREX_GET_ALIGN,
									JREX_SET_ALIGN,
									JREX_GET_BG_COLOR,
									JREX_SET_BG_COLOR,
									JREX_GET_BORDER,
									JREX_SET_BORDER,
									JREX_GET_CELL_PADDING,
									JREX_SET_CELL_PADDING,
									JREX_GET_CELL_SPACING,
									JREX_SET_CELL_SPACING,
									JREX_GET_FRAME,
									JREX_SET_FRAME,
									JREX_GET_RULES,
									JREX_SET_RULES,
									JREX_GET_SUMMARY,
									JREX_SET_SUMMARY,
									JREX_GET_WIDTH,
									JREX_SET_WIDTH,
									JREX_CREATE_T_HEAD,
									JREX_DELETE_T_HEAD,
									JREX_CREATE_T_FOOT,
									JREX_DELETE_T_FOOT,
									JREX_CREATE_CAPTION,
									JREX_DELETE_CAPTION,
									JREX_INSERT_ROW,
									JREX_DELETE_ROW};

static void* PR_CALLBACK HandleJRexHTMLTableElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLTableElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLTableElementImpl_InsertRowInternal(JNIEnv *env, nsIDOMHTMLTableElement* element, jint value){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (element){
		nsCOMPtr<nsIDOMHTMLElement> tmpElement;
		rv = element->InsertRow(value,getter_AddRefs(tmpElement));
		JREX_LOGLN("JRexHTMLTableElementImpl_InsertRowInternal()--> **** InsertRow rv<"<<rv<<"> ****")
		if(tmpElement)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpElement.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetCaption
 * Signature: ()Lorg/w3c/dom/html2/HTMLTableCaptionElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetCaption
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI (env , jhtmlEle, HTMLTableElement, HTMLTableCaptionElement, GetCaption, JREX_GET_CAPTION, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetCaption
 * Signature: (Lorg/w3c/dom/html2/HTMLTableCaptionElement;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetCaption
  (JNIEnv *env, jobject  jhtmlEle, jobject jvalue){
	SET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, jvalue, HTMLTableCaptionElement, SetCaption, JREX_SET_CAPTION, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetTHead
 * Signature: ()Lorg/w3c/dom/html2/HTMLTableSectionElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetTHead
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI (env , jhtmlEle, HTMLTableElement, HTMLTableSectionElement, GetTHead, JREX_GET_T_HEAD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetTHead
 * Signature: (Lorg/w3c/dom/html2/HTMLTableSectionElement;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetTHead
  (JNIEnv *env, jobject jhtmlEle, jobject jvalue){
	SET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, jvalue, HTMLTableSectionElement, SetTHead, JREX_SET_T_HEAD, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetTFoot
 * Signature: ()Lorg/w3c/dom/html2/HTMLTableSectionElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetTFoot
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI (env , jhtmlEle, HTMLTableElement, HTMLTableSectionElement, GetTFoot, JREX_GET_T_FOOT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetTFoot
 * Signature: (Lorg/w3c/dom/html2/HTMLTableSectionElement;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetTFoot
  (JNIEnv *env, jobject jhtmlEle, jobject jvalue){
	SET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, jvalue,  HTMLTableSectionElement, SetTFoot, JREX_SET_T_FOOT, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetRows
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetRows
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_COL_JNI(env , jhtmlEle, HTMLTableElement, GetRows, JREX_GET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetTBodies
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetTBodies
  (JNIEnv *env, jobject  jhtmlEle){
	GET_DOM_HTML_COL_JNI(env , jhtmlEle, HTMLTableElement, GetTBodies, JREX_GET_T_BODIES, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetAlign
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetBgColor
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetBgColor
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetBgColor, JREX_GET_BG_COLOR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetBgColor
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetBgColor
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetBgColor, JREX_SET_BG_COLOR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetBorder
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetBorder
  (JNIEnv *env, jobject  jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetBorder, JREX_GET_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetBorder
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetBorder
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetBorder, JREX_SET_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetCellPadding
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetCellPadding
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetCellPadding, JREX_GET_CELL_PADDING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetCellPadding
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetCellPadding
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetCellPadding, JREX_SET_CELL_PADDING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetCellSpacing
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetCellSpacing
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetCellSpacing, JREX_GET_CELL_SPACING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetCellSpacing
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetCellSpacing
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetCellSpacing, JREX_SET_CELL_SPACING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetFrame
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetFrame
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetFrame, JREX_GET_FRAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetFrame
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetFrame
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetFrame, JREX_SET_FRAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetRules
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetRules
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetRules, JREX_GET_RULES, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetRules
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetRules
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetRules, JREX_SET_RULES, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetSummary
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetSummary
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetSummary, JREX_GET_SUMMARY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetSummary
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetSummary
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetSummary, JREX_SET_SUMMARY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    GetWidth
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_GetWidth
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableElement, GetWidth, JREX_GET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    SetWidth
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_SetWidth
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableElement, SetWidth, JREX_SET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    CreateTHead
 * Signature: ()Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_CreateTHead
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, HTMLElement, CreateTHead, JREX_CREATE_T_HEAD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    DeleteTHead
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_DeleteTHead
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTableElement, DeleteTHead, JREX_DELETE_T_HEAD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    CreateTFoot
 * Signature: ()Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_CreateTFoot
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, HTMLElement, CreateTFoot, JREX_CREATE_T_FOOT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    DeleteTFoot
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_DeleteTFoot
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTableElement, DeleteTFoot, JREX_DELETE_T_FOOT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    CreateCaption
 * Signature: ()Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_CreateCaption
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_ELE_JNI(env , jhtmlEle, HTMLTableElement, HTMLElement, CreateCaption, JREX_CREATE_CAPTION, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    DeleteCaption
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_DeleteCaption
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTableElement, DeleteCaption, JREX_DELETE_CAPTION, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    InsertRow
 * Signature: (I)Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_InsertRow
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	if(!JRexDOMGlobals::sIntialized)return NULL;

	JREX_TRY

	nsIDOMHTMLTableElement* thisElement=(nsIDOMHTMLTableElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertRow()--> **** thisElement <"<<thisElement<<"> ****")

	if(IS_NULL(thisElement) || IS_NULL(jvalue)){
		ThrowJRexException(env, "**** InsertRow()--> thisElement/newElement DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("InsertRow()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLTableElementImpl_InsertRowInternal(env, thisElement, jvalue);
	}else{
		nsresult rv=ExecInEventQDOM(thisElement, JREX_INSERT_ROW, (void*)jvalue, PR_TRUE, HandleJRexHTMLTableElementEvent, DestroyJRexHTMLTableElementEvent, (void**)&jrv);
		JREX_LOGLN("InsertRow()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("InsertRow()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("InsertRow()--> **** InsertRow DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("InsertRow()--> **** InsertRow NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** InsertRow ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl
 * Method:    DeleteRow
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl_DeleteRow
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLTableElement, DeleteRow, JREX_DELETE_ROW, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

void* PR_CALLBACK HandleJRexHTMLTableElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLTableElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLTableElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_CAPTION:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_CAPTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLTableCaptionElement, NULL, ele.get(), GetCaption, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CAPTION:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_CAPTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsIDOMHTMLTableCaptionElement* value = NS_REINTERPRET_CAST(nsIDOMHTMLTableCaptionElement*, event->eventData);
			SET_DOM_HTML_ELE_EQT(value, ele.get(), SetCaption, jrv)
			return (void*)jrv;
		}
		case JREX_GET_T_HEAD:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_T_HEAD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLTableSectionElement, NULL, ele.get(), GetTHead, jrv)
			return (void*)jrv;
		}
		case JREX_SET_T_HEAD:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_T_HEAD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsIDOMHTMLTableSectionElement* value = NS_REINTERPRET_CAST(nsIDOMHTMLTableSectionElement*, event->eventData);
			SET_DOM_HTML_ELE_EQT(value, ele.get(), SetTHead, jrv)
			return (void*)jrv;
		}
		case JREX_GET_T_FOOT:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_T_FOOT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLTableSectionElement, NULL, ele.get(), GetTFoot, jrv)
			return (void*)jrv;
		}
		case JREX_SET_T_FOOT:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_T_FOOT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsIDOMHTMLTableSectionElement* value = NS_REINTERPRET_CAST(nsIDOMHTMLTableSectionElement*, event->eventData);
			SET_DOM_HTML_ELE_EQT(value, ele.get(), SetTFoot, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetRows, jrv)
			return (void*)jrv;
		}
		case JREX_GET_T_BODIES:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_T_BODIES EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetTBodies, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BG_COLOR:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_BG_COLOR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BG_COLOR:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_BG_COLOR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBgColor, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBorder, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBorder, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CELL_PADDING:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_CELL_PADDING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCellPadding, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CELL_PADDING:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_CELL_PADDING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCellPadding, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CELL_SPACING:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_CELL_SPACING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCellSpacing, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CELL_SPACING:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_CELL_SPACING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCellSpacing, jrv)
			return (void*)jrv;
		}
		case JREX_GET_FRAME:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_FRAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetFrame, jrv)
			return (void*)jrv;
		}
		case JREX_SET_FRAME:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_FRAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetFrame, jrv)
			return (void*)jrv;
		}
		case JREX_GET_RULES:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_RULES EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetRules, jrv)
			return (void*)jrv;
		}
		case JREX_SET_RULES:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_RULES EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetRules, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SUMMARY:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_SUMMARY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetSummary, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SUMMARY:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_SUMMARY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetSummary, jrv)
			return (void*)jrv;
		}
		case JREX_GET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_GET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetWidth, jrv)
			return (void*)jrv;
		}
		case JREX_SET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_SET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetWidth, jrv)
			return (void*)jrv;
		}
		case JREX_CREATE_T_HEAD:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_CREATE_T_HEAD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLElement, NULL, ele.get(), CreateTHead, jrv)
			return (void*)jrv;
		}
		case JREX_DELETE_T_HEAD:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_DELETE_T_HEAD EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), DeleteTHead, jrv)
			return (void*)jrv;
		}
		case JREX_CREATE_T_FOOT:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_CREATE_T_FOOT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLElement, NULL, ele.get(), CreateTFoot, jrv)
			return (void*)jrv;
		}
		case JREX_DELETE_T_FOOT:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_DELETE_T_FOOT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), DeleteTFoot, jrv)
			return (void*)jrv;
		}
		case JREX_CREATE_CAPTION:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_CREATE_CAPTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLElement, NULL, ele.get(), CreateCaption, jrv)
			return (void*)jrv;
		}
		case JREX_DELETE_CAPTION:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_DELETE_CAPTION EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), DeleteCaption, jrv)
			return (void*)jrv;
		}
		case JREX_INSERT_ROW:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_INSERT_ROW EVENT!!!****")

			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			return (void*)JRexHTMLTableElementImpl_InsertRowInternal(nsnull, ele.get(), value);
		}
		case JREX_DELETE_ROW:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent JREX_DELETE_ROW EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), DeleteRow, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLTableElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLTableElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLTableElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLTableElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
