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

	nsresult JRexWindow::PrintInternal(PRBool prompt, PRBool showProgress){
		JREX_LOGLN("PrintInternal()--> **** prompt<"<<prompt<<"> showProgress<"<<showProgress<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"PrintInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		nsCOMPtr<nsIPrintSettings> printSettings;
		rv = browserAsPrint->GetGlobalPrintSettings(getter_AddRefs(printSettings));
		JREX_RETURN_IF_FAILED(rv,"PrintInternal()--> **** GetGlobalPrintSettings nsIPrintSettings")
		printSettings->SetPrintSilent(!prompt);
		printSettings->SetShowPrintProgress(showProgress);
		rv = browserAsPrint->Print(printSettings, nsnull);
		JREX_LOGLN("PrintInternal()--> **** Print rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::Print(PRBool prompt, PRBool showProgress){
		JREX_LOGLN("Print()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		if(IS_EQT)
			return PrintInternal(prompt, showProgress);

		PRBool *temp=new PRBool[2];
		temp[0]=prompt;
		temp[1]=showProgress;
		rv=ExecInEventQ(this, JREX_PRINT,temp, PR_FALSE, HandlePrintEvent,DestroyPrintEvent,nsnull);
		if (NS_FAILED(rv) && temp)
			delete temp;
		JREX_LOGLN("Print()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CancelPrintInternal(){
		if(mBrowCreated==PR_FALSE)return NS_OK;
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"CancelPrintInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		PRBool printing=PR_FALSE;
		browserAsPrint->GetDoingPrint(&printing);
		if(printing==PR_TRUE){
			rv = browserAsPrint->Cancel();
			JREX_LOGLN("CancelPrintInternal()--> **** Cancel rv<"<<rv<<"> ****")
		}
		return rv;
	}


	nsresult JRexWindow::CancelPrint(){
		JREX_LOGLN("CancelPrint()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		if(IS_EQT)
			return CancelPrintInternal();
		rv=ExecInEventQ(this, JREX_CANCEL_PRINT,nsnull, PR_FALSE, HandlePrintEvent,DestroyPrintEvent,nsnull);
		JREX_LOGLN("CancelPrint()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::PrintPreviewInternal(PRBool shrinkToFit, PRBool isLandScape){
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> print(do_GetInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"PrintPreviewInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		nsCOMPtr<nsIPrintSettings> printSettings;
		rv = print->GetGlobalPrintSettings(getter_AddRefs(printSettings));
		JREX_RETURN_IF_FAILED(rv,"PrintPreviewInternal()--> **** GetGlobalPrintSettings nsIPrintSettings")
		rv=printSettings->SetShrinkToFit(shrinkToFit);
		JREX_LOGLN("PrintPreviewInternal()--> **** SetShrinkToFit rv<"<<rv<<"> ****")
		PRInt32 land=nsIPrintSettings::kLandscapeOrientation;
		PRInt32 port=nsIPrintSettings::kPortraitOrientation;
		rv=printSettings->SetOrientation(isLandScape?land:port);
		JREX_LOGLN("PrintPreviewInternal()--> **** SetOrientation rv<"<<rv<<"> ****")
		print->PrintPreview(printSettings, nsnull, nsnull);
		JREX_LOGLN("PrintPreviewInternal()--> **** PrintPreview rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::PrintPreview(PRBool shrinkToFit, PRBool isLandScape){
		JREX_LOGLN("PrintPreview()--> **** mBrowCreated<"<<mBrowCreated<<"> shrinkToFit<"<<shrinkToFit<<"> isLandScape<"<<isLandScape<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		if(IS_EQT)
			return PrintPreviewInternal(shrinkToFit,isLandScape);
		PRBool *temp=new PRBool[2];
		temp[0]=shrinkToFit;
		temp[1]=isLandScape;
		rv=ExecInEventQ(this, JREX_PRINT_PREVIEW,temp, PR_FALSE, HandlePrintEvent,DestroyPrintEvent,nsnull);
		if (NS_FAILED(rv) && temp)
			delete temp;
		JREX_LOGLN("PrintPreview()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::CancelPrintPreviewInternal(){
		if(mBrowCreated==PR_FALSE)return NS_OK;
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"CancelPrintPreviewInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		PRBool printPreviewing=PR_FALSE;
		rv=browserAsPrint->GetDoingPrintPreview(&printPreviewing);
		JREX_LOGLN("CancelPrintPreviewInternal()--> **** GetDoingPrintPreview rv<"<<rv<<"> printPreviewing<"<<printPreviewing<<"> ****")
		if(printPreviewing==PR_TRUE){
			try{
				rv = browserAsPrint->ExitPrintPreview();
				JREX_LOGLN("CancelPrintPreviewInternal()--> **** ExitPrintPreview rv<"<<rv<<"> ****")
			}catch(...){
				JREX_LOGLN("CancelPrintPreviewInternal()--> **** UGLY F**KN BUG ****")
			}
		}
		return rv;
	}

	nsresult JRexWindow::CancelPrintPreview(){
		JREX_LOGLN("CancelPrintPreview()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		if(IS_EQT)
			return CancelPrintPreviewInternal();
		rv=ExecInEventQ(this, JREX_CANCEL_PREVIEW,nsnull, PR_FALSE, HandlePrintEvent,DestroyPrintEvent,nsnull);
		JREX_LOGLN("CancelPrintPreview()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::GetPrintPreviewNumPagesInternal(PRInt32 *aPrintPreviewNumPages){
		NS_ENSURE_ARG_POINTER(aPrintPreviewNumPages);
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"GetPrintPreviewNumPagesInternal()--> **** do_GetInterface nsIWebBrowserPrint")
		rv=browserAsPrint->GetPrintPreviewNumPages(aPrintPreviewNumPages);
		JREX_LOGLN("GetPrintPreviewNumPagesInternal()--> **** GetPrintPreviewNumPages rv<"<<rv<<"> aPrintPreviewNumPages<"<<*aPrintPreviewNumPages<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetPrintPreviewNumPages(PRInt32 *aPrintPreviewNumPages){
		NS_ENSURE_ARG_POINTER(aPrintPreviewNumPages);
		JREX_LOGLN("GetPrintPreviewNumPages()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		nsresult rv;
		if(IS_EQT)
			return GetPrintPreviewNumPagesInternal(aPrintPreviewNumPages);
		PRInt32 printPreviewNumPages=0;
		rv=ExecInEventQ(this, JREX_PREVIEW_PAGES,nsnull, PR_TRUE, HandlePrintEvent,DestroyPrintEvent, (void**)&printPreviewNumPages);
		JREX_LOGLN("GetPrintPreviewNumPages()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*aPrintPreviewNumPages=printPreviewNumPages;
		JREX_LOGLN("GetPrintPreviewNumPages()--> **** pages <"<<printPreviewNumPages<<"> ****")
		return rv;
	}

	nsresult JRexWindow::PrintPreviewNavigateInternal(PRInt16 aNavType, PRInt32 aPageNum){
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"PrintPreviewNavigateInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		PRBool printPreviewing=PR_FALSE;
		rv=browserAsPrint->GetDoingPrintPreview(&printPreviewing);
		JREX_LOGLN("PrintPreviewNavigateInternal()--> **** GetDoingPrintPreview rv<"<<rv<<"> printPreviewing<"<<printPreviewing<<"> ****")
		if(printPreviewing==PR_TRUE){
			rv = browserAsPrint->PrintPreviewNavigate(aNavType, aPageNum);
			JREX_LOGLN("PrintPreviewNavigateInternal()--> **** PrintPreviewNavigate rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::PrintPreviewNavigate(PRInt16 aNavType, PRInt32 aPageNum){
		JREX_LOGLN("PrintPreviewNavigate()--> **** mBrowCreated<"<<mBrowCreated<<"> aNavType<"<<aNavType<<"> aPageNum<"<<aPageNum<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return PrintPreviewNavigateInternal(aNavType, aPageNum);
		PRInt32 *temp=new PRInt32[2];
		temp[0]=aNavType;
		temp[1]=aPageNum;
		nsresult rv=ExecInEventQ(this, JREX_NAV_PREVIEW,temp, PR_FALSE, HandlePrintEvent,DestroyPrintEvent,nsnull);
		if (NS_FAILED(rv) && temp)
			delete temp;
		JREX_LOGLN("PrintPreviewNavigate()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::PageSetupInternal(){
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"PageSetupInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		nsCOMPtr<nsIDOMWindow> domWindow;
		rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
		JREX_RETURN_IF_FAILED(rv,"PageSetupInternal()--> **** GetContentDOMWindow")

		nsCOMPtr<nsIPrintSettings> printSettings;
		rv = browserAsPrint->GetGlobalPrintSettings(getter_AddRefs(printSettings));
		JREX_RETURN_IF_FAILED(rv,"PageSetupInternal()--> **** GetGlobalPrintSettings")

		nsCOMPtr<nsIPrintingPromptService> printingPromptService =do_GetService("@mozilla.org/embedcomp/printingprompt-service;1",&rv);
		JREX_RETURN_IF_FAILED(rv,"PageSetupInternal()--> **** do_GetService nsIPrintingPromptService")
		rv=printingPromptService->ShowPageSetup(domWindow, printSettings, nsnull);
		JREX_LOGLN("PageSetupInternal()--> **** ShowPageSetup rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::PageSetup(){
		JREX_LOGLN("PageSetup()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv;
		if(IS_EQT)
			return PageSetupInternal();
		rv=ExecInEventQ(this, JREX_PAGE_SETUP,nsnull, PR_FALSE, HandlePrintEvent,DestroyPrintEvent, nsnull);
		JREX_LOGLN("PageSetup()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::IsPrintingInternal(PRBool *isPrinting){
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"IsPrintingInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		PRBool printing=PR_FALSE;
		browserAsPrint->GetDoingPrint(&printing);
		*isPrinting=printing;
		JREX_LOGLN("IsPrintingInternal()--> **** printing <"<<printing<<"> ****")
		return rv;
	}

	nsresult JRexWindow::IsPrinting(PRBool *isPrinting){
		NS_ENSURE_ARG_POINTER(isPrinting);
		JREX_LOGLN("IsPrinting()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		nsresult rv;
		if(IS_EQT)
			return IsPrintingInternal(isPrinting);
		PRBool printing=PR_FALSE;
		rv=ExecInEventQ(this, JREX_DOING_PRINT,nsnull, PR_TRUE, HandlePrintEvent,DestroyPrintEvent, (void**)&printing);
		JREX_LOGLN("IsPrinting()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*isPrinting=printing;
		JREX_LOGLN("IsPrinting()--> **** printing <"<<printing<<"> ****")
		return rv;
	}

	nsresult JRexWindow::IsPrintPreviewingInternal(PRBool *isPrintPreviewing){
		nsresult rv;
		nsCOMPtr<nsIWebBrowserPrint> browserAsPrint=do_GetInterface(mWebBrowser,&rv);
		JREX_RETURN_IF_FAILED(rv,"IsPrintPreviewingInternal()--> **** do_GetInterface nsIWebBrowserPrint")

		PRBool printPreviewing=PR_FALSE;
		browserAsPrint->GetDoingPrintPreview(&printPreviewing);
		*isPrintPreviewing=printPreviewing;
		JREX_LOGLN("IsPrintPreviewingInternal()--> **** printPreviewing <"<<printPreviewing<<"> ****")
		return rv;
	}

	nsresult JRexWindow::IsPrintPreviewing(PRBool *isPrintPreviewing){
		NS_ENSURE_ARG_POINTER(isPrintPreviewing);
		JREX_LOGLN("IsPrintPreviewing()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		nsresult rv;
		if(IS_EQT)
			return IsPrintPreviewingInternal(isPrintPreviewing);
		PRBool printPreviewing=PR_FALSE;
		rv=ExecInEventQ(this, JREX_DOING_PREVIEW,nsnull, PR_TRUE, HandlePrintEvent, DestroyPrintEvent, (void**)&printPreviewing);
		JREX_LOGLN("IsPrintPreviewing()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*isPrintPreviewing=printPreviewing;
		JREX_LOGLN("IsPrintPreviewing()--> **** printPreviewing <"<<printPreviewing<<"> ****")
		return rv;
	}

	void* PR_CALLBACK JRexWindow::HandlePrintEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandlePrintEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case JREX_PRINT:
			{
				PRBool *temp=(PRBool *)event->eventData;
				JREX_LOGLN("HandlePrintEvent()--> **** PrintInternal prompt<"<<temp[0]<<"> showProgress<"<<temp[1]<<"> ****")
				rVal->rv=window->PrintInternal(temp[0], temp[1]);
				JREX_LOGLN("HandlePrintEvent()--> **** PrintInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case JREX_PRINT_PREVIEW:
			{
				PRBool *temp=(PRBool *)event->eventData;
				JREX_LOGLN("HandlePrintEvent()--> **** PrintPreviewInternal prompt<"<<temp[0]<<"> showProgress<"<<temp[1]<<"> ****")
				rVal->rv=window->PrintPreviewInternal(temp[0], temp[1]);
				JREX_LOGLN("HandlePrintEvent()--> **** PrintInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case JREX_PREVIEW_PAGES:
			{
				PRInt32 printPreviewNumPages=0;
				rVal->rv=window->GetPrintPreviewNumPagesInternal(&printPreviewNumPages);
				JREX_LOGLN("HandlePrintEvent()--> **** GetPrintPreviewNumPagesInternal rv<"<<rVal->rv<<"> printPreviewNumPages<"<<printPreviewNumPages<<"> ****")
				rVal->rData=(void*)printPreviewNumPages;
				break;
			}
			case JREX_DOING_PRINT:
			{
				PRBool isPrinting=PR_FALSE;
				rVal->rv=window->IsPrintingInternal(&isPrinting);
				JREX_LOGLN("HandlePrintEvent()--> **** IsPrintingInternal rv<"<<rVal->rv<<"> isPrinting<"<<isPrinting<<"> ****")
				rVal->rData=(void*)isPrinting;
				break;
			}
			case JREX_DOING_PREVIEW:
			{
				PRBool isPreviewing=PR_FALSE;
				rVal->rv=window->IsPrintPreviewingInternal(&isPreviewing);
				JREX_LOGLN("HandlePrintEvent()--> **** IsPrintPreviewingInternal rv<"<<rVal->rv<<"> isPreviewing<"<<isPreviewing<<"> ****")
				rVal->rData=(void*)isPreviewing;
				break;
			}
			case JREX_CANCEL_PRINT:
			{
				rVal->rv=window->CancelPrintInternal();
				JREX_LOGLN("HandlePrintEvent()--> **** CancelPrintInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case JREX_CANCEL_PREVIEW:
			{
				rVal->rv=window->CancelPrintPreviewInternal();
				JREX_LOGLN("HandlePrintEvent()--> **** CancelPrintPreviewInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case JREX_NAV_PREVIEW:
			{
				PRInt32 *temp=(PRInt32 *)event->eventData;
				JREX_LOGLN("HandlePrintEvent()--> **** PrintPreviewNavigate NavType<"<<temp[0]<<"> pageNum<"<<temp[1]<<"> ****")
				rVal->rv=window->PrintPreviewNavigateInternal(temp[0], temp[1]);
				JREX_LOGLN("HandlePrintEvent()--> **** PrintPreviewNavigateInternal rv<"<<rVal->rv<<"> ****")
				break;

			}
			case JREX_PAGE_SETUP:
			{
				rVal->rv=window->PageSetupInternal();
				JREX_LOGLN("HandlePrintEvent()--> **** PageSetupInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandlePrintEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandlePrintEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexWindow::DestroyPrintEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyPrintEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData){
			if(event->eventType==JREX_PRINT || event->eventType==JREX_PRINT_PREVIEW){
				PRBool *temp=(PRBool *)event->eventData;
				delete temp;
			}else
			if(event->eventType==JREX_NAV_PREVIEW){
				PRInt32 *temp=(PRInt32 *)event->eventData;
				delete temp;
			}
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
