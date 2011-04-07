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


#include "org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexNodeFilter.h"

//event types for JRexDocTrav
enum JRexDocTravEventTypes{JREX_CREATE_NODE_ITR=0U,
								JREX_CREATE_TREE_WKR};

static void* PR_CALLBACK HandleJRexDocTravEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocTravEvent(PLEvent* aEvent);

struct JRexDocTravEventParam{
	nsIDOMNode *node;
	PRUint32 whatShow;
	jobject jfilter;
	PRBool entityReferenceExpansion;
};

inline JREX_JNI_UTIL::JRexCommonJRV*
		JRexDocumentTraversalImpl_CreateNodeIteratorInternal(JNIEnv* env,
			nsIDOMDocumentTraversal *docTrav,nsIDOMNode *node,PRUint32 whatShow, jobject jfilter,
					PRBool entityReferenceExpansion){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docTrav){
		nsCOMPtr<nsIDOMNodeIterator> tmpNodeItr;
		nsIDOMNodeFilter *filter=nsnull;
		if(NOT_NULL(jfilter)){
			filter =new JRexNodeFilter(jfilter);
		}
		rv = docTrav->CreateNodeIterator(node,whatShow, filter,
								entityReferenceExpansion, getter_AddRefs(tmpNodeItr));
		JREX_LOGLN("JRexDocumentTraversalImpl_CreateNodeIteratorInternal()--> **** CreateNodeIterator rv<"<<rv<<"> ****")
		if(tmpNodeItr)
			jval=JRexDOMGlobals::CreateNodeIterator(env, tmpNodeItr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
		JRexDocumentTraversalImpl_CreateTreeWalkerInternal(JNIEnv* env,
			nsIDOMDocumentTraversal *docTrav,nsIDOMNode *node,PRUint32 whatShow, jobject jfilter,
					PRBool entityReferenceExpansion){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (docTrav){
		nsCOMPtr<nsIDOMTreeWalker> tmpTreeWkr;
		nsIDOMNodeFilter *filter=nsnull;
		if(NOT_NULL(jfilter)){
			filter =new JRexNodeFilter(jfilter);
		}
		rv = docTrav->CreateTreeWalker(node,whatShow, filter,
								entityReferenceExpansion, getter_AddRefs(tmpTreeWkr));
		JREX_LOGLN("JRexDocumentTraversalImpl_CreateTreeWalkerInternal()--> **** CreateTreeWalker rv<"<<rv<<"> ****")
		if(tmpTreeWkr)
			jval=JRexDOMGlobals::CreateTreeWalker(env, tmpTreeWkr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl
 * Method:    CreateNodeIterator
 * Signature: (Lorg/w3c/dom/Node;ILorg/w3c/dom/traversal/NodeFilter;Z)Lorg/w3c/dom/traversal/NodeIterator;
 */

JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl_CreateNodeIterator
  (JNIEnv *env, jobject jdocTrav, jobject jnode, jint whatShow, jobject jfilter, jboolean entityReferenceExpansion){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentTraversal* thisDocTrav=(nsIDOMDocumentTraversal*)NS_INT32_TO_PTR(env->GetIntField(jdocTrav, JRexDOMGlobals::docTravPeerID));
	JREX_LOGLN("CreateNodeIterator --> **** thisDocTrav <"<<thisDocTrav<<"> ****")
	nsIDOMNode* node=nsnull;
	if(NOT_NULL(jnode))
		node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateNodeIterator()--> **** node <"<<node<<"> ****")

	if(IS_NULL(thisDocTrav) || IS_NULL(node)){
		ThrowJRexException(env, "**** CreateNodeIterator()--> thisDocTrav/node DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateNodeIterator()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTraversalImpl_CreateNodeIteratorInternal(env, thisDocTrav,node,(PRUint32)whatShow, jfilter,
													(entityReferenceExpansion==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		JRexDocTravEventParam *param=new JRexDocTravEventParam;
		if (IS_NULL(param))return NULL;
		param->node=node;
		param->whatShow=whatShow;
		param->jfilter=env->NewGlobalRef(jfilter);
		param->entityReferenceExpansion=entityReferenceExpansion;

		nsresult rv=ExecInEventQDOM(thisDocTrav, JREX_CREATE_NODE_ITR, param, PR_TRUE, HandleJRexDocTravEvent, DestroyJRexDocTravEvent, (void**)&jrv);
		JREX_LOGLN("CreateNodeIterator()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateNodeIterator()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateNodeIterator()--> **** CreateNodeIterator DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateNodeIterator()--> **** CreateNodeIterator NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateNodeIterator Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl
 * Method:    CreateTreeWalker
 * Signature: (Lorg/w3c/dom/Node;ILorg/w3c/dom/traversal/NodeFilter;Z)Lorg/w3c/dom/traversal/TreeWalker;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl_CreateTreeWalker
  (JNIEnv *env, jobject jdocTrav, jobject jnode, jint whatShow, jobject jfilter, jboolean entityReferenceExpansion){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocumentTraversal* thisDocTrav=(nsIDOMDocumentTraversal*)NS_INT32_TO_PTR(env->GetIntField(jdocTrav, JRexDOMGlobals::docTravPeerID));
	JREX_LOGLN("CreateTreeWalker --> **** thisDocTrav <"<<thisDocTrav<<"> ****")
	nsIDOMNode* node=nsnull;
	if(NOT_NULL(jnode))
		node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateTreeWalker()--> **** node <"<<node<<"> ****")

	if(IS_NULL(thisDocTrav) || IS_NULL(node)){
		ThrowJRexException(env, "**** CreateTreeWalker()--> thisDocTrav/node DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateTreeWalker()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentTraversalImpl_CreateTreeWalkerInternal(env, thisDocTrav,node,(PRUint32)whatShow, jfilter,
													(entityReferenceExpansion==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		JRexDocTravEventParam *param=new JRexDocTravEventParam;
		if (IS_NULL(param))return NULL;
		param->node=node;
		param->whatShow=whatShow;
		param->jfilter=env->NewGlobalRef(jfilter);
		param->entityReferenceExpansion=entityReferenceExpansion;

		nsresult rv=ExecInEventQDOM(thisDocTrav, JREX_CREATE_TREE_WKR, param, PR_TRUE, HandleJRexDocTravEvent, DestroyJRexDocTravEvent, (void**)&jrv);
		JREX_LOGLN("CreateTreeWalker()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateTreeWalker()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateTreeWalker()--> **** CreateTreeWalker DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateTreeWalker()--> **** CreateTreeWalker NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateTreeWalker Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl
 * Method:    Finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl_Finalize
  (JNIEnv *env, jobject jdocTrav){
	if(!JRexDOMGlobals::sIntialized)return;
	JREX_TRY
	nsIDOMDocumentTraversal* thisDocTrav=(nsIDOMDocumentTraversal*)NS_INT32_TO_PTR(env->GetIntField(jdocTrav, JRexDOMGlobals::docTravPeerID));
	JREX_LOGLN("JRexDocumentRangeImpl Finalize()--> **** thisDocTrav <"<<thisDocTrav<<"> ****")
	if(IS_NULL(thisDocTrav)){
		ThrowJRexException(env, "JRexDocumentRangeImpl Finalize()--> **** thisDocTrav DOES NOT EXIST!!! ****",0);
		return;
	}
	SAFE_RELEASE(thisDocTrav)
	JREX_CATCH(env)

}

void* PR_CALLBACK HandleJRexDocTravEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocTravEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMDocumentTraversal> docTrav(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_CREATE_NODE_ITR:
		{
			JREX_LOGLN("HandleJRexDocTravEvent JREX_CREATE_NODE_ITR EVENT!!!****")
			JRexDocTravEventParam *param = NS_REINTERPRET_CAST(JRexDocTravEventParam*, event->eventData);

			return (void*)JRexDocumentTraversalImpl_CreateNodeIteratorInternal(nsnull, docTrav.get(),
								param->node,param->whatShow, param->jfilter,param->entityReferenceExpansion);
		}
		case JREX_CREATE_TREE_WKR:
		{
			JREX_LOGLN("HandleJRexDocTravEvent JREX_CREATE_NODE_ITR EVENT!!!****")
			JRexDocTravEventParam *param = NS_REINTERPRET_CAST(JRexDocTravEventParam*, event->eventData);

			return (void*)JRexDocumentTraversalImpl_CreateTreeWalkerInternal(nsnull, docTrav.get(),
								param->node,param->whatShow, param->jfilter,param->entityReferenceExpansion);
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocTravEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocTravEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocTravEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocTravEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData){
		JRexDocTravEventParam *param = NS_REINTERPRET_CAST(JRexDocTravEventParam*, event->eventData);
		delete param;
	}
	delete event;
}

