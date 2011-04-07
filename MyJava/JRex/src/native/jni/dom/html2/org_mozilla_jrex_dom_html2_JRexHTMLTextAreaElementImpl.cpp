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


#include "org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLTextAreaElement
enum JRexHTMLTextAreaElementEventTypes{	JREX_GET_DEFAULT_VALUE=0U,
										JREX_SET_DEFAULT_VALUE,
										JREX_GET_FORM,
										JREX_GET_ACCESS_KEY,
										JREX_SET_ACCESS_KEY,
										JREX_GET_COLS,
										JREX_SET_COLS,
										JREX_GET_DISABLED,
										JREX_SET_DISABLED,
										JREX_GET_NAME,
										JREX_SET_NAME,
										JREX_GET_READ_ONLY,
										JREX_SET_READ_ONLY,
										JREX_GET_ROWS,
										JREX_SET_ROWS,
										JREX_GET_VALUE,
										JREX_SET_VALUE,
										JREX_GET_TAB_INDEX,
										JREX_SET_TAB_INDEX,
										JREX_GET_TYPE,
										JREX_SELECT,
										JREX_BLUR,
										JREX_FOCUS };

static void* PR_CALLBACK HandleJRexHTMLTextAreaElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLTextAreaElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLTextAreaElementImpl_GetFormInternal(JNIEnv *env, nsIDOMHTMLTextAreaElement* ele){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMHTMLFormElement> tmpForm;
		rv = ele->GetForm(getter_AddRefs(tmpForm));
		JREX_LOGLN("JRexHTMLTextAreaElementImpl_GetFormInternal()--> **** GetForm rv<"<<rv<<"> ****")
		if(tmpForm)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpForm.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetDefaultValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetDefaultValue
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTextAreaElement,GetDefaultValue, JREX_GET_DEFAULT_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetDefaultValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetDefaultValue
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTextAreaElement, SetDefaultValue, JREX_SET_DEFAULT_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetForm
 * Signature: ()Lorg/w3c/dom/html2/HTMLFormElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetForm
(JNIEnv *env, jobject jhtmlEle){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLTextAreaElement* thisEle=(nsIDOMHTMLTextAreaElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetForm()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetForm()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetForm()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLTextAreaElementImpl_GetFormInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_FORM, nsnull, PR_TRUE, HandleJRexHTMLTextAreaElementEvent, DestroyJRexHTMLTextAreaElementEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetAccessKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetAccessKey
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTextAreaElement, GetAccessKey, JREX_GET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetAccessKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetAccessKey
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTextAreaElement, SetAccessKey, JREX_SET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetCols
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetCols
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTextAreaElement,PRInt32, GetCols, JREX_GET_COLS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetCols
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetCols
(JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLTextAreaElement, SetCols, JREX_SET_COLS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetDisabled
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLTextAreaElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetDisabled
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLTextAreaElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetName
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTextAreaElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetName
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLTextAreaElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)	}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetReadOnly
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetReadOnly
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLTextAreaElement, GetReadOnly, JREX_GET_READ_ONLY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetReadOnly
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetReadOnly
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLTextAreaElement, SetReadOnly, JREX_SET_READ_ONLY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetRows
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetRows
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTextAreaElement,PRInt32, GetRows, JREX_GET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetRows
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetRows
(JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLTextAreaElement, SetRows, JREX_SET_ROWS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetTabIndex
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLTextAreaElement,PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetTabIndex
(JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLTextAreaElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetType
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTextAreaElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_GetValue
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLTextAreaElement, GetValue, JREX_GET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_SetValue
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env,jhtmlEle, jvalue, HTMLTextAreaElement, SetValue, JREX_SET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    Blur
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_Blur
(JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTextAreaElement, Blur, JREX_BLUR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    Focus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_Focus
(JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTextAreaElement, Focus, JREX_FOCUS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl
 * Method:    Select
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl_Select
(JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLTextAreaElement, Select, JREX_SELECT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLTextAreaElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLTextAreaElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_FORM:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_FORM EVENT!!!****")

			return (void*)JRexHTMLTextAreaElementImpl_GetFormInternal(nsnull, ele.get());
		}
		case JREX_GET_DEFAULT_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_DEFAULT_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetDefaultValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DEFAULT_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_DEFAULT_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetDefaultValue, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccessKey, jrv)
			return (void*)jrv;
		}
        case JREX_SET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccessKey, jrv)
			return (void*)jrv;
		}
		case JREX_GET_COLS:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_COLS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetCols, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COLS:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_COLS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetCols, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_DISABLED_ONLY!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_READ_ONLY:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_READ_ONLY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetReadOnly, jrv)
			return (void*)jrv;
		}
		case JREX_SET_READ_ONLY:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_READ_ONLY!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetReadOnly, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetRows, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ROWS:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_ROWS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetRows, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetValue, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}
		case JREX_SELECT:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_SELECT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Select, jrv)
			return (void*)jrv;
		}
		case JREX_BLUR:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_BLUR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Blur, jrv)
			return (void*)jrv;
		}
		case JREX_FOCUS:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent JREX_FOCUS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Focus, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLTextAreaElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLTextAreaElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLTextAreaElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
