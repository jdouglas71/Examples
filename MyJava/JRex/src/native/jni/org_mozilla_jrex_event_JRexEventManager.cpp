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

#include "org_mozilla_jrex_event_JRexEventManager.h"
#include "org_mozilla_jrex_event_window_WindowEvent.h"
#include "org_mozilla_jrex_event_window_CreateEventParam.h"
#include "org_mozilla_jrex_event_history_HistoryEvent.h"
#include "org_mozilla_jrex_event_history_IntegerEventParam.h"
#include "org_mozilla_jrex_event_progress_ProgressEvent.h"
#include "org_mozilla_jrex_event_progress_StateChangeEventParam.h"
#include "org_mozilla_jrex_event_progress_ProgressChangeEventParam.h"
#include "org_mozilla_jrex_event_progress_StatusChangeEventParam.h"
#include "org_mozilla_jrex_event_context_ContextMenuEvent.h"
#include "org_mozilla_jrex_event_tooltip_TooltipEvent.h"
#include "org_mozilla_jrex_event_observer_ObserverEvent.h"
#include "org_mozilla_jrex_event_uricontent_URIContentEvent.h"
#include "org_mozilla_jrex_event_uricontent_CanHandleEventParam.h"
#include "org_mozilla_jrex_event_uricontent_DoContentEventParam.h"


#include "JRex_JNI_Event.h"
#include "JRex_JNI_WindowEvent.h"
#include "JRex_JNI_HistoryEvent.h"
#include "JRex_JNI_ProgressEvent.h"
#include "JRex_JNI_ContextMenuEvent.h"
#include "JRex_JNI_TooltipEvent.h"
#include "JRex_JNI_ObserverEvent.h"
#include "JRex_JNI_URIContentEvent.h"
#include "JRexStreamListener.h"

using namespace JREX_JNI_UTIL;
using namespace JRex_JNI_Event;
using namespace JRex_JNI_WindowEvent;
using namespace JRex_JNI_HistoryEvent;
using namespace JRex_JNI_ProgressEvent;
using namespace JRex_JNI_ContextMenuEvent;
using namespace JRex_JNI_TooltipEvent;
using namespace JRex_JNI_ObserverEvent;
using namespace JRex_JNI_URIContentEvent;

/* EventManager Fields used from native*/
jmethodID EventManagerFields::postEvtID;
jmethodID EventManagerFields::postSyncEvtID;
jmethodID EventManagerFields::postKeyEventID;
jmethodID EventManagerFields::postMouseEventID;
jclass 	  EventManagerFields::eventMgrCls;

/* WindowEvent Fields used from native*/
jclass		WindowEventFields::winEvtCls;
jmethodID	WindowEventFields::cid;

jclass		WindowEventFields::winCrtPrmCls;
jmethodID	WindowEventFields::winCrtCID;

jclass 		WindowEventFields::winDimPrmCls;
jmethodID 	WindowEventFields::dimCID;

jclass 		WindowEventFields::winBoolPrmCls;
jmethodID 	WindowEventFields::boolCID;

jclass 		WindowEventFields::winLongPrmCls;
jmethodID 	WindowEventFields::longCID;

jmethodID   WindowEventFields::intValMID;

/* HistoryEvent Fields used from native*/
jclass 		HistoryEventFields::hisEvtCls;
jmethodID 	HistoryEventFields::cid;

jclass 		HistoryEventFields::hisIntPrmCls;
jmethodID 	HistoryEventFields::hisIntCID;

jmethodID 	HistoryEventFields::boolValueID;

/* ProgressEvent Fields used from native*/
jclass 		ProgressEventFields::progEvtCls;
jmethodID 	ProgressEventFields::cid;

jclass 		ProgressEventFields::stateChangePrmCls;
jmethodID 	ProgressEventFields::stateChangeCID;

jclass 		ProgressEventFields::progressChangePrmCls;
jmethodID 	ProgressEventFields::progressChangeCID;

jclass 		ProgressEventFields::statusChangePrmCls;
jmethodID 	ProgressEventFields::statusChangeCID;

/* ContextMenuEvent Fields used from native*/
jclass 		ContextMenuEventFields::ctxEvtCls;
jmethodID 	ContextMenuEventFields::cid;

/* TooltipEvent Fields used from native*/
jclass 		TooltipEventFields::toolTipEvtCls;
jmethodID 	TooltipEventFields::cid;

/* ObserverEvent Fields used from native*/
jclass 		ObserverEventFields::observerEvtCls;
jmethodID 	ObserverEventFields::cid;

/* URIContentEvent Fields used from native*/
jclass 		URIContentEventFields::uriContentEvtCls;
jmethodID 	URIContentEventFields::cid;

jclass 		URIContentEventFields::doContentPrmCls;
jmethodID 	URIContentEventFields::doContentCID;

jclass 		URIContentEventFields::canHandlePrmCls;
jmethodID 	URIContentEventFields::canHandleCID;

jmethodID	URIContentEventFields::boolValueID;
jmethodID	URIContentEventFields::getBoolRV;
jmethodID	URIContentEventFields::getObjectRV;

/* JRexStreamListener Fields used from native*/
jmethodID	JRexStreamListener::availableMID;
jmethodID	JRexStreamListener::onStopMID;
jmethodID	JRexStreamListener::onStartMID;
jclass		JRexStreamListener::jrexInputStreamCls;
jmethodID	JRexStreamListener::jrexInputCID;
jmethodID	JRexStreamListener::jrexInputCloseMID;

/* JRexHeaderVisitor Fields used from native*/
jclass		JRexHeaderVisitor::hashTableCls;
jmethodID	JRexHeaderVisitor::hashTableCID;
jmethodID	JRexHeaderVisitor::hashTablePutMID;

/*
 * Class:     org_mozilla_jrex_event_JRexEventManager
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_JRexEventManager_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	EventManagerFields::eventMgrCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("JRexEventManager_initIDs()--> **** eventMgrCls <"<<EventManagerFields::eventMgrCls<<"> ****")
    EventManagerFields::postEvtID		= env->GetStaticMethodID(cls, "postEvent", "(ILjava/lang/Object;)V");
    JREX_LOGLN("JRexEventManager_initIDs()--> **** postEvtID <"<<EventManagerFields::postEvtID<<"> ****")
    EventManagerFields::postSyncEvtID	= env->GetStaticMethodID(cls, "postSyncEvent", "(ILjava/lang/Object;)Ljava/lang/Object;");
    JREX_LOGLN("JRexEventManager_initIDs()--> **** postSyncEvtID <"<<EventManagerFields::postSyncEvtID<<"> ****")
    EventManagerFields::postKeyEventID	= env->GetStaticMethodID(cls, "postKeyEvent", "(IIIIC)V");
    JREX_LOGLN("JRexEventManager_initIDs()--> **** postKeyEventID <"<<EventManagerFields::postKeyEventID<<"> ****")
    EventManagerFields::postMouseEventID	= env->GetStaticMethodID(cls, "postMouseEvent", "(IIIIIII)V");
    JREX_LOGLN("JRexEventManager_initIDs()--> **** postMouseEventID <"<<EventManagerFields::postMouseEventID<<"> ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_event_JRexEventManager
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_JRexEventManager_processNativeEvents
  (JNIEnv *env, jclass cls){
	JREX_LOGLN("processNativeEvents()--> **** I AM HERE ****")
	if(!gXpcomRunning)return;
	JREX_TRY
	PLEvent* event=nsnull;
	PRBool eventAvail=PR_FALSE;
	gEventQ->EventAvailable(eventAvail);
	if(eventAvail){
		nsresult rv=gEventQ->GetEvent(&event);
		if (NS_SUCCEEDED(rv))
			rv=gEventQ->HandleEvent(event);
	}
	//GetNativeEvent is a blocking call, so we need to check if event is pending then call GetNativeEvent.
	//Presently we have no X platform way to detect pending event, so doing native way.
	PRBool isAvial=PR_FALSE;
#if defined(XP_WIN32)
	   MSG nativeMsg;
	   BOOL isWinAvail= ::PeekMessage(&nativeMsg, NULL, 0, 0, PM_NOREMOVE);
	   isAvial=isWinAvail==TRUE?PR_TRUE:PR_FALSE;
#elif defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	if(g_main_pending())
		isAvial=PR_TRUE;
#endif
	if(isAvial){
	void* nativEvent=nsnull;
	PRBool isRealEvent=PR_FALSE;
	gAppShell->GetNativeEvent(isRealEvent, nativEvent);
	if(nativEvent)
		gAppShell->DispatchNativeEvent(isRealEvent, nativEvent);
	}
	PR_Sleep(PR_INTERVAL_NO_WAIT);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_event_creator_WindowEvent
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_window_WindowEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	WindowEventFields::winEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("WindowEvent_initIDs()--> **** winEvtCls <"<<WindowEventFields::winEvtCls<<"> ****")
    WindowEventFields::cid	= env->GetMethodID(cls, "<init>", "(IILjava/lang/Object;)V");
    JREX_LOGLN("WindowEvent_initIDs()--> **** cid <"<<WindowEventFields::cid<<"> ****")
	if (env->EnsureLocalCapacity(5) < 0) {
		ThrowJRexException(env, "**** WindowEvent_initIDs()-->  EnsureLocalCapacity Failed ****",0);
		return;
	}
	jclass tempcls = env->FindClass("java/awt/Dimension");
	WindowEventFields::winDimPrmCls	= (jclass)env->NewGlobalRef(tempcls);
	JREX_LOGLN("WindowEvent_initIDs()--> **** winDimPrmCls <"<<WindowEventFields::winDimPrmCls<<"> ****")
	WindowEventFields::dimCID=env->GetMethodID(WindowEventFields::winDimPrmCls,"<init>", "(II)V");
	JREX_LOGLN("WindowEvent_initIDs()--> **** dimCID <"<<WindowEventFields::dimCID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/lang/Boolean");
	WindowEventFields::winBoolPrmCls = (jclass)env->NewGlobalRef(tempcls);
	JREX_LOGLN("WindowEvent_initIDs()--> **** winBoolPrmCls <"<<WindowEventFields::winBoolPrmCls<<"> ****")
	WindowEventFields::boolCID=env->GetMethodID(WindowEventFields::winBoolPrmCls,"<init>", "(Z)V");
	JREX_LOGLN("WindowEvent_initIDs()--> **** boolCID <"<<WindowEventFields::boolCID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/lang/Long");
	WindowEventFields::winLongPrmCls = (jclass)env->NewGlobalRef(tempcls);
	JREX_LOGLN("WindowEvent_initIDs()--> **** winLongPrmCls <"<<WindowEventFields::winLongPrmCls<<"> ****")
	WindowEventFields::longCID=env->GetMethodID(tempcls,"<init>", "(J)V");
	JREX_LOGLN("WindowEvent_initIDs()--> **** longCID <"<<WindowEventFields::longCID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/lang/Integer");
	WindowEventFields::intValMID=env->GetMethodID(tempcls,"intValue", "()I");
	JREX_LOGLN("WindowEvent_initIDs()--> **** intValMID <"<<WindowEventFields::intValMID<<"> ****")
	env->DeleteLocalRef(tempcls);

    JREX_CATCH(env)
}


JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_window_CreateEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	WindowEventFields::winCrtPrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("WindowCreateEventParam_initIDs()--> **** winCrtPrmCls <"<<WindowEventFields::winCrtPrmCls<<"> ****")
    WindowEventFields::winCrtCID	= env->GetMethodID(cls, "<init>", "(IJILjava/lang/String;)V");
    JREX_LOGLN("WindowCreateEventParam_initIDs()--> **** winCrtCID <"<<WindowEventFields::winCrtCID<<"> ****")
    JREX_CATCH(env)
}



/*
 * Class:     org_mozilla_jrex_event_history_HistoryEvent
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_history_HistoryEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	HistoryEventFields::hisEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("HistoryEvent_initIDs()--> **** hisEvtCls <"<<HistoryEventFields::hisEvtCls<<"> ****")
    HistoryEventFields::cid	= env->GetMethodID(cls, "<init>", "(IILjava/lang/Object;)V");
    JREX_LOGLN("HistoryEvent_initIDs()--> **** cid <"<<HistoryEventFields::cid<<"> ****")
	if (env->EnsureLocalCapacity(2) < 0) {
		ThrowJRexException(env, "**** HistoryEvent_initIDs()-->  EnsureLocalCapacity Failed ****",0);
		return;
	}
	jclass tempcls = env->FindClass("java/lang/Boolean");
	HistoryEventFields::boolValueID=env->GetMethodID(tempcls,"booleanValue", "()Z");
	JREX_LOGLN("HistoryEvent_initIDs()--> **** boolValueID <"<<HistoryEventFields::boolValueID<<"> ****")
	env->DeleteLocalRef(tempcls);
    JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_event_history_HistoryIntegerEventParam
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_history_IntegerEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	HistoryEventFields::hisIntPrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("HistoryIntegerEventParam_initIDs()--> **** hisIntPrmCls <"<<HistoryEventFields::hisIntPrmCls<<"> ****")
    HistoryEventFields::hisIntCID	= env->GetMethodID(cls, "<init>", "(ILjava/lang/String;)V");
    JREX_LOGLN("HistoryIntegerEventParam_initIDs()--> **** hisIntCID <"<<HistoryEventFields::hisIntCID<<"> ****")
    JREX_CATCH(env)

}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_progress_ProgressEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ProgressEventFields::progEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("ProgressEvent_initIDs()--> **** progEvtCls <"<<ProgressEventFields::progEvtCls<<"> ****")
    ProgressEventFields::cid	= env->GetMethodID(cls, "<init>", "(IIZLjava/lang/String;IZLjava/lang/Object;)V");
    JREX_LOGLN("ProgressEvent_initIDs()--> **** cid <"<<ProgressEventFields::cid<<"> ****")
    JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_progress_StateChangeEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ProgressEventFields::stateChangePrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("StateChangeEventParam_initIDs()--> **** stateChangePrmCls <"<<ProgressEventFields::stateChangePrmCls<<"> ****")
    ProgressEventFields::stateChangeCID	= env->GetMethodID(cls, "<init>", "(IILjava/util/Hashtable;Ljava/util/Hashtable;)V");
    JREX_LOGLN("StateChangeEventParam_initIDs()--> **** stateChangeCID <"<<ProgressEventFields::stateChangeCID<<"> ****")
    JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_progress_ProgressChangeEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ProgressEventFields::progressChangePrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("ProgressChangeEventParam_initIDs()--> **** progressChangePrmCls <"<<ProgressEventFields::progressChangePrmCls<<"> ****")
    ProgressEventFields::progressChangeCID	= env->GetMethodID(cls, "<init>", "(IIII)V");
    JREX_LOGLN("ProgressChangeEventParam_initIDs()--> **** progressChangeCID <"<<ProgressEventFields::progressChangeCID<<"> ****")
    JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_progress_StatusChangeEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ProgressEventFields::statusChangePrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("StatusChangeEventParam_initIDs()--> **** statusChangePrmCls <"<<ProgressEventFields::statusChangePrmCls<<"> ****")
    ProgressEventFields::statusChangeCID	= env->GetMethodID(cls, "<init>", "(ILjava/lang/String;)V");
    JREX_LOGLN("StatusChangeEventParam_initIDs()--> **** statusChangeCID <"<<ProgressEventFields::statusChangeCID<<"> ****")
    JREX_CATCH(env)
}


JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_context_ContextMenuEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ContextMenuEventFields::ctxEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("ContextMenuEvent_initIDs()--> **** ctxEvtCls <"<<ContextMenuEventFields::ctxEvtCls<<"> ****")
    ContextMenuEventFields::cid	= env->GetMethodID(cls, "<init>", "(IIIILorg/w3c/dom/Node;ILjava/lang/String;Ljava/lang/String;)V");
    JREX_LOGLN("ContextMenuEvent_initIDs()--> **** cid <"<<ContextMenuEventFields::cid<<"> ****")
    JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_tooltip_TooltipEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	TooltipEventFields::toolTipEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("TooltipEvent_initIDs()--> **** toolTipEvtCls <"<<TooltipEventFields::toolTipEvtCls<<"> ****")
    TooltipEventFields::cid	= env->GetMethodID(cls, "<init>", "(IIIILjava/lang/String;)V");
    JREX_LOGLN("TooltipEvent_initIDs()--> **** cid <"<<TooltipEventFields::cid<<"> ****")
    JREX_CATCH(env)
}


JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_observer_ObserverEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	ObserverEventFields::observerEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("ObserverEvent_initIDs()--> **** observerEvtCls <"<<ObserverEventFields::observerEvtCls<<"> ****")
    ObserverEventFields::cid	= env->GetMethodID(cls, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    JREX_LOGLN("ObserverEvent_initIDs()--> **** cid <"<<ObserverEventFields::cid<<"> ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_event_uricontent_URIContentEvent
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_uricontent_URIContentEvent_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	URIContentEventFields::uriContentEvtCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("URIContentEvent_initIDs()--> **** uriContentEvtCls <"<<URIContentEventFields::uriContentEvtCls<<"> ****")
    URIContentEventFields::cid	= env->GetMethodID(cls, "<init>", "(IILjava/lang/Object;)V");
    JREX_LOGLN("URIContentEvent_initIDs()--> **** cid <"<<URIContentEventFields::cid<<"> ****")

	if (env->EnsureLocalCapacity(6) < 0) {
		ThrowJRexException(env, "**** URIContentEvent_initIDs()-->  EnsureLocalCapacity Failed ****",0);
		return;
	}

	jclass tempcls = env->FindClass("org/mozilla/jrex/io/JRexInputStream");
	JRexStreamListener::jrexInputStreamCls	= (jclass)env->NewGlobalRef(tempcls);
	JREX_LOGLN("URIContentEvent_initIDs()--> **** jrexInputStreamCls <"<<JRexStreamListener::jrexInputStreamCls<<"> ****")

	JRexStreamListener::jrexInputCID=env->GetMethodID(tempcls,"<init>", "(I)V");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** jrexInputCID <"<<JRexStreamListener::jrexInputCID<<"> ****")
	JRexStreamListener::jrexInputCloseMID=env->GetMethodID(tempcls,"close", "()V");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** jrexInputCloseMID <"<<JRexStreamListener::jrexInputCloseMID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("org/mozilla/jrex/io/JRexStreamListener");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** JRexStreamListenerCls <"<<tempcls<<"> ****")
	JRexStreamListener::onStartMID=env->GetMethodID(tempcls,"onStartRequest", "(Ljava/lang/String;IZLjava/lang/Object;Ljava/util/Hashtable;)Z");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** onStartMID <"<<JRexStreamListener::onStartMID<<"> ****")
	JRexStreamListener::availableMID=env->GetMethodID(tempcls,"onDataAvailable", "(Ljava/lang/String;IZLjava/lang/Object;Lorg/mozilla/jrex/io/JRexInputStream;II)Z");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** availableMID <"<<JRexStreamListener::availableMID<<"> ****")
	JRexStreamListener::onStopMID=env->GetMethodID(tempcls,"onStopRequest", "(Ljava/lang/String;IZLjava/lang/Object;I)V");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** onStopMID <"<<JRexStreamListener::onStopMID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/util/Hashtable");
	JRexHeaderVisitor::hashTableCls	= (jclass)env->NewGlobalRef(tempcls);
	JREX_LOGLN("URIContentEvent_initIDs()--> **** hashTableCls <"<<JRexHeaderVisitor::hashTableCls<<"> ****")
	JRexHeaderVisitor::hashTableCID=env->GetMethodID(tempcls,"<init>", "(I)V");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** hashTableCID <"<<JRexHeaderVisitor::hashTableCID<<"> ****")
	JRexHeaderVisitor::hashTablePutMID=env->GetMethodID(tempcls,"put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** hashTablePutMID <"<<JRexHeaderVisitor::hashTablePutMID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("org/mozilla/jrex/event/uricontent/URIContentEventRV");
	URIContentEventFields::getBoolRV=env->GetMethodID(tempcls,"getBoolRV", "()Z");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** getBoolRV <"<<URIContentEventFields::getBoolRV<<"> ****")
	URIContentEventFields::getObjectRV=env->GetMethodID(tempcls,"getObjectRV", "()Ljava/lang/Object;");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** getObjectRV <"<<URIContentEventFields::getObjectRV<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/lang/Boolean");
	URIContentEventFields::boolValueID=env->GetMethodID(tempcls,"booleanValue", "()Z");
	JREX_LOGLN("URIContentEvent_initIDs()--> **** boolValueID <"<<URIContentEventFields::boolValueID<<"> ****")
	env->DeleteLocalRef(tempcls);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_event_uricontent_DoContentEventParam
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_uricontent_DoContentEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	URIContentEventFields::doContentPrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("DoContentEventParam_initIDs()--> **** doContentPrmCls <"<<URIContentEventFields::doContentPrmCls<<"> ****")
	URIContentEventFields::doContentCID	= env->GetMethodID(cls, "<init>", "(ZLjava/lang/String;Ljava/lang/String;IZ)V");
	JREX_LOGLN("DoContentEventParam_initIDs()--> **** doContentCID <"<<URIContentEventFields::doContentCID<<"> ****")
	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_event_uricontent_CanHandleEventParam
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_event_uricontent_CanHandleEventParam_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
	URIContentEventFields::canHandlePrmCls	= (jclass)env->NewGlobalRef(cls);
	JREX_LOGLN("CanHandleEventParam_initIDs()--> **** canHandlePrmCls <"<<URIContentEventFields::canHandlePrmCls<<"> ****")
	URIContentEventFields::canHandleCID	= env->GetMethodID(cls, "<init>", "(ZLjava/lang/String;)V");
	JREX_LOGLN("CanHandleEventParam_initIDs()--> **** canHandleCID <"<<URIContentEventFields::canHandleCID<<"> ****")
	JREX_CATCH(env)
}
