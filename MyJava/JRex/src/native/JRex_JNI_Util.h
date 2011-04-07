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

#ifndef JRex_JNI_util_h_
	#define JRex_JNI_util_h_
	#include "JRexIncludes.h"


	#define JREX_EXP_NAME	"org/mozilla/jrex/exception/JRexException"

	#define JNI_EXP_BASE(s)						if(env->ExceptionCheck()){ \
												if(IS_NULL(s)) \
        											JREX_LOGLN_ERR("*** JNI EXCEPTION HAS OCCURRED, SEE JREX LOG FOR DETAILS ***") \
        										else \
        											JREX_LOGLN_ERR(s) \
        										env->ExceptionDescribe();

	#define JNI_EXP_DESC(s)						JNI_EXP_BASE(s)		}
	#define JNI_EXP_DESC_CLR(s)					JNI_EXP_BASE(s)		env->ExceptionClear(); }
	#define JNI_EXP_DESC_RET(s,ret) 			JNI_EXP_DESC(s)		return ret;
	#define JNI_EXP_DESC_CLR_RET(s,ret) 		JNI_EXP_DESC_CLR(s)	return ret;
	#define JNI_IF_EXP_DESC_RET(s,ret) 			JNI_EXP_BASE(s)		return ret;}
	#define JNI_IF_EXP_DESC_CLR_RET(s,ret) 		JNI_EXP_BASE(s)		env->ExceptionClear(); return ret;}
	#define JNI_IF_EXP_DESC_CLR_GT(s,gt) 		JNI_EXP_BASE(s)		env->ExceptionClear(); goto gt;}

	#define NS_STR_TO_JSTR_RET(env, nsstr)		{ \
													char* XXXXtempXXXX=ToNewUTF8String(nsstr); \
													jstring jstr_=env->NewStringUTF(XXXXtempXXXX); \
													nsMemory::Free(XXXXtempXXXX); \
													return jstr_; \
												}

	#define NS_STR_TO_JSTR(env, nsstr, retVal)	{ \
													char* XXXXtempXXXX=ToNewUTF8String(nsstr); \
													retVal=env->NewStringUTF(XXXXtempXXXX); \
													nsMemory::Free(XXXXtempXXXX); \
												}


	#define JSTR_TO_NEW_PRUNI(env, jstr_, retVal)	{ \
													if(jstr_){ \
														PRInt32 len=(PRInt32)env->GetStringLength(jstr_); \
														JREX_LOGLN("**** JSTR_TO_NEW_PRUNI len<"<<len<<"> ****") \
														PRUnichar* XXXXtempXXXX=(PRUnichar*)env->GetStringCritical(jstr_,0); \
														if (XXXXtempXXXX!=NULL){ \
															nsEmbedString XXXXtempXXXXns(XXXXtempXXXX,len); \
															retVal=ToNewUnicode(XXXXtempXXXXns); \
															env->ReleaseStringCritical(jstr_,XXXXtempXXXX); \
														}else{ \
															JNI_EXP_DESC_CLR("JSTR_TO_NATIVE FAILED!!!") \
														} \
													} \
												}


	namespace JREX_JNI_UTIL{

		JavaVM *JRex_GetVM();

		JNIEnv *JRex_GetEnv(jint version);

		void JRex_ThrowByName(JNIEnv *env, const char *name, const char *msg);

		void ThrowJRexException(JNIEnv *env, const char *msg,nsresult status);

		extern JNIEnv*	gJenv;

		struct JRexCommonJRV{
			JRexCommonJRV() : jobj(NULL), rv(NS_ERROR_FAILURE){}
			jobject jobj;
			nsresult rv;
		};
	}

#endif /* JRex_JNI_util_h_ */

