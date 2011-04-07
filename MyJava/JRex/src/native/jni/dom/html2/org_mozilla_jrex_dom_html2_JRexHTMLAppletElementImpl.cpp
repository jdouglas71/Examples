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


#include "org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexHTMLAppletElement
enum JRexHTMLAppletElementEventTypes{	JREX_GET_ALIGN=0U,
										JREX_SET_ALIGN,
										JREX_GET_ALT,
										JREX_SET_ALT,
										JREX_GET_ARCHIVE,
										JREX_SET_ARCHIVE,
										JREX_GET_CODE,
										JREX_SET_CODE,
										JREX_GET_CODEBASE,
										JREX_SET_CODEBASE,
										JREX_GET_OBJECT,
										JREX_SET_OBJECT,
										JREX_GET_HEIGHT,
										JREX_SET_HEIGHT,
										JREX_GET_HSPACE,
										JREX_SET_HSPACE,
										JREX_GET_NAME,
										JREX_SET_NAME,
										JREX_GET_VSPACE,
										JREX_SET_VSPACE,
										JREX_GET_WIDTH,
										JREX_SET_WIDTH
										};

static void* PR_CALLBACK HandleJRexHTMLAppletElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLAppletElementEvent(PLEvent* aEvent);

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetAlign
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetAlt
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetAlt
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetAlt, JREX_GET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetAlt
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetAlt
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetAlt, JREX_SET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetArchive
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetArchive
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetArchive, JREX_GET_ARCHIVE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetArchive
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetArchive
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetArchive, JREX_SET_ARCHIVE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetCode
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetCode, JREX_GET_CODE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetCode
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetCode
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetCode, JREX_SET_CODE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetCodeBase
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetCodeBase
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetCodeBase, JREX_GET_CODEBASE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetCodeBase
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetCodeBase
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetCodeBase, JREX_SET_CODEBASE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetObject
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetObject
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetObject, JREX_GET_OBJECT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetObject
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetObject
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetObject, JREX_SET_OBJECT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetHeight
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetHeight
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetHeight, JREX_GET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetHeight
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetHeight
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetHeight, JREX_SET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetHspace
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetHspace
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLAppletElement, PRInt32, GetHspace, JREX_GET_HSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetHspace
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetHspace
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLAppletElement, SetHspace, JREX_SET_HSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetName
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetName
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetVspace
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetVspace
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_INT_JNI(env , jhtmlEle, HTMLAppletElement, PRInt32, GetVspace, JREX_GET_VSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetVspace
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetVspace
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){
	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLAppletElement, SetVspace, JREX_SET_VSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    GetWidth
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_GetWidth
  (JNIEnv *env, jobject jhtmlEle){
	GET_DOM_STRING_JNI(env , jhtmlEle, HTMLAppletElement, GetWidth, JREX_GET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl
 * Method:    SetWidth
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl_SetWidth
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){
	SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLAppletElement, SetWidth, JREX_SET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


void* PR_CALLBACK HandleJRexHTMLAppletElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLAppletElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLAppletElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_ALIGN EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_ALIGN EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_ALT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlt, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_ALT EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlt, jrv)
			return (void*)jrv;
		}
		case JREX_GET_ARCHIVE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_ARCHIVE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetArchive, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ARCHIVE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_ARCHIVE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetArchive, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CODE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_CODE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCode, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CODE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_CODE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCode, jrv)
			return (void*)jrv;
		}
		case JREX_GET_CODEBASE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_CODEBASE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetCodeBase, jrv)
			return (void*)jrv;
		}
		case JREX_SET_CODEBASE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_CODEBASE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetCodeBase, jrv)
			return (void*)jrv;
		}
		case JREX_GET_OBJECT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_OBJECT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetObject, jrv)
			return (void*)jrv;
		}
		case JREX_SET_OBJECT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_OBJECT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetObject, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_HSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetHspace, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_HSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetHspace, jrv)
			return (void*)jrv;
		}
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_VSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetVspace, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_VSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetVspace, jrv)
			return (void*)jrv;
		}
		case JREX_GET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_GET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetWidth, jrv)
			return (void*)jrv;
		}
		case JREX_SET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent JREX_SET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetWidth, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLAppletElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLAppletElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLAppletElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLAppletElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}