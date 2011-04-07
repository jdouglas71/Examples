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

#include "org_mozilla_jrex_liveconnect_JRexJSObject.h"
#include "JRexLiveConnectSession.h"
#include "JRex_JNI_Util.h"
#include "netscape_javascript_JSObject.h"

using namespace JREX_LIVECONNECT;
using namespace JREX_JNI_UTIL;

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    GetWindowForSession
 * Signature: (Lorg/mozilla/jrex/liveconnect/JRexLiveConnectSessionImpl;)Lorg/mozilla/jrex/liveconnect/JRexJSObject;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_GetWindowForSession
  (JNIEnv *env, jclass clazz, jobject lcSession) {
	jobject ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::GetWindowForSession(env, clazz, lcSession, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** LiveConnectSession_GetWindowForSession()-->  Failed to create JSObject ****",rv);
        return NULL;
    }
	JREX_LOGLN("LiveConnectSession_GetWindowForSession()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_Finalize
(JNIEnv *env, jobject jrex_jsobj) {
	JREX_LOGLN("JRexFinalize()--> **** I AM HERE ****")
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::Finalize(env, jrex_jsobj);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexFinalize()-->  Failed ****",rv);
		return;
    }
	JREX_LOGLN("JRexFinalize()--> **** DONE ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexEval
 * Signature: (Ljava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexEval
  (JNIEnv *env, jobject jrex_jsobj, jstring evalstr) {
	jobject ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::Eval(env, jrex_jsobj, evalstr, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexEval()-->  Failed ****",rv);
        return NULL;
    }
	JREX_LOGLN("JRexEval()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}


/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexGetMember
 * Signature: (Ljava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexGetMember
  (JNIEnv *env, jobject jrex_jsobj, jstring name) {
	jobject ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::GetMember(env, jrex_jsobj, name, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexGetMember()-->  Failed ****",rv);
        return NULL;
    }
	JREX_LOGLN("JRexGetMember()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexGetSlot
 * Signature: (I)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexGetSlot
  (JNIEnv *env, jobject jrex_jsobj, jint indx) {
	jobject ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::GetSlot(env, jrex_jsobj, indx, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexGetSlot()-->  Failed ****",rv);
        return NULL;
    }
	JREX_LOGLN("JRexGetSlot()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexSetMember
 * Signature: (Ljava/lang/String;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexSetMember
  (JNIEnv *env, jobject jrex_jsobj, jstring name, jobject value) {
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::SetMember(env, jrex_jsobj, name, value);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexSetMember()-->  Failed ****",rv);
		return;
    }
	JREX_LOGLN("JRexSetMember()--> **** DONE ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexSetSlot
 * Signature: (ILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexSetSlot
  (JNIEnv *env, jobject jrex_jsobj, jint indx, jobject value) {
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::SetSlot(env, jrex_jsobj, indx, value);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexSetSlot()-->  Failed ****",rv);
		return;
    }
	JREX_LOGLN("JRexSetSlot()--> **** DONE ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexRemoveMember
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexRemoveMember
  (JNIEnv *env, jobject jrex_jsobj, jstring name) {
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::RemoveMember(env, jrex_jsobj, name);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexRemoveMember()-->  Failed ****",rv);
		return;
    }
	JREX_LOGLN("JRexRemoveMember()--> **** DONE ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexCall
 * Signature: (Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexCall
  (JNIEnv *env, jobject jrex_jsobj, jstring func, jobjectArray args) {
	jobject ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::Call(env, jrex_jsobj, func, args, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexCall()-->  Failed ****",rv);
        return NULL;
    }
	JREX_LOGLN("JRexCall()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexToString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexToString
  (JNIEnv *env, jobject jrex_jsobj) {
	jstring ret = NULL;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::ToString(env, jrex_jsobj, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexToString()-->  Failed ****",rv);
        return NULL;
    }
	JREX_LOGLN("JRexToString()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JRexEquals
 * Signature: (Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JRexEquals
  (JNIEnv *env, jobject jrex_jsobj, jobject cmp_obj) {
	jboolean ret = JNI_FALSE;
	JREX_TRY
    nsresult rv = JRexLiveConnectSession::Equals(env, jrex_jsobj, cmp_obj, &ret);
	if (NS_FAILED(rv)) {
		ThrowJRexException(env, "**** JRexEquals()-->  Failed ****",rv);
		return JNI_FALSE;
    }
	JREX_LOGLN("JRexEquals()--> **** DONE ****")
    JREX_CATCH(env)
    return ret;
}
/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectGetMember
 * Signature: (Ljava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectGetMember
  (JNIEnv *env, jobject jsObj, jstring name) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return NULL;
	}
	jobject ret = NULL;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_getMember(env, jsObj, name);
    JREX_CATCH(env)
	return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectGetSlot
 * Signature: (I)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectGetSlot
  (JNIEnv *env, jobject jsObj, jint indx) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return NULL;
	}
	jobject ret = NULL;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_getSlot(env, jsObj, indx);
    JREX_CATCH(env)
	return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectSetMember
 * Signature: (Ljava/lang/String;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectSetMember
  (JNIEnv *env, jobject jsObj, jstring name, jobject data) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return;
	}
	JREX_TRY
    Java_netscape_javascript_JSObject_setMember(env, jsObj, name, data);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectSetSlot
 * Signature: (ILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectSetSlot
  (JNIEnv *env, jobject jsObj, jint indx, jobject data) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return;
	}
	JREX_TRY
    Java_netscape_javascript_JSObject_setSlot(env, jsObj, indx, data);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectRemoveMember
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectRemoveMember
  (JNIEnv *env, jobject jsObj, jstring name) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return;
	}
	JREX_TRY
    Java_netscape_javascript_JSObject_removeMember(env, jsObj, name);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectCall
 * Signature: (Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectCall
  (JNIEnv *env, jobject jsObj, jstring func, jobjectArray args) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return NULL;
	}
	jobject ret = NULL;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_call(env, jsObj, func, args);
    JREX_CATCH(env)
	return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectEval
 * Signature: (Ljava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectEval
  (JNIEnv *env, jobject jsObj, jstring evalstr) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return NULL;
	}
	jobject ret = NULL;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_eval(env, jsObj, evalstr);
    JREX_CATCH(env)
	return ret;
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectToString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectToString
  (JNIEnv *env, jobject jsObj) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return NULL;
	}
	jstring ret = NULL;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_toString(env, jsObj);
    JREX_CATCH(env)
	return ret;
}


/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectFinalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectFinalize
  (JNIEnv *env, jobject jsObj) {
    // XXX This is not called because of a problem with finalizing not calling our lc callbacks. See JRexJSObject.cpp.
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return;
	}
	JREX_TRY
    Java_netscape_javascript_JSObject_finalize(env, jsObj);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_liveconnect_JRexJSObject
 * Method:    JSObjectEquals
 * Signature: (Ljava/lang/Object;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_liveconnect_JRexJSObject_JSObjectEquals
 (JNIEnv *env, jobject jsObj, jobject cmp) {
	if (!IS_EQT) {
		ThrowJRexException(env, "**** JSObject methods must be invoked on the JRex event thread ****",0);
		return JNI_FALSE;
	}
	jboolean ret = JNI_FALSE;
	JREX_TRY
    ret = Java_netscape_javascript_JSObject_equals(env, jsObj, cmp);
    JREX_CATCH(env)
	return ret;
}