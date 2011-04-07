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

#if defined(JREX_DOM)

#include "org_mozilla_jrex_selection_JRexSelectionImpl.h"
#include "JRexDOMGlobals.h"
#include "JRexSelection.h"
#include "JRexWindow.h"

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetAnchorNode
 * Signature: (I)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetAnchorNode
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetAnchorNode()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetAnchorNode()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMNode* myNode=nsnull;
    nsresult rv=JRexSelection::GetAnchorNode(window, &myNode);
	JREX_LOGLN("GetAnchorNode()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && myNode){
		JREX_LOGLN("GetAnchorNode()--> *** NOT_NULL myNode ***")
		jobject jobj=JRexDOMGlobals::CreateNodeByType(env, myNode, PR_FALSE);
		return jobj;
	}
	JREX_LOGLN("GetAnchorNode()--> *** GetAnchorNode Failed ***")
  	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetAnchorOffset
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetAnchorOffset
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return 0;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetAnchorOffset()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetAnchorOffset()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 rVal=0;
    nsresult rv=JRexSelection::GetAnchorOffset(window, &rVal);
	JREX_LOGLN("GetAnchorOffset()--> *** rv<"<<rv<<"> rVal<"<<rVal<<">***")
	return (jint)rVal;
  	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetFocusNode
 * Signature: (I)Lorg/w3c/dom/Node;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetFocusNode
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetFocusNode()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetFocusNode()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMNode* myNode=nsnull;
    nsresult rv=JRexSelection::GetFocusNode(window, &myNode);
	JREX_LOGLN("GetFocusNode()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && myNode){
		JREX_LOGLN("GetFocusNode()--> *** NOT_NULL myNode ***")
		jobject jobj=JRexDOMGlobals::CreateNodeByType(env, myNode, PR_FALSE);
		return jobj;
	}
	JREX_LOGLN("GetFocusNode()--> *** GetFocusNode Failed ***")
  	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetFocusOffset
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetFocusOffset
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return 0;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetFocusOffset()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetFocusOffset()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 rVal=0;
    nsresult rv=JRexSelection::GetFocusOffset(window, &rVal);
	JREX_LOGLN("GetFocusOffset()--> *** rv<"<<rv<<"> rVal<"<<rVal<<">***")
	return (jint)rVal;
  	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetIsCollapsed
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetIsCollapsed
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetIsCollapsed()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetIsCollapsed()-->YOU DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool rVal=PR_FALSE;
    nsresult rv=JRexSelection::GetIsCollapsed(window, &rVal);
	JREX_LOGLN("GetIsCollapsed()--> *** rv<"<<rv<<"> rVal<"<<rVal<<">***")
	return (rVal==PR_TRUE?JNI_TRUE:JNI_FALSE);
  	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetRangeCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetRangeCount
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return 0;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetRangeCount()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetRangeCount()-->YOU DO NOT EXIST!!! ****",0);
		return 0;
	}
	PRInt32 rVal=0;
    nsresult rv=JRexSelection::GetRangeCount(window, &rVal);
	JREX_LOGLN("GetRangeCount()--> *** rv<"<<rv<<"> rVal<"<<rVal<<">***")
	return (jint)rVal;
  	JREX_CATCH(env)
	return 0;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    GetRangeAt
 * Signature: (II)Lorg/w3c/dom/ranges/Range;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_GetRangeAt
  (JNIEnv *env, jobject jsel, jint jrexPeer, jint index){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("GetRangeAt()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** GetRangeAt()-->YOU DO NOT EXIST!!! ****",0);
		return NULL;
	}
	nsIDOMRange* myRange=nsnull;
    nsresult rv=JRexSelection::GetRangeAt(window, index, &myRange);
	JREX_LOGLN("GetRangeAt()--> *** rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv) && myRange){
		JREX_LOGLN("GetRangeAt()--> *** NOT_NULL myRange ***")
		jobject jobj=JRexDOMGlobals::CreateRange(env, myRange, PR_FALSE);
		return jobj;
	}
	JREX_LOGLN("GetRangeAt()--> *** GetRangeAt Failed ***")
  	JREX_CATCH(env)
	return NULL;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    Collapse
 * Signature: (ILorg/w3c/dom/Node;I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_Collapse
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jparentNode, jint joffset){
	if(!gXpcomRunning)return;

	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMNode* parentNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jparentNode, JRexDOMGlobals::nodePeerID));

	JREX_LOGLN("Collapse()--> **** JRexWindow <"<<window<<"> parentNode<"<<parentNode<<"> ****")
	if(IS_NULL(window) || IS_NULL(parentNode)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Collapse()-->window/parentNode DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::Collapse(window, parentNode, (PRInt32)joffset);
    JREX_LOGLN("Collapse()--> *** Collapse rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** Collapse() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    Extend
 * Signature: (ILorg/w3c/dom/Node;I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_Extend
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jparentNode , jint joffset){
	if(!gXpcomRunning)return;

	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMNode* parentNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jparentNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("Extend()--> **** JRexWindow <"<<window<<"> parentNode<"<<parentNode<<"> ****")
	if(IS_NULL(window) || IS_NULL(parentNode)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** Extend()-->window/parentNode DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::Extend(window, parentNode, (PRInt32)joffset);
    JREX_LOGLN("Extend()--> *** Extend rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** Extend() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    CollapseToStart
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_CollapseToStart
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("CollapseToStart()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CollapseToStart()-->You DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::CollapseToStart(window);
    JREX_LOGLN("CollapseToStart()--> *** CollapseToStart rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** CollapseToStart() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    CollapseToEnd
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_CollapseToEnd
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("CollapseToEnd()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** CollapseToEnd()-->You DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::CollapseToEnd(window);
    JREX_LOGLN("CollapseToEnd()--> *** CollapseToEnd rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** CollapseToEnd() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    ContainsNode
 * Signature: (ILorg/w3c/dom/Node;Z)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_ContainsNode
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jnode, jboolean jentirelyContained){
	if(!gXpcomRunning)return JNI_FALSE;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMNode* node=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jnode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("ContainsNode()--> **** JRexWindow <"<<window<<"> node<"<<node<<"> ****")
	if(IS_NULL(window) || IS_NULL(node)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** ContainsNode()-->window/node DO NOT EXIST!!! ****",0);
		return JNI_FALSE;
	}
	PRBool rVal=PR_FALSE;
    nsresult rv=JRexSelection::ContainsNode(window, node,
    							(jentirelyContained==JNI_TRUE?PR_TRUE:PR_FALSE), &rVal);
	JREX_LOGLN("ContainsNode()--> *** rv<"<<rv<<"> rVal<"<<rVal<<">***")
	return (rVal==PR_TRUE?JNI_TRUE:JNI_FALSE);
  	JREX_CATCH(env)
	return JNI_FALSE;
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    SelectAllChildren
 * Signature: (ILorg/w3c/dom/Node;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_SelectAllChildren
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jparentNode){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMNode* parentNode=(nsIDOMNode*)NS_INT32_TO_PTR(env->GetIntField(jparentNode, JRexDOMGlobals::nodePeerID));
	JREX_LOGLN("SelectAllChildren()--> **** JRexWindow <"<<window<<"> parentNode<"<<parentNode<<"> ****")
	if(IS_NULL(window) || IS_NULL(parentNode)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SelectAllChildren()-->window/parentNode DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::SelectAllChildren(window, parentNode);
    JREX_LOGLN("SelectAllChildren()--> *** SelectAllChildren rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** SelectAllChildren() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    AddRange
 * Signature: (ILorg/w3c/dom/ranges/Range;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_AddRange
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jrange){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMRange* range=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrange, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("AddRange()--> **** JRexWindow <"<<window<<"> range<"<<range<<"> ****")
	if(IS_NULL(window) || IS_NULL(range)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** AddRange()-->window/range DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::AddRange(window, range);
    JREX_LOGLN("AddRange()--> *** AddRange rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** AddRange() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    RemoveRange
 * Signature: (ILorg/w3c/dom/ranges/Range;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_RemoveRange
  (JNIEnv *env, jobject jsel, jint jrexPeer, jobject jrange){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	nsIDOMRange* range=(nsIDOMRange*)NS_INT32_TO_PTR(env->GetIntField(jrange, JRexDOMGlobals::rangePeerID));
	JREX_LOGLN("RemoveRange()--> **** JRexWindow <"<<window<<"> range<"<<range<<"> ****")
	if(IS_NULL(window) || IS_NULL(range)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveRange()-->window/range DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::RemoveRange(window, range);
    JREX_LOGLN("RemoveRange()--> *** RemoveRange rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** RemoveRange() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    RemoveAllRanges
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_RemoveAllRanges
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("RemoveAllRanges()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** RemoveAllRanges()-->You DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::RemoveAllRanges(window);
    JREX_LOGLN("RemoveAllRanges()--> *** RemoveAllRanges rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** RemoveAllRanges() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    DeleteFromDocument
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_DeleteFromDocument
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("DeleteFromDocument()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** DeleteFromDocument()-->You DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::DeleteFromDocument(window);
    JREX_LOGLN("DeleteFromDocument()--> *** DeleteFromDocument rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** DeleteFromDocument() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    SelectionLanguageChange
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_SelectionLanguageChange
  (JNIEnv *env, jobject jsel, jint jrexPeer, jboolean jlangRTL){
	if(!gXpcomRunning)return;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("SelectionLanguageChange()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** SelectionLanguageChange()-->You DO NOT EXIST!!! ****",0);
		return;
	}
    nsresult rv=JRexSelection::SelectionLanguageChange(window, (jlangRTL==JNI_TRUE?PR_TRUE:PR_FALSE));
    JREX_LOGLN("SelectionLanguageChange()--> *** SelectionLanguageChange rv<"<<rv<<"> ***")
	if(NS_FAILED(rv))
    	ThrowJRexException(env, "**** SelectionLanguageChange() Falied!!! ****",rv);
  	JREX_CATCH(env)
}

/*
 * Class:     org_mozilla_jrex_selection_JRexSelectionImpl
 * Method:    ToString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_jrex_selection_JRexSelectionImpl_ToString
  (JNIEnv *env, jobject jsel, jint jrexPeer){
	if(!gXpcomRunning)return NULL;
	JREX_TRY
	JRexWindow *window=(JRexWindow *)NS_INT32_TO_PTR(jrexPeer);
	JREX_LOGLN("ToString()--> **** JRexWindow <"<<window<<"> ****")
	if(IS_NULL(window)
				|| JRexWindow::IsWindowAvailable(window)==PR_FALSE){
		ThrowJRexException(env, "**** ToString()-->You DO NOT EXIST!!! ****",0);
		return NULL;
	}
	PRUnichar *tmpStr=nsnull;
    nsresult rv=JRexSelection::ToString(window, &tmpStr);
    JREX_LOGLN("ToString()--> *** ToString rv<"<<rv<<"> ***")
	if(NS_FAILED(rv)){
    	ThrowJRexException(env, "**** ToString() Falied!!! ****",rv);
		return NULL;
	}
	nsEmbedString str(tmpStr);
	NS_STR_TO_JSTR_RET(env, str)
  	JREX_CATCH(env)
  	return NULL;
}

#endif //JREX_DOM