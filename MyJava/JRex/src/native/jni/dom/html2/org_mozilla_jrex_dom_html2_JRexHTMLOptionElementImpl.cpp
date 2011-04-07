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


#include "org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLSelectElement
enum JRexHTMLOptionElementEventTypes{	JREX_GET_FORM=0U,
										JREX_GET_DEFAULT_SELECTED,
										JREX_SET_DEFAULT_SELECTED,
										JREX_GET_TEXT,
										JREX_GET_INDEX,
										JREX_GET_DISABLED,
										JREX_SET_DISABLED,
										JREX_GET_LABEL,
										JREX_SET_LABEL,
										JREX_GET_SELECTED,
										JREX_SET_SELECTED,
										JREX_GET_VALUE,
										JREX_SET_VALUE };

static void* PR_CALLBACK HandleJRexHTMLOptionElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLOptionElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLOptionElementImpl_GetFormInternal(JNIEnv *env, nsIDOMHTMLOptionElement* ele){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMHTMLFormElement> tmpForm;
		rv = ele->GetForm(getter_AddRefs(tmpForm));
		JREX_LOGLN("JRexHTMLSelectElementImpl_GetFormInternal()--> **** GetForm rv<"<<rv<<"> ****")
		if(tmpForm)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpForm.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetForm
 * Signature: ()Lorg/w3c/dom/html2/HTMLFormElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetForm
(JNIEnv *env, jobject jhtmlEle) {
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLOptionElement* thisEle=(nsIDOMHTMLOptionElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetForm()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetForm()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetForm()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLOptionElementImpl_GetFormInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_FORM, nsnull, PR_TRUE, HandleJRexHTMLOptionElementEvent, DestroyJRexHTMLOptionElementEvent, (void**)&jrv);
		JREX_LOGLN("GetForm()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetForm()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetForm()--> **** GetForm NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetForm Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetDefaultSelected
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetDefaultSelected
(JNIEnv *env, jobject jhtmlEle) {
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLOptionElement, GetDefaultSelected, JREX_GET_DEFAULT_SELECTED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    SetDefaultSelected
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_SetDefaultSelected
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue) {
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLOptionElement, SetDefaultSelected, JREX_SET_DEFAULT_SELECTED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetText
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetText
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLOptionElement, GetText, JREX_GET_TEXT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetIndex
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLOptionElement,PRInt32, GetIndex, JREX_GET_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetDisabled
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLOptionElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_SetDisabled
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLOptionElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetLabel
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetLabel
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLOptionElement, GetLabel, JREX_GET_LABEL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    SetLabel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_SetLabel
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLOptionElement, SetLabel, JREX_SET_LABEL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetSelected
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetSelected
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLOptionElement, GetSelected, JREX_GET_SELECTED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    SetSelected
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_SetSelected
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLOptionElement, SetSelected, JREX_SET_SELECTED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_GetValue
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLOptionElement, GetValue, JREX_GET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl_SetValue
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLOptionElement, SetValue, JREX_SET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLOptionElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLOptionElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLOptionElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_FORM:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_FORM EVENT!!!****")

			return (void*)JRexHTMLOptionElementImpl_GetFormInternal(nsnull, ele.get());
		}
		case JREX_GET_DEFAULT_SELECTED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_DEFAULT_SELECTED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDefaultSelected, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DEFAULT_SELECTED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_SET_DEFAULT_SELECTED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDefaultSelected, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TEXT:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_TEXT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetText, jrv)
			return (void*)jrv;
		}
		case JREX_GET_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_SET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LABEL:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_LABEL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLabel, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LABEL:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_SET_LABEL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLabel, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SELECTED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_SELECTED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetSelected, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SELECTED:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_SET_SELECTED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetSelected, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_GET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent JREX_SET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetValue, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLOptionElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLOptionElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLOptionElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLOptionElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
