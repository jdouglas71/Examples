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

	#include "JRexDOMGlobals.h"

	jclass 		JRexDOMGlobals::attrCls=0;
	jclass 		JRexDOMGlobals::cDATASectionCls=0;
	jclass 		JRexDOMGlobals::commentCls=0;
	jclass 		JRexDOMGlobals::documentFragmentCls=0;
	jclass 		JRexDOMGlobals::documentCls=0;
	jclass 		JRexDOMGlobals::documentTypeCls=0;
	jclass 		JRexDOMGlobals::domImplCls=0;
	jclass 		JRexDOMGlobals::elementCls=0;
	jclass 		JRexDOMGlobals::entityCls=0;
	jclass 		JRexDOMGlobals::entityRefCls=0;
	jclass 		JRexDOMGlobals::nodeMapCls=0;
	jclass 		JRexDOMGlobals::nodeCls=0;
	jclass 		JRexDOMGlobals::nodeListCls=0;
	jclass 		JRexDOMGlobals::notationCls=0;
	jclass 		JRexDOMGlobals::processingInstCls=0;
	jclass 		JRexDOMGlobals::textCls=0;
	jclass 		JRexDOMGlobals::domExpCls=0;
	jclass 		JRexDOMGlobals::rangeExpCls=0;
	jclass  	JRexDOMGlobals::rangeCls=0;
	jclass  	JRexDOMGlobals::docRangeCls=0;
	jclass  	JRexDOMGlobals::evtExpCls=0;
	jclass  	JRexDOMGlobals::evtTargetCls=0;
	jclass  	JRexDOMGlobals::docEventCls=0;
	jclass  	JRexDOMGlobals::domEventCls=0;
	jclass  	JRexDOMGlobals::domUIEventCls=0;
	jclass  	JRexDOMGlobals::domMouseEventCls=0;
	jclass  	JRexDOMGlobals::domMutEventCls=0;
	jclass  	JRexDOMGlobals::abstractViewCls=0;
	jclass  	JRexDOMGlobals::documentViewCls=0;
	jclass  	JRexDOMGlobals::docTravCls=0;
	jclass  	JRexDOMGlobals::nodeItrCls=0;
	jclass  	JRexDOMGlobals::treeWkrCls=0;
	jclass  	JRexDOMGlobals::domCfgCls=0;
	jclass  	JRexDOMGlobals::domStrListCls=0;

	//HTML2 stuff
#if defined(JREX_DOM_HTML2)
	jclass 		JRexDOMGlobals::anchorEleCls=0;
	jclass 		JRexDOMGlobals::appEleCls=0;
	jclass 		JRexDOMGlobals::areaEleCls=0;
	jclass 		JRexDOMGlobals::baseEleCls=0;
	jclass 		JRexDOMGlobals::baseFontEleCls=0;
	jclass 		JRexDOMGlobals::bodyEleCls=0;
	jclass 		JRexDOMGlobals::breEleCls=0;
	jclass 		JRexDOMGlobals::butnEleCls=0;
	jclass 		JRexDOMGlobals::colctEleCls=0;
	jclass 		JRexDOMGlobals::dirEleCls=0;
	jclass 		JRexDOMGlobals::divEleCls=0;
	jclass 		JRexDOMGlobals::dListEleCls=0;
	jclass 		JRexDOMGlobals::docEleCls=0;
	jclass 		JRexDOMGlobals::fieldSetEleCls=0;
	jclass 		JRexDOMGlobals::fontEleCls=0;
	jclass 		JRexDOMGlobals::formEleCls=0;
	jclass 		JRexDOMGlobals::frameEleCls=0;
	jclass 		JRexDOMGlobals::frameSetEleCls=0;
	jclass 		JRexDOMGlobals::headEleCls=0;
	jclass 		JRexDOMGlobals::headingEleCls=0;
	jclass 		JRexDOMGlobals::hrEleCls=0;
	jclass 		JRexDOMGlobals::htmlHTMLEleCls=0;
	jclass 		JRexDOMGlobals::iframeEleCls=0;
	jclass 		JRexDOMGlobals::imageEleCls=0;
	jclass 		JRexDOMGlobals::inputEleCls=0;
	jclass 		JRexDOMGlobals::isIndexEleCls=0;
	jclass 		JRexDOMGlobals::labelEleCls=0;
	jclass 		JRexDOMGlobals::legendEleCls=0;
	jclass 		JRexDOMGlobals::liEleCls=0;
	jclass 		JRexDOMGlobals::linkEleCls=0;
	jclass 		JRexDOMGlobals::mapEleCls=0;
	jclass 		JRexDOMGlobals::menuEleCls=0;
	jclass 		JRexDOMGlobals::metaEleCls=0;
	jclass 		JRexDOMGlobals::modEleCls=0;
	jclass 		JRexDOMGlobals::objEleCls=0;
	jclass 		JRexDOMGlobals::oListEleCls=0;
	jclass 		JRexDOMGlobals::optGrpEleCls=0;
	jclass 		JRexDOMGlobals::optEleCls=0;
	jclass 		JRexDOMGlobals::optColEleCls=0;
	jclass 		JRexDOMGlobals::paraEleCls=0;
	jclass 		JRexDOMGlobals::paramEleCls=0;
	jclass 		JRexDOMGlobals::preEleCls=0;
	jclass 		JRexDOMGlobals::quoteEleCls=0;
	jclass 		JRexDOMGlobals::scriptEleCls=0;
	jclass 		JRexDOMGlobals::selEleCls=0;
	jclass 		JRexDOMGlobals::styleEleCls=0;
	jclass 		JRexDOMGlobals::tableCapEleCls=0;
	jclass 		JRexDOMGlobals::tableCellEleCls=0;
	jclass 		JRexDOMGlobals::tableColEleCls=0;
	jclass 		JRexDOMGlobals::tableEleCls=0;
	jclass 		JRexDOMGlobals::tableRowEleCls=0;
	jclass 		JRexDOMGlobals::tableSelEleCls=0;
	jclass 		JRexDOMGlobals::textAreaEleCls=0;
	jclass 		JRexDOMGlobals::titleEleCls=0;
	jclass 		JRexDOMGlobals::uListEleCls=0;
	jclass 		JRexDOMGlobals::htmlEleCls=0;
#endif //JREX_DOM_HTML2
	jmethodID 	JRexDOMGlobals::nodeCID=0;
	jmethodID 	JRexDOMGlobals::nodeMapCID=0;
	jmethodID 	JRexDOMGlobals::nodeListCID=0;
	jmethodID 	JRexDOMGlobals::domImplCID=0;
	jmethodID 	JRexDOMGlobals::domExpCID=0;
	jmethodID 	JRexDOMGlobals::rangeExpCID=0;
	jmethodID 	JRexDOMGlobals::rangeCID=0;
	jmethodID 	JRexDOMGlobals::docRangeCID=0;
	jmethodID 	JRexDOMGlobals::evtTargetCID=0;
	jmethodID 	JRexDOMGlobals::evtExpCID=0;
	jmethodID 	JRexDOMGlobals::docEventCID=0;
	jmethodID 	JRexDOMGlobals::docTravCID=0;
	jmethodID 	JRexDOMGlobals::domEventCID=0;
	jmethodID 	JRexDOMGlobals::evtListnHndlEvtMID=0;
	jmethodID 	JRexDOMGlobals::usrDataHndlMID=0;
	jmethodID 	JRexDOMGlobals::abstractViewCID=0;
	jmethodID 	JRexDOMGlobals::documentViewCID=0;
	jmethodID 	JRexDOMGlobals::nodeItrCID=0;
	jmethodID 	JRexDOMGlobals::treeWkrCID=0;
	jmethodID 	JRexDOMGlobals::domCfgCID=0;
	jmethodID 	JRexDOMGlobals::domStrListCID=0;
	jmethodID 	JRexDOMGlobals::nodeFilterAcptMID=0;
#if defined(JREX_DOM_HTML2)
	jmethodID 	JRexDOMGlobals::colctEleCID=0;
	jmethodID 	JRexDOMGlobals::colOptctEleCID=0;
#endif //JREX_DOM_HTML2
	jfieldID 	JRexDOMGlobals::nodePeerID=0;
	jfieldID 	JRexDOMGlobals::nodeListPeerID=0;
	jfieldID 	JRexDOMGlobals::domImplPeerID=0;
	jfieldID 	JRexDOMGlobals::nodeMapPeerID=0;
	jfieldID 	JRexDOMGlobals::rangePeerID=0;
	jfieldID 	JRexDOMGlobals::docRangePeerID=0;
	jfieldID 	JRexDOMGlobals::evtTargetPeerID=0;
	jfieldID 	JRexDOMGlobals::docEventPeerID=0;
	jfieldID 	JRexDOMGlobals::domEventPeerID=0;
	jfieldID 	JRexDOMGlobals::abstractViewPeerID=0;
	jfieldID 	JRexDOMGlobals::documentViewPeerID=0;
	jfieldID 	JRexDOMGlobals::docTravPeerID=0;
	jfieldID 	JRexDOMGlobals::nodeItrPeerID=0;
	jfieldID 	JRexDOMGlobals::treeWkrPeerID=0;
	jfieldID 	JRexDOMGlobals::domCfgPeerID=0;
	jfieldID 	JRexDOMGlobals::domStrListPeerID=0;
#if defined(JREX_DOM_HTML2)
	jfieldID 	JRexDOMGlobals::colctElePeerID=0;
	jfieldID 	JRexDOMGlobals::colOptctElePeerID=0;
#endif //JREX_DOM_HTML2

	PRBool		JRexDOMGlobals::sIntialized=PR_FALSE;

	const char* const JRexDOMGlobals::DOM_EXP_CODE_MESSAGE[]={
		"UNKNOWN DOM Error code '0'",
		"Index or size is negative, or greater than the allowed value.",
		"Specified range of text does not fit into a DOMString.",
		"Node is inserted somewhere it doesn't belong.",
		"Node is used in a different document than the one that created it(that doesn't support it).",
		"Invalid or illegal character is specified, such as in a name.",
		"Data specified for a node which does not support data.",
		"Attempt is made to modify an object where modifications are not allowed.",
		"Aempt is made to reference a node in a context where it does not exist.",
		"Implementation does not support the requested type of object or operation.",
		"Attempt is made to add an attribute that is already in use elsewhere.",
		"Attempt is made to use an object that is not, or is no longer usable.",
		"Invalid or illegal string is specified.",
		"Attempt is made to modify the type of the underlying object.",
		"Attempt is made to create or change an object in a way which is incorrect with regard to namespaces.",
		"Parameter or an operation is not supported by the underlying object."
	};

	const char* const JRexDOMGlobals::RANGE_EXP_CODE_MESSAGE[]={
		"UNKNOWN Range Error code '0'",
		"Boundary-points of a Range do not meet specific requirements.",
		"Invalid Node type Or Invalid Ancestor Node type"
	};

	const char* const JRexDOMGlobals::EVENT_EXP_CODE_MESSAGE="UNKNOWN Event type specified";

	#define INIT_DOM_CLASS(target, cls)	tempCls = env->FindClass(cls); \
										if(tempCls){ \
											target = (jclass) env->NewGlobalRef(tempCls); \
											env->DeleteLocalRef(tempCls); \
										} \
										JREX_LOGLN("**** Intialize() "<<#target<<"<"<<target<<"> ****") \
										if (env->ExceptionCheck())goto FAILED;

	#define UNINIT_DOM_CLASS(target) 	JREX_LOGLN("**** UnIntialize() "<<#target<<"<"<<target<<"> ****") \
										if(target)env->DeleteGlobalRef(target); \
										target=NULL; \
										JNI_EXP_DESC_CLR("*** UnIntialize() Deleting Class Failed!!!! ***")


	nsDataHashtable<nsISupportsHashKey, jobject> *JRexDOMGlobals::nodeJPair=nsnull;

	struct JRexDOMGlobalEventParam{
		JRexDOMGlobalEventParam(): node(nsnull), addRef(PR_TRUE){}
		nsIDOMNode *node;
		PRBool addRef;
	};


	jboolean JRexDOMGlobals::Intialize(JNIEnv* env){
		JREX_LOGLN("**** Intialize() env<"<<env<<"> ****")

		if(JRexDOMGlobals::sIntialized){
			JREX_LOGLN("**** Intialize() Already Intialized ****")
			return JNI_TRUE;
		}

		jclass tempCls	= NULL;
		INIT_DOM_CLASS(attrCls, "org/mozilla/jrex/dom/JRexAttrImpl")
		INIT_DOM_CLASS(cDATASectionCls, "org/mozilla/jrex/dom/JRexCDATASectionImpl")
		INIT_DOM_CLASS(commentCls, "org/mozilla/jrex/dom/JRexCommentImpl")
		INIT_DOM_CLASS(documentFragmentCls, "org/mozilla/jrex/dom/JRexDocumentFragmentImpl")
		INIT_DOM_CLASS(documentCls, "org/mozilla/jrex/dom/JRexDocumentImpl")
		INIT_DOM_CLASS(documentTypeCls, "org/mozilla/jrex/dom/JRexDocumentTypeImpl")
		INIT_DOM_CLASS(domImplCls, "org/mozilla/jrex/dom/JRexDOMImplementationImpl")
		INIT_DOM_CLASS(elementCls, "org/mozilla/jrex/dom/JRexElementImpl")
		INIT_DOM_CLASS(entityCls, "org/mozilla/jrex/dom/JRexEntityImpl")
		INIT_DOM_CLASS(entityRefCls, "org/mozilla/jrex/dom/JRexEntityReferenceImpl")
		INIT_DOM_CLASS(nodeMapCls, "org/mozilla/jrex/dom/JRexNamedNodeMapImpl")
		INIT_DOM_CLASS(nodeCls, "org/mozilla/jrex/dom/JRexNodeImpl")
		INIT_DOM_CLASS(nodeListCls, "org/mozilla/jrex/dom/JRexNodeListImpl")
		INIT_DOM_CLASS(notationCls, "org/mozilla/jrex/dom/JRexNotationImpl")
		INIT_DOM_CLASS(processingInstCls, "org/mozilla/jrex/dom/JRexProcessingInstructionImpl")
		INIT_DOM_CLASS(textCls, "org/mozilla/jrex/dom/JRexTextImpl")
		INIT_DOM_CLASS(rangeCls, "org/mozilla/jrex/dom/ranges/JRexDOMRangeImpl")
		INIT_DOM_CLASS(docRangeCls, "org/mozilla/jrex/dom/ranges/JRexDocumentRangeImpl")
		INIT_DOM_CLASS(evtTargetCls, "org/mozilla/jrex/dom/events/JRexEventTargetImpl")
		INIT_DOM_CLASS(docEventCls, "org/mozilla/jrex/dom/events/JRexDocumentEventImpl")
		INIT_DOM_CLASS(domEventCls, "org/mozilla/jrex/dom/events/JRexEventImpl")
		INIT_DOM_CLASS(domUIEventCls, "org/mozilla/jrex/dom/events/JRexUIEventImpl")
		INIT_DOM_CLASS(domMouseEventCls, "org/mozilla/jrex/dom/events/JRexMouseEventImpl")
		INIT_DOM_CLASS(domMutEventCls, "org/mozilla/jrex/dom/events/JRexMutationEventImpl")
		INIT_DOM_CLASS(abstractViewCls, "org/mozilla/jrex/dom/views/JRexAbstractViewImpl")
		INIT_DOM_CLASS(documentViewCls, "org/mozilla/jrex/dom/views/JRexDocumentViewImpl")
		INIT_DOM_CLASS(docTravCls, "org/mozilla/jrex/dom/traversal/JRexDocumentTraversalImpl")
		INIT_DOM_CLASS(nodeItrCls, "org/mozilla/jrex/dom/traversal/JRexNodeIteratorImpl")
		INIT_DOM_CLASS(treeWkrCls, "org/mozilla/jrex/dom/traversal/JRexTreeWalkerImpl")
		INIT_DOM_CLASS(domCfgCls, "org/mozilla/jrex/dom/JRexDOMConfigurationImpl")
		INIT_DOM_CLASS(domStrListCls, "org/mozilla/jrex/dom/JRexDOMStringListImpl")

		INIT_DOM_CLASS(domExpCls, "org/w3c/dom/DOMException")
		INIT_DOM_CLASS(rangeExpCls, "org/w3c/dom/ranges/RangeException")
		INIT_DOM_CLASS(evtExpCls, "org/w3c/dom/events/EventException")

		domImplPeerID= env->GetFieldID(domImplCls, "peerDOMImpl", "I");
		domImplCID = env->GetMethodID(domImplCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() domImplPeerID<"<<domImplPeerID<<"> domImplCID<"<<domImplCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		nodeMapPeerID = env->GetFieldID(nodeMapCls, "peerNodeMap", "I");
		nodeMapCID = env->GetMethodID(nodeMapCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() nodeMapPeerID<"<<nodeMapPeerID<<"> nodeMapCID<"<<nodeMapCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		nodePeerID = env->GetFieldID(nodeCls, "peerNode", "I");
		nodeCID = env->GetMethodID(nodeCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() nodePeerID<"<<nodePeerID<<"> nodeCID<"<<nodeCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		nodeListPeerID = env->GetFieldID(nodeListCls, "peerNodeList", "I");
		nodeListCID = env->GetMethodID(nodeListCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() nodeListPeerID<"<<nodeListPeerID<<"> nodeListCID<"<<nodeListCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		rangePeerID = env->GetFieldID(rangeCls, "peerRange", "I");
		rangeCID = env->GetMethodID(rangeCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() rangePeerID<"<<rangePeerID<<"> rangeCID<"<<rangeCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		docRangePeerID = env->GetFieldID(docRangeCls, "peerDocRange", "I");
		docRangeCID = env->GetMethodID(docRangeCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() docRangePeerID<"<<docRangePeerID<<"> docRangeCID<"<<docRangeCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		evtTargetPeerID = env->GetFieldID(evtTargetCls, "peerEvtTarget", "I");
		evtTargetCID = env->GetMethodID(evtTargetCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() evtTargetPeerID<"<<evtTargetPeerID<<"> evtTargetCID<"<<evtTargetCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		docEventPeerID = env->GetFieldID(docEventCls, "peerDocEvent", "I");
		docEventCID = env->GetMethodID(docEventCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() docEventPeerID<"<<docEventPeerID<<"> docEventCID<"<<docEventCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		docTravPeerID = env->GetFieldID(docTravCls, "peerDocTrav", "I");
		docTravCID = env->GetMethodID(docTravCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() docTravPeerID<"<<docTravPeerID<<"> docTravCID<"<<docTravCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		nodeItrPeerID = env->GetFieldID(nodeItrCls, "peerNodeItr", "I");
		nodeItrCID = env->GetMethodID(nodeItrCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() nodeItrPeerID<"<<nodeItrPeerID<<"> nodeItrCID<"<<nodeItrCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		treeWkrPeerID = env->GetFieldID(treeWkrCls, "peerTreeWkr", "I");
		treeWkrCID = env->GetMethodID(treeWkrCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() treeWkrPeerID<"<<treeWkrPeerID<<"> treeWkrCID<"<<treeWkrCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		domCfgPeerID = env->GetFieldID(domCfgCls, "peerDomCfg", "I");
		domCfgCID = env->GetMethodID(domCfgCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() domCfgPeerID<"<<domCfgPeerID<<"> domCfgCID<"<<domCfgCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		domStrListPeerID = env->GetFieldID(domStrListCls, "peerDomStrList", "I");
		domStrListCID = env->GetMethodID(domStrListCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() domStrListPeerID<"<<domStrListPeerID<<"> domStrListCID<"<<domStrListCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		domEventPeerID = env->GetFieldID(domEventCls, "peerEvent", "I");
		domEventCID = env->GetMethodID(domEventCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() domEventPeerID<"<<domEventPeerID<<"> domEventCID<"<<domEventCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		abstractViewPeerID = env->GetFieldID(abstractViewCls, "peerAbstractView", "I");
		abstractViewCID = env->GetMethodID(abstractViewCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() abstractViewPeerID<"<<abstractViewPeerID<<"> abstractViewCID<"<<abstractViewCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		documentViewPeerID = env->GetFieldID(documentViewCls, "peerDocView", "I");
		documentViewCID = env->GetMethodID(documentViewCls, "<init>", "()V");
		JREX_LOGLN("**** Intialize() documentViewPeerID<"<<documentViewPeerID<<"> documentViewCID<"<<documentViewCID<<"> ****")
		if (env->ExceptionCheck())goto FAILED;

		domExpCID = env->GetMethodID(domExpCls, "<init>", "(SLjava/lang/String;)V");
		if (env->ExceptionCheck())goto FAILED;
		JREX_LOGLN("**** Intialize() domExpCID<"<<domExpCID<<"> ****")

		rangeExpCID = env->GetMethodID(rangeExpCls, "<init>", "(SLjava/lang/String;)V");
		if (env->ExceptionCheck())goto FAILED;
		JREX_LOGLN("**** Intialize() rangeExpCID<"<<rangeExpCID<<"> ****")

		evtExpCID = env->GetMethodID(evtExpCls, "<init>", "(SLjava/lang/String;)V");
		if (env->ExceptionCheck())goto FAILED;
		JREX_LOGLN("**** Intialize() evtExpCID<"<<evtExpCID<<"> ****")

		tempCls = env->FindClass("org/w3c/dom/events/EventListener");
		if(tempCls){
			evtListnHndlEvtMID = env->GetMethodID(tempCls, "handleEvent", "(Lorg/w3c/dom/events/Event;)V");
			JREX_LOGLN("**** Intialize() evtListnHndlEvtMID<"<<evtListnHndlEvtMID<<"> ****")
			env->DeleteLocalRef(tempCls);
		}
		if (env->ExceptionCheck())goto FAILED;

		tempCls = env->FindClass("org/w3c/dom/UserDataHandler");
		if(tempCls){
			usrDataHndlMID = env->GetMethodID(tempCls, "handle", "(SLjava/lang/String;Ljava/lang/Object;Lorg/w3c/dom/Node;Lorg/w3c/dom/Node;)V");
			JREX_LOGLN("**** Intialize() usrDataHndlMID<"<<usrDataHndlMID<<"> ****")
			env->DeleteLocalRef(tempCls);
		}
		if (env->ExceptionCheck())goto FAILED;

		tempCls = env->FindClass("org/w3c/dom/traversal/NodeFilter");
		if(tempCls){
			nodeFilterAcptMID = env->GetMethodID(tempCls, "acceptNode", "(Lorg/w3c/dom/Node;)S");
			JREX_LOGLN("**** Intialize() nodeFilterAcptMID<"<<nodeFilterAcptMID<<"> ****")
			env->DeleteLocalRef(tempCls);
		}
		if (env->ExceptionCheck())goto FAILED;

#if defined(JREX_DOM_HTML2)
		//HTML2 stuff
		INIT_DOM_CLASS(anchorEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLAnchorElementImpl")
		INIT_DOM_CLASS(appEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLAnchorElementImpl")
		INIT_DOM_CLASS(areaEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLAreaElementImpl")
		INIT_DOM_CLASS(baseEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLBaseElementImpl")
		INIT_DOM_CLASS(baseFontEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLBaseFontElementImpl")
		INIT_DOM_CLASS(bodyEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLBodyElementImpl")
		INIT_DOM_CLASS(breEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLBRElementImpl")
		INIT_DOM_CLASS(butnEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLButtonElementImpl")
		INIT_DOM_CLASS(colctEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLCollectionImpl")
		INIT_DOM_CLASS(dirEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLDirectoryElementImpl")
		INIT_DOM_CLASS(divEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLDivElementImpl")
		INIT_DOM_CLASS(dListEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLDListElementImpl")
		INIT_DOM_CLASS(docEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLDocumentImpl")
		INIT_DOM_CLASS(fieldSetEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLFieldSetElementImpl")
		INIT_DOM_CLASS(fontEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLFontElementImpl")
		INIT_DOM_CLASS(formEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLFormElementImpl")
		INIT_DOM_CLASS(frameEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLFrameElementImpl")
		INIT_DOM_CLASS(frameSetEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLFrameSetElementImpl")
		INIT_DOM_CLASS(headEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLHeadElementImpl")
		INIT_DOM_CLASS(headingEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLHeadingElementImpl")
		INIT_DOM_CLASS(hrEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLHRElementImpl")
		INIT_DOM_CLASS(htmlHTMLEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLHtmlElementImpl")
		INIT_DOM_CLASS(iframeEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLIFrameElementImpl")
		INIT_DOM_CLASS(imageEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLImageElementImpl")
		INIT_DOM_CLASS(inputEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLInputElementImpl")
		INIT_DOM_CLASS(isIndexEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLIsIndexElementImpl")
		INIT_DOM_CLASS(labelEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLLabelElementImpl")
		INIT_DOM_CLASS(legendEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLLegendElementImpl")
		INIT_DOM_CLASS(liEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLLIElementImpl")
		INIT_DOM_CLASS(linkEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLLinkElementImpl")
		INIT_DOM_CLASS(mapEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLMapElementImpl")
		INIT_DOM_CLASS(menuEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLMenuElementImpl")
		INIT_DOM_CLASS(metaEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLMetaElementImpl")
		INIT_DOM_CLASS(modEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLModElementImpl")
		INIT_DOM_CLASS(objEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLObjectElementImpl")
		INIT_DOM_CLASS(oListEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLOListElementImpl")
		INIT_DOM_CLASS(optGrpEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLOptGroupElementImpl")
		INIT_DOM_CLASS(optEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLOptionElementImpl")
		INIT_DOM_CLASS(optColEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLOptionsCollectionImpl")
		INIT_DOM_CLASS(paraEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLParagraphElementImpl")
		INIT_DOM_CLASS(paramEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLParamElementImpl")
		INIT_DOM_CLASS(preEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLPreElementImpl")
		INIT_DOM_CLASS(quoteEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLQuoteElementImpl")
		INIT_DOM_CLASS(scriptEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLScriptElementImpl")
		INIT_DOM_CLASS(selEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLSelectElementImpl")
		INIT_DOM_CLASS(styleEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLStyleElementImpl")
		INIT_DOM_CLASS(tableCapEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableCaptionElementImpl")
		INIT_DOM_CLASS(tableCellEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableCellElementImpl")
		INIT_DOM_CLASS(tableColEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableColElementImpl")
		INIT_DOM_CLASS(tableEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableElementImpl")
		INIT_DOM_CLASS(tableRowEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableRowElementImpl")
		INIT_DOM_CLASS(tableSelEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTableSectionElementImpl")
		INIT_DOM_CLASS(textAreaEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTextAreaElementImpl")
		INIT_DOM_CLASS(titleEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLTitleElementImpl")
		INIT_DOM_CLASS(uListEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLUListElementImpl")
		INIT_DOM_CLASS(htmlEleCls,"org/mozilla/jrex/dom/html2/JRexHTMLElementImpl")

		colctElePeerID = env->GetFieldID(colctEleCls, "peerHTMLCol", "I");
		colctEleCID = env->GetMethodID(colctEleCls, "<init>", "()V");
		if (env->ExceptionCheck())goto FAILED;
		JREX_LOGLN("**** Intialize() colctElePeerID<"<<colctElePeerID<<"> colctEleCID<"<<colctEleCID<<"> ****")

		colOptctElePeerID = env->GetFieldID(optColEleCls, "peerHTMLOptCol", "I");
		colOptctEleCID = env->GetMethodID(optColEleCls, "<init>", "()V");
		if (env->ExceptionCheck())goto FAILED;
		JREX_LOGLN("**** Intialize() colOptctElePeerID<"<<colOptctElePeerID<<"> colOptctEleCID<"<<colOptctEleCID<<"> ****")
#endif //JREX_DOM_HTML2
		nodeJPair=new nsDataHashtable<nsISupportsHashKey,jobject>();
		if(!(nodeJPair && nodeJPair->Init(50)))goto FAILED;
		JREX_LOGLN("**** Intialize() created nodeJPair ****")
		JRexDOMGlobals::sIntialized=PR_TRUE;
		return JNI_TRUE;
FAILED:
		JNI_EXP_DESC_CLR((char*)NULL);
		UnIntialize(env);
		return JNI_FALSE;
	}

	void JRexDOMGlobals::UnIntialize(JNIEnv* env){
		JREX_LOGLN("**** UnIntialize() sIntialized<"<<JRexDOMGlobals::sIntialized<<"> env<"<<env<<"> attrCls<"<<attrCls<<"> ****")
		JRexDOMGlobals::sIntialized=PR_FALSE;
		if(nodeJPair){
			if(IS_EQT){
				delete nodeJPair;
			}else{
				nsresult srv=NS_OK;
				ExecInEventQDOM(nsnull, JRexDOMGlobals::JREX_NODE_PAIR_DELETE, nsnull, PR_TRUE, JRexDOMGlobals::HandleJRexDOMEvent, JRexDOMGlobals::DestroyJRexDOMEvent, (void**)&srv);
			}
			JREX_LOGLN("**** UnIntialize() nodeJPair delete Done!!!****")
		}
		if(attrCls)env->DeleteGlobalRef(attrCls);
		attrCls=NULL;
		if (env->ExceptionCheck())goto clean;

		UNINIT_DOM_CLASS(attrCls)
		UNINIT_DOM_CLASS(cDATASectionCls)
		UNINIT_DOM_CLASS(commentCls)
		UNINIT_DOM_CLASS(documentFragmentCls)
		UNINIT_DOM_CLASS(documentCls)
		UNINIT_DOM_CLASS(documentTypeCls)
		UNINIT_DOM_CLASS(domImplCls)
		UNINIT_DOM_CLASS(elementCls)
		UNINIT_DOM_CLASS(entityCls)
		UNINIT_DOM_CLASS(entityRefCls)
		UNINIT_DOM_CLASS(nodeMapCls)
		UNINIT_DOM_CLASS(nodeCls)
		UNINIT_DOM_CLASS(nodeListCls)
		UNINIT_DOM_CLASS(notationCls)
		UNINIT_DOM_CLASS(processingInstCls)
		UNINIT_DOM_CLASS(textCls)
		UNINIT_DOM_CLASS(domExpCls)
		UNINIT_DOM_CLASS(rangeExpCls)
		UNINIT_DOM_CLASS(rangeCls)
		UNINIT_DOM_CLASS(docRangeCls)
		UNINIT_DOM_CLASS(evtExpCls)
		UNINIT_DOM_CLASS(evtTargetCls)
		UNINIT_DOM_CLASS(docEventCls)
		UNINIT_DOM_CLASS(domEventCls)
		UNINIT_DOM_CLASS(domUIEventCls)
		UNINIT_DOM_CLASS(domMouseEventCls)
		UNINIT_DOM_CLASS(domMutEventCls)
		UNINIT_DOM_CLASS(abstractViewCls)
		UNINIT_DOM_CLASS(documentViewCls)
		UNINIT_DOM_CLASS(docTravCls)
		UNINIT_DOM_CLASS(nodeItrCls)
		UNINIT_DOM_CLASS(treeWkrCls)
		UNINIT_DOM_CLASS(domCfgCls)
		UNINIT_DOM_CLASS(domStrListCls)

		//HTML2 stuff
#if defined(JREX_DOM_HTML2)
		UNINIT_DOM_CLASS(anchorEleCls)
		UNINIT_DOM_CLASS(appEleCls)
		UNINIT_DOM_CLASS(areaEleCls)
		UNINIT_DOM_CLASS(baseEleCls)
		UNINIT_DOM_CLASS(baseFontEleCls)
		UNINIT_DOM_CLASS(bodyEleCls)
		UNINIT_DOM_CLASS(breEleCls)
		UNINIT_DOM_CLASS(butnEleCls)
		UNINIT_DOM_CLASS(colctEleCls)
		UNINIT_DOM_CLASS(dirEleCls)
		UNINIT_DOM_CLASS(divEleCls)
		UNINIT_DOM_CLASS(dListEleCls)
		UNINIT_DOM_CLASS(docEleCls)
		UNINIT_DOM_CLASS(fieldSetEleCls)
		UNINIT_DOM_CLASS(fontEleCls)
		UNINIT_DOM_CLASS(formEleCls)
		UNINIT_DOM_CLASS(frameEleCls)
		UNINIT_DOM_CLASS(frameSetEleCls)
		UNINIT_DOM_CLASS(headEleCls)
		UNINIT_DOM_CLASS(headingEleCls)
		UNINIT_DOM_CLASS(hrEleCls)
		UNINIT_DOM_CLASS(htmlHTMLEleCls)
		UNINIT_DOM_CLASS(iframeEleCls)
		UNINIT_DOM_CLASS(imageEleCls)
		UNINIT_DOM_CLASS(inputEleCls)
		UNINIT_DOM_CLASS(isIndexEleCls)
		UNINIT_DOM_CLASS(labelEleCls)
		UNINIT_DOM_CLASS(legendEleCls)
		UNINIT_DOM_CLASS(liEleCls)
		UNINIT_DOM_CLASS(linkEleCls)
		UNINIT_DOM_CLASS(mapEleCls)
		UNINIT_DOM_CLASS(menuEleCls)
		UNINIT_DOM_CLASS(metaEleCls)
		UNINIT_DOM_CLASS(modEleCls)
		UNINIT_DOM_CLASS(objEleCls)
		UNINIT_DOM_CLASS(oListEleCls)
		UNINIT_DOM_CLASS(optGrpEleCls)
		UNINIT_DOM_CLASS(optEleCls)
		UNINIT_DOM_CLASS(optColEleCls)
		UNINIT_DOM_CLASS(paraEleCls)
		UNINIT_DOM_CLASS(paramEleCls)
		UNINIT_DOM_CLASS(preEleCls)
		UNINIT_DOM_CLASS(quoteEleCls)
		UNINIT_DOM_CLASS(scriptEleCls)
		UNINIT_DOM_CLASS(selEleCls)
		UNINIT_DOM_CLASS(styleEleCls)
		UNINIT_DOM_CLASS(tableCapEleCls)
		UNINIT_DOM_CLASS(tableCellEleCls)
		UNINIT_DOM_CLASS(tableColEleCls)
		UNINIT_DOM_CLASS(tableEleCls)
		UNINIT_DOM_CLASS(tableRowEleCls)
		UNINIT_DOM_CLASS(tableSelEleCls)
		UNINIT_DOM_CLASS(textAreaEleCls)
		UNINIT_DOM_CLASS(titleEleCls)
		UNINIT_DOM_CLASS(uListEleCls)
		UNINIT_DOM_CLASS(htmlEleCls)
#endif //JREX_DOM_HTML2
		return;
	clean:
		env->ExceptionDescribe();
		env->ExceptionClear();
	}

	jobject JRexDOMGlobals::CreateNodeByType(JNIEnv* env, nsIDOMNode *node){
		return CreateNodeByType(env, node, PR_TRUE);
	}


#if defined(JREX_DOM_HTML2)
	//TODO Find Some faster way
	inline jclass JRexDOMGlobals::GetHTMLElementClass(nsIDOMHTMLElement *htmlEle){

		nsCOMPtr<nsIDOMHTMLAnchorElement> anchorEle;
		nsCOMPtr<nsIDOMHTMLAppletElement> appEle;
		nsCOMPtr<nsIDOMHTMLAreaElement>  areaEle;
		nsCOMPtr<nsIDOMHTMLBaseElement>  baseEle;
		nsCOMPtr<nsIDOMHTMLBaseFontElement> baseFontEle;
		nsCOMPtr<nsIDOMHTMLBodyElement>     bodyEle;
		nsCOMPtr<nsIDOMHTMLBRElement>       breEle;
		nsCOMPtr<nsIDOMHTMLButtonElement>   butnEle;
		nsCOMPtr<nsIDOMHTMLCollection>      colctEle;
		nsCOMPtr<nsIDOMHTMLDirectoryElement> dirEle;
		nsCOMPtr<nsIDOMHTMLDivElement>       divEle;
		nsCOMPtr<nsIDOMHTMLDListElement>     dListEle;
		nsCOMPtr<nsIDOMHTMLFieldSetElement>  fieldSetEle;
		nsCOMPtr<nsIDOMHTMLFontElement>      fontEle;
		nsCOMPtr<nsIDOMHTMLFormElement>      formEle;
		nsCOMPtr<nsIDOMHTMLFrameElement>     frameEle;
		nsCOMPtr<nsIDOMHTMLFrameSetElement>  frameSetEle;
		nsCOMPtr<nsIDOMHTMLHeadElement>      headEle;
		nsCOMPtr<nsIDOMHTMLHeadingElement>   headingEle;
		nsCOMPtr<nsIDOMHTMLHRElement>        hrEle;
		nsCOMPtr<nsIDOMHTMLHtmlElement>      htmlHTMLEle;
		nsCOMPtr<nsIDOMHTMLIFrameElement>    iframeEle;
		nsCOMPtr<nsIDOMHTMLImageElement>     imageEle;
		nsCOMPtr<nsIDOMHTMLInputElement>     inputEle;
		nsCOMPtr<nsIDOMHTMLIsIndexElement>   isIndexEle;
		nsCOMPtr<nsIDOMHTMLLabelElement>     labelEle;
		nsCOMPtr<nsIDOMHTMLLegendElement>    legendEle;
		nsCOMPtr<nsIDOMHTMLLIElement>        liEle;
		nsCOMPtr<nsIDOMHTMLLinkElement>      linkEle;
		nsCOMPtr<nsIDOMHTMLMapElement>       mapEle;
		nsCOMPtr<nsIDOMHTMLMenuElement>      menuEle;
		nsCOMPtr<nsIDOMHTMLMetaElement>      metaEle;
		nsCOMPtr<nsIDOMHTMLModElement>       modEle;
		nsCOMPtr<nsIDOMHTMLObjectElement>    objEle;
		nsCOMPtr<nsIDOMHTMLOListElement>     oListEle;
		nsCOMPtr<nsIDOMHTMLOptGroupElement>  optGrpEle;
		nsCOMPtr<nsIDOMHTMLOptionElement>    optEle;
		nsCOMPtr<nsIDOMHTMLOptionsCollection> optColEle;
		nsCOMPtr<nsIDOMHTMLParagraphElement>  paraEle;
		nsCOMPtr<nsIDOMHTMLParamElement>      paramEle;
		nsCOMPtr<nsIDOMHTMLPreElement>        preEle;
		nsCOMPtr<nsIDOMHTMLQuoteElement>      quoteEle;
		nsCOMPtr<nsIDOMHTMLScriptElement>     scriptEle;
		nsCOMPtr<nsIDOMHTMLSelectElement>     selEle;
		nsCOMPtr<nsIDOMHTMLStyleElement>      styleEle;
		nsCOMPtr<nsIDOMHTMLTableCaptionElement> tableCapEle;
		nsCOMPtr<nsIDOMHTMLTableCellElement>    tableCellEle;
		nsCOMPtr<nsIDOMHTMLTableColElement>     tableColEle;
		nsCOMPtr<nsIDOMHTMLTableElement>        tableEle;
		nsCOMPtr<nsIDOMHTMLTableRowElement>     tableRowEle;
		nsCOMPtr<nsIDOMHTMLTableSectionElement> tableSelEle;
		nsCOMPtr<nsIDOMHTMLTextAreaElement>     textAreaEle;
		nsCOMPtr<nsIDOMHTMLTitleElement>        titleEle;
		nsCOMPtr<nsIDOMHTMLUListElement>        uListEle;

		jclass retCls=NULL;
		if(anchorEle=do_QueryInterface(htmlEle))
			retCls=anchorEleCls;
		else
		if(appEle=do_QueryInterface(htmlEle))
			retCls=appEleCls;
		else
		if(areaEle=do_QueryInterface(htmlEle))
			retCls=areaEleCls;
		else
		if(baseEle=do_QueryInterface(htmlEle))
			retCls=baseEleCls;
		else
		if(baseFontEle=do_QueryInterface(htmlEle))
			retCls=baseFontEleCls;
		else
		if(bodyEle=do_QueryInterface(htmlEle))
			retCls=bodyEleCls;
		else
		if(breEle=do_QueryInterface(htmlEle))
			retCls=breEleCls;
		else
		if(butnEle=do_QueryInterface(htmlEle))
			retCls=butnEleCls;
		else
		if(colctEle=do_QueryInterface(htmlEle))
			retCls=colctEleCls;
		else
		if(dirEle=do_QueryInterface(htmlEle))
			retCls=dirEleCls;
		else
		if(divEle=do_QueryInterface(htmlEle))
			retCls=divEleCls;
		else
		if(dListEle=do_QueryInterface(htmlEle))
			retCls=dListEleCls;
		else
		if(fieldSetEle=do_QueryInterface(htmlEle))
			retCls=fieldSetEleCls;
		else
		if(fontEle=do_QueryInterface(htmlEle))
			retCls=fontEleCls;
		else
		if(formEle=do_QueryInterface(htmlEle))
			retCls=formEleCls;
		else
		if(frameEle=do_QueryInterface(htmlEle))
			retCls=frameEleCls;
		else
		if(frameSetEle=do_QueryInterface(htmlEle))
			retCls=frameSetEleCls;
		else
		if(headEle=do_QueryInterface(htmlEle))
			retCls=headEleCls;
		else
		if(headingEle=do_QueryInterface(htmlEle))
			retCls=headingEleCls;
		else
		if(hrEle=do_QueryInterface(htmlEle))
			retCls=hrEleCls;
		else
		if(htmlHTMLEle=do_QueryInterface(htmlEle))
			retCls=htmlHTMLEleCls;
		else
		if(iframeEle=do_QueryInterface(htmlEle))
			retCls=iframeEleCls;
		else
		if(imageEle=do_QueryInterface(htmlEle))
			retCls=imageEleCls;
		else
		if(isIndexEle=do_QueryInterface(htmlEle))
			retCls=isIndexEleCls;
		else
		if(labelEle=do_QueryInterface(htmlEle))
			retCls=labelEleCls;
		else
		if(legendEle=do_QueryInterface(htmlEle))
			retCls=legendEleCls;
		else
		if(liEle=do_QueryInterface(htmlEle))
			retCls=liEleCls;
		else
		if(linkEle=do_QueryInterface(htmlEle))
			retCls=linkEleCls;
		else
		if(mapEle=do_QueryInterface(htmlEle))
			retCls=mapEleCls;
		else
		if(menuEle=do_QueryInterface(htmlEle))
			retCls=menuEleCls;
		else
		if(metaEle=do_QueryInterface(htmlEle))
			retCls=metaEleCls;
		else
		if(modEle=do_QueryInterface(htmlEle))
			retCls=modEleCls;
		else
		if(objEle=do_QueryInterface(htmlEle))
			retCls=objEleCls;
		else
		if(oListEle=do_QueryInterface(htmlEle))
			retCls=oListEleCls;
		else
		if(optGrpEle=do_QueryInterface(htmlEle))
			retCls=optGrpEleCls;
		else
		if(optEle=do_QueryInterface(htmlEle))
			retCls=optEleCls;
		else
		if(optColEle=do_QueryInterface(htmlEle))
			retCls=optColEleCls;
		else
		if(paraEle=do_QueryInterface(htmlEle))
			retCls=paraEleCls;
		else
		if(paramEle=do_QueryInterface(htmlEle))
			retCls=paramEleCls;
		else
		if(preEle=do_QueryInterface(htmlEle))
			retCls=preEleCls;
		else
		if(quoteEle=do_QueryInterface(htmlEle))
			retCls=quoteEleCls;
		else
		if(scriptEle=do_QueryInterface(htmlEle))
			retCls=scriptEleCls;
		else
		if(selEle=do_QueryInterface(htmlEle))
			retCls=selEleCls;
		else
		if(styleEle=do_QueryInterface(htmlEle))
			retCls=styleEleCls;
		else
		if(tableCapEle=do_QueryInterface(htmlEle))
			retCls=tableCapEleCls;
		else
		if(tableCellEle=do_QueryInterface(htmlEle))
			retCls=tableCellEleCls;
		else
		if(tableColEle=do_QueryInterface(htmlEle))
			retCls=tableColEleCls;
		else
		if(tableEle=do_QueryInterface(htmlEle))
			retCls=tableEleCls;
		else
		if(tableRowEle=do_QueryInterface(htmlEle))
			retCls=tableRowEleCls;
		else
		if(tableSelEle=do_QueryInterface(htmlEle))
			retCls=tableSelEleCls;
		else
		if(textAreaEle=do_QueryInterface(htmlEle))
			retCls=textAreaEleCls;
		else
		if(titleEle=do_QueryInterface(htmlEle))
			retCls=titleEleCls;
		else
		if(uListEle=do_QueryInterface(htmlEle))
			retCls=uListEleCls;
		else
		if(inputEle=do_QueryInterface(htmlEle))
			retCls=inputEleCls;

		return IS_NULL(retCls)?htmlEleCls:retCls;
	}
	#endif //JREX_DOM_HTML2

	jobject JRexDOMGlobals::CreateNodeByTypeInternal(JNIEnv *env, nsIDOMNode *node, PRBool addRef){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateNodeByTypeInternal env<"<<env<<"> node<"<<node<<"> ****")
  		if (IS_NULL(node) || env->EnsureLocalCapacity(2))return NULL;

  		PRUint16 nodeType = 0;
  		nsresult rv= node->GetNodeType(&nodeType);
  		JREX_LOGLN("**** CreateNodeByTypeInternal GetNodeType rv<"<<rv<<"> nodeType<"<<nodeType<<"> ****")

		jclass cls=NULL;
		switch (nodeType) {
			case nsIDOMNode::ATTRIBUTE_NODE:
				cls = attrCls;
				break;

			case nsIDOMNode::CDATA_SECTION_NODE:
				cls = cDATASectionCls;
				break;

			case nsIDOMNode::COMMENT_NODE:
				cls = commentCls;
				break;

			case nsIDOMNode::DOCUMENT_FRAGMENT_NODE:
				cls = documentFragmentCls;
				break;

			case nsIDOMNode::DOCUMENT_NODE:
			{
				jclass tmpCls=NULL;
#if defined(JREX_DOM_HTML2)
				nsCOMPtr<nsIDOMHTMLDocument> htmlDoc;
				if(htmlDoc=do_QueryInterface(node)){
					JREX_LOGLN("**** CreateNodeByTypeInternal Got A HTML Document !!!****")
					tmpCls=docEleCls;
				}
#endif //JREX_DOM_HTML2
				cls = IS_NULL(tmpCls)?documentCls:tmpCls;
				break;
			}
			case nsIDOMNode::DOCUMENT_TYPE_NODE:
				cls = documentTypeCls;
				break;

			case nsIDOMNode::ELEMENT_NODE:
			{
				jclass tmpCls=NULL;
#if defined(JREX_DOM_HTML2)
				nsCOMPtr<nsIDOMHTMLElement> htmlEle;
				if(htmlEle=do_QueryInterface(node)){
					JREX_LOGLN("**** CreateNodeByTypeInternal Got A HTML Element !!!****")
					tmpCls=GetHTMLElementClass(htmlEle.get());
				}
#endif //JREX_DOM_HTML2
				cls = IS_NULL(tmpCls)?elementCls:tmpCls;
				break;
			}
			case nsIDOMNode::ENTITY_NODE:
				cls = entityCls;
				break;

			case nsIDOMNode::ENTITY_REFERENCE_NODE:
				cls = entityRefCls;
				break;

			case nsIDOMNode::NOTATION_NODE:
				cls = notationCls;
				break;

			case nsIDOMNode::PROCESSING_INSTRUCTION_NODE:
				cls = processingInstCls;
				break;

			case nsIDOMNode::TEXT_NODE:
				cls = textCls;
				break;

			default:
				cls=nodeCls;
		}
		JREX_LOGLN("**** CreateNodeByTypeInternal() cls<"<<cls<<"> ****")
		if(IS_NULL(cls))return NULL; //this can happen if DOM is disabled via sys property

		jobject value=NULL;
		nodeJPair->Get(node,&value);
		if(value){
			jboolean instanceOf=env->IsInstanceOf(value, cls);
			if(instanceOf==JNI_TRUE){
				JREX_LOGLN("**** CreateNodeByTypeInternal Returning Already Created Instance!!!****")
				return value;
			}
		}

		jobject jdomNode = env->NewObject(cls,nodeCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomNode)){
			JREX_LOGLN("**** CreateNodeByTypeInternal() jdomNode<"<<jdomNode<<"> nodePeerID<"<<NS_PTR_TO_INT32(node)<<"> ****")
			env->SetIntField(jdomNode, nodePeerID,(jint)NS_PTR_TO_INT32(node));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateNodeByTypeInternal()--> ***jdomNode Creation done ****")
				if(addRef)NS_ADDREF(node);
				//jobject putObj=env->NewWeakGlobalRef(jdomNode);
				SAFE_PUT(node,jdomNode);
				return jdomNode;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateNodeByTypeInternal() Exception Occured ****");
		JREX_LOGLN("CreateNodeByTypeInternal()--> **** jdomNode Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateNodeByType(JNIEnv* env, nsIDOMNode *node, PRBool addRef){
		if(IS_EQT)
			return CreateNodeByTypeInternal(env, node,addRef);
		else{
			JRexDOMGlobalEventParam* param=new JRexDOMGlobalEventParam;
			if(IS_NULL(param))return NULL;
			param->node=node;
			param->addRef=addRef;

			JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL;
			nsresult rv=ExecInEventQDOM(nsnull, JREX_CREATE_NODE_BY_TYPE, param, PR_TRUE, JRexDOMGlobals::HandleJRexDOMEvent, JRexDOMGlobals::DestroyJRexDOMEvent, (void**)&jrv);
			JREX_LOGLN("CreateNodeByType()--> **** ExecInEventQDOM rv<"<<rv<<"> jrv<"<<jrv<<">  ****")
			jobject retObj = (jrv && NS_SUCCEEDED(jrv->rv))?jrv->jobj:NULL;
			if (NOT_NULL(jrv)) {
				delete jrv;
			}
			return retObj;
		}
	}


	jobject JRexDOMGlobals::CreateNodeMap(JNIEnv* env, nsIDOMNamedNodeMap *nodeMap){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateNodeMap env<"<<env<<"> nodeMap<"<<nodeMap<<"> ****")
  		if (IS_NULL(nodeMap) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(nodeMap,&value);
		if(value){
			JREX_LOGLN("**** CreateNodeMap Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomNodeMap = env->NewObject(nodeMapCls,nodeMapCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomNodeMap)){
			JREX_LOGLN("**** CreateNodeMap() jdomNodeMap<"<<jdomNodeMap<<"> nodeMapPeerID<"<<NS_PTR_TO_INT32(nodeMap)<<"> ****")
			env->SetIntField(jdomNodeMap, nodeMapPeerID,(jint)NS_PTR_TO_INT32(nodeMap));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateNodeMap()--> ***jdomNodeMap Creation done ****")
				NS_ADDREF(nodeMap);
				//jobject putObj=env->NewWeakGlobalRef(jdomNodeMap);
				SAFE_PUT(nodeMap,jdomNodeMap);
				return jdomNodeMap;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateNodeMap() Exception Occured ****");
		JREX_LOGLN("CreateNodeMap()--> **** jdomNodeMap Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateNodeList(JNIEnv* env, nsIDOMNodeList *nodeList){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateNodeList env<"<<env<<"> nodeList<"<<nodeList<<"> ****")
  		if (IS_NULL(nodeList) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(nodeList,&value);
		if(value){
			JREX_LOGLN("**** CreateNodeList Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomNodeList = env->NewObject(nodeListCls,nodeListCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomNodeList)){
			JREX_LOGLN("**** CreateNodeList() jdomNodeList<"<<jdomNodeList<<"> nodeListPeerID<"<<NS_PTR_TO_INT32(nodeList)<<"> ****")
			env->SetIntField(jdomNodeList, nodeListPeerID,(jint)NS_PTR_TO_INT32(nodeList));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateNodeList()--> ***jdomNodeList Creation done ****")
				NS_ADDREF(nodeList);
				//jobject putObj=env->NewWeakGlobalRef(jdomNodeList);
				SAFE_PUT(nodeList, jdomNodeList);
				return jdomNodeList;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateNodeList() Exception Occured ****");
		JREX_LOGLN("CreateNodeList()--> **** jdomNodeList Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDOMImpl(JNIEnv* env, nsIDOMDOMImplementation *domImpl){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDOMImpl env<"<<env<<"> domImpl<"<<domImpl<<"> ****")
  		if (IS_NULL(domImpl) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(domImpl,&value);
		if(value){
			JREX_LOGLN("**** CreateDOMImpl Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomImpl = env->NewObject(domImplCls,domImplCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomImpl)){
			JREX_LOGLN("**** CreateDOMImpl() jdomImpl<"<<jdomImpl<<"> domImplPeerID<"<<NS_PTR_TO_INT32(domImpl)<<"> ****")
			env->SetIntField(jdomImpl, domImplPeerID,(jint)NS_PTR_TO_INT32(domImpl));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDOMImpl()--> ***jdomImpl Creation done ****")
				NS_ADDREF(domImpl);
				//jobject putObj=env->NewWeakGlobalRef(jdomImpl);
				SAFE_PUT(domImpl, jdomImpl);
				return jdomImpl;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDOMImpl() Exception Occured ****");
		JREX_LOGLN("CreateDOMImpl()--> **** jdomImpl Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateRange(JNIEnv* env, nsIDOMRange *range){
		return CreateRange(env, range, PR_TRUE);
	}

	jobject JRexDOMGlobals::CreateRange(JNIEnv* env, nsIDOMRange *range, PRBool addRef){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateRange env<"<<env<<"> range<"<<range<<"> ****")
  		if (IS_NULL(range) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(range,&value);
		if(value){
			JREX_LOGLN("**** CreateRange Returning Already Created Instance!!!****")
			return value;
		}

		jobject jrange = env->NewObject(rangeCls,rangeCID);
		if(!env->ExceptionCheck() && NOT_NULL(jrange)){
			JREX_LOGLN("**** CreateRange() jrange<"<<jrange<<"> rangePeerID<"<<NS_PTR_TO_INT32(range)<<"> ****")
			env->SetIntField(jrange, rangePeerID, (jint)NS_PTR_TO_INT32(range));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateRange()--> ***jrange Creation done ****")
				if(addRef)NS_ADDREF(range);
				//jobject putObj=env->NewWeakGlobalRef(jrange);
				SAFE_PUT(range,jrange);
				return jrange;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateRange() Exception Occured ****");
		JREX_LOGLN("CreateRange()--> **** jrange Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDocumentRange(JNIEnv* env, nsIDOMDocumentRange *docRange){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDocumentRange env<"<<env<<"> docRange<"<<docRange<<"> ****")
  		if (IS_NULL(docRange) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(docRange,&value);
		if(value){
			JREX_LOGLN("**** CreateDocumentRange Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdocRange = env->NewObject(docRangeCls,docRangeCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdocRange)){
			JREX_LOGLN("**** CreateDocumentRange() jdocRange<"<<jdocRange<<"> docRangePeerID<"<<NS_PTR_TO_INT32(docRange)<<"> ****")
			env->SetIntField(jdocRange, docRangePeerID, (jint)NS_PTR_TO_INT32(docRange));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDocumentRange()--> ***jdocRange Creation done ****")
				NS_ADDREF(docRange);
				//jobject putObj=env->NewWeakGlobalRef(jdocRange);
				SAFE_PUT(docRange,jdocRange);
				return jdocRange;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDocumentRange() Exception Occured ****");
		JREX_LOGLN("CreateDocumentRange()--> **** jdocRange Creation Failed !!! ****")
		return NULL;
	}


	jobject JRexDOMGlobals::CreateEventTarget(JNIEnv* env, nsIDOMEventTarget *evtTarget){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateEventTarget env<"<<env<<"> evtTarget<"<<evtTarget<<"> ****")
  		if (IS_NULL(evtTarget) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(evtTarget,&value);
		if(value){
			JREX_LOGLN("**** CreateEventTarget Returning Already Created Instance!!!****")
			return value;
		}

		jobject jevtTarget = env->NewObject(evtTargetCls,evtTargetCID);
		if(!env->ExceptionCheck() && NOT_NULL(jevtTarget)){
			JREX_LOGLN("**** CreateEventTarget() jevtTarget<"<<jevtTarget<<"> evtTargetPeerID<"<<NS_PTR_TO_INT32(evtTarget)<<"> ****")
			env->SetIntField(jevtTarget, evtTargetPeerID, (jint)NS_PTR_TO_INT32(evtTarget));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateEventTarget()--> ***jevtTarget Creation done ****")
				NS_ADDREF(evtTarget);
				//jobject putObj=env->NewWeakGlobalRef(jevtTarget);
				SAFE_PUT(evtTarget,jevtTarget);
				return jevtTarget;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateEventTarget() Exception Occured ****");
		JREX_LOGLN("CreateEventTarget()--> **** jevtTarget Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDocumentEvent(JNIEnv* env, nsIDOMDocumentEvent *docEvent){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDocumentEvent env<"<<env<<"> docEvent<"<<docEvent<<"> ****")
  		if (IS_NULL(docEvent) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(docEvent,&value);
		if(value){
			JREX_LOGLN("**** CreateDocumentEvent Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdocEvent = env->NewObject(docEventCls,docEventCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdocEvent)){
			JREX_LOGLN("**** CreateDocumentEvent() jdocEvent<"<<jdocEvent<<"> docEventPeerID<"<<NS_PTR_TO_INT32(docEvent)<<"> ****")
			env->SetIntField(jdocEvent, docEventPeerID, (jint)NS_PTR_TO_INT32(docEvent));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDocumentEvent()--> ***jevtDoc Creation done ****")
				NS_ADDREF(docEvent);
				//jobject putObj=env->NewWeakGlobalRef(jdocEvent);
				SAFE_PUT(docEvent,jdocEvent);
				return jdocEvent;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDocumentEvent() Exception Occured ****");
		JREX_LOGLN("CreateDocumentEvent()--> **** jdocEvent Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDocumentTraversal(JNIEnv* env, nsIDOMDocumentTraversal *docTrav){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDocumentTraversal env<"<<env<<"> docTrav<"<<docTrav<<"> ****")
  		if (IS_NULL(docTrav) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(docTrav,&value);
		if(value){
			JREX_LOGLN("**** CreateDocumentTraversal Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdocTrav = env->NewObject(docTravCls,docTravCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdocTrav)){
			JREX_LOGLN("**** CreateDocumentTraversal() jdocTrav<"<<jdocTrav<<"> docTravPeerID<"<<NS_PTR_TO_INT32(docTrav)<<"> ****")
			env->SetIntField(jdocTrav, docTravPeerID, (jint)NS_PTR_TO_INT32(docTrav));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDocumentTraversal()--> ***jevtDoc Creation done ****")
				NS_ADDREF(docTrav);
				//jobject putObj=env->NewWeakGlobalRef(jdocTrav);
				SAFE_PUT(docTrav,jdocTrav);
				return jdocTrav;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDocumentTraversal() Exception Occured ****");
		JREX_LOGLN("CreateDocumentTraversal()--> **** jdocTrav Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDocumentView(JNIEnv* env, nsIDOMDocumentView *docView){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDocumentView env<"<<env<<"> docView<"<<docView<<"> ****")
  		if (IS_NULL(docView) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(docView,&value);
		if(value){
			JREX_LOGLN("**** CreateDocumentView Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdocView = env->NewObject(documentViewCls,documentViewCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdocView)){
			JREX_LOGLN("**** CreateDocumentView() jdocView<"<<jdocView<<"> documentViewPeerID<"<<NS_PTR_TO_INT32(docView)<<"> ****")
			env->SetIntField(jdocView, documentViewPeerID, (jint)NS_PTR_TO_INT32(docView));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDocumentView()--> ***jevtDoc Creation done ****")
				NS_ADDREF(docView);
				//jobject putObj=env->NewWeakGlobalRef(jdocView);
				SAFE_PUT(docView,jdocView);
				return jdocView;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDocumentView() Exception Occured ****");
		JREX_LOGLN("CreateDocumentView()--> **** jdocView Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDOMEvent(JNIEnv* env, nsIDOMEvent *event){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDOMEvent env<"<<env<<"> event<"<<event<<"> ****")
  		if (IS_NULL(event) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(event,&value);
		if(value){
			JREX_LOGLN("**** CreateDOMEvent Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomEvent=NULL;

		nsCOMPtr<nsIDOMMutationEvent> mutEvent;
		nsCOMPtr<nsIDOMMouseEvent>	mouseEvent;
		nsCOMPtr<nsIDOMUIEvent>	uiEvent;

		if(mutEvent=do_QueryInterface(event)){
			JREX_LOGLN("**** CreateDOMEvent() MutationEvents ****")
			jdomEvent = env->NewObject(domMutEventCls,domEventCID);
		}else
		if(mouseEvent=do_QueryInterface(event)){
			JREX_LOGLN("**** CreateDOMEvent() MouseEvents ****")
			jdomEvent = env->NewObject(domMouseEventCls,domEventCID);
		}else
		if(uiEvent=do_QueryInterface(event)){
			JREX_LOGLN("**** CreateDOMEvent() UIEvents ****")
			jdomEvent = env->NewObject(domUIEventCls,domEventCID);
		}else{
			JREX_LOGLN("**** CreateDOMEvent() Normal Events ****")
			jdomEvent = env->NewObject(domEventCls,domEventCID);
		}

		if(!env->ExceptionCheck() && NOT_NULL(jdomEvent)){
			JREX_LOGLN("**** CreateDOMEvent() jdomEvent<"<<jdomEvent<<"> domEventPeerID<"<<NS_PTR_TO_INT32(event)<<"> ****")
			env->SetIntField(jdomEvent, domEventPeerID, (jint)NS_PTR_TO_INT32(event));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDOMEvent()--> ***jdomEvent Creation done ****")
				NS_ADDREF(event);
				//jobject putObj=env->NewWeakGlobalRef(jdomEvent);
				SAFE_PUT(event,jdomEvent);
				return jdomEvent;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDOMEvent() Exception Occured ****");
		JREX_LOGLN("CreateDOMEvent()--> **** jdomEvent Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateNodeIterator(JNIEnv* env, nsIDOMNodeIterator *nodeItr){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateNodeIterator env<"<<env<<"> nodeItr<"<<nodeItr<<"> ****")
  		if (IS_NULL(nodeItr) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(nodeItr,&value);
		if(value){
			JREX_LOGLN("**** CreateNodeIterator Returning Already Created Instance!!!****")
			return value;
		}

		jobject jnodeItr = env->NewObject(nodeItrCls,nodeItrCID);
		if(!env->ExceptionCheck() && NOT_NULL(jnodeItr)){
			JREX_LOGLN("**** CreateNodeIterator() jnodeItr<"<<jnodeItr<<"> nodeItrPeerID<"<<NS_PTR_TO_INT32(nodeItr)<<"> ****")
			env->SetIntField(jnodeItr, nodeItrPeerID, (jint)NS_PTR_TO_INT32(nodeItr));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateNodeIterator()--> ***jnodeItr Creation done ****")
				NS_ADDREF(nodeItr);
				//jobject putObj=env->NewWeakGlobalRef(jnodeItr);
				SAFE_PUT(nodeItr,jnodeItr);
				return jnodeItr;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateNodeIterator() Exception Occured ****");
		JREX_LOGLN("CreateNodeIterator()--> **** jnodeItr Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateTreeWalker(JNIEnv* env, nsIDOMTreeWalker *treeWkr){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateTreeWalker env<"<<env<<"> treeWkr<"<<treeWkr<<"> ****")
  		if (IS_NULL(treeWkr) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(treeWkr,&value);
		if(value){
			JREX_LOGLN("**** CreateTreeWalker Returning Already Created Instance!!!****")
			return value;
		}

		jobject jtreeWkr = env->NewObject(treeWkrCls,treeWkrCID);
		if(!env->ExceptionCheck() && NOT_NULL(jtreeWkr)){
			JREX_LOGLN("**** CreateTreeWalker() jtreeWkr<"<<jtreeWkr<<"> treeWkrPeerID<"<<NS_PTR_TO_INT32(treeWkr)<<"> ****")
			env->SetIntField(jtreeWkr, treeWkrPeerID, (jint)NS_PTR_TO_INT32(treeWkr));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateTreeWalker()--> ***jtreeWkr Creation done ****")
				NS_ADDREF(treeWkr);
				//jobject putObj=env->NewWeakGlobalRef(jtreeWkr);
				SAFE_PUT(treeWkr,jtreeWkr);
				return jtreeWkr;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateTreeWalker() Exception Occured ****");
		JREX_LOGLN("CreateTreeWalker()--> **** jtreeWkr Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDOMConfiguration(JNIEnv* env, nsIDOMDOMConfiguration *domCfg){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDOMConfiguration env<"<<env<<"> domCfg<"<<domCfg<<"> ****")
  		if (IS_NULL(domCfg) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(domCfg,&value);
		if(value){
			JREX_LOGLN("**** CreateDOMConfiguration Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomCfg = env->NewObject(domCfgCls,domCfgCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomCfg)){
			JREX_LOGLN("**** CreateDOMConfiguration() jdomCfg<"<<jdomCfg<<"> domCfgPeerID<"<<NS_PTR_TO_INT32(domCfg)<<"> ****")
			env->SetIntField(jdomCfg, domCfgPeerID, (jint)NS_PTR_TO_INT32(domCfg));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDOMConfiguration()--> ***jdomCfg Creation done ****")
				NS_ADDREF(domCfg);
				//jobject putObj=env->NewWeakGlobalRef(jdomCfg);
				SAFE_PUT(domCfg,jdomCfg);
				return jdomCfg;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDOMConfiguration() Exception Occured ****");
		JREX_LOGLN("CreateDOMConfiguration()--> **** jdomCfg Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateDOMStringList(JNIEnv* env, nsIDOMDOMStringList *domStrList){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateDOMStringList env<"<<env<<"> domStrList<"<<domStrList<<"> ****")
  		if (IS_NULL(domStrList) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(domStrList,&value);
		if(value){
			JREX_LOGLN("**** CreateDOMStringList Returning Already Created Instance!!!****")
			return value;
		}

		jobject jdomStrList = env->NewObject(domStrListCls,domStrListCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomStrList)){
			JREX_LOGLN("**** CreateDOMStringList() jdomStrList<"<<jdomStrList<<"> domStrListPeerID<"<<NS_PTR_TO_INT32(domStrList)<<"> ****")
			env->SetIntField(jdomStrList, domStrListPeerID, (jint)NS_PTR_TO_INT32(domStrList));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateDOMStringList()--> ***jdomStrList Creation done ****")
				NS_ADDREF(domStrList);
				//jobject putObj=env->NewWeakGlobalRef(jdomStrList);
				SAFE_PUT(domStrList,jdomStrList);
				return jdomStrList;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateDOMStringList() Exception Occured ****");
		JREX_LOGLN("CreateDOMStringList()--> **** jdomStrList Creation Failed !!! ****")
		return NULL;
	}


	jobject JRexDOMGlobals::CreateAbstractView(JNIEnv* env, nsIDOMAbstractView *view){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateAbstractView env<"<<env<<"> view<"<<view<<"> ****")
  		if (IS_NULL(view) || env->EnsureLocalCapacity(2))return NULL;

		jobject value=NULL;
		nodeJPair->Get(view,&value);
		if(value){
			JREX_LOGLN("**** CreateAbstractView Returning Already Created Instance!!!****")
			return value;
		}

		jobject jabstractView = env->NewObject(abstractViewCls,abstractViewCID);
		if(!env->ExceptionCheck() && NOT_NULL(jabstractView)){
			JREX_LOGLN("**** CreateAbstractView() jabstractView<"<<jabstractView<<"> abstractViewPeerID<"<<NS_PTR_TO_INT32(view)<<"> ****")
			env->SetIntField(jabstractView, abstractViewPeerID, (jint)NS_PTR_TO_INT32(view));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateAbstractView()--> ***jabstractView Creation done ****")
				NS_ADDREF(view);
				//jobject putObj=env->NewWeakGlobalRef(jabstractView);
				SAFE_PUT(view,jabstractView);
				return jabstractView;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateAbstractView() Exception Occured ****");
		JREX_LOGLN("CreateAbstractView()--> **** jabstractView Creation Failed !!! ****")
		return NULL;
	}

#if defined(JREX_DOM_HTML2)
	jobject JRexDOMGlobals::CreateHTMLCollection(JNIEnv* env, nsIDOMHTMLCollection *htmlCol){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateHTMLCollection env<"<<env<<"> htmlCol<"<<htmlCol<<"> ****")
  		if (IS_NULL(htmlCol) || env->EnsureLocalCapacity(2))return NULL;

		jobject jdomHtmlCol = env->NewObject(colctEleCls,colctEleCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomHtmlCol)){
			JREX_LOGLN("**** CreateHTMLCollection() jdomHtmlCol<"<<jdomHtmlCol<<"> colctElePeerID<"<<NS_PTR_TO_INT32(htmlCol)<<"> ****")
			env->SetIntField(jdomHtmlCol, colctElePeerID,(jint)NS_PTR_TO_INT32(htmlCol));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateHTMLCollection()--> ***jdomHtmlCol Creation done ****")
				NS_ADDREF(htmlCol);
				return jdomHtmlCol;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateHTMLCollection() Exception Occured ****");
		JREX_LOGLN("CreateHTMLCollection()--> **** jdomHtmlCol Creation Failed !!! ****")
		return NULL;
	}

	jobject JRexDOMGlobals::CreateHTMLOptionsCollection(JNIEnv* env, nsIDOMHTMLOptionsCollection *htmlOptCol){
		if(IS_NULL(env))env=JRex_GetEnv(0);
		JREX_LOGLN("**** CreateHTMLOptionsCollection env<"<<env<<"> htmlOptCol<"<<htmlOptCol<<"> ****")
  		if (IS_NULL(htmlOptCol) || env->EnsureLocalCapacity(2))return NULL;

		jobject jdomHtmlOptCol = env->NewObject(optColEleCls,colOptctEleCID);
		if(!env->ExceptionCheck() && NOT_NULL(jdomHtmlOptCol)){
			JREX_LOGLN("**** CreateHTMLOptionsCollection() jdomHtmlOptCol<"<<jdomHtmlOptCol<<"> colOptctElePeerID<"<<NS_PTR_TO_INT32(htmlOptCol)<<"> ****")
			env->SetIntField(jdomHtmlOptCol, colOptctElePeerID,(jint)NS_PTR_TO_INT32(htmlOptCol));
			if (!env->ExceptionCheck()){
				JREX_LOGLN("CreateHTMLOptionsCollection()--> ***jdomHtmlOptCol Creation done ****")
				NS_ADDREF(htmlOptCol);
				return jdomHtmlOptCol;
			}
		}
		JNI_EXP_DESC_CLR("**** CreateHTMLOptionsCollection() Exception Occured ****");
		JREX_LOGLN("CreateHTMLOptionsCollection()--> **** jdomHtmlOptCol Creation Failed !!! ****")
		return NULL;
	}
#endif //JREX_DOM_HTML2

	/** A utility function to throw w3c DOM excepiton */
	void JRexDOMGlobals::ThrowDOMException(JNIEnv *env, nsresult errorCode){
		JREX_LOGLN("******* ThrowDOMException errorCode <"<<errorCode<<"> ****")
		PRUint32 nsErrCode=NS_ERROR_GET_CODE(errorCode);
		if(nsErrCode>15)nsErrCode=0;

		if (env->EnsureLocalCapacity(2) < 0) {
			JREX_LOGLN("******* ThrowDOMException EnsureLocalCapacity Failed ****")
			return;
		}

		jstring jexpMsg=env->NewStringUTF(DOM_EXP_CODE_MESSAGE[nsErrCode]);
		jthrowable domException = (jthrowable)env->NewObject(domExpCls,domExpCID,nsErrCode,jexpMsg);
		if(jexpMsg)env->DeleteLocalRef(jexpMsg);
		if(NOT_NULL(domException))
			env->Throw(domException);
	}

	/** A utility function to throw w3c DOM Range excepiton */
	void JRexDOMGlobals::ThrowRangeException(JNIEnv *env, nsresult errorCode){
		JREX_LOGLN("******* ThrowRangeException errorCode <"<<errorCode<<"> ****")
		PRUint32 nsErrCode=NS_ERROR_GET_CODE(errorCode);
		if(nsErrCode>2)nsErrCode=0;

		if (env->EnsureLocalCapacity(2) < 0) {
			JREX_LOGLN("******* ThrowRangeException EnsureLocalCapacity Failed ****")
			return;
		}

		jstring jexpMsg=env->NewStringUTF(RANGE_EXP_CODE_MESSAGE[nsErrCode]);
		jthrowable rangeException = (jthrowable)env->NewObject(rangeExpCls,rangeExpCID,nsErrCode,jexpMsg);
		if(jexpMsg)env->DeleteLocalRef(jexpMsg);
		if(NOT_NULL(rangeException))
			env->Throw(rangeException);
	}

	/** A utility function to throw w3c DOM Event excepiton */
	void JRexDOMGlobals::ThrowEventException(JNIEnv *env, nsresult errorCode){
		JREX_LOGLN("******* ThrowEventException errorCode <"<<errorCode<<"> ****")
		if (env->EnsureLocalCapacity(2) < 0) {
			JREX_LOGLN("******* ThrowRangeException EnsureLocalCapacity Failed ****")
			return;
		}
		jstring jexpMsg=env->NewStringUTF(EVENT_EXP_CODE_MESSAGE);
		jthrowable eventException = (jthrowable)env->NewObject(evtExpCls,evtExpCID,0,jexpMsg);
		if(jexpMsg)env->DeleteLocalRef(jexpMsg);
		if(NOT_NULL(eventException))
			env->Throw(eventException);
	}

	void* PR_CALLBACK JRexDOMGlobals::HandleJRexDOMEvent(PLEvent* aEvent){
		if(!JRexDOMGlobals::sIntialized)return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		nsresult rv=NS_OK;
		JREX_LOGLN("HandleJRexDOMEvent()--> **** target <"<<event->target<<"> ****")
		nsISupports* tempSup= NS_REINTERPRET_CAST(nsISupports*, event->target);
		switch(event->eventType){
			case JREX_CREATE_NODE_BY_TYPE:
			{
				JREX_LOGLN("HandleJRexDOMEvent JREX_CREATE_NODE_BY_TYPE EVENT!!!****")
				JREX_JNI_UTIL::JRexCommonJRV *jrv=new JREX_JNI_UTIL::JRexCommonJRV;
				if(IS_NULL(jrv))return NULL;
				JRexDOMGlobalEventParam* parm = NS_REINTERPRET_CAST(JRexDOMGlobalEventParam*, event->eventData);
				jrv->jobj=CreateNodeByTypeInternal(NULL, parm->node,parm->addRef);
				jrv->rv=IS_NULL(jrv->jobj)?NS_ERROR_FAILURE:NS_OK;
				return jrv;
			}
			case JREX_RELEASE:
			{
				JREX_LOGLN("HandleJRexDOMEvent JREX_RELEASE EVENT!!!****")
				/*jobject myVal=NULL;
				nodeJPair->Get(tempSup,&myVal);
				if(myVal){
					JNIEnv* env =JRex_GetEnv(0);
					env->DeleteWeakGlobalRef(myVal);
				}*/
				nodeJPair->Remove(tempSup);
				NS_IF_RELEASE(tempSup);
				break;
			}
			case JREX_NODE_PAIR_PUT:
			{
				JREX_LOGLN("HandleJRexDOMEvent JREX_NODE_PAIR_PUT EVENT!!!****")
				nodeJPair->Put(tempSup,(jobject)event->eventData);
				break;
			}
			case JREX_NODE_PAIR_DELETE:
			{
				JREX_LOGLN("HandleJRexDOMEvent JREX_NODE_PAIR_DELETE EVENT!!!****")
				delete nodeJPair;
				break;
			}
			default:
			{
				JREX_LOGLN("HandleJRexDOMEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleJRexDOMEvent()--> **** returning rv<"<<rv<<"> ****")
		return (void*)rv;
	}

	void PR_CALLBACK JRexDOMGlobals::DestroyJRexDOMEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyJRexDOMEvent()--> **** target <"<<event->target<<"> ****")
		switch(event->eventType){
			case JREX_CREATE_NODE_BY_TYPE:
			{
				JRexDOMGlobalEventParam* param = NS_REINTERPRET_CAST(JRexDOMGlobalEventParam*, event->eventData);
				delete param;
			}
		}
		delete event;
	}
