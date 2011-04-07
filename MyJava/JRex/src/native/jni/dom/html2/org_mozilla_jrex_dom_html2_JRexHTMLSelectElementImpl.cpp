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


#include "org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLSelectElement
enum JRexHTMLSelectElementEventTypes{	JREX_GET_TYPE=0U,
										JREX_GET_SELECTED_INDEX,
										JREX_SET_SELECTED_INDEX,
										JREX_GET_VALUE,
										JREX_SET_VALUE,
										JREX_GET_LENGTH,
										JREX_SET_LENGTH,
										JREX_GET_FORM,
										JREX_GET_OPTIONS,
										JREX_GET_DISABLED,
										JREX_SET_DISABLED,
										JREX_GET_MULTIPLE,
										JREX_SET_MULTIPLE,
										JREX_GET_NAME,
										JREX_SET_NAME,
										JREX_GET_SIZE,
										JREX_SET_SIZE,
										JREX_GET_TAB_INDEX,
										JREX_SET_TAB_INDEX,
										JREX_ADD,
										JREX_REMOVE,
										JREX_BLUR,
										JREX_FOCUS };

struct JRexSelectEventParam{
	nsIDOMHTMLElement *element1;
	nsIDOMHTMLElement *element2;
};

static void* PR_CALLBACK HandleJRexHTMLSelectElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLSelectElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLSelectElementImpl_GetFormInternal(JNIEnv *env, nsIDOMHTMLSelectElement* ele){
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

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLSelectElementImpl_AddInternal(JNIEnv *env, nsIDOMHTMLSelectElement* element, nsIDOMHTMLElement* newElement, nsIDOMHTMLElement* refElement){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (element){
		rv = element->Add(newElement, refElement);
		JREX_LOGLN("JRexHTMLSelectElementImpl_AddInternal()--> **** Add rv<"<<rv<<"> ****")
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetType
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLSelectElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetSelectedIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetSelectedIndex
(JNIEnv *env, jobject jhtmlEle) {
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLSelectElement,PRInt32, GetSelectedIndex, JREX_GET_SELECTED_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetSelectedIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetSelectedIndex
(JNIEnv *env, jobject jhtmlEle, jint jvalue) {
	SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLSelectElement, SetSelectedIndex, JREX_SET_SELECTED_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetValue
(JNIEnv *env, jobject jhtmlEle) {

		GET_DOM_STRING_JNI(env , jhtmlEle, HTMLSelectElement, GetValue, JREX_GET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetValue
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLSelectElement, SetValue, JREX_SET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetLength
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_INT_JNI(env , jhtmlEle, HTMLSelectElement,PRUint32, GetLength, JREX_GET_LENGTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetLength
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetLength
(JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLSelectElement, SetLength, JREX_SET_LENGTH, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetForm
 * Signature: ()Lorg/w3c/dom/html2/HTMLFormElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetForm
(JNIEnv *env, jobject jhtmlEle){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLSelectElement* thisEle=(nsIDOMHTMLSelectElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetForm()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetForm()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetForm()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLSelectElementImpl_GetFormInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_FORM, nsnull, PR_TRUE, HandleJRexHTMLSelectElementEvent, DestroyJRexHTMLSelectElementEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetOptions
 * Signature: ()Lorg/w3c/dom/html2/HTMLOptionsCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetOptions
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_HTML_OPT_COL_JNI(env , jhtmlEle, HTMLSelectElement, GetOptions, JREX_GET_OPTIONS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetDisabled
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLSelectElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetDisabled
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){

	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLSelectElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetMultiple
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetMultiple
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLSelectElement, GetMultiple, JREX_GET_MULTIPLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetMultiple
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetMultiple
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){

	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLSelectElement, SetMultiple, JREX_SET_MULTIPLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetName
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLSelectElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetName
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLSelectElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetSize
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_INT_JNI(env , jhtmlEle, HTMLSelectElement,PRInt32, GetSize, JREX_GET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetSize
(JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLSelectElement, SetSize, JREX_SET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_GetTabIndex
(JNIEnv *env, jobject jhtmlEle){

	GET_DOM_INT_JNI(env , jhtmlEle, HTMLSelectElement, PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_SetTabIndex
(JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLSelectElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    Add
 * Signature: (Lorg/w3c/dom/html2/HTMLElement;Lorg/w3c/dom/html2/HTMLElement;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_Add
(JNIEnv *env, jobject jhtmlEle, jobject jnewElement, jobject jrefElement){

	if(!JRexDOMGlobals::sIntialized)return;

	JREX_TRY

	nsIDOMHTMLSelectElement* thisElement=(nsIDOMHTMLSelectElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("Add()--> **** thisElement <"<<thisElement<<"> ****")

	nsIDOMHTMLElement* newElement=nsnull;

	if(NOT_NULL(jnewElement))
		newElement=(nsIDOMHTMLElement*)NS_INT32_TO_PTR(env->GetIntField(jnewElement, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("Add()--> **** newElement <"<<newElement<<"> ****")

	nsIDOMHTMLElement* refElement=nsnull;
	if(NOT_NULL(jrefElement))
		refElement=(nsIDOMHTMLElement*)NS_INT32_TO_PTR(env->GetIntField(jrefElement, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("Add()--> **** refElement <"<<refElement<<"> ****")

	if(IS_NULL(thisElement) || IS_NULL(newElement)){
		ThrowJRexException(env, "**** Add()--> thisElement/newElement DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Add()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLSelectElementImpl_AddInternal(env, thisElement, newElement, refElement);
	}else{
		JRexSelectEventParam* param=new JRexSelectEventParam;
		if(IS_NULL(param))return;
		param->element1=newElement;
		param->element2=refElement;

		nsresult rv=ExecInEventQDOM(thisElement, JREX_ADD, param, PR_TRUE, HandleJRexHTMLSelectElementEvent, DestroyJRexHTMLSelectElementEvent, (void**)&jrv);
		JREX_LOGLN("Add()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("Add()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if ((NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){
				JREX_LOGLN("Add()--> ****  DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("Add()--> ****  NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** Add  Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    Remove
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_Remove
(JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLSelectElement, Remove, JREX_REMOVE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    Blur
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_Blur
(JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLSelectElement, Blur, JREX_BLUR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl
 * Method:    Focus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl_Focus
(JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLSelectElement, Focus, JREX_FOCUS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLSelectElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLSelectElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLSelectElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_FORM:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_FORM EVENT!!!****")

			return (void*)JRexHTMLSelectElementImpl_GetFormInternal(nsnull, ele.get());
		}
		case JREX_ADD:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_ADD EVENT!!!****")

			JRexSelectEventParam* param = NS_REINTERPRET_CAST(JRexSelectEventParam*, event->eventData);
			return (void*)JRexHTMLSelectElementImpl_AddInternal(nsnull, ele.get(), param->element1, param->element2);
		}
		case JREX_REMOVE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_REMOVE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), Remove, jrv)
			return (void*)jrv;
		}
		case JREX_GET_OPTIONS:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_OPTIONS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_OPT_COL_EQT(NULL, ele.get(), GetOptions, jrv)
			return (void*)jrv;
		}

		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}

		case JREX_GET_SELECTED_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_SELECTED_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetSelectedIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SELECTED_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_SELECTED_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetSelectedIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetValue, jrv)
			return (void*)jrv;

		}
		case JREX_GET_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_LENGTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRUint32, GetLength, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_LENGTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetLength, jrv)
			return (void*)jrv;
		}

		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;

		}
		case JREX_GET_MULTIPLE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_MULTIPLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetMultiple, jrv)
			return (void*)jrv;
		}
		case JREX_SET_MULTIPLE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_MULTIPLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetMultiple, jrv)
			return (void*)jrv;

		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetSize, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetSize, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_GET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;
		}

		case JREX_BLUR:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_BLUR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Blur, jrv)
			return (void*)jrv;

		}
		case JREX_FOCUS:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_FOCUS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Focus, jrv)
			return (void*)jrv;

		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLSelectElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLSelectElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLSelectElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
