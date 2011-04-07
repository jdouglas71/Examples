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
 	#include "JRex_JNI_ProgressEvent.h"
 	using namespace JRex_JNI_ProgressEvent;


	/* void onStateChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long aStateFlags, in nsresult aStatus); */
	NS_IMETHODIMP JRexWindow::OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus)
	{
		JREX_LOGLN("OnStateChange()--> aStateFlags<"<<aStateFlags<<"> mProgListenerAdded <"<<mProgListenerAdded<<">")
		if((aStateFlags & STATE_IS_NETWORK) &&
                        (mChromeFlag & nsIWebBrowserChrome::CHROME_OPENAS_CHROME)){
               	JREX_LOGLN("OnStateChange()--> Doing SizeToContent ")
		        nsCOMPtr<nsIDOMWindow> contentWin;
    	        nsresult rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));
            	if (contentWin)
    		        rv= contentWin->SizeToContent();
				JREX_LOGLN("OnStateChange()--> SizeToContent rv<"<<rv<<">")
		}
		if(!mProgListenerAdded)return NS_OK;

		nsresult rv=NS_OK;
		StateChangeProgressEventParam *sParm=new StateChangeProgressEventParam;
		if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;
		sParm->target=NS_PTR_TO_INT32(this);
		sParm->progEventType=PROG_STATE_CHANGE;
		SetCommonParam(sParm,aWebProgress,aRequest);
		sParm->stateFlags=aStateFlags;
		sParm->status=aStatus;
		sParm->request=aRequest;
		rv=fireEvent(sParm,PR_FALSE,nsnull);
		JREX_LOGLN("OnStateChange()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* void onProgressChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in long aCurSelfProgress, in long aMaxSelfProgress, in long aCurTotalProgress, in long aMaxTotalProgress); */
	NS_IMETHODIMP JRexWindow::OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress)
	{
		JREX_LOGLN("OnProgressChange()--> aCurSelfProgress<"<<aCurSelfProgress
								<<"> aMaxSelfProgress<"<<aMaxSelfProgress
								<<"> aCurTotalProgress<"<<aCurTotalProgress
								<<"> aMaxTotalProgress<"<<aMaxTotalProgress
								<<"> mProgListenerAdded <"<<mProgListenerAdded<<">")
		if(!mProgListenerAdded)return NS_OK;
		nsresult rv=NS_OK;
		ProgressChangeProgressEventParam *sParm=new ProgressChangeProgressEventParam;
		if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;

		sParm->target=NS_PTR_TO_INT32(this);
		sParm->progEventType=PROG_PROGRESS_CHANGE;
		SetCommonParam(sParm,aWebProgress,aRequest);
		sParm->curSelfProgress=aCurSelfProgress;
		sParm->maxSelfProgress=aMaxSelfProgress;
		sParm->curTotalProgress=aCurTotalProgress;
		sParm->maxTotalProgress=aMaxTotalProgress;
		rv=fireEvent(sParm,PR_FALSE,nsnull);
		JREX_LOGLN("OnProgressChange()--> *** fireEvent rv<"<<rv<<"> ***")

		return NS_OK;
	}

	/* void onLocationChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsIURI location); */
	NS_IMETHODIMP JRexWindow::OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location)
	{
		JREX_LOGLN("OnLocationChange()--> *** location <"<<location<<"> mProgListenerAdded <"<<mProgListenerAdded<<"> ***")
		if(!mProgListenerAdded)return NS_OK;
		if (NOT_NULL(aWebProgress)) {
			nsCOMPtr<nsIDOMWindow>  domWindow;
			nsCOMPtr<nsIDOMWindow>  topDomWindow;

			aWebProgress->GetDOMWindow(getter_AddRefs(domWindow));
			if (NOT_NULL(domWindow)){
				domWindow->GetTop(getter_AddRefs(topDomWindow));
				if (domWindow != topDomWindow){
					nsresult rv=NS_OK;
					LocationChangeProgressEventParam *sParm=new LocationChangeProgressEventParam;
					if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;

					sParm->target=NS_PTR_TO_INT32(this);
					sParm->progEventType=PROG_LOC_CHANGE;
					SetCommonParam(sParm,aWebProgress,aRequest);
					if(NOT_NULL(location)){
						JREX_LOGLN("OnLocationChange()--> *** NOT_NULL location ***")
						nsEmbedCString spec;
						rv=location->GetSpec(spec);
						if(NS_SUCCEEDED(rv))
							sParm->loc =ToNewCString(spec);
						else
							sParm->loc=nsnull;
					}else{
						JREX_LOGLN("OnLocationChange()--> *** NULL location ***")
						sParm->loc=nsnull;
					}
					rv=fireEvent(sParm,PR_FALSE,nsnull);
					JREX_LOGLN("OnLocationChange()--> *** fireEvent rv<"<<rv<<"> ***")
				}

			}
		}
		return NS_OK;
	}

	/* void onStatusChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsresult aStatus, in wstring aMessage); */
	NS_IMETHODIMP JRexWindow::OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage)
	{
		JREX_LOGLN("OnStatusChange()--> *** aStatus <"<<aStatus<<"> mProgListenerAdded <"<<mProgListenerAdded<<"> ***")
		if(!mProgListenerAdded)return NS_OK;
		nsresult rv=NS_OK;
		StatusChangeProgressEventParam *sParm=new StatusChangeProgressEventParam;
		if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;

		sParm->target=NS_PTR_TO_INT32(this);
		sParm->progEventType=PROG_STATUS_CHANGE;
		SetCommonParam(sParm,aWebProgress,aRequest);
		sParm->status=aStatus;
		if(NOT_NULL(aMessage)){
			nsEmbedString statusStr(aMessage);
			char* temp=ToNewUTF8String(statusStr);
			JREX_LOGLN("OnStatusChange()--> ***  status<"<<aStatus<<"> statusMessage<"<<temp<<"> ***")
			sParm->statusMessage=temp;
		}else
			sParm->statusMessage=nsnull;

		rv=fireEvent(sParm,PR_FALSE,nsnull);
		JREX_LOGLN("OnStatusChange()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* void onSecurityChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long state); */
	NS_IMETHODIMP JRexWindow::OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state)
	{
		JREX_LOGLN("OnSecurityChange()--> *** state <"<<state<<"> mProgListenerAdded <"<<mProgListenerAdded<<"> ***")
		if(!mProgListenerAdded)return NS_OK;
		nsresult rv=NS_OK;
		StateChangeProgressEventParam *sParm=new StateChangeProgressEventParam;
		if(IS_NULL(sParm))return NS_ERROR_OUT_OF_MEMORY;

		sParm->target=NS_PTR_TO_INT32(this);
		sParm->progEventType=PROG_SECURITY_CHANGE;
		SetCommonParam(sParm,aWebProgress,aRequest);
		sParm->stateFlags=state;
		sParm->status=rv;
		rv=fireEvent(sParm,PR_FALSE,nsnull);
		JREX_LOGLN("OnSecurityChange()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

