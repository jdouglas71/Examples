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


#include "org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLDocument
enum JRexHTMLDocumentEventTypes{	JREX_GET_TITLE=0U,
									JREX_SET_TITLE,
									JREX_GET_REFERRER,
									JREX_GET_DOMAIN,
									JREX_GET_URL,
									JREX_GET_BODY,
									JREX_SET_BODY,
									JREX_GET_IMAGES,
									JREX_GET_APPLETS,
									JREX_GET_LINKS,
									JREX_GET_FORMS,
									JREX_GET_ANCHORS,
									JREX_GET_COOKIE,
									JREX_SET_COOKIE,
									JREX_OPEN,
									JREX_CLOSE,
									JREX_WRITE,
									JREX_WRITELN,
									JREX_GET_ELEMENTS_BY_NAME};

static void* PR_CALLBACK HandleJRexHTMLDocumentEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLDocumentEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexHTMLDocumentImpl_GetElementsByNameInternal(JNIEnv *env, nsIDOMHTMLDocument* htmlDoc, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (htmlDoc){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		nsEmbedString tname(name);
		rv = htmlDoc->GetElementsByName(tname, getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexHTMLDocumentImpl_GetElementsByNameInternal()--> **** GetElementsByName rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetTitle
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetTitle
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_STRING_JNI(env , jhtmlDoc, HTMLDocument, GetTitle, JREX_GET_TITLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    SetTitle
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_SetTitle
  (JNIEnv *env, jobject jhtmlDoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlDoc, jvalue, HTMLDocument, SetTitle, JREX_SET_TITLE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetReferrer
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetReferrer
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_STRING_JNI(env , jhtmlDoc, HTMLDocument, GetReferrer, JREX_GET_REFERRER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetDomain
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetDomain
  (JNIEnv *env, jobject jhtmlDoc){
	  GET_DOM_STRING_JNI(env , jhtmlDoc, HTMLDocument, GetDomain, JREX_GET_DOMAIN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetURL
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetURL
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_STRING_JNI(env , jhtmlDoc, HTMLDocument, GetURL, JREX_GET_URL, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetBody
 * Signature: ()Lorg/w3c/dom/html2/HTMLElement;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetBody
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_ELE_JNI(env, jhtmlDoc, HTMLDocument, HTMLElement, GetBody, JREX_GET_BODY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    SetBody
 * Signature: (Lorg/w3c/dom/html2/HTMLElement;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_SetBody
  (JNIEnv *env, jobject jhtmlDoc, jobject jhtmlEle){
	SET_DOM_HTML_ELE_JNI(env , jhtmlDoc, HTMLDocument, jhtmlEle, HTMLElement, SetBody, JREX_SET_BODY, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetImages
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetImages
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_COL_JNI(env , jhtmlDoc, HTMLDocument, GetImages, JREX_GET_IMAGES, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetApplets
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetApplets
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_COL_JNI(env , jhtmlDoc, HTMLDocument, GetApplets, JREX_GET_APPLETS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetLinks
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetLinks
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_COL_JNI(env , jhtmlDoc, HTMLDocument, GetLinks, JREX_GET_LINKS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetForms
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetForms
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_COL_JNI(env , jhtmlDoc, HTMLDocument, GetForms, JREX_GET_FORMS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetAnchors
 * Signature: ()Lorg/w3c/dom/html2/HTMLCollection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetAnchors
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_HTML_COL_JNI(env , jhtmlDoc, HTMLDocument, GetAnchors, JREX_GET_ANCHORS, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetCookie
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetCookie
  (JNIEnv *env, jobject jhtmlDoc){
	GET_DOM_STRING_JNI(env , jhtmlDoc, HTMLDocument, GetCookie, JREX_GET_COOKIE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    SetCookie
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_SetCookie
  (JNIEnv *env, jobject jhtmlDoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlDoc, jvalue, HTMLDocument, SetCookie, JREX_SET_COOKIE, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    Open
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_Open
  (JNIEnv *env, jobject jhtmlDoc){
	CALL_DOM_JNI(env , jhtmlDoc, HTMLDocument, Open, JREX_OPEN, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    Close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_Close
  (JNIEnv *env, jobject jhtmlDoc){
	CALL_DOM_JNI(env , jhtmlDoc, HTMLDocument, Close, JREX_CLOSE, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    Write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_Write
  (JNIEnv *env, jobject jhtmlDoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlDoc, jvalue, HTMLDocument, Write, JREX_WRITE, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    Writeln
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_Writeln
  (JNIEnv *env, jobject jhtmlDoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlDoc, jvalue, HTMLDocument, Writeln, JREX_WRITELN, JRexDOMGlobals::nodePeerID, PR_TRUE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl
 * Method:    GetElementsByName
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl_GetElementsByName
  (JNIEnv *env, jobject jhtmlDoc, jstring jvalue){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMHTMLDocument* thisDoc=(nsIDOMHTMLDocument*)NS_INT32_TO_PTR(env->GetIntField(jhtmlDoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementsByName()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetElementsByName()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jvalue)){
		JREX_LOGLN("GetElementsByName()--> **** jvalue is NULL ****")
		return NULL;
	}

	PRUnichar* value=nsnull;
	JSTR_TO_NEW_PRUNI(env, jvalue, value);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementsByName()--> **** IN EVT Q THREAD ****")
		jrv=JRexHTMLDocumentImpl_GetElementsByNameInternal(env, thisDoc, value);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_ELEMENTS_BY_NAME, (void*)value, PR_TRUE,
						HandleJRexHTMLDocumentEvent, DestroyJRexHTMLDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetElementsByName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementsByName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetElementsByName()--> **** GetElementsByName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementsByName Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}


void* PR_CALLBACK HandleJRexHTMLDocumentEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLDocumentEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLDocument> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_TITLE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_TITLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetTitle, jrv)
			return (void*)jrv;
		}
		case JREX_SET_TITLE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_SET_TITLE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetTitle, jrv)
			return (void*)jrv;

		}
		case JREX_GET_REFERRER:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_REFERRER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetReferrer, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DOMAIN:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_DOMAIN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetDomain, jrv)
			return (void*)jrv;
		}
		case JREX_GET_URL:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_URL EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetURL, jrv)
			return (void*)jrv;
		}
		case JREX_GET_BODY:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_BODY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_ELE_EQT(HTMLElement, NULL, ele.get(), GetBody, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BODY:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_SET_BODY EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsIDOMHTMLElement* value = NS_REINTERPRET_CAST(nsIDOMHTMLElement*, event->eventData);
			SET_DOM_HTML_ELE_EQT(value, ele.get(), SetBody, jrv)
			return (void*)jrv;
		}
		case JREX_GET_IMAGES:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_IMAGES EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetImages, jrv)
			return (void*)jrv;
		}
		case JREX_GET_APPLETS:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_APPLETS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetApplets, jrv)
			return (void*)jrv;
		}
		case JREX_GET_LINKS:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_LINKS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetLinks, jrv)
			return (void*)jrv;
		}
		case JREX_GET_FORMS:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_FORMS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetForms, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ANCHORS:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_ANCHORS EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_HTML_COL_EQT(NULL, ele.get(), GetAnchors, jrv)
			return (void*)jrv;
		}
		case JREX_GET_COOKIE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_COOKIE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCookie, jrv)
			return (void*)jrv;
		}
		case JREX_SET_COOKIE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_SET_COOKIE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCookie, jrv)
			return (void*)jrv;

		}
		case JREX_OPEN:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_OPEN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Open, jrv)
			return (void*)jrv;

		}
		case JREX_CLOSE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_CLOSE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(ele.get(), Close, jrv)
			return (void*)jrv;

		}
		case JREX_WRITE:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_WRITE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), Write, jrv)
			return (void*)jrv;

		}
		case JREX_WRITELN:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_WRITELN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), Writeln, jrv)
			return (void*)jrv;

		}
		case JREX_GET_ELEMENTS_BY_NAME:
		{

			JREX_LOGLN("HandleJRexHTMLDocumentEvent JREX_GET_ELEMENTS_BY_NAME EVENT!!!****")

			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexHTMLDocumentImpl_GetElementsByNameInternal(nsnull, ele.get(), name);
		}

		default:
		{
			JREX_LOGLN("HandleJRexHTMLDocumentEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLDocumentEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLDocumentEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLDocumentEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
