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
#include "JRexLiveConnectSession.h"

#include <string.h>
using namespace JREX_LIVECONNECT;
using namespace JREX_JNI_UTIL;


static JSJavaVM *           the_jsj_vm = NULL;
static nsHashtable          sThreadSessionHash(32, PR_TRUE); // thread-safe
static JRexLiveConnectSession * last_session;

#define DECL_CURRENT_THREAD_HASH_KEY(key) nsPRUint32Key key(NS_PTR_TO_INT32(PR_GetCurrentThread()));

PRBool JRexLiveConnectSession::sLCInited = PR_FALSE;

#define JREX_LOGLN_ERR_WITHP(err) JREX_LOGLN_ERR(err) \
          if (errp) *errp=err;

inline static void jrex_liveconnect_setThreadSession(JRexLiveConnectSession* session) {
	DECL_CURRENT_THREAD_HASH_KEY(key)
	sThreadSessionHash.Put(&key, (void*)session);
}

inline static JRexLiveConnectSession* jrex_liveconnect_getThreadSession() {
	DECL_CURRENT_THREAD_HASH_KEY(key)
	void* thread_session = sThreadSessionHash.Get(&key);
	if (NOT_NULL(thread_session)) {
		return (last_session = (JRexLiveConnectSession*)thread_session);
	} else {
		// TODO FIXME Sometimes a java wrapper will be created from javascript,
		// and we do not know what the session should be. This is a workaround.
		// Might be able to get it from the context in the JSObjectHandle...
		return last_session;
	}
}

inline static void jrex_liveconnect_removeThreadSession() {
	DECL_CURRENT_THREAD_HASH_KEY(key)
	sThreadSessionHash.Remove(&key);
}

inline static JRexLiveConnectSession* jrex_getSession(jobject hintAsObj, JNIEnv *env, char **errp, PRBool checkCache) {
	if (checkCache == PR_TRUE) {
		// Try and get the hashed session
		JRexLiveConnectSession* hashed_session = jrex_liveconnect_getThreadSession();
		if (hashed_session) {
			return hashed_session;
		}
	}

    if (IS_NULL(hintAsObj)) {
        JREX_LOGLN_ERR_WITHP("jrex_getSessionID()--> **** Hint is NULL ****");
        return NULL;
    }

    int sessionId = 0;
    if (env->IsInstanceOf(hintAsObj, JRexLiveConnectFields::lcimpl_clazz)) {
        JREX_LOGLN("jrex_getSessionID()--> **** Is lcimpl_clazz ****");
        sessionId = env->CallIntMethod(hintAsObj, JRexLiveConnectFields::getSessionID);
    } else if (env->IsInstanceOf(hintAsObj, JRexLiveConnectFields::jrexjsobject_clazz)) {
        JREX_LOGLN("jrex_getSessionID()--> **** Is jrexjsobject_clazz ****");
        jfieldID jsobject_jrexLCSession	= env->GetFieldID(JRexLiveConnectFields::jrexjsobject_clazz, "jrexLCSession", "I");
        sessionId = env->GetIntField(hintAsObj, jsobject_jrexLCSession);
    } else {
        JREX_LOGLN_ERR_WITHP("jrex_getSessionID()--> **** Hint is not an instance of JRexLiveConnectSessionImpl or JSObject ****");
        return NULL;
    }

    JNI_EXP_DESC_CLR("jrex_getSession() Exception Occured")

    if (sessionId) {
        JRexLiveConnectSession* theSession = (JRexLiveConnectSession *)NS_INT32_TO_PTR(sessionId);
		// Mark this session as the current in the hash...
		jrex_liveconnect_setThreadSession(theSession);
        return theSession;
    } else {
        JREX_LOGLN_ERR_WITHP("jrex_getSessionID()--> **** Failed to get sessionId ****");
		return NULL;
    }
}

JS_STATIC_DLL_CALLBACK(JSJavaThreadState*)
jrex_map_js_context_to_jsj_thread_impl(JSContext *cx, char **errp) {
    JREX_LOGLN("jrex_map_js_context_to_jsj_thread_impl()--> **** cx<"<<cx<<"> ****");
	JSJavaThreadState* thread_state = JSJ_AttachCurrentThreadToJava(the_jsj_vm, NULL, NULL);
    JREX_LOGLN("jrex_map_js_context_to_jsj_thread_impl()--> **** returning thread_state<"<<thread_state<<"> ****");
	return thread_state;
}

JS_STATIC_DLL_CALLBACK(JSContext*)
jrex_map_jsj_thread_to_js_context_impl(JSJavaThreadState *jsj_env,
                                     void *vhint,
                                     JNIEnv *env,
                                     char **errp) {
    JRexLiveConnectSession *session = jrex_getSession((jobject)vhint, env, errp, PR_TRUE);
    if (NOT_NULL(session)) {
        JREX_LOGLN("jrex_map_jsj_thread_to_js_context_impl()--> **** session<"<<session<<"> jscontext<"<<session->GetJSContext()<<"> ****");
        return session->GetJSContext();
    } else {
		return NULL;
    }
}

/* Trivial implementation of callback function */
JS_STATIC_DLL_CALLBACK(JSObject*)
jrex_map_java_object_to_js_object_impl(JNIEnv *env, void *vhint, char **errp) {
    JRexLiveConnectSession *session = jrex_getSession((jobject)vhint, env, errp, PR_TRUE);
    if (NOT_NULL(session)) {
        JREX_LOGLN("jrex_map_java_object_to_js_object_impl()--> **** session<"<<session<<"> globalObj<"<<session->GetGlobalJSObject()<<"> ****");
        return session->GetGlobalJSObject();
    } else {
        return NULL;
    }
}

JS_STATIC_DLL_CALLBACK(JSBool)
jrex_create_java_vm_impl(SystemJavaVM* *jvm, JNIEnv* *env, void* initargs) {
    JREX_LOGLN("jrex_default_create_java_vm_impl()--> **** I AM HERE ****");
    fflush(stdout);
    jint err;
    const char* user_classpath = (const char*)initargs;
    char* full_classpath = NULL;

    /* No Java VM supplied, so create our own */
    JDK1_1InitArgs vm_args;
    memset(&vm_args, 0, sizeof(vm_args));

    /* Magic constant indicates JRE version 1.1 */
    vm_args.version = JNI_VERSION_1_4;
    JNI_GetDefaultJavaVMInitArgs(&vm_args);

    /* Prepend the classpath argument to the default JVM classpath */
    if (user_classpath) {
#if defined(XP_UNIX) || defined(XP_BEOS) || defined(XP_MAC) || defined(XP_MACOSX)
        full_classpath = JS_smprintf("%s:%s", user_classpath, vm_args.classpath);
#else
        full_classpath = JS_smprintf("%s;%s", user_classpath, vm_args.classpath);
#endif
        if (!full_classpath) {
            JREX_LOGLN_ERR("jrex_default_create_java_vm_impl()--> **** full_classpath is NULL ****");
            return JS_FALSE;
        }
        JREX_LOGLN("jrex_default_create_java_vm_impl()--> **** full_classpath<"<<(PRUint32)full_classpath<<"> ****");
        vm_args.classpath = (char*)full_classpath;
    }

    err = JNI_CreateJavaVM((JavaVM**)jvm, (void**)env, &vm_args);
	if (err != 0) {
        JREX_LOGLN_ERR("jrex_default_create_java_vm_impl()--> **** LCShell: Failed to create Java VM: err<"<<err<<"> ****");
	}

    if (full_classpath)
        JS_smprintf_free(full_classpath);

    JREX_LOGLN("jrex_default_create_java_vm_impl()--> **** DONE, err<"<<(err != 0)<<"> ****");
    return err == 0;
}

JS_STATIC_DLL_CALLBACK(JSBool)
jrex_destroy_java_vm_impl(SystemJavaVM* jvm, JNIEnv* env) {
    JREX_LOGLN("jrex_destroy_java_vm_impl()--> **** I AM HERE ****");
    // Current mozilla impl does nothing. The JNIEnv is tied to the lifetime of threads,
    // so this method does nothing (see jvmmgr.cpp).
    return PR_TRUE;
}

JS_STATIC_DLL_CALLBACK(JNIEnv*)
jrex_attach_current_thread_impl(SystemJavaVM* jvm) {
    JREX_LOGLN("jrex_attach_current_thread_impl()--> **** I AM HERE ****");
    JNIEnv* env = JRex_GetEnv(0);
    JREX_LOGLN("jrex_attach_current_thread_impl()--> **** env<"<<env<<"> ****");
    if (IS_NULL(env)) {
        JREX_LOGLN_ERR("jrex_attach_current_thread_impl()--> **** RETURN JNIENV FROM AttachCurrentThread WAS NULL ****");
        return NULL;
    } else {
        return env;
    }
}

JS_STATIC_DLL_CALLBACK(JSBool)
jrex_detach_current_thread_impl(SystemJavaVM* jvm, JNIEnv* env) {
    JREX_LOGLN("jrex_detach_current_thread_impl()--> **** I AM HERE ****");
    JavaVM* java_vm = (JavaVM*)jvm;
    /* assert that env is the JNIEnv of the current thread */
    jint err = java_vm->DetachCurrentThread();
    JNI_EXP_DESC_CLR("jrex_detach_current_thread_impl() Exception Occured")
    return err == 0;
}

JS_STATIC_DLL_CALLBACK(SystemJavaVM*)
jrex_get_java_vm_impl(JNIEnv* env) {
    JREX_LOGLN("jrex_get_java_vm_impl()--> **** I AM HERE ****");
    JavaVM* java_vm = NULL;
    env->GetJavaVM(&java_vm);
    JNI_EXP_DESC_CLR("jrex_get_java_vm_impl() Exception Occured")
    return (SystemJavaVM*)java_vm;
}

// Copied from lcglue.cpp
JS_STATIC_DLL_CALLBACK(JSPrincipals*)
jrex_get_JSPrincipals_from_java_caller_impl(JNIEnv *pJNIEnv, JSContext *pJSContext,
               void  **ppNSIPrincipalArrayIN, int numPrincipals, void *pNSISecurityContext) {
    JREX_LOGLN("jrex_get_JSPrincipals_from_java_caller_impl()--> **** I AM HERE ****");
	nsresult rv;
	nsCOMPtr<nsIScriptSecurityManager> secMan = do_GetService(NS_SCRIPTSECURITYMANAGER_CONTRACTID, &rv);
	if (NS_FAILED(rv)) {
		JREX_LOGLN_ERR("StartupLiveConnectInternal()--> **** Failed to obtain nsIScriptSecurityManager, rv<"<<rv<<"> ****");
		return NULL;
	}
    nsCOMPtr<nsIPrincipal> principal;
    rv = secMan->GetPrincipalFromContext(pJSContext, getter_AddRefs(principal));
    if (NS_FAILED(rv)) {
        JREX_LOGLN_ERR("jrex_get_JSPrincipals_from_java_caller_impl()--> **** Failed to obtain nsIPrincipal, rv<"<<rv<<"> ****");
        return NULL;
    }

    JSPrincipals* jsprincipals = NULL;
#ifdef JREX_MOZ1_4
    principal->GetJSPrincipals(&jsprincipals);
#else
    principal->GetJSPrincipals(pJSContext, &jsprincipals);
#endif
    JREX_LOGLN("jrex_get_JSPrincipals_from_java_caller_impl()--> **** DONE, jsprincipals<"<<jsprincipals<<"> ****");
    return jsprincipals;
	return NULL;
}

// Copied from lcglue.cpp
JS_STATIC_DLL_CALLBACK(JSBool)
jrex_enter_js_from_java_impl(JNIEnv *env, char **errp,
                        void **pNSIPrincipaArray, int numPrincipals,
                        void *pNSISecurityContext,
                        void *java_applet_obj) {
    JREX_LOGLN("jrex_enter_js_from_java_impl()--> **** ret<true> ****");
	return PR_TRUE;
}

// Copied from lcglue.cpp
JS_STATIC_DLL_CALLBACK(void)
jrex_exit_js_impl(JNIEnv *env, JSContext *cx) {
    JREX_LOGLN("jrex_exit_js_impl()--> **** I AM HERE ****");
    // The main idea is to execute terminate function if have any;
    if (NOT_NULL(cx))
    {
#ifdef JREX_MOZ1_4
        nsISupports* supports = NS_REINTERPRET_CAST(nsIScriptContext*,
                                                    JS_GetContextPrivate(cx));
        nsCOMPtr<nsIScriptContext> scriptContext = do_QueryInterface(supports);
#else
        nsIScriptContext* scriptContext = GetScriptContextFromJSContext(cx);
#endif

        if (NOT_NULL(scriptContext))
        {
            scriptContext->ScriptEvaluated(PR_TRUE);
            JREX_LOGLN("jrex_exit_js_impl()--> **** Called ScriptEvaluated ****");
        }
    }
}

NS_IMETHODIMP GetJavaWrapper(JNIEnv* env,
				   jint browser_obj,
				   jobject* java_obj) {
    JREX_LOGLN("GetJavaWrapper()--> **** I AM HERE ****");

    if (IS_NULL(browser_obj) || IS_NULL(java_obj))
	    return NS_ERROR_NULL_POINTER;

    jmethodID njJSObject_JSObject = JRexLiveConnectFields::jrexjsobject_initID;

    if (!env->ExceptionCheck()) {
        jobject ret = env->CallStaticObjectMethod(JRexLiveConnectFields::jrexjsobject_clazz, njJSObject_JSObject,
          browser_obj, (jint)NS_PTR_TO_INT32(jrex_liveconnect_getThreadSession()));
		// The JNIEnv may be a global env, meaning the local reference must be deleted for garbage
		// collection to work.
		*java_obj = ret;
    }

    JNI_EXP_DESC_CLR("GetJavaWrapper() Exception Occured")

    if (IS_NULL(*java_obj)) {
        JREX_LOGLN_ERR("GetJavaWrapper()--> **** ERROR: Failed to create org/mozilla/jrex/liveconnect/JRexJSObject ****");
	    return NS_ERROR_NULL_POINTER;
    } else {
        return NS_OK;
    }
}

// Copied from lcglue.cpp
JS_STATIC_DLL_CALLBACK(jobject)
jrex_get_java_wrapper_impl(JNIEnv *pJNIEnv, jint a_jsobject) {
    jobject  pJSObjectWrapper = NULL;
    JREX_LOGLN("jrex_get_java_wrapper_impl()--> **** a_jsobject<"<<a_jsobject<<"> ****");
    nsresult rv = GetJavaWrapper(pJNIEnv, a_jsobject, &pJSObjectWrapper);
    if (NS_FAILED(rv)) {
        JREX_LOGLN_ERR("jrex_get_java_wrapper_impl()--> **** FAILED TO GET JAVA WRAPPER ****");
        return NULL;
    } else {
        JREX_LOGLN("jrex_get_java_wrapper_impl()--> **** pJSObjectWrapper<"<<pJSObjectWrapper<<"> ****");
        return pJSObjectWrapper;
    }
}

// Copied from lcglue.cpp
JS_STATIC_DLL_CALLBACK(jint)
jrex_unwrap_java_wrapper_impl(JNIEnv *pJNIEnv, jobject java_wrapper) {
    jint jsObjId = pJNIEnv->GetIntField(java_wrapper, JRexLiveConnectFields::jsobjInternalFieldID);
    JREX_LOGLN("jrex_unwrap_java_wrapper_impl()--> **** jsObjId<"<<jsObjId<<"> ****");
	// If the javawrapper obj is set, make sure the session hash is valid. This
	// is required because some jsj methods do not supply the hintAsObj when calling
	// these callbacks.
	// Note: the cache may be valid, but may need to be reset at this point, so just reset it...
	jrex_getSession(java_wrapper, pJNIEnv, NULL, PR_FALSE);
    return jsObjId;
}

JS_STATIC_DLL_CALLBACK(void)
error_print(const char *error_msg) {
    if (NOT_NULL(error_msg)) {
        JREX_LOGLN_ERR(error_msg);
    }
}

/* JRex implementations of callback functions */
JSJCallbacks jsj_jrex_callbacks = {
    jrex_map_jsj_thread_to_js_context_impl,
    jrex_map_js_context_to_jsj_thread_impl,
    jrex_map_java_object_to_js_object_impl,
    jrex_get_JSPrincipals_from_java_caller_impl,
    jrex_enter_js_from_java_impl,
    jrex_exit_js_impl,
    error_print,
    jrex_get_java_wrapper_impl,
    jrex_unwrap_java_wrapper_impl,
    jrex_create_java_vm_impl,
    jrex_destroy_java_vm_impl,
    jrex_attach_current_thread_impl,
    jrex_detach_current_thread_impl,
    jrex_get_java_vm_impl
};

JRexLiveConnectSession::JRexLiveConnectSession(jobject lcSession, JRexWindow *window, PRBool useRootDocShell) : mJRexWindow(window), mShouldUseRootDocShell(useRootDocShell) {

    JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
	JREX_LOGLN("JRexLiveConnectSession()--> **** env<"<<env<<"> ****")
        //BF - Pepper Computer: store the global ref to lcSession right away
    if(NOT_NULL(env) && NOT_NULL(lcSession))
        mLCSession = env->NewGlobalRef(lcSession);
	else{
		JREX_LOGLN("JRexLiveConnectSession()--> **** CREATION FAILED!!!!!!!!!****")
		throw NS_ERROR_NULL_POINTER;
	}

	JREX_LOGLN("JRexLiveConnectSession()--> **** mLCSession<"<<mLCSession<<"> ****")
}

NS_IMETHODIMP JRexLiveConnectSession::StartupLiveConnect(JNIEnv *env) {
    JREX_LOGLN("JRexLiveConnectSession::StartupLiveConnect()--> **** env<"<<env<<"> ****")
    if(IS_EQT)
        return StartupLiveConnectInternal();
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    if (eventData) {
        JREX_LOGLN("StartupLiveConnect()--> **** eventData Created ****")
        eventData->session = this;
        eventData->lcEventData = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,STARTUP_LIVECONNECT,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
        JREX_LOGLN("StartupLiveConnect()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("StartupLiveConnect()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::StartupLiveConnectInternal() {
    JavaVM *java_vm = JRex_GetVM();
    JREX_LOGLN("StartupLiveConnectInternal()--> **** java_vm<"<<java_vm<<"> ****");

    if (!JRexLiveConnectSession::sLCInited) {
        JSJ_Init(&jsj_jrex_callbacks);
        JRexLiveConnectSession::sLCInited = TRUE;
    }

    if (IS_NULL(the_jsj_vm)) {
        the_jsj_vm = JSJ_ConnectToJavaVM((SystemJavaVM*)java_vm, NULL);
        if (IS_NULL(the_jsj_vm)) {
            JREX_LOGLN_ERR("StartupLiveConnectInternal JSJ_JRexInit()--> **** Failed to get jsjvm from JSJ_ConnectToJavaVM  ****");
            return NS_ERROR_UNEXPECTED;
        }
        JREX_LOGLN("StartupLiveConnectInternal()--> **** the_jsj_vm<"<<the_jsj_vm<<"> ****");
    }

    if (!JSJ_InitJSContext(GetJSContext(), GetGlobalJSObject(), NULL)) {
        JREX_LOGLN_ERR("ERROR: StartupLiveConnectInternal()--> **** JSJ_InitJSContext failed ****");
        return NS_ERROR_UNEXPECTED;
    }
    // Note: The default js context is not set here. If this is done, the recursion depth for the
    // js thread state will be set to 1, and the liveconnect code will only allow one JSContext
    // per java thread. In order to support multiple JSContexts (As in a multithreaded app),
    // JSJ_SetDefaultJSContextForJavaThread is never called.
    // See jsj_EnterJava method in jsjs_utils.c for the recursion depth check.
    JREX_LOGLN("StartupLiveConnectInternal()--> **** Finished setting up LiveConnect ****");
    return NS_OK;
}

NS_IMETHODIMP JRexLiveConnectSession::Init(JNIEnv *env) {
    JREX_LOGLN("JRexLiveConnectSession::Init()--> **** env<"<<env<<"> ****")
    if(IS_EQT)
        return InitInternal();
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    if (eventData) {
        JREX_LOGLN("Init()--> **** eventData Created ****")
        eventData->session = this;
        eventData->lcEventData = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,INIT,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
        JREX_LOGLN("Init()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("Init()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::InitInternal() {
    JREX_LOGLN("JRexLiveConnectSession::Init()--> **** mLCSession<"<<mLCSession<<"> I AM HERE ****");

    nsCOMPtr<nsIDOMDocument> pIDOMDocument;
    nsresult rv = mJRexWindow->GetDocument(getter_AddRefs(pIDOMDocument));
    JREX_RETURN_IF_FAILED(rv,"JRexLiveConnectSession::Init()--> ****  Getting nsIDOMDocument")

    nsCOMPtr<nsIDocShell> pIDocShell;
	if (mShouldUseRootDocShell) {
		rv = mJRexWindow->GetRootDocShell(getter_AddRefs(pIDocShell));
	} else {
		rv = mJRexWindow->GetDocShell(getter_AddRefs(pIDocShell));
	}
    JREX_RETURN_IF_FAILED(rv,"JRexLiveConnectSession::Init()--> **** Getting nsIDocShell")

	// Try to query directly for it...
	nsCOMPtr<nsIScriptGlobalObject> global(do_GetInterface(pIDocShell,&rv));
	if (NS_FAILED(rv)) {
		nsCOMPtr<nsIPresShell> pIPresShell;
		rv = pIDocShell->GetPresShell(getter_AddRefs(pIPresShell));
		JREX_RETURN_IF_FAILED(rv,"JRexLiveConnectSession::Init()--> **** Getting nsIPresShell")
		nsCOMPtr<nsIDocument> pIDocument;
		rv = pIPresShell->GetDocument(getter_AddRefs(pIDocument));
		JREX_RETURN_IF_FAILED(rv,"JRexLiveConnectSession::Init()--> **** Getting nsIDocument")

	#ifdef JREX_MOZ1_4
		nsIScriptGlobalObject* globalObj = NULL;
		pIDocument->GetScriptGlobalObject(&globalObj);
	#else
		nsIScriptGlobalObject* globalObj = pIDocument->GetScriptGlobalObject();
	#endif
		if (IS_NULL(globalObj)) {
			JREX_LOGLN_ERR("ERROR: JRexLiveConnectSession::Init()--> **** Failed to get nsIScriptGlobalObject ****");
			return NS_ERROR_UNEXPECTED;
		}
		global = globalObj;
	}
#ifdef JREX_MOZ1_4
    global->GetContext(getter_AddRefs(mScriptContext));
#else
    mScriptContext = global->GetContext();
#endif
    if (IS_NULL(mScriptContext)) {
        JREX_LOGLN_ERR("ERROR: JRexLiveConnectSession::Init()--> **** Failed to get nsIScriptContext ****");
        return NS_ERROR_UNEXPECTED;
    }
    JSContext *pJSContext = (JSContext*)mScriptContext->GetNativeContext();
    if (IS_NULL(pJSContext)) {
        JREX_LOGLN_ERR("ERROR: JRexLiveConnectSession::Init()--> **** Failed to get JSContext ****");
        return NS_ERROR_UNEXPECTED;
    }
    JREX_LOGLN("JRexLiveConnectSession::Init()--> **** Got JSContext ****");

    JS_SetOptions(pJSContext, JS_GetOptions(pJSContext) | JSOPTION_VAROBJFIX);

    JSObject *jsglobal = JS_GetGlobalObject(pJSContext);
    if (IS_NULL(jsglobal)) {
        JREX_LOGLN_ERR("ERROR: JRexLiveConnectSession::Init()--> **** Failed to get JSObject global object ****");
        return NS_ERROR_UNEXPECTED;
    }

    JREX_LOGLN("JRexLiveConnectSession::Init()--> **** DONE ****");
    return rv;
}

NS_IMETHODIMP JRexLiveConnectSession::jsGC(JNIEnv *env) {
    JREX_LOGLN("JRexLiveConnectSession::Init()--> **** env<"<<env<<"> ****")
    JREX_LOGLN("JRexLiveConnectSession::jsGC()--> **** I AM HERE ****")
    if(IS_EQT)
        return jsGCInternal();
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    if (eventData) {
        JREX_LOGLN("JRexLiveConnectSession::jsGC()--> **** eventData Created ****")
        eventData->session = this;
        eventData->lcEventData = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,JSGC,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
        JREX_LOGLN("jsGC()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("jsGC()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::jsGCInternal() {
    JREX_LOGLN("JRexLiveConnectSession::jsGCInternal()--> **** I AM HERE ****")
	JSContext* cx = GetJSContext();
	nsresult rv = NS_ERROR_FAILURE;
	if (NOT_NULL(cx)) {
		JS_GC(cx);
		rv = NS_OK;
	} else {
		JREX_LOGLN_ERR("JRexLiveConnectSession::jsGCInternal()--> **** ERROR: JSContext DOES NOT EXIST ****")
	}
	return rv;
}

NS_IMETHODIMP JRexLiveConnectSession::InvokeStringJavascriptMethod(JNIEnv *env, const char *functionName, const char *arg, char **retStr) {
    JREX_LOGLN("JRexLiveConnectSession::InvokeStringJavascriptMethod()--> **** env<"<<env<<"> ****")
    if(IS_EQT)
        return InvokeStringJavascriptMethodInternal(functionName, arg, retStr);
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    InvokeStringEventData *lcEventData = new InvokeStringEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("InvokeStringJavascriptMethod()--> **** eventData Created ****")
        eventData->session = this;
        nsEmbedCString tempFunctionName(functionName);
        lcEventData->functionName = ToNewCString(tempFunctionName);
        nsEmbedCString tempArg(arg);
        lcEventData->arg = ToNewCString(tempArg);
        eventData->lcEventData = lcEventData;
        *retStr = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,INVOKE_STRING_METHOD,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
		if (NS_SUCCEEDED(rv)) {
			*retStr = (char*)lcrv->retData;
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
        JREX_LOGLN("InvokeStringJavascriptMethod()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("InvokeStringJavascriptMethod()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::InvokeStringJavascriptMethodInternal(const char *functionName, const char *arg, char **retStr) {
    JREX_LOGLN("InvokeStringJavascriptMethodInternal()--> **** function<"<<(PRUint32)functionName<<"('"<<(PRUint32)arg<<"')> ****");

    jsval jval;
    jsval jsargs[1];
    nsresult rv = NS_OK;
	JSContext* cx = GetJSContext();
    // TODO: The memory for this string copy needs to be recovered
    JSString* jStr = JS_NewStringCopyN(GetJSContext(), arg, strlen(arg));

    jsargs[0] = STRING_TO_JSVAL(jStr);
    JSBool jb = JS_CallFunctionName(cx, GetGlobalJSObject(), functionName, 1, jsargs, &jval);

    *retStr = NULL;
    if(jb == JS_TRUE) {
        if (jval) {
            JSString *s = JS_ValueToString(cx, jval);
            *retStr = JS_GetStringBytes(s);
            JREX_LOGLN("InvokeStringJavascriptMethodInternal()--> **** Invoked javascript method function<"<<(PRUint32)functionName<<"('"<<(PRUint32)arg<<"')> ret<"<<(PRUint32)(*retStr)<<"> ****");
        } else {
            JREX_LOGLN("InvokeStringJavascriptMethodInternal()--> **** Invoked javascript method function<"<<(PRUint32)functionName<<"('"<<(PRUint32)arg<<"')> no return ****");
        }
    } else {
        JREX_LOGLN_ERR("ERROR: InvokeStringJavascriptMethodInternal()--> **** Failed to invoke javascript method function<"<<(PRUint32)functionName<<"('"<<(PRUint32)arg<<"')> ****");
        rv = NS_ERROR_UNEXPECTED;
    }
    return rv;
}

PRBool JRexLiveConnectSession::IsContextValid() {
	PRBool isValid = PR_FALSE;
	// This walks backwards from JSContext just to make absolutely sure it is valid...
	JSContext* cx = GetJSContext();
	if (NOT_NULL(cx)) {
#ifdef JREX_MOZ1_4
		nsCOMPtr<nsIScriptContext> scriptContext;
		if (NOT_NULL(JS_GetContextPrivate(cx))) {
			nsISupports* supports = NS_REINTERPRET_CAST(nsIScriptContext*,
														JS_GetContextPrivate(cx));
			scriptContext = do_QueryInterface(supports);
		}
#else
        nsIScriptContext* scriptContext = GetScriptContextFromJSContext(cx);
#endif
		if (NOT_NULL(scriptContext)) {
			isValid = PR_TRUE;
		}
	}
    JREX_LOGLN("JRexLiveConnectSession::IsContextValid()--> **** isValid<"<<isValid<<"> ****")
	return isValid;
}

NS_IMETHODIMP JRexLiveConnectSession::EvalScript(JNIEnv *env, const jschar* script_chars, size_t script_chars_length,
												 jschar** retStr, size_t *retLength) {
    JREX_LOGLN("JRexLiveConnectSession::EvalScript()--> **** env<"<<env<<"> ****")
    *retStr = NULL;
	*retLength = -1;
    if(IS_EQT) {
        JSString *ret = NULL;
        nsresult rv = EvalScriptInternal(env, script_chars, script_chars_length, &ret);
        if (NS_SUCCEEDED(rv)) {
            *retStr = JS_GetStringChars(ret);
            *retLength = JS_GetStringLength(ret);
        }
        return rv;
    }
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    EvalScriptEventData *lcEventData = new EvalScriptEventData(script_chars);
    if (eventData && lcEventData) {
        JREX_LOGLN("EvalScript()--> **** eventData Created ****")
        eventData->session = this;
        lcEventData->script_chars_length = script_chars_length;
        eventData->lcEventData = lcEventData;
        JSString *ret = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,EVAL_SCRIPT,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("EvalScript()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
        if (NS_SUCCEEDED(rv)){
			if (IS_NULL(lcrv->ex)) {
				*retStr = JS_GetStringChars((JSString*)lcrv->retData);
				*retLength = JS_GetStringLength((JSString*)lcrv->retData);
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("EvalScript()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::EvalScriptInternal(JNIEnv *env, const jschar* script_chars, size_t script_chars_length, JSString** retStr) {
    JREX_LOGLN("EvalScriptInternal()--> **** I AM HERE ****");
	JSContext* cx = GetJSContext();
    *retStr = NULL;
    JSPrincipals *principals = jrex_get_JSPrincipals_from_java_caller_impl(env, cx, NULL, 0, NULL);
    const char *codebase = principals ? principals->codebase : NULL;
    jsval js_val;

    JREX_LOGLN("EvalScriptInternal()--> **** principals<"<<(PRUint32)principals<<"> codebase<"<<(PRUint32)codebase<<"> ****");

    JSBool eval_succeeded = JS_EvaluateUCScriptForPrincipals(cx, GetGlobalJSObject(), principals,
                                                             script_chars, script_chars_length,
                                                             codebase, 0, &js_val);

    JREX_LOGLN("EvalScriptInternal()--> **** eval_succeeded<"<<eval_succeeded<<"> ****");

    if (eval_succeeded) {
        *retStr = JS_ValueToString(cx, js_val);
        return NS_OK;
    } else {
        JREX_LOGLN_ERR("EvalScriptInternal()--> **** FAILED TO EVALUATE SCRIPT ****");
        return NS_ERROR_UNEXPECTED;
    }
}

void* PR_CALLBACK JRexLiveConnectSession::HandleLiveConnectEvent(PLEvent* aEvent){
    JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
	JRexEventRV* rVal=nsnull;
	if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

    JRexBasicEvent* basicEvent = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
    JRexLiveConnectEvent* event = NS_REINTERPRET_CAST(JRexLiveConnectEvent*, basicEvent->eventData);
	//Assign this so that it can be deleted in proper place.
	basicEvent->eRV=rVal;

	rVal->rv=NS_OK;
	if (event->session) {
		JREX_LOGLN("HandleLiveConnectEvent()--> **** JRexLiveConnectSession <"<<event->session<<"> ****")
		// Mark this session as the current in the hash...
		jrex_liveconnect_setThreadSession(event->session);
	} else {
		JREX_LOGLN("HandleLiveConnectEvent()--> **** JRexLiveConnectSession ****")
	}
	// It is possible the env for the event thread has an exception waiting. If
	// it hasn't been handled yet, then just report it. Clear it here and
	// report it if there was one, that way we won't think one of our calls
	// failed.
	JNI_EXP_DESC_CLR(NULL);
	// Initialize the return value
	JRexLiveConnectRV* lcrv = new JRexLiveConnectRV();
	if (IS_NULL(lcrv)) {
		rVal->rv = NS_ERROR_OUT_OF_MEMORY;
		return rVal;
	}
	if (env->PushLocalFrame(16) == 0) {
		rVal->rData = lcrv;
		switch(basicEvent->eventType){
			case INIT:
			{
				rVal->rv=event->session->InitInternal();
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent InitInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case STARTUP_LIVECONNECT:
			{
				rVal->rv=event->session->StartupLiveConnectInternal();
				JREX_LOGLN("HandleNavigationEvent()--> **** HandleLiveConnectEvent StartupLiveConnectInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case INVOKE_STRING_METHOD:
			{
				InvokeStringEventData* evtData = NS_REINTERPRET_CAST(InvokeStringEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				char *retStr = NULL;
				rVal->rv =event->session->InvokeStringJavascriptMethodInternal(evtData->functionName, evtData->arg, &retStr);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** InvokeStringJavascriptMethodInternal rv<"<<rVal->rv<<"> retStr<"<<(PRUint32)retStr<<"> ****")
				lcrv->retData=retStr;
				break;
			}
			case EVAL_SCRIPT:
			{
				EvalScriptEventData* evtData = NS_REINTERPRET_CAST(EvalScriptEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				JSString *retStr = NULL;
				rVal->rv =event->session->EvalScriptInternal(env, evtData->script_chars, evtData->script_chars_length, &retStr);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** EvalScriptInternal rv<"<<rVal->rv<<"> retStr<"<<(PRUint32)retStr<<"> ****")
				lcrv->retData=retStr;
				break;
			}
			case JSGC:
			{
				rVal->rv=event->session->jsGCInternal();
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent jsGCInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GET_WINDOW:
			{
				GetWindowEventData* evtData = NS_REINTERPRET_CAST(GetWindowEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jobject retObj = NULL;
				rVal->rv=JRexLiveConnectSession::GetWindowForSessionInternal(env, evtData->clazz, evtData->lcSession, &retObj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent GetWindowForSessionInternal rv<"<<rVal->rv<<"> retObj<"<<retObj<<"> ****")
				lcrv->retData=retObj;
				break;
			}
			case GET_MEMBER:
			{
				GetMemberEventData* evtData = NS_REINTERPRET_CAST(GetMemberEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jobject retObj = NULL;
				rVal->rv=JRexLiveConnectSession::GetMemberInternal(env, evtData->jrex_jsobj, evtData->name, &retObj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent GetMemberInternal rv<"<<rVal->rv<<"> retObj<"<<retObj<<"> ****")
				lcrv->retData=retObj;
				break;
			}
			case GET_SLOT:
			{
				GetSlotEventData* evtData = NS_REINTERPRET_CAST(GetSlotEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jobject retObj = NULL;
				rVal->rv=JRexLiveConnectSession::GetSlotInternal(env, evtData->jrex_jsobj, evtData->indx, &retObj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent GetSlotInternal rv<"<<rVal->rv<<"> retObj<"<<retObj<<"> ****")
				lcrv->retData=retObj;
				break;
			}
			case EVAL:
			{
				EvalEventData* evtData = NS_REINTERPRET_CAST(EvalEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jobject retObj = NULL;
				rVal->rv=JRexLiveConnectSession::EvalInternal(env, evtData->jrex_jsobj, evtData->evalstr, &retObj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent EvalInternal rv<"<<rVal->rv<<"> retObj<"<<retObj<<"> ****")
				lcrv->retData=retObj;
				break;
			}
			case SET_MEMBER:
			{
				SetMemberEventData* evtData = NS_REINTERPRET_CAST(SetMemberEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=JRexLiveConnectSession::SetMemberInternal(env, evtData->jrex_jsobj, evtData->name, evtData->value);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent SetMemberInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case SET_SLOT:
			{
				SetSlotEventData* evtData = NS_REINTERPRET_CAST(SetSlotEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=JRexLiveConnectSession::SetSlotInternal(env, evtData->jrex_jsobj, evtData->indx, evtData->value);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent SetSlotInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_MEMBER:
			{
				RemoveMemberEventData* evtData = NS_REINTERPRET_CAST(RemoveMemberEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=JRexLiveConnectSession::RemoveMemberInternal(env, evtData->jrex_jsobj, evtData->name);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent RemoveMemberInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case CALL:
			{
				CallEventData* evtData = NS_REINTERPRET_CAST(CallEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jobject retObj = NULL;
				rVal->rv=JRexLiveConnectSession::CallInternal(env, evtData->jrex_jsobj, evtData->func, evtData->args, &retObj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent CallInternal rv<"<<rVal->rv<<"> retObj<"<<retObj<<"> ****")
				lcrv->retData=retObj;
				break;
			}
			case TO_STRING:
			{
				ToStringEventData* evtData = NS_REINTERPRET_CAST(ToStringEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jstring retStr = NULL;
				rVal->rv=JRexLiveConnectSession::ToStringInternal(env, evtData->jrex_jsobj, &retStr);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent ToStringInternal rv<"<<rVal->rv<<"> retStr<"<<retStr<<"> ****")
				lcrv->retData=retStr;
				break;
			}
			case EQUALS:
			{
				EqualsEventData* evtData = NS_REINTERPRET_CAST(EqualsEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				jboolean retIsEq=PR_FALSE;
				rVal->rv=JRexLiveConnectSession::EqualsInternal(env, evtData->jrex_jsobj, evtData->cmp_obj, &retIsEq);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent EqualsInternal rv<"<<rVal->rv<<"> retIsEq<"<<retIsEq<<"> ****")
				lcrv->retData=(void*)retIsEq;
				break;
			}
			case FINALIZE:
			{
				FinalizeEventData* evtData = NS_REINTERPRET_CAST(FinalizeEventData*, event->lcEventData);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=JRexLiveConnectSession::FinalizeInternal(env, evtData->jrex_jsobj);
				JREX_LOGLN("HandleLiveConnectEvent()--> **** HandleLiveConnectEvent FinalizeInternal rv<"<<rVal->rv<<"> ****")
   				break;
			}
			default:
			{
				JREX_LOGLN_ERR("HandleLiveConnectEvent()--> **** EVENT TYPE<"<<basicEvent->eventType<<"> not handled!!! ****")
				ThrowJRexException(env,"HandleLiveConnectEvent()--> **** EVENT TYPE not handled!!! ****",0);
			}
		};

		// Pop the local reference frame
		env->PopLocalFrame(NULL);
	} // else the out of memory exception will be propagated below
    JREX_LOGLN("HandleLiveConnectEvent()--> **** returning rVal<"<<rVal<<"> ****")
	jrex_liveconnect_removeThreadSession();
	// Was there a Java exception from a js call? If there was, make sure the exception is propagated back
	// to the calling thread.
	if (env->ExceptionCheck()) {
		jthrowable theex = env->ExceptionOccurred();
		lcrv->ex = (jthrowable)env->NewGlobalRef(theex);
		env->DeleteLocalRef(theex);
		// Clear the exception
		env->ExceptionClear();
	}
    return rVal;
}

void PR_CALLBACK  JRexLiveConnectSession::DestroyLiveConnectEvent(PLEvent* aEvent){
    JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
    JRexBasicEvent* basicEvent = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
    JRexLiveConnectEvent* event = NS_REINTERPRET_CAST(JRexLiveConnectEvent*, basicEvent->eventData);
    JREX_LOGLN("DestroyLiveConnectEvent()--> **** session <"<<event->session<<"> ****")
    if(event->lcEventData){
        if(basicEvent->eventType==INVOKE_STRING_METHOD){
            InvokeStringEventData* evtData = NS_REINTERPRET_CAST(InvokeStringEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** INVOKE_STRING_METHOD evtData<"<<evtData<<"> ****")
            CRTFREEIF(evtData->functionName);
            CRTFREEIF(evtData->arg);
            delete evtData;
        } else if(basicEvent->eventType==EVAL_SCRIPT){
            EvalScriptEventData* evtData = NS_REINTERPRET_CAST(EvalScriptEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** EVAL_SCRIPT evtData<"<<evtData<<"> ****")
            delete evtData;
        } else if(basicEvent->eventType==GET_WINDOW){
            GetWindowEventData* evtData = NS_REINTERPRET_CAST(GetWindowEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** GET_WINDOW evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->lcSession);
			env->DeleteGlobalRef(evtData->clazz);
            delete evtData;
        } else if(basicEvent->eventType==GET_MEMBER){
            GetMemberEventData* evtData = NS_REINTERPRET_CAST(GetMemberEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** GET_MEMBER evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->name);
            delete evtData;
        } else if(basicEvent->eventType==GET_SLOT){
            GetSlotEventData* evtData = NS_REINTERPRET_CAST(GetSlotEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** GET_SLOT evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
            delete evtData;
        } else if(basicEvent->eventType==SET_MEMBER){
            SetMemberEventData* evtData = NS_REINTERPRET_CAST(SetMemberEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** SET_MEMBER evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->name);
			if (NOT_NULL(evtData->value)) env->DeleteGlobalRef(evtData->value);
            delete evtData;
        } else if(basicEvent->eventType==EVAL){
            EvalEventData* evtData = NS_REINTERPRET_CAST(EvalEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** EVAL evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->evalstr);
            delete evtData;
        } else if(basicEvent->eventType==SET_SLOT){
            SetSlotEventData* evtData = NS_REINTERPRET_CAST(SetSlotEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** SET_SLOT evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			if (NOT_NULL(evtData->value)) env->DeleteGlobalRef(evtData->value);
            delete evtData;
        } else if(basicEvent->eventType==REMOVE_MEMBER){
            RemoveMemberEventData* evtData = NS_REINTERPRET_CAST(RemoveMemberEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** REMOVE_MEMBER evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->name);
            delete evtData;
        } else if(basicEvent->eventType==CALL){
            CallEventData* evtData = NS_REINTERPRET_CAST(CallEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** CALL evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->func);
			if (NOT_NULL(evtData->args)) env->DeleteGlobalRef(evtData->args);
            delete evtData;
        } else if(basicEvent->eventType==TO_STRING){
            ToStringEventData* evtData = NS_REINTERPRET_CAST(ToStringEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** TO_STRING evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
            delete evtData;
        } else if(basicEvent->eventType==EQUALS){
            EqualsEventData* evtData = NS_REINTERPRET_CAST(EqualsEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** EQUALS evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
			env->DeleteGlobalRef(evtData->cmp_obj);
            delete evtData;
        } else if(basicEvent->eventType==FINALIZE){
            FinalizeEventData* evtData = NS_REINTERPRET_CAST(FinalizeEventData*, event->lcEventData);
            JREX_LOGLN("DestroyLiveConnectEvent()--> **** FINALIZE evtData<"<<evtData<<"> ****")
			env->DeleteGlobalRef(evtData->jrex_jsobj);
            delete evtData;
		}
    }
	if((basicEvent->isSync==PR_FALSE) && basicEvent->eRV)//Delete eRV of Non-Sync Event Here
		delete basicEvent->eRV;
	delete event;
    delete basicEvent;
    JREX_LOGLN("DestroyLiveConnectEvent()--> **** DONE ****")
}

JRexLiveConnectSession::~JRexLiveConnectSession(){
    JNIEnv *env=JREX_JNI_UTIL::JRex_GetEnv(0);
    JREX_LOGLN("~JRexLiveConnectSession()--> **** env<"<<env<<"> ****")
    env->DeleteGlobalRef(mLCSession);
	mScriptContext = NULL;
}
