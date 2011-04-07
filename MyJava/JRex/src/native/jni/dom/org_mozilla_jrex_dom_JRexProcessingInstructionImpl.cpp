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


#include "org_mozilla_jrex_dom_JRexProcessingInstructionImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexProcessingInstruction
enum JRexProcessingInstructionEventTypes{	JREX_GET_DATA=0U,
											JREX_GET_TARGET,
											JREX_SET_TARGET};

static void* PR_CALLBACK HandleJRexProcessingInstructionEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexProcessingInstructionEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexProcessingInstructionImpl_GetDataInternal(JNIEnv *env, nsIDOMProcessingInstruction* pInst){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (pInst){
		nsEmbedString retString;
		rv = pInst->GetData(retString);
		JREX_LOGLN("JRexProcessingInstructionImpl_GetDataInternal()--> **** GetData rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexProcessingInstructionImpl_GetTargetInternal(JNIEnv *env, nsIDOMProcessingInstruction* pInst){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (pInst){
		nsEmbedString retString;
		rv = pInst->GetTarget(retString);
		JREX_LOGLN("JRexProcessingInstructionImpl_GetTargetInternal()--> **** GetTarget rv<"<<rv<<"> ****")
		NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexProcessingInstructionImpl_SetDataInternal(JNIEnv *env, nsIDOMProcessingInstruction* pInst, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (pInst){
		nsEmbedString tdata(data);
		rv = pInst->SetData(tdata);
		JREX_LOGLN("JRexProcessingInstructionImpl_SetDataInternal()--> **** SetData rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexProcessingInstructionImpl
 * Method:    GetData
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexProcessingInstructionImpl_GetData
  (JNIEnv * env, jobject jprocInst){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMProcessingInstruction* thisProcInst=(nsIDOMProcessingInstruction*)
								NS_INT32_TO_PTR(env->GetIntField(jprocInst, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetData()--> **** thisProcInst <"<<thisProcInst<<"> ****")
	if(IS_NULL(thisProcInst)){
		ThrowJRexException(env, "GetData()--> **** thisProcInst DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetData()--> **** IN EVT Q THREAD ****")
		jrv=JRexProcessingInstructionImpl_GetDataInternal(env, thisProcInst);
	}else{
		nsresult rv=ExecInEventQDOM(thisProcInst, JREX_GET_DATA, nsnull, PR_TRUE,
						HandleJRexProcessingInstructionEvent, DestroyJRexProcessingInstructionEvent, (void**)&jrv);
		JREX_LOGLN("GetData()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetData()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetData()--> **** GetData NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetData Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexProcessingInstructionImpl
 * Method:    GetTarget
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexProcessingInstructionImpl_GetTarget
  (JNIEnv * env, jobject jprocInst){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMProcessingInstruction* thisProcInst=(nsIDOMProcessingInstruction*)
									NS_INT32_TO_PTR(env->GetIntField(jprocInst, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetTarget()--> **** thisProcInst <"<<thisProcInst<<"> ****")
	if(IS_NULL(thisProcInst)){
		ThrowJRexException(env, "GetTarget()--> **** thisProcInst DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetTarget()--> **** IN EVT Q THREAD ****")
		jrv=JRexProcessingInstructionImpl_GetDataInternal(env, thisProcInst);
	}else{
		nsresult rv=ExecInEventQDOM(thisProcInst, JREX_GET_TARGET, nsnull, PR_TRUE,
						HandleJRexProcessingInstructionEvent, DestroyJRexProcessingInstructionEvent, (void**)&jrv);
		JREX_LOGLN("GetTarget()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetTarget()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetTarget()--> **** GetTarget NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetTarget Failed ****",rv);
			return NULL;
		}
		return (jstring)jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexProcessingInstructionImpl
 * Method:    SetData
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexProcessingInstructionImpl_SetData
  (JNIEnv * env, jobject jprocInst, jstring jdata){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMProcessingInstruction* thisProcInst=(nsIDOMProcessingInstruction*)
										NS_INT32_TO_PTR(env->GetIntField(jprocInst, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetData()--> **** thisProcInst <"<<thisProcInst<<"> ****")
	if(IS_NULL(thisProcInst)){
		ThrowJRexException(env, "SetData()--> **** thisProcInst DOES NOT EXIST!!! ****",0);
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
		jrv=JRexProcessingInstructionImpl_SetDataInternal(env, thisProcInst, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisProcInst, JREX_SET_TARGET, (void*)data, PR_TRUE,
						HandleJRexProcessingInstructionEvent, DestroyJRexProcessingInstructionEvent, (void**)&jrv);
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

void* PR_CALLBACK HandleJRexProcessingInstructionEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexProcessingInstructionEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMProcessingInstruction> pInst(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_DATA:
		{
			JREX_LOGLN("HandleJRexProcessingInstructionEvent JREX_GET_DATA EVENT!!!****")
			return (void*)JRexProcessingInstructionImpl_GetDataInternal(nsnull, pInst.get());
		}
		case JREX_GET_TARGET:
		{
			JREX_LOGLN("HandleJRexProcessingInstructionEvent JREX_GET_TARGET EVENT!!!****")
			return (void*)JRexProcessingInstructionImpl_GetTargetInternal(nsnull, pInst.get());
		}
		case JREX_SET_TARGET:
		{
			JREX_LOGLN("HandleJRexProcessingInstructionEvent JREX_SET_TARGET EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexProcessingInstructionImpl_SetDataInternal(nsnull, pInst.get(), data);
		}
		default:
		{
			JREX_LOGLN("HandleJRexProcessingInstructionEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexProcessingInstructionEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexProcessingInstructionEvent(PLEvent* aEvent){
	 JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexProcessingInstructionEvent()--> **** target <"<<event->target<<"> ****")
	delete event;
}

