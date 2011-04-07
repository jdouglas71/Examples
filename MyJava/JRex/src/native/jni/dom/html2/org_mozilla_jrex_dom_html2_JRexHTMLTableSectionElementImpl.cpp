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


#include "org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLTableSectionElement
enum JRexHTMLTableSectionElementEventTypes{	JREX_GET_ALIGN=0U,
											JREX_SET_ALIGN,
											JREX_GET_CH,
											JREX_SET_CH,
											JREX_GET_CH_OFF,
											JREX_SET_CH_OFF,
											JREX_GET_VALIGN,
											JREX_SET_VALIGN,
											JREX_GET_ROWS,
											JREX_INSERT_ROW,
											JREX_DELETE_ROW};

static void* PR_CALLBACK HandleJRexHTMLTableSectionElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLTableSectionElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLTableSectionElementImpl_InsertRowInternal(JNIEnv *env, nsIDOMHTMLTableSectionElement* element, jint value){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (element){
		nsCOMPtr<nsIDOMHTMLElement> tmpElement;
		rv = element->InsertRow(value,getter_AddRefs(tmpElement));
		JREX_LOGLN("JRexHTMLTableSectionElementImpl_InsertRowInternal()--> **** InsertRow rv<"<<rv<<"> ****")
		if(tmpElement)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpElement.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_GetAlign
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableSectionElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_SetAlign
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableSectionElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    GetCh
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_GetCh
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableSectionElement, GetCh, JREX_GET_CH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    SetCh
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_SetCh
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableSectionElement, SetCh, JREX_SET_CH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    GetChOff
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_GetChOff
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableSectionElement, GetChOff, JREX_GET_CH_OFF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    SetChOff
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_SetChOff
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableSectionElement, SetChOff, JREX_SET_CH_OFF, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    GetVAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_GetVAlign
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTableSectionElement, GetVAlign, JREX_GET_VALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    SetVAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_SetVAlign
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTableSectionElement, SetVAlign, JREX_SET_VALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    GetRows
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_GetRows
  (JNIEnv *env, jobject jhtmlEle){

	GET_DOM_HTML_COL_JNI(env , jhtmlEle, HTMLTableSectionElement, GetRows, JREX_GET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    InsertRow
 * Signature: (I)Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_InsertRow
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	if(!JRexDOMGlobals::sIntialized)return NULL;

	JREX_TRY

	nsIDOMHTMLTableSectionElement* thisElement=(nsIDOMHTMLTableSectionElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertRow()--> **** thisElement <"<<thisElement<<"> ****")

	if(IS_NULL(thisElement) || IS_NULL(jvalue)){
		ThrowJRexException(env, "**** InsertRow()--> thisElement/newElement DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("InsertRow()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLTableSectionElementImpl_InsertRowInternal(env, thisElement, jvalue);
	}else{
		nsresult rv=ExecInEventQDOM(thisElement, JREX_INSERT_ROW, (void*)jvalue, PR_TRUE, HandleJRexHTMLTableSectionElementEvent, DestroyJRexHTMLTableSectionElementEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl
 * Method:    DeleteRow
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl_DeleteRow
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLTableSectionElement, DeleteRow, JREX_DELETE_ROW, JRexDOMGlobals::nodePeerID, PR_TRUE)
}


void* PR_CALLBACK HandleJRexHTMLTableSectionElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLTableSectionElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){

		case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_GET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_SET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CH:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_GET_CH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCh, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CH:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_SET_CH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCh, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CH_OFF:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_GET_CHOFF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetChOff, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CH_OFF:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_SET_CHOFF EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetChOff, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_GET_VALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetVAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_SET_VALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetVAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_GET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetRows, jrv)
			return (void*)jrv;
		}
		case JREX_INSERT_ROW:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_INSERT_ROW EVENT!!!****")

			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			return (void*)JRexHTMLTableSectionElementImpl_InsertRowInternal(nsnull, ele.get(), value);
		}
		case JREX_DELETE_ROW:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent JREX_DELETE_ROW EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), DeleteRow, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLTableSectionElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLTableSectionElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLTableSectionElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
