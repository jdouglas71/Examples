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

	#ifndef JRexDOMGlobals_h_
	#define JRexDOMGlobals_h_

	#include "JRexIncludes.h"
	#include "JRex_JNI_Util.h"

	using namespace JREX_JNI_UTIL;

	#define DOM_EXP_NAME				"org/w3c/dom/DOMException"
	#define RANGE_EXP_NAME				"org/w3c/dom/ranges/RangeException"
	#define EVENT_EXP_NAME				"org/w3c/dom/events/EventException"

	class JRexDOMGlobals{
		public :
			static jclass attrCls;
			static jclass cDATASectionCls;
			//static jclass characterDataCls; //no object used
			static jclass commentCls;
			static jclass documentFragmentCls;
			static jclass documentCls;
			static jclass documentTypeCls;
			static jclass domImplCls;
			static jclass elementCls;
			static jclass entityCls;
			static jclass entityRefCls;
			static jclass nodeMapCls;
			static jclass nodeCls;
			static jclass nodeListCls;
			static jclass notationCls;
			static jclass processingInstCls;
			static jclass textCls;
			static jclass domExpCls;
			static jclass rangeCls;
			static jclass rangeExpCls;
			static jclass docRangeCls;
			static jclass evtExpCls;
			static jclass evtTargetCls;
			static jclass docEventCls;
			static jclass domEventCls;
			static jclass domUIEventCls;
			static jclass domMouseEventCls;
			static jclass domMutEventCls;
			static jclass abstractViewCls;
			static jclass documentViewCls;
			static jclass docTravCls;
			static jclass nodeItrCls;
			static jclass treeWkrCls;
			static jclass domCfgCls;
			static jclass domStrListCls;

#if defined(JREX_DOM_HTML2)
			//HTML2 Stuff
			static jclass anchorEleCls;
			static jclass appEleCls;
			static jclass areaEleCls;
			static jclass baseEleCls;
			static jclass baseFontEleCls;
			static jclass bodyEleCls;
			static jclass breEleCls;
			static jclass butnEleCls;
			static jclass colctEleCls;
			static jclass dirEleCls;
			static jclass divEleCls;
			static jclass dListEleCls;
			static jclass docEleCls;
			static jclass fieldSetEleCls;
			static jclass fontEleCls;
			static jclass formEleCls;
			static jclass frameEleCls;
			static jclass frameSetEleCls;
			static jclass headEleCls;
			static jclass headingEleCls;
			static jclass hrEleCls;
			static jclass htmlHTMLEleCls;
			static jclass iframeEleCls;
			static jclass imageEleCls;
			static jclass inputEleCls;
			static jclass isIndexEleCls;
			static jclass labelEleCls;
			static jclass legendEleCls;
			static jclass liEleCls;
			static jclass linkEleCls;
			static jclass mapEleCls;
			static jclass menuEleCls;
			static jclass metaEleCls;
			static jclass modEleCls;
			static jclass objEleCls;
			static jclass oListEleCls;
			static jclass optGrpEleCls;
			static jclass optEleCls;
			static jclass optColEleCls;
			static jclass paraEleCls;
			static jclass paramEleCls;
			static jclass preEleCls;
			static jclass quoteEleCls;
			static jclass scriptEleCls;
			static jclass selEleCls;
			static jclass styleEleCls;
			static jclass tableCapEleCls;
			static jclass tableCellEleCls;
			static jclass tableColEleCls;
			static jclass tableEleCls;
			static jclass tableRowEleCls;
			static jclass tableSelEleCls;
			static jclass textAreaEleCls;
			static jclass titleEleCls;
			static jclass uListEleCls;
			static jclass htmlEleCls;
#endif //JREX_DOM_HTML2

			static jmethodID nodeCID;
			static jmethodID nodeMapCID;
			static jmethodID nodeListCID;
			static jmethodID domImplCID;
			static jmethodID domExpCID;
			static jmethodID rangeExpCID;
			static jmethodID rangeCID;
			static jmethodID docRangeCID;
			static jmethodID evtExpCID;
			static jmethodID evtTargetCID;
			static jmethodID docEventCID;
			static jmethodID domEventCID;
			static jmethodID evtListnHndlEvtMID;
			static jmethodID usrDataHndlMID;
			static jmethodID abstractViewCID;
			static jmethodID documentViewCID;
			static jmethodID docTravCID;
			static jmethodID nodeItrCID;
			static jmethodID treeWkrCID;
			static jmethodID domCfgCID;
			static jmethodID domStrListCID;
			static jmethodID nodeFilterAcptMID;

#if defined(JREX_DOM_HTML2)
			static jmethodID colctEleCID;
			static jmethodID colOptctEleCID;
#endif //JREX_DOM_HTML2
			static jfieldID nodePeerID;
			static jfieldID nodeListPeerID;
			static jfieldID nodeMapPeerID;
			static jfieldID domImplPeerID;
			static jfieldID rangePeerID;
			static jfieldID docRangePeerID;
			static jfieldID evtTargetPeerID;
			static jfieldID docEventPeerID;
			static jfieldID domEventPeerID;
			static jfieldID abstractViewPeerID;
			static jfieldID documentViewPeerID;
			static jfieldID docTravPeerID;
			static jfieldID nodeItrPeerID;
			static jfieldID treeWkrPeerID;
			static jfieldID domCfgPeerID;
			static jfieldID domStrListPeerID;
#if defined(JREX_DOM_HTML2)
			static jfieldID colctElePeerID;
			static jfieldID colOptctElePeerID;
#endif //JREX_DOM_HTML2

			static PRBool sIntialized;

			static jboolean Intialize(JNIEnv*);
			static void UnIntialize(JNIEnv*);
			static jobject CreateNodeByType(JNIEnv*, nsIDOMNode *node);
			static jobject CreateNodeByType(JNIEnv*, nsIDOMNode *node, PRBool addRef);
			static jobject CreateNodeMap(JNIEnv* env, nsIDOMNamedNodeMap *nodeMap);
			static jobject CreateNodeList(JNIEnv* env, nsIDOMNodeList *nodeList);
			static jobject CreateDOMImpl(JNIEnv* env, nsIDOMDOMImplementation *domImpl);
			static jobject CreateDocumentRange(JNIEnv* env,  nsIDOMDocumentRange *docRange);
			static jobject CreateRange(JNIEnv* env, nsIDOMRange *range);
			static jobject CreateRange(JNIEnv* env, nsIDOMRange *range, PRBool addRef);
			static jobject CreateEventTarget(JNIEnv* env, nsIDOMEventTarget *evtTarget);
			static jobject CreateDocumentEvent(JNIEnv* env, nsIDOMDocumentEvent *docEvent);
			static jobject CreateDOMEvent(JNIEnv* env, nsIDOMEvent *event);
			static jobject CreateAbstractView(JNIEnv* env, nsIDOMAbstractView *view);
			static jobject CreateDocumentView(JNIEnv* env, nsIDOMDocumentView *view);
			static jobject CreateDocumentTraversal(JNIEnv* env, nsIDOMDocumentTraversal *docTrav);
			static jobject CreateNodeIterator(JNIEnv* env, nsIDOMNodeIterator *nodeItr);
			static jobject CreateTreeWalker(JNIEnv* env, nsIDOMTreeWalker *treeWkr);
			static jobject CreateDOMConfiguration(JNIEnv* env, nsIDOMDOMConfiguration *domCfg);
			static jobject CreateDOMStringList(JNIEnv* env, nsIDOMDOMStringList *domStrList);
#if defined(JREX_DOM_HTML2)
			static jobject CreateHTMLCollection(JNIEnv* env, nsIDOMHTMLCollection *htmlCol);
			static jobject CreateHTMLOptionsCollection(JNIEnv* env, nsIDOMHTMLOptionsCollection *htmlOptCol);
#endif //JREX_DOM_HTML2
			static void ThrowDOMException(JNIEnv *env, nsresult errorCode);
			static void ThrowRangeException(JNIEnv *env, nsresult errorCode);
			static void ThrowEventException(JNIEnv *env, nsresult errorCode);

			//event types for JRexDOM
			enum JRexDOMEventTypes{	JREX_CREATE_NODE_BY_TYPE=0U, JREX_RELEASE, JREX_NODE_PAIR_PUT, JREX_NODE_PAIR_DELETE};

			static void* PR_CALLBACK HandleJRexDOMEvent(PLEvent* aEvent);
			static void PR_CALLBACK DestroyJRexDOMEvent(PLEvent* aEvent);

			static nsDataHashtable<nsISupportsHashKey,jobject> *nodeJPair;

		private :
			static const char* const DOM_EXP_CODE_MESSAGE[];
			static const char* const RANGE_EXP_CODE_MESSAGE[];
			static const char* const EVENT_EXP_CODE_MESSAGE;
#if defined(JREX_DOM_HTML2)
			static jclass GetHTMLElementClass(nsIDOMHTMLElement *htmlEle);
#endif //JREX_DOM_HTML2
			static jobject CreateNodeByTypeInternal(JNIEnv *env, nsIDOMNode *node, PRBool addRef);
	};

		inline nsresult ExecInEventQDOM(void* target, PRUint16 eventType,void* eventData, PRBool isSync,
								PLHandleEventProc handler, PLDestroyEventProc destructor, void** _result){
			JREX_LOGLN("ExecInEventQDOM()--> **** eventType<"<<eventType<<">  eventData<"<<eventData<<">****")
			if(!gXpcomRunning)return NS_OK;
			if(isSync)
				NS_ENSURE_ARG_POINTER(_result);

			JRexBasicEvent* event = new JRexBasicEvent;
			nsresult rv;
			if (event) {
				JREX_LOGLN("ExecInEventQDOM()--> **** gEventQ JRexBasicEvent Created ****")
				rv=gEventQ->InitEvent(NS_REINTERPRET_CAST(PLEvent*, event),
											nsnull,handler,destructor);
				JREX_LOGLN("ExecInEventQDOM()--> **** gEventQ InitEvent rv<"<<rv<<">  ****")
				if(NS_SUCCEEDED(rv)){
					event->target=target;
					event->eventType=eventType;
					event->eventData=eventData;
					rv = gEventQ->EnterMonitor();
					if (NS_SUCCEEDED(rv)){
						if(isSync){
							void* rVal;
							rv = gEventQ->PostSynchronousEvent(NS_REINTERPRET_CAST(PLEvent*, event),&rVal);
							JREX_LOGLN("ExecInEventQDOM()--> **** gEventQ  PostSynchronousEvent rv<"<<rv<<"> rVal<"<<rVal<<"> ****")
							if(NS_SUCCEEDED(rv))
								*_result=rVal;
						}else{
							rv = gEventQ->PostEvent(NS_REINTERPRET_CAST(PLEvent*, event));
							JREX_LOGLN("ExecInEventQDOM()--> **** gEventQ  PostEvent rv<"<<rv<<"> ****")
						}
					}
					gEventQ->ExitMonitor();
				}
				if (NS_FAILED(rv)){
					JREX_LOGLN("ExecInEventQDOM()--> **** POSTING EVENT FAILED rv<"<<rv<<"> ****")
					PR_DELETE(event);
				}
			}else
				rv=NS_ERROR_OUT_OF_MEMORY;
			JREX_LOGLN("ExecInEventQDOM()--> **** returning rv<"<<rv<<"> ****")
			return rv;
	}

#define SAFE_RELEASE(obj)			if(IS_EQT){ \
										JRexDOMGlobals::nodeJPair->Remove(obj); \
										NS_IF_RELEASE(obj); \
									}else{ \
										nsresult srv=NS_OK; \
										ExecInEventQDOM(obj, JRexDOMGlobals::JREX_RELEASE, nsnull, PR_TRUE, JRexDOMGlobals::HandleJRexDOMEvent, JRexDOMGlobals::DestroyJRexDOMEvent, (void**)&srv); \
									}

#define SAFE_PUT(obj,data)	  	    if(IS_EQT){ \
										JRexDOMGlobals::nodeJPair->Put(obj,data); \
									}else{ \
										nsresult srv=NS_OK; \
										ExecInEventQDOM(obj, JRexDOMGlobals::JREX_NODE_PAIR_PUT, (void*)data, PR_TRUE, JRexDOMGlobals::HandleJRexDOMEvent, JRexDOMGlobals::DestroyJRexDOMEvent, (void**)&srv); \
									}

#define GET_DOM_STRING_EQT(env, ele, funct, mjrv) \
									JNIEnv *myenv=IS_NULL(env)?JRex_GetEnv(0):env; \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										nsEmbedString retString;  \
										tempJrv->rv = ele->funct(retString);  \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
										NS_STR_TO_JSTR(myenv,retString,tempJrv->jobj) \
										mjrv=tempJrv; \
									}


#define GET_DOM_STRING_JNI(env , jele, eleType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return NULL; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
									if(IS_NULL(thisEle)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
										return NULL; \
									} \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										GET_DOM_STRING_EQT(env, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										jobject jobj=jrv->jobj; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
											return NULL; \
										} \
										return (jstring)jobj; \
									} \
									JREX_CATCH(env) \
									return NULL;

#define SET_DOM_STRING_EQT(strval, ele, funct, mjrv) \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										nsEmbedString tval(strval); \
										tempJrv->rv = ele->funct(tval); \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****") \
										tempJrv->jobj=NULL; \
										mjrv=tempJrv; \
									}

#define SET_DOM_STRING_JNI(env , jele, jstrVal, eleType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
									if(IS_NULL(thisEle)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
										return; \
									} \
									if (IS_NULL(jstrVal)){ \
										JREX_LOGLN(#funct"()--> **** "#jstrVal" is NULL ****") \
										return; \
									}						 \
									PRUnichar* value=nsnull; \
									JSTR_TO_NEW_PRUNI(env, jstrVal, value); \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										SET_DOM_STRING_EQT(value, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, (void*)value, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
										} \
									} \
									JREX_CATCH(env)

#define GET_DOM_BOOL_EQT(env, ele, funct, mjrv) \
								JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
								if(NOT_NULL(tempJrv)){ \
									PRBool retBool = PR_FALSE; \
									tempJrv->rv = ele->funct(&retBool);  \
									JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
									if(NS_SUCCEEDED(tempJrv->rv)) \
										tempJrv->jobj=(jobject)(retBool==PR_TRUE?JNI_TRUE:JNI_FALSE); \
									mjrv=tempJrv; \
								}


#define GET_DOM_BOOL_JNI(env , jele, eleType, funct, eid, peerID, throwsDOMExp) 	\
								if(!JRexDOMGlobals::sIntialized)return JNI_FALSE; \
								JREX_TRY \
								nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
								JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
								if(IS_NULL(thisEle)){  \
									ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
									return JNI_FALSE; \
								} \
								JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
								if(IS_EQT){ \
									JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
									GET_DOM_BOOL_EQT(env, thisEle, funct, jrv) \
								}else{ \
									nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
													HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
									JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
								} \
								JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
								if(NOT_NULL(jrv)){ \
									nsresult rv=jrv->rv; \
									jobject jobj=jrv->jobj; \
									delete jrv; \
									if(NS_FAILED(rv)){ \
										if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
											JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
											JRexDOMGlobals::ThrowDOMException(env, rv); \
										}else{ \
											JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
											ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
										} \
										return JNI_FALSE; \
									} \
									return (jboolean)NS_PTR_TO_INT32(jobj); \
								} \
								JREX_CATCH(env) \
								return JNI_FALSE;


#define SET_DOM_BOOL_EQT(boolval, ele, funct, mjrv) \
								JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
								if(NOT_NULL(tempJrv)){ \
									tempJrv->rv = ele->funct(boolval); \
									JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****") \
									tempJrv->jobj=NULL; \
									mjrv=tempJrv; \
								}

#define SET_DOM_BOOL_JNI(env , jele, jboolVal, eleType, funct, eid, peerID, throwsDOMExp) 	\
								if(!JRexDOMGlobals::sIntialized)return; \
								JREX_TRY \
								nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
								JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
								if(IS_NULL(thisEle)){  \
									ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
									return; \
								} \
								JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
								if(IS_EQT){ \
									JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
									SET_DOM_BOOL_EQT((jboolVal==JNI_TRUE?PR_TRUE:PR_FALSE), thisEle, funct, jrv) \
								}else{ \
									nsresult rv=ExecInEventQDOM(thisEle, eid, (void*)(jboolVal==JNI_TRUE?PR_TRUE:PR_FALSE), PR_TRUE, \
													HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
									JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
								} \
								JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
								if(NOT_NULL(jrv)){ \
									nsresult rv=jrv->rv; \
									delete jrv; \
									if(NS_FAILED(rv)){ \
										if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
											JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
											JRexDOMGlobals::ThrowDOMException(env, rv); \
										}else{ \
											JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
											ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
										} \
									} \
								} \
								JREX_CATCH(env)
#define GET_DOM_INT_EQT(env, ele, intType, funct, mjrv) \
								JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
								if(NOT_NULL(tempJrv)){ \
									intType retVal = 0; \
									tempJrv->rv = ele->funct(&retVal);  \
									JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
									if(NS_SUCCEEDED(tempJrv->rv)) \
										tempJrv->jobj=(jobject)retVal; \
									mjrv=tempJrv; \
								}


#define GET_DOM_INT_JNI(env , jele, eleType, intType, funct, eid, peerID, throwsDOMExp) 	\
								if(!JRexDOMGlobals::sIntialized)return 0; \
								JREX_TRY \
								nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
								JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
								if(IS_NULL(thisEle)){  \
									ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
									return 0; \
								} \
								JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
								if(IS_EQT){ \
									JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
									GET_DOM_INT_EQT(env, thisEle, intType, funct, jrv) \
								}else{ \
									nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
													HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
									JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
								} \
								JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
								if(NOT_NULL(jrv)){ \
									nsresult rv=jrv->rv; \
									jobject jobj=jrv->jobj; \
									delete jrv; \
									if(NS_FAILED(rv)){ \
										if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
											JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
											JRexDOMGlobals::ThrowDOMException(env, rv); \
										}else{ \
											JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
											ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
										} \
										return 0; \
									} \
									return (jint)NS_PTR_TO_INT32(jobj); \
								} \
								JREX_CATCH(env) \
								return 0;


#define SET_DOM_INT_EQT(intval, ele, funct, mjrv) \
								JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
								if(NOT_NULL(tempJrv)){ \
									tempJrv->rv = ele->funct(intval); \
									JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****") \
									tempJrv->jobj=NULL; \
									mjrv=tempJrv; \
								}

#define SET_DOM_INT_JNI(env , jele, intType, jintval, eleType, funct, eid, peerID, throwsDOMExp) 	\
								if(!JRexDOMGlobals::sIntialized)return; \
								JREX_TRY \
								nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
								JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
								if(IS_NULL(thisEle)){  \
									ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
									return; \
								} \
								JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
								if(IS_EQT){ \
									JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
									SET_DOM_INT_EQT((intType)jintval, thisEle, funct, jrv) \
								}else{ \
									nsresult rv=ExecInEventQDOM(thisEle, eid, (void*)jintval, PR_TRUE, \
													HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
									JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
								} \
								JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
								if(NOT_NULL(jrv)){ \
									nsresult rv=jrv->rv; \
									delete jrv; \
									if(NS_FAILED(rv)){ \
										if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
											JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
											JRexDOMGlobals::ThrowDOMException(env, rv); \
										}else{ \
											JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
											ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
										} \
									} \
								} \
								JREX_CATCH(env)


#define CALL_DOM_EQT(ele, funct, mjrv) \
								JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
								if(NOT_NULL(tempJrv)){ \
									tempJrv->rv = ele->funct(); \
									JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****") \
									tempJrv->jobj=NULL; \
									mjrv=tempJrv; \
								}
#define CALL_DOM_JNI(env , jele, eleType, funct, eid, peerID, throwsDOMExp) 	\
								if(!JRexDOMGlobals::sIntialized)return; \
								JREX_TRY \
								nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
								JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
								if(IS_NULL(thisEle)){  \
									ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
									return; \
								} \
								JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
								if(IS_EQT){ \
									JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
									CALL_DOM_EQT(thisEle, funct, jrv) \
								}else{ \
									nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
													HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
									JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
								} \
								JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
								if(NOT_NULL(jrv)){ \
									nsresult rv=jrv->rv; \
									delete jrv; \
									if(NS_FAILED(rv)){ \
										if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
											JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
											JRexDOMGlobals::ThrowDOMException(env, rv); \
										}else{ \
											JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
											ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
										} \
									} \
								} \
								JREX_CATCH(env)

#define GET_DOM_HTML_COL_EQT(env, ele, funct, mjrv) \
									JNIEnv *myenv=IS_NULL(env)?JRex_GetEnv(0):env; \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										nsCOMPtr<nsIDOMHTMLCollection> tmpCol;  \
										tempJrv->rv = ele->funct(getter_AddRefs(tmpCol));  \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
										if(tmpCol) \
											tempJrv->jobj=JRexDOMGlobals::CreateHTMLCollection(myenv, tmpCol.get()); \
										mjrv=tempJrv; \
									}

#define GET_DOM_HTML_COL_JNI(env , jele, eleType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return NULL; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
									if(IS_NULL(thisEle)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
										return NULL; \
									} \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										GET_DOM_HTML_COL_EQT(env, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										jobject jobj=jrv->jobj; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
											return NULL; \
										} \
										return jobj; \
									} \
									JREX_CATCH(env) \
									return NULL;

#define GET_DOM_HTML_OPT_COL_EQT(env, ele, funct, mjrv) \
									JNIEnv *myenv=IS_NULL(env)?JRex_GetEnv(0):env; \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										nsCOMPtr<nsIDOMHTMLOptionsCollection> tmpCol;  \
										tempJrv->rv = ele->funct(getter_AddRefs(tmpCol));  \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
										if(tmpCol) \
											tempJrv->jobj=JRexDOMGlobals::CreateHTMLOptionsCollection(myenv, tmpCol.get()); \
										mjrv=tempJrv; \
									}

#define GET_DOM_HTML_OPT_COL_JNI(env , jele, eleType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return NULL; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
									if(IS_NULL(thisEle)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
										return NULL; \
									} \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										GET_DOM_HTML_OPT_COL_EQT(env, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										jobject jobj=jrv->jobj; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
											return NULL; \
										} \
										return jobj; \
									} \
									JREX_CATCH(env) \
									return NULL;

#define GET_DOM_HTML_ELE_EQT(retType, env, ele, funct, mjrv) \
									JNIEnv *myenv=IS_NULL(env)?JRex_GetEnv(0):env; \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										nsCOMPtr<nsIDOM##retType> tmpEle;  \
										tempJrv->rv = ele->funct(getter_AddRefs(tmpEle));  \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****")  \
										if(tmpEle) \
											tempJrv->jobj=JRexDOMGlobals::CreateNodeByType(myenv, tmpEle.get()); \
										mjrv=tempJrv; \
									}

#define GET_DOM_HTML_ELE_JNI(env , jele, eleType, retType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return NULL; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> ****")  \
									if(IS_NULL(thisEle)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle DOES NOT EXIST!!! ****",0);  \
										return NULL; \
									} \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										GET_DOM_HTML_ELE_EQT(retType, env, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, nsnull, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										jobject jobj=jrv->jobj; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
											return NULL; \
										} \
										return jobj; \
									} \
									JREX_CATCH(env) \
									return NULL;

#define SET_DOM_HTML_ELE_EQT(eleVal, ele, funct, mjrv) \
									JREX_JNI_UTIL::JRexCommonJRV *tempJrv=new JREX_JNI_UTIL::JRexCommonJRV;  \
									if(NOT_NULL(tempJrv)){ \
										tempJrv->rv = ele->funct(eleVal); \
										JREX_LOGLN(#funct"Internal()--> **** "#funct" rv<"<<tempJrv->rv<<"> ****") \
										tempJrv->jobj=NULL; \
										mjrv=tempJrv; \
									}

#define SET_DOM_HTML_ELE_JNI(env , jele, eleType, jeleVal, eleValType, funct, eid, peerID, throwsDOMExp) 	\
									if(!JRexDOMGlobals::sIntialized)return; \
									JREX_TRY \
									nsIDOM##eleType* thisEle=(nsIDOM##eleType*)NS_INT32_TO_PTR(env->GetIntField(jele, peerID));  \
									nsIDOMHTMLElement* eleVal=(nsIDOMHTMLElement*)NS_INT32_TO_PTR(env->GetIntField(jeleVal, JRexDOMGlobals::nodePeerID));\
									JREX_LOGLN(#funct"()--> **** thisEle <"<<thisEle<<"> eleVal <"<<eleVal<<"> ****")  \
									if(IS_NULL(thisEle) || IS_NULL(eleVal)){  \
										ThrowJRexException(env, #funct"()--> **** thisEle/eleVal DOES NOT EXIST!!! ****",0);  \
										return; \
									} \
									JREX_JNI_UTIL::JRexCommonJRV *jrv=NULL; \
									if(IS_EQT){ \
										JREX_LOGLN(#funct"()--> **** IN EVT Q THREAD ****") \
										SET_DOM_HTML_ELE_EQT((nsIDOM##eleValType*)eleVal, thisEle, funct, jrv) \
									}else{ \
										nsresult rv=ExecInEventQDOM(thisEle, eid, (void*)eleVal, PR_TRUE, \
														HandleJRex##eleType##Event, DestroyJRex##eleType##Event, (void**)&jrv); \
										JREX_LOGLN(#funct"()--> **** ExecInEventQDOM rv<"<<rv<<"> ****") \
									} \
									JREX_LOGLN(#funct"()--> **** jrv<"<<jrv<<"> ****") \
									if(NOT_NULL(jrv)){ \
										nsresult rv=jrv->rv; \
										delete jrv; \
										if(NS_FAILED(rv)){ \
											if (throwsDOMExp && (NS_ERROR_GET_MODULE(rv) == NS_ERROR_MODULE_DOM)){ \
												JREX_LOGLN(#funct"()--> **** "#funct" DOM ERROR OCCURED !!!****") \
												JRexDOMGlobals::ThrowDOMException(env, rv); \
											}else{ \
												JREX_LOGLN(#funct"()--> **** "#funct" NON-DOM ERROR OCCURED !!!****") \
												ThrowJRexException(env, "**** "#funct" Failed ****",rv); \
											} \
										} \
									} \
									JREX_CATCH(env)
#endif//#define JRexDOMGlobals_h_
