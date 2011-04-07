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

#include "org_mozilla_jrex_xpcom_JRexXPCOMImpl.h"
#include "JRex_JNI_Util.h"
#include "JRexDirServiceProvider.h"
#include "JRexWindow.h"
using namespace JREX_JNI_UTIL;

#if defined(XP_MAC) || defined(XP_MACOSX)
	#define XPCOM_DLL  "libxpcom.dylib"
#elif defined(XP_UNIX) || defined(XP_BEOS)
	#define XPCOM_DLL  "libxpcom.so"
#else
	#define XPCOM_DLL  "xpcom.dll"
#endif

nsIAppShell* 	gAppShell=nsnull;
nsIEventQueue* 	gEventQ=nsnull;
PRThread* 		gThread=nsnull;
JNIEnv* 		JREX_JNI_UTIL::gJenv=nsnull;
PRBool			gXpcomRunning=PR_FALSE;

static NS_DEFINE_CID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);
static NS_DEFINE_CID(kAppShellCID, NS_APPSHELL_CID);
static PRBool SHUTDOWN_COMPLETE=PR_TRUE;

struct ShutDownEvent{
	PLEvent mEvent;

	static void* PR_CALLBACK HandleShutDownEvent(PLEvent* aEvent){
		nsresult rv=NS_OK;
		if(NOT_NULL(gAppShell)){
			rv|=gAppShell->ListenToEventQueue(gEventQ,PR_FALSE);
			JREX_LOGLN("HandleShutDownEvent()--> **** gAppShell ListenToEventQueue rv<"<<rv<<">****")
			rv|=gAppShell->Exit();
			JREX_LOGLN("HandleShutDownEvent()--> **** Exiting  gAppShell DONE rv<"<<rv<<">****")
		}
		return (void*)rv;
	}

	static void PR_CALLBACK DestroyShutDownEvent(PLEvent* aEvent){
		ShutDownEvent* event = NS_REINTERPRET_CAST(ShutDownEvent*, aEvent);
		JREX_LOGLN("DestroyShutDownEvent()--> **** I AM HERE****")
		delete event;
		SHUTDOWN_COMPLETE=PR_TRUE;
	}
};

static nsresult InitXPCOMInternal(JNIEnv *env, jobject xpcomImplObj, const char* grePath, jstring profileName, jstring profilePath);
static nsresult ShutDownXPCOMInternal();


/*
 * Class:     org_mozilla_jrex_xpcom_JRexXPCOMImpl
 * Method:    initXPCOM
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_xpcom_JRexXPCOMImpl_InitXPCOM
  (JNIEnv *env, jobject obj, jstring jgrePath, jstring jprofileName, jstring jprofilePath){
	if(gXpcomRunning)return;
	JREX_TRY
	if(IS_NULL(jgrePath)){
		ThrowJRexException(env, "GRE PATH CAN'T BE NULL",NS_ERROR_INVALID_ARG);
		return;
	}
	JREX_LOGLN("initXPCOM()-->**** GOT jgrePath <"<<jgrePath<<"> jprofileName <"<<jprofileName<<"> jprofilePath <"<<jprofilePath<<"> ****")

	jboolean isCopy=JNI_FALSE;
	const char *grePath = env->GetStringUTFChars(jgrePath, &isCopy);
	JREX_LOGLN("initXPCOM()-->**** GOT grePath <"<<grePath<<">");

	nsresult rv=InitXPCOMInternal(env,obj,grePath, jprofileName,jprofilePath);
	env->ReleaseStringUTFChars(jgrePath, grePath);
	if (NS_FAILED(rv)){
		jclass cls=env->GetObjectClass(obj);
		env->CallVoidMethod(obj,env->GetMethodID(cls,"notifyXPCOMInited","(I)V"),(jint)-1);
		JREX_LOGLN("initXPCOM()-->**** notifyXPCOMInited called ****")
		env->DeleteLocalRef(cls);
		ThrowJRexException(env, "initXPCOM()-->Intialization of XPCOM failed",rv);
	}
	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_xpcom_JRexXPCOMImpl
 * Method:    shutDownXPCOM
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_xpcom_JRexXPCOMImpl_ShutDownXPCOM
  (JNIEnv *env, jobject obj){
	if(!gXpcomRunning)return;
	JREX_TRY
	JREX_LOGLN("ShutDownXPCOM()-->Destroying all JRexWindow's ")
	JRexWindow::SayGoodBye();
	gXpcomRunning=PR_FALSE;
	JREX_LOGLN("ShutDownXPCOM()--> **** SayGoodBye DONE ****")
	SHUTDOWN_COMPLETE=PR_FALSE;
	nsresult rv=ShutDownXPCOMInternal();
	JREX_LOGLN("ShutDownXPCOMInternal()--> ShutDownXPCOMInternal rv<"<<rv<<"> ")
	if (NS_FAILED(rv))
		ThrowJRexException(env, "ShutDown of XPCOM failed",rv);
	JREX_CATCH(env)
}


nsresult InitXPCOMInternal( JNIEnv *env, jobject xpcomImplObj, const char* grePath, jstring jprofileName, jstring jprofilePath){
	JREX_LOGLN("InitXPCOMInternal()-->GOT GRE PATH <"<<grePath<<"> jprofileName <"<<jprofileName<<">jprofilePath <"<<jprofilePath<<">")
	char* xpcomPath = (char*) malloc(strlen(grePath) + sizeof(XPCOM_DLL) + sizeof(FILE_PATH_SEPARATOR)+1);
	sprintf(xpcomPath, "%s" FILE_PATH_SEPARATOR XPCOM_DLL, grePath);

	JREX_LOGLN("InitXPCOMInternal()--> **** USING XPCOM PATH <"<<xpcomPath<<"> ****")
	nsresult rv=XPCOMGlueStartup(xpcomPath);
	free(xpcomPath);
    JREX_RETURN_IF_FAILED(rv,"InitXPCOMInternal()--> **** XPCOMGlueStartup")

	PRUnichar* profileName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jprofileName, profileName);
	PRUnichar* profilePath=nsnull;
	JSTR_TO_NEW_PRUNI(env, jprofilePath, profilePath);
	JREX_LOGLN("InitXPCOMInternal()-->**** profileName <"<<(PRInt32)profileName<<"> profilePath <"<<(PRInt32)profilePath<<"> ****")

	nsCOMPtr<nsILocalFile> binDir;
	nsCOMPtr<nsIAppShell> tempShell;
	nsCOMPtr<nsIEventQueue> tempEventQueue;
	nsCOMPtr<nsIEventQueueService> eventQueueService;
	nsCOMPtr<nsIProfile> 			profileService;

	jclass cls;
	nsEmbedCString  gPath(grePath);
	JRexDirServiceProvider *provider = new JRexDirServiceProvider();
	PRBool XPCOM_INITED=PR_FALSE;

	JREX_FAILED_GOTO(provider?NS_OK:NS_ERROR_FAILURE,"InitXPCOMInternal()--> **** Creating  JRexDirectoryServiceProvider FAILED ****",failed);
	JREX_LOGLN("InitXPCOMInternal()--> ****Creating  JRexDirectoryServiceProvider Done **** ")

	rv=provider->Initialize(grePath);
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** Initializing  JRexDirectoryServiceProvider FAILED ****",failed);
	NS_ADDREF(provider);
	JREX_LOGLN("InitXPCOMInternal()--> **** Initializing  JRexDirectoryServiceProvider Done **** ")

	JREX_LOGLN("InitXPCOMInternal()--> **** Creating  NS_InitXPCOM2 ****")
	rv=NS_NewNativeLocalFile(gPath,PR_TRUE,getter_AddRefs(binDir));
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** Creating  NS_NewNativeLocalFile  FAILED ****",failed);

	rv=NS_InitXPCOM2(nsnull,binDir,provider);
	NS_RELEASE(provider);
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** NS_InitXPCOM2  FAILED ****",failed);
	JREX_LOGLN("InitXPCOMInternal()--> **** XPCOM USING GLUE INITED ****")

	XPCOM_INITED=PR_TRUE;

	if(profileName!=nsnull){

		PRBool profileExists=PR_FALSE;

		profileService =do_GetService(NS_PROFILE_CONTRACTID, &rv);
		JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** do_GetService profileService Failed ****",failed)
		JREX_LOGLN("InitXPCOMInternal()--> **** do_GetService profileService Done ****")


		rv=profileService->ProfileExists(profileName,&profileExists);
		JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** profileService ProfileExists FAILED ****",failed)
		JREX_LOGLN("InitXPCOMInternal()--> **** profileExists <"<<profileExists<<"> ****")

		if(profileExists==PR_TRUE){
			profileService->SetCurrentProfile(profileName);
			JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** profileService SetCurrentProfile FAILED ****",failed)
			JREX_LOGLN("InitXPCOMInternal()--> **** CurrentProfile <"<<profileName<<"> ****")
		}else{
			rv=profileService->CreateNewProfile(profileName,profilePath,nsnull,PR_TRUE);
			JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** profileService CreateNewProfile FAILED ****",failed)
			profileService->SetCurrentProfile(profileName);
			JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** profileService NEW SetCurrentProfile FAILED ****",failed)
			JREX_LOGLN("InitXPCOMInternal()--> **** CurrentProfile is <"<<profileName<<"> ****")
		}
	}//profile

	eventQueueService = do_GetService(kEventQueueServiceCID,&rv);
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** do_GetService eventQueueService Failed ****",failed)
	JREX_LOGLN("InitXPCOMInternal()--> **** do_GetService eventQueueService Done ****")

	rv= eventQueueService->GetThreadEventQueue(PR_GetCurrentThread(),getter_AddRefs(tempEventQueue));
	JREX_LOGLN("InitXPCOMInternal()--> **** GetThreadEventQueue rv<"<<rv<<"> ****")

	if(IS_NULL(tempEventQueue)){
		rv=eventQueueService->CreateThreadEventQueue();
	    JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** CreateThreadEventQueue Failed ****",failed)
		JREX_LOGLN("InitXPCOMInternal()--> **** CreateThreadEventQueue Done ****")
		rv= eventQueueService->GetThreadEventQueue(PR_GetCurrentThread(),getter_AddRefs(tempEventQueue));
	    JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** GetThreadEventQueue for gEventQ Failed ****",failed)
		JREX_LOGLN("InitXPCOMInternal()--> **** GetThreadEventQueue for Done ****")
	}
	NS_ADDREF(gEventQ=tempEventQueue.get());
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		gtk_set_locale();
		rv=(gtk_init_check(0,nsnull)!=0)?NS_OK:NS_ERROR_FAILURE;
		JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** gtk_init_check Failed ****",failed)
#endif
	rv = nsComponentManager::CreateInstance(kAppShellCID, nsnull,
                                          NS_GET_IID(nsIAppShell),
                                          (void**)getter_AddRefs(tempShell));
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** nsIgAppShell do_CreateInstance Failed ****",failed)
	JREX_LOGLN("InitXPCOMInternal()--> **** nsIgAppShell do_CreateInstance Done ****")

	NS_ADDREF(gAppShell=tempShell.get());
	JREX_LOGLN("InitXPCOMInternal()--> **** gAppShell AddRefed <"<<gAppShell<<"> ****")

	rv=gAppShell->Create(0, nsnull);
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** nsIgAppShell Create Failed ****",failed)
	JREX_LOGLN("InitXPCOMInternal()--> **** nsIgAppShell Create Done ****")

	rv=gAppShell->ListenToEventQueue(gEventQ,PR_TRUE);
	JREX_RETURN_IF_FAILED(rv,"InitXPCOMInternal()--> **** nsIgAppShell ListenToEventQueue")

	gThread=PR_GetCurrentThread();
	JREX_LOGLN("InitXPCOMInternal()--> **** gThread<"<<gThread<<"> ****")
	JREX_JNI_UTIL::gJenv=env;
	JREX_LOGLN("InitXPCOMInternal()--> **** gJenv<"<<JREX_JNI_UTIL::gJenv<<"> ****")

	rv=gAppShell->Spinup();
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** nsIgAppShell Spinup Failed ****",failed)
	JREX_LOGLN("InitXPCOMInternal()--> **** nsIgAppShell Spinup Done ****")

	gXpcomRunning=PR_TRUE;

	//changes for fixing BUG-ID<6426>, contributed by damon@javasteam.com
	//moved notification after Xpcom is Running.
	cls=env->GetObjectClass(xpcomImplObj);
	env->CallVoidMethod(xpcomImplObj,env->GetMethodID(cls,"notifyXPCOMInited","(I)V"),(jint)1);
	JREX_LOGLN("InitXPCOMInternal()--> **** notifyXPCOMInited called ****")
	env->DeleteLocalRef(cls);

	JREX_LOGLN("InitXPCOMInternal()--> **** Calling gAppShell Run ****")
	rv=gAppShell->Run();
	JREX_FAILED_GOTO(rv,"InitXPCOMInternal()--> **** nsIgAppShell Run Failed ****",failed)

	JRexWindow::SayGoodBye();
	JREX_LOGLN("InitXPCOMInternal()--> **** SayGoodBye DONE ****")

	gXpcomRunning=PR_FALSE;
	while(SHUTDOWN_COMPLETE==PR_FALSE){
		JREX_LOGLN("InitXPCOMInternal()--> **** WAITING FOR SHUTDOWN ****")
		PR_Sleep(1*PR_TicksPerSecond()/1000);
	}
	if(profileService){
		rv=profileService->ShutDownCurrentProfile(nsIProfile::SHUTDOWN_PERSIST);
		JREX_LOGLN("InitXPCOMInternal()--> **** profileService ShutDownCurrentProfile Done rv<"<<rv<<">****")
	}
	rv|=gAppShell->Spindown();
	JREX_LOGLN("InitXPCOMInternal()--> **** gAppShell Spindown DONE rv<"<<rv<<">****")

	rv|=gEventQ->ProcessPendingEvents();
	JREX_LOGLN("InitXPCOMInternal()--> **** ProcessPendingEvents DONE rv<"<<rv<<">****")
	rv|=gEventQ->StopAcceptingEvents();
	JREX_LOGLN("InitXPCOMInternal()--> **** gEventQ StopAcceptingEvents DONE rv<"<<rv<<">****")
	rv|=eventQueueService->DestroyThreadEventQueue();
	JREX_LOGLN("InitXPCOMInternal()--> **** gEventQ DestroyThreadEventQueue rv<"<<rv<<">****")

	JREX_LOGLN("InitXPCOMInternal()--> **** BRIGING DOWN XPCOM ***")
	rv|=NS_ShutdownXPCOM(nsnull);
	JREX_LOGLN("InitXPCOMInternal()--> **** NS_ShutdownXPCOM DONE rv<"<<rv<<">****")

	NS_IF_RELEASE(gEventQ);
	NS_IF_RELEASE(gAppShell);
	JREX_LOGLN("InitXPCOMInternal()--> **** RELEASE gEventQ gAppShell DONE ****")

	rv|=XPCOMGlueShutdown();
	JREX_LOGLN("InitXPCOMInternal()--> **** XPCOMGlueShutdown DONE rv<"<<rv<<">****")
	return rv;
failed:
	if(XPCOM_INITED)
		NS_ShutdownXPCOM(nsnull);
	NS_IF_RELEASE(gEventQ);
	NS_IF_RELEASE(gAppShell);
	XPCOMGlueShutdown();
	return rv;
}

inline nsresult ShutDownXPCOMInternal(){
	nsresult rv=NS_OK;
	if(IS_EQT && NOT_NULL(gAppShell)){
		rv|=gAppShell->ListenToEventQueue(gEventQ,PR_FALSE);
		JREX_LOGLN("ShutDownXPCOMInternal()--> **** gAppShell ListenToEventQueue rv<"<<rv<<">****")
		rv|=gAppShell->Exit();
		JREX_LOGLN("ShutDownXPCOMInternal()--> **** Exiting  gAppShell DONE rv<"<<rv<<">****")
		return rv;
	}

	if(gEventQ){
        ShutDownEvent* event = new ShutDownEvent;
        if (event) {
			JREX_LOGLN("ShutDownXPCOMInternal()--> **** gEventQ ShutDownEvent Created ****")
			gEventQ->InitEvent(NS_REINTERPRET_CAST(PLEvent*, event),
								nsnull,ShutDownEvent::HandleShutDownEvent,
									ShutDownEvent::DestroyShutDownEvent);
			JREX_LOGLN("ShutDownXPCOMInternal()--> **** gEventQ InitEvent done ****")
			rv = gEventQ->EnterMonitor();
			nsresult srv;
			if (NS_SUCCEEDED(rv))
				rv = gEventQ->PostSynchronousEvent(NS_REINTERPRET_CAST(PLEvent*, event),(void**)&srv);

			JREX_LOGLN("ShutDownXPCOMInternal()--> **** gEventQ ShutDownEvent srv<"<<srv<<"> ****")
			gEventQ->ExitMonitor();
			if (NS_FAILED(rv))
            	delete event;
		}else
          rv = NS_ERROR_OUT_OF_MEMORY;
	}
	return rv;
}
