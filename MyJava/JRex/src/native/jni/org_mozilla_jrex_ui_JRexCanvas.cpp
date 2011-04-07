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

#include "org_mozilla_jrex_ui_JRexCanvas.h"
#include "JRex_JNI_Util.h"
#include "JRexWindow.h"
#include "JRexCanvas.h"
#if defined(JREX_DOM)
	#include "JRexDOMGlobals.h"
#endif
#include "JRexInputStream.h" //Note JRexInputStream jni fileds are intialized in org_mozilla_jrex_navigation_WebNavigationImpl.cpp
#include "org_mozilla_jrex_ui_JRexFindConfig.h"

#if defined(XP_MAC) || defined(XP_MACOSX)
	#include <Cocoa/Cocoa.h>
#endif

using namespace JREX_JNI_UTIL;

jfieldID JRexCanvasFields::peerID;
jfieldID JRexCanvasFields::xID;
jfieldID JRexCanvasFields::yID;
jfieldID JRexCanvasFields::widthID;
jfieldID JRexCanvasFields::heightID;

jmethodID JRexCanvasFields::hashGetMID;
jmethodID JRexCanvasFields::boolValueMID;

jclass JRexCanvasFields::findConfigCls;
jmethodID JRexCanvasFields::findConfigCID;
jfieldID JRexCanvasFields::fcSearchStringID;
jfieldID JRexCanvasFields::fcFindBackwardsID;
jfieldID JRexCanvasFields::fcWrapFindID;
jfieldID JRexCanvasFields::fcEntireWordID;
jfieldID JRexCanvasFields::fcMatchCaseID;
jfieldID JRexCanvasFields::fcSearchFramesID;



inline nsNativeWidget GetNativeWindowPointer(JNIEnv *env, jobject component){
	JREX_LOGLN("GetNativeWindowPointer()--> **** Inside ****")

	JAWT awt;
	awt.version=JAWT_VERSION_1_4;
	jboolean rv=JAWT_GetAWT(env, &awt);
	if(rv==JNI_FALSE)
		ThrowJRexException(env, "GetNativeWindowPointer()-->Could not get JAWT, is component HEADLESS ?",0);
	JREX_LOGLN("GetNativeWindowPointer()--> **** GOT JAWT ****")

	JAWT_DrawingSurface* ds=awt.GetDrawingSurface(env,component);
	if(IS_NULL(ds))
		ThrowJRexException(env, "GetNativeWindowPointer()-->Could not get JAWT_DrawingSurface",0);
	JREX_LOGLN("GetNativeWindowPointer()--> **** GOT JAWT_DrawingSurface ****")

	jint lock = ds->Lock(ds);
	if(lock & JAWT_LOCK_ERROR)
		ThrowJRexException(env, "GetNativeWindowPointer()-->Could not lock DrawingSurface JAWT_LOCK_ERROR",0);
	JREX_LOGLN("GetNativeWindowPointer()--> **** LOCKED JAWT_DrawingSurface ****")

	JAWT_DrawingSurfaceInfo* dsInf=ds->GetDrawingSurfaceInfo(ds);
	if(IS_NULL(dsInf))
		ThrowJRexException(env, "GetNativeWindowPointer()-->Could not get JAWT_DrawingSurfaceInfo",0);
	JREX_LOGLN("GetNativeWindowPointer()--> **** GOT JAWT_DrawingSurfaceInfo ****")

#if defined(XP_WIN32) || defined(XP_OS2)
	nsNativeWidget mainWnd=((JAWT_Win32DrawingSurfaceInfo*)dsInf->platformInfo)->hwnd;
#elif defined(XP_MAC) || defined(XP_MACOSX)
	NSView *view=((JAWT_MacOSXDrawingSurfaceInfo*)dsInf->platformInfo)->cocoaViewRef;
	nsNativeWidget mainWnd = view;//[view window];
#else
	Display *myDis=((JAWT_X11DrawingSurfaceInfo*)dsInf->platformInfo)->display;
	Window myWin=(Window)((JAWT_X11DrawingSurfaceInfo*)dsInf->platformInfo)->drawable;
	JREX_LOGLN("GetNativeWindowPointer()--> **** Display<"<<myDis<<"> myWin<"<<myWin<<">****")
	if(myWin==0)myWin=XDefaultRootWindow(myDis);//what is this?
	nsNativeWidget mainWnd=(nsNativeWidget)myWin;
#endif
	JREX_LOGLN("GetNativeWindowPointer()--> **** mainWnd<"<<mainWnd<<"> ****")
	if(IS_NULL(mainWnd))
		ThrowJRexException(env, "GetNativeWindowPointer()-->Could not get handle to main Window",0);//does this occur?

	JREX_LOGLN("GetNativeWindowPointer()--> **** GOT THE MAIN WINDOW POINTER <"<<mainWnd<<"> ****")

	ds->FreeDrawingSurfaceInfo(dsInf);
	JREX_LOGLN("GetNativeWindowPointer()--> **** FreeDrawingSurfaceInfo done ****")
	ds->Unlock(ds);
	JREX_LOGLN("GetNativeWindowPointer()--> **** Unlock done ****")
	awt.FreeDrawingSurface(ds);
	JREX_LOGLN("GetNativeWindowPointer()--> **** FreeDrawingSurface done ****")
	return mainWnd;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
    JRexCanvasFields::peerID	= env->GetFieldID(cls, "jrexPeer", "I");
    JREX_LOGLN("JRexCanvas_initIDs()--> **** peerID <"<<JRexCanvasFields::peerID<<"> ****")
    JRexCanvasFields::xID		= env->GetFieldID(cls, "x", "I");
    JREX_LOGLN("JRexCanvas_initIDs()--> **** xID <"<<JRexCanvasFields::xID<<"> ****")
    JRexCanvasFields::yID		= env->GetFieldID(cls, "y", "I");
    JREX_LOGLN("JRexCanvas_initIDs()--> **** yID <"<<JRexCanvasFields::yID<<"> ****")
    JRexCanvasFields::heightID	= env->GetFieldID(cls, "height", "I");
    JREX_LOGLN("JRexCanvas_initIDs()--> **** heightID <"<<JRexCanvasFields::heightID<<"> ****")
    JRexCanvasFields::widthID	= env->GetFieldID(cls, "width", "I");
    JREX_LOGLN("JRexCanvas_initIDs()--> **** widthID <"<<JRexCanvasFields::widthID<<"> ****")

	jclass tempcls = env->FindClass("java/util/Hashtable");
	JRexCanvasFields::hashGetMID=env->GetMethodID(tempcls,"get", "(Ljava/lang/Object;)Ljava/lang/Object;");
	JREX_LOGLN("JRexCanvas_initIDs()--> **** hashGetMID <"<<JRexCanvasFields::hashGetMID<<"> ****")
	env->DeleteLocalRef(tempcls);

	tempcls = env->FindClass("java/lang/Boolean");
	JRexCanvasFields::boolValueMID=env->GetMethodID(tempcls,"booleanValue", "()Z");
	JREX_LOGLN("JRexCanvas_initIDs()--> **** boolValueMID <"<<JRexCanvasFields::boolValueMID<<"> ****")
	env->DeleteLocalRef(tempcls);
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexFindConfig
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexFindConfig_initIDs
  (JNIEnv *env, jclass cls){
	JREX_TRY
    JRexCanvasFields::findConfigCls	= (jclass)env->NewGlobalRef(cls);
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** findConfigCls <"<<JRexCanvasFields::findConfigCls<<"> ****")\
	JRexCanvasFields::findConfigCID	= env->GetMethodID(cls, "<init>", "(Ljava/lang/String;ZZZZZ)V");
	JREX_LOGLN("JRexFindConfig_initIDs()--> **** findConfigCID <"<<JRexCanvasFields::findConfigCID<<"> ****")
    JRexCanvasFields::fcSearchStringID	= env->GetFieldID(cls, "searchString", "Ljava/lang/String;");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcSearchStringID <"<<JRexCanvasFields::fcSearchStringID<<"> ****")
    JRexCanvasFields::fcFindBackwardsID	= env->GetFieldID(cls, "findBackwards", "Z");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcFindBackwardsID <"<<JRexCanvasFields::fcFindBackwardsID<<"> ****")
    JRexCanvasFields::fcWrapFindID	= env->GetFieldID(cls, "wrapFind", "Z");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcWrapFindID <"<<JRexCanvasFields::fcWrapFindID<<"> ****")
    JRexCanvasFields::fcEntireWordID	= env->GetFieldID(cls, "entireWord", "Z");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcEntireWordID <"<<JRexCanvasFields::fcEntireWordID<<"> ****")
    JRexCanvasFields::fcMatchCaseID	= env->GetFieldID(cls, "matchCase", "Z");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcMatchCaseID <"<<JRexCanvasFields::fcMatchCaseID<<"> ****")
    JRexCanvasFields::fcSearchFramesID	= env->GetFieldID(cls, "searchFrames", "Z");
    JREX_LOGLN("JRexFindConfig_initIDs()--> **** fcSearchFramesID <"<<JRexCanvasFields::fcSearchFramesID<<"> ****")
    JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    createPeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CreatePeer
  (JNIEnv *env, jobject jrexCanvas, jobject jbrowserSetupFlag){
	if(!gXpcomRunning)return;
	JREX_TRY
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	JREX_LOGLN("CreatePeer()--> **** MOZ_WIDGET_GTK ***")
	nsNativeWidget mainWnd=nsnull;
#else
	JREX_LOGLN("CreatePeer()--> **** WIN32 ***")
	nsNativeWidget mainWnd=GetNativeWindowPointer(env,jrexCanvas);
#endif
	JREX_LOGLN("CreatePeer()--> **** mainWnd <"<<mainWnd<<"> jbrowserSetupFlag <"<<jbrowserSetupFlag<<"> ****")

	nsDataHashtable<nsUint32HashKey,PRUint32> *browserSetupFlag=nsnull;
	if(NOT_NULL(jbrowserSetupFlag)){
		browserSetupFlag=new nsDataHashtable<nsUint32HashKey,PRUint32>();
		if (env->EnsureLocalCapacity(9) < 0) {
			ThrowJRexException(env, "**** CreatePeer()-->  EnsureLocalCapacity Failed ****",0);
		}

		if(!browserSetupFlag->Init(9))
			ThrowJRexException(env, "**** CreatePeer-->  Could not create nsDataHashtable ****",0);

		jobject boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.allow.plugin"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.allow.javascript"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_ALLOW_JAVASCRIPT,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.allow.metaredirects"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_ALLOW_META_REDIRECTS,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.allow.subframes"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_ALLOW_SUBFRAMES,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.allow.images"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_ALLOW_IMAGES,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.ischromewrapper"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_IS_CHROME_WRAPPER,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));

		boolVal=env->CallObjectMethod(jbrowserSetupFlag,JRexCanvasFields::hashGetMID,env->NewStringUTF("jrex.browser.useglobalhistory"));
		if(NOT_NULL(boolVal))
			browserSetupFlag->Put(nsIWebBrowserSetup::SETUP_USE_GLOBAL_HISTORY,
								(PRUint32)env->CallBooleanMethod(boolVal,JRexCanvasFields::boolValueMID));
	}

	JRexWindow *window=new JRexWindow(mainWnd, browserSetupFlag);
	if(IS_NULL(window))
		ThrowJRexException(env, "**** CreatePeer-->  Could not create native JRexWindow ****",0);
	env->SetIntField(jrexCanvas, JRexCanvasFields::peerID,(jint)NS_PTR_TO_INT32(window));
	JREX_LOGLN("CreatePeer()--> **** SetIntField <"<<window<<"> ****")
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RealizePeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GotVisual
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GotVisual()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
			|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GotVisual()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return;
	}
	nsNativeWidget parentWnd=GetNativeWindowPointer(env,jrexCanvas);
	window->GotVisual(parentWnd);
	JREX_CATCH(env)
#endif
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RealizePeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RealizePeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RealizePeer()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RealizePeer()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return;
	}
    PRInt32 x		= env->GetIntField(jrexCanvas, JRexCanvasFields::xID);
    PRInt32 y		= env->GetIntField(jrexCanvas, JRexCanvasFields::yID);
    PRInt32 width	= env->GetIntField(jrexCanvas, JRexCanvasFields::widthID);
    PRInt32 height	= env->GetIntField(jrexCanvas, JRexCanvasFields::heightID);

	JREX_LOGLN("RealizePeer()--> **** Calling window->show x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<">****")
	nsresult rv =window->Show(x,y,width,height);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RealizePeer()-->  JRexWindow show Failed ****",rv);
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    destroyPeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_DestroyPeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("DestroyPeer()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** DestroyPeer()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return;
	}
	window->Dispose();
	env->SetIntField(jrexCanvas , JRexCanvasFields::peerID,0);
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    BoundsChangedPeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetBoundsPeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetBoundsPeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetBoundsPeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
    PRInt32 x		= 0;//env->GetIntField(jrexCanvas, JRexCanvasFields::xID);
    PRInt32 y		= 0;//env->GetIntField(jrexCanvas, JRexCanvasFields::yID);
    PRInt32 width	= env->GetIntField(jrexCanvas, JRexCanvasFields::widthID);
    PRInt32 height	= env->GetIntField(jrexCanvas, JRexCanvasFields::heightID);
  	nsresult rv=window->SetBounds(x,y,width,height);
	JREX_LOGLN("SetBoundsPeer()--> **** window->SetBounds called ****")

	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetBoundsPeer()-->  JRexWindow SetBounds Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    BoundsChangedPeer
 * Signature: ()V
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetBoundsPeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return NULL;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetBoundsPeer()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetBoundsPeer()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}

    PRInt32 x;
    PRInt32 y;
    PRInt32 width;
    PRInt32 height;
    nsresult rv=window->GetBounds(&x,&y,&width,&height);
	if (NS_FAILED(rv)){
		ThrowJRexException(env, "**** GetBoundsPeer()-->  JRexWindow SetBounds Failed ****",rv);
		return NULL;
	}
	JREX_LOGLN("GetBoundsPeer()--> **** Got x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<"> ****")

	//Rectangle(int x, int y, int width, int height)
 	if (env->EnsureLocalCapacity(2) < 0) {
		ThrowJRexException(env, "**** GetBoundsPeer()-->  EnsureLocalCapacity Failed ****",0);
		return NULL;
    }
    jclass cls = env->FindClass("java/awt/Rectangle");
    jmethodID cid=env->GetMethodID(cls,"<init>", "(IIII)V");
    jobject rectObj=env->NewObject(cls,cid,(jint)x,(jint)y,(jint)width,(jint)height);
    JNI_IF_EXP_DESC_CLR_RET("GetBoundsPeer()--> **** New rectObj Failed with Exception ****", (jobject)NULL)
	env->DeleteLocalRef(cls);
	return rectObj;
  	JREX_CATCH(env)
  	return NULL;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SetVisiblePeer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetVisiblePeer
  (JNIEnv *env, jobject jrexCanvas, jboolean visible){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetVisiblePeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetVisiblePeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}

	nsresult rv=window->SetVisible(visible==JNI_TRUE?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetVisiblePeer()-->  JRexWindow SetVisible Failed ****",rv);
  	JREX_CATCH(env)

}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SetEnabledPeer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetEnabledPeer
  (JNIEnv *env, jobject jrexCanvas, jboolean enabled){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetEnabledPeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetEnabledPeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}

	nsresult rv=window->SetEnabled(enabled==JNI_TRUE?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetEnabledPeer()-->  JRexWindow SetEnabled Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    IsVisiblePeer
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_IsVisiblePeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("IsVisiblePeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** IsVisiblePeer()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool temp=PR_FALSE;
	nsresult rv=window->IsVisible(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsVisiblePeer()-->  JRexWindow IsVisible Failed ****",rv);

	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    IsEnabledPeer
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_IsEnabledPeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("IsEnabledPeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** IsEnabledPeer()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	PRBool temp=PR_FALSE;
	nsresult rv=window->IsEnabled(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsEnabledPeer()-->  JRexWindow IsEnabled Failed ****",rv);

	return temp==PR_TRUE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    GetTitlePeer
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetTitlePeer
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return NULL;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetTitlePeer()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetTitlePeer()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}

	nsXPIDLString title;
	nsresult rv=window->GetTitle(getter_Copies(title));
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetTitlePeer()-->  JRexWindow GetBaseTitle Failed ****",rv);

	NS_STR_TO_JSTR_RET(env,title)
  	JREX_CATCH(env)
  	return NULL;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SetTitlePeer
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetTitlePeer
  (JNIEnv *env, jobject jrexCanvas, jstring jtitle){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetTitlePeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window) || IS_NULL(jtitle)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetTitlePeer()-->YOU/jtitle DO NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* title=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtitle, title);

	nsresult rv=window->SetBaseTitle(title);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetTitlePeer()-->  JRexWindow SetBaseTitle Failed ****",rv);
  	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RepaintPeer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RepaintPeer
  (JNIEnv *env, jobject jrexCanvas, jboolean force){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RepaintPeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RepaintPeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Repaint(force==JNI_TRUE?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RepaintPeer()-->  JRexWindow Repaint Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SetFocusPeer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetFocusPeer
  (JNIEnv *env, jobject jrexCanvas, jboolean focusGained){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetFocusPeer()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetFocusPeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->ChangeFocus(focusGained?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetFocusPeer()-->  JRexWindow SetFocus Failed ****",rv);
  	JREX_CATCH(env)

}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    MoveFocusPeer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_MoveFocusPeer
  (JNIEnv *env, jobject jrexCanvas, jboolean jforward){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("MoveFocusPeer()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** MoveFocusPeer()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->MoveFocus(jforward?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** MoveFocusPeer()-->  JRexWindow MoveFocus Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    GetFocusedElement
 * Signature: ()Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetFocusedElement
  (JNIEnv *env, jobject jrexCanvas){
#if defined(JREX_DOM)
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetFocusedElement()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetFocusedElement()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMElement* myEle=nsnull;//no nsCOMPtr since not thread-safe
    nsresult rv=window->GetFocusedElement(&myEle);
	JREX_LOGLN("GetFocusedElement()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && myEle){
		JREX_LOGLN("GetFocusedElement()--> *** NOT_NULL myEle ***")
		jobject jobj=JRexDOMGlobals::CreateNodeByType(env, myEle,PR_FALSE);
		return jobj;
	}
	JREX_LOGLN("GetFocusedElement()--> *** GetFocusedElement Failed ***")
  	JREX_CATCH(env)
#endif
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    SetFocusedElement
 * Signature: (Lorg/w3c/dom/Element;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetFocusedElement
  (JNIEnv *env, jobject jrexCanvas, jobject jdomEle){
#if defined(JREX_DOM)
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	nsIDOMElement* focusEle=(nsIDOMElement*)NS_INT32_TO_PTR(env->GetIntField(jdomEle, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetFocusedElement()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window) || IS_NULL(focusEle)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetFocusedElement()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=window->SetFocusedElement(focusEle);
	JREX_LOGLN("SetFocusedElement()--> *** rv<"<<rv<<"> ***")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetFocusedElement()-->  JRexWindow SetFocusedElement Failed ****",rv);
  	JREX_CATCH(env)
#endif
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Print
 * Signature: (ZZ)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Print
  (JNIEnv *env, jobject jrexCanvas, jboolean prompt, jboolean showProgress){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Print()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Print()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Print(prompt?PR_TRUE:PR_FALSE,showProgress?PR_TRUE:PR_FALSE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Print()-->  JRexWindow Print Failed ****",rv);
  	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Print
 * Signature: (ZZ)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CancelPrint
  (JNIEnv *env, jobject jrexCanvas, jboolean prompt, jboolean showProgress){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CancelPrint()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CancelPrint()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CancelPrint();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CancelPrint()-->  JRexWindow Print Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    IsPrinting
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_IsPrinting
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("IsPrinting()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** IsPrinting()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool isPrinting=PR_FALSE;
	nsresult rv=window->IsPrinting(&isPrinting);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsPrinting()--> IsPrinting Failed ****",rv);
	return isPrinting==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    PrintPreview
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_PrintPreview
  (JNIEnv *env, jobject jrexCanvas, jboolean jshrinkToFit, jboolean jisLandScape){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("PrintPreview()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** PrintPreview()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->PrintPreview(jshrinkToFit==JNI_TRUE,jisLandScape==JNI_TRUE);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** PrintPreview()-->  JRexWindow PrintPreview Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    GetPrintPreviewNumPages
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetPrintPreviewNumPages
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return 0;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetPrintPreviewNumPages()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetPrintPreviewNumPages()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 numOfPage=0;
	nsresult rv=window->GetPrintPreviewNumPages(&numOfPage);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetPrintPreviewNumPages()-->  GetPrintPreviewNumPages Failed ****",rv);
	return (jint)numOfPage;
  	JREX_CATCH(env)
  	return 0;
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CancelPrintPreview
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CancelPrintPreview
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CancelPrintPreview()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CancelPrintPreview()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CancelPrintPreview();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CancelPrintPreview()-->  JRexWindow CancelPrintPreview Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    IsPreviewing
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_IsPrintPreviewing
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("IsPrintPreviewing()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** IsPrintPreviewing()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool isPreviewing=PR_FALSE;
	nsresult rv=window->IsPrintPreviewing(&isPreviewing);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsPrintPreviewing()--> IsPrintPreviewing Failed ****",rv);
	return isPreviewing==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    PrintPreviewNavigate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_PrintPreviewNavigate
  (JNIEnv *env, jobject jrexCanvas, jint navType, jint pageNum){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("PrintPreviewNavigate()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** PrintPreviewNavigate()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->PrintPreviewNavigate(navType,pageNum);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** PrintPreviewNavigate()-->  JRexWindow PrintPreviewNavigate Failed ****",rv);
  	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    PageSetup
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_PageSetup
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("PageSetup()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** PageSetup()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->PageSetup();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** PageSetup()-->  JRexWindow PageSetup Failed ****",rv);
  	JREX_CATCH(env)

}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanUndo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanUndo
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanUndo()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanUndo()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanUndo(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanUndo()-->  JRexWindow CanUndo Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanRedo
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanRedo
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanRedo()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanRedo()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanRedo(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanRedo()-->  JRexWindow CanRedo Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanCut
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanCut
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanCut()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanCut()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanCut(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanCut()-->  JRexWindow CanCut Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanCopy
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanCopy
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanCopy()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanCopy()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanCopy(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanCopy()-->  JRexWindow CanCopy Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;

}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanCopyLinkLocation
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanCopyLinkLocation
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanCopyLinkLocation()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanCopyLinkLocation()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanCopyLinkLocation(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanCopyLinkLocation()-->  JRexWindow CanCopyLinkLocation Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;

}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanCopyImageLocation
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanCopyImageLocation
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanCopyImageLocation()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanCopyImageLocation()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanCopyImageLocation(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanCopyImageLocation()-->  JRexWindow CanCopyImageLocation Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;

}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanCopyImageContents
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanCopyImageContents
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanCopyImageContents()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanCopyImageContents()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanCopyImageContents(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanCopyImageContents()-->  JRexWindow CanCopyImageContents Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;

}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanPaste
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanPaste
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanPaste()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanPaste()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanPaste(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanPaste()-->  JRexWindow CanPaste Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;

}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CanDelete
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CanDelete
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CanDelete()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CanDelete()-->YOU DO NOT EXIST!!! ****",0);
		return PR_FALSE;
	}
	PRBool temp=PR_FALSE;
	nsresult rv=window->CanDelete(&temp);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CanDelete()-->  JRexWindow CanDelete Failed ****",rv);
	return temp==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Undo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Undo
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Undo()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Undo()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Undo();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Undo()-->  JRexWindow Undo Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Redo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Redo
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Redo()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Redo()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Redo();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Redo()-->  JRexWindow Cut Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Cut
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Cut
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Cut()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Cut()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Cut();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Cut()-->  JRexWindow Cut Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Copy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Copy
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Copy()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Copy()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Copy();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Copy()-->  JRexWindow Copy Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CopyLinkLocation
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CopyLinkLocation
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CopyLinkLocation()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CopyLinkLocation()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CopyLinkLocation();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CopyLinkLocation()-->  JRexWindow CopyLinkLocation Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CopyImageLocation
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CopyImageLocation
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CopyImageLocation()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CopyImageLocation()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CopyImageLocation();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CopyImageLocation()-->  JRexWindow CopyImageLocation Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    CopyImageContents
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CopyImageContents
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CopyImageContents()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CopyImageContents()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CopyImageContents();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CopyImageContents()-->  JRexWindow Cut Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Paste
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Paste
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Paste()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Paste()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Paste();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Paste()-->  JRexWindow Cut Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SelectAll
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SelectAll
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SelectAll()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SelectAll()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->SelectAll();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SelectAll()-->  JRexWindow SelectAll Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    SelectNone
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SelectNone
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SelectNone()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SelectNone()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->SelectNone();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SelectNone()-->  JRexWindow SelectNone Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Delete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Delete
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Delete()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Delete()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->Delete();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Delete()-->  JRexWindow Delete Failed ****",rv);
  	JREX_CATCH(env)
}
/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    Find
 * Signature: ()V
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_Find
  (JNIEnv *env, jobject jrexCanvas, jobject jfindConfig){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("Find()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Find()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return JNI_FALSE;
	}

    jstring jsrchStr	= (jstring)env->GetObjectField(jfindConfig, JRexCanvasFields::fcSearchStringID);
    jboolean findBack	= env->GetBooleanField(jfindConfig, JRexCanvasFields::fcFindBackwardsID);
    jboolean wrapFind	= env->GetBooleanField(jfindConfig, JRexCanvasFields::fcWrapFindID);
    jboolean entireWord	= env->GetBooleanField(jfindConfig, JRexCanvasFields::fcEntireWordID);
    jboolean matchCase	= env->GetBooleanField(jfindConfig, JRexCanvasFields::fcMatchCaseID);
    jboolean searchFrames	= env->GetBooleanField(jfindConfig, JRexCanvasFields::fcSearchFramesID);

	PRUnichar* srchStr=nsnull;
	JSTR_TO_NEW_PRUNI(env, jsrchStr, srchStr);

	JREX_LOGLN("Find()--> **** Calling window->Find findBack<"<<findBack<<"> wrapFind<"<<wrapFind<<"> entireWord<"<<entireWord<<"> matchCase<"<<matchCase<<"> searchFrames<"<<searchFrames<<">****")
	PRBool isFound=PR_FALSE;
	nsresult rv =window->Find(srchStr,(findBack==JNI_TRUE?PR_TRUE:PR_FALSE),
							(wrapFind==JNI_TRUE?PR_TRUE:PR_FALSE),(entireWord==JNI_TRUE?PR_TRUE:PR_FALSE),
								(matchCase==JNI_TRUE?PR_TRUE:PR_FALSE),
									(searchFrames==JNI_TRUE?PR_TRUE:PR_FALSE), &isFound);
	if(srchStr)nsMemory::Free(srchStr);
	JREX_LOGLN("Find()--> **** Find rv<"<<rv<<"> isFound<"<<isFound<<"> ****")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** Find()-->  Find Failed ****",rv);
	return isFound==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    FindAgain
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_FindAgain
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("FindAgain()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** FindAgain()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return JNI_FALSE;
	}
	PRBool isFound=PR_FALSE;
	nsresult rv =window->FindNext(&isFound);
	JREX_LOGLN("FindAgain()--> **** rv<"<<rv<<"> isFound<"<<isFound<<"> ****")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** FindAgain()-->  FindNext Failed ****",rv);
	return isFound==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    IsLoadingDocument
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_IsLoadingDocument
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("IsLoadingDocument()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** IsLoadingDocument()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return JNI_FALSE;
	}
	PRBool isLoading=PR_FALSE;
	nsresult rv =window->GetIsLoadingDocument(&isLoading);
	JREX_LOGLN("IsLoadingDocument()--> **** rv<"<<rv<<"> isLoading<"<<isLoading<<"> ****")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsLoadingDocument()-->  GetIsLoadingDocument Failed ****",rv);
	return isLoading==PR_TRUE?JNI_TRUE:JNI_FALSE;
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    GetFindConfig
 * Signature: (Lorg/mozilla/jrex/ui/JRexFindConfig)
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetFindConfig
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetFindConfig()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetFindConfig()-->YOU DO NOT EXIST!!! ****",0);//does this occur?
		return NULL;
	}
	nsXPIDLString srchStr;
	PRBool findBack=PR_FALSE;
    PRBool wrapFind=PR_FALSE;
    PRBool entireWord=PR_FALSE;
    PRBool matchCase=PR_FALSE;
    PRBool searchFrames=PR_FALSE;

	nsresult rv =window->GetFindConfig(getter_Copies(srchStr),&findBack,&wrapFind,&entireWord, &matchCase, &searchFrames);
	JREX_LOGLN("GetFindConfig()--> **** rv<"<<rv<<"> srchStr<"<<srchStr<<"> findBack<"<<findBack<<"> wrapFind<"<<wrapFind<<"> entireWord<"<<entireWord<<"> matchCase<"<<matchCase<<"> searchFrames<"<<searchFrames<<">****")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetFindConfig()-->  GetFindConfig Failed ****",rv);

	if (env->EnsureLocalCapacity(2) < 0)
		ThrowJRexException(env, "**** GetFindConfig()-->  EnsureLocalCapacity Failed ****",0);

	jstring jsrchStr=NULL;
	if(NOT_NULL(srchStr)){
		JREX_LOGLN("GetFindConfig()--> **** Got NOT NULL srchStr ****")
		char* tempuft=ToNewUTF8String(srchStr);
		jsrchStr= env->NewStringUTF(tempuft);
		nsMemory::Free(tempuft);
	}
	JREX_LOGLN("GetFindConfig()--> **** jsrchStr <"<<jsrchStr<<"> ****")

	jobject findConfigObj=env->NewObject(JRexCanvasFields::findConfigCls,JRexCanvasFields::findConfigCID,jsrchStr,
									(findBack==PR_TRUE?JNI_TRUE:JNI_FALSE),(wrapFind==PR_TRUE?JNI_TRUE:JNI_FALSE),
										(entireWord==PR_TRUE?JNI_TRUE:JNI_FALSE),(matchCase==PR_TRUE?JNI_TRUE:JNI_FALSE)
											,(searchFrames==PR_TRUE?JNI_TRUE:JNI_FALSE));
	JNI_IF_EXP_DESC_CLR_RET("GetFindConfig()--> **** New findConfigObj Failed with Exception ****", (jobject)NULL)
	if(jsrchStr)env->DeleteLocalRef(jsrchStr);
	return findConfigObj;
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    GetPersistFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetPersistFlags
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return 0;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetPersistFlags()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetPersistFlags()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint32 persistFlags=0;
	nsresult rv=window->GetPersistFlags(&persistFlags);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetPersistFlags()-->  GetPersistFlags Failed ****",rv);
	return (jint)persistFlags;
  	JREX_CATCH(env)
  	return 0;
}


/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    SetPersistFlags
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SetPersistFlags
  (JNIEnv *env, jobject jrexCanvas, jint jpersistFlags){
	if(!gXpcomRunning)return ;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SetPersistFlags()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SetPersistFlags()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->SetPersistFlags((PRUint32)jpersistFlags);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetPersistFlags()-->  SetPersistFlags Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    GetCurrentPersistState
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetCurrentPersistState
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return 0;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetCurrentPersistState()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetCurrentPersistState()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint32 persistState=0;
	nsresult rv=window->GetCurrentState(&persistState);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetCurrentPersistState()-->  GetCurrentState Failed ****",rv);
	return (jint)persistState;
  	JREX_CATCH(env)
  	return 0;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    GetPersistResult
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_GetPersistResult
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return 0;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("GetPersistResult()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetPersistResult()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint32 persistResult=0;
	nsresult rv=window->GetResult(&persistResult);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetPersistResult()-->  GetPersistResult Failed ****",rv);
	return (jint)persistResult;
  	JREX_CATCH(env)
  	return 0;
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    SaveURI
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/io/InputStream;Ljava/lang/String;Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SaveURI
  (JNIEnv *env, jobject jrexCanvas, jstring juri, jstring jrefUri,
  	jobject jpostData, jstring jxtraHeaders, jstring jfilePath, jboolean jaddProgListn){
	if(!gXpcomRunning)return;
  	JREX_TRY

	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SaveURI()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SaveURI()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}

	nsIInputStream* postIn=NOT_NULL(jpostData)?new JRexInputStream(jpostData):nsnull;
	JREX_LOGLN("SaveURI()--> **** postIn <"<<postIn<<"> ***")

	PRUnichar* uri=nsnull;
	JSTR_TO_NEW_PRUNI(env, juri, uri);
	PRUnichar* refUri=nsnull;
	JSTR_TO_NEW_PRUNI(env, jrefUri, refUri);
	PRUnichar* xtraHeaders=nsnull;
	JSTR_TO_NEW_PRUNI(env, jxtraHeaders, xtraHeaders);
	PRUnichar* filePath=nsnull;
	JSTR_TO_NEW_PRUNI(env, jfilePath, filePath);

	nsresult rv=window->SaveURI(uri,refUri,postIn,xtraHeaders,filePath,(PRBool)jaddProgListn);
	if(NS_FAILED(rv))
		ThrowJRexException(env, "**** SaveURI()-->  SaveURI Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    SaveCurrentDocument
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIZ)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_SaveCurrentDocument
  (JNIEnv *env, jobject jrexCanvas, jstring jfilePath, jstring jdataPath,
  		jstring jcnType, jint jencodingFlags, jint jwrapColumn, jboolean jaddProgListn){

	if(!gXpcomRunning)return;
  	JREX_TRY

	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("SaveCurrentDocument()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SaveCurrentDocument()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}

	PRUnichar* filePath=nsnull;
	JSTR_TO_NEW_PRUNI(env, jfilePath, filePath);
	PRUnichar* dataPath=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdataPath, dataPath);
	PRUnichar* cnType=nsnull;
	JSTR_TO_NEW_PRUNI(env, jcnType, cnType);

	nsresult rv=window->SaveDocument(filePath,dataPath,cnType,(PRUint32)jencodingFlags,(PRUint32)jwrapColumn,(PRBool)jaddProgListn);
	if(NS_FAILED(rv))
		ThrowJRexException(env, "**** SaveCurrentDocument()-->  SaveDocument Failed ****",rv);
  	JREX_CATCH(env)

}

/*
 * Class:     org_mozilla_jrex_ui_JRexCanvas
 * Method:    CancelSave
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_CancelSave
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("CancelSave()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CancelSave()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->CancelSave();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** CancelSave()-->  SetPersistFlags Failed ****",rv);
  	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddProgressListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddProgressListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddProgressListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddProgressListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddProgressListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddProgressListener()-->  JRexWindow AddProgressListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddContextMenuListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddContextMenuListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddContextMenuListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddContextMenuListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddContextMenuListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddContextMenuListener()-->  JRexWindow AddContextMenuListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddHistoryListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddHistoryListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddHistoryListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddHistoryListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddHistoryListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddHistoryListener()-->  JRexWindow AddHistoryListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddKeyListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddKeyListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddKeyListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddKeyListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddKeyListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddKeyListener()-->  JRexWindow AddKeyListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddMouseListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddMouseListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddMouseListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddMouseListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddMouseListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddMouseListener()-->  JRexWindow AddMouseListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    AddMouseMotionListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddMouseMotionListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddMouseMotionListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddMouseMotionListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddMouseMotionListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddMouseMotionListener()-->  JRexWindow AddMouseMotionListener Failed ****",rv);
  	JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_AddURIContentListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("AddURIContentListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddURIContentListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->AddURIContentListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** AddURIContentListener()-->  JRexWindow AddURIContentListener Failed ****",rv);
  	JREX_CATCH(env)
}

JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveURIContentListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveURIContentListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveURIContentListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveURIContentListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveURIContentListener()-->  JRexWindow RemoveURIContentListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveProgressListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveProgressListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveProgressListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveProgressListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveProgressListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveProgressListener()-->  JRexWindow RemoveProgressListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveContextMenuListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveContextMenuListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveContextMenuListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveContextMenuListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveContextMenuListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveContextMenuListener()-->  JRexWindow RemoveContextMenuListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveHistoryListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveHistoryListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveHistoryListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveHistoryListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveHistoryListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveHistoryListener()-->  JRexWindow RemoveHistoryListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveKeyListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveKeyListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveKeyListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveKeyListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveKeyListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveKeyListener()-->  JRexWindow RemoveKeyListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveMouseListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveMouseListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveMouseListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveMouseListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveMouseListener();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** RemoveMouseListener()-->  JRexWindow RemoveMouseListener Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_ui_JRexBrowser
 * Method:    RemoveMouseMotionListener
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_ui_JRexCanvas_RemoveMouseMotionListener
  (JNIEnv *env, jobject jrexCanvas){
	if(!gXpcomRunning)return;
  	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(env->GetIntField(jrexCanvas, JRexCanvasFields::peerID));
	JREX_LOGLN("RemoveMouseMotionListener()--> **** JRexWindow <"<<window<<"> ****")

	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveMouseMotionListener()-->YOU DO NOT EXIST!!! ****",0);
		return;
	}
	nsresult rv=window->RemoveMouseMotionListener();
	if (NS_FAILED(rv)){
		ThrowJRexException(env, "**** RemoveMouseMotionListener()-->  JRexWindow RemoveMouseMotionListener Failed ****",rv);
		return;
	}
  	JREX_CATCH(env)
}
