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


#include "org_mozilla_jrex_dom_JRexAttrImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexAttr
enum JRexAttrEventTypes{JREX_GET_NAME=0U,
						JREX_OWNER_ELEMENT,
						JREX_GET_VALUE,
						JREX_SET_VALUE};

static void* PR_CALLBACK HandleJRexAttrEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexAttrEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexAttrImpl_GetNameInternal(JNIEnv *env, nsIDOMAttr* attr){
	if(IS_NULL(env))env=JRex_GetEnv(0);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (attr){
		nsEmbedString retString;
		rv = attr->GetName(retString);
		JREX_LOGLN("JRexAttrImpl_GetNameInternal()--> **** GetName rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexAttrImpl_GetOwnerElementInternal(JNIEnv *env, nsIDOMAttr* attr){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (attr){
		nsCOMPtr<nsIDOMElement> tmpEle;
		rv = attr->GetOwnerElement(getter_AddRefs(tmpEle));
		JREX_LOGLN("JRexAttrImpl_GetOwnerElementInternal()--> **** GetOwnerElement rv<"<<rv<<"> ****")
		if(tmpEle)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEle.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexAttrImpl_GetValueInternal(JNIEnv *env, nsIDOMAttr* attr){
	if(IS_NULL(env))env=JRex_GetEnv(0);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (attr){
		nsEmbedString retString;
		rv = attr->GetValue(retString);
		JREX_LOGLN("JRexAttrImpl_GetValueInternal()--> **** GetValue rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexAttrImpl_SetValueInternal(JNIEnv *env, nsIDOMAttr* attr, PRUnichar* value){

	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (attr){
		nsEmbedString tvalue(value);
		rv = attr->SetValue(tvalue);
		JREX_LOGLN("JRexAttrImpl_SetValueInternal()--> **** SetValue rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexAttrImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexAttrImpl_GetName
  (JNIEnv * env, jobject jattr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMAttr* thisAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jattr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetName()--> **** thisAttr <"<<thisAttr<<"> ****")
	if(IS_NULL(thisAttr)){
		ThrowJRexException(env, "GetName()--> **** thisAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetName()--> **** IN EVT Q THREAD ****")
		jrv=JRexAttrImpl_GetNameInternal(env, thisAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisAttr, JREX_GET_NAME, nsnull, PR_TRUE,
						HandleJRexAttrEvent, DestroyJRexAttrEvent, (void**)&jrv);
		JREX_LOGLN("GetName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetName()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetName()--> **** GetName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetName Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexAttrImpl
 * Method:    GetOwnerElement
 * Signature: ()Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexAttrImpl_GetOwnerElement
  (JNIEnv * env, jobject jattr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMAttr* thisAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jattr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetOwnerElement()--> **** thisAttr <"<<thisAttr<<"> ****")
	if(IS_NULL(thisAttr)){
		ThrowJRexException(env, "GetOwnerElement()--> **** thisAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetOwnerElement()--> **** IN EVT Q THREAD ****")
		jrv=JRexAttrImpl_GetOwnerElementInternal(env, thisAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisAttr, JREX_OWNER_ELEMENT, nsnull, PR_TRUE,
						HandleJRexAttrEvent, DestroyJRexAttrEvent, (void**)&jrv);
		JREX_LOGLN("GetOwnerElement()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetOwnerElement()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetOwnerElement()--> **** GetOwnerElement NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetOwnerElement Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexAttrImpl
 * Method:    GetSpecified
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexAttrImpl_GetSpecified
  (JNIEnv * env, jobject jattr){
	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMAttr* thisAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jattr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetSpecified()--> **** thisAttr <"<<thisAttr<<"> ****")
	if(IS_NULL(thisAttr)){
		ThrowJRexException(env, "GetSpecified()--> **** thisAttr DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool retBool = PR_FALSE;
	nsresult rv = thisAttr->GetSpecified(&retBool);
	JREX_LOGLN("GetSpecified()--> **** GetSpecified rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetSpecified()--> **** GetSpecified NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetSpecified Failed ****",rv);
		return JNI_FALSE;
	}
	return retBool==PR_FALSE?JNI_FALSE:JNI_TRUE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexAttrImpl
 * Method:    GetValue
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexAttrImpl_GetValue
  (JNIEnv * env, jobject jattr){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMAttr* thisAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jattr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetValue()--> **** thisAttr <"<<thisAttr<<"> ****")
	if(IS_NULL(thisAttr)){
		ThrowJRexException(env, "GetValue()--> **** thisAttr DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetValue()--> **** IN EVT Q THREAD ****")
		jrv=JRexAttrImpl_GetValueInternal(env, thisAttr);
	}else{
		nsresult rv=ExecInEventQDOM(thisAttr, JREX_GET_VALUE, nsnull, PR_TRUE,
						HandleJRexAttrEvent, DestroyJRexAttrEvent, (void**)&jrv);
		JREX_LOGLN("GetValue()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetValue()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetValue()--> **** GetValue NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetValue Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexAttrImpl
 * Method:    SetValue
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexAttrImpl_SetValue
  (JNIEnv * env, jobject jattr, jstring jvalue){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMAttr* thisAttr=(nsIDOMAttr*)NS_INT32_TO_PTR(env->GetIntField(jattr, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetValue()--> **** thisAttr <"<<thisAttr<<"> ****")
	if(IS_NULL(thisAttr)){
		ThrowJRexException(env, "SetValue()--> **** thisAttr DOES NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* value=nsnull;
	JSTR_TO_NEW_PRUNI(env, jvalue, value);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetValue()--> **** IN EVT Q THREAD ****")
		jrv=JRexAttrImpl_SetValueInternal(env, thisAttr, value);
	}else{
		nsresult rv=ExecInEventQDOM(thisAttr, JREX_SET_VALUE, (void*)value, PR_TRUE,
						HandleJRexAttrEvent, DestroyJRexAttrEvent, (void**)&jrv);
		JREX_LOGLN("SetValue()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetValue()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetValue()--> **** SetValue DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetValue()--> **** SetValue NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetValue Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexAttrEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexAttrEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMAttr> attr(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexAttrEvent JREX_GET_NAME EVENT!!!****")
			return (void*)JRexAttrImpl_GetNameInternal(nsnull, attr.get());
		}
		case JREX_OWNER_ELEMENT:
		{
			JREX_LOGLN("HandleJRexAttrEvent JREX_OWNER_ELEMENT EVENT!!!****")
			return (void*)JRexAttrImpl_GetOwnerElementInternal(nsnull, attr.get());
		}
		case JREX_GET_VALUE:
		{
			JREX_LOGLN("HandleJRexAttrEvent JREX_GET_VALUE EVENT!!!****")
			return (void*)JRexAttrImpl_GetValueInternal(nsnull, attr.get());
		}
		case JREX_SET_VALUE:
		{
			JREX_LOGLN("HandleJRexAttrEvent JREX_SET_VALUE EVENT!!!****")
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexAttrImpl_SetValueInternal(nsnull, attr.get(), value);
		}
		default:
		{
			JREX_LOGLN("HandleJRexAttrEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexAttrEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexAttrEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexAttrEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

