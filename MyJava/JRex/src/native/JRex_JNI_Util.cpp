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

# include "JRex_JNI_Util.h"

	/** A utility function to get a handle to java VM */
	JavaVM *JREX_JNI_UTIL::JRex_GetVM(){
		JavaVM*	vmArray[2];
		jsize	count=0;
		jint	rv = JNI_GetCreatedJavaVMs(vmArray, (jsize)2, &count);
		if (rv == JNI_OK && count >= 1){
			if(count>1){
				JREX_LOGLN("************ JNI_GetCreatedJavaVMs() returned >1 VMs ************")
			}
			JREX_LOGLN("******* WE GOT VM <"<<vmArray[0]<<"> *******")
			return vmArray[0];
		}
		return NULL;
	}

	/** A utility function to get a handle to JNIEnv  */
	JNIEnv *JREX_JNI_UTIL::JRex_GetEnv(jint version){
		if(IS_EQT){
			JREX_LOGLN("******* CURRENT-THREAD JRex-XPCOM THREAD ******")
			return gJenv;
		}

		void	*env;
		static JavaVM* vm=JRex_GetVM();//one time
		if (NOT_NULL(vm)){
			JREX_LOGLN("******* VM NOT_NULL ******")
			JavaVMAttachArgs attArgs;
			attArgs.version = version==0?JNI_VERSION_1_4:version;
			char tName[32];
			sprintf(tName,"JRex-Thread<%dL>",NS_PTR_TO_INT32(PR_GetCurrentThread()));
			attArgs.name = tName;
			attArgs.group = NULL;

			jint rv=vm->AttachCurrentThreadAsDaemon((void **)&env, (void *)&attArgs);
			JREX_LOGLN("******* env <"<<env<<"> GOT ******")
			//Where do detach CurrentThread, is detach required?
			if(rv!=JNI_OK){
				JREX_LOGLN("******* AttachCurrentThread FAILED, TRYING PLAIN WAY *******")
				vm->GetEnv(&env,(version==0?JNI_VERSION_1_4:version));
			}
		}else{
			JREX_LOGLN("******* I GOT NO VM, WHAT'S UP *******")
		}
		return (JNIEnv *)env;
	}


	/** A utility function to throw java excepiton by name*/
	void JREX_JNI_UTIL::JRex_ThrowByName(JNIEnv *env, const char *name, const char *msg){
		JREX_LOGLN("******* JRex_ThrowByName name"<<name<<" msg "<<msg<<" *******")
    	jclass cls = env->FindClass(name);
    	if (cls != 0){
			env->ThrowNew(cls, msg);
    		env->DeleteLocalRef(cls);
		}
	}


	/** A utility function to throw java JRex excepiton */
 	void JREX_JNI_UTIL::ThrowJRexException(JNIEnv *env, const char *msg,
																nsresult status){
		JREX_LOGLN("******* ThrowJRexException msg <"<<msg<<"> status <"<<status<<"> *******")
		JNI_EXP_DESC((char*)NULL);
		char* myMsg= (char*)malloc( sizeof(char)*(strlen(msg)+33));
		if(NOT_NULL(myMsg)){			sprintf(myMsg,"%s [NS-ERROR<0x%dL>]",msg,status);			JRex_ThrowByName(env, JREX_EXP_NAME, myMsg);			free(myMsg);
		}else			JRex_ThrowByName(env, JREX_EXP_NAME, "MSG_MALLOC_FAILED");	}
