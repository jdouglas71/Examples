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


#include "org_mozilla_jrex_dom_JRexDocumentImpl.h"
#include "JRexDOMGlobals.h"

//event types for JRexDocument
enum JRexDocumentEventTypes{JREX_CREATE_ATTRB=0U,
							JREX_CREATE_ATTRBNS,
							JREX_CREATE_CDATA,
							JREX_CREATE_COMMENT,
 							JREX_CREATE_DOC_FRAG,
							JREX_CREATE_ELE,
							JREX_CREATE_ELENS,
 							JREX_CREATE_ENTITY_REF,
 							JREX_CREATE_PROC_INST,
 							JREX_CREATE_TEXT_NODE,
 							JREX_GET_DOC_TYPE,
 							JREX_GET_DOC_ELE,
 							JREX_GET_ELE_BYID,
 							JREX_GET_ELES_BY_TAG,
 							JREX_GET_ELES_BY_TAGNS,
 							JREX_GET_IMPL,
 							JREX_IMPORT_NODE,
 							JREX_GET_DOC_RANGE,
 							JREX_GET_DOC_EVENT,
 							JREX_GET_DOC_TRAV,
 							JREX_GET_DOC_VIEW,
 							//DOM3
 							JREX_GET_IN_ENCOD,
 							JREX_GET_XML_ENCOD,
 							JREX_GET_XML_STDALN,
 							JREX_SET_XML_STDALN,
 							JREX_GET_XML_VER,
 							JREX_SET_XML_VER,
 							JREX_GET_STRIC_ERROR,
 							JREX_SET_STRIC_ERROR,
 							JREX_GET_DOC_URI,
 							JREX_SET_DOC_URI,
 							JREX_ADPT_NODE,
 							JREX_GET_CONFIG,
 							JREX_NORM_DOC,
 							JREX_RNM_NODE};


static void* PR_CALLBACK HandleJRexDocumentEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRexDocumentEvent(PLEvent* aEvent);

static void* PR_CALLBACK HandleJRex3DocumentEvent(PLEvent* aEvent);
static void PR_CALLBACK DestroyJRex3DocumentEvent(PLEvent* aEvent);

struct JRexDocumentEventParam{
	PRUnichar *data1;
	PRUnichar *data2;
};

struct JRexImportNodeEventParam{
	nsIDOMNode *node;
	PRBool deep;
};

struct JRexRenameNodeEventParam : JRexDocumentEventParam{
	nsIDOMNode *node;
};

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateAttributeInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		nsEmbedString tname(name);
		rv = doc->CreateAttribute(tname, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexDocumentImpl_CreateAttributeInternal()--> **** CreateAttribute rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateAttributeNSInternal(JNIEnv *env, nsIDOMDocument* doc,
									PRUnichar* nameSpace, PRUnichar* qualifiedName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMAttr> tmpAttr;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tqualifiedName(qualifiedName);
		rv = doc->CreateAttributeNS(tnameSpace, tqualifiedName, getter_AddRefs(tmpAttr));
		JREX_LOGLN("JRexDocumentImpl_CreateAttributeNSInternal()--> **** CreateAttributeNS rv<"<<rv<<"> ****")
		if(tmpAttr)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpAttr.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateCDATASectionInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMCDATASection> tmpCData;
		nsEmbedString tdata(data);
		rv = doc->CreateCDATASection(tdata, getter_AddRefs(tmpCData));
		JREX_LOGLN("JRexDocumentImpl_CreateCDATASectionInternal()--> **** CreateCDATASection rv<"<<rv<<"> ****")
		if(tmpCData)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpCData.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateCommentInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMComment> tmpCmt;
		nsEmbedString tdata(data);
		rv = doc->CreateComment(tdata, getter_AddRefs(tmpCmt));
		JREX_LOGLN("JRexDocumentImpl_CreateCommentInternal()--> **** CreateComment rv<"<<rv<<"> ****")
		if(tmpCmt)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpCmt.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateDocumentFragmentInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentFragment> tmpDocFrag;
		rv = doc->CreateDocumentFragment(getter_AddRefs(tmpDocFrag));
		JREX_LOGLN("JRexDocumentImpl_CreateDocumentFragmentInternal()--> **** CreateDocumentFragment rv<"<<rv<<"> ****")
		if(tmpDocFrag)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocFrag.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateElementInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* tagName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMElement> tmpEle;
		nsEmbedString ttagName(tagName);
		rv = doc->CreateElement(ttagName, getter_AddRefs(tmpEle));
		JREX_LOGLN("JRexDocumentImpl_CreateElementInternal()--> **** CreateElement rv<"<<rv<<"> ****")
		if(tmpEle)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEle.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateElementNSInternal(JNIEnv *env, nsIDOMDocument* doc,
									PRUnichar* nameSpace, PRUnichar* qualifiedName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMElement> tmpEle;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tqualifiedName(qualifiedName);
		rv = doc->CreateElementNS(tnameSpace, tqualifiedName, getter_AddRefs(tmpEle));
		JREX_LOGLN("JRexDocumentImpl_CreateElementNSInternal()--> **** CreateElementNS rv<"<<rv<<"> ****")
		if(tmpEle)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEle.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateEntityReferenceInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMEntityReference> tmpEntRef;
		nsEmbedString tname(name);
		rv = doc->CreateEntityReference(tname, getter_AddRefs(tmpEntRef));
		JREX_LOGLN("JRexDocumentImpl_CreateEntityReferenceInternal()--> **** CreateEntityReference rv<"<<rv<<"> ****")
		if(tmpEntRef)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEntRef.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateProcessingInstructionInternal(JNIEnv *env, nsIDOMDocument* doc,
									PRUnichar* target, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMProcessingInstruction> tmpPInst;
		nsEmbedString ttarget(target);
		nsEmbedString tdata(data);
		rv = doc->CreateProcessingInstruction(ttarget, tdata, getter_AddRefs(tmpPInst));
		JREX_LOGLN("JRexDocumentImpl_CreateProcessingInstructionInternal()--> **** CreateProcessingInstruction rv<"<<rv<<"> ****")
		if(tmpPInst)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpPInst.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_CreateTextNodeInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* data){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMText> tmpTxt;
		nsEmbedString tdata(data);
		rv = doc->CreateTextNode(tdata, getter_AddRefs(tmpTxt));
		JREX_LOGLN("JRexDocumentImpl_CreateTextNodeInternal()--> **** CreateTextNode rv<"<<rv<<"> ****")
		if(tmpTxt)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpTxt.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDoctypeInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentType> tmpDocType;
		rv = doc->GetDoctype(getter_AddRefs(tmpDocType));
		JREX_LOGLN("JRexDocumentImpl_GetDoctypeInternal()--> **** GetDoctype rv<"<<rv<<"> ****")
		if(tmpDocType)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpDocType.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDocumentElementInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMElement> tmpEle;
		rv = doc->GetDocumentElement(getter_AddRefs(tmpEle));
		JREX_LOGLN("JRexDocumentImpl_GetDocumentElementInternal()--> **** GetDocumentElement rv<"<<rv<<"> ****")
		if(tmpEle)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEle.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetElementByIdInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* eleID){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMElement> tmpEle;
		nsEmbedString teleID(eleID);
		rv = doc->GetElementById(teleID, getter_AddRefs(tmpEle));
		JREX_LOGLN("JRexDocumentImpl_GetElementByIdInternal()--> **** GetElementById rv<"<<rv<<"> ****")
		if(tmpEle)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpEle.get());
	}
	if(eleID)nsMemory::Free(eleID);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetElementsByTagNameInternal(JNIEnv *env, nsIDOMDocument* doc, PRUnichar* name){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		nsEmbedString tname(name);
		rv = doc->GetElementsByTagName(tname, getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexDocumentImpl_GetElementsByTagNameInternal()--> **** GetElementsByTagName rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	if(name)nsMemory::Free(name);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetElementsByTagNameNSInternal(JNIEnv *env, nsIDOMDocument* doc,
										PRUnichar* nameSpace, PRUnichar* localName) {
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMNodeList> tmpNodeList;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tlocalName(localName);

		rv = doc->GetElementsByTagNameNS(tnameSpace, tlocalName, getter_AddRefs(tmpNodeList));
		JREX_LOGLN("JRexDocumentImpl_GetElementsByTagNameNSInternal()--> **** GetElementsByTagNameNS rv<"<<rv<<"> ****")
		if(tmpNodeList)
			jval=JRexDOMGlobals::CreateNodeList(env, tmpNodeList.get());
	}
	if(nameSpace)nsMemory::Free(nameSpace);
	if(localName)nsMemory::Free(localName);
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetImplementationInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDOMImplementation> tmpDomImpl;
		rv = doc->GetImplementation(getter_AddRefs(tmpDomImpl));
		JREX_LOGLN("JRexDocumentImpl_GetImplementationInternal()--> **** GetImplementation rv<"<<rv<<"> ****")
		if(tmpDomImpl)
			jval=JRexDOMGlobals::CreateDOMImpl(env, tmpDomImpl.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_ImportNodeInternal(JNIEnv *env, nsIDOMDocument* doc, nsIDOMNode* node, PRBool deep){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = doc->ImportNode(node, deep, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDocumentImpl_ImportNodeInternal()--> **** ImportNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDocumentRangeInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentRange> docRange(do_QueryInterface(doc,&rv));
		JREX_LOGLN("JRexDocumentImpl_GetDocumentRangeInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(docRange)
			jval=JRexDOMGlobals::CreateDocumentRange(env, docRange.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDocumentEventInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentEvent> docEvent(do_QueryInterface(doc,&rv));
		JREX_LOGLN("JRexDocumentImpl_GetDocumentEventInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(docEvent)
			jval=JRexDOMGlobals::CreateDocumentEvent(env, docEvent.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDocumentTraversalInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentTraversal> docTrav(do_QueryInterface(doc,&rv));
		JREX_LOGLN("JRexDocumentImpl_GetDocumentTraversalInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(docTrav)
			jval=JRexDOMGlobals::CreateDocumentTraversal(env, docTrav.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDocumentViewInternal(JNIEnv *env, nsIDOMDocument* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDocumentView> docView(do_QueryInterface(doc,&rv));
		JREX_LOGLN("JRexDocumentImpl_GetDocumentViewInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
		if(docView)
			jval=JRexDOMGlobals::CreateDocumentView(env, docView.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_AdoptNodeInternal(JNIEnv *env, nsIDOM3Document* doc, nsIDOMNode* node){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMNode> tmpNode;
		rv = doc->AdoptNode(node, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDocumentImpl_AdoptNodeInternal()--> **** AdoptNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_GetDomConfigInternal(JNIEnv *env, nsIDOM3Document* doc){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMDOMConfiguration> tmpCfg;
		rv = doc->GetDomConfig(getter_AddRefs(tmpCfg));
		JREX_LOGLN("JRexDocumentImpl_GetDomConfigInternal()--> **** GetDomConfig rv<"<<rv<<"> ****")
		if(tmpCfg)
			jval=JRexDOMGlobals::CreateDOMConfiguration(env, tmpCfg.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}

inline JREX_JNI_UTIL::JRexCommonJRV*
	JRexDocumentImpl_RenameNodeInternal(JNIEnv *env, nsIDOM3Document* doc, nsIDOMNode* node
											, PRUnichar* nameSpace, PRUnichar* qualifiedName){
	JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
	if(IS_NULL(jrv))return NULL;
	jobject jval=NULL;
	nsresult rv=NS_ERROR_FAILURE;
	if (doc){
		nsCOMPtr<nsIDOMNode> tmpNode;
		nsEmbedString tnameSpace(nameSpace);
		nsEmbedString tqualifiedName(qualifiedName);
		rv = doc->RenameNode(node, tnameSpace, tqualifiedName, getter_AddRefs(tmpNode));
		JREX_LOGLN("JRexDocumentImpl_RenameNodeInternal()--> **** RenameNode rv<"<<rv<<"> ****")
		if(tmpNode)
			jval=JRexDOMGlobals::CreateNodeByType(env, tmpNode.get());
	}
	jrv->jobj=jval;
	jrv->rv=rv;
	return jrv;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateAttribute
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateAttribute
  (JNIEnv * env, jobject jdoc, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateAttribute()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateAttribute()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("CreateAttribute()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateAttribute()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateAttributeInternal(env, thisDoc, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_ATTRB, (void*)name, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateAttribute()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateAttribute()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateAttribute()--> **** CreateAttribute DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateAttribute()--> **** CreateAttribute NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateAttribute Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateAttributeNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Attr;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateAttributeNS
  (JNIEnv * env, jobject jdoc, jstring jnamespaceURI ,jstring jqualifiedName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateAttributeNS()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateAttributeNS()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName)){
		JREX_LOGLN("CreateAttributeNS()--> **** jnamespaceURI/jqualifiedName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateAttributeNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateAttributeNSInternal(env, thisDoc, namespaceURI, qualifiedName);
	}else{
		JRexDocumentEventParam *param=new JRexDocumentEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=namespaceURI;
		param->data2=qualifiedName;

		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_ATTRBNS, param, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateAttributeNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateAttributeNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateAttributeNS()--> **** CreateAttributeNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateAttributeNS()--> **** CreateAttributeNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateAttributeNS Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateCDATASection
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/CDATASection;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateCDATASection
  (JNIEnv * env, jobject jdoc, jstring jdata){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateCDATASection()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateCDATASection()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jdata)){
		JREX_LOGLN("CreateCDATASection()--> **** jdata is NULL ****")
		return NULL;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateCDATASection()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateCDATASectionInternal(env, thisDoc, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_CDATA, (void*)data, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateCDATASection()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateCDATASection()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateCDATASection()--> **** CreateCDATASection DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateCDATASection()--> **** CreateCDATASection NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateCDATASection Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateComment
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Comment;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateComment
  (JNIEnv * env, jobject jdoc, jstring jdata){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateComment()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateComment()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jdata)){
		JREX_LOGLN("CreateComment()--> **** jdata is NULL ****")
		return NULL;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateComment()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateCommentInternal(env, thisDoc, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_COMMENT, (void*)data, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateComment()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateComment()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("CreateComment()--> **** CreateComment NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CreateComment Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateDocumentFragment
 * Signature: ()Lorg/w3c/dom/DocumentFragment;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateDocumentFragment
  (JNIEnv * env, jobject jdoc){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateDocumentFragment()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateDocumentFragment()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateDocumentFragment()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateDocumentFragmentInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_DOC_FRAG, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateDocumentFragment()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateDocumentFragment()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("CreateDocumentFragment()--> **** CreateDocumentFragment NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CreateDocumentFragment Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateElement
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateElement
  (JNIEnv * env, jobject jdoc, jstring jtagName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateElement()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateElement()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jtagName)){
		JREX_LOGLN("CreateElement()--> **** jtagName is NULL ****")
		return NULL;
	}

	PRUnichar* tagName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtagName, tagName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateElement()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateElementInternal(env, thisDoc, tagName);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_ELE, (void*)tagName, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateElement()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateElement()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateElement()--> **** CreateElement DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateElement()--> **** CreateElement NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateElement Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateElementNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateElementNS
  (JNIEnv * env, jobject jdoc, jstring jnamespaceURI, jstring jqualifiedName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateElementNS()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateElementNS()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName)){
		JREX_LOGLN("CreateElementNS()--> **** jnamespaceURI/jqualifiedName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateElementNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateElementNSInternal(env, thisDoc, namespaceURI, qualifiedName);
	}else{
		JRexDocumentEventParam *param=new JRexDocumentEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=namespaceURI;
		param->data2=qualifiedName;

		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_ELENS, param, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateElementNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateElementNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateElementNS()--> **** CreateElementNS DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateElementNS()--> **** CreateElementNS NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateElementNS Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateEntityReference
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/EntityReference;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateEntityReference
  (JNIEnv * env, jobject jdoc, jstring jname){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateEntityReference()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateEntityReference()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jname)){
		JREX_LOGLN("CreateEntityReference()--> **** jname is NULL ****")
		return NULL;
	}

	PRUnichar* name=nsnull;
	JSTR_TO_NEW_PRUNI(env, jname, name);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateEntityReference()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateEntityReferenceInternal(env, thisDoc, name);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_ENTITY_REF, (void*)name, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateEntityReference()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateEntityReference()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateEntityReference()--> **** CreateEntityReference DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateEntityReference()--> **** CreateEntityReference NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateEntityReference Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateProcessingInstruction
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/ProcessingInstruction;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateProcessingInstruction
  (JNIEnv * env, jobject jdoc, jstring jtarget, jstring jdata){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateProcessingInstruction()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateProcessingInstruction()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	if (IS_NULL(jtarget) || IS_NULL(jdata)){
		JREX_LOGLN("CreateProcessingInstruction()--> **** jtarget/jdata is NULL ****")
		return NULL;
	}
	PRUnichar* target=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtarget, target);
	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateProcessingInstruction()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateProcessingInstructionInternal(env, thisDoc, target, data);
	}else{
		JRexDocumentEventParam *param=new JRexDocumentEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=target;
		param->data2=data;

		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_PROC_INST, param, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateProcessingInstruction()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateProcessingInstruction()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("CreateProcessingInstruction()--> **** CreateProcessingInstruction DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("CreateProcessingInstruction()--> **** CreateProcessingInstruction NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** CreateProcessingInstruction Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
 }

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    CreateTextNode
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Text;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_CreateTextNode
  (JNIEnv * env, jobject jdoc, jstring jdata){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("CreateTextNode()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "CreateTextNode()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jdata)){
		JREX_LOGLN("CreateTextNode()--> **** jdata is NULL ****")
		return NULL;
	}

	PRUnichar* data=nsnull;
	JSTR_TO_NEW_PRUNI(env, jdata, data);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("CreateTextNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_CreateTextNodeInternal(env, thisDoc, data);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_CREATE_TEXT_NODE, (void*)data, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("CreateTextNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("CreateTextNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("CreateTextNode()--> **** CreateTextNode NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** CreateTextNode Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDoctype
 * Signature: ()Lorg/w3c/dom/DocumentType;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDoctype
  (JNIEnv * env, jobject jdoc){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDoctype()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDoctype()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDoctype()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDoctypeInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_TYPE, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDoctype()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDoctype()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDoctype()--> **** GetDoctype NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDoctype Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentElement
 * Signature: ()Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentElement
  (JNIEnv * env, jobject jdoc){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDocumentElement()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDocumentElement()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocumentElement()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDocumentElementInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_ELE, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDocumentElement()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocumentElement()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocumentElement()--> **** GetDocumentElement NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocumentElement Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetElementById
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/Element;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetElementById
  (JNIEnv * env, jobject jdoc, jstring jeleID){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementById()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetElementById()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jeleID)){
		JREX_LOGLN("GetElementById()--> **** jeleID is NULL ****")
		return NULL;
	}

	PRUnichar* eleID=nsnull;
	JSTR_TO_NEW_PRUNI(env, jeleID, eleID);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementById()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetElementByIdInternal(env, thisDoc, eleID);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_ELE_BYID, (void*)eleID, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetElementById()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementById()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetElementById()--> **** GetElementById NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementById Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetElementsByTagName
 * Signature: (Ljava/lang/String;)Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetElementsByTagName
  (JNIEnv * env, jobject jdoc, jstring jtagName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementsByTagName()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetElementsByTagName()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jtagName)){
		JREX_LOGLN("GetElementsByTagName()--> **** jtagName is NULL ****")
		return NULL;
	}

	PRUnichar* tagName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jtagName, tagName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementsByTagName()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetElementsByTagNameInternal(env, thisDoc, tagName);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_ELES_BY_TAG, (void*)tagName, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetElementsByTagName()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementsByTagName()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetElementsByTagName()--> **** GetElementsByTagName NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementsByTagName Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;

}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetElementsByTagNameNS
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/NodeList;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetElementsByTagNameNS
  (JNIEnv * env, jobject jdoc, jstring jnamespaceURI, jstring jlocalName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetElementsByTagNameNS()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetElementsByTagNameNS()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jlocalName)){
		JREX_LOGLN("GetElementsByTagNameNS()--> **** jnamespaceURI/jlocalName is NULL ****")
		return NULL;
	}

	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* localName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jlocalName, localName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetElementsByTagNameNS()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetElementsByTagNameNSInternal(env, thisDoc, namespaceURI, localName);
	}else{
		JRexDocumentEventParam *param=new JRexDocumentEventParam;
		if (IS_NULL(param))return NULL;
		param->data1=namespaceURI;
		param->data2=localName;
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_ELES_BY_TAGNS, param, PR_TRUE, HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetElementsByTagNameNS()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetElementsByTagNameNS()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if (NS_FAILED(rv)) {
			JREX_LOGLN("GetElementsByTagNameNS()--> **** GetElementsByTagNameNS NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetElementsByTagNameNS Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetImplementation
 * Signature: ()Lorg/w3c/dom/DOMImplementation;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetImplementation
  (JNIEnv * env, jobject jdoc){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetImplementation()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetImplementation()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetImplementation()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetImplementationInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_IMPL, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetImplementation()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetImplementation()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetImplementation()--> **** GetImplementation NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetImplementation Failed ****",rv);
			return NULL;
		}
		return jobj;
	}

	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    ImportNode
 * Signature: (Lorg/w3c/dom/Node;Z)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_ImportNode
  (JNIEnv * env, jobject jdoc, jobject jimportedNode, jboolean jdeep){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ImportNode()--> **** thisDoc <"<<thisDoc<<"> jdeep <"<<jdeep<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "ImportNode()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMNode *importedNode=nsnull;
	if(jimportedNode)
		importedNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jimportedNode, JRexDOMGlobals::nodePeerID));
	if(IS_NULL(importedNode)){
		ThrowJRexException(env, "ImportNode()--> **** importedNode is NULL!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("ImportNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_ImportNodeInternal(env, thisDoc, importedNode, (jdeep==JNI_TRUE?PR_TRUE:PR_FALSE));
	}else{
		JRexImportNodeEventParam *param=new JRexImportNodeEventParam;
		if (IS_NULL(param))return NULL;
		param->node=importedNode;
		param->deep=(jdeep==JNI_TRUE?PR_TRUE:PR_FALSE);
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_IMPORT_NODE, param, PR_TRUE, HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("ImportNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("ImportNode()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("ImportNode()--> **** ImportNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("ImportNode()--> **** ImportNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** ImportNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentRange
 * Signature: (V)Lorg/w3c/dom/ranges/DocumentRange;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentRange
  (JNIEnv * env, jobject jdoc){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDocumentRange()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDocumentRange()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocumentRange()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDocumentRangeInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_RANGE, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDocumentRange()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocumentRange()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocumentRange()--> **** GetDocumentRange NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocumentRange Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentEvent
 * Signature: (V)Lorg/w3c/dom/events/GetDocumentEvent;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentEvent
  (JNIEnv * env, jobject jdoc){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDocumentEvent()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDocumentEvent()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocumentEvent()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDocumentEventInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_EVENT, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDocumentEvent()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocumentEvent()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocumentEvent()--> **** GetDocumentEvent NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocumentEvent Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentTraversal
 * Signature: (V)Lorg/w3c/dom/traversal/GetDocumentTraversal;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentTraversal
  (JNIEnv * env, jobject jdoc){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDocumentTraversal()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDocumentTraversal()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocumentTraversal()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDocumentTraversalInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_TRAV, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDocumentTraversal()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocumentTraversal()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocumentTraversal()--> **** GetDocumentTraversal NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocumentTraversal Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentView
 * Signature: (V)Lorg/w3c/dom/views/GetDocumentView;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentView
  (JNIEnv * env, jobject jdoc){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOMDocument* thisDoc=(nsIDOMDocument*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDocumentView()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDocumentView()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDocumentView()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDocumentViewInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_DOC_VIEW, nsnull, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDocumentView()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDocumentView()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDocumentView()--> **** GetDocumentView NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDocumentView Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetInputEncoding
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetInputEncoding
  (JNIEnv * env, jobject jdoc){
	GET_DOM_STRING_JNI(env , jdoc, 3Document, GetActualEncoding, JREX_GET_IN_ENCOD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetXmlEncoding
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetXmlEncoding
  (JNIEnv * env, jobject jdoc){
	GET_DOM_STRING_JNI(env , jdoc, 3Document, GetXmlEncoding, JREX_GET_XML_ENCOD, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetXmlStandalone
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetXmlStandalone
  (JNIEnv * env, jobject jdoc){
	GET_DOM_BOOL_JNI(env , jdoc, 3Document, GetXmlStandalone, JREX_GET_XML_STDALN, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    SetXmlStandalone
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_SetXmlStandalone
  (JNIEnv * env, jobject jdoc, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jdoc, jvalue, 3Document, SetXmlStandalone, JREX_SET_XML_STDALN, JRexDOMGlobals::nodePeerID, PR_TRUE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetXmlVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetXmlVersion
  (JNIEnv * env, jobject jdoc){
	GET_DOM_STRING_JNI(env , jdoc, 3Document, GetXmlVersion, JREX_GET_XML_VER, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    SetXmlVersion
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_SetXmlVersion
  (JNIEnv * env, jobject jdoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jdoc, jvalue, 3Document, SetXmlVersion, JREX_SET_XML_VER, JRexDOMGlobals::nodePeerID, PR_TRUE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetStrictErrorChecking
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetStrictErrorChecking
  (JNIEnv * env, jobject jdoc){
	GET_DOM_BOOL_JNI(env , jdoc, 3Document, GetStrictErrorChecking, JREX_GET_STRIC_ERROR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    SetStrictErrorChecking
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_SetStrictErrorChecking
  (JNIEnv * env, jobject jdoc, jboolean jvalue){
	SET_DOM_BOOL_JNI(env , jdoc, jvalue, 3Document, SetStrictErrorChecking, JREX_SET_STRIC_ERROR, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDocumentURI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDocumentURI
  (JNIEnv * env, jobject jdoc){
	GET_DOM_STRING_JNI(env , jdoc, 3Document, GetDocumentURI, JREX_GET_DOC_URI, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    SetDocumentURI
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_SetDocumentURI
  (JNIEnv * env, jobject jdoc, jstring jvalue){
	SET_DOM_STRING_JNI(env , jdoc, jvalue, 3Document, SetDocumentURI, JREX_SET_DOC_URI, JRexDOMGlobals::nodePeerID, PR_FALSE)
}


/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    AdoptNode
 * Signature: (Lorg/w3c/dom/Node;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_AdoptNode
  (JNIEnv * env, jobject jdoc, jobject jnodeObj){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Document* thisDoc=(nsIDOM3Document*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	nsIDOMNode* thisNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnodeObj, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("AdoptNode()--> **** thisDoc <"<<thisDoc<<"> thisNode <"<<thisNode<<"> ****")
	if(IS_NULL(thisNode) || IS_NULL(thisDoc)){
		ThrowJRexException(env, "AdoptNode()--> **** thisDoc/thisNode DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("AdoptNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_AdoptNodeInternal(env, thisDoc, thisNode);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_ADPT_NODE, thisNode, PR_TRUE,
						HandleJRex3DocumentEvent, DestroyJRex3DocumentEvent, (void**)&jrv);
		JREX_LOGLN("AdoptNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("AdoptNode()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("AdoptNode()--> **** AdoptNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("AdoptNode()--> **** AdoptNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** AdoptNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    GetDomConfig
 * Signature: ()Lorg/w3c/dom/DOMConfiguration;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_GetDomConfig
  (JNIEnv * env, jobject jdoc){
	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Document* thisDoc=(nsIDOM3Document*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("GetDomConfig()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "GetDomConfig()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("GetDomConfig()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_GetDomConfigInternal(env, thisDoc);
	}else{
		nsresult rv=ExecInEventQDOM(thisDoc, JREX_GET_CONFIG, nsnull, PR_TRUE,
						HandleJRex3DocumentEvent, DestroyJRex3DocumentEvent, (void**)&jrv);
		JREX_LOGLN("GetDomConfig()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("GetDomConfig()--> **** jrv<"<<jrv<<"> ****")
	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			JREX_LOGLN("GetDomConfig()--> **** GetDomConfig NON-DOM ERROR OCCURED !!!****")
			ThrowJRexException(env, "**** GetDomConfig Failed ****",rv);
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    NormalizeDocument
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_NormalizeDocument
  (JNIEnv * env, jobject jdoc){
	CALL_DOM_JNI(env , jdoc, 3Document, NormalizeDocument, JREX_NORM_DOC, JRexDOMGlobals::nodePeerID, PR_FALSE)
}

/*
 * Class:     org_mozilla_jrex_dom_JRexDocumentImpl
 * Method:    RenameNode
 * Signature: (Lorg/w3c/dom/Node;Ljava/lang/String;Ljava/lang/String;)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_dom_JRexDocumentImpl_RenameNode
  (JNIEnv * env, jobject jdoc, jobject jnode, jstring jnamespaceURI, jstring jqualifiedName){

	if(!JRexDOMGlobals::sIntialized)return NULL;
	JREX_TRY
	nsIDOM3Document* thisDoc=(nsIDOM3Document*)NS_INT32_TO_PTR(env->GetIntField(jdoc, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("RenameNode()--> **** thisDoc <"<<thisDoc<<"> ****")
	if(IS_NULL(thisDoc)){
		ThrowJRexException(env, "RenameNode()--> **** thisDoc DOES NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMNode *node=nsnull;
	if(jnode)
		node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	if(IS_NULL(node)){
		ThrowJRexException(env, "RenameNode()--> **** node is NULL!!! ****",0);
		return NULL;
	}
	if (IS_NULL(jnamespaceURI) || IS_NULL(jqualifiedName)){
		JREX_LOGLN("RenameNode()--> **** jnamespaceURI/jqualifiedName is NULL ****")
		return NULL;
	}
	PRUnichar* namespaceURI=nsnull;
	JSTR_TO_NEW_PRUNI(env, jnamespaceURI, namespaceURI);
	PRUnichar* qualifiedName=nsnull;
	JSTR_TO_NEW_PRUNI(env, jqualifiedName, qualifiedName);

	JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
	if(IS_EQT){
		JREX_LOGLN("RenameNode()--> **** IN EVT Q THREAD ****")
		jrv=JRexDocumentImpl_RenameNodeInternal(env, thisDoc, node, namespaceURI, qualifiedName);
	}else{
		JRexRenameNodeEventParam *param=new JRexRenameNodeEventParam;
		if (IS_NULL(param))return NULL;
		param->node=node;
		param->data1=namespaceURI;
		param->data2=qualifiedName;

		nsresult rv=ExecInEventQDOM(thisDoc, JREX_RNM_NODE, param, PR_TRUE,
						HandleJRexDocumentEvent, DestroyJRexDocumentEvent, (void**)&jrv);
		JREX_LOGLN("RenameNode()--> **** ExecInEventQDOM rv<"<<rv<<"> ****")
	}
	JREX_LOGLN("RenameNode()--> **** jrv<"<<jrv<<"> ****")

	if(NOT_NULL(jrv)){
		nsresult rv=jrv->rv;
		jobject jobj=jrv->jobj;
		delete jrv;
		if(NS_FAILED(rv)){
			if (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM){
				JREX_LOGLN("RenameNode()--> **** RenameNode DOM ERROR OCCURED !!!****")
				JRexDOMGlobals::ThrowDOMException(env, rv);
			}else{
				JREX_LOGLN("RenameNode()--> **** RenameNode NON-DOM ERROR OCCURED !!!****")
				ThrowJRexException(env, "**** RenameNode Failed ****",rv);
			}
			return NULL;
		}
		return jobj;
	}
	JREX_CATCH(env)
	return NULL;
}


void* PR_CALLBACK HandleJRexDocumentEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRexDocumentEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOMDocument> doc(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_CREATE_ATTRB:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_ATTRB EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateAttributeInternal(nsnull, doc.get(), name);
		}
		case JREX_CREATE_ATTRBNS:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_ATTRBNS EVENT!!!****")
			JRexDocumentEventParam* parm = NS_REINTERPRET_CAST(JRexDocumentEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_CreateAttributeNSInternal(nsnull, doc.get(), parm->data1, parm->data2);
		}
		case JREX_CREATE_CDATA:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_CDATA EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateCDATASectionInternal(nsnull, doc.get(), data);
		}
		case JREX_CREATE_COMMENT:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_COMMENT EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateCommentInternal(nsnull, doc.get(), data);

		}
		case JREX_CREATE_DOC_FRAG:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_DOC_FRAG EVENT!!!****")
			return (void*)JRexDocumentImpl_CreateDocumentFragmentInternal(nsnull, doc.get());
		}
		case JREX_CREATE_ELE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_ELE EVENT!!!****")
			PRUnichar* tagName = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateElementInternal(nsnull, doc.get(), tagName);
		}
		case JREX_CREATE_ELENS:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_ELENS EVENT!!!****")
			JRexDocumentEventParam* parm = NS_REINTERPRET_CAST(JRexDocumentEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_CreateElementNSInternal(nsnull, doc.get(), parm->data1, parm->data2);
		}
		case JREX_CREATE_ENTITY_REF:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_ENTITY_REF EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateEntityReferenceInternal(nsnull, doc.get(), name);
		}
		case JREX_CREATE_PROC_INST:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_PROC_INST EVENT!!!****")
			JRexDocumentEventParam* parm = NS_REINTERPRET_CAST(JRexDocumentEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_CreateProcessingInstructionInternal(nsnull, doc.get(), parm->data1, parm->data2);
		}
		case JREX_CREATE_TEXT_NODE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_CREATE_TEXT_NODE EVENT!!!****")
			PRUnichar* data = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_CreateTextNodeInternal(nsnull, doc.get(), data);
		}
		case JREX_GET_DOC_TYPE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_TYPE EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDoctypeInternal(nsnull, doc.get());
		}
		case JREX_GET_DOC_ELE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_ELE EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDocumentElementInternal(nsnull, doc.get());
		}
		case JREX_GET_ELE_BYID:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_ELE_BYID EVENT!!!****")
			PRUnichar* eleID = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_GetElementByIdInternal(nsnull, doc.get(), eleID);
		}
		case JREX_GET_ELES_BY_TAG:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_ELES_BY_TAG EVENT!!!****")
			PRUnichar* name = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			return (void*)JRexDocumentImpl_GetElementsByTagNameInternal(nsnull, doc.get(), name);
		}
		case JREX_GET_ELES_BY_TAGNS:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_ELES_BY_TAGNS EVENT!!!****")
			JRexDocumentEventParam* parm = NS_REINTERPRET_CAST(JRexDocumentEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_GetElementsByTagNameNSInternal(nsnull, doc.get(), parm->data1, parm->data2);
		}
		case JREX_GET_IMPL:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_IMPL EVENT!!!****")
			return (void*)JRexDocumentImpl_GetImplementationInternal(nsnull, doc.get());
		}
		case JREX_IMPORT_NODE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_IMPORT_NODE EVENT!!!****")
			JRexImportNodeEventParam* parm = NS_REINTERPRET_CAST(JRexImportNodeEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_ImportNodeInternal(nsnull, doc.get(), parm->node, parm->deep);
		}
		case JREX_GET_DOC_RANGE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_RANGE EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDocumentRangeInternal(nsnull, doc.get());
		}
		case JREX_GET_DOC_EVENT:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_EVENT EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDocumentEventInternal(nsnull, doc.get());
		}
		case JREX_GET_DOC_TRAV:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_TRAV EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDocumentTraversalInternal(nsnull, doc.get());
		}
		case JREX_GET_DOC_VIEW:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_GET_DOC_VIEW EVENT!!!****")
			return (void*)JRexDocumentImpl_GetDocumentViewInternal(nsnull, doc.get());
		}
		default:
		{
			JREX_LOGLN("HandleJRexDocumentEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRexDocumentEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRexDocumentEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRexDocumentEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData){
		if(event->eventType==JREX_CREATE_ATTRBNS || event->eventType==JREX_CREATE_ELENS
			|| event->eventType==JREX_GET_ELES_BY_TAGNS){
			JRexDocumentEventParam* param = NS_REINTERPRET_CAST(JRexDocumentEventParam*, event->eventData);
			delete param;
		}else
		if(event->eventType==JREX_IMPORT_NODE){
			JRexImportNodeEventParam* param = NS_REINTERPRET_CAST(JRexImportNodeEventParam*, event->eventData);
			delete param;
		}
	}
	delete event;
}


void* PR_CALLBACK HandleJRex3DocumentEvent(PLEvent* aEvent){
	if(!JRexDOMGlobals::sIntialized)return nsnull;
	JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
	nsresult rv=NS_OK;
	JREX_LOGLN("HandleJRex3DocumentEvent()--> **** target <"<<event->target<<"> ****")
	nsCOMPtr<nsIDOM3Document> doc(do_QueryInterface(NS_REINTERPRET_CAST(nsISupports*, event->target)));
	switch(event->eventType){
		case JREX_GET_IN_ENCOD:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_IN_ENCOD EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, doc.get(), GetActualEncoding, jrv)
			return (void*)jrv;
		}
		case JREX_GET_XML_ENCOD:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_XML_ENCOD EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, doc.get(), GetXmlEncoding, jrv)
			return (void*)jrv;
		}
		case JREX_GET_XML_STDALN:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_XML_STDALN EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(nsnull, doc.get(), GetXmlStandalone, jrv)
			return (void*)jrv;
		}
		case JREX_SET_XML_STDALN:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_SET_XML_STDALN EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, doc.get(), SetXmlStandalone, jrv)
			return (void*)jrv;
		}
		case JREX_GET_XML_VER:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_XML_VER EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, doc.get(), GetXmlVersion, jrv)
			return (void*)jrv;
		}
		case JREX_SET_XML_VER:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_XML_VER EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, doc.get(), SetXmlVersion, jrv)
			return (void*)jrv;
		}
		case JREX_GET_STRIC_ERROR:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_STRIC_ERROR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_BOOL_EQT(nsnull, doc.get(), GetStrictErrorChecking, jrv)
			return (void*)jrv;
		}
		case JREX_SET_STRIC_ERROR:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_SET_STRIC_ERROR EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRBool value = NS_REINTERPRET_CAST(PRBool, event->eventData);
			SET_DOM_BOOL_EQT(value, doc.get(), SetStrictErrorChecking, jrv)
			return (void*)jrv;
		}
		case JREX_GET_DOC_URI:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_DOC_URI EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			GET_DOM_STRING_EQT(nsnull, doc.get(), GetDocumentURI, jrv)
			return (void*)jrv;
		}
		case JREX_SET_DOC_URI:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_SET_DOC_URI EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			PRUnichar* value = NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
			SET_DOM_STRING_EQT(value, doc.get(), SetDocumentURI, jrv)
			return (void*)jrv;
		}
		case JREX_ADPT_NODE:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_ADPT_NODE EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsIDOMNode* value = NS_REINTERPRET_CAST(nsIDOMNode*, event->eventData);
			return (void*)JRexDocumentImpl_AdoptNodeInternal(nsnull, doc.get(), value);
		}
		case JREX_GET_CONFIG:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_GET_CONFIG EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			return (void*)JRexDocumentImpl_GetDomConfigInternal(nsnull, doc.get());
		}
		case JREX_NORM_DOC:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent JREX_NORM_DOC EVENT!!!****")
			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			CALL_DOM_EQT(doc.get(), NormalizeDocument, jrv)
			return (void*)jrv;
		}
		case JREX_RNM_NODE:
		{
			JREX_LOGLN("HandleJRexDocumentEvent JREX_RNM_NODE EVENT!!!****")
			JRexRenameNodeEventParam* parm = NS_REINTERPRET_CAST(JRexRenameNodeEventParam*, event->eventData);
			return (void*)JRexDocumentImpl_RenameNodeInternal(nsnull, doc.get(), parm->node, parm->data1, parm->data2);
		}
		default:
		{
			JREX_LOGLN("HandleJRex3DocumentEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
		}
	}
	JREX_LOGLN("HandleJRex3DocumentEvent()--> **** returning rv<"<<rv<<"> ****")
	return (void*)rv;
}

void PR_CALLBACK DestroyJRex3DocumentEvent(PLEvent* aEvent){
	JRexBasicEvent* event = NS_REINTERPRET_CAST( JRexBasicEvent*, aEvent);
	JREX_LOGLN("DestroyJRex3DocumentEvent()--> **** target <"<<event->target<<"> ****")
	if(event->eventData
		&& event->eventType==JREX_RNM_NODE){
		JRexRenameNodeEventParam* param = NS_REINTERPRET_CAST(JRexRenameNodeEventParam*, event->eventData);
		delete param;
	}
	delete event;
}
