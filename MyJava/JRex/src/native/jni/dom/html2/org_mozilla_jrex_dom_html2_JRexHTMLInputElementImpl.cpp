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


#include "org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLInputElement
enum JRexHTMLInputElementEventTypes{	JREX_GET_DEF_VAL=0U,
										JREX_SET_DEF_VAL,
										JREX_GET_DEFAULT_CHECKED,
										JREX_SET_DEFAULT_CHECKED,
										JREX_GET_FORM,
										JREX_GET_ACCEPT,
										JREX_SET_ACCEPT,
										JREX_GET_ACCESS_KEY,
										JREX_SET_ACCESS_KEY,
										JREX_GET_ALIGN,
										JREX_SET_ALIGN,
										JREX_GET_ALT,
										JREX_SET_ALT,
										JREX_GET_CHECKED,
										JREX_SET_CHECKED,
										JREX_GET_DISABLED,
										JREX_SET_DISABLED,
										JREX_GET_MAX_LENGTH,
										JREX_SET_MAX_LENGTH,
										JREX_GET_NAME,
										JREX_SET_NAME,
										JREX_GET_READ_ONLY,
										JREX_SET_READ_ONLY,
										JREX_GET_SIZE,
										JREX_SET_SIZE,
										JREX_GET_SRC,
										JREX_SET_SRC,
										JREX_GET_TAB_INDEX,
										JREX_SET_TAB_INDEX,
										JREX_GET_TYPE,
										JREX_SET_TYPE,
										JREX_GET_USEMAP,
										JREX_SET_USEMAP,
										JREX_GET_VALUE,
										JREX_SET_VALUE,
										JREX_BLUR,
										JREX_FOCUS,
										JREX_SELECT,
										JREX_CLICK};

static void* PR_CALLBACK HandleJRexHTMLInputElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLInputElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLInputElementImpl_GetFormInternal(JNIEnv *env, nsIDOMHTMLInputElement* ele){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMHTMLFormElement> tmpForm;
		rv = ele->GetForm(getter_AddRefs(tmpForm));
		JREX_LOGLN("JRexHTMLInputElementImpl_GetFormInternal()--> **** GetForm rv<"<<rv<<"> ****")
		if(tmpForm)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpForm.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetDefaultValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetDefaultValue
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetDefaultValue, JREX_GET_DEF_VAL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetDefaultValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetDefaultValue
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetDefaultValue, JREX_SET_DEF_VAL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetDefaultChecked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetDefaultChecked
  (JNIEnv *env, jobject jhtmlEle){
	  GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLInputElement, GetDefaultChecked, JREX_GET_DEFAULT_CHECKED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetDefaultChecked
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetDefaultChecked
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetDefaultChecked, JREX_SET_DEFAULT_CHECKED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetForm
 * Signature: ()Lorg/w3c/dom/html2/HTMLFormElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetForm
  (JNIEnv *env, jobject jhtmlEle){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLInputElement* thisEle=(nsIDOMHTMLInputElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetForm()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetForm()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetForm()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLInputElementImpl_GetFormInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_FORM, nsnull, PR_TRUE, HandleJRexHTMLInputElementEvent, DestroyJRexHTMLInputElementEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetAccept
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetAccept
  (JNIEnv *env, jobject jhtmlEle){
	  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetAccept, JREX_GET_ACCEPT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetAccept
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetAccept
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetAccept, JREX_SET_ACCEPT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetAccessKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetAccessKey
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetAccessKey, JREX_GET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetAccessKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetAccessKey
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetAccessKey, JREX_SET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetAlign
  (JNIEnv *env, jobject jhtmlEle){
	  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetAlt
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetAlt
  (JNIEnv *env, jobject jhtmlEle){
	  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetAlt, JREX_GET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetAlt
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetAlt
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetAlt, JREX_SET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetChecked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetChecked
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLInputElement, GetChecked, JREX_GET_CHECKED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetChecked
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetChecked
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetChecked, JREX_SET_CHECKED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetDisabled
  (JNIEnv *env, jobject jhtmlEle){
	  GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLInputElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetDisabled
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetMaxLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetMaxLength
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLInputElement, PRInt32, GetMaxLength, JREX_GET_MAX_LENGTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetMaxLength
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetMaxLength
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLInputElement, SetMaxLength, JREX_SET_MAX_LENGTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetName
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetName
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetReadOnly
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetReadOnly
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLInputElement, GetReadOnly, JREX_GET_READ_ONLY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetReadOnly
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetReadOnly
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetReadOnly, JREX_SET_READ_ONLY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetSize
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLInputElement, PRUint32, GetSize, JREX_GET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetSize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetSize
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	  SET_DOM_INT_JNI(env , jhtmlEle, PRUint32, jvalue, HTMLInputElement, SetSize, JREX_SET_SIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetSrc
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetSrc
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetSrc, JREX_GET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetSrc
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetSrc
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetSrc, JREX_SET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetTabIndex
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLInputElement, PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetTabIndex
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLInputElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetType
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetType
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetType
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetType, JREX_SET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetUseMap
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetUseMap
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetUseMap, JREX_GET_USEMAP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetUseMap
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetUseMap
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetUseMap, JREX_SET_USEMAP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_GetValue
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLInputElement, GetValue, JREX_GET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_SetValue
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLInputElement, SetValue, JREX_SET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    Blur
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_Blur
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLInputElement, Blur, JREX_BLUR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    Focus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_Focus
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLInputElement, Focus, JREX_FOCUS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    Select
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_Select
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLInputElement, Select, JREX_SELECT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl
 * Method:    Click
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl_Click
  (JNIEnv *env, jobject jhtmlEle){
	CALL_DOM_JNI(env , jhtmlEle, HTMLInputElement, Click, JREX_CLICK, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

void* PR_CALLBACK HandleJRexHTMLInputElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLInputElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLInputElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_DEF_VAL:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_DEF_VAL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetDefaultValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DEF_VAL:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_DEF_VAL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetDefaultValue, jrv)
			return (void*)jrv;

		}
		case JREX_GET_DEFAULT_CHECKED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_DEFAULT_CHECKED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDefaultChecked, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DEFAULT_CHECKED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_DEFAULT_CHECKED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDefaultChecked, jrv)
			return (void*)jrv;

		}
		case JREX_GET_FORM:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_FORM EVENT!!!****")

			return (void*)JRexHTMLInputElementImpl_GetFormInternal(nsnull, ele.get());
		}
		case JREX_GET_ACCEPT:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_ACCEPT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccept, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ACCEPT:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_ACCEPT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccept, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccessKey, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccessKey, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_ALT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlt, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_ALT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlt, jrv)
			return (void*)jrv;

		}
		case JREX_GET_CHECKED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_CHECKED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetChecked, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CHECKED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_CHECKED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetChecked, jrv)
			return (void*)jrv;

		}
		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;

		}
		case JREX_GET_MAX_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_MAX_LENGTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetMaxLength, jrv)
			return (void*)jrv;
		}
		case JREX_SET_MAX_LENGTH:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_MAX_LENGTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetMaxLength, jrv)
			return (void*)jrv;

		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;

		}
		case JREX_GET_READ_ONLY:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_READ_ONLY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetReadOnly, jrv)
			return (void*)jrv;
		}
		case JREX_SET_READ_ONLY:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_READ_ONLY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetReadOnly, jrv)
			return (void*)jrv;

		}
		case JREX_GET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRUint32, GetSize, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SIZE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_SIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetSize, jrv)
			return (void*)jrv;

		}
		case JREX_GET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetSrc, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetSrc, jrv)
			return (void*)jrv;

		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;

		}
		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetType, jrv)
			return (void*)jrv;

		}
		case JREX_GET_USEMAP:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_USEMAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetUseMap, jrv)
			return (void*)jrv;
		}
		case JREX_SET_USEMAP:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_USEMAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetUseMap, jrv)
			return (void*)jrv;

		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_GET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetValue, jrv)
			return (void*)jrv;

		}
		case JREX_BLUR:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_BLUR EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Blur, jrv)
			return (void*)jrv;

		}
		case JREX_FOCUS:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_FOCUS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Focus, jrv)
			return (void*)jrv;

		}
		case JREX_SELECT:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_SELECT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Select, jrv)
			return (void*)jrv;

		}
		case JREX_CLICK:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent JREX_CLICK EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Click, jrv)
			return (void*)jrv;

		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLInputElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLInputElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLInputElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLInputElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
