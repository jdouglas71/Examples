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


#include "JRexWindow.h"
#define UNDO_COMMAND            "cmd_undo"
#define REDO_COMMAND            "cmd_redo"
#define DELETE_COMMAND          "cmd_delete"

	nsresult JRexWindow::CanUndoInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		IsCommandEnabled(UNDO_COMMAND, _retval);
		JREX_LOGLN("CanUndoInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return NS_OK;
	}

	nsresult JRexWindow::CanUndo(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanUndo()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanUndoInternal(_retval);
		PRBool canUndo=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_UNDO,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canUndo);
		JREX_LOGLN("CanUndo()--> **** canUndo<"<<(canUndo==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canUndo;
		JREX_LOGLN("CanUndo()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CanRedoInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		IsCommandEnabled(REDO_COMMAND, _retval);
		JREX_LOGLN("CanRedoInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return NS_OK;
	}

	nsresult JRexWindow::CanRedo(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanRedo()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanRedoInternal(_retval);
		PRBool canRedo=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_REDO,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canRedo);
		JREX_LOGLN("CanRedo()--> **** canRedo<"<<(canRedo==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canRedo;
		JREX_LOGLN("CanRedo()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CanCutInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanCutInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanCutSelection(_retval);
			JREX_LOGLN("CanCutInternal()--> **** CanCutSelection rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanCutInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCut(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanCut()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanCutInternal(_retval);
		PRBool canCut=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_CUT,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canCut);
		JREX_LOGLN("CanCut()--> **** canCut<"<<(canCut==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canCut;
		JREX_LOGLN("CanCut()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CanCopyInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanCopyInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanCopySelection(_retval);
			JREX_LOGLN("CanCopyInternal()--> **** CanCopySelection rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanCopyInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopy(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanCopy()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanCopyInternal(_retval);
		PRBool canCopy=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_COPY,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canCopy);
		JREX_LOGLN("CanCopy()--> **** canCopy<"<<(canCopy==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canCopy;
		JREX_LOGLN("CanCopy()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyLinkLocationInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanCopyLinkLocationInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanCopyLinkLocation(_retval);
			JREX_LOGLN("CanCopyLinkLocationInternal()--> **** CanCopyLinkLocation rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanCopyLinkLocationInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyLinkLocation(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanCopyLinkLocation()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanCopyLinkLocationInternal(_retval);
		PRBool canCopy=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_COPY_LINK_LOC,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canCopy);
		JREX_LOGLN("CanCopyLinkLocation()--> **** canCopy<"<<(canCopy==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canCopy;
		JREX_LOGLN("CanCopyLinkLocation()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyImageLocationInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanCopyImageLocationInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanCopyImageLocation(_retval);
			JREX_LOGLN("CanCopyImageLocationInternal()--> **** CanCopyImageLocation rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanCopyImageLocationInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyImageLocation(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanCopyImageLocation()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanCopyImageLocationInternal(_retval);
		PRBool canCopy=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_COPY_IMG_LOC,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canCopy);
		JREX_LOGLN("CanCopyImageLocation()--> **** canCopy<"<<(canCopy==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canCopy;
		JREX_LOGLN("CanCopyImageLocation()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyImageContentsInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanCopyImageContentsInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanCopyImageContents(_retval);
			JREX_LOGLN("CanCopyImageContentsInternal()--> **** CanCopyImageContents rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanCopyImageContentsInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanCopyImageContents(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanCopyImageContents()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanCopyImageContentsInternal(_retval);
		PRBool canCopy=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_COPY_IMG_CONT,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canCopy);
		JREX_LOGLN("CanCopyImageContents()--> **** canCopy<"<<(canCopy==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canCopy;
		JREX_LOGLN("CanCopyImageContents()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CanPasteInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CanPasteInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CanPaste(_retval);
			JREX_LOGLN("CanPasteInternal()--> **** CanPaste rv<"<<rv<<"> ****")
		}
		JREX_LOGLN("CanPasteInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CanPaste(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanPaste()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanPasteInternal(_retval);
		PRBool canPaste=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_PASTE,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canPaste);
		JREX_LOGLN("CanPaste()--> **** canPaste<"<<(canPaste==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canPaste;
		JREX_LOGLN("CanPaste()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CanDeleteInternal(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		IsCommandEnabled(DELETE_COMMAND, _retval);
		JREX_LOGLN("CanDeleteInternal()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return NS_OK;
	}

	nsresult JRexWindow::CanDelete(PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("CanDelete()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return CanDeleteInternal(_retval);
		PRBool canDelete=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_DELETE,nsnull,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&canDelete);
		JREX_LOGLN("CanDelete()--> **** canDelete<"<<(canDelete==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=canDelete;
		JREX_LOGLN("CanDelete()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::UndoInternal(){
		JREX_LOGLN("UndoInternal()--> **** ****")
		DoCommand(UNDO_COMMAND, 0);
		return NS_OK;
	}

	nsresult JRexWindow::Undo(){
		JREX_LOGLN("Undo()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return UndoInternal();
		nsresult rv=ExecInEventQ(this,UNDO,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Undo()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::RedoInternal(){
		JREX_LOGLN("RedoInternal()--> **** ****")
		DoCommand(REDO_COMMAND, 0);
		return NS_OK;
	}

	nsresult JRexWindow::Redo(){
		JREX_LOGLN("Redo()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return RedoInternal();
		nsresult rv=ExecInEventQ(this,REDO,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Redo()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CutInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CutInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CutSelection();
			JREX_LOGLN("CutInternal()--> **** CutSelection rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::Cut(){
		JREX_LOGLN("Cut()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return CutInternal();
		nsresult rv=ExecInEventQ(this,CUT,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Cut()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CopyInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CopyInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CopySelection();
			JREX_LOGLN("CopyInternal()--> **** CopySelection rv<"<<rv<<"> ****")
		}
		return rv;
	}


	nsresult JRexWindow::Copy(){
		JREX_LOGLN("Copy()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return CopyInternal();
		nsresult rv=ExecInEventQ(this,COPY,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Copy()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::CopyLinkLocationInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CopyLinkLocationInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CopyLinkLocation();
			JREX_LOGLN("CopyLinkLocationInternal()--> **** CopyLinkLocation rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::CopyLinkLocation(){
		JREX_LOGLN("CopyLinkLocation()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return CopyLinkLocationInternal();
		nsresult rv=ExecInEventQ(this,COPY_LINK_LOC,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("CopyLinkLocation()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CopyImageLocationInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CopyImageLocationInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CopyImageLocation();
			JREX_LOGLN("CopyImageLocationInternal()--> **** CopyImageLocation rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::CopyImageLocation(){
		JREX_LOGLN("CopyImageLocation()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return CopyImageLocationInternal();
		nsresult rv=ExecInEventQ(this,COPY_IMG_LOC,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("CopyImageLocation()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CopyImageContentsInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("CopyImageContentsInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->CopyImageContents();
			JREX_LOGLN("CopyImageContentsInternal()--> **** CopyImageContents rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::CopyImageContents(){
		JREX_LOGLN("CopyImageContents()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return CopyImageContentsInternal();
		nsresult rv=ExecInEventQ(this,COPY_IMG_CONT,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("CopyImageContents()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::PasteInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("PasteInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->Paste();
			JREX_LOGLN("PasteInternal()--> **** Paste rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::Paste(){
		JREX_LOGLN("Paste()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return PasteInternal();
		nsresult rv=ExecInEventQ(this,PASTE,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Paste()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::SelectAllInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("SelectAllInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->SelectAll();
			JREX_LOGLN("SelectAllInternal()--> **** SelectAll rv<"<<rv<<"> ****")
		}
		return rv;
	}


	nsresult JRexWindow::SelectAll(){
		JREX_LOGLN("SelectAll()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return SelectAllInternal();
		nsresult rv=ExecInEventQ(this,SELECT_ALL,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("SelectAll()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SelectNoneInternal(){
		nsresult rv;
		nsCOMPtr<nsIClipboardCommands> clipboard(do_GetInterface(mWebBrowser,&rv));
		JREX_LOGLN("SelectNoneInternal()--> **** do_GetInterface rv<"<<rv<<"> ****")
		if (clipboard){
			rv=clipboard->SelectNone();
			JREX_LOGLN("SelectNoneInternal()--> **** SelectNone rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::SelectNone(){
		JREX_LOGLN("SelectNone()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return SelectNoneInternal();
		nsresult rv=ExecInEventQ(this,SELECT_NONE,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("SelectNone()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::DeleteInternal(){
		JREX_LOGLN("DeleteInternal()--> **** ****")
		DoCommand(DELETE_COMMAND, 0);
		return NS_OK;
	}


	nsresult JRexWindow::Delete(){
		JREX_LOGLN("Delete()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return DeleteInternal();
		nsresult rv=ExecInEventQ(this,DELETE_ALL,nsnull,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
		JREX_LOGLN("Delete()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::IsCommandSupportedInternal(const char *aCommand, PRBool *_retval){
		JREX_LOGLN("IsCommandSupportedInternal()--> **** aCommand<"<<aCommand<<"> ****")
	    nsCOMPtr<nsIDOMWindow> domWindow;
	    nsresult rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
	    if(NS_SUCCEEDED(rv))
	    	rv=mCmdManager->IsCommandSupported(aCommand, domWindow, _retval);
	    JREX_LOGLN("IsCommandSupportedInternal()--> **** IsCommandSupported rv<"<<rv<<"> ****")
	    return rv;
	}

	nsresult JRexWindow::IsCommandSupported(const char *aCommand, PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("IsCommandSupported()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return IsCommandSupportedInternal(aCommand,_retval);
		PRBool temp=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CMD_SUP,(void*)aCommand,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&temp);
		JREX_LOGLN("IsCommandSupported()--> **** temp<"<<(temp==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=temp;
		JREX_LOGLN("IsCommandSupported()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}


	nsresult JRexWindow::IsCommandEnabledInternal(const char *aCommand, PRBool *_retval){
		JREX_LOGLN("IsCommandEnabledInternal()--> **** aCommand<"<<aCommand<<"> ****")
	    nsCOMPtr<nsIDOMWindow> domWindow;
	    nsresult rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
	    if(NS_SUCCEEDED(rv))
	    	rv=mCmdManager->IsCommandEnabled(aCommand, domWindow, _retval);
	    JREX_LOGLN("IsCommandEnabledInternal()--> **** IsCommandEnabled rv<"<<rv<<"> ****")
	    return rv;
	}


	nsresult JRexWindow::IsCommandEnabled(const char *aCommand, PRBool *_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		JREX_LOGLN("IsCommandEnabled()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return IsCommandEnabledInternal(aCommand,_retval);
		PRBool temp=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CMD_ENABLE,(void*)aCommand,PR_TRUE,HandleEditEvent,DestroyEditEvent,(void**)&temp);
		JREX_LOGLN("IsCommandEnabled()--> **** temp<"<<(temp==PR_TRUE)<<"> ****")
		if (NS_SUCCEEDED(rv))*_retval=temp;
		JREX_LOGLN("IsCommandEnabled()--> **** _retval<"<<(*_retval==PR_TRUE)<<"> ****")
		return rv;
	}

	nsresult JRexWindow::DoCommandInternal(const char *aCommand, nsICommandParams *aCommandParams){
		JREX_LOGLN("DoCommandInternal()--> **** aCommand<"<<aCommand<<"> ****")
	    nsCOMPtr<nsIDOMWindow> domWindow;
	    nsresult rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
	    if(NS_SUCCEEDED(rv))
	    	rv=mCmdManager->DoCommand(aCommand, aCommandParams, domWindow);
	    JREX_LOGLN("DoCommandInternal()--> **** DoCommand rv<"<<rv<<"> ****")
	    return rv;
	}


	nsresult JRexWindow::DoCommand(const char *aCommand, nsICommandParams *aCommandParams){
		JREX_LOGLN("DoCommand()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return DoCommandInternal(aCommand,aCommandParams);

		nsresult rv;
	   	CommandEventData* eventData = new CommandEventData;
		if (eventData) {
			eventData->cmd=aCommand;
			eventData->cmdParams=aCommandParams;
			rv=ExecInEventQ(this,DO_CMD,(void*)eventData,PR_FALSE,HandleEditEvent,DestroyEditEvent,nsnull);
			JREX_LOGLN("DoCommand()--> ****  ExecInEventQ rv<"<<rv<<"> ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	nsresult JRexWindow::ObserverCommand(const char *aCommandToObserve){
		JREX_LOGLN("ObserverCommand()--> **** aCommandToObserve<"<<aCommandToObserve<<"> ****")
	    return NS_OK;
	}

  	nsresult JRexWindow::UnObserverCommand(const char *aCommandObserved){
		JREX_LOGLN("ObserverCommand()--> **** aCommandObserved<"<<aCommandObserved<<"> ****")
	    return NS_OK;
	}

	void* PR_CALLBACK JRexWindow::HandleEditEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleEditEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;
		rVal->rv=window->GrabFocusInternal();
		JREX_LOGLN("HandleEditEvent()--> **** GrabFocusInternal rv<"<<rVal->rv<<"> ****")
		switch(event->eventType){
			case CAN_UNDO:
			{
				PRBool temp=PR_FALSE;
				rVal->rv=window->CanUndoInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanUndoInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_REDO:
			{

				PRBool temp=PR_FALSE;
				rVal->rv=window->CanRedoInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanRedoInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_CUT:
			{

				PRBool temp=PR_FALSE;
				rVal->rv=window->CanCutInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanCutInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_COPY:
			{

				PRBool temp=PR_FALSE;
				rVal->rv=window->CanCopyInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanCopyInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;

			}
			case CAN_COPY_LINK_LOC:
			{
				PRBool temp=PR_FALSE;
				rVal->rv=window->CanCopyLinkLocationInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanCopyLinkLocationInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_COPY_IMG_LOC:
			{
				PRBool temp=PR_FALSE;
				rVal->rv=window->CanCopyImageLocationInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanCopyImageLocationInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_COPY_IMG_CONT:
			{
				PRBool temp=PR_FALSE;
				rVal->rv=window->CanCopyImageContentsInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanCopyImageContentsInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CAN_DELETE:
			{
				PRBool temp=PR_FALSE;
				rVal->rv=window->CanDeleteInternal(&temp);
				JREX_LOGLN("HandleEditEvent()--> **** CanDeleteInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case UNDO:
			{
				rVal->rv=window->UndoInternal();
				JREX_LOGLN("HandleEditEvent()--> **** UndoInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REDO:
			{
				rVal->rv=window->RedoInternal();
				JREX_LOGLN("HandleEditEvent()--> **** RedoInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case CUT:
			{
				rVal->rv=window->CutInternal();
				JREX_LOGLN("HandleEditEvent()--> **** CutInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case COPY:
			{
				rVal->rv=window->CopyInternal();
				JREX_LOGLN("HandleEditEvent()--> **** CopyInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case COPY_LINK_LOC:
			{
				rVal->rv=window->CopyLinkLocationInternal();
				JREX_LOGLN("HandleEditEvent()--> **** CopyLinkLocationInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case COPY_IMG_LOC:
			{
				rVal->rv=window->CopyImageLocationInternal();
				JREX_LOGLN("HandleEditEvent()--> **** CopyImageLocationInternal rv<"<<rVal->rv<<"> ****")

			}
			case COPY_IMG_CONT:
			{
				rVal->rv=window->CopyImageContentsInternal();
				JREX_LOGLN("HandleEditEvent()--> **** CopyImageContentsInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case PASTE:
			{
				rVal->rv=window->PasteInternal();
				JREX_LOGLN("HandleEditEvent()--> **** PasteInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case SELECT_ALL:
			{
				rVal->rv=window->SelectAllInternal();
				JREX_LOGLN("HandleEditEvent()--> **** SelectAllInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case SELECT_NONE:
			{
				rVal->rv=window->SelectNoneInternal();
				JREX_LOGLN("HandleEditEvent()--> **** SelectNoneInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case DELETE_ALL:
			{
				rVal->rv=window->DeleteInternal();
				JREX_LOGLN("HandleEditEvent()--> **** DeleteInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case CMD_SUP:
			{
				char* evtData = NS_REINTERPRET_CAST(char*, event->eventData);
				PRBool temp=PR_FALSE;
				rVal->rv=window->IsCommandEnabledInternal(evtData,&temp);
				JREX_LOGLN("HandleEditEvent()--> **** IsCommandSupportedInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case CMD_ENABLE:
			{
				char* evtData = NS_REINTERPRET_CAST(char*, event->eventData);
				PRBool temp=PR_FALSE;
				rVal->rv=window->IsCommandSupportedInternal(evtData,&temp);
				JREX_LOGLN("HandleEditEvent()--> **** IsCommandSupportedInternal temp<"<<(temp==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)temp;
				break;
			}
			case DO_CMD:
			{
				CommandEventData* evtData = NS_REINTERPRET_CAST(CommandEventData*, event->eventData);
				rVal->rv=window->DoCommandInternal(evtData->cmd, evtData->cmdParams);
				JREX_LOGLN("HandleEditEvent()--> **** DoCommandInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandleEditEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		};
		JREX_LOGLN("HandleEditEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK  JRexWindow::DestroyEditEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyEditEvent()--> **** event <"<<event<<"> ****")
		if(event->eventType==DO_CMD && event->eventData){
			CommandEventData* evtData = NS_REINTERPRET_CAST(CommandEventData*, event->eventData);
			delete evtData;
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
