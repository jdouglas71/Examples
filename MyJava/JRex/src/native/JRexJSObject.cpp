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
#include "JRex_JNI_Util.h"
#include "netscape_javascript_JSObject.h"
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
#include "nsIScriptSecurityManager.h"
#include "nsILiveconnect.h"
#include "nsIPresShell.h"

#include <string.h>
using namespace JREX_LIVECONNECT;
using namespace JREX_JNI_UTIL;

// Uncomment this to make Java calls instead of straight JNI calls
#define JSOBJECT_CALL_DIRECT

#define JSOBJ_GETSESSION    JRexLiveConnectSession* session = (JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(jrex_jsobj, JRexLiveConnectFields::jsobjSessionFieldID)); \
	if(IS_NULL(session)){ \
		ThrowJRexException(env, "**** JRexLiveConnectSession DOES NOT EXIST!!! ****",0); \
        return NS_ERROR_UNEXPECTED; \
	}

#define JSOBJ_INTERNAL_CHECKSESSION    JRexLiveConnectSession* session = (JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(jrex_jsobj, JRexLiveConnectFields::jsobjSessionFieldID)); \
	if(IS_NULL(session)){ \
		JREX_LOGLN_ERR("**** WARNING: in JSObject call: JRexLiveConnectSession DOES NOT EXIST!!! ****"); \
        return NS_ERROR_UNEXPECTED; \
	} \
	if (session->IsContextValid()==PR_FALSE) { \
		JREX_LOGLN_ERR("**** WARNING: JSObject call failed-->CONTEXT DOES NOT EXIST!!! ****"); \
        return NS_ERROR_UNEXPECTED; \
	}

#define LCOBJ_INTERNAL_CHECKSESSION    JRexLiveConnectSession* session = (JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID)); \
	if(IS_NULL(session)){ \
		JREX_LOGLN_ERR("**** WARNING: in JSObject call: JRexLiveConnectSession DOES NOT EXIST!!! ****"); \
        return NS_ERROR_UNEXPECTED; \
	} \
	if (session->IsContextValid()==PR_FALSE) { \
		JREX_LOGLN_ERR("**** WARNING: JSObject call failed-->CONTEXT DOES NOT EXIST!!! ****"); \
        return NS_ERROR_UNEXPECTED; \
	}

inline static jobject jobject_globalToLocal(JNIEnv* env, jobject obj) {
	jobject ret = env->NewLocalRef(obj);
	env->DeleteGlobalRef(obj);
	return ret;
}

inline static jobject jobject_localToGlobal(JNIEnv* env, jobject obj) {
	jobject ret = env->NewGlobalRef(obj);
	// PopLocalFrame takes care of deleting the local ref (if it is a local ref)
	return ret;
}

nsresult JRexLiveConnectSession::GetWindowForSession(JNIEnv *env, jclass clazz, jobject lcSession, jobject *retObj) {
	JREX_LOGLN("GetWindowForSession()--> **** lcSession<"<<lcSession<<"> env<"<<env<<"> ****")
	*retObj = NULL;
    if(IS_EQT) {
        jobject ret = NULL;
        nsresult rv = GetWindowForSessionInternal(env, clazz, lcSession, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retObj = jobject_globalToLocal(env,ret);
        }
		return rv;
    }
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    GetWindowEventData *lcEventData = new GetWindowEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("GetWindowForSession()--> **** eventData Created ****")
        eventData->session = (JRexLiveConnectSession *)NS_INT32_TO_PTR(env->GetIntField(lcSession, JRexLiveConnectFields::sessionID));
		lcEventData->lcSession = env->NewGlobalRef(lcSession);
        lcEventData->clazz = (jclass) env->NewGlobalRef(clazz);
        eventData->lcEventData = lcEventData;
        *retObj = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,GET_WINDOW,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("GetWindowForSession()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retObj = jobject_globalToLocal(env,(jobject)lcrv->retData);
				} else {
					ThrowJRexException(env, "**** GetWindowForSession returned NULL but rv was success. An unknown error has occurred. ****",0);
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("GetWindowForSession()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::GetWindowForSessionInternal(JNIEnv *env, jclass clazz, jobject lcSession, jobject *retWin) {
    JREX_LOGLN("GetWindowForSessionInternal()--> **** env<"<<env<<"> ****");
	LCOBJ_INTERNAL_CHECKSESSION
    // Invoke the native getWindow method for the lcSession. This method is necessary
    // because sun's plugin implementation overides JSObject.getWindow and a native
    // call is not made. Here, this native call delegates to the standard getWindow
    // native method.
    *retWin = Java_netscape_javascript_JSObject_getWindow(env, clazz, lcSession);
    if (NOT_NULL(*retWin)) {
		*retWin = jobject_localToGlobal(env,*retWin);
        return NS_OK;
    } else {
        return NS_ERROR_UNEXPECTED;
    }
}

nsresult JRexLiveConnectSession::GetMember(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject *retObj) {
	JREX_LOGLN("GetMember()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
	*retObj = NULL;
    if(IS_EQT) {
        jobject ret = NULL;
        nsresult rv = GetMemberInternal(env, jrex_jsobj, name, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retObj = jobject_globalToLocal(env,ret);
        }
		return rv;
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    GetMemberEventData *lcEventData = new GetMemberEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("GetMember()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->name = (jstring) env->NewGlobalRef(name);
        eventData->lcEventData = lcEventData;
        *retObj = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,GET_MEMBER,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("GetMember()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retObj = jobject_globalToLocal(env,(jobject)lcrv->retData);
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("GetMember()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::GetMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject *retObj) {
    JREX_LOGLN("GetMemberInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retObj = Java_netscape_javascript_JSObject_getMember(env, jrex_jsobj, name);
#else
	*retObj = env->CallObjectMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectGetMember, name);
#endif
    if (NOT_NULL(*retObj)) {
		*retObj = jobject_localToGlobal(env,*retObj);
    }
	return NS_OK;
}

nsresult JRexLiveConnectSession::GetSlot(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject *retObj) {
	JREX_LOGLN("GetSlot()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
	*retObj = NULL;
    if(IS_EQT) {
        jobject ret = NULL;
        nsresult rv = GetSlotInternal(env, jrex_jsobj, indx, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retObj = jobject_globalToLocal(env,ret);
        }
		return rv;
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    GetSlotEventData *lcEventData = new GetSlotEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("GetSlot()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
        lcEventData->indx = indx;
        eventData->lcEventData = lcEventData;
        *retObj = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,GET_MEMBER,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("GetSlot()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retObj = jobject_globalToLocal(env,(jobject)lcrv->retData);
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("GetSlot()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::GetSlotInternal(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject *retObj) {
    JREX_LOGLN("GetSlotInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retObj = Java_netscape_javascript_JSObject_getSlot(env, jrex_jsobj, indx);
#else
	*retObj = env->CallObjectMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectGetSlot, indx);
#endif
    if (NOT_NULL(*retObj)) {
		*retObj = jobject_localToGlobal(env,*retObj);
    }
	return NS_OK;
}

nsresult JRexLiveConnectSession::Eval(JNIEnv *env, jobject jrex_jsobj, jstring evalstr, jobject *retObj) {
	JREX_LOGLN("Eval()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
	*retObj = NULL;
    if(IS_EQT) {
        jobject ret = NULL;
        nsresult rv = EvalInternal(env, jrex_jsobj, evalstr, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retObj = jobject_globalToLocal(env,ret);
        }
		return rv;
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    EvalEventData *lcEventData = new EvalEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("Eval()--> **** eventData Created jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->evalstr = (jstring) env->NewGlobalRef(evalstr);
        eventData->lcEventData = lcEventData;
        *retObj = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,EVAL,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("Eval()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retObj = jobject_globalToLocal(env,(jobject)lcrv->retData);
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("Eval()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::EvalInternal(JNIEnv *env, jobject jrex_jsobj, jstring evalstr, jobject *retObj) {
    JREX_LOGLN("EvalInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retObj = Java_netscape_javascript_JSObject_eval(env, jrex_jsobj, evalstr);
#else
	*retObj = env->CallObjectMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectEval, evalstr);
#endif
    if (NOT_NULL(*retObj)) {
		*retObj = jobject_localToGlobal(env,*retObj);
    }
	return NS_OK;
}

nsresult JRexLiveConnectSession::SetMember(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject value) {
	JREX_LOGLN("GetSlot()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
    if(IS_EQT) {
        return SetMemberInternal(env, jrex_jsobj, name, value);
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    SetMemberEventData *lcEventData = new SetMemberEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("SetMember()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->name = (jstring) env->NewGlobalRef(name);
		if (NOT_NULL(value)) {
			lcEventData->value = env->NewGlobalRef(value);
		} else {
			lcEventData->value = NULL;
		}
        eventData->lcEventData = lcEventData;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,SET_MEMBER,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("SetMember()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("SetMember()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::SetMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name, jobject value) {
    JREX_LOGLN("SetMemberInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	Java_netscape_javascript_JSObject_setMember(env, jrex_jsobj, name, value);
#else
	env->CallVoidMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectSetMember, name, value);
#endif
    return NS_OK;
}

nsresult JRexLiveConnectSession::SetSlot(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject value) {
	JREX_LOGLN("SetSlot()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> indx<"<<indx<<"> ****")
    if(IS_EQT) {
        return SetSlotInternal(env, jrex_jsobj, indx, value);
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    SetSlotEventData *lcEventData = new SetSlotEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("SetSlot()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
        lcEventData->indx = indx;
		if (NOT_NULL(value)) {
			lcEventData->value = env->NewGlobalRef(value);
		} else {
			lcEventData->value = NULL;
		}
        eventData->lcEventData = lcEventData;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,SET_SLOT,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
        JREX_LOGLN("SetSlot()--> **** ExecInEventQ rv<"<<rv<<"> ****")
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("SetSlot()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::SetSlotInternal(JNIEnv *env, jobject jrex_jsobj, jint indx, jobject value) {
    JREX_LOGLN("SetSlotInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	Java_netscape_javascript_JSObject_setSlot(env, jrex_jsobj, indx, value);
#else
	env->CallVoidMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectSetSlot, indx, value);
#endif
    return NS_OK;
}

nsresult JRexLiveConnectSession::RemoveMember(JNIEnv *env, jobject jrex_jsobj, jstring name) {
	JREX_LOGLN("SetSlot()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
    if(IS_EQT) {
        return RemoveMemberInternal(env, jrex_jsobj, name);
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    RemoveMemberEventData *lcEventData = new RemoveMemberEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("RemoveMember()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->name = (jstring) env->NewGlobalRef(name);
        eventData->lcEventData = lcEventData;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,REMOVE_MEMBER,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("RemoveMember()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("RemoveMember()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::RemoveMemberInternal(JNIEnv *env, jobject jrex_jsobj, jstring name) {
    JREX_LOGLN("RemoveMemberInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	Java_netscape_javascript_JSObject_removeMember(env, jrex_jsobj, name);
#else
	env->CallVoidMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectRemoveMember, name);
#endif
    return NS_OK;
}

nsresult JRexLiveConnectSession::Call(JNIEnv *env, jobject jrex_jsobj, jstring func, jobjectArray args, jobject* retObj) {
	JREX_LOGLN("Call()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
	*retObj = NULL;
    if(IS_EQT) {
        jobject ret = NULL;
        nsresult rv = CallInternal(env, jrex_jsobj, func, args, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retObj = jobject_globalToLocal(env,ret);
        }
		return rv;
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    CallEventData *lcEventData = new CallEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("Call()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->func = (jstring) env->NewGlobalRef(func);
		if (NOT_NULL(args)) {
			lcEventData->args = (jobjectArray)env->NewGlobalRef(args);
		} else {
			lcEventData->args = NULL;
		}
        eventData->lcEventData = lcEventData;
        *retObj = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,CALL,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("Call()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
        JREX_LOGLN("Call()--> **** jobject_globalToLocal start lcrv->retData<"<<lcrv->retData<<"> ****")
					*retObj = jobject_globalToLocal(env,(jobject)lcrv->retData);
        JREX_LOGLN("Call()--> **** jobject_globalToLocal end ****")
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("Call()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::CallInternal(JNIEnv *env, jobject jrex_jsobj, jstring func, jobjectArray args, jobject* retObj) {
    JREX_LOGLN("CallInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retObj = Java_netscape_javascript_JSObject_call(env, jrex_jsobj, func, args);
#else
	*retObj = env->CallObjectMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectCall, func, args);
#endif
    if (NOT_NULL(*retObj)) {
		*retObj = jobject_localToGlobal(env,*retObj);
    }
	return NS_OK;
}

nsresult JRexLiveConnectSession::ToString(JNIEnv *env, jobject jrex_jsobj, jstring* retStr) {
	JREX_LOGLN("ToString()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
	*retStr = NULL;
    if(IS_EQT) {
        jstring ret = NULL;
        nsresult rv = ToStringInternal(env, jrex_jsobj, &ret);
        if (NS_SUCCEEDED(rv) && NOT_NULL(ret)) {
			*retStr = (jstring)jobject_globalToLocal(env,ret);
        }
		return rv;
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    ToStringEventData *lcEventData = new ToStringEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("ToString()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
        eventData->lcEventData = lcEventData;
        *retStr = NULL;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,TO_STRING,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("ToString()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retStr = (jstring)jobject_globalToLocal(env,(jobject)lcrv->retData);
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("ToString()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::ToStringInternal(JNIEnv *env, jobject jrex_jsobj, jstring* retStr) {
    JREX_LOGLN("ToStringInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retStr = Java_netscape_javascript_JSObject_toString(env, jrex_jsobj);
    if (NOT_NULL(retStr)) {
		*retStr = (jstring)jobject_localToGlobal(env, *retStr);
    }
#else
	jobject retObj = env->CallObjectMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectToString);
    if (NOT_NULL(retObj)) {
		*retStr = (jstring)jobject_localToGlobal(env, retObj);
    }
#endif
    return NS_OK;
}

nsresult JRexLiveConnectSession::Equals(JNIEnv *env, jobject jrex_jsobj, jobject cmp_obj, jboolean* retIsEq) {
	JREX_LOGLN("Equals()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
    if(IS_EQT) {
        return EqualsInternal(env, jrex_jsobj, cmp_obj, retIsEq);
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    EqualsEventData *lcEventData = new EqualsEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("Equals()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
		lcEventData->cmp_obj = env->NewGlobalRef(cmp_obj);
        eventData->lcEventData = lcEventData;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,EQUALS,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("Equals()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			if (IS_NULL(lcrv->ex)) {
				if (NOT_NULL(lcrv->retData)) {
					*retIsEq = (jboolean)lcrv->retData;
				}
			} else {
				CHECK_LCRV_EX(lcrv);
			}
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("Equals()--> **** rv<"<<rv<<"> ****")
    return rv;
}

nsresult JRexLiveConnectSession::EqualsInternal(JNIEnv *env, jobject jrex_jsobj, jobject cmp_obj, jboolean* retIsEq) {
    JREX_LOGLN("EqualsInternal()--> **** env<"<<env<<"> ****");
	JSOBJ_INTERNAL_CHECKSESSION
#ifdef JSOBJECT_CALL_DIRECT
	*retIsEq = Java_netscape_javascript_JSObject_equals(env, jrex_jsobj, cmp_obj);
#else
	*retIsEq = env->CallBooleanMethod(jrex_jsobj, JRexLiveConnectFields::jsObjectEquals, cmp_obj);
#endif
    return NS_OK;
}


nsresult JRexLiveConnectSession::Finalize(JNIEnv *env, jobject jrex_jsobj) {
	JREX_LOGLN("Finalize()--> **** jrex_jsobj<"<<jrex_jsobj<<"> env<"<<env<<"> ****")
    if(IS_EQT) {
        return FinalizeInternal(env, jrex_jsobj);
    }
	JSOBJ_GETSESSION
    nsresult rv=NS_OK;
    JRexLiveConnectEvent *eventData = new JRexLiveConnectEvent;
    FinalizeEventData *lcEventData = new FinalizeEventData;
    if (eventData && lcEventData) {
        JREX_LOGLN("Equals()--> **** eventData Created ****")
		eventData->session = session;
		lcEventData->jrex_jsobj = env->NewGlobalRef(jrex_jsobj);
        eventData->lcEventData = lcEventData;
        JRexLiveConnectRV* lcrv = NULL;
        rv=ExecInEventQ(nsnull,FINALIZE,eventData,PR_TRUE,HandleLiveConnectEvent,DestroyLiveConnectEvent,(void**)&lcrv);
        JREX_LOGLN("Finalize()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)) {
			CHECK_LCRV_EX(lcrv);
		}
		if (NOT_NULL(lcrv)) {
			delete lcrv;
		}
    }else
        rv=NS_ERROR_OUT_OF_MEMORY;
    JREX_LOGLN("Finalize()--> **** rv<"<<rv<<"> ****")
    return rv;
}

/* This object provides is the "anchor" by which netscape.javscript.JSObject
   objects hold a reference to native JSObjects. */
struct JSObjectHandle {
    JSObject *js_obj;
    JSRuntime *rt;
};
typedef struct JSObjectHandle JSObjectHandle;

extern JSJCallbacks jsj_jrex_callbacks;

nsresult JRexLiveConnectSession::FinalizeInternal(JNIEnv *env, jobject jrex_jsobj) {
    JREX_LOGLN("FinalizeInternal()--> **** env<"<<env<<"> ****");
	// Note: no need to call JSOBJ_INTERNAL_CHECKSESSION
	// XXX The JSObject finalize implementation does not call our jrex lc callback method. This is a bug.
	// This code properly removes the reference...
    JSBool success;
    JSObjectHandle *handle;

    success = JS_FALSE;

    handle = (JSObjectHandle*)jsj_jrex_callbacks.unwrap_java_wrapper(env, jrex_jsobj);
    JS_ASSERT(handle);
    if (!handle)
        return NS_OK; // XXX If the handle doesn't exist, assume it was garbage collected

    success = JS_RemoveRootRT(handle->rt, &handle->js_obj);
    free(handle);
	JS_ASSERT(success);
    return NS_OK;
}
