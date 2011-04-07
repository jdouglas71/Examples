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
 	using namespace JRex_JNI_WindowEvent;

	NS_IMETHODIMP JRexWindow::SetDimensions(PRUint32 flags, PRInt32 x,
										PRInt32 y, PRInt32 cx, PRInt32 cy){
		JREX_LOGLN("nsIEmbeddingSiteWindow2Impl -->SetDimensions()-->**** flags<"<<flags<<"> x<"<<x<<"> y<"<<y<<"> cx<"<<cx<<"> cy<"<<cy<<">****")
		if(mBeingDisposed)return NS_OK;
		if (flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION &&
				(flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
			nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER))) {
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
			if(NOT_NULL(mMainWnd)){
				gtk_widget_set_usize((GtkWidget*)mMainWnd, cx, cy);
				gdk_window_move_resize(((GtkWidget*)mMainWnd)->window,x, y, cx, cy);
			}
#endif
			return mBaseWindow->SetPositionAndSize(x, y, cx, cy, PR_TRUE);
		}
		else if (flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION) {
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
			if(NOT_NULL(mMainWnd))
				gdk_window_move(((GtkWidget*)mMainWnd)->window,x, y);
#endif
			return mBaseWindow->SetPosition(x, y);
		}
		else if (flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
			 				nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER)) {
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
			if(NOT_NULL(mMainWnd)){
				gtk_widget_set_usize((GtkWidget*)mMainWnd, cx, cy);
				gdk_window_resize(((GtkWidget*)mMainWnd)->window, cx, cy);
			}
#endif
			return mBaseWindow->SetSize(cx, cy, PR_TRUE);
		}
		return NS_ERROR_INVALID_ARG;
	}


	NS_IMETHODIMP JRexWindow::GetDimensions(PRUint32 flags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy){
		if(mBeingDisposed)return NS_OK;
		JREX_LOGLN("nsIEmbeddingSiteWindow2Impl -->GetDimensions()")
		if (flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION
				&& (flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER
					| nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER))) {
				return mBaseWindow->GetPositionAndSize(x, y, cx, cy);
		}
		else if (flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION) {
			return mBaseWindow->GetPosition(x, y);
		}
		else if (flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER
						| nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER)) {
			return mBaseWindow->GetSize(cx, cy);
		}
		return NS_ERROR_INVALID_ARG;
	}


	NS_IMETHODIMP JRexWindow::SetFocus(){
		if(mBeingDisposed)return NS_OK;
		return mBaseWindow->SetFocus();
	}


	NS_IMETHODIMP JRexWindow::GetVisibility(PRBool *aVisibility){
		  return IsVisible(aVisibility);
	}

	NS_IMETHODIMP JRexWindow::SetVisibility(PRBool aVisibility){
		return SetVisible(aVisibility);
	}


	NS_IMETHODIMP JRexWindow::GetTitle(PRUnichar * *aTitle){
	  *aTitle = mTitle;
	  return NS_OK;
	}

	NS_IMETHODIMP JRexWindow::SetTitle(const PRUnichar * aTitle){
		JREX_LOGLN("SetTitle()--> **** Title <"<<aTitle<<">****")

		nsEmbedString titleStr(aTitle);
		mTitle = ToNewUnicode(titleStr);

		char* temp=ToNewUTF8String(titleStr);
		JREX_LOGLN("SetTitle()--> ***  Title is <"<<temp<<"> ***")

		WindowTitleEventParam *wParm=new WindowTitleEventParam;
		if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;

		wParm->target=NS_PTR_TO_INT32(this);
		wParm->winEventType=WIN_SET_TITLE_EVENT;
		wParm->title=temp;
		nsresult rv=fireEvent(wParm,PR_FALSE,nsnull);
		JREX_LOGLN("SetTitle()--> *** fireEvent rv<"<<rv<<"> ***")
		return rv;
	}


	NS_IMETHODIMP JRexWindow::GetSiteWindow(void * *aSiteWindow){
	  *aSiteWindow = mMainWnd;
	  return NS_OK;
	}

	NS_IMETHODIMP JRexWindow::Blur(){
		JREX_LOGLN("Blur()--> **** @@@@@@@ nsIEmbeddingSiteWindow2Impl @@@@@ ****")
		return NS_OK;
	}
