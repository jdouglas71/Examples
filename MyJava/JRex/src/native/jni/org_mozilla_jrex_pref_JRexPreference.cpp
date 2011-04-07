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

#include "org_mozilla_jrex_pref_JRexPreference.h"
#include "JRex_JNI_Util.h"
#include "JRexPreference.h"
using namespace JREX_JNI_UTIL;
using namespace JRexPreference;


/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    ReadUserPrefs
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_ReadUserPrefs
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::ReadUserPrefs(prefName);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** ReadUserPrefs()--> ReadUserPrefs Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    ResetPrefs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_ResetPrefs
  (JNIEnv *env, jobject jprefObj){
	if(!gXpcomRunning)return;
	JREX_TRY
	nsresult rv=JRexPreference::ResetPrefs();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** ResetPrefs()--> ResetPrefs Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    ResetUserPrefs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_ResetUserPrefs
  (JNIEnv *env, jobject jprefObj){
	if(!gXpcomRunning)return;
	JREX_TRY
	nsresult rv=JRexPreference::ResetUserPrefs();
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** ResetUserPrefs()--> ResetUserPrefs Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SavePrefFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SavePrefFile
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::SavePrefFile(prefName);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SavePrefFile()--> SavePrefFile Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetRoot
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetRoot
  (JNIEnv *env, jobject jprefObj){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	char *root=nsnull;
	nsresult rv=JRexPreference::GetRoot(&root);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetRoot()--> GetRoot Failed ****",rv);
	return root==nsnull?NULL:env->NewStringUTF(root);
  	JREX_CATCH(env)
  	return NULL;

}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetPrefType
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetPrefType
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return -1;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRInt32 rVal=0;
	nsresult rv=JRexPreference::GetPrefType(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetPrefType()--> GetPrefType Failed ****",rv);
	return (jlong)rVal;
  	JREX_CATCH(env)
  	return -1;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetBoolPref
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetBoolPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRBool rVal=PR_FALSE;
	nsresult rv=JRexPreference::GetBoolPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetBoolPref()--> GetBoolPref Failed ****",rv);
	return rVal==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetBoolPref
 * Signature: (Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetBoolPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jboolean jbval){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::SetBoolPref(prefName,(jbval==JNI_TRUE?PR_TRUE:PR_FALSE));
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetBoolPref()--> SetBoolPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetCharPref
 * Signature: (Ljava/lang/String;)C
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetCharPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	char *rVal=nsnull;
	nsresult rv=JRexPreference::GetCharPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetCharPref()--> GetCharPref Failed ****",rv);
	return rVal==nsnull?NULL:env->NewStringUTF(rVal);
  	JREX_CATCH(env)
  	return NULL;

}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetCharPref
 * Signature: (Ljava/lang/String;C)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetCharPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jstring jsval){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	const char *value=env->GetStringUTFChars(jsval,&copy);
	nsresult rv=JRexPreference::SetCharPref(prefName,value);
	env->ReleaseStringUTFChars(jprefName,prefName);
	env->ReleaseStringUTFChars(jsval,value);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetCharPref()--> SetCharPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetIntPref
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetIntPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return -1;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRInt32 rVal=0;
	nsresult rv=JRexPreference::GetIntPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetIntPref()--> GetIntPref Failed ****",rv);
	return (jlong)rVal;
  	JREX_CATCH(env)
  	return -1;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetIntPref
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetIntPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jlong jlval){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::SetIntPref(prefName,(PRInt32)jlval);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetIntPref()--> SetIntPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    ClearUserPref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_ClearUserPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::ClearUserPref(prefName);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** ClearUserPref()--> ClearUserPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    IsPrefLocked
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_pref_JRexPreference_IsPrefLocked
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRBool rVal=PR_FALSE;
	nsresult rv=JRexPreference::IsPrefLocked(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** IsPrefLocked()--> IsPrefLocked Failed ****",rv);
	return rVal==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    LockPref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_LockPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::LockPref(prefName);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** LockPref()--> LockPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    UnLockPref
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_UnLockPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::UnlockPref(prefName);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** UnlockPref()--> UnLockPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    PrefHasUserValue
 * Signature: (Ljava/lang/String;)Z
 */
/*JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_pref_JRexPreference_PrefHasUserValue
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRBool rVal=PR_FALSE;
	nsresult rv=JRexPreference::PrefHasUserValue(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** PrefHasUserValue()--> PrefHasUserValue Failed ****",rv);
	return rVal==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}*/

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetDefaultBoolPref
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetDefaultBoolPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRBool rVal=PR_FALSE;
	nsresult rv=JRexPreference::GetDefaultBoolPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetDefaultBoolPref()--> GetDefaultBoolPref Failed ****",rv);
	return rVal==PR_TRUE?JNI_TRUE:JNI_FALSE;
  	JREX_CATCH(env)
  	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetDefaultBoolPref
 * Signature: (Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetDefaultBoolPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jboolean jbval){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::SetDefaultBoolPref(prefName,(jbval==JNI_TRUE?PR_TRUE:PR_FALSE));
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetDefaultBoolPref()--> SetDefaultBoolPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetDefaultCharPref
 * Signature: (Ljava/lang/String;)C
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetDefaultCharPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	char *rVal=nsnull;
	nsresult rv=JRexPreference::GetDefaultCharPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetDefaultCharPref()--> GetDefaultCharPref Failed ****",rv);
	return rVal==nsnull?NULL:env->NewStringUTF(rVal);
  	JREX_CATCH(env)
  	return NULL;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetDefaultCharPref
 * Signature: (Ljava/lang/String;C)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetDefaultCharPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jstring jsval){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	const char *value=env->GetStringUTFChars(jsval,&copy);
	nsresult rv=JRexPreference::SetDefaultCharPref(prefName,value);
	env->ReleaseStringUTFChars(jprefName,prefName);
	env->ReleaseStringUTFChars(jsval,value);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetDefaultCharPref()--> SetDefaultCharPref Failed ****",rv);
  	JREX_CATCH(env)

}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetDefaultIntPref
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetDefaultIntPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName){
	if(!gXpcomRunning)return -1;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	PRInt32 rVal=0;
	nsresult rv=JRexPreference::GetDefaultIntPref(prefName,&rVal);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** GetDefaultIntPref()--> GetDefaultIntPref Failed ****",rv);
	return (jlong)rVal;
  	JREX_CATCH(env)
  	return -1;
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    SetDefaultIntPref
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_pref_JRexPreference_SetDefaultIntPref
  (JNIEnv *env, jobject jprefObj, jstring jprefName, jlong jprefValue){
	if(!gXpcomRunning)return;
	JREX_TRY
	jboolean copy=JNI_FALSE;
	const char *prefName=env->GetStringUTFChars(jprefName,&copy);
	nsresult rv=JRexPreference::SetDefaultIntPref(prefName,(PRInt32)jprefValue);
	env->ReleaseStringUTFChars(jprefName,prefName);
	if (NS_FAILED(rv))
		ThrowJRexException(env, "**** SetDefaultIntPref()--> SetDefaultIntPref Failed ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_pref_JRexPreference
 * Method:    GetPrefChildren
 * Signature: (Ljava/lang/String;)Ljava/util/Collection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_pref_JRexPreference_GetPrefChildren
  (JNIEnv *env, jobject jprefObj, jstring jprefParentName){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JREX_LOGLN("GetPrefChildren()--> **** jprefParentName<"<<jprefParentName<<"> ****")
	jboolean copy=JNI_FALSE;
	char *prefName=nsnull;
	if(jprefParentName!=NULL)
		prefName=(char*)env->GetStringUTFChars(jprefParentName,&copy);

	JREX_LOGLN("GetPrefChildren()--> **** USing prefName<"<<(PRInt32)prefName<<"> ****")
	nsVoidArray *vArray=new nsVoidArray();
	if(IS_NULL(vArray)){
		ThrowJRexException(env, "**** GetPrefChildren()-->  nsVoidArray alloc Failed ****",0);
		return NULL;
	}

	nsresult rv=JRexPreference::GetPrefChildren(prefName,vArray);
	if(prefName)
		env->ReleaseStringUTFChars(jprefParentName,prefName);
	if(NS_FAILED(rv)){
		delete vArray;
		ThrowJRexException(env, "**** GetPrefChildren()-->  GetPrefChildren Failed ****",rv);
		return NULL;
	}

	PRInt32 count=vArray->Count();
	JREX_LOGLN("GetPrefChildren()--> **** GetPrefChildren count<"<<count<<"> ****")
	if(count<1){
		delete vArray;
		return NULL;
	}

	if (env->EnsureLocalCapacity(3) < 0){
		delete vArray;
		ThrowJRexException(env, "**** GetPrefChildren()-->  EnsureLocalCapacity Failed ****",rv);
		return NULL;
	}
	JREX_LOGLN("GetPrefChildren()--> **** EnsureLocalCapacity Done!!! ****")

	jclass clazz = env->FindClass("java/util/ArrayList");
	if(clazz==NULL){
		delete vArray;
		ThrowJRexException(env, "**** GetPrefChildren()-->  FindClass ArrayList Failed ****",0);
		return NULL;
	}

	jmethodID arryListCID=env->GetMethodID(clazz,"<init>", "()V");
	JREX_LOGLN("GetPrefChildren()--> **** arryListCID <"<<arryListCID<<"> ****")
	jmethodID arryListAddID=env->GetMethodID(clazz,"add", "(Ljava/lang/Object;)Z");
	JREX_LOGLN("GetPrefChildren()--> **** arryListAddID <"<<arryListAddID<<"> ****")

	jobject arryList=env->NewObject(clazz,arryListCID);
	JNI_EXP_DESC_CLR("GetPrefChildren() NewObject arryList Exception Occured")
	if(arryList==NULL){
		delete vArray;
		ThrowJRexException(env, "**** GetPrefChildren()-->  arryList Creation Failed ****",0);
		return NULL;
	}
	JREX_LOGLN("GetPrefChildren()--> **** arryList creation Done!!! ****")

	jstring jchild=NULL;
	while (vArray->Count()>0) {
		char *child = NS_REINTERPRET_CAST(char *, vArray->ElementAt(0));
		if(NOT_NULL(child)){
			jchild=env->NewStringUTF(child);
		}else
			jchild=NULL;
		JREX_LOGLN("GetPrefChildren()--> *** jchild<"<<jchild<<"> ***")
		if(jchild!=NULL){
			jboolean added=env->CallBooleanMethod(arryList,arryListAddID,jchild);
			JREX_LOGLN("GetPrefChildren()--> *** added<"<<(added==JNI_TRUE)<<"> ***")
			env->DeleteLocalRef(jchild);
		}
		PRBool removed=vArray->RemoveElementAt(0);
		JREX_LOGLN("GetPrefChildren()--> *** removed<"<<(removed==PR_TRUE)<<"> ***")
		if(NOT_NULL(child))nsMemory::Free(child);
		JREX_LOGLN("GetPrefChildren()--> *** Freed Child ***")
	}
	env->DeleteLocalRef(clazz);
	delete vArray;
	return arryList;
  	JREX_CATCH(env)
  	return NULL;
}

