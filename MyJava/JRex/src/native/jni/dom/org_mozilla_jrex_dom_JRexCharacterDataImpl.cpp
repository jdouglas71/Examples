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


#include "org_mozilla_jrex_dom_JRexCharacterDataImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexCharacterData
enum JRexCharacterDataEventTypes{JREX_APPENED_DATA=0U,
								JREX_DELETE_DATA,
								JREX_GET_DATA,
								JREX_INSERT_DATA,
								JREX_REPLACE_DATA,
								JREX_SET_DATA,
								JREX_SUBSTR_DATA};

static void* PR_CALLBACK HandleJRexCharacterDataEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexCharacterDataEvent(PLEvent* aEvent);

struct JRexCharacterDataEventParam{
	PRUnichar* data;
	PRUint32 offset;
	PRUint32 len;
};

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_AppendDataInternal(JNIEnv *env, nsIDOMCharacterData* cData, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString tdata(data);
		rv = cData->AppendData(tdata);
		JREX_LOGLN("JRexCharacterDataImpl_AppendDataInternal()--> **** AppendData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_DeleteDataInternal(JNIEnv *env, nsIDOMCharacterData* cData, PRUint32 offset, PRUint32 len){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		rv = cData->DeleteData(offset, len);
		JREX_LOGLN("JRexCharacterDataImpl_DeleteDataInternal()--> **** DeleteData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_GetDataInternal(JNIEnv *env, nsIDOMCharacterData* cData){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString retString;
		rv = cData->GetData(retString);
		JREX_LOGLN("JRexCharacterDataImpl_GetDataInternal()--> **** GetData rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_InsertDataInternal(JNIEnv *env, nsIDOMCharacterData* cData, int offset, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString tdata(data);
		rv = cData->InsertData(offset, tdata);
		JREX_LOGLN("JRexCharacterDataImpl_InsertDataInternal()--> **** InsertData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_ReplaceDataInternal(JNIEnv *env, nsIDOMCharacterData* cData,
													int offset, int len, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString tdata(data);
		rv = cData->ReplaceData(offset, len, tdata);
		JREX_LOGLN("JRexCharacterDataImpl_ReplaceDataInternal()--> **** ReplaceData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_SetDataInternal(JNIEnv *env, nsIDOMCharacterData* cData, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString tdata(data);
		rv = cData->SetData(tdata);
		JREX_LOGLN("JRexCharacterDataImpl_SetDataInternal()--> **** SetData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexCharacterDataImpl_SubstringDataInternal(JNIEnv *env, nsIDOMCharacterData* cData,
																		int offset, int len){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (cData){
		nsEmbedString retString;
		rv = cData->SubstringData(offset, len, retString);
		JREX_LOGLN("JRexCharacterDataImpl_SubstringDataInternal()--> **** SubstringData rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    AppendData
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_AppendData
  (JNIEnv * env, jobject jcd, jstring jdata){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("AppendData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "AppendData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return;
	}
	if(IS_NULL(jdata)){
		ThrowJRexException(env, "AppendData()--> **** jdata is NULL!!! ****",0);
		return;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("AppendData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_AppendDataInternal(env, thisCD, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisCD, JREX_APPENED_DATA, (void*)data, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("AppendData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("AppendData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("AppendData()--> **** AppendData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("AppendData()--> **** AppendData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** AppendData Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    DeleteData
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_DeleteData
  (JNIEnv * env, jobject jcd, jint joffset, jint jlen){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("DeleteData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "DeleteData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("DeleteData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_DeleteDataInternal(env, thisCD, (PRUint32)joffset, (PRUint32)jlen);
	}else{
		JRexCharacterDataEventParam *param=new JRexCharacterDataEventParam;
		if (IS_NULL(param))return;
		param->offset=(PRUint32)joffset;
		param->len=(PRUint32)jlen;

		nsresult rv=ExecInEventQDOM(thisCD, JREX_DELETE_DATA, param, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("DeleteData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("DeleteData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("DeleteData()--> **** DeleteData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("DeleteData()--> **** DeleteData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** DeleteData Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    GetData
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_GetData
  (JNIEnv * env, jobject jcd){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "GetData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_GetDataInternal(env, thisCD);
	}else{
		nsresult rv=ExecInEventQDOM(thisCD, JREX_GET_DATA, nsnull, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("GetData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetData()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetData()--> **** GetData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetData()--> **** GetData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetData Failed ****",rv);
			}
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    GetLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_GetLength
  (JNIEnv * env, jobject jcd){
	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetLength()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "GetLength()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRUint32 retLen=0;
	nsresult rv = thisCD->GetLength(&retLen);
	JREX_LOGLN("GetLength()--> **** GetLength rv<"<<rv<<"> ****")
	if(NS_FAILED(rv)){
		JREX_LOGLN("GetLength()--> **** GetLength NON-DOM ERROR OCCURED !!!****")
		ThrowJRexException(env, "**** GetLength Failed ****",rv);
		return 0;
	}
	return (jint)retLen;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    InsertData
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_InsertData
  (JNIEnv * env, jobject jcd, jint joffset, jstring jdata){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "InsertData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return;
	}
	if(IS_NULL(jdata)){
		ThrowJRexException(env, "InsertData()--> **** jdata is NULL!!! ****",0);
		return;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("InsertData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_InsertDataInternal(env, thisCD, (PRUint32)joffset, data);
	}else{
		JRexCharacterDataEventParam *param=new JRexCharacterDataEventParam;
		if (IS_NULL(param))return;
		param->offset=(PRUint32)joffset;
		param->data=data;

		nsresult rv=ExecInEventQDOM(thisCD, JREX_INSERT_DATA, param, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("InsertData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("InsertData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("InsertData()--> **** InsertData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("InsertData()--> **** InsertData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** InsertData Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    ReplaceData
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_ReplaceData
  (JNIEnv * env, jobject jcd, jint joffset, jint jlen, jstring jdata){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ReplaceData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "ReplaceData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return;
	}
	if(IS_NULL(jdata)){
		ThrowJRexException(env, "ReplaceData()--> **** jdata is NULL!!! ****",0);
		return;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ReplaceData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_ReplaceDataInternal(env, thisCD, (PRUint32)joffset, (PRUint32)jlen, data);
	}else{
		JRexCharacterDataEventParam *param=new JRexCharacterDataEventParam;
		if (IS_NULL(param))return;
		param->offset=(PRUint32)joffset;
		param->len=(PRUint32)jlen;
		param->data=data;

		nsresult rv=ExecInEventQDOM(thisCD, JREX_REPLACE_DATA, param, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("ReplaceData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ReplaceData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("ReplaceData()--> **** ReplaceData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("ReplaceData()--> **** ReplaceData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** ReplaceData Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    SetData
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_SetData
  (JNIEnv * env, jobject jcd, jstring jdata){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "SetData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return;
	}
	if(IS_NULL(jdata)){
		ThrowJRexException(env, "SetData()--> **** jdata is NULL!!! ****",0);
		return;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_SetDataInternal(env, thisCD, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisCD, JREX_SET_DATA, (void*)data, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("SetData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetData()--> **** SetData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SetData()--> **** SetData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetData Failed ****",rv);
			}
		}
	}

	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexCharacterDataImpl
 * Method:    SubstringData
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexCharacterDataImpl_SubstringData
  (JNIEnv * env, jobject jcd, jint joffset, jint jlen){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMCharacterData* thisCD=(nsIDOMCharacterData*)NS_INT32_TO_PTR(env->GetIntField(jcd, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SubstringData()--> **** thisCD <"<<thisCD<<"> ****")
	if(IS_NULL(thisCD)){
		ThrowJRexException(env, "SubstringData()--> **** thisCD DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SubstringData()--> **** IN EVT Q THREAD ****")
		jrv=JRexCharacterDataImpl_SubstringDataInternal(env, thisCD,(PRUint32)joffset, (PRUint32)jlen);
	}else{
		JRexCharacterDataEventParam *param=new JRexCharacterDataEventParam;
		if (IS_NULL(param))return NULL;
		param->offset=(PRUint32)joffset;
		param->len=(PRUint32)jlen;

		nsresult rv=ExecInEventQDOM(thisCD, JREX_SUBSTR_DATA, param, PR_TRUE,
						HandleJRexCharacterDataEvent, DestroyJRexCharacterDataEvent, (void**)&jrv);
		JREX_LOGLN("SubstringData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SubstringData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SubstringData()--> **** SubstringData DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("SubstringData()--> **** SubstringData NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SubstringData Failed ****",rv);
			}
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

void* PR_CALLBACK HandleJRexCharacterDataEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexCharacterDataEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMCharacterData> cData(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_APPENED_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_APPENED_DATA EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexCharacterDataImpl_AppendDataInternal(nsnull, cData.get(), data);
		}
		case JREX_DELETE_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_DELETE_DATA EVENT!!!****")
			JRexCharacterDataEventParam* param = NS_REINTERPRET_CAST(JRexCharacterDataEventParam*, event->eventData);
			return (void*)JRexCharacterDataImpl_DeleteDataInternal(nsnull, cData.get(), param->offset, param->len);
		}
		case JREX_GET_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_GET_DATA EVENT!!!****")
			return (void*)JRexCharacterDataImpl_GetDataInternal(nsnull, cData.get());
		}
		case JREX_INSERT_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_INSERT_DATA EVENT!!!****")
			JRexCharacterDataEventParam* param = NS_REINTERPRET_CAST(JRexCharacterDataEventParam*, event->eventData);
			return (void*)JRexCharacterDataImpl_InsertDataInternal(nsnull, cData.get(), param->offset, param->data);
		}
		case JREX_REPLACE_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_REPLACE_DATA EVENT!!!****")
			JRexCharacterDataEventParam* param = NS_REINTERPRET_CAST(JRexCharacterDataEventParam*, event->eventData);
			return (void*)JRexCharacterDataImpl_ReplaceDataInternal(nsnull, cData.get(), param->offset, param->len, param->data);
		}
		case JREX_SET_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_SET_DATA EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexCharacterDataImpl_SetDataInternal(nsnull, cData.get(), data);
		}
		case JREX_SUBSTR_DATA:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent JREX_SUBSTR_DATA EVENT!!!****")
			JRexCharacterDataEventParam* param = NS_REINTERPRET_CAST(JRexCharacterDataEventParam*, event->eventData);
			return (void*)JRexCharacterDataImpl_SubstringDataInternal(nsnull, cData.get(), param->offset, param->len);
		}
		default:
		{
			JREX_LOGLN("HandleJRexCharacterDataEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexCharacterDataEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexCharacterDataEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexCharacterDataEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData){
		if(event->eventType==JREX_INSERT_DATA || event->eventType==JREX_DELETE_DATA
			|| event->eventType==JREX_REPLACE_DATA || event->eventType==JREX_SUBSTR_DATA){
			JRexCharacterDataEventParam* param = NS_REINTERPRET_CAST(JRexCharacterDataEventParam*, event->eventData);
			delete param;
		}
	}
	delete event;
}

