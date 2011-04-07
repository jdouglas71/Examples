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


#include "org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLButtonElement
enum JRexHTMLButtonElementEventTypes{	JREX_GET_FORM=0U,
										JREX_GET_ACCESS_KEY,
										JREX_SET_ACCESS_KEY,
										JREX_GET_DISABLED,
										JREX_SET_DISABLED,
										JREX_GET_NAME,
										JREX_SET_NAME,
										JREX_GET_TAB_INDEX,
										JREX_SET_TAB_INDEX,
										JREX_GET_TYPE,
										JREX_GET_VALUE,
										JREX_SET_VALUE};

static void* PR_CALLBACK HandleJRexHTMLButtonElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLButtonElementEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLButtonElementImpl_GetFormInternal(JNIEnv *env, nsIDOMHTMLButtonElement* ele){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMHTMLFormElement> tmpForm;
		rv = ele->GetForm(getter_AddRefs(tmpForm));
		JREX_LOGLN("JRexHTMLButtonElementImpl_GetFormInternal()--> **** GetForm rv<"<<rv<<"> ****")
		if(tmpForm)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpForm.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetForm
 * Signature: ()Lorg/w3c/dom/html2/HTMLFormElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetForm
(JNIEnv *env, jobject jhtmlEle){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLButtonElement* thisEle=(nsIDOMHTMLButtonElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetForm()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetForm()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetForm()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLButtonElementImpl_GetFormInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_FORM, nsnull, PR_TRUE, HandleJRexHTMLButtonElementEvent, DestroyJRexHTMLButtonElementEvent, (void**)&jrv);
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
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetAccessKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetAccessKey
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLButtonElement, GetAccessKey, JREX_GET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    SetAccessKey
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_SetAccessKey
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLButtonElement, SetAccessKey, JREX_SET_ACCESS_KEY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetDisabled
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetDisabled
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLButtonElement, GetDisabled, JREX_GET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    SetDisabled
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_SetDisabled
(JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLButtonElement, SetDisabled, JREX_SET_DISABLED, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetName
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLButtonElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_SetName
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLButtonElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)	}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetTabIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetTabIndex
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLButtonElement,PRInt32, GetTabIndex, JREX_GET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    SetTabIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_SetTabIndex
(JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLButtonElement, SetTabIndex, JREX_SET_TAB_INDEX, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetType
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLButtonElement, GetType, JREX_GET_TYPE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_GetValue
(JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLButtonElement, GetValue, JREX_GET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl_SetValue
(JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env,jhtmlEle, jvalue, HTMLButtonElement, SetValue, JREX_SET_VALUE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLButtonElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLButtonElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLButtonElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_FORM:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_FORM EVENT!!!****")

			return (void*)JRexHTMLButtonElementImpl_GetFormInternal(nsnull, ele.get());
		}
		case JREX_GET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAccessKey, jrv)
			return (void*)jrv;
		}
        case JREX_SET_ACCESS_KEY:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_SET_ACCESS_KEY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAccessKey, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_DISABLED EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DISABLED:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_SET_DISABLED_ONLY!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetDisabled, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TAB_INDEX:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_SET_TAB_INDEX EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRInt32 value = NS_REINTERPRET_CAST(PRInt32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetTabIndex, jrv)
			return (void*)jrv;
		}
		case JREX_GET_TYPE:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_TYPE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetType, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_GET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetValue, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent JREX_SET_VALUE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetValue, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLButtonElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLButtonElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLButtonElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLButtonElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
