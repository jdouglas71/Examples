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


#include "org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl.h"
#include "JRexDOMGlobals.h"

 enum JRexHTMLImageElementEventTypes{	JREX_GET_NAME=0U,
										JREX_SET_NAME,
										JREX_GET_ALIGN,
										JREX_SET_ALIGN,
										JREX_GET_ALT,
										JREX_SET_ALT,
										JREX_GET_BORDER,
										JREX_SET_BORDER,
										JREX_GET_HEIGHT,
										JREX_SET_HEIGHT,
										JREX_GET_HSPACE,
										JREX_SET_HSPACE,
										JREX_GET_IS_MAP,
										JREX_SET_IS_MAP,
										JREX_GET_LONG_DESC,
										JREX_SET_LONG_DESC,
										JREX_GET_SRC,
										JREX_SET_SRC,
										JREX_GET_USE_MAP,
										JREX_SET_USE_MAP,
										JREX_GET_VSPACE,
										JREX_SET_VSPACE,
										JREX_GET_WIDTH,
										JREX_SET_WIDTH};

static void* PR_CALLBACK HandleJRexHTMLImageElementEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexHTMLImageElementEvent(PLEvent* aEvent);

JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetName
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetName, JREX_GET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetAlign
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetAlign
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetAlign, JREX_GET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetAlt
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetAlt
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetAlt, JREX_GET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetBorder
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetBorder
 (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetBorder, JREX_GET_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetHeight
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_INT_JNI(env , jhtmlEle, HTMLImageElement,PRInt32, GetHeight, JREX_GET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetHspace
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetHspace
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_INT_JNI(env , jhtmlEle, HTMLImageElement,PRInt32, GetHspace, JREX_GET_HSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetIsMap
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetIsMap
  (JNIEnv *env, jobject jhtmlEle){

	  GET_DOM_BOOL_JNI(env , jhtmlEle, HTMLImageElement, GetIsMap, JREX_GET_IS_MAP, JRexDOMGlobals::nodePeerID, PR_FALSE)

}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetLongDesc
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetLongDesc
 (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetLongDesc, JREX_GET_LONG_DESC, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetSrc
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetSrc
   (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetSrc, JREX_GET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetUseMap
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetUseMap
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_STRING_JNI(env , jhtmlEle, HTMLImageElement, GetUseMap, JREX_GET_USE_MAP, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetVspace
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetVspace
  (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_INT_JNI(env , jhtmlEle, HTMLImageElement,PRInt32, GetVspace, JREX_GET_VSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    GetWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_GetWidth
   (JNIEnv *env, jobject jhtmlEle){

  GET_DOM_INT_JNI(env , jhtmlEle, HTMLImageElement,PRInt32, GetWidth, JREX_GET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
  }

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetAlign
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetAlign
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetAlign, JREX_SET_ALIGN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetAlt
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetAlt
 (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetAlt, JREX_SET_ALT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetBorder
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetBorder
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetBorder, JREX_SET_BORDER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}
/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetHeight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetHeight
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLImageElement, SetHeight, JREX_SET_HEIGHT, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetHspace
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetHspace
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLImageElement, SetHspace, JREX_SET_HSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetIsMap
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetIsMap
  (JNIEnv *env, jobject jhtmlEle, jboolean jvalue){

	SET_DOM_BOOL_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetIsMap, JREX_SET_IS_MAP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetLongDesc
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetLongDesc
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetLongDesc, JREX_SET_LONG_DESC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetName
 (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetName, JREX_SET_NAME, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetSrc
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetSrc
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetSrc, JREX_SET_SRC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetUseMap
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetUseMap
  (JNIEnv *env, jobject jhtmlEle, jstring jvalue){

	  SET_DOM_STRING_JNI(env , jhtmlEle, jvalue, HTMLImageElement, SetUseMap, JREX_SET_USE_MAP, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetVspace
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetVspace
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLImageElement, SetVspace, JREX_SET_VSPACE, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl
 * Method:    SetWidth
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl_SetWidth
  (JNIEnv *env, jobject jhtmlEle, jint jvalue){

	SET_DOM_INT_JNI(env , jhtmlEle, PRInt32, jvalue, HTMLImageElement, SetWidth, JREX_SET_WIDTH, JRexDOMGlobals::nodePeerID, PR_FALSE)
}



void* PR_CALLBACK HandleJRexHTMLImageElementEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexHTMLImageElementEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMHTMLImageElement> ele(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetName, jrv)
			return (void*)jrv;
		}
		case JREX_SET_NAME:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_NAME EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetName, jrv)
			return (void*)jrv;
		}

        case JREX_GET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlign, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALIGN:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_ALIGN EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlign, jrv)
			return (void*)jrv;
		}

        case JREX_GET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_ALT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetAlt, jrv)
			return (void*)jrv;
		}
		case JREX_SET_ALT:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_ALT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetAlt, jrv)
			return (void*)jrv;
		}
        case JREX_GET_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetBorder, jrv)
			return (void*)jrv;
		}
		case JREX_SET_BORDER:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_BORDER EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetBorder, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HEIGHT:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_HEIGHT EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetHeight, jrv)
			return (void*)jrv;
		}
		case JREX_GET_HSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_HSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetHspace, jrv)
			return (void*)jrv;
		}
		case JREX_SET_HSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_HSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetHspace, jrv)
			return (void*)jrv;
		}
		case JREX_GET_IS_MAP:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_IS_MAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(NULL, ele.get(), GetIsMap, jrv)
			return (void*)jrv;
		}
		case JREX_SET_IS_MAP:
		{
			JREX_LOGLN("HandleJRexHTMLSelectElementEvent JREX_SET_IS_MAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, ele.get(), SetIsMap, jrv)
			return (void*)jrv;

		}
		case JREX_GET_LONG_DESC:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_LONG_DESC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetLongDesc, jrv)
			return (void*)jrv;
		}
		case JREX_SET_LONG_DESC:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_LONG_DESC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetLongDesc, jrv)
			return (void*)jrv;
		}
		case JREX_GET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetSrc, jrv)
			return (void*)jrv;
		}
		case JREX_SET_SRC:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_SRC EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetSrc, jrv)
			return (void*)jrv;
		}
		case JREX_GET_USE_MAP:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_USE_MAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(NULL, ele.get(), GetUseMap, jrv)
			return (void*)jrv;
		}
		case JREX_SET_USE_MAP:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_USE_MAP EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, ele.get(), SetUseMap, jrv)
			return (void*)jrv;
		}
		case JREX_GET_VSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_VSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetVspace, jrv)
			return (void*)jrv;
		}
		case JREX_SET_VSPACE:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_VSPACE EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetVspace, jrv)
			return (void*)jrv;
		}
		case JREX_GET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_GET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_INT_EQT(NULL, ele.get(), PRInt32, GetWidth, jrv)
			return (void*)jrv;
		}
		case JREX_SET_WIDTH:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent JREX_SET_WIDTH EVENT!!!****")

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUint32 value = NS_REINTERPRET_CAST(PRUint32, event->eventData);
			SET_DOM_INT_EQT(value, ele.get(), SetWidth, jrv)
			return (void*)jrv;
		}
		default:
		{
			JREX_LOGLN("HandleJRexHTMLImageElementEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}

	JREX_LOGLN("HandleJRexHTMLImageElementEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexHTMLImageElementEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexHTMLImageElementEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}
