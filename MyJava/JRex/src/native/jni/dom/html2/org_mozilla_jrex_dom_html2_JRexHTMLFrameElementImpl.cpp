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


#include "org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLFrameElement
enum JRexHTMLFrameElementEventTypes{JREX_GET_FRAME_BORDER=0U,
									JREX_SET_FRAME_BORDER,
									JREX_GET_LONG_DESC,
									JREX_SET_LONG_DESC,
									JREX_GET_MARGIN_HEIGHT,
									JREX_SET_MARGIN_HEIGHT,
									JREX_GET_MARGIN_WIDTH,
									JREX_SET_MARGIN_WIDTH,
									JREX_GET_NAME,
									JREX_SET_NAME,
									JREX_GET_NO_RESIZE,
									JREX_SET_NO_RESIZE,
									JREX_GET_SCROLLING,
									JREX_SET_SCROLLING,
									JREX_GET_SRC,
									JREX_SET_SRC,
									JREX_GET_DOC};

static void* PR_CALLBACK HandleJRexHTMLFrameElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLFrameElementEvent(PLEvent* aEvent);


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLFrameElementImpl_GetContentDocumentInternal(JNIEnv *env, nsIDOMHTMLFrameElement* ele){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (ele){
		nsCOMPtr<nsIDOMDocument> tmpDoc;
		rv = ele->GetContentDocument(getter_AddRefs(tmpDoc));
		JREX_LOGLN("JRexHTMLFrameElementImpl_GetContentDocumentInternal()--> **** GetContentDocument rv<"<<rv<<"> ****")
		if(tmpDoc)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDoc.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetFrameBorder
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetFrameBorder
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetFrameBorder, JREX_GET_FRAME_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetFrameBorder
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetFrameBorder
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetFrameBorder, JREX_SET_FRAME_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetLongDesc
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetLongDesc
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetLongDesc, JREX_GET_LONG_DESC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetLongDesc
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetLongDesc
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetLongDesc, JREX_SET_LONG_DESC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetMarginHeight
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetMarginHeight
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetMarginHeight, JREX_GET_MARGIN_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetMarginHeight
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetMarginHeight
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetMarginHeight, JREX_SET_MARGIN_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetMarginWidth
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetMarginWidth
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetMarginWidth, JREX_GET_MARGIN_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetMarginWidth
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetMarginWidth
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetMarginWidth, JREX_SET_MARGIN_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetName
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetName
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetNoResize
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetNoResize
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLFrameElement, GetNoResize, JREX_GET_NO_RESIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetNoResize
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetNoResize
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetNoResize, JREX_SET_NO_RESIZE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetScrolling
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetScrolling
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetScrolling, JREX_GET_SCROLLING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetScrolling
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetScrolling
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetScrolling, JREX_SET_SCROLLING, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetSrc
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetSrc
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLFrameElement, GetSrc, JREX_GET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    SetSrc
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_SetSrc
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLFrameElement, SetSrc, JREX_SET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl
 * Method:    GetContentDocument
 * Signature: ()Lorg/w3c/dom/Document;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl_GetContentDocument
  (JNIEnv *env, jobject jhtmlEle){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLFrameElement* thisEle=(nsIDOMHTMLFrameElement*)NS_INT32_TO_PTR(env->GetIntField(jhtmlEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetContentDocument()--> **** thisEle <"<<thisEle<<"> ****")
	if(IS_NULL(thisEle)){
		ThrowJRexException(env, "GetContentDocument()--> **** thisEle DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetContentDocument()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLFrameElementImpl_GetContentDocumentInternal(env, thisEle);
	}else{
		nsresult rv=ExecInEventQDOM(thisEle, JREX_GET_DOC, nsnull, PR_TRUE, HandleJRexHTMLFrameElementEvent, DestroyJRexHTMLFrameElementEvent, (void**)&jrv);
		JREX_LOGLN("GetContentDocument()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetContentDocument()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetContentDocument()--> **** GetContentDocument NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetContentDocument Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


void* PR_CALLBACK HandleJRexHTMLFrameElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLFrameElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLFrameElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_FRAME_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_FRAME_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetFrameBorder, jrv)
			return (void*)jrv;
		}
		case JREX_SET_FRAME_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_FRAME_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetFrameBorder, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LONG_DESC:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_LONG_DESC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLongDesc, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LONG_DESC:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_LONG_DESC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLongDesc, jrv)
			return (void*)jrv;
		}
		case JREX_GET_MARGIN_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_MARGIN_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetMarginHeight, jrv)
			return (void*)jrv;
		}
		case JREX_SET_MARGIN_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_MARGIN_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetMarginHeight, jrv)
			return (void*)jrv;
		}
		case JREX_GET_MARGIN_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_MARGIN_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetMarginWidth, jrv)
			return (void*)jrv;
		}
		case JREX_SET_MARGIN_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_MARGIN_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetMarginWidth, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NO_RESIZE:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_NO_RESIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetNoResize, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NO_RESIZE:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_NO_RESIZE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetNoResize, jrv)
			return (void*)jrv;

		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SCROLLING:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_SCROLLING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetScrolling, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SCROLLING:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_SCROLLING EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetScrolling, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetSrc, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_SET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetSrc, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DOC:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent JREX_GET_DOC EVENT!!!****")

			return (void*)JRexHTMLFrameElementImpl_GetContentDocumentInternal(nsnull, ele.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLFrameElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLFrameElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLFrameElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLFrameElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}