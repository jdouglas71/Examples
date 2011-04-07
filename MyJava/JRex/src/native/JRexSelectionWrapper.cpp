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

	#include "JRexSelection.h"

	inline nsresult GetAnchorNodeInternal(JRexWindow *window, nsIDOMNode * *aAnchorNode){
		JREX_LOGLN("GetAnchorNodeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetAnchorNodeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetAnchorNode(aAnchorNode);
			JREX_LOGLN("GetAnchorNodeInternal --> **** GetAnchorNode rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetAnchorOffsetInternal(JRexWindow *window, PRInt32 *aAnchorOffset){
		JREX_LOGLN("GetAnchorOffsetInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetAnchorOffsetInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetAnchorOffset(aAnchorOffset);
			JREX_LOGLN("GetAnchorOffsetInternal --> **** GetAnchorOffset rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetFocusNodeInternal(JRexWindow *window, nsIDOMNode * *aFocusNode){
		JREX_LOGLN("GetFocusNodeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetFocusNodeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetFocusNode(aFocusNode);
			JREX_LOGLN("GetFocusNodeInternal --> **** GetFocusNode rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetFocusOffsetInternal(JRexWindow *window, PRInt32 *aFocusOffset){
		JREX_LOGLN("GetFocusOffsetInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetFocusOffsetInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetFocusOffset(aFocusOffset);
			JREX_LOGLN("GetFocusOffsetInternal --> **** GetFocusOffset rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetIsCollapsedInternal(JRexWindow *window, PRBool *aIsCollapsed){
		JREX_LOGLN("GetIsCollapsedInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetIsCollapsedInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetIsCollapsed(aIsCollapsed);
			JREX_LOGLN("GetIsCollapsedInternal --> **** GetIsCollapsed rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetRangeCountInternal(JRexWindow *window, PRInt32 *aRangeCount){
		JREX_LOGLN("GetRangeCountInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetRangeCountInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetRangeCount(aRangeCount);
			JREX_LOGLN("GetRangeCountInternal --> **** GetRangeCount rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult GetRangeAtInternal(JRexWindow *window, PRInt32 index, nsIDOMRange **_retval){
		JREX_LOGLN("GetRangeAtInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("GetRangeAtInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->GetRangeAt(index, _retval);
			JREX_LOGLN("GetRangeAtInternal --> **** GetRangeAt rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult CollapseInternal(JRexWindow *window, nsIDOMNode *parentNode, PRInt32 offset){
		JREX_LOGLN("CollapseInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("CollapseInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->Collapse(parentNode, offset);
			JREX_LOGLN("CollapseInternal --> **** Collapse rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult ExtendInternal(JRexWindow *window, nsIDOMNode *parentNode, PRInt32 offset){
		JREX_LOGLN("ExtendInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("ExtendInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->Extend(parentNode, offset);
			JREX_LOGLN("ExtendInternal --> **** Extend rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult CollapseToStartInternal(JRexWindow *window){
		JREX_LOGLN("CollapseToStartInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("CollapseToStartInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->CollapseToStart();
			JREX_LOGLN("CollapseToStartInternal --> **** CollapseToStart rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult CollapseToEndInternal(JRexWindow *window){
		JREX_LOGLN("CollapseToEndInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("CollapseToEndInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->CollapseToEnd();
			JREX_LOGLN("CollapseToEndInternal --> **** CollapseToEnd rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult ContainsNodeInternal(JRexWindow *window, nsIDOMNode *node, PRBool entirelyContained, PRBool *_retval){
		JREX_LOGLN("ContainsNodeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("ContainsNodeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->ContainsNode(node, entirelyContained, _retval);
			JREX_LOGLN("ContainsNodeInternal --> **** ContainsNode rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult SelectAllChildrenInternal(JRexWindow *window, nsIDOMNode *parentNode){
		JREX_LOGLN("SelectAllChildrenInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("SelectAllChildrenInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->SelectAllChildren(parentNode);
			JREX_LOGLN("SelectAllChildrenInternal --> **** SelectAllChildren rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult AddRangeInternal(JRexWindow *window, nsIDOMRange *range){
		JREX_LOGLN("AddRangeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("AddRangeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->AddRange(range);
			JREX_LOGLN("AddRangeInternal --> **** AddRange rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult RemoveRangeInternal(JRexWindow *window, nsIDOMRange *range){
		JREX_LOGLN("RemoveRangeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("RemoveRangeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->RemoveRange(range);
			JREX_LOGLN("RemoveRangeInternal --> **** RemoveRange rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult RemoveAllRangesInternal(JRexWindow *window){
		JREX_LOGLN("RemoveAllRangesInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("RemoveAllRangesInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->RemoveAllRanges();
			JREX_LOGLN("RemoveAllRangesInternal --> **** RemoveAllRanges rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult DeleteFromDocumentInternal(JRexWindow *window){
		JREX_LOGLN("DeleteFromDocumentInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("DeleteFromDocumentInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->DeleteFromDocument();
			JREX_LOGLN("DeleteFromDocumentInternal --> **** DeleteFromDocument rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult SelectionLanguageChangeInternal(JRexWindow *window, PRBool langRTL){
		JREX_LOGLN("SelectionLanguageChangeInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("SelectionLanguageChangeInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->SelectionLanguageChange(langRTL);
			JREX_LOGLN("SelectionLanguageChangeInternal --> **** SelectionLanguageChange rv"<<rv<<" ****")
		}
		return rv;
	}

	inline nsresult ToStringInternal(JRexWindow *window, PRUnichar **_retval){
		JREX_LOGLN("ToStringInternal --> **** window"<<window<<" ****")
		nsCOMPtr<nsISelection> selection;
		nsresult rv=window->GetSelection(getter_AddRefs(selection));
		JREX_LOGLN("ToStringInternal --> **** GetSelection rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv) && selection){
			rv=selection->ToString(_retval);
			JREX_LOGLN("ToStringInternal --> **** ToString rv"<<rv<<" ****")
		}
		return rv;
	}


	nsresult JRexSelection::GetAnchorNode(JRexWindow *window, nsIDOMNode * *aAnchorNode){
		JREX_LOGLN("GetAnchorNode --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aAnchorNode);
		if(IS_EQT)return GetAnchorNodeInternal(window, aAnchorNode);
		nsIDOMNode *temp=nsnull;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_ANCHR_NODE,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&temp);
		JREX_LOGLN("GetAnchorNode()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*aAnchorNode=temp;
		return rv;
	}

	nsresult JRexSelection::GetAnchorOffset(JRexWindow *window, PRInt32 *aAnchorOffset){
		JREX_LOGLN("GetAnchorOffset --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aAnchorOffset);
		if(IS_EQT)return GetAnchorOffsetInternal(window, aAnchorOffset);
		PRInt32 rVal=0;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_ANCHR_OFFSET,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&rVal);
		JREX_LOGLN("GetAnchorOffset()--> **** ExecInEventQ rv<"<<rv<<"> rVal<"<<rVal<<">****")
		if(NS_SUCCEEDED(rv))
			*aAnchorOffset=rVal;
		return rv;
	}

	nsresult JRexSelection::GetFocusNode(JRexWindow *window, nsIDOMNode * *aFocusNode){
		JREX_LOGLN("GetFocusNode --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aFocusNode);
		if(IS_EQT)return GetFocusNodeInternal(window, aFocusNode);
		nsIDOMNode *temp=nsnull;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_FOCUS_NODE,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&temp);
		JREX_LOGLN("GetFocusNode()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*aFocusNode=temp;
		return rv;
	}

	nsresult JRexSelection::GetFocusOffset(JRexWindow *window, PRInt32 *aFocusOffset){
		JREX_LOGLN("GetFocusOffset --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aFocusOffset);
		if(IS_EQT)return GetFocusOffsetInternal(window, aFocusOffset);
		PRInt32 rVal=0;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_FOCUS_OFFSET,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&rVal);
		JREX_LOGLN("GetFocusOffset()--> **** ExecInEventQ rv<"<<rv<<"> rVal<"<<rVal<<">****")
		if(NS_SUCCEEDED(rv))
			*aFocusOffset=rVal;
		return rv;
	}

	nsresult JRexSelection::GetIsCollapsed(JRexWindow *window, PRBool *aIsCollapsed){
		JREX_LOGLN("GetIsCollapsed --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aIsCollapsed);
		if(IS_EQT)return GetIsCollapsedInternal(window, aIsCollapsed);
		PRBool rVal=PR_FALSE;
		nsresult rv=ExecInEventQ(window,JREX_SEL_IS_COLLAPSED,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&rVal);
		JREX_LOGLN("GetIsCollapsed()--> **** ExecInEventQ rv<"<<rv<<"> rVal<"<<rVal<<">****")
		if(NS_SUCCEEDED(rv))
			*aIsCollapsed=rVal;
		return rv;
	}

	nsresult JRexSelection::GetRangeCount(JRexWindow *window, PRInt32 *aRangeCount){
		JREX_LOGLN("GetRangeCount --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(aRangeCount);
		if(IS_EQT)return GetRangeCountInternal(window, aRangeCount);
		PRInt32 rVal=0;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_RANGE_COUNT,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&rVal);
		JREX_LOGLN("GetRangeCount()--> **** ExecInEventQ rv<"<<rv<<"> rVal<"<<rVal<<">****")
		if(NS_SUCCEEDED(rv))
			*aRangeCount=rVal;
		return rv;
	}

	nsresult JRexSelection::GetRangeAt(JRexWindow *window, PRInt32 index, nsIDOMRange **_retval){
		JREX_LOGLN("GetRangeAt --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(_retval);
		if(IS_EQT)return GetRangeAtInternal(window,index, _retval);
		nsIDOMRange *temp=nsnull;
		nsresult rv=ExecInEventQ(window,JREX_SEL_GET_RANGE_AT,(void*)index,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&temp);
		JREX_LOGLN("GetRangeAt()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*_retval=temp;
		return rv;

	}

	nsresult JRexSelection::Collapse(JRexWindow *window, nsIDOMNode *parentNode, PRInt32 offset){
		JREX_LOGLN("Collapse --> **** window"<<window<<" ****")
		if(IS_EQT)return CollapseInternal(window, parentNode, offset);
		NodeEventData *evtData= new NodeEventData;
		nsresult rv=NS_OK;
		if(evtData){
			evtData->node=parentNode;
			evtData->intVal=offset;
			rv=ExecInEventQ(window,JREX_SEL_COLLAPSE,(void*)evtData,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
			JREX_LOGLN("Collapse()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	nsresult JRexSelection::Extend(JRexWindow *window, nsIDOMNode *parentNode, PRInt32 offset){
		JREX_LOGLN("Extend --> **** window"<<window<<" ****")
		if(IS_EQT)return ExtendInternal(window, parentNode, offset);
		NodeEventData *evtData= new NodeEventData;
		nsresult rv=NS_OK;
		if(evtData){
			evtData->node=parentNode;
			evtData->intVal=offset;
			rv=ExecInEventQ(window,JREX_SEL_EXTEND,(void*)evtData,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
			JREX_LOGLN("Extend()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	nsresult JRexSelection::CollapseToStart(JRexWindow *window){
		JREX_LOGLN("CollapseToStart --> **** window"<<window<<" ****")
		if(IS_EQT)return CollapseToStartInternal(window);
		nsresult rv=ExecInEventQ(window,JREX_SEL_COLLAPSE_TO_START,nsnull,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("CollapseToStart()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::CollapseToEnd(JRexWindow *window){
		JREX_LOGLN("CollapseToEnd --> **** window"<<window<<" ****")
		if(IS_EQT)return CollapseToEndInternal(window);
		nsresult rv=ExecInEventQ(window,JREX_SEL_COLLAPSE_TO_END,nsnull,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("CollapseToEnd()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::ContainsNode(JRexWindow *window, nsIDOMNode *node, PRBool entirelyContained, PRBool *_retval){
		JREX_LOGLN("ContainsNode --> **** window"<<window<<" ****")
		if(IS_EQT)return ContainsNodeInternal(window, node, entirelyContained,_retval);
		NodeEventData *evtData= new NodeEventData;
		nsresult rv=NS_OK;
		if(evtData){
			evtData->node=node;
			evtData->intVal=entirelyContained;
			rv=ExecInEventQ(window,JREX_SEL_CONTAINS_NODE,(void*)evtData,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
			JREX_LOGLN("ContainsNode()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	nsresult JRexSelection::SelectAllChildren(JRexWindow *window, nsIDOMNode *parentNode){
		JREX_LOGLN("SelectAllChildren --> **** window"<<window<<" ****")
		if(IS_EQT)return SelectAllChildrenInternal(window, parentNode);
		nsresult rv=ExecInEventQ(window,JREX_SEL_ALL_CHILD,(void*)parentNode,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("SelectAllChildren()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::AddRange(JRexWindow *window, nsIDOMRange *range){
		JREX_LOGLN("AddRange --> **** window"<<window<<" ****")
		if(IS_EQT)return AddRangeInternal(window, range);
		nsresult rv=ExecInEventQ(window,JREX_SEL_ADD_RANGE,(void*)range,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("AddRange()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::RemoveRange(JRexWindow *window, nsIDOMRange *range){
		JREX_LOGLN("RemoveRange --> **** window"<<window<<" ****")
		if(IS_EQT)return RemoveRangeInternal(window, range);
		nsresult rv=ExecInEventQ(window,JREX_SEL_REMOVE_RANGE,(void*)range,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("RemoveRange()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::RemoveAllRanges(JRexWindow *window){
		JREX_LOGLN("RemoveAllRanges --> **** window"<<window<<" ****")
		if(IS_EQT)return RemoveAllRangesInternal(window);
		nsresult rv=ExecInEventQ(window,JREX_SEL_REMOVEALL_RANGES,nsnull,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("RemoveAllRanges()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::DeleteFromDocument(JRexWindow *window){
		JREX_LOGLN("DeleteFromDocument --> **** window"<<window<<" ****")
		if(IS_EQT)return DeleteFromDocumentInternal(window);
		nsresult rv=ExecInEventQ(window,JREX_SEL_DELECT_FROM_DOC,nsnull,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("DeleteFromDocument()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::SelectionLanguageChange(JRexWindow *window, PRBool langRTL){
		JREX_LOGLN("SelectionLanguageChange --> **** window"<<window<<" ****")
		if(IS_EQT)return SelectionLanguageChangeInternal(window, langRTL);
		nsresult rv=ExecInEventQ(window,JREX_SEL_LANG_CHANGE,(void*)langRTL,
						PR_FALSE,HandleSelectionEvent,
							DestroySelectionEvent,nsnull);
		JREX_LOGLN("SelectionLanguageChange()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexSelection::ToString(JRexWindow *window, PRUnichar **_retval){
		JREX_LOGLN("ToString --> **** window"<<window<<" ****")
		NS_ENSURE_ARG_POINTER(_retval);
		if(IS_EQT)return ToStringInternal(window, _retval);
		PRUnichar *temp=nsnull;
		nsresult rv=ExecInEventQ(window,JREX_SEL_TO_STRING,nsnull,
						PR_TRUE,HandleSelectionEvent,
							DestroySelectionEvent,(void**)&temp);
		JREX_LOGLN("ToString()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*_retval=temp;
		return rv;
	}

	void* PR_CALLBACK JRexSelection::HandleSelectionEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleSelectionEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case JREX_SEL_GET_ANCHR_NODE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_ANCHR_NODE EVENT!!!****")
				nsIDOMNode *domNode=nsnull;
				rVal->rv=GetAnchorNodeInternal(window, &domNode);
				JREX_LOGLN("HandleSelectionEvent GetAnchorNodeInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=domNode;
				break;
			}
			case JREX_SEL_GET_ANCHR_OFFSET:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_ANCHR_OFFSET EVENT!!!****")
				PRInt32 temp=0;
				rVal->rv=GetAnchorOffsetInternal(window, &temp);
				JREX_LOGLN("HandleSelectionEvent GetAnchorNodeInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=(void*)temp;
				break;
			}
			case JREX_SEL_GET_FOCUS_NODE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_FOCUS_NODE EVENT!!!****")
				nsIDOMNode *domNode=nsnull;
				rVal->rv=GetFocusNodeInternal(window, &domNode);
				JREX_LOGLN("HandleSelectionEvent GetFocusNodeInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=domNode;
				break;
			}
			case JREX_SEL_GET_FOCUS_OFFSET:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_FOCUS_OFFSET EVENT!!!****")
				PRInt32 temp=0;
				rVal->rv=GetFocusOffsetInternal(window, &temp);
				JREX_LOGLN("HandleSelectionEvent GetFocusOffsetInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=(void*)temp;
				break;
			}
			case JREX_SEL_IS_COLLAPSED:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_IS_COLLAPSED EVENT!!!****")
				PRBool temp=PR_FALSE;
				rVal->rv=GetIsCollapsedInternal(window, &temp);
				JREX_LOGLN("HandleSelectionEvent GetIsCollapsedInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=(void*)temp;
				break;
			}
			case JREX_SEL_GET_RANGE_COUNT:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_RANGE_COUNT EVENT!!!****")
				PRInt32 temp=0;
				rVal->rv=GetRangeCountInternal(window, &temp);
				JREX_LOGLN("HandleSelectionEvent GetRangeCountInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=(void*)temp;
				break;
			}
			case JREX_SEL_GET_RANGE_AT:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_GET_RANGE_AT EVENT!!!****")
				nsIDOMRange *range=nsnull;
				rVal->rv=GetRangeAtInternal(window, (PRInt32)event->eventData, &range);
				JREX_LOGLN("HandleSelectionEvent GetRangeAtInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=range;
				break;
			}
			case JREX_SEL_COLLAPSE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_COLLAPSE EVENT!!!****")
				NodeEventData* evtData = NS_REINTERPRET_CAST(NodeEventData*, event->eventData);
				rVal->rv=CollapseInternal(window, evtData->node, evtData->intVal);
				JREX_LOGLN("HandleSelectionEvent CollapseInternal rv<"<<rVal->rv<<">****")
			}
			case JREX_SEL_EXTEND:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_EXTEND EVENT!!!****")
				NodeEventData* evtData = NS_REINTERPRET_CAST(NodeEventData*, event->eventData);
				rVal->rv=ExtendInternal(window, evtData->node, evtData->intVal);
				JREX_LOGLN("HandleSelectionEvent ExtendInternal rv<"<<rVal->rv<<">****")
			}
			case JREX_SEL_COLLAPSE_TO_START:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_COLLAPSE_TO_START EVENT!!!****")
				rVal->rv=CollapseToStartInternal(window);
				JREX_LOGLN("HandleSelectionEvent CollapseToStartInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_COLLAPSE_TO_END:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_COLLAPSE_TO_END EVENT!!!****")
				rVal->rv=CollapseToEndInternal(window);
				JREX_LOGLN("HandleSelectionEvent CollapseToEndInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_CONTAINS_NODE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_CONTAINS_NODE EVENT!!!****")
				NodeEventData* evtData = NS_REINTERPRET_CAST(NodeEventData*, event->eventData);
				PRBool temp=PR_FALSE;
				rVal->rv=ContainsNodeInternal(window, evtData->node, (PRBool)evtData->intVal, &temp);
				JREX_LOGLN("HandleSelectionEvent ContainsNodeInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=(void*)temp;
				break;
			}
			case JREX_SEL_ALL_CHILD:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_ALL_CHILD EVENT!!!****")
				rVal->rv=SelectAllChildrenInternal(window, (nsIDOMNode *)event->eventData);
				JREX_LOGLN("HandleSelectionEvent SelectAllChildrenInternal rv<"<<rVal->rv<<">****")
				break;

			}
			case JREX_SEL_ADD_RANGE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_ADD_RANGE EVENT!!!****")
				rVal->rv=AddRangeInternal(window, (nsIDOMRange *)event->eventData);
				JREX_LOGLN("HandleSelectionEvent AddRangeInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_REMOVE_RANGE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_REMOVE_RANGE EVENT!!!****")
				rVal->rv=RemoveRangeInternal(window, (nsIDOMRange *)event->eventData);
				JREX_LOGLN("HandleSelectionEvent RemoveRangeInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_REMOVEALL_RANGES:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_REMOVEALL_RANGES EVENT!!!****")
				rVal->rv=RemoveAllRangesInternal(window);
				JREX_LOGLN("HandleSelectionEvent RemoveAllRangesInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_DELECT_FROM_DOC:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_DELECT_FROM_DOC EVENT!!!****")
				rVal->rv=DeleteFromDocumentInternal(window);
				JREX_LOGLN("HandleSelectionEvent DeleteFromDocumentInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_LANG_CHANGE:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_LANG_CHANGE EVENT!!!****")
				rVal->rv=SelectionLanguageChangeInternal(window, (PRBool)event->eventData);
				JREX_LOGLN("HandleSelectionEvent SelectionLanguageChangeInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SEL_TO_STRING:
			{
				JREX_LOGLN("HandleSelectionEvent JREX_SEL_TO_STRING EVENT!!!****")
				PRUnichar *temp=nsnull;
				rVal->rv=ToStringInternal(window, &temp);
				JREX_LOGLN("HandleSelectionEvent ToStringInternal rv<"<<rVal->rv<<">****")
				if(NS_SUCCEEDED(rVal->rv))
					rVal->rData=temp;
				break;
			}
			default:
			{
				JREX_LOGLN("HandleSelectionEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleSelectionEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexSelection::DestroySelectionEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroySelectionEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData && (event->eventType==JREX_SEL_COLLAPSE
			|| event->eventType==JREX_SEL_EXTEND || event->eventType==JREX_SEL_CONTAINS_NODE)){
				JREX_LOGLN("DestroySelectionEvent()--> **** deleting evtData ****")
				NodeEventData* evtData = NS_REINTERPRET_CAST(NodeEventData*, event->eventData);
				delete evtData;
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}

#endif //JREX_DOM
