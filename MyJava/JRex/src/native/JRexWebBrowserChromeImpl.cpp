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
 	#include "JRex_JNI_WindowEvent.h"
 	#include "JRex_JNI_ProgressEvent.h"

 	using namespace JRex_JNI_WindowEvent;
 	using namespace JRex_JNI_ProgressEvent;

	static NS_DEFINE_CID(kAppShellCID, NS_APPSHELL_CID);
	static NS_DEFINE_CID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);

	/* void setStatus (in unsigned long statusType, in wstring status); */
	NS_IMETHODIMP JRexWindow::SetStatus(PRUint32 statusType, const PRUnichar *status)
	{
		JREX_LOGLN("SetStatus()--> **** mProgListenerAdded <"<<mProgListenerAdded<<"> ****")
		if(!mProgListenerAdded || IS_NULL(status))return NS_OK;

		nsEmbedString statusStr(status);
		char* temp=ToNewUTF8String(statusStr);
		JREX_LOGLN("SetStatus()--> ***  statusType<"<<statusType<<"> status<"<<temp<<"> ***")

		StatusChangeProgressEventParam *sParm=new StatusChangeProgressEventParam;
		if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;
		sParm->target=NS_PTR_TO_INT32(this);
		sParm->progEventType=PROG_LINK_STATUS_CHANGE;
		SetCommonParam(sParm,nsnull,nsnull);
		sParm->status=statusType;
		sParm->statusMessage=temp;
		nsresult rv=JRex_JNI_ProgressEvent::fireEvent(sParm,PR_FALSE,nsnull);
		JREX_LOGLN("SetStatus()--> *** fireEvent rv<"<<rv<<"> ***")
		return rv;
	}

	/* attribute nsIWebBrowser webBrowser; */
	NS_IMETHODIMP JRexWindow::GetWebBrowser(nsIWebBrowser * *aWebBrowser)
	{
		JREX_LOGLN("GetWebBrowser()--> **** I AM HERE ****")
		NS_ENSURE_ARG_POINTER(aWebBrowser);
		*aWebBrowser = mWebBrowser;
		NS_IF_ADDREF(*aWebBrowser);
  		return NS_OK;
	}

	NS_IMETHODIMP JRexWindow::SetWebBrowser(nsIWebBrowser * aWebBrowser)
	{
		JREX_LOGLN("SetWebBrowser()--> **** I AM HERE ****")
		mWebBrowser = aWebBrowser;
  		return NS_OK;
	}

	/* attribute unsigned long chromeFlags; */
	NS_IMETHODIMP JRexWindow::GetChromeFlags(PRUint32 *aChromeFlags)
	{
		JREX_LOGLN("GetChromeFlags()--> **** I AM HERE ****")
		NS_ENSURE_ARG_POINTER(aChromeFlags);
		*aChromeFlags=mChromeFlag;
		return NS_OK;

	}

	NS_IMETHODIMP JRexWindow::SetChromeFlags(PRUint32 aChromeFlags)
	{
		JREX_LOGLN("SetChromeFlags()--> **** aChromeFlags<"<<aChromeFlags<<">  ****")
		if(mChromeFlag!=aChromeFlags){
			WindowChromeEventParam *wParm=new WindowChromeEventParam;
			if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;
			wParm->target=NS_PTR_TO_INT32(this);
			wParm->winEventType=WIN_CHROME_FLAG_EVENT;
			wParm->chromeFlags=aChromeFlags;
			nsresult rv=JRex_JNI_WindowEvent::fireEvent(wParm,PR_FALSE,nsnull);
			JREX_LOGLN("SetChromeFlags()--> *** fireEvent rv<"<<rv<<"> ***")
		}
		mChromeFlag=aChromeFlags;
		return NS_OK;
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

	/* void destroyBrowserWindow (); */
	NS_IMETHODIMP JRexWindow::DestroyBrowserWindow()
	{
		JREX_LOGLN("DestroyBrowserWindow()--> **** Destroy<"<<NS_PTR_TO_INT32(this)<<"> ****")
		mBeingDisposed=PR_TRUE;
		if(NOT_NULL(mWebBrowser)){
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
			if(NOT_NULL(mMainWnd)){
				GtkWidget *child = GTK_BIN(mMainWnd)->child;
				GtkObject *gtkObj= NOT_NULL(child)?GTK_OBJECT(child):NULL;
				if(NOT_NULL(gtkObj) && mSignaled){
					gtk_signal_disconnect_by_func(gtkObj,GTK_SIGNAL_FUNC(HandleFocusIn),this);
					gtk_signal_disconnect_by_func(gtkObj,GTK_SIGNAL_FUNC(HandleFocusOut),this);
				}
			}
			mSignaled=PR_FALSE;
#endif
			nsresult rv=mWebBrowser->SetContainerWindow(nsnull);
			JREX_LOGLN("DestroyBrowserWindow()--> *** SetContainerWindow null rv<"<<rv<<"> ***")
			if(NOT_NULL(mBaseWindow)){
				rv=mBaseWindow->Destroy();
				JREX_LOGLN("DestroyBrowserWindow()--> **** mBaseWindow Destroy rv<"<<rv<<">****")
				mBaseWindow=nsnull;
			}
		}
		BasicWindowEventParam *wParm=new BasicWindowEventParam;
		if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;
		wParm->target=NS_PTR_TO_INT32(this);
		wParm->winEventType=WIN_DESTROY_EVENT;
		nsresult rv=JRex_JNI_WindowEvent::fireEvent(wParm,PR_FALSE,nsnull);
		JREX_LOGLN("DestroyBrowserWindow()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* void sizeBrowserTo (in long aCX, in long aCY); */
	NS_IMETHODIMP JRexWindow::SizeBrowserTo(PRInt32 aCX, PRInt32 aCY)
	{
		if(mBeingDisposed)return NS_OK;
		JREX_LOGLN("SizeBrowserTo()--> ***  aCX<"<<aCX<<"> aCY<"<<aCY<<"> ***")
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		if(NOT_NULL(mMainWnd)){
			gtk_widget_set_usize((GtkWidget*)mMainWnd, aCX, aCY);
			gdk_window_resize(((GtkWidget*)mMainWnd)->window,aCX, aCY);
		}
#endif
		mBaseWindow->SetSize(aCX,aCY,PR_FALSE);
		WindowReSizeEventParam *wParm=new WindowReSizeEventParam;
		if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;

		wParm->target=NS_PTR_TO_INT32(this);
		wParm->winEventType=WIN_RESIZE_EVENT;
		wParm->xSize=aCX;
		wParm->ySize=aCY;
		nsresult rv=JRex_JNI_WindowEvent::fireEvent(wParm,PR_FALSE,nsnull);
		JREX_LOGLN("SizeBrowserTo()--> *** fireEvent rv<"<<rv<<"> ***")
		return rv;
	}

	static inline nsresult processMainEvents(){
		PLEvent* event=nsnull;
		PRBool eventAvail=PR_FALSE;
		gEventQ->EventAvailable(eventAvail);
		if(eventAvail){
			nsresult rv=gEventQ->GetEvent(&event);
			if (NS_SUCCEEDED(rv))
				rv=gEventQ->HandleEvent(event);
		}
		return NS_OK;
	}

	/* void showAsModal (); */
	NS_IMETHODIMP JRexWindow::ShowAsModal()
	{
		JREX_LOGLN("ShowAsModal()--> **** I AM HERE ****")
		mIsModal=PR_TRUE;
		mInModalLoop=PR_TRUE;

		WindowSetModalEventParam *wParm=new WindowSetModalEventParam;
		if(IS_NULL(wParm)){
			if(mParentIntPtr>0){
				JRexWindow *temp=(JRexWindow *)NS_INT32_TO_PTR(mParentIntPtr);
				if(IsWindowAvailable(temp))
					temp->mChildIsModalLooping=PR_FALSE;
			}
			mIsModal = PR_FALSE;
			mInModalLoop=PR_FALSE;
			return NS_ERROR_OUT_OF_MEMORY;
		}

		wParm->target=NS_PTR_TO_INT32(this);
		wParm->winEventType=WIN_SETMODAL_EVENT;
		wParm->isModal=PR_TRUE;
		nsresult rv=JRex_JNI_WindowEvent::fireEvent(wParm,PR_FALSE,nsnull);
		JREX_LOGLN("ShowAsModal()--> *** fireEvent rv<"<<rv<<"> ***")

		nsCOMPtr<nsIWidget> window;
		rv=mBaseWindow->GetMainWidget(getter_AddRefs(window));
		JREX_RETURN_IF_FAILED(rv,"ShowAsModal()--> *** GetMainWidget")

#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		nsCOMPtr<nsIThreadJSContextStack> stack(do_GetService("@mozilla.org/js/xpc/ContextStack;1"));
		if (stack && NS_SUCCEEDED(stack->Push(nsnull))) {
			while (NS_SUCCEEDED(rv) && mIsModal) {
				if(gtk_events_pending())
					gtk_main_iteration();
				processMainEvents();
			}
			JSContext* cx=nsnull;
			stack->Pop(&cx);
			NS_ASSERTION(!cx, "ShowAsModal()--> *** JSContextStack mismatch ***");
		} else
			rv = NS_ERROR_FAILURE;
#else
		nsCOMPtr<nsIAppShell> appShell(do_CreateInstance(kAppShellCID,&rv));
		JREX_RETURN_IF_FAILED(rv,"ShowAsModal()--> *** do_CreateInstance appShell")

		rv=appShell->Create(0, nsnull);
		JREX_RETURN_IF_FAILED(rv,"ShowAsModal()--> *** Create appShell")

		rv=appShell->Spinup();
		JREX_RETURN_IF_FAILED(rv,"ShowAsModal()--> *** Spinup appShell")

		nsCOMPtr<nsIThreadJSContextStack> stack(do_GetService("@mozilla.org/js/xpc/ContextStack;1"));
		if (stack && NS_SUCCEEDED(stack->Push(nsnull))) {
			while (NS_SUCCEEDED(rv) && mIsModal) {
				processMainEvents();//reqired for modal over modal dialog.
				void* event=nsnull;
				PRBool isRealEvent;
				PRBool processEvent;
				rv = appShell->GetNativeEvent(isRealEvent, event);
				if (NS_SUCCEEDED(rv)) {
					window->ModalEventFilter(isRealEvent, event, &processEvent);
					if (processEvent)
						appShell->DispatchNativeEvent(isRealEvent, event);
				}
			}
			JSContext* cx=nsnull;
			stack->Pop(&cx);
			NS_ASSERTION(!cx, "ShowAsModal()--> *** JSContextStack mismatch ***");
		} else
			rv = NS_ERROR_FAILURE;
		rv=appShell->Spindown();
		JREX_LOGLN("ShowAsModal()--> *** Spindown appShell rv<"<<rv<<">***")
#endif
		mIsModal = PR_FALSE;

		JREX_LOGLN("ShowAsModal()--> *** mParentIntPtr<"<<mParentIntPtr<<"> ***")
		if(mParentIntPtr>0){
			JREX_LOGLN("ShowAsModal()--> **** tempParentIntPtr<"<<mParentIntPtr<<"> ****")
			JRexWindow *myParent=(JRexWindow *)NS_INT32_TO_PTR(mParentIntPtr);
			if(IsWindowAvailable(myParent)){
				JREX_LOGLN("ShowAsModal()--> **** ChildIsModalLooping<"<<myParent->mChildIsModalLooping<<"> ****")
				myParent->mChildIsModalLooping=PR_FALSE;
			}
		}
		mInModalLoop=PR_FALSE;
		return mModalStatus;
	}

	/* boolean isWindowModal (); */
	NS_IMETHODIMP JRexWindow::IsWindowModal(PRBool *_retval)
	{
		JREX_LOGLN("IsWindowModal()--> **** mIsModal<"<<mIsModal<<"> ****")
		NS_ENSURE_ARG_POINTER(_retval);
		*_retval=mIsModal;
		return NS_OK;
	}

	/* void exitModalEventLoop (in nsresult aStatus); */
	NS_IMETHODIMP JRexWindow::ExitModalEventLoop(nsresult aStatus)
	{
		JREX_LOGLN("ExitModalEventLoop()--> **** aStatus<"<<aStatus<<"> ****")
		mModalStatus=aStatus;
		mIsModal=PR_FALSE;

		WindowSetModalEventParam *wParm=new WindowSetModalEventParam;
		if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;

		wParm->target=NS_PTR_TO_INT32(this);
		wParm->winEventType=WIN_SETMODAL_EVENT;
		wParm->isModal=PR_FALSE;
		nsresult rv=JRex_JNI_WindowEvent::fireEvent(wParm,PR_FALSE,nsnull);
		JREX_LOGLN("ExitModalEventLoop()--> *** fireEvent rv<"<<rv<<"> ***")
		return rv;
	}
