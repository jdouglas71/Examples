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

	nsresult JRexWindow::AddProgressListener(){
		if(mBrowCreated!=PR_FALSE)
			mProgListenerAdded=PR_TRUE;
		return NS_OK;
	}

	nsresult JRexWindow::AddContextMenuListenerInternal(){
		if(WINDOW_NOT_VALID || mContextListenerAdded)return NS_OK;
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		nsresult rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
		JREX_RETURN_IF_FAILED(rv,"AddContextMenuListenerInternal()--> **** CallQueryInterface nsISupportsWeakReference****")

		nsCOMPtr<nsIWeakReference> weakRef;
		rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
		JREX_RETURN_IF_FAILED(rv,"AddContextMenuListenerInternal()--> **** GetWeakReference Failed ****")
		JREX_LOGLN("AddContextMenuListenerInternal()--> **** GetWeakReference Done ****")

		rv=mWebBrowser->AddWebBrowserListener(weakRef,nsIContextMenuListener2::GetIID());
		JREX_LOGLN("AddContextMenuListenerInternal()--> **** AddWebBrowserListener nsIContextMenuListener rv <"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			mContextListenerAdded=PR_TRUE;
		return rv;
	}

	nsresult JRexWindow::AddContextMenuListener(){
		JREX_LOGLN("AddContextMenuListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mContextListenerAdded<"<<mContextListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || mContextListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddContextMenuListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_CTX_MENU_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("AddContextMenuListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::AddHistoryListenerInternal(){
		if(WINDOW_NOT_VALID || mHistoryListenerAdded)return NS_OK;
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		nsresult rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
		JREX_RETURN_IF_FAILED(rv,"AddHistoryListenerInternal()--> **** CallQueryInterface nsISupportsWeakReference ****")

		nsCOMPtr<nsIWeakReference> weakRef;
		rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
		JREX_RETURN_IF_FAILED(rv,"AddHistoryListenerInternal()--> **** GetWeakReference ****")

		rv=mWebBrowser->AddWebBrowserListener(weakRef,nsISHistoryListener::GetIID());
		JREX_LOGLN("AddHistoryListenerInternal()--> **** AddWebBrowserListener nsISHistoryListener rv <"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			mHistoryListenerAdded=PR_TRUE;
		return rv;
	}

	nsresult JRexWindow::AddHistoryListener(){
		JREX_LOGLN("AddHistoryListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mHistoryListenerAdded<"<<mHistoryListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || mHistoryListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddHistoryListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_HISTORY_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("AddHistoryListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::AddKeyListenerInternal(){
		if(WINDOW_NOT_VALID || mKeyListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMKeyListener *, this));
		nsresult rv = mEventReceiver->AddEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMKeyListener));
		JREX_LOGLN("AddKeyListenerInternal()--> **** AddEventListenerByIID rv<"<<rv<<"> ****")

		if(NS_SUCCEEDED(rv))
			mKeyListenerAdded=PR_TRUE;
		return rv;
	}

	nsresult JRexWindow::AddKeyListener(){
		JREX_LOGLN("AddKeyListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mKeyListenerAdded<"<<mKeyListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || mKeyListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddKeyListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_KEY_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("AddKeyListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::AddMouseListenerInternal(){
		if(WINDOW_NOT_VALID || mMouseListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMMouseListener *, this));
		nsresult rv = mEventReceiver->AddEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMMouseListener));
		JREX_LOGLN("AddMouseListener()--> **** AddEventListenerByIID rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			mMouseListenerAdded=PR_TRUE;
		return rv;
	}

	nsresult JRexWindow::AddMouseListener(){
		JREX_LOGLN("AddMouseListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mMouseListenerAdded<"<<mMouseListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || mMouseListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddMouseListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_MOUSE_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("AddMouseListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::AddMouseMotionListenerInternal(){
		if(WINDOW_NOT_VALID || mMouseMotionListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMMouseMotionListener *, this));
		nsresult rv = mEventReceiver->AddEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMMouseMotionListener));
		JREX_LOGLN("AddMouseMotionListenerInternal()--> **** AddEventListenerByIID rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			mMouseMotionListenerAdded=PR_TRUE;
		return rv;
	}


	nsresult JRexWindow::AddMouseMotionListener(){
		JREX_LOGLN("AddMouseMotionListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mMouseMotionListenerAdded<"<<mMouseMotionListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || mMouseMotionListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddMouseMotionListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_MOUSE_MOTION_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("AddMouseMotionListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::RemoveProgressListener(){
		mProgListenerAdded=PR_FALSE;
		return NS_OK;
	}

	nsresult JRexWindow::RemoveContextMenuListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mContextListenerAdded)return NS_OK;
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		nsresult rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
		JREX_LOGLN("RemoveContextMenuListenerInternal()--> **** CallQueryInterface nsISupportsWeakReference rv <"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)){
			nsCOMPtr<nsIWeakReference> weakRef;
			rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
			if (NS_SUCCEEDED(rv)){
				rv=mWebBrowser->RemoveWebBrowserListener(weakRef,nsIContextMenuListener2::GetIID());
				JREX_LOGLN("RemoveContextMenuListenerInternal()--> **** RemoveWebBrowserListener nsIContextMenuListener rv <"<<rv<<"> ****")
			}
		}
		mContextListenerAdded=PR_FALSE;
		return rv;
	}

	nsresult JRexWindow::RemoveContextMenuListener(){
		JREX_LOGLN("RemoveContextMenuListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mContextListenerAdded<"<<mContextListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mContextListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveContextMenuListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_CTX_MENU_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("RemoveContextMenuListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::RemoveHistoryListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mHistoryListenerAdded)return NS_OK;
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		nsresult rv=CallQueryInterface(this, NS_STATIC_CAST(nsISupportsWeakReference**,getter_AddRefs(supportsWeak)));
		JREX_LOGLN("RemoveHistoryListenerInternal()--> **** CallQueryInterface nsISupportsWeakReference rv <"<<rv<<"> ****")
		if (NS_SUCCEEDED(rv)){
			nsCOMPtr<nsIWeakReference> weakRef;
			rv=supportsWeak->GetWeakReference(getter_AddRefs(weakRef));
			if (NS_SUCCEEDED(rv)){
				rv=mWebBrowser->RemoveWebBrowserListener(weakRef,nsISHistoryListener::GetIID());
				JREX_LOGLN("RemoveHistoryListenerInternal()--> **** RemoveWebBrowserListener nsISHistoryListener rv <"<<rv<<"> ****")
			}
		}
		mHistoryListenerAdded=PR_FALSE;
		return rv;
	}


	nsresult JRexWindow::RemoveHistoryListener(){
		JREX_LOGLN("RemoveHistoryListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mHistoryListenerAdded<"<<mHistoryListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mHistoryListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveHistoryListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_HISTORY_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("RemoveHistoryListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::RemoveKeyListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mKeyListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMKeyListener *, this));
		nsresult rv = mEventReceiver->RemoveEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMKeyListener));
		JREX_LOGLN("RemoveKeyListenerInternal()--> **** RemoveEventListenerByIID rv<"<<rv<<"> ****")
		mKeyListenerAdded=PR_FALSE;
		return rv;
	}

	nsresult JRexWindow::RemoveKeyListener(){
		JREX_LOGLN("RemoveKeyListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mKeyListenerAdded<"<<mKeyListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mKeyListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveKeyListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_KEY_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("RemoveKeyListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::RemoveMouseListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mMouseListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMMouseListener *, this));
		nsresult rv = mEventReceiver->RemoveEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMMouseListener));
		JREX_LOGLN("RemoveMouseListenerInternal()--> **** RemoveEventListenerByIID rv<"<<rv<<"> ****")
		mMouseListenerAdded=PR_FALSE;
		return rv;
	}

	nsresult JRexWindow::RemoveMouseListener(){
		JREX_LOGLN("RemoveMouseListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mMouseListenerAdded<"<<mMouseListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mMouseListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveMouseListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_MOUSE_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("RemoveMouseListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::RemoveMouseMotionListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mMouseMotionListenerAdded)return NS_OK;
  		nsIDOMEventListener *eventListener =
				NS_STATIC_CAST(nsIDOMEventListener *,
					NS_STATIC_CAST(nsIDOMMouseMotionListener *, this));
		nsresult rv = mEventReceiver->RemoveEventListenerByIID(eventListener,
					     			NS_GET_IID(nsIDOMMouseMotionListener));
		JREX_LOGLN("RemoveMouseMotionListenerInternal()--> **** RemoveEventListenerByIID rv<"<<rv<<"> ****")
		mMouseListenerAdded=PR_FALSE;
		return rv;
	}

	nsresult JRexWindow::RemoveMouseMotionListener(){
		JREX_LOGLN("RemoveMouseMotionListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mMouseMotionListenerAdded<"<<mMouseMotionListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mMouseMotionListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveMouseMotionListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_MOUSE_MOTION_LISTENER,nsnull, PR_FALSE, HandleListenerEvent,DestroyListenerEvent,nsnull);
		JREX_LOGLN("RemoveMouseMotionListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	void* PR_CALLBACK JRexWindow::HandleListenerEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleListenerEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case ADD_KEY_LISTENER:
			{
				rVal->rv=window->AddKeyListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** AddKeyListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case ADD_MOUSE_LISTENER:
			{
				rVal->rv=window->AddMouseListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** AddMouseListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case ADD_MOUSE_MOTION_LISTENER:
			{
				rVal->rv=window->AddMouseMotionListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** AddMouseMotionListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case ADD_HISTORY_LISTENER:
			{
				rVal->rv=window->AddHistoryListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** AddHistoryListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case ADD_CTX_MENU_LISTENER:
			{
				rVal->rv=window->AddContextMenuListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** AddContextMenuListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_KEY_LISTENER:
			{
				rVal->rv=window->RemoveKeyListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** RemoveKeyListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_MOUSE_LISTENER:
			{
				rVal->rv=window->RemoveMouseListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** RemoveMouseListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_MOUSE_MOTION_LISTENER:
			{
				rVal->rv=window->RemoveMouseMotionListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** RemoveMouseMotionListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_HISTORY_LISTENER:
			{
				rVal->rv=window->RemoveHistoryListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** RemoveHistoryListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_CTX_MENU_LISTENER:
			{
				rVal->rv=window->RemoveContextMenuListenerInternal();
				JREX_LOGLN("HandleListenerEvent()--> **** RemoveContextMenuListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandleListenerEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleListenerEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexWindow::DestroyListenerEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyListenerEvent()--> **** event <"<<event<<"> ****")
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
