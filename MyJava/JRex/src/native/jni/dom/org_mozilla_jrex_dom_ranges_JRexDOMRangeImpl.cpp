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


#include "org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDOMRange
enum JRexDOMRangeEventTypes{	JREX_GET_START_CONT=0U,
								JREX_GET_START_OFFSET,
								JREX_GET_END_CONT,
								JREX_GET_END_OFFSET,
								JREX_GET_COLLAPSED,
								JREX_GET_COM_CONT,
								JREX_SET_END,
								JREX_SET_START,
								JREX_SET_START_BEFORE,
								JREX_SET_START_AFTER,
								JREX_SET_END_BEFORE,
								JREX_SET_END_AFTER,
								JREX_COLLAPSE,
								JREX_SEL_NODE,
								JREX_SEL_NODE_CONT,
								JREX_DEL_CONT,
								JREX_EXT_CONT,
								JREX_CLONE_CONT,
								JREX_INSERT_NODE,
								JREX_SUR_CONT,
								JREX_CLONE_RANGE,
								JREX_TO_STRING,
								JREX_DETACH};

struct JRexRangeEventParam{
	nsIDOMNode *node;
	PRUint32 offset;
};

static void* PR_CALLBACK HandleJRexDOMRangeEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDOMRangeEvent(PLEvent* aEvent);

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetStartContainerInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = range->GetStartContainer(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDOMRangeImpl_GetStartContainerInternal()--> **** GetStartContainer rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetStartOffsetInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		PRInt32 startOffSet=0;
		rv = range->GetStartOffset(&startOffSet);
		JREX_LOGLN("JRexDOMRangeImpl_GetStartOffsetInternal()--> **** GetStartOffset rv<"<<rv<<"> startOffSet<"<<startOffSet<<"> ****")
		if(NS_SUCCEEDED(rv))
			jval=(jobject)startOffSet;
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetEndContainerInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = range->GetEndContainer(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDOMRangeImpl_GetEndContainerInternal()--> **** GetEndContainer rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetEndOffsetInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		PRInt32 endOffSet=0;
		rv = range->GetEndOffset(&endOffSet);
		JREX_LOGLN("JRexDOMRangeImpl_GetEndOffsetInternal()--> **** GetEndOffset rv<"<<rv<<"> endOffSet<"<<endOffSet<<">****")
		if(NS_SUCCEEDED(rv))
			jval=(jobject)endOffSet;
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetCollapsedInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		PRBool retBool = PR_FALSE;
		rv = range->GetCollapsed(&retBool);
		JREX_LOGLN("JRexDOMRangeImpl_GetCollapsedInternal()--> **** GetEndOffset rv<"<<rv<<"> retBool<"<<retBool<<">****")
		if(NS_SUCCEEDED(rv))
			jval=(jobject)retBool;
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_GetCommonAncestorContainerInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = range->GetCommonAncestorContainer(getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDOMRangeImpl_GetCommonAncestorContainerInternal()--> **** GetCommonAncestorContainer rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetStartInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node, PRUint32 offSet){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SetStart(node, offSet);
		JREX_LOGLN("JRexDOMRangeImpl_SetStartInternal()--> **** SetStart rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetEndInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node, PRUint32 offSet){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SetEnd(node, offSet);
		JREX_LOGLN("JRexDOMRangeImpl_SetEndInternal()--> **** SetEnd rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetStartBeforeInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SetStartBefore(node);
		JREX_LOGLN("JRexDOMRangeImpl_SetStartBeforeInternal()--> **** SetStartBefore rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetStartAfterInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SetStartAfter(node);
		JREX_LOGLN("JRexDOMRangeImpl_SetStartAfterInternal()--> **** SetStartAfter rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetEndBeforeInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SetEndBefore(node);
		JREX_LOGLN("JRexDOMRangeImpl_SetEndBeforeInternal()--> **** SetEndBefore rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SetEndAfterInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		JREX_LOGLN("JRexDOMRangeImpl_SetEndAfterInternal()--> **** SetEndAfter rv<"<<rv<<"> ****")
		rv = range->SetEndAfter(node);
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_CollapseInternal(JNIEnv *env, nsIDOMRange* range, PRBool toStart){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->Collapse(toStart);
		JREX_LOGLN("JRexDOMRangeImpl_CollapseInternal()--> **** Collapse rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SelectNodeInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SelectNode(node);
		JREX_LOGLN("JRexDOMRangeImpl_SelectNodeInternal()--> **** SelectNode rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SelectNodeContentsInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SelectNodeContents(node);
		JREX_LOGLN("JRexDOMRangeImpl_SelectNodeContentsInternal()--> **** SelectNodeContents rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_DeleteContentsInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->DeleteContents();
		JREX_LOGLN("JRexDOMRangeImpl_DeleteContentsInternal()--> **** DeleteContents rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_ExtractContentsInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMDocumentFragment> tmpDocFrag;
		rv = range->ExtractContents(getter_AddRefs(tmpDocFrag));
		JREX_LOGLN("JRexDOMRangeImpl_ExtractContentsInternal()--> **** ExtractContents rv<"<<rv<<"> ****")
		if(tmpDocFrag)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocFrag.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_CloneContentsInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMDocumentFragment> tmpDocFrag;
		rv = range->CloneContents(getter_AddRefs(tmpDocFrag));
		JREX_LOGLN("JRexDOMRangeImpl_CloneContentsInternal()--> **** CloneContents rv<"<<rv<<"> ****")
		if(tmpDocFrag)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocFrag.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_InsertNodeInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->InsertNode(node);
		JREX_LOGLN("JRexDOMRangeImpl_InsertNodeInternal()--> **** InsertNode rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_SurroundContentsInternal(JNIEnv *env, nsIDOMRange* range, nsIDOMNode *node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->SurroundContents(node);
		JREX_LOGLN("JRexDOMRangeImpl_SurroundContentsInternal()--> **** SurroundContents rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_CloneRangeInternal(JNIEnv *env, nsIDOMRange* range){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsCOMPtr<nsIDOMRange> tmpRange;
		rv = range->CloneRange(getter_AddRefs(tmpRange));
		JREX_LOGLN("JRexDOMRangeImpl_CloneRangeInternal()--> **** CloneRange rv<"<<rv<<"> ****")
		if(tmpRange)
			jval=JRexDOMGlobals::CreateRange(env, tmpRange.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_ToStringInternal(JNIEnv *env, nsIDOMRange* range){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		nsEmbedString retString;
		rv = range->ToString(retString);
		JREX_LOGLN("JRexDOMRangeImpl_ToStringInternal()--> **** ToString rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			NS_STR_TO_JSTR(env,retString,jval)
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDOMRangeImpl_DetachInternal(JNIEnv *env, nsIDOMRange* range){
	if(IS_NULL(env))env=JRex_GetEnv(0);
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (range){
		rv = range->Detach();
		JREX_LOGLN("JRexDOMRangeImpl_DetachInternal()--> **** Detach rv<"<<rv<<"> ****")
	}
	jrv->jobj=NULL;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetStartContainer
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetStartContainer
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetStartContainer()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetStartContainer()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetStartContainer()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetStartContainerInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_START_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetStartContainer()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetStartContainer()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetStartContainer()--> **** GetStartContainer DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetStartContainer()--> **** GetStartContainer NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetStartContainer Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetStartOffset
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetStartOffset
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return -1;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetStartOffset()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetStartOffset()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return -1;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetStartOffset()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetStartOffsetInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_START_OFFSET, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetStartOffset()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetStartOffset()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetStartOffset()--> **** GetStartOffset DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetStartOffset()--> **** GetStartOffset NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetStartOffset Failed ****",rv);
			}
			return -1;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return -1;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetEndContainer
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetEndContainer
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetEndContainer()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetEndContainer()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetEndContainer()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetEndContainerInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_END_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetEndContainer()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetEndContainer()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetEndContainer()--> **** GetEndContainer DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetEndContainer()--> **** GetEndContainer NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetEndContainer Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetEndOffset
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetEndOffset
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return -1;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetEndOffset()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetEndOffset()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return -1;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetEndOffset()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetEndOffsetInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_END_OFFSET, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetEndOffset()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetEndOffset()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetEndOffset()--> **** GetEndOffset DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetEndOffset()--> **** GetEndOffset NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetEndOffset Failed ****",rv);
			}
			return -1;
		}
		return (jint)jobj;
	}
	JREX_CATCH(env)
	return -1;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetCollapsed
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetCollapsed
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return JNI_FALSE;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetCollapsed()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetCollapsed()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetCollapsed()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetCollapsedInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_COLLAPSED, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetCollapsed()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetCollapsed()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetCollapsed()--> **** GetCollapsed DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetCollapsed()--> **** GetCollapsed NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetCollapsed Failed ****",rv);
			}
			return JNI_FALSE;
		}
		return (jboolean)NS_PTR_TO_INT32(jobj);
	}
	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    GetCommonAncestorContainer
 * Signature: ()Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_GetCommonAncestorContainer
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("GetCommonAncestorContainer()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "GetCommonAncestorContainer()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetCommonAncestorContainer()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_GetCommonAncestorContainerInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_GET_COM_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("GetCommonAncestorContainer()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetCommonAncestorContainer()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("GetCommonAncestorContainer()--> **** GetCommonAncestorContainer DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("GetCommonAncestorContainer()--> **** GetCommonAncestorContainer NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** GetCommonAncestorContainer Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetStart
 * Signature: (Lorg/w3c/dom/Node;I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetStart
  (JNIEnv * env, jobject jrangeImpl, jobject jnode, jint joffSet){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetStart()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetStart()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetStart()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetStart()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetStartInternal(env, thisRange, refNode, (PRUint32)joffSet);
	}else{
		JRexRangeEventParam* param=new JRexRangeEventParam;
		if(IS_NULL(param))return;
		param->node=refNode;
		param->offset=(PRUint32)joffSet;
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_START, param, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetStart()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetStart()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetStart()--> **** SetStart DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetStart()--> **** SetStart RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetStart()--> **** SetStart NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetStart Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetEnd
 * Signature: (Lorg/w3c/dom/Node;I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetEnd
  (JNIEnv * env, jobject jrangeImpl, jobject jnode, jint joffSet){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetEnd()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetEnd()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetEnd()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetEnd()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetEndInternal(env, thisRange, refNode, (PRUint32)joffSet);
	}else{
		JRexRangeEventParam* param=new JRexRangeEventParam;
		if(IS_NULL(param))return;
		param->node=refNode;
		param->offset=(PRUint32)joffSet;
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_END, param, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetEnd()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetEnd()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetEnd()--> **** SetEnd DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetEnd()--> **** SetEnd RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetEnd()--> **** SetEnd NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetEnd Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetStartBefore
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetStartBefore
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetStartBefore()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetStartBefore()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetStartBefore()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetStartBefore()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetStartBeforeInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_START_BEFORE, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetStartBefore()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetStartBefore()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetStartBefore()--> **** SetStartBefore DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetStartBefore()--> **** SetStartBefore RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetStartBefore()--> **** SetStartBefore NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetStartBefore Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetStartAfter
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetStartAfter
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetStartAfter()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetStartAfter()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetStartAfter()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetStartAfter()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetStartAfterInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_START_AFTER, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetStartAfter()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetStartAfter()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetStartAfter()--> **** SetStartAfter DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetStartAfter()--> **** SetStartAfter RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetStartAfter()--> **** SetStartAfter NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetStartAfter Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetEndBefore
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetEndBefore
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetEndBefore()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetEndBefore()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetEndBefore()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetEndBefore()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetEndBeforeInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_END_BEFORE, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetEndBefore()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetEndBefore()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetEndBefore()--> **** SetEndBefore DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetEndBefore()--> **** SetEndBefore RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetEndBefore()--> **** SetEndBefore NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetEndBefore Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SetEndAfter
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SetEndAfter
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SetEndAfter()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SetEndAfter()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SetEndAfter()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SetEndAfter()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SetEndAfterInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SET_END_AFTER, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SetEndAfter()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SetEndAfter()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SetEndAfter()--> **** SetEndAfter DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SetEndAfter()--> **** SetEndAfter RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SetEndAfter()--> **** SetEndAfter NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SetEndAfter Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    Collapse
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_Collapse
  (JNIEnv * env, jobject jrangeImpl, jboolean jtoStart){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("Collapse()--> **** thisRange <"<<thisRange<<"> ****")

	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "**** Collapse()--> thisRange DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Collapse()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_CollapseInternal(env, thisRange, (jtoStart==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_COLLAPSE, (void*)(jtoStart==JNI_TRUE?PR_TRUE:PR_FALSE), PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("Collapse()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("Collapse()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("Collapse()--> **** Collapse DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("Collapse()--> **** Collapse NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** Collapse Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SelectNode
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SelectNode
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SelectNode()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SelectNode()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SelectNode()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SelectNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SelectNodeInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SEL_NODE, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SelectNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SelectNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SelectNode()--> **** SelectNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SelectNode()--> **** SelectNode RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SelectNode()--> **** SelectNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SelectNode Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SelectNodeContents
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SelectNodeContents
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SelectNodeContents()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SelectNodeContents()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SelectNodeContents()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SelectNodeContents()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SelectNodeInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SEL_NODE_CONT, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SelectNodeContents()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SelectNodeContents()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("SelectNodeContents()--> **** SelectNodeContents DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else
			if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
				JREX_LOGLN("SelectNodeContents()--> **** SelectNodeContents RANGE ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowRangeException(env, rv);
			}else{
				JREX_LOGLN("SelectNodeContents()--> **** SelectNodeContents NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** SelectNodeContents Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    CompareBoundaryPoints
 * Signature: (ILorg/mozilla/jrex/dom/JRexDOMRange;)I
 */
JNIEXPORT jshort JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_CompareBoundaryPoints
  (JNIEnv * env, jobject jrangeImpl, jint cmptype, jobject jsrcRange){

	if(!JRexDOMGlobals::sIntialized)return 0;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("CompareBoundaryPoints()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMRange* srcRange=nsnull;
	if(NOT_NULL(jsrcRange))
		srcRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jsrcRange, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("CompareBoundaryPoints()--> **** srcRange <"<<srcRange<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(srcRange)){
		ThrowJRexException(env, "**** CompareBoundaryPoints()--> thisRange/srcRange DOES NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt16 rVal=0;
	nsresult rv = thisRange->CompareBoundaryPoints((PRUint16)cmptype,srcRange,&rVal);
	JREX_LOGLN("CompareBoundaryPoints()--> **** CompareBoundaryPoints rv<"<<rv<<"> ****")
	if (NS_FAILED(rv)) {
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("CompareBoundaryPoints()--> **** CompareBoundaryPoints DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
			JREX_LOGLN("CompareBoundaryPoints()--> **** CompareBoundaryPoints NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CompareBoundaryPoints Failed ****",rv);
		}
		return 0;
	}
	return (jshort)rVal;
	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    DeleteContents
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_DeleteContents
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("DeleteContents()--> **** thisRange <"<<thisRange<<"> ****")

	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "**** DeleteContents()--> thisRange DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("DeleteContents()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_DeleteContentsInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_DEL_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("DeleteContents()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("DeleteContents()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
	if (NS_FAILED(rv)) {
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("DeleteContents()--> **** DeleteContents DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else{
			JREX_LOGLN("DeleteContents()--> **** DeleteContents NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** DeleteContents Failed ****",rv);
		}
	}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    ExtractContents
 * Signature: ()Lorg/w3c/dom/DocumentFragment;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_ExtractContents
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("ExtractContents()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "ExtractContents()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ExtractContents()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_ExtractContentsInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_EXT_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("ExtractContents()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ExtractContents()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("ExtractContents()--> **** ExtractContents DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("ExtractContents()--> **** ExtractContents NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** ExtractContents Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    CloneContents
 * Signature: ()Lorg/w3c/dom/DocumentFragment;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_CloneContents
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("CloneContents()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "CloneContents()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CloneContents()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_CloneContentsInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_CLONE_CONT, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("CloneContents()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CloneContents()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CloneContents()--> **** CloneContents DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CloneContents()--> **** CloneContents NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CloneContents Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    InsertNode
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_InsertNode
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("InsertNode()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("InsertNode()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** InsertNode()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("InsertNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_InsertNodeInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_INSERT_NODE, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("InsertNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("InsertNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
	if (NS_FAILED(rv)) {
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("InsertNode()--> **** InsertNode DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else
		if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
			JREX_LOGLN("InsertNode()--> **** InsertNode RANGE ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowRangeException(env, rv);
		}else{
			JREX_LOGLN("InsertNode()--> **** InsertNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** InsertNode Failed ****",rv);
		}
	}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    SurroundContents
 * Signature: (Lorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_SurroundContents
  (JNIEnv * env, jobject jrangeImpl, jobject jnode){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("SurroundContents()--> **** thisRange <"<<thisRange<<"> ****")

	nsIDOMNode* refNode=nsnull;
	if(NOT_NULL(jnode))
		refNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SurroundContents()--> **** refNode <"<<refNode<<"> ****")

	if(IS_NULL(thisRange) || IS_NULL(refNode)){
		ThrowJRexException(env, "**** SurroundContents()--> thisRange/refNode DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("SurroundContents()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_SurroundContentsInternal(env, thisRange, refNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_SUR_CONT, refNode, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("SurroundContents()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("SurroundContents()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
	if (NS_FAILED(rv)) {
		if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
			JREX_LOGLN("SurroundContents()--> **** SurroundContents DOM ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowDOMException(env, rv);
		}else
		if(NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM_RANGE){
			JREX_LOGLN("SurroundContents()--> **** SurroundContents RANGE ERROR OCCURED !!!****")
			JRexDOMGlobals::ThrowRangeException(env, rv);
		}else{
			JREX_LOGLN("SurroundContents()--> **** SurroundContents NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** SurroundContents Failed ****",rv);
		}
	}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    CloneRange
 * Signature: ()Lorg/mozilla/jrex/dom/JRexDOMRange;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_CloneRange
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("CloneRange()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "CloneRange()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CloneRange()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_CloneRangeInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_CLONE_RANGE, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("CloneRange()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CloneRange()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CloneRange()--> **** CloneRange DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CloneRange()--> **** CloneRange NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CloneRange Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    ToString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_ToString
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("ToString()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "ToString()--> **** thisRange DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ToString()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_ToStringInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_TO_STRING, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("ToString()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ToString()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("ToString()--> **** ToString DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("ToString()--> **** ToString NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** ToString Failed ****",rv);
			}
			return NULL;
		}
		return (jstring)jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    Detach
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_Detach
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("Detach()--> **** thisRange <"<<thisRange<<"> ****")

	if(IS_NULL(thisRange)){
		ThrowJRexException(env, "**** Detach()--> thisRange DOES NOT EXIST!!! ****",0);
		return;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("Detach()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_DetachInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_DETACH, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("Detach()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("Detach()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("Detach()--> **** Detach DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("Detach()--> **** Detach NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** Detach Failed ****",rv);
			}
		}
	}
	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl_Finalize
  (JNIEnv * env, jobject jrangeImpl){

	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMRange* thisRange=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrangeImpl, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** thisRange <"<<thisRange<<"> ****")
	if(IS_NULL(thisRange)){
		JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** thisRange DOES NOT EXIST!!! ****");
		return;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** IN EVT Q THREAD ****")
		jrv=JRexDOMRangeImpl_DetachInternal(env, thisRange);
	}else{
		nsresult rv=ExecInEventQDOM(thisRange, JREX_DETACH, nsnull, PR_TRUE, HandleJRexDOMRangeEvent, DestroyJRexDOMRangeEvent, (void**)&jrv);
		JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** Detach DOM ERROR OCCURED !!!****")
			}else{
				JREX_LOGLN("JRexDOMRangeImpl Finalize()--> **** Detach NON-DOM ERROR OCCURED !!!****")
			}
		}
	}
	SAFE_RELEASE(thisRange)
	JREX_CATCH(env)
}


void* PR_CALLBACK HandleJRexDOMRangeEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDOMRangeEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMRange> range(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_START_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_START_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetStartContainerInternal(nsnull, range.get());
		}
		case JREX_GET_START_OFFSET:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_START_OFFSET EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetStartOffsetInternal(nsnull, range.get());
		}
		case JREX_GET_END_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_END_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetEndContainerInternal(nsnull, range.get());
		}
		case JREX_GET_END_OFFSET:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_END_OFFSET EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetEndOffsetInternal(nsnull, range.get());
		}
		case JREX_GET_COLLAPSED:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_COLLAPSED EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetCollapsedInternal(nsnull, range.get());
		}
		case JREX_GET_COM_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_GET_COM_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_GetCommonAncestorContainerInternal(nsnull, range.get());
		}
		case JREX_SET_START:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_START EVENT!!!****")
			JRexRangeEventParam* parm = NS_REINTERPRET_CAST(JRexRangeEventParam*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetStartInternal(nsnull, range.get(), parm->node, parm->offset);
		}
		case JREX_SET_END:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_END EVENT!!!****")
			JRexRangeEventParam* parm = NS_REINTERPRET_CAST(JRexRangeEventParam*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetEndInternal(nsnull, range.get(), parm->node, parm->offset);
		}
		case JREX_SET_START_BEFORE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_START_BEFORE EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetStartBeforeInternal(nsnull, range.get(), node);
		}
		case JREX_SET_START_AFTER:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_START_AFTER EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetStartAfterInternal(nsnull, range.get(), node);
		}
		case JREX_SET_END_BEFORE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_END_BEFORE EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetEndBeforeInternal(nsnull, range.get(), node);
		}
		case JREX_SET_END_AFTER:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SET_END_AFTER EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SetEndAfterInternal(nsnull, range.get(), node);
		}
		case JREX_COLLAPSE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_COLLAPSE EVENT!!!****")
			PRBool isStart = NS_REINTERPRET_CAST(PRBool, event->eventData);
			return (void*)JRexDOMRangeImpl_CollapseInternal(nsnull, range.get(), isStart);
		}
		case JREX_SEL_NODE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SEL_NODE EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SelectNodeInternal(nsnull, range.get(), node);
		}
		case JREX_SEL_NODE_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SEL_NODE_CONT EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SelectNodeContentsInternal(nsnull, range.get(), node);
		}
		case JREX_DEL_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_DEL_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_DeleteContentsInternal(nsnull, range.get());
		}
		case JREX_EXT_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_EXT_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_ExtractContentsInternal(nsnull, range.get());
		}
		case JREX_CLONE_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_CLONE_CONT EVENT!!!****")
			return (void*)JRexDOMRangeImpl_CloneContentsInternal(nsnull, range.get());
		}
		case JREX_INSERT_NODE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_INSERT_NODE EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_InsertNodeInternal(nsnull, range.get(),node);
		}
		case JREX_SUR_CONT:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_SUR_CONT EVENT!!!****")
			nsIDOMNode* node = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDOMRangeImpl_SurroundContentsInternal(nsnull, range.get(),node);
		}
		case JREX_CLONE_RANGE:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_CLONE_RANGE EVENT!!!****")
			return (void*)JRexDOMRangeImpl_CloneRangeInternal(nsnull, range.get());
		}
		case JREX_TO_STRING:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_TO_STRING EVENT!!!****")
			return (void*)JRexDOMRangeImpl_ToStringInternal(nsnull, range.get());
		}
		case JREX_DETACH:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent JREX_DETACH EVENT!!!****")
			return (void*)JRexDOMRangeImpl_DetachInternal(nsnull, range.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDOMRangeEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDOMRangeEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDOMRangeEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDOMRangeEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData &&
			(event->eventType==JREX_SET_START
			|| event->eventType==JREX_SET_END)){
			JRexRangeEventParam* param = NS_REINTERPRET_CAST(JRexRangeEventParam*, event->eventData);
			delete param;
	}
	delete event;
}

