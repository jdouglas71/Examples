/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 *   Rich Giuli <richard.giuli@sri.com>
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

#include "org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl.h"
#include "JRexLiveConnectSession.h"
#include "JRex_JNI_Util.h"

using namespace JREX_LIVECONNECT;
using namespace JREX_JNI_UTIL;

jfieldID  JRexLiveConnectFields::peerID;
jfieldID  JRexLiveConnectFields::sessionID;
jmethodID JRexLiveConnectFields::getSessionID;
jmethodID JRexLiveConnectFields::jrexjsobject_initID;
jclass JRexLiveConnectFields::lcimpl_clazz;
jclass JRexLiveConnectFields::jrexjsobject_clazz;
jfieldID  JRexLiveConnectFields::jsobjSessionFieldID;
jfieldID  JRexLiveConnectFields::jsobjInternalFieldID;
jclass JRexLiveConnectFields::iNativeJSObject_clazz;
jmethodID JRexLiveConnectFields::jsObjectGetMember;
jmethodID JRexLiveConnectFields::jsObjectGetSlot;
jmethodID JRexLiveConnectFields::jsObjectSetMember;
jmethodID JRexLiveConnectFields::jsObjectSetSlot;
jmethodID JRexLiveConnectFields::jsObjectRemoveMember;
jmethodID JRexLiveConnectFields::jsObjectCall;
jmethodID JRexLiveConnectFields::jsObjectEval;
jmethodID JRexLiveConnectFields::jsObjectToString;
jmethodID JRexLiveConnectFields::jsObjectFinalize;
jmethodID JRexLiveConnectFields::jsObjectEquals;

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
    JRexLiveConnectFields::lcimpl_clazz	= (jclass)env->NewGlobalRef(env->FindClass(LC_SESSION_CLASS_NAME));
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** lcimpl_clazz<"<<JRexLiveConnectFields::lcimpl_clazz<<"> ****")
    JRexLiveConnectFields::jrexjsobject_clazz	= (jclass)env->NewGlobalRef(env->FindClass(JREX_JS_OBJECT_CLASS_NAME));
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jrexjsobject_clazz<"<<JRexLiveConnectFields::jrexjsobject_clazz<<"> ****")
    JRexLiveConnectFields::peerID	= env->GetFieldID(cls, "jrexPeer", "I");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** peerID<"<<JRexLiveConnectFields::peerID<<"> ****")
    JRexLiveConnectFields::sessionID	= env->GetFieldID(cls, "sessionID", "I");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** sessionID<"<<JRexLiveConnectFields::sessionID<<"> ****")
    JRexLiveConnectFields::getSessionID	= env->GetMethodID(cls, "getSessionID", "()I");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** getSessionID<"<<JRexLiveConnectFields::getSessionID<<"> ****")
    JRexLiveConnectFields::jrexjsobject_initID	= env->GetStaticMethodID(JRexLiveConnectFields::jrexjsobject_clazz, 
	                                                        "newJRexJSObject", "(II)Lorg/mozilla/jrex/liveconnect/JRexJSObject;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jrexjsobject_initID<"<<JRexLiveConnectFields::jrexjsobject_initID<<"> ****")
	JRexLiveConnectFields::jsobjSessionFieldID = env->GetFieldID(JRexLiveConnectFields::jrexjsobject_clazz, "jrexLCSession", "I");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsobjSessionFieldID<"<<JRexLiveConnectFields::jsobjSessionFieldID<<"> ****")
	JRexLiveConnectFields::jsobjInternalFieldID = env->GetFieldID(JRexLiveConnectFields::jrexjsobject_clazz, "internal", "I");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsobjInternalFieldID<"<<JRexLiveConnectFields::jsobjInternalFieldID<<"> ****")

    JRexLiveConnectFields::iNativeJSObject_clazz	= (jclass)env->NewGlobalRef(env->FindClass(INATIVE_JS_OBJECT_CLASS_NAME));
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** iNativeJSObject_clazz<"<<JRexLiveConnectFields::iNativeJSObject_clazz<<"> ****")
    JRexLiveConnectFields::jsObjectGetMember	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectGetMember", 
	                                                               "(Ljava/lang/String;)Ljava/lang/Object;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectGetMember<"<<JRexLiveConnectFields::jsObjectGetMember<<"> ****")
    JRexLiveConnectFields::jsObjectGetSlot	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectGetSlot", 
	                                                               "(I)Ljava/lang/Object;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectGetSlot<"<<JRexLiveConnectFields::jsObjectGetSlot<<"> ****")
    JRexLiveConnectFields::jsObjectSetMember	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectSetMember", 
	                                                               "(Ljava/lang/String;Ljava/lang/Object;)V");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectSetMember<"<<JRexLiveConnectFields::jsObjectSetMember<<"> ****")
    JRexLiveConnectFields::jsObjectSetSlot	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectSetSlot", 
	                                                               "(ILjava/lang/Object;)V");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectSetSlot<"<<JRexLiveConnectFields::jsObjectSetSlot<<"> ****")
    JRexLiveConnectFields::jsObjectRemoveMember	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectRemoveMember", 
	                                                               "(Ljava/lang/String;)V");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectRemoveMember<"<<JRexLiveConnectFields::jsObjectRemoveMember<<"> ****")
    JRexLiveConnectFields::jsObjectCall	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectCall", 
	                                                               "(Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectCall<"<<JRexLiveConnectFields::jsObjectCall<<"> ****")
    JRexLiveConnectFields::jsObjectEval	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectEval", 
	                                                               "(Ljava/lang/String;)Ljava/lang/Object;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectEval<"<<JRexLiveConnectFields::jsObjectEval<<"> ****")
    JRexLiveConnectFields::jsObjectToString	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectToString", 
	                                                               "()Ljava/lang/String;");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectToString<"<<JRexLiveConnectFields::jsObjectToString<<"> ****")
    JRexLiveConnectFields::jsObjectFinalize	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectFinalize", 
	                                                               "()V");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectFinalize<"<<JRexLiveConnectFields::jsObjectFinalize<<"> ****")
    JRexLiveConnectFields::jsObjectEquals	= env->GetMethodID(JRexLiveConnectFields::iNativeJSObject_clazz, "JSObjectEquals", 
	                                                               "(Ljava/lang/Object;)Z");
    JREX_LOGLN("JRexLiveConnectSessionImpl_initIDs()--> **** jsObjectEquals<"<<JRexLiveConnectFields::jsObjectEquals<<"> ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    Init
 * Signature: (Z)I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_Init
  (JNIEnv *env, jobject lcSession, jboolean useRootDocShell) {
    jint ret = 0;
	PRBool pr_useRootDocShell = (useRootDocShell == JNI_TRUE ? PR_TRUE : PR_FALSE);
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::peerID));
	JREX_LOGLN("LiveConnectSession_Init()--> **** JRexWindow <"<<window<<"> pr_useRootDocShell<"<<pr_useRootDocShell<<"> ****")
	if(IS_NULL(window)
			|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** LiveConnectSession_Init()-->YOU DO NOT EXIST!!! ****",0);
        return ret;
	}
    JRexLiveConnectSession *session = new JRexLiveConnectSession(lcSession, window, pr_useRootDocShell);
    if (IS_NULL(session)) {
		ThrowJRexException(env, "**** LiveConnectSession_Init()-->FAILED TO CREATE JRexLiveConnectSession!!! ****",0);
        return ret;
    }
    nsresult rv = session->Init(env);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_Init()-->  Failed to init JRexLiveConnectSessionImpl ****",rv);
        return ret;
    }
    ret = (jint)NS_PTR_TO_INT32(session);
    JREX_CATCH(env)
	JREX_LOGLN("LiveConnectSession_Init()--> **** ret<"<<ret<<"> ****")
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    StartupLiveConnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_StartupLiveConnect
  (JNIEnv *env, jobject lcSession) {
	JREX_TRY
	JRexLiveConnectSession *session=(JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
    nsresult rv = session->StartupLiveConnect(env);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_StartupLiveConnect()-->  Failed to startup live connect ****",rv);
        return;
    }
	JREX_LOGLN("LiveConnectSession_StartupLiveConnect()--> **** DONE ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    InvokeStringMethod
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_InvokeStringMethod
  (JNIEnv *env, jobject lcSession, jstring functionName, jstring arg) {
	JREX_TRY
	JRexLiveConnectSession *session=(JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
	char *ret = NULL;
	jboolean isFNameCopy=JNI_FALSE;
	const char* functionName_c = env->GetStringUTFChars(functionName,&isFNameCopy);
	JREX_LOGLN("LiveConnectSession_InvokeStringMethod()--> **** functionName_c<"<<(PRUint32)functionName_c<<"> isFNameCopy<"<<(isFNameCopy==JNI_TRUE)<<"> ***")
	jboolean isArgCopy=JNI_FALSE;
	const char* arg_c = env->GetStringUTFChars(arg,&isArgCopy);
	JREX_LOGLN("LiveConnectSession_invokeStringMethod()--> **** arg_c<"<<(PRUint32)arg_c<<"> isArgCopy<"<<(isArgCopy==JNI_TRUE)<<"> ***")
	nsresult rv = session->InvokeStringJavascriptMethod(env, functionName_c, arg_c, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_InvokeStringMethod()-->  Failed to invoke javascript method ****",rv);
        return NULL;
    }
	env->ReleaseStringUTFChars(functionName,functionName_c);
	env->ReleaseStringUTFChars(arg,arg_c);
	if (NOT_NULL(ret)) {
        JREX_LOGLN("LiveConnectSession_InvokeStringMethod()--> *** ret <"<<ret<<"> ***")
        return env->NewStringUTF(ret);
    } else {
        JREX_LOGLN_ERR("LiveConnectSession_InvokeStringMethod()--> *** NO RETURN VALUE RECEIVED FROM INVOCATION ***")
        return NULL;
    }
    JREX_CATCH(env)
    return NULL;
}


/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    EvalUntrusted
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_EvalUntrusted
  (JNIEnv *env, jobject lcSession, jstring jscript) {
	JREX_TRY
	JRexLiveConnectSession *session=(JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
	jboolean isScriptCopy=JNI_FALSE;
    const jchar *script_chars = env->GetStringChars(jscript, &isScriptCopy);
    if (!script_chars) {
		ThrowJRexException(env, "**** LiveConnectSession_EvalUntrusted()-->  Unable to get jchars from script string ****",NS_ERROR_UNEXPECTED);
        return NULL;
    }
	JREX_LOGLN("LiveConnectSession_EvalUntrusted()--> **** script_chars<"<<script_chars<<"> isScriptCopy<"<<(isScriptCopy==JNI_TRUE)<<"> ***")
    jint script_chars_length = env->GetStringLength(jscript);
	jchar *retStr;
	size_t retLength;
	nsresult rv = session->EvalScript(env, script_chars, script_chars_length, &retStr, &retLength);
    JREX_LOGLN("LiveConnectSession_EvalUntrusted()--> *** retStr<"<<retStr<<"> retLength<"<<retLength<<"> ***")
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_EvalUntrusted()-->  Failed to evaluate javascript ****",rv);
        return NULL;
    }
    env->ReleaseStringChars(jscript, script_chars);
    jstring ret = env->NewString(retStr, retLength);
	if (NOT_NULL(ret)) {
        JREX_LOGLN("LiveConnectSession_EvalUntrusted()--> *** ret<"<<ret<<"> ***")
        return ret;
    } else {
        JREX_LOGLN_ERR("LiveConnectSession_EvalUntrusted()--> *** FAILED TO CREATE JAVA STRING ***")
        return NULL;
    }
    JREX_CATCH(env)
    return NULL;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    JS_GC
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_JS_1GC
  (JNIEnv *env, jobject lcSession){
	JREX_TRY
	JRexLiveConnectSession *session=(JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
	nsresult rv = session->jsGC(env);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_JS_GC()-->  Failed to invoke javascript garbage collection ****",rv);
    }
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl_Finalize
  (JNIEnv *env, jobject lcSession){

	JREX_TRY
	JRexLiveConnectSession *session=(JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
	if (NOT_NULL(session)) {
	    delete session;
	}
	JREX_CATCH(env)
}