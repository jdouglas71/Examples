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


	nsresult JRexWindow::AddURIContentListenerInternal(){
		if(WINDOW_NOT_VALID || mURIContentListenerAdded)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIURILoader> uriLoader(do_GetService(NS_URI_LOADER_CONTRACTID,&rv));
		JREX_LOGLN("AddURIContentListenerInternal()--> **** do_GetService nsIURILoader rv<"<<rv<<"> ****")
		if(uriLoader){
			rv = uriLoader->RegisterContentListener(this);
			JREX_LOGLN("AddURIContentListenerInternal()--> **** RegisterContentListener rv<"<<rv<<"> ****")
		mURIContentListenerAdded=NS_SUCCEEDED(rv);
		}
		return rv;
	}


	nsresult JRexWindow::AddURIContentListener(){
		if(WINDOW_NOT_VALID || mURIContentListenerAdded)return NS_OK;
		if(IS_EQT)
			return AddURIContentListenerInternal();
		nsresult rv=ExecInEventQ(this, ADD_URI_CONTENT_LISTENER,nsnull, PR_FALSE, HandleURIListenerEvent,DestroyURIListenerEvent,nsnull);
		JREX_LOGLN("AddURIContentListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::RemoveURIContentListenerInternal(){
		if(mBrowCreated==PR_FALSE || !mURIContentListenerAdded)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIURILoader> uriLoader(do_GetService(NS_URI_LOADER_CONTRACTID,&rv));
		JREX_LOGLN("RemoveURIContentListenerInternal()--> **** do_GetService nsIURILoader rv<"<<rv<<"> ****")
		if(uriLoader){
			rv = uriLoader->UnRegisterContentListener(this);
			JREX_LOGLN("RemoveURIContentListenerInternal()--> **** UnRegisterContentListener rv<"<<rv<<"> ****")
			mURIContentListenerAdded=NS_SUCCEEDED(rv);
		}
		//nsresult rv= mWebBrowser->SetParentURIContentListener(nsnull);
		//JREX_LOGLN("AddURIContentListenerInternal()--> **** SetParentURIContentListener  rv<"<<rv<<"> ****")
		mURIContentListenerAdded=PR_FALSE;
		return rv;
	}

	nsresult JRexWindow::RemoveURIContentListener(){
		JREX_LOGLN("RemoveURIContentListener()--> **** mBrowCreated<"<<mBrowCreated<<"> mURIContentListenerAdded<"<<mURIContentListenerAdded<<"> ****")
		if(WINDOW_NOT_VALID || !mURIContentListenerAdded)return NS_OK;
		if(IS_EQT)
			return RemoveURIContentListenerInternal();
		nsresult rv=ExecInEventQ(this, REMOVE_URI_CONTENT_LISTENER,nsnull, PR_FALSE, HandleURIListenerEvent,DestroyURIListenerEvent,nsnull);
		JREX_LOGLN("RemoveURIContentListener()--> **** ExecInEventQ  rv<"<<rv<<"> ****")
		return rv;
	}

	void* PR_CALLBACK JRexWindow::HandleURIListenerEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleURIListenerEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case ADD_URI_CONTENT_LISTENER:
			{
				rVal->rv=window->AddURIContentListenerInternal();
				JREX_LOGLN("HandleURIListenerEvent()--> **** AddURIContentListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case REMOVE_URI_CONTENT_LISTENER:
			{
				rVal->rv=window->RemoveURIContentListenerInternal();
				JREX_LOGLN("HandleURIListenerEvent()--> **** RemoveURIContentListenerInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandleURIListenerEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleURIListenerEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexWindow::DestroyURIListenerEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyURIListenerEvent()--> **** event <"<<event<<"> ****")
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
