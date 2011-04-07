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

 	static NS_DEFINE_CID(kAppShellCID, NS_APPSHELL_CID);
	static NS_DEFINE_CID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);

	nsVoidArray			*JRexWindow::sWindowList		= nsnull;
	JRexWindowCreator	*JRexWindow::sJRexWindowCreator	= nsnull;

	JRexWindow::JRexWindow(nsNativeWidget hWnd, nsDataHashtable<nsUint32HashKey,PRUint32> *browserSetupFlags)
								:mMainWnd(hWnd), mBrowserSetupFlags(browserSetupFlags){
		if(IS_NULL(sWindowList)){
			JREX_LOGLN("JRexWindow()--> **** Called Me First Time ****")
			sWindowList = new nsVoidArray();
			JREX_LOGLN("JRexWindow()--> **** Created window list ****")
			nsresult rv=Init();
			JREX_EXP(rv,"JRexWindow()--> **** init Failed ****")
			JREX_LOGLN("JRexWindow()--> **** init done ****")
		}
		mIsModal					= PR_FALSE;
		mIsVisible					= PR_FALSE;
		mBrowCreated				= PR_FALSE;
		mInModalLoop				= PR_FALSE;

		mProgListenerAdded			= PR_FALSE;
		mContextListenerAdded		= PR_FALSE;
		mHistoryListenerAdded		= PR_FALSE;

		mKeyListenerAdded			= PR_FALSE;
		mMouseListenerAdded			= PR_FALSE;
		mMouseMotionListenerAdded	= PR_FALSE;

		mURIContentListenerAdded	= PR_FALSE;
		mPersistProgListenerAdded	= PR_FALSE;
		mChildIsModalLooping	    = PR_FALSE;
		mBeingDisposed				= PR_FALSE;
		mParentIntPtr				= 0;

		mChromeFlag					= 0;
		mModalStatus				= NS_OK;
		mTitle						= nsnull;

		sWindowList->AppendElement(this);
		JREX_LOGLN("JRexWindow()--> **** Added to window list <"<<this<<"> ****")
		mChromeGrip=NS_STATIC_CAST(nsIWebBrowserChrome*,this);
		JREX_LOGLN("JRexWindow()--> **** Created chrome grip ****")

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		GtkWidget* widg=nsnull;
        nsresult rv=NS_OK;
		if(IS_EQT){
			JREX_LOGLN("JRexWindow()--> **** gtk_window_new IN EVT Q THREAD ****")
			widg=gtk_window_new (GTK_WINDOW_POPUP);
			if(NOT_NULL(widg))gtk_widget_realize(widg);
		}else{
			rv=ExecInEventQ(this,JREX_CREATE_GTK,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&widg);
			JREX_LOGLN("JRexWindow()--> **** JREX_CREATE_GTK ExecInEventQ rv<"<<rv<<"> GTK widg <"<<widg<<">****")
		}
		if(IS_NULL(widg))
			JREX_EXP(rv,"JRexWindow()--> **** JREX_CREATE_GTK Failed ****")
		mMainWnd=widg;
		mSignaled=PR_FALSE;
#endif
	}

	JRexWindow::~JRexWindow(){
		JREX_LOGLN("~JRexWindow()--> **** I AM HERE ****")
		if(mTitle) nsMemory::Free(mTitle);
		sWindowList->RemoveElement(this);
		JREX_LOGLN("~JRexWindow()--> **** Removed from window list <"<<this<<"> ****")
		if(sWindowList->Count()<=0){
			JREX_LOGLN("~JRexWindow--> **** All windows deleted, so deleting sWindowList ****")
			delete sWindowList;
			sWindowList=nsnull;
			JREX_LOGLN("~JRexWindow--> **** Setting window creator null ****")
			nsCOMPtr<nsIWindowWatcher> winWatcher = do_GetService(NS_WINDOWWATCHER_CONTRACTID);
			if(NOT_NULL(winWatcher))
				winWatcher->SetWindowCreator(nsnull);//will delete sJRexWindowCreator
		}
		JREX_LOGLN("~JRexWindow()--> **** DONE ****")
	}

	NS_IMPL_THREADSAFE_ADDREF(JRexWindow)
	NS_IMPL_THREADSAFE_RELEASE(JRexWindow)

	NS_INTERFACE_MAP_BEGIN(JRexWindow)
		NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, nsIWebBrowserChrome)
		NS_INTERFACE_MAP_ENTRY(nsIWebBrowserChrome)
		NS_INTERFACE_MAP_ENTRY(nsIWebBrowserChromeFocus)
		NS_INTERFACE_MAP_ENTRY(nsIWebProgressListener)
		NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsIEmbeddingSiteWindow, nsIEmbeddingSiteWindow2)
		NS_INTERFACE_MAP_ENTRY(nsIEmbeddingSiteWindow2)
		NS_INTERFACE_MAP_ENTRY(nsITooltipListener)
		NS_INTERFACE_MAP_ENTRY(nsIInterfaceRequestor)
		NS_INTERFACE_MAP_ENTRY(nsIContextMenuListener2)
		NS_INTERFACE_MAP_ENTRY(nsISHistoryListener)
		NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsIDOMEventListener, nsIDOMKeyListener)
		NS_INTERFACE_MAP_ENTRY(nsIDOMKeyListener)
		NS_INTERFACE_MAP_ENTRY(nsIDOMMouseListener)
		NS_INTERFACE_MAP_ENTRY(nsIURIContentListener)
		NS_INTERFACE_MAP_ENTRY(nsISupportsWeakReference)
	NS_INTERFACE_MAP_END

	nsresult JRexWindow::InternalInit(){
		NS_ASSERTION(IS_NULL(sJRexWindowCreator),"Window creator being initalized twice");
		nsresult rv=NS_OK;
		sJRexWindowCreator = new JRexWindowCreator();
		nsCOMPtr<nsIWindowCreator2> myWinCreator;
		CallQueryInterface(sJRexWindowCreator, NS_STATIC_CAST(nsIWindowCreator2**,
                                          getter_AddRefs(myWinCreator)));
		nsCOMPtr<nsIWindowWatcher> winWatcher = do_GetService(NS_WINDOWWATCHER_CONTRACTID,&rv);
		JREX_RETURN_IF_FAILED(rv,"InternalInit()--> **** do_GetService nsIWindowWatcher ")
		rv=winWatcher->SetWindowCreator(myWinCreator);
		JREX_RETURN_IF_FAILED(rv,"InternalInit()--> **** SetWindowCreator ")
		return rv;
	}

	nsresult JRexWindow::GetPIDOMWindow(nsPIDOMWindow **_result){
		NS_ENSURE_ARG_POINTER(_result);

		nsCOMPtr<nsIDocShell> docShell;
		nsresult rv=GetDocShell(getter_AddRefs(docShell));
		JREX_RETURN_IF_FAILED(rv,"GetPIDOMWindow()--> **** GetDocShell ")

		nsCOMPtr<nsPIDOMWindow> piWin(do_GetInterface(docShell,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetPIDOMWindow()--> **** nsPIDOMWindow do_GetInterface")
		NS_IF_ADDREF(*_result=piWin.get());
		return rv;
	}

	nsresult JRexWindow::GetDocShellInternal(nsIDocShell **_result){
		NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;
		nsCOMPtr<nsIDocShellTreeItem> docShellTreeItem(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetDocShellInternal()--> **** do_QueryInterface nsIDocShellTreeItem")

		nsCOMPtr<nsIDocShellTreeOwner> docShellTreeOwner;
		rv=docShellTreeItem->GetTreeOwner(getter_AddRefs(docShellTreeOwner));
		JREX_RETURN_IF_FAILED(rv,"GetDocShellInternal()--> **** GetTreeOwner")

		nsCOMPtr<nsIDocShellTreeItem> dShellItem;
		docShellTreeOwner->GetPrimaryContentShell(getter_AddRefs(dShellItem));
		JREX_RETURN_IF_FAILED(rv,"GetDocShellInternal()--> **** GetPrimaryContentShell")

		nsCOMPtr<nsIDocShell> docShell(do_QueryInterface(dShellItem,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetDocShellInternal()--> **** nsIDocShell do_QueryInterface")
		NS_IF_ADDREF(*_result=docShell.get());
		return rv;
	}

	nsresult JRexWindow::GetDocShell(nsIDocShell **_result){
		JREX_LOGLN("GetDocShell()--> **** I AM HERE ****")
		if(IS_EQT)
			return GetDocShellInternal(_result);
		nsIDocShell* tmpDocShell=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_DOC_SHELL,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&tmpDocShell);
		JREX_LOGLN("GetDocShell()--> **** ExecInEventQ rv<"<<rv<<"> tmpDocShell<"<<tmpDocShell<<"> ****")
		if (NS_SUCCEEDED(rv))
			*_result=tmpDocShell;
		return rv;
	}

	nsresult JRexWindow::GetRootDocShellInternal(nsIDocShell **_result){
		NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

		nsCOMPtr<nsIInterfaceRequestor> mWebBrowserAsReq(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetRootDocShellInternal()--> **** nsIInterfaceRequestor do_QueryInterface")

		nsCOMPtr<nsIDocShell> docShell;
		rv=mWebBrowserAsReq->GetInterface(NS_GET_IID(nsIDocShell),getter_AddRefs(docShell));
		JREX_RETURN_IF_FAILED(rv,"GetRootDocShellInternal()--> **** nsIDocShell GetInterface")
		NS_IF_ADDREF(*_result=docShell.get());
		return rv;
	}

	nsresult JRexWindow::GetRootDocShell(nsIDocShell **_result){
		JREX_LOGLN("GetRootDocShell()--> **** I AM HERE ****")
		if(IS_EQT)
			return GetRootDocShellInternal(_result);
		nsIDocShell* tmpDocShell=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_ROOT_DOC_SHELL,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&tmpDocShell);
		JREX_LOGLN("GetRootDocShell()--> **** ExecInEventQ rv<"<<rv<<"> tmpDocShell<"<<tmpDocShell<<"> ****")
		if (NS_SUCCEEDED(rv))
			*_result=tmpDocShell;
		return rv;
	}


	nsresult JRexWindow::GetIsLoadingDocumentInternal(PRBool *isLoading){
		NS_ENSURE_ARG_POINTER(isLoading);
		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebProgress> webProgress(do_GetInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetIsLoadingDocumentInternal()--> **** do_GetInterface nsIWebProgress")
		if(webProgress){
			rv=webProgress->GetIsLoadingDocument(isLoading);
			JREX_LOGLN("GetIsLoadingDocumentInternal()--> **** GetIsLoadingDocument rv<"<<rv<<"> ***")
		}
		return rv;
	}

	nsresult JRexWindow::GetIsLoadingDocument(PRBool *isLoading){
		JREX_LOGLN("GetIsLoadingDocument()--> **** I AM HERE ****")
		if(IS_EQT)
			return GetIsLoadingDocumentInternal(isLoading);
		PRBool temp=PR_FALSE;
		nsresult rv=ExecInEventQ(this,JREX_GET_IS_DOC_LOADING,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("GetIsLoadingDocument()--> **** ExecInEventQ rv<"<<rv<<"> isLoading<"<<temp<<">****")
		if(NS_SUCCEEDED(rv))
			*isLoading=temp;
		return NS_OK;//ignore rv
	}

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	static gint HandleFocusIn(GtkWidget *widget, GdkEventFocus *focusEvent, JRexWindow *window){
		window->ChangeFocus(PR_TRUE);
		return FALSE;
	}

	static gint HandleFocusOut(GtkWidget *widget, GdkEventFocus *focusEvent, JRexWindow *window){
		window->ChangeFocus(PR_FALSE);
		return FALSE;
	}
#endif

	nsresult JRexWindow::ShowInternal(PRInt32 x, PRInt32 y, PRInt32 width, PRInt32 height){
		JREX_LOGLN("ShowInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(mBrowCreated==PR_TRUE)return NS_OK;
		nsresult rv=NS_OK;

		JREX_LOGLN("ShowInternal()--> **** Using HWND <"<<mMainWnd<<"> ****")
		JREX_LOGLN("ShowInternal()--> **** Using x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<"> ****")

		mWebBrowser=do_CreateInstance(NS_WEBBROWSER_CONTRACTID,&rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** WebBrowser do_CreateInstance")

		nsCOMPtr<nsIWebBrowserChrome> myChrome;
		CallQueryInterface(mChromeGrip, NS_STATIC_CAST(nsIWebBrowserChrome**,
                                          getter_AddRefs(myChrome)));
		JREX_LOGLN("ShowInternal()--> **** Got myChrome ****")

		rv=mWebBrowser->SetContainerWindow(myChrome);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** WebBrowser SetContainerWindow")

		nsCOMPtr<nsIDocShellTreeItem> docShellTreeItem(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** WebBrowser do_QueryInterface nsIDocShellTreeItem")

		rv=docShellTreeItem->SetItemType(nsIDocShellTreeItem::typeContentWrapper);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** docShellTreeItem SetItemType")

  		mBaseWindow = do_QueryInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIBaseWindow do_QueryInterface")

		rv=mBaseWindow->InitWindow(mMainWnd,nsnull,x,y,width,height);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIBaseWindow InitWindow")

		nsCOMPtr<nsIWebBrowserSetup> webBrowserAsSetup(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** webBrowserAsSetup do_QueryInterface")
		PRUint32 value=0;
		//we do it here since it should before create and rest after.
		if (NOT_NULL(mBrowserSetupFlags) &&
				mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_IS_CHROME_WRAPPER,&value)){
			webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_IS_CHROME_WRAPPER,(value<1?PR_FALSE:PR_TRUE));
			JREX_LOGLN("ShowInternal()--> **** SETUP_IS_CHROME_WRAPPER rv<"<<rv<<"> value <"<<value<<"> ****")
		}

		rv=mBaseWindow->Create();
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIBaseWindow Create")

		if(NOT_NULL(mBrowserSetupFlags)){
			JREX_LOGLN("ShowInternal()--> **** Setting  mBrowserSetupFlags ****")
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS,&value)){
				rv=webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_ALLOW_PLUGINS rv<"<<rv<<"> value<"<<value<<"> ****")
			}
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_ALLOW_JAVASCRIPT,&value)){
				webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_JAVASCRIPT,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_ALLOW_JAVASCRIPT rv<"<<rv<<"> value <"<<value<<"> ****")
			}
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_ALLOW_META_REDIRECTS,&value)){
				webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_META_REDIRECTS,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_ALLOW_META_REDIRECTS rv<"<<rv<<"> value <"<<value<<"> ****")
			}
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_ALLOW_SUBFRAMES,&value)){
				webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_SUBFRAMES,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_ALLOW_SUBFRAMES rv<"<<rv<<"> value <"<<value<<"> ****")
			}
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_ALLOW_IMAGES,&value)){
				webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_IMAGES,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_ALLOW_IMAGES rv<"<<rv<<"> value <"<<value<<"> ****")
			}
			if (mBrowserSetupFlags->Get(nsIWebBrowserSetup::SETUP_USE_GLOBAL_HISTORY,&value)){
				webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_USE_GLOBAL_HISTORY,(value<1?PR_FALSE:PR_TRUE));
				JREX_LOGLN("ShowInternal()--> **** SETUP_USE_GLOBAL_HISTORY rv<"<<rv<<"> value <"<<value<<"> ****")
			}
		}

        rv=mBaseWindow->SetPositionAndSize(x,y,width,height,PR_TRUE);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIBaseWindow SetPositionAndSize")

	    rv=mBaseWindow->SetVisibility(mIsVisible);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIBaseWindow SetVisibility")

		nsCOMPtr<nsIWebBrowserFocus> webBrowserFocus = do_QueryInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIWebBrowserFocus do_QueryInterface")
		rv=webBrowserFocus->Activate();
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** Activate")

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
  		GtkWidget *child = GTK_BIN(mMainWnd)->child;
  		gtk_signal_connect_while_alive(GTK_OBJECT(child),"focus_in_event",(GTK_SIGNAL_FUNC(HandleFocusIn)),
				 							this,GTK_OBJECT(child));
  		gtk_signal_connect_while_alive(GTK_OBJECT(child),"focus_out_event",(GTK_SIGNAL_FUNC(HandleFocusOut)),
				 							this,GTK_OBJECT(child));
		mSignaled=PR_TRUE;
#endif
		mWebNavigation= do_QueryInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIWebNavigation do_QueryInterface")

		//We add nsIWebProgressListener here, as adding when required may be late
		//We need it for calling SizeToContent etc.
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** CallQueryInterface nsISupportsWeakReference")

		nsCOMPtr<nsIWeakReference> weakRef;
		rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** GetWeakReference")

		rv=mWebBrowser->AddWebBrowserListener(weakRef,nsIWebProgressListener::GetIID());
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** AddWebBrowserListener")

		nsCOMPtr<nsPIDOMWindow> piWin;
		rv=GetPIDOMWindow(getter_AddRefs(piWin));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** GetPIDOMWindow")

		nsCOMPtr<nsIChromeEventHandler> cHandler;
		rv=piWin->GetChromeEventHandler(getter_AddRefs(cHandler));
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** GetChromeEventHandler")

		mEventReceiver = do_QueryInterface(cHandler,&rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** nsIDOMEventReceiver do_QueryInterface")

		mCmdManager=do_GetInterface(mWebBrowser, &rv);
		JREX_RETURN_IF_FAILED(rv,"ShowInternal()--> **** mCmdManager do_GetInterface")
		mBrowCreated=PR_TRUE;
		return rv;
    }

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	nsresult JRexWindow::GotVisualInternal(nsNativeWidget parentWnd){
		JREX_LOGLN("GotVisualInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		XReparentWindow(GDK_DISPLAY(),GDK_WINDOW_XWINDOW(((GtkWidget*)mMainWnd)->window), (Window)parentWnd, 0, 0);
		JREX_LOGLN("GotVisualInternal()--> **** XReparentWindow DONE !!!!***")
		gtk_widget_show((GtkWidget*)mMainWnd);
		JREX_LOGLN("GotVisualInternal()--> **** gtk_widget_show DONE !!!!***")
		return NS_OK;
	}
#endif

	nsresult JRexWindow::DisposeInternal(){
		JREX_LOGLN("DisposeInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(NOT_NULL(mBrowserSetupFlags))
			delete mBrowserSetupFlags;

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		if(mSignaled && NOT_NULL(mMainWnd)){
  			GtkWidget *child = GTK_BIN(mMainWnd)->child;
  			GtkObject *gtkObj= NOT_NULL(child)?GTK_OBJECT(child):NULL;
  			if(gtkObj){
  				gtk_signal_disconnect_by_func(gtkObj,GTK_SIGNAL_FUNC(HandleFocusIn),this);
  				gtk_signal_disconnect_by_func(gtkObj,GTK_SIGNAL_FUNC(HandleFocusOut),this);
			}
		}
		mSignaled=PR_FALSE;
#endif
		if(mBrowCreated==PR_FALSE){
			JREX_LOGLN("DisposeInternal()--> **** Browser not created, deleting JRexWindow ****")
           PRUint32 dieGrip=NS_PTR_TO_INT32(this);
           mChromeGrip=nsnull;
           JRexWindow *temp=(JRexWindow *)NS_INT32_TO_PTR(dieGrip);
           //This will be false if some interface releases JRexWindow object.
           PRBool isWinAvail=IsWindowAvailable(temp);
           JREX_LOGLN("DisposeInternal()--> **** dieGrip<"<<dieGrip<<"> isWinAvail <"<<isWinAvail<<"> ****")
           if(isWinAvail){
			this->mRefCnt = 1; //stabilize
			NS_DELETEXPCOM(this);
           }
			return NS_OK;
		}

		nsresult rv=NS_OK;
		rv=CancelPrintPreviewInternal();
		JREX_LOGLN("DisposeInternal()--> **** CancelPrintPreviewInternal rv<"<<rv<<">****")
		rv=CancelPrintInternal();
		JREX_LOGLN("DisposeInternal()--> **** CancelPrintInternal rv<"<<rv<<">****")
		rv=RemoveProgressListener();
		JREX_LOGLN("DisposeInternal()--> **** RemoveProgressListener rv<"<<rv<<">****")

		if(mContextListenerAdded){
			rv=RemoveContextMenuListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveContextMenuListenerInternal rv<"<<rv<<">****")
		}
		if(mHistoryListenerAdded){
			rv=RemoveHistoryListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveHistoryListenerInternal rv<"<<rv<<">****")
		}
		if(mKeyListenerAdded){
			rv=RemoveKeyListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveKeyListenerInternal rv<"<<rv<<">****")
		}
		if(mMouseListenerAdded){
			rv=RemoveMouseListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveMouseListenerInternal rv<"<<rv<<">****")
		}
		if(mMouseMotionListenerAdded){
			rv=RemoveMouseMotionListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveMouseMotionListenerInternal rv<"<<rv<<">****")
		}
		if(mURIContentListenerAdded){
			rv=RemoveURIContentListenerInternal();
			JREX_LOGLN("DisposeInternal()--> **** RemoveURIContentListenerInternal rv<"<<rv<<">****")
		}

		if(mEventReceiver){
			nsCOMPtr<nsIEventListenerManager> eventLisManager;
			rv=mEventReceiver->GetListenerManager(getter_AddRefs(eventLisManager));
			JREX_LOGLN("DisposeInternal()--> **** GetListenerManager rv<"<<rv<<">****")
			if(eventLisManager){
				rv=eventLisManager->RemoveAllListeners(PR_FALSE);
				JREX_LOGLN("DisposeInternal()--> **** eventLisManager RemoveAllListeners rv<"<<rv<<">****")
			}
		}

		rv=gEventQ->RevokeEvents(this);
		JREX_LOGLN("DisposeInternal()--> **** gEventQ RevokeEvents rv<"<<rv<<">****")
		PRUint32 dieGrip=NS_PTR_TO_INT32(this);
		JREX_LOGLN("DisposeInternal()--> **** dieGrip<"<<dieGrip<<"> ****")

		mBrowCreated=PR_FALSE;
		if(NOT_NULL(mWebBrowser)){
			if(mPersistProgListenerAdded){
				nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
				JREX_LOGLN("DisposeInternal()--> **** browserAsPersist rv<"<<rv<<">****")
				if(browserAsPersist)browserAsPersist->SetProgressListener(nsnull);
			}

			nsCOMPtr<nsISupportsWeakReference> supportsWeak;
			rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
			JREX_LOGLN("DisposeInternal()--> **** CallQueryInterface nsISupportsWeakReference rv <"<<rv<<"> ****")
			if (NS_SUCCEEDED(rv)){
				nsCOMPtr<nsIWeakReference> weakRef;
				rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
				if (NS_SUCCEEDED(rv)){
					rv=mWebBrowser->RemoveWebBrowserListener(weakRef,nsIWebProgressListener::GetIID());
					JREX_LOGLN("DisposeInternal()--> **** RemoveWebBrowserListener rv <"<<rv<<"> ****")
				}
			}

			rv=mWebBrowser->SetContainerWindow(nsnull);
			JREX_LOGLN("DisposeInternal()--> **** SetContainerWindow set null rv <"<<rv<<"> ****")

			if(NOT_NULL(mBaseWindow)){
				rv=mBaseWindow->Destroy();
				JREX_LOGLN("DisposeInternal()--> **** mBaseWindow Destroy rv <"<<rv<<">****")
			}
		}

		mBaseWindow=nsnull;
		mWebNavigation=nsnull;
		mEventReceiver=nsnull;
		mCmdManager=nsnull;
		mWebBrowser=nsnull;
		mMainWnd=nsnull;
		mBrowserSetupFlags=nsnull;
       mChromeGrip=nsnull;

		JRexWindow *temp=(JRexWindow *)NS_INT32_TO_PTR(dieGrip);
		//This will be false if some interface releases JRexWindow object.
		PRBool isWinAvail=IsWindowAvailable(temp);
		JREX_LOGLN("DisposeInternal()--> **** dieGrip<"<<dieGrip<<"> isWinAvail <"<<isWinAvail<<"> ****")
		if(isWinAvail){
			temp->mRefCnt = 1; //stabilize
			NS_DELETEXPCOM(temp);
		}
		JREX_LOGLN("DisposeInternal()--> **** Disposing JRexWindow dieGrip<"<<dieGrip<<"> DONE ****")
		return rv;
	}


	PRBool JRexWindow::IsWindowAvailable(JRexWindow* checkWin){
		if(IS_NULL(sWindowList) || IS_NULL(checkWin))return PR_FALSE;
  		PRInt32 count = sWindowList->Count();
  		JREX_LOGLN("IsWindowAvailable()--> **** checkWin <"<<checkWin<<"> count<"<<count<<">****")
  		for (int i = 0; i < count; i++) {
			if(checkWin==sWindowList->ElementAt(i))
				return PR_TRUE;
		}
		return PR_FALSE;
	}

	JRexWindow* JRexWindow::GetJRexWindow(nsIWebBrowserChrome *chrome){
		if(IS_NULL(sWindowList) || IS_NULL(chrome))return nsnull;
  		PRInt32 count = sWindowList->Count();
  		for (int i = 0; i < count; i++) {
			JRexWindow *tmp = NS_STATIC_CAST(JRexWindow *, sWindowList->ElementAt(i));
			if(tmp->mChromeGrip==chrome)
			return tmp;
		}
		return nsnull;
	}

	void JRexWindow::SayGoodBye(){
		JREX_LOGLN("SayGoodBye()--> **** NOT ALL WINDOWS ARE DIPOSED <"<<(NOT_NULL(sWindowList)?"TRUE":"FALSE")<<"> ****")
		while (NOT_NULL(sWindowList) && sWindowList->Count()>0) {
			JRexWindow *tmp = NS_STATIC_CAST(JRexWindow *, sWindowList->ElementAt(0));
			JREX_LOGLN("SayGoodBye()--> **** Disposing JRexWindow<"<<tmp<<">  ****")
			nsresult rv=tmp->Dispose();
			JREX_LOGLN("SayGoodBye()--> **** Disposing JRexWindow<"<<tmp<<"> done  rv <"<<rv<<"> ****")
		}
	}

	nsresult JRexWindow::Init(){
		JREX_LOGLN("Init()--> **** I AM HERE ****")
		if(IS_EQT)return InternalInit();
		nsresult srv=NS_OK;
		nsresult rv=ExecInEventQ(this,JREX_CREATE,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&srv);
		JREX_LOGLN("Init()--> **** ExecInEventQ rv<"<<rv<<"> srv<"<<srv<<"> ****")
		return srv;
	}

	nsresult JRexWindow::Show(PRInt32 x, PRInt32 y, PRInt32 width, PRInt32 height){
		JREX_LOGLN("Show()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(mBrowCreated==PR_TRUE)return NS_OK;
		JREX_LOGLN("Show()--> **** Using HWND <"<<mMainWnd<<"> x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<"> ****")
		if(IS_EQT)
			return ShowInternal(x,y,(width<1?1:width),(height<1?1:height));

		PRInt32* temp=new PRInt32[4];
		if(!temp)return NS_ERROR_OUT_OF_MEMORY;
		temp[0]=x;
		temp[1]=y;
		temp[2]=(width<1?1:width);
		temp[3]=(height<1?1:height);
		nsresult srv=NS_OK;
		nsresult rv=ExecInEventQ(this,JREX_SHOW,temp,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&srv);
		JREX_LOGLN("Show()--> **** ExecInEventQ rv<"<<rv<<"> srv<"<<srv<<"> ****")
		return srv;
	}

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
	nsresult JRexWindow::GotVisual(nsNativeWidget parentWnd){
		JREX_LOGLN("GotVisual()--> **** mBrowCreated<"<<mBrowCreated<<"> parentWnd<"<<parentWnd<<">****")
		if(IS_EQT)return GotVisualInternal(parentWnd);
		nsresult rv=ExecInEventQ(this,JREX_GOT_VISUAL,(void*)parentWnd,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("GotVisual()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}
#endif

	nsresult JRexWindow::Dispose(){
		JREX_LOGLN("Dispose()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(mInModalLoop){
			mModalStatus=NS_OK;
			mIsModal=PR_FALSE;
			//just fire a dummy event, appShell->GetNativeEvent in ShowAsModal() will be blocking for a event
   			ExecInEventQ(this,JREX_DUMMY,nsnull,IS_EQT,HandleBasicEvent,DestroyBasicEvent,nsnull);
			while(mInModalLoop){
				JREX_LOGLN("Dispose()--> **** SLEEPING ZZZZZ ****")
				PR_Sleep(1*PR_TicksPerSecond()/1000);
			}
		}
		if(IS_EQT)return DisposeInternal();
		nsresult srv=NS_OK;
		nsresult rv=ExecInEventQ(this,JREX_DISPOSE,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&srv);
		JREX_LOGLN("Dispose()--> **** ExecInEventQ rv<"<<rv<<">  ****")
		return rv;
	}

	nsresult JRexWindow::SetBoundsInternal(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height){
		JREX_LOGLN("SetBoundsInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("SetBoundsInternal()--> **** Using x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<"> ****")
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		if(NOT_NULL(mMainWnd)){
			gtk_widget_set_usize((GtkWidget*)mMainWnd,width,height);
			gdk_window_move_resize(((GtkWidget*)mMainWnd)->window,x,y,width,height);
			JREX_LOGLN("SetBoundsInternal()--> gdk_window_move_resize Done ****")
		}
#endif
		nsresult rv=mBaseWindow->SetPositionAndSize(x,y,width,height,PR_FALSE);
		JREX_LOGLN("SetBoundsInternal()--> SetPositionAndSize rv<"<<rv<<"> ****")
		return NS_OK;//ignore rv
	}


	nsresult JRexWindow::SetBounds(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height){
		JREX_LOGLN("SetBounds()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("SetBounds()--> **** Using x<"<<x<<"> y<"<<y<<"> width<"<<width<<"> height<"<<height<<"> ****")
		if(IS_EQT)return SetBoundsInternal(x,y,(width<1?1:width),(height<1?1:height));
		PRInt32* temp=new PRInt32[4];
		if(!temp)return NS_ERROR_OUT_OF_MEMORY;
		temp[0]=x;
		temp[1]=y;
		temp[2]=(width<1?1:width);
		temp[3]=(height<1?1:height);
		nsresult rv=ExecInEventQ(this,JREX_SET_BOUNDS,temp,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("SetBounds()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetBounds(PRInt32 *x, PRInt32 *y, PRInt32 *width,PRInt32 *height){
		JREX_LOGLN("GetBounds()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID){
			*x=0;
			*y=0;
			*width=1;
			*height=1;
			return NS_OK;
		}
		NS_ENSURE_ARG_POINTER(x);NS_ENSURE_ARG_POINTER(y);
		NS_ENSURE_ARG_POINTER(width);NS_ENSURE_ARG_POINTER(height);
		if(IS_EQT)return mBaseWindow->GetPositionAndSize(x,y,width,height);

		PRInt32* temp=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_BOUNDS,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("GetBounds()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp){
			*x=temp[0];
			*y=temp[1];
			*width=temp[2];
			*height=temp[3];
			delete temp;
		}
		JREX_LOGLN("GetBounds()--> **** Got x<"<<*x<<"> y<"<<*y<<"> width<"<<*width<<"> height<"<<*height<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SetVisible(PRBool visible){
		JREX_LOGLN("SetVisible()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID){
			mIsVisible=visible;
			return NS_OK;
		}
		if(IS_EQT){
			nsresult rv=mBaseWindow->SetVisibility(visible);
			JREX_LOGLN("SetVisible()--> **** SetVisibility rv<"<<rv<<"> ****")
			return NS_OK;//ignore rv
		}
		nsresult rv=ExecInEventQ(this,JREX_SET_VISIBLE,(void*)visible,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("SetVisible()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return NS_OK;//ignore rv
	}

	nsresult JRexWindow::IsVisible(PRBool *visible){
		JREX_LOGLN("IsVisible()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID){
			*visible=PR_FALSE;
			return NS_OK;
		}
		NS_ENSURE_ARG_POINTER(visible);
		*visible=mIsVisible;
		return NS_OK;
	}

	nsresult JRexWindow::IsVisibleInternal(PRBool *visible){
		JREX_LOGLN("IsVisibleInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		NS_ENSURE_ARG_POINTER(visible);
		if(IS_EQT)return mBaseWindow->GetVisibility(visible);
		PRBool temp=PR_FALSE;
		nsresult rv=ExecInEventQ(this,JREX_IS_VISIBLE,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("GetBounds()--> **** ExecInEventQ rv<"<<rv<<"> visible<"<<temp<<">****")
		if(NS_SUCCEEDED(rv))
			*visible=temp;
		return rv;
	}


	nsresult JRexWindow::SetEnabled(PRBool enable){
		JREX_LOGLN("SetEnabled()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)return mBaseWindow->SetEnabled(enable);
		nsresult rv=ExecInEventQ(this,JREX_SET_ENABLED,(void*)enable,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("SetEnabled()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return NS_OK;//ignore rv
	}

	nsresult JRexWindow::IsEnabled(PRBool *enable){
		JREX_LOGLN("IsEnabled()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID){
			*enable=PR_FALSE;
			return NS_OK;
		}
		NS_ENSURE_ARG_POINTER(enable);
		if(IS_EQT)return mBaseWindow->GetEnabled(enable);
		PRBool temp=PR_FALSE;
		nsresult rv=ExecInEventQ(this,JREX_IS_ENABLED,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("IsEnabled()--> **** ExecInEventQ rv<"<<rv<<"> enable<"<<temp<<">****")
		if(NS_SUCCEEDED(rv))
			*enable=temp;
		return NS_OK;//ignore rv
	}

	nsresult JRexWindow::GetBaseTitle(PRUnichar * *aTitle){
		JREX_LOGLN("GetBaseTitle()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		NS_ENSURE_ARG_POINTER(aTitle);
		if(IS_EQT)return mBaseWindow->GetTitle(aTitle);
		PRUnichar* temp=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_TITLE,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("GetBaseTitle()--> **** ExecInEventQ rv<"<<rv<<"> title<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*aTitle=temp;
		return rv;
	}

	nsresult JRexWindow::SetBaseTitle(const PRUnichar * aTitle){
		JREX_LOGLN("SetBaseTitle()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("SetBaseTitle()--> **** aTitle <"<<aTitle<<">****")
		if(IS_EQT)return mBaseWindow->SetTitle(aTitle);
		nsresult rv=ExecInEventQ(this,JREX_SET_TITLE,(void*)aTitle,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("SetBaseTitle()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::Repaint(PRBool force){
		JREX_LOGLN("Repaint()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("Repaint()--> **** force <"<<force<<">****")
		if(IS_EQT)return mBaseWindow->Repaint(force);
		nsresult rv=ExecInEventQ(this,JREX_REPAINT,(void*)force,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("Repaint()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::ChangeFocusInternal(PRBool focusGained){
		nsCOMPtr<nsPIDOMWindow> piWin;
		nsresult rv=GetPIDOMWindow(getter_AddRefs(piWin));
		JREX_LOGLN("ChangeFocusInternal()--> **** GetPIDOMWindow rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv) && piWin){
			rv=focusGained?piWin->Activate():piWin->Deactivate();
			JREX_LOGLN("ChangeFocusInternal()--> **** Activate/Deactivate rv<"<<rv<<"> ****")
			nsCOMPtr<nsIFocusController> focusController;
			rv=piWin->GetRootFocusController(getter_AddRefs(focusController));
			JREX_LOGLN("ChangeFocusInternal()--> **** GetRootFocusController rv<"<<rv<<"> ****")
			if (focusController){
				rv=focusController->SetActive(PR_TRUE);
				JREX_LOGLN("ChangeFocusInternal()--> **** SetActive rv<"<<rv<<"> ****")
			}
		}
		return rv;
	}

	nsresult JRexWindow::ChangeFocus(PRBool focusGained){
		JREX_LOGLN("ChangeFocus()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("ChangeFocus()--> **** focusGained <"<<focusGained<<"> ****")
		if(IS_EQT){
			nsresult rv=ChangeFocusInternal(focusGained);
			JREX_LOGLN("ChangeFocus()--> **** ChangeFocusInternal rv<"<<rv<<"> ****")
			return NS_OK;//ignore rv
		}
		nsresult rv=ExecInEventQ(this,JREX_CHANGE_FOCUS,(void*)focusGained,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("ChangeFocus()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return NS_OK;//ignore rv
	}

	nsresult JRexWindow::GrabFocusInternal(){
		if(WINDOW_NOT_VALID)return NS_OK;
		nsCOMPtr<nsPIDOMWindow> piWin;
		nsresult rv=GetPIDOMWindow(getter_AddRefs(piWin));
		JREX_LOGLN("GrabFocusInternal()--> **** GetPIDOMWindow rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv) && piWin){
			nsCOMPtr<nsIFocusController> focusController;
			rv=piWin->GetRootFocusController(getter_AddRefs(focusController));
			JREX_LOGLN("GrabFocusInternal()--> **** GetRootFocusController rv<"<<rv<<"> ****")
			if (focusController){
				rv=focusController->RewindFocusState();
				JREX_LOGLN("GrabFocusInternal()--> **** RewindFocusState rv<"<<rv<<"> ****")

				nsCOMPtr<nsIDOMElement> domEle;
				rv=focusController->GetFocusedElement(getter_AddRefs(domEle));
				JREX_LOGLN("GrabFocusInternal()--> **** GetFocusedElement rv<"<<rv<<"> ****")
				nsCOMPtr<nsIDOMHTMLInputElement> htmlInputEle;
				if(domEle && (htmlInputEle=do_QueryInterface(domEle))){
				rv=focusController->MoveFocus(true, domEle);
				JREX_LOGLN("GrabFocusInternal()--> **** MoveFocus forward rv<"<<rv<<"> ****")
				rv=focusController->MoveFocus(false, nsnull);
				JREX_LOGLN("GrabFocusInternal()--> **** MoveFocus backward rv<"<<rv<<"> ****")
				}else{
				  nsCOMPtr<nsIDOMWindowInternal> internalWin;
				  rv=piWin->GetPrivateRoot(getter_AddRefs(internalWin));
				  JREX_LOGLN("GrabFocusInternal()--> **** GetPrivateRoot rv<"<<rv<<"> ****")
				  rv=focusController->SetFocusedWindow(internalWin);
				  JREX_LOGLN("GrabFocusInternal()--> **** SetFocusedWindow rv<"<<rv<<"> ****")
				}
			}
		}
		return rv;
	}

	nsresult JRexWindow::GrabFocus(){
		JREX_LOGLN("GrabFocus()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT){
			nsresult rv=GrabFocusInternal();
			JREX_LOGLN("GrabFocus()--> **** GrabFocusInternal rv<"<<rv<<"> ****")
			return NS_OK;//ignore rv
		}
		nsresult rv=ExecInEventQ(this,JREX_GRAB_FOCUS,nsnull,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("GrabFocus()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return NS_OK;//ignore rv
	}

	nsresult JRexWindow::MoveFocusInternal(PRBool forward){
		nsCOMPtr<nsPIDOMWindow> piWin;
		nsresult rv=GetPIDOMWindow(getter_AddRefs(piWin));
		JREX_LOGLN("MoveFocusInternal()--> **** GetPIDOMWindow rv<"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv) && piWin){
			nsCOMPtr<nsIFocusController> focusController;
			rv=piWin->GetRootFocusController(getter_AddRefs(focusController));
			JREX_LOGLN("MoveFocusInternal()--> **** GetRootFocusController rv<"<<rv<<"> ****")
			if (focusController){
				nsCOMPtr<nsIDOMElement> domEle;
				rv=focusController->GetFocusedElement(getter_AddRefs(domEle));
				JREX_LOGLN("MoveFocusInternal()--> **** GetFocusedElement rv<"<<rv<<"> ****")
				rv=focusController->MoveFocus(forward, domEle);
				JREX_LOGLN("MoveFocusInternal()--> **** MoveFocus rv<"<<rv<<"> ****")
			}
		}
		return rv;
	}

	nsresult JRexWindow::MoveFocus(PRBool forward){
		JREX_LOGLN("MoveFocus()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("MoveFocus()--> **** forward <"<<forward<<"> ****")
		if(IS_EQT)return MoveFocusInternal(forward);
		nsresult rv=ExecInEventQ(this,JREX_MOVE_FOCUS,(void*)forward,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("MoveFocus()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetFocusedElementInternal(nsIDOMElement** aResult){
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserFocus> webBrowserFocus = do_QueryInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"GetFocusedElementInternal()--> **** nsIWebBrowserFocus do_QueryInterface")
		if (webBrowserFocus){
			nsCOMPtr<nsIDOMElement> domEle;
			rv=webBrowserFocus->GetFocusedElement(getter_AddRefs(domEle));
			JREX_LOGLN("GetFocusedElementInternal()--> **** GetFocusedElement rv<"<<rv<<"> ****")
			if(NS_SUCCEEDED(rv))
				NS_IF_ADDREF(*aResult=domEle.get());
		}
		return rv;
	}

	nsresult JRexWindow::GetFocusedElement(nsIDOMElement** aResult){
		JREX_LOGLN("GetFocusedElement()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		NS_ENSURE_ARG_POINTER(aResult);
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)return GetFocusedElementInternal(aResult);
		nsIDOMElement* srv=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_FOCUSED_ELE,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&srv);
		JREX_LOGLN("GetFocusedElement()--> **** ExecInEventQ rv<"<<rv<<"> srv<"<<srv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*aResult=srv;
		return rv;
	}

	nsresult JRexWindow::SetFocusedElementInternal(nsIDOMElement* aElement){
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserFocus> webBrowserFocus = do_QueryInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"SetFocusedElementInternal()--> **** nsIWebBrowserFocus do_QueryInterface")
		if (webBrowserFocus){
			nsCOMPtr<nsIDOMElement> domEle;
			rv=webBrowserFocus->SetFocusedElement(aElement);
			JREX_LOGLN("SetFocusedElementInternal()--> **** SetFocusedElement rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::SetFocusedElement(nsIDOMElement* aElement){
		JREX_LOGLN("SetFocusedElement()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		JREX_LOGLN("SetFocusedElement()--> **** aElement <"<<aElement<<"> ****")
		if(IS_EQT)return SetFocusedElementInternal(aElement);
		nsresult rv=ExecInEventQ(this,JREX_SET_FOCUSED_ELE,aElement,PR_FALSE,HandleBasicEvent,DestroyBasicEvent,nsnull);
		JREX_LOGLN("SetFocusedElement()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetSelectionInternal(nsISelection * *selection){
		nsCOMPtr<nsPIDOMWindow> piWin;
		nsresult rv=GetPIDOMWindow(getter_AddRefs(piWin));
		JREX_LOGLN("GetSelectionInternal()--> **** GetPIDOMWindow rv<"<<rv<<"> ****")
		nsCOMPtr<nsIDOMWindow> domWindow;
		if (NS_SUCCEEDED(rv) && piWin){
			nsCOMPtr<nsIFocusController> focusController;
			rv=piWin->GetRootFocusController(getter_AddRefs(focusController));
			JREX_LOGLN("GetSelectionInternal()--> **** GetRootFocusController rv<"<<rv<<"> ****")
			if (focusController){
				nsCOMPtr<nsIDOMWindowInternal> fdomWnd;
				rv=focusController->GetFocusedWindow(getter_AddRefs(fdomWnd));
				JREX_LOGLN("GetSelectionInternal()--> **** GetFocusedWindow rv<"<<rv<<"> ****")
				if(fdomWnd){
					domWindow=do_QueryInterface(fdomWnd,&rv);
					JREX_LOGLN("GetSelectionInternal()--> **** do_QueryInterface rv<"<<rv<<"> ****")
				}
			}
		}
		if(IS_NULL(domWindow)){
			rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
			JREX_LOGLN("GetSelectionInternal()--> **** GetContentDOMWindow rv<"<<rv<<"> ****")
		}
		if(NS_SUCCEEDED(rv) && domWindow){
			nsCOMPtr<nsISelection> tmpSelection;
			rv=domWindow->GetSelection(getter_AddRefs(tmpSelection));
			JREX_LOGLN("GetSelectionInternal()--> **** GetSelection rv<"<<rv<<"> ****")
			if(NS_SUCCEEDED(rv))
				NS_IF_ADDREF(*selection=tmpSelection.get());
		}
		return rv;
	}

	nsresult JRexWindow::GetSelection(nsISelection * *selection){
		JREX_LOGLN("GetSelection()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		NS_ENSURE_ARG_POINTER(selection);
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)return GetSelectionInternal(selection);
		nsISelection *temp=nsnull;
		nsresult rv=ExecInEventQ(this,JREX_GET_SELECTION,nsnull,PR_TRUE,HandleBasicEvent,DestroyBasicEvent,(void**)&temp);
		JREX_LOGLN("GetSelection()--> **** ExecInEventQ rv<"<<rv<<"> temp<"<<temp<<">****")
		if(NS_SUCCEEDED(rv) && temp)
			*selection=temp;
		return rv;
	}


	void* PR_CALLBACK JRexWindow::HandleBasicEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		JREX_LOGLN("HandleBasicEvent()--> **** JRexWindow <"<<window<<">****")
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		if(event->eventType!=JREX_CREATE
				&& JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case JREX_CREATE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_CREATE EVENT!!!****")
				rVal->rv=InternalInit();
				JREX_LOGLN("HandleBasicEvent InternalInit rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SHOW:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SHOW EVENT!!!****")
				PRInt32* temp=NS_REINTERPRET_CAST(PRInt32*, event->eventData);
				JREX_LOGLN("HandleBasicEvent()--> **** Using x<"<<temp[0]<<"> y<"<<temp[1]<<"> width<"<<temp[2]<<"> height<"<<temp[3]<<"> ****")
				rVal->rv=window->ShowInternal(temp[0],temp[1],temp[2],temp[3]);
				JREX_LOGLN("HandleBasicEvent ShowInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_DISPOSE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_DISPOSE EVENT!!!****")
				rVal->rv=window->DisposeInternal();
				JREX_LOGLN("HandleBasicEvent DisposeInternal rv<"<<rVal->rv<<">****")
				break;
			}
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
			case JREX_CREATE_GTK:
			{
				JREX_LOGLN("HandleBasicEvent JREX_CREATE_GTK EVENT!!!****")
				GtkWidget* widg=gtk_window_new (GTK_WINDOW_POPUP);
				if(NOT_NULL(widg))
					gtk_widget_realize(widg);
				rVal->rData=widg;
				break;
			}
			case JREX_GOT_VISUAL:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GOT_VISUAL EVENT!!!****")
				nsNativeWidget parentWnd=NS_REINTERPRET_CAST(nsNativeWidget, event->eventData);
				JREX_LOGLN("HandleBasicEvent parentWnd <"<<parentWnd<<">****")
				rVal->rv=window->GotVisualInternal(parentWnd);
				JREX_LOGLN("HandleBasicEvent GotVisualInternal rv<"<<rVal->rv<<">****")
				break;
			}
#endif
			case JREX_GET_BOUNDS:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_BOUNDS EVENT!!!****")
				PRInt32* temp=new PRInt32[4];
				if(temp && window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->GetPositionAndSize(&temp[0],&temp[1],&temp[2],&temp[3]);
					JREX_LOGLN("HandleBasicEvent()--> **** GetPositionAndSize rv<"<<rVal->rv<<"> Got x<"<<temp[0]<<"> y<"<<temp[1]<<"> width<"<<temp[2]<<"> height<"<<temp[3]<<"> ****")
				}
				rVal->rData=temp;
				break;
			}
			case JREX_SET_BOUNDS:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SET_BOUNDS EVENT!!!****")
				PRInt32* temp=NS_REINTERPRET_CAST(PRInt32*, event->eventData);
				JREX_LOGLN("HandleBasicEvent()--> **** Using x<"<<temp[0]<<"> y<"<<temp[1]<<"> width<"<<temp[2]<<"> height<"<<temp[3]<<"> ****")
				rVal->rv=window->SetBoundsInternal(temp[0],temp[1],temp[2],temp[3]);
				JREX_LOGLN("HandleBasicEvent SetBoundsInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_IS_VISIBLE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_IS_VISIBLE EVENT!!!****")
				PRBool visible=PR_FALSE;
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->GetVisibility(&visible);
					JREX_LOGLN("HandleBasicEvent()--> **** GetVisibility rv<"<<rVal->rv<<"> visible<"<<visible<<"> ****")
				}
				rVal->rData=(void*)visible;
				break;
			}
			case JREX_SET_VISIBLE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SET_VISIBLE EVENT!!!****")
				PRBool visible=(PRBool)event->eventData;
				JREX_LOGLN("HandleBasicEvent()--> **** Using visible<"<<visible<<"> ****")
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->SetVisibility(visible);
					JREX_LOGLN("HandleBasicEvent SetVisibility rv<"<<rVal->rv<<">****")
				}
				break;
			}
			case JREX_IS_ENABLED:
			{
				JREX_LOGLN("HandleBasicEvent JREX_IS_ENABLED EVENT!!!****")
				PRBool enabled=PR_FALSE;
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->GetEnabled(&enabled);
					JREX_LOGLN("HandleBasicEvent()--> **** GetEnabled rv<"<<rVal->rv<<"> enabled<"<<enabled<<"> ****")
				}
				rVal->rData=(void*)enabled;
				break;
			}
			case JREX_SET_ENABLED:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SET_ENABLED EVENT!!!****")
				PRBool enabled=(PRBool)event->eventData;
				JREX_LOGLN("HandleBasicEvent()--> **** Using enabled<"<<enabled<<"> ****")
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->SetEnabled(enabled);
					JREX_LOGLN("HandleBasicEvent SetEnabled rv<"<<rVal->rv<<">****")
				}
				break;
			}
			case JREX_REPAINT:
			{
				JREX_LOGLN("HandleBasicEvent JREX_REPAINT EVENT!!!****")
				PRBool force=(PRBool)event->eventData;
				JREX_LOGLN("HandleBasicEvent()--> **** Using force<"<<force<<"> ****")
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->Repaint(force);
					JREX_LOGLN("HandleBasicEvent Repaint rv<"<<rVal->rv<<">****")
				}
				break;
			}
			case JREX_CHANGE_FOCUS:
			{
				JREX_LOGLN("HandleBasicEvent JREX_CHANGE_FOCUS EVENT!!!****")
				PRBool focusGained=(PRBool)event->eventData;
				JREX_LOGLN("HandleBasicEvent()--> **** Using focusGained<"<<focusGained<<"> ****")
				rVal->rv=window->ChangeFocusInternal(focusGained);
				JREX_LOGLN("HandleBasicEvent ChangeFocusInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_GRAB_FOCUS:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GRAB_FOCUS EVENT!!!****")
				rVal->rv=window->GrabFocusInternal();
				JREX_LOGLN("HandleBasicEvent GrabFocusInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_MOVE_FOCUS:
			{
				JREX_LOGLN("HandleBasicEvent JREX_MOVE_FOCUS EVENT!!!****")
				PRBool forward=(PRBool)event->eventData;
				JREX_LOGLN("HandleBasicEvent()--> **** Using forward<"<<forward<<"> ****")
				rVal->rv=window->MoveFocusInternal(forward);
				JREX_LOGLN("HandleBasicEvent MoveFocusInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_GET_FOCUSED_ELE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_FOCUSED_ELE EVENT!!!****")
				nsCOMPtr<nsIDOMElement> myEle;
				rVal->rv=window->GetFocusedElementInternal(getter_AddRefs(myEle));
				JREX_LOGLN("HandleBasicEvent GetFocusedElementInternal rv<"<<rVal->rv<<">****")
				nsIDOMElement* temp=nsnull;
				if(NS_SUCCEEDED(rVal->rv))
					NS_IF_ADDREF(temp=myEle.get());

				rVal->rData=temp;
				break;
			}
			case JREX_SET_FOCUSED_ELE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SET_FOCUSED_ELE EVENT!!!****")
				nsIDOMElement* myEle=NS_REINTERPRET_CAST(nsIDOMElement*, event->eventData);
				JREX_LOGLN("HandleBasicEvent Using myEle<"<<myEle<<">****")
				rVal->rv=window->SetFocusedElementInternal(myEle);
				JREX_LOGLN("HandleBasicEvent SetFocusedElementInternal rv<"<<rVal->rv<<">****")
				break;
			}
			case JREX_SET_TITLE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_SET_TITLE EVENT!!!****")
				PRUnichar* title=NS_REINTERPRET_CAST(PRUnichar*, event->eventData);
				JREX_LOGLN("HandleBasicEvent()--> **** Using title<"<<title<<">***")
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->SetTitle(title);
					JREX_LOGLN("HandleBasicEvent SetTitle rv<"<<rVal->rv<<">****")
				}
				break;
			}
			case JREX_GET_TITLE:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_TITLE EVENT!!!****")
				PRUnichar* title=nsnull;
				if(window->mBeingDisposed==PR_FALSE){
					rVal->rv=window->mBaseWindow->GetTitle(&title);
					JREX_LOGLN("HandleBasicEvent()--> **** GetTitle rv<"<<rVal->rv<<"> title<"<<title<<">***")
				}
				rVal->rData=title;
				break;
			}
			case JREX_GET_SELECTION:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_SELECTION EVENT!!!****")
				nsISelection *temp=nsnull;
				rVal->rv=window->GetSelectionInternal(&temp);
				JREX_LOGLN("HandleBasicEvent()--> **** GetSelectionInternal rv<"<<rVal->rv<<"> temp<"<<temp<<">***")
				rVal->rData=temp;
				break;
			}
			case JREX_GET_DOC_SHELL:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_DOC_SHELL EVENT!!!****")
				nsIDocShell* tmpDocShell=nsnull;
				rVal->rv=window->GetDocShellInternal(&tmpDocShell);
				JREX_LOGLN("HandleBasicEvent()--> **** GetSelectionInternal rv<"<<rVal->rv<<"> tmpDocShell<"<<tmpDocShell<<">***")
				rVal->rData=tmpDocShell;
				break;
			}
			case JREX_GET_ROOT_DOC_SHELL:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_ROOT_DOC_SHELL EVENT!!!****")
				nsIDocShell* tmpDocShell=nsnull;
				rVal->rv=window->GetRootDocShellInternal(&tmpDocShell);
				JREX_LOGLN("HandleBasicEvent()--> **** GetRootDocShellInternal rv<"<<rVal->rv<<"> tmpDocShell<"<<tmpDocShell<<">***")
				rVal->rData=tmpDocShell;
				break;
			}
			case JREX_GET_IS_DOC_LOADING:
			{
				JREX_LOGLN("HandleBasicEvent JREX_GET_IS_DOC_LOADING EVENT!!!****")
				PRBool isLoading=PR_FALSE;
				rVal->rv=window->GetIsLoadingDocumentInternal(&isLoading);
				JREX_LOGLN("HandleBasicEvent()--> **** GetIsLoadingDocumentInternal rv<"<<rVal->rv<<"> isLoading<"<<isLoading<<"> ****")
				rVal->rData=(void*)isLoading;
				break;
			}
			case JREX_DUMMY://used to wake up event queue, required for modal dialogs
			{
				JREX_LOGLN("HandleBasicEvent JREX_DUMMY EVENT!!!****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandleBasicEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleBasicEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK  JRexWindow::DestroyBasicEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyBasicEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData){
			if(event->eventType==JREX_SHOW || event->eventType==JREX_SET_BOUNDS){
				PRInt32* evtData = NS_REINTERPRET_CAST(PRInt32*, event->eventData);
				delete evtData;
			}
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
