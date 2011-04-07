/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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

#include "org_mozilla_jrex_navigation_WebNavigationImpl.h"
#include "org_mozilla_jrex_navigation_History.h"
#include "org_mozilla_jrex_navigation_HistoryEntry.h"
#include "JRex_JNI_Util.h"
#include "JRexWindow.h"
#include "JRexInputStream.h"
#include "JRexNavigation.h"
#include "JRexIncludes.h"

#if defined(JREX_DOM)
	#include "JRexDOMGlobals.h"
#endif

using namespace JREX_JNI_UTIL;

jmethodID JRexInputStream::closeMID;
jmethodID JRexInputStream::availableMID;
jmethodID JRexInputStream::readMID;

jclass JRexNavigationFields::hisCls;
jclass JRexNavigationFields::hisEntryCls;

jmethodID JRexNavigationFields::arryListAddID;
jmethodID JRexNavigationFields::hisCID;
jmethodID JRexNavigationFields::hisEntryCID;
jfieldID  JRexNavigationFields::hisListID;
jfieldID  JRexNavigationFields::hisMaxLenID;

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_initIDs
  (JNIEnv *env, jclass clazz){
	if(!gXpcomRunning)return;
	JREX_TRY
	if (env->EnsureLocalCapacity(2) < 0) {
		ThrowJRexException(env, "**** WebNavigationImpl_initIDs()-->  EnsureLocalCapacity Failed ****",0);
		return;
	}
	jclass tempcls = env->FindClass("java/io/InputStream");
	JRexInputStream::closeMID=env->GetMethodID(tempcls,"close", "()V");
	JREX_LOGLN("WebNavigationImpl_initIDs()--> **** closeMID <"<<JRexInputStream::closeMID<<"> ****")

	JRexInputStream::availableMID=env->GetMethodID(tempcls,"available", "()I");
	JREX_LOGLN("WebNavigationImpl_initIDs()--> **** availableMID <"<<JRexInputStream::availableMID<<"> ****")

	JRexInputStream::readMID=env->GetMethodID(tempcls,"read", "([BII)I");
	JREX_LOGLN("WebNavigationImpl_initIDs()--> **** readMID <"<<JRexInputStream::readMID<<"> ****")
	env->DeleteLocalRef(tempcls);
	JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_History_initIDs
  (JNIEnv *env, jclass clazz){
	if(!gXpcomRunning)return;
	JREX_TRY
	if (env->EnsureLocalCapacity(2) < 0) {
		ThrowJRexException(env, "**** History_initIDs()-->  EnsureLocalCapacity Failed ****",0);
		return;
	}
	JRexNavigationFields::hisCls=(jclass)env->NewGlobalRef(clazz);

	jclass tempcls = env->FindClass("java/util/ArrayList");
	JRexNavigationFields::arryListAddID=env->GetMethodID(tempcls,"add", "(Ljava/lang/Object;)Z");
	JREX_LOGLN("History_initIDs()--> **** arryListAddID <"<<JRexNavigationFields::arryListAddID<<"> ****")
	env->DeleteLocalRef(tempcls);

	JRexNavigationFields::hisCID=env->GetMethodID(clazz,"<init>", "()V");
	JREX_LOGLN("History_initIDs()--> **** hisCID <"<<JRexNavigationFields::hisCID<<"> ****")

	JRexNavigationFields::hisListID=env->GetFieldID(clazz, "list", "Ljava/util/ArrayList;");
	JREX_LOGLN("History_initIDs()--> **** hisListID <"<<JRexNavigationFields::hisListID<<"> ****")

	JRexNavigationFields::hisMaxLenID=env->GetFieldID(clazz, "maxLength", "I");
	JREX_LOGLN("History_initIDs()--> **** hisMaxLenID <"<<JRexNavigationFields::hisMaxLenID<<"> ****")
	JREX_CATCH(env)
}


JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_HistoryEntry_initIDs
  (JNIEnv *env, jclass clazz){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexNavigationFields::hisEntryCls=(jclass)env->NewGlobalRef(clazz);
	JRexNavigationFields::hisEntryCID=env->GetMethodID(clazz,"<init>", "(Ljava/lang/String;Ljava/lang/String;Z)V");
	JREX_LOGLN("HistoryEntry_initIDs()--> **** hisEntryCID <"<<JRexNavigationFields::hisEntryCID<<"> ****")
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    CanGoBack
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_CanGoBack
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("CanGoBack()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanGoBack()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->GetCanGoBack(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanGoBack()-->  GetCanGoBack Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    CanGoForward
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_CanGoForward
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("CanGoForward()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanGoForward()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->GetCanGoForward(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanGoForward()-->  GetCanGoForward Failed ****",rv);

	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GoBack
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GoBack
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GoBack()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GoBack()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	nsresult rv=window->GoBack();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GoBack()-->  GoBack Failed ****",rv);
	else
		return JNI_TRUE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GoForward
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GoForward
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GoForward()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GoForward()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	nsresult rv=window->GoForward();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GoForward()-->  GoForward Failed ****",rv);
	else
		return JNI_TRUE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GoToIndex
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GoToIndex
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jint index){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GoToIndex()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GoToIndex()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	nsresult rv=window->GotoIndex((PRInt32)index);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GoToIndex()-->  GoToIndex Failed ****",rv);
	else
		return JNI_TRUE;

  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    LoadURI
 * Signature: (ILjava/lang/String;ILorg/mozilla/JRexBrowser/NSURI;Lorg/mozilla/JRexBrowser/NSInputStream;Lorg/mozilla/JRexBrowser/NSInputStream;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_LoadURI
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jstring juri, jint loadFlags, jstring jrefUri, jobject postData, jobject headers){
	if(!gXpcomRunning)return;
	JREX_TRY
	JREX_LOGLN("LoadURI()--> **** juri <"<<juri<<"> loadFlags <"<<loadFlags<<"> jrefUri<"<<jrefUri<<"> postData<"<<postData<<"> headers<"<<headers<<"> ****")
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("LoadURI()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** LoadURI()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* uri=nsnull;
	JSTR_TO_NEW_PRUNI(env, juri, uri);
	PRUnichar* refUri=nsnull;
	JSTR_TO_NEW_PRUNI(env, jrefUri, refUri);

	nsIInputStream* postIn=NOT_NULL(postData)?new JRexInputStream(postData):nsnull;
	JREX_LOGLN("LoadURI()--> **** postIn <"<<postIn<<"> ***")
	nsIInputStream* headersIn=NOT_NULL(headers)?new JRexInputStream(headers):nsnull;
	JREX_LOGLN("LoadURI()--> **** headersIn <"<<headersIn<<"> ***")

	nsresult rv=window->LoadURI(uri,(PRUint32)loadFlags,refUri,postIn,headersIn);
	JREX_LOGLN("LoadURI()--> **** LoadURI rv <"<<rv<<"> ****")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** LoadURI()-->  LoadURI Failed ****",rv);
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    LoadStream
 * Signature: (Ljava/io/InputStream;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/Object;ZLorg/mozilla/jrex/navigation/HistoryEntry;Ljava/lang/String;Ljava/io/InputStream;Ljava/io/InputStream;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_LoadStream
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jobject jinStream, jstring juri, jstring jcontType,
  	jstring jcharset,jint jloadFlags, jstring jrefUri, jobject jowner, jboolean jinhherit,
  			jstring jtarget, jobject jpostStream, jobject jheaderStream){
	if(!gXpcomRunning)return;
	JREX_TRY
	JREX_LOGLN("LoadStream()--> **** jinStream <"<<jinStream<<"> juri <"<<juri<<"> jcontType <"
				<<jcontType<<"> jcharset <"<<jcharset<<"> jloadFlags <"<<jloadFlags<<"> jrefUri<"
				<<jrefUri<<"> jtarget <"<<jtarget<<"> jpostStream<"<<jpostStream<<"> jheaderStream<"<<jheaderStream<<"> ****")
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("LoadStream()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window) || IS_NULL(jinStream)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** LoadStream()--> jinStream/YOU DO NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* uri=nsnull;
	JSTR_TO_NEW_PRUNI(env, juri, uri);
	PRUnichar* refUri=nsnull;
	JSTR_TO_NEW_PRUNI(env, jrefUri, refUri);
	PRUnichar* contType=nsnull;
	JSTR_TO_NEW_PRUNI(env, jcontType, contType);
	PRUnichar* target=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtarget, target);
	PRUnichar* charset=nsnull;
	JSTR_TO_NEW_PRUNI(env, jcharset, charset);

	nsIInputStream* inStream=NOT_NULL(jinStream)?new JRexInputStream(jinStream):nsnull;
	JREX_LOGLN("LoadStream()--> **** inStream <"<<inStream<<"> ***")
	nsIInputStream* postStream=NOT_NULL(jpostStream)?new JRexInputStream(jpostStream):nsnull;
	JREX_LOGLN("LoadStream()--> **** postStream <"<<postStream<<"> ***")
	nsIInputStream* headerStream=NOT_NULL(jheaderStream)?new JRexInputStream(jheaderStream):nsnull;
	JREX_LOGLN("LoadStream()--> **** headerStream <"<<headerStream<<"> ***")

	nsresult rv=window->LoadStream(inStream, uri, contType, charset,(PRUint32)jloadFlags, refUri,
					nsnull,(jinhherit==JNI_TRUE?PR_TRUE:PR_FALSE), target, postStream, headerStream);
	JREX_LOGLN("LoadStream()--> **** LoadStream rv <"<<rv<<"> ****")
	if(NS_FAILED(rv))
		ThrowJRexException(env, "**** LoadStream()-->  LoadStream Failed ****",rv);
	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    OpenWindow
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_OpenWindow
  (JNIEnv *env, jobject navigObj,  jint jrexPeer, jshort type, jstring juri, jstring jreferrer, jstring jname, jstring jfeature){
	if(!gXpcomRunning)return;
	JREX_TRY
	JREX_LOGLN("OpenWindow()--> **** type <"<<type<<"> juri <"<<juri<<"> jname <"<<jname<<"> jfeature<"<<jfeature<<"> ****")
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("OpenWindow()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** OpenWindow()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	jboolean isUriCopy=JNI_FALSE;
	const char* uri=NOT_NULL(juri)?env->GetStringUTFChars(juri,&isUriCopy):nsnull;
	JREX_LOGLN("OpenWindow()--> **** uri<"<<(PRUint32)uri<<"> isUriCopy<"<<(isUriCopy==JNI_TRUE)<<"> ***")
	const char* referrer=NOT_NULL(jreferrer)?env->GetStringUTFChars(jreferrer,&isUriCopy):nsnull;
	JREX_LOGLN("OpenWindow()--> **** referrer<"<<(PRUint32)referrer<<"> isUriCopy<"<<(isUriCopy==JNI_TRUE)<<"> ***")
	const char* name=NOT_NULL(jname)?env->GetStringUTFChars(jname,&isUriCopy):nsnull;
	JREX_LOGLN("OpenWindow()--> **** name<"<<(PRUint32)name<<"> isUriCopy<"<<(isUriCopy==JNI_TRUE)<<"> ***")
	const char* feature=NOT_NULL(jfeature)?env->GetStringUTFChars(jfeature,&isUriCopy):nsnull;
	JREX_LOGLN("OpenWindow()--> **** feature<"<<(PRUint32)feature<<"> isUriCopy<"<<(isUriCopy==JNI_TRUE)<<"> ***")

	nsresult rv=window->OpenWindow(type,uri,referrer,name,feature);
	JREX_LOGLN("OpenWindow()--> **** rv <"<<rv<<"> ****")
	if(NOT_NULL(juri))
		env->ReleaseStringUTFChars(juri,uri);
	if(NOT_NULL(jreferrer))
		env->ReleaseStringUTFChars(jreferrer,referrer);
	if(NOT_NULL(jname))
		env->ReleaseStringUTFChars(jname,name);
	if(NOT_NULL(jfeature))
		env->ReleaseStringUTFChars(jfeature,feature);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** OpenWindow()-->  OpenWindow Failed ****",rv);
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    Reload
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_Reload
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jint reloadFlags){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("Reload()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Reload()-->YOU DO NOT EXIST!!! ****",0);
		return ;
	}
	nsresult rv=window->Reload((PRInt32)reloadFlags);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Reload()-->  Reload Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GoToAnchor
 * Signature: (ILjava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GoToAnchor
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jstring janchorName, jboolean jshouldScroll){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GoToAnchor()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GoToAnchor()-->YOU DO NOT EXIST!!! ****",0);
		return ;
	}
	PRUnichar* anchorName=nsnull;
	JSTR_TO_NEW_PRUNI(env, janchorName, anchorName);

	nsresult rv=window->GoToAnchor(anchorName, jshouldScroll?PR_TRUE:PR_FALSE);
	if(NS_FAILED(rv))
		ThrowJRexException(env, "**** GoToAnchor()-->  GoToAnchor Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GetContentString
 * Signature: (ILjava/lang/String;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GetContentString
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jstring jcontType, jint outFlag){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetContentString()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetContentString()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	PRUnichar* contType=nsnull;
	JSTR_TO_NEW_PRUNI(env, jcontType, contType);

	nsXPIDLString contentStr;
	nsresult rv=window->GetContentString(getter_Copies(contentStr), contType, (PRUint32)outFlag);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetContentString()-->  JRexWindow GetContentString Failed ****",rv);

	NS_STR_TO_JSTR_RET(env,contentStr)
  	JREX_CATCH(env)
  	return NULL;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    Stop
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_Stop
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jint stopFlags){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("Stop()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Stop()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Stop((PRInt32)stopFlags);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Stop()-->  Stop Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GetDocument
 * Signature: (I)Lorg/mozilla/JRexBrowser/NSDOMDocument;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GetDocument
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
#if defined(JREX_DOM)
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetDocument()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetDocument()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMDocument* mydoc=nsnull;//no nsCOMPtr since not thread-safe
    nsresult rv=window->GetDocument(&mydoc);
	JREX_LOGLN("GetDocument()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && mydoc){
		JREX_LOGLN("GetDocument()--> *** NOT_NULL mydoc ***")
		jobject jobj=JRexDOMGlobals::CreateNodeByType(env, mydoc,PR_FALSE);
		return jobj;
	}
	JREX_LOGLN("GetDocument()--> *** GetDocument Failed ***")
  	JREX_CATCH(env)
#endif
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GetCurrentURI
 * Signature: (I)Lorg/mozilla/JRexBrowser/NSURI;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GetCurrentURI
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetCurrentURI()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetCurrentURI()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}

	nsIURI* currUri=nsnull;
	nsresult rv =window->GetCurrentURI(&currUri);
	JREX_LOGLN("GetCurrentURI()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && currUri){
		JREX_LOGLN("GetCurrentURI()--> *** NOT_NULL currUri ***")
		nsEmbedCString spec;
		rv=currUri->GetSpec(spec);
		if(NS_SUCCEEDED(rv)){
			char* tempCurrUri=ToNewCString(spec);
			JREX_LOGLN("GetCurrentURI()--> *** tempCurrUri <"<<tempCurrUri<<"> ***")
			jstring jretStr=env->NewStringUTF(tempCurrUri);
			nsMemory::Free(tempCurrUri);
			return jretStr;
		}
		NS_IF_RELEASE(currUri);
	}else{
		JREX_LOGLN("GetCurrentURI()--> *** NULL currUri ***")
	}
	JREX_LOGLN("GetCurrentURI()--> *** GetCurrentURI Failed ***")
  	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GetReferringURI
 * Signature: (I)Lorg/mozilla/JRexBrowser/NSURI;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GetReferringURI
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetReferringURI()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetReferringURI()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}

	nsIURI* refUri=nsnull;
	nsresult rv =window->GetReferringURI(&refUri);
	JREX_LOGLN("GetReferringURI()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && refUri){
		JREX_LOGLN("GetReferringURI()--> *** NOT_NULL refUri ***")
		nsEmbedCString spec;
		rv=refUri->GetSpec(spec);
		if(NS_SUCCEEDED(rv)){
			char* tempRefUri=ToNewCString(spec);
			JREX_LOGLN("GetReferringURI()--> *** tempRefUri <"<<tempRefUri<<"> ***")
			jstring jretStr=env->NewStringUTF(tempRefUri);
			nsMemory::Free(tempRefUri);
			return jretStr;
		}
		NS_IF_RELEASE(refUri);
	}else{
		JREX_LOGLN("GetReferringURI()--> *** NULL refUri ***")
	}
	JREX_LOGLN("GetReferringURI()--> *** Failed ***")
  	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_navigation_WebNavigationImpl
 * Method:    GetSessionHistory
 * Signature: (I)Lorg/mozilla/JRexBrowser/SHistory;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_GetSessionHistory
  (JNIEnv *env, jobject navigObj, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetSessionHistory()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetSessionHistory()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}

	nsVoidArray *vArray=new nsVoidArray();
	if(IS_NULL(vArray)){
		ThrowJRexException(env, "**** GetSessionHistory()-->  nsVoidArray alloc Failed ****",0);
		return NULL;
	}

	PRInt32 maxLength	= 0;
	nsresult rv=window->GetSessionHistory(vArray,&maxLength);
	JREX_LOGLN("GetSessionHistory()--> **** window->GetSessionHistory rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		delete vArray;
		ThrowJRexException(env, "**** GetSessionHistory()-->  window->GetSessionHistory Failed ****",rv);
		return NULL;
	}
	JREX_LOGLN("GetSessionHistory()--> **** window->GetSessionHistory Done!!! maxLength<"<<maxLength<<"> ****")

	PRInt32 count=vArray->Count();
	JREX_LOGLN("GetSessionHistory()--> **** GetCount count<"<<count<<"> ****")
	if(count<1){
		delete vArray;
		return NULL;
	}

	if (env->EnsureLocalCapacity(count+3) < 0){
		delete vArray;
		ThrowJRexException(env, "**** GetSessionHistory()-->  EnsureLocalCapacity Failed ****",rv);
		return NULL;
	}
	JREX_LOGLN("GetSessionHistory()--> **** EnsureLocalCapacity Done!!! ****")


	jobject hisObj=env->NewObject(JRexNavigationFields::hisCls,JRexNavigationFields::hisCID);
	JNI_EXP_DESC_CLR("GetSessionHistory() NewObject hisObj Exception Occured")
	if(hisObj==NULL){
		delete vArray;
		ThrowJRexException(env, "**** GetSessionHistory()-->  hisObj Creation Failed ****",0);
		return NULL;
	}
	JREX_LOGLN("GetSessionHistory()--> **** History object creation Done!!! ****")

	env->SetIntField(hisObj, JRexNavigationFields::hisMaxLenID,(jint)maxLength);
	jobject lisObj=env->GetObjectField(hisObj,JRexNavigationFields::hisListID);
	JREX_LOGLN("GetSessionHistory()--> **** Got  lisObj<"<<lisObj<<"> ****")

	jstring juri=NULL;
	jstring jtitle=NULL;
	PRBool isSubFrame=PR_FALSE;

	while (vArray->Count()>0) {
		JRexWindow::HistoryEntry* myEntry = NS_REINTERPRET_CAST(JRexWindow::HistoryEntry*, vArray->ElementAt(0));
		if(NOT_NULL(myEntry->uri)){
			nsEmbedString tempUri(myEntry->uri);
			char* temp=ToNewUTF8String(tempUri);
			juri=env->NewStringUTF(temp);
			nsMemory::Free(temp);
			nsMemory::Free(myEntry->uri);
		}else
			juri=NULL;
		JREX_LOGLN("GetSessionHistory()--> *** juri<"<<juri<<"> ***")

		if(NOT_NULL(myEntry->title)){
			nsEmbedString tempTtl(myEntry->title);
			char* temp=ToNewUTF8String(tempTtl);
			jtitle=env->NewStringUTF(temp);
			nsMemory::Free(temp);
			nsMemory::Free(myEntry->title);
		}else
			jtitle=NULL;
		JREX_LOGLN("GetSessionHistory()--> *** jtitle<"<<jtitle<<"> ***")

		isSubFrame=myEntry->isSubFrame;
		JREX_LOGLN("GetSessionHistory()--> *** isSubFrame<"<<(isSubFrame==PR_TRUE)<<"> ***")

		jobject hisEntryObj=env->NewObject(JRexNavigationFields::hisEntryCls,JRexNavigationFields::hisEntryCID,juri,jtitle,(isSubFrame==PR_TRUE?JNI_TRUE:JNI_FALSE));
		JNI_EXP_DESC_CLR("GetSessionHistory() NewObject hisEntryObj Exception Occured")
		if(juri)env->DeleteLocalRef(juri);
		if(jtitle)env->DeleteLocalRef(jtitle);
		if(hisEntryObj!=NULL){
			jboolean added=env->CallBooleanMethod(lisObj,JRexNavigationFields::arryListAddID,hisEntryObj);
			JREX_LOGLN("GetSessionHistory()--> *** added<"<<(added==JNI_TRUE)<<"> ***")
		}
		PRBool removed=vArray->RemoveElementAt(0);
		JREX_LOGLN("GetSessionHistory()--> *** removed<"<<(removed==PR_TRUE)<<"> ***")
		delete myEntry;
		env->DeleteLocalRef(hisEntryObj);
		JREX_LOGLN("GetSessionHistory()--> *** DeleteLocalRef Done ***")
	}
	delete vArray;
	return hisObj;
  	JREX_CATCH(env)
  	return NULL;
}


JNIEXPORT void JNICALL Java_org_mozilla_jrex_navigation_WebNavigationImpl_SetSessionHistory
  (JNIEnv *env, jobject navigObj, jint jrexPeer, jobject his){
	if(!gXpcomRunning)return;
 }

