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
#ifndef JRexLiveConnectSession_h_
#define JRexLiveConnectSession_h_
#include "JRexWindow.h"
#include "jni.h"
#include "jsapi.h"

#include "JRex_JNI_Util.h"
#include "jsjava.h"
#include "jsprf.h"
#include "jsutil.h"
#include "jscntxt.h"
#include "prtypes.h"
#include "jsdbgapi.h"
#include "nsError.h"

#include "nsISecurityContext.h"
#include "nsIScriptContext.h"
#include "nsIScriptGlobalObject.h"
#include "nsIScriptObjectPrincipal.h"
#include "nsIServiceManager.h"
#include "nsILiveconnect.h"
#include "nsIPresShell.h"
#include "nsIScriptSecurityManager.h"
#include "nsHashtable.h"

#define LC_SESSION_CLASS_NAME   "org/mozilla/jrex/liveconnect/JRexLiveConnectSessionImpl"
#define JREX_JS_OBJECT_CLASS_NAME    "org/mozilla/jrex/liveconnect/JRexJSObject"
#define INATIVE_JS_OBJECT_CLASS_NAME    "org/mozilla/jrex/liveconnect/INativeJSObject"

#define CHECK_LCRV_EX(lcrv) \
if (NOT_NULL(lcrv->ex)) { \
	jthrowable theex = (jthrowable)env->NewLocalRef(lcrv->ex); \
	env->DeleteGlobalRef(lcrv->ex); \
	lcrv->ex = NULL; \
	env->Throw(theex); \
}

namespace JREX_LIVECONNECT{

    class JRexLiveConnectFields {
        public :
            static jfieldID peerID;
            static jfieldID sessionID;
			static jfieldID jsobjSessionFieldID;
			static jfieldID jsobjInternalFieldID;
            static jmethodID getSessionID;
			static jmethodID jrexjsobject_initID;
            static jclass lcimpl_clazz; // global ref
            static jclass jrexjsobject_clazz; // global ref

			// JSObject callbacks into Jav which in turn invoke native JSObject functions
            static jclass iNativeJSObject_clazz;
            static jmethodID jsObjectGetMember;
            static jmethodID jsObjectGetSlot;
            static jmethodID jsObjectSetMember;
            static jmethodID jsObjectSetSlot;
            static jmethodID jsObjectRemoveMember;
            static jmethodID jsObjectCall;
            static jmethodID jsObjectEval;
            static jmethodID jsObjectToString;
            static jmethodID jsObjectFinalize;
            static jmethodID jsObjectEquals;
    };

    class JRexLiveConnectSession {
        public:
			//BF - Pepper Computer: pass in lcSession to constructor so global ref
			//can be created right away
			JRexLiveConnectSession(jobject lcSession, JRexWindow *window, PRBool useRootDocShell);
			//BF - no need to pass in lcSession here anymore as it's passed into ctor
            NS_IMETHOD Init(JNIEnv *env);
            NS_IMETHOD StartupLiveConnect(JNIEnv *env);
            NS_IMETHOD InvokeStringJavascriptMethod(JNIEnv *env, const char* functionName, const char* arg, char** retStr);
            NS_IMETHOD EvalScript(JNIEnv *env, const jschar* script_chars, size_t script_chars_length, jschar** retStr, size_t* retLength);
            NS_IMETHOD jsGC(JNIEnv *env);
            JSObject* GetGlobalJSObject() { return JS_GetGlobalObject(GetJSContext()); }
            JSContext* GetJSContext() { return (JSContext*)mScriptContext->GetNativeContext(); }
			PRBool IsContextValid();
            virtual ~JRexLiveConnectSession();

            // JSObject JRex-specific methods. These must be called directly from JSObject,
            // because they access private members of JSObject.
            static nsresult GetWindowForSession(JNIEnv *env, jclass clazz, jobject lcSession, jobject* retWin);
            static nsresult GetMember(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject* retObj);
            static nsresult GetSlot(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject* retObj);
            static nsresult SetMember(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject value);
            static nsresult Eval(JNIEnv *env, jobject jrex_jsobj, jstring evalstr, jobject* retObj);
            static nsresult SetSlot(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject value);
            static nsresult RemoveMember(JNIEnv *env, jobject jrex_jsobj, jstring name);
            static nsresult Call(JNIEnv *env, jobject jrex_jsobj, jstring func, jobjectArray args, jobject* retObj);
            static nsresult ToString(JNIEnv *env, jobject jrex_jsobj, jstring* retStr);
            static nsresult Equals(JNIEnv *env, jobject jrex_jsobj, jobject cmp_obj, jboolean* retIsEq);
            static nsresult Finalize(JNIEnv *env, jobject jrex_jsobj);

        private:
            //event types for liveconnect
            enum LiveConnectEventTypes{	INIT,
                                        STARTUP_LIVECONNECT,
                                        INVOKE_STRING_METHOD,
                                        EVAL_SCRIPT,
                                        GET_WINDOW,
                                        GET_MEMBER,
                                        GET_SLOT,
                                        SET_MEMBER,
                                        EVAL,
                                        SET_SLOT,
                                        REMOVE_MEMBER,
                                        CALL,
                                        TO_STRING,
                                        EQUALS,
                                        FINALIZE,
										JSGC};

            struct InvokeStringEventData{
                char* functionName;
                char* arg;
            };

            struct EvalScriptEventData{
                EvalScriptEventData(const jschar* theChars) : script_chars(theChars) {}
                const jschar* script_chars;
                size_t script_chars_length;
            };

            struct GetWindowEventData{
                jobject lcSession;
                jclass clazz;
            };

            struct GetMemberEventData{
                jobject jrex_jsobj;
                jstring name;
            };

            struct GetSlotEventData{
                jobject jrex_jsobj;
                jint indx;
            };

            struct SetMemberEventData{
                jobject jrex_jsobj;
                jstring name;
                jobject value;
            };

            struct EvalEventData{
                jobject jrex_jsobj;
                jstring evalstr;
            };

            struct SetSlotEventData{
                jobject jrex_jsobj;
                jint indx;
                jobject value;
            };

            struct RemoveMemberEventData{
                jobject jrex_jsobj;
                jstring name;
            };

            struct CallEventData{
                jobject jrex_jsobj;
                jstring func;
                jobjectArray args;
            };

            struct ToStringEventData{
                jobject jrex_jsobj;
            };

            struct EqualsEventData{
                jobject jrex_jsobj;
                jobject cmp_obj;
            };

            struct FinalizeEventData{
                jobject jrex_jsobj;
            };

            struct JRexLiveConnectEvent : PLEvent{
				JRexLiveConnectEvent() : PLEvent() {}
                JRexLiveConnectSession *session;
                void* lcEventData;
            };

			struct JRexLiveConnectRV {
				JRexLiveConnectRV() : retData(NULL), ex(NULL) {}
				void *retData;
				jthrowable ex;
			};

            static void* PR_CALLBACK HandleLiveConnectEvent(PLEvent* aEvent);
            static void PR_CALLBACK  DestroyLiveConnectEvent(PLEvent* aEvent);

            nsresult InitInternal();
            nsresult StartupLiveConnectInternal();
            nsresult InvokeStringJavascriptMethodInternal(const char* functionName, const char* arg, char** retStr);
            nsresult EvalScriptInternal(JNIEnv *env, const jschar* script_chars, size_t script_chars_length, JSString** retStr);
            nsresult jsGCInternal();

            // JSObject JRex-specific method implementations
            static nsresult GetWindowForSessionInternal(JNIEnv *env, jclass clazz, jobject lcSession, jobject* retWin);
            static nsresult GetMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject* retObj);
            static nsresult GetSlotInternal(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject* retObj);
            static nsresult SetMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject value);
            static nsresult EvalInternal(JNIEnv *env, jobject jrex_jsobj, jstring evalstr, jobject* retObj);
            static nsresult SetSlotInternal(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject value);
            static nsresult RemoveMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name);
            static nsresult CallInternal(JNIEnv *env, jobject jrex_jsobj, jstring func, jobjectArray args, jobject* retObj);
            static nsresult ToStringInternal(JNIEnv *env, jobject jrex_jsobj, jstring* retStr);
            static nsresult EqualsInternal(JNIEnv *env, jobject jrex_jsobj, jobject cmp_obj, jboolean* retIsEq);
            static nsresult FinalizeInternal(JNIEnv *env, jobject jrex_jsobj);

            jobject mLCSession;
            JRexWindow *mJRexWindow;
			PRBool mShouldUseRootDocShell;
			nsCOMPtr<nsIScriptContext> mScriptContext;
            static PRBool sLCInited;
    };
}

#endif // LiveConnectSession_h_

