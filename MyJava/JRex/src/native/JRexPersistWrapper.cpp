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

	static NS_DEFINE_CID(kIOServiceCID, NS_IOSERVICE_CID);

	nsresult JRexWindow::GetPersistFlagsInternal(PRUint32 *aPersistFlags){
		JREX_LOGLN("GetPersistFlagsInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetPersistFlagsInternal()--> **** do_GetInterface nsIWebBrowserPersist")
		rv=browserAsPersist->GetPersistFlags(aPersistFlags);
		JREX_LOGLN("GetPersistFlagsInternal()--> **** GetPersistFlags rv<"<<rv<<"> aPersistFlags<"<<*aPersistFlags<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetPersistFlags(PRUint32 *aPersistFlags){
		JREX_LOGLN("GetPersistFlags()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GetPersistFlagsInternal(aPersistFlags);

		PRInt32 persistFlags=0;
		nsresult rv=ExecInEventQ(this, GET_PERSIST_FLAGS, nsnull, PR_TRUE, HandlePersistEvent,DestroyPersistEvent, (void**)&persistFlags);
		JREX_LOGLN("GetPersistFlags()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*aPersistFlags=persistFlags;
		JREX_LOGLN("GetPersistFlags()--> **** persistFlags <"<<persistFlags<<"> ****")
		return rv;
	}


	nsresult JRexWindow::SetPersistFlagsInternal(PRUint32 aPersistFlags){
		JREX_LOGLN("SetPersistFlagsInternal()--> **** aPersistFlags<"<<aPersistFlags<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"SetPersistFlagsInternal()--> **** do_GetInterface nsIWebBrowserPersist")
		rv=browserAsPersist->SetPersistFlags(aPersistFlags);
		JREX_LOGLN("SetPersistFlagsInternal()--> **** SetPersistFlags rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SetPersistFlags(PRUint32 persistFlags){
		JREX_LOGLN("SetPersistFlags()--> **** mBrowCreated<"<<mBrowCreated<<"> persistFlags <"<<persistFlags<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return SetPersistFlagsInternal(persistFlags);
		nsresult rv=ExecInEventQ(this, SET_PERSIST_FLAGS, (void*)persistFlags, PR_FALSE, HandlePersistEvent,DestroyPersistEvent, nsnull);
		JREX_LOGLN("SetPersistFlags()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}


	nsresult JRexWindow::GetCurrentStateInternal(PRUint32 *aCurrentState){
		JREX_LOGLN("GetCurrentStateInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetCurrentStateInternal()--> **** do_GetInterface nsIWebBrowserPersist")
		rv=browserAsPersist->GetCurrentState(aCurrentState);
		JREX_LOGLN("GetCurrentStateInternal()--> **** GetCurrentState rv<"<<rv<<"> aCurrentState<"<<*aCurrentState<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetCurrentState(PRUint32 *aCurrentState){
		JREX_LOGLN("GetCurrentState()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GetCurrentStateInternal(aCurrentState);

		PRInt32 currentState=0;
		nsresult rv=ExecInEventQ(this, GET_CURRENT_STATE, nsnull, PR_TRUE, HandlePersistEvent,DestroyPersistEvent, (void**)&currentState);
		JREX_LOGLN("GetCurrentState()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*aCurrentState=currentState;
		JREX_LOGLN("GetCurrentState()--> **** currentState <"<<currentState<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetResultInternal(PRUint32 *aResult){
		JREX_LOGLN("GetResultInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetResultInternal()--> **** do_GetInterface nsIWebBrowserPersist")
		rv=browserAsPersist->GetResult(aResult);
		JREX_LOGLN("GetResultInternal()--> **** GetResult rv<"<<rv<<"> aResult<"<<*aResult<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetResult(PRUint32 *aResult){
		JREX_LOGLN("GetResult()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GetResultInternal(aResult);

		PRInt32 result=0;
		nsresult rv=ExecInEventQ(this, GET_RESULT, nsnull, PR_TRUE, HandlePersistEvent,DestroyPersistEvent, (void**)&result);
		JREX_LOGLN("GetResult()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*aResult=result;
		JREX_LOGLN("GetResult()--> **** result <"<<result<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SaveURIInternal(PRUnichar* uri, PRUnichar* referrer,
							nsIInputStream *postData, PRUnichar* aExtraHeaders,
										PRUnichar* saveFile, PRBool addProgListn){
		JREX_LOGLN("SaveURIInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv=NS_OK;
		nsCOMPtr<nsIIOService> service(do_GetService(kIOServiceCID,&rv));
		JREX_RETURN_IF_FAILED(rv,"SaveURIInternal()--> **** nsIIOService do_GetService")

		nsEmbedString specu(uri);
		nsEmbedCString speca;
		CopyUCS2toASCII(specu, speca);

		nsCOMPtr<nsIURI> tempUri=nsnull;
		rv=service->NewURI(speca, nsnull, nsnull, getter_AddRefs(tempUri));
		JREX_RETURN_IF_FAILED(rv,"SaveURIInternal()--> **** uri NewURI")

		nsCOMPtr<nsIURI> tempRefUri=nsnull;
		if(NOT_NULL(referrer)){
			nsEmbedString refSpecu(referrer);
			nsEmbedCString refSpeca;
			CopyUCS2toASCII(refSpecu, refSpeca);

			rv=service->NewURI(refSpeca, nsnull, nsnull, getter_AddRefs(tempRefUri));
			JREX_RETURN_IF_FAILED(rv,"SaveURIInternal()--> **** referrer NewURI")
		}

		nsEmbedString tempSaveFileu(saveFile);
		nsEmbedCString tempSaveFilea;
		NS_CopyUnicodeToNative(tempSaveFileu,tempSaveFilea);

		nsCOMPtr<nsILocalFile> filePath;
		rv=NS_NewNativeLocalFile(tempSaveFilea,PR_TRUE,getter_AddRefs(filePath));
		JREX_RETURN_IF_FAILED(rv,"SaveURIInternal()--> **** NS_NewNativeLocalFile")

		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"SaveURIInternal()--> **** do_GetInterface nsIWebBrowserPersist")

		if(addProgListn){
			nsCOMPtr<nsIWebProgressListener> tempProgListener;
			rv=browserAsPersist->GetProgressListener(getter_AddRefs(tempProgListener));
			JREX_LOGLN("SaveURIInternal()--> **** GetProgressListener rv<"<<rv<<"> ****")
			if(!mPersistProgListenerAdded){
				nsCOMPtr<nsIWebProgressListener> progListener=NS_REINTERPRET_CAST(nsIWebProgressListener*, this);
				rv=browserAsPersist->SetProgressListener(progListener);
				JREX_LOGLN("SaveURIInternal()--> **** SetProgressListener rv<"<<rv<<"> ****")
				mPersistProgListenerAdded=NS_SUCCEEDED(rv);
			}
		}
		nsEmbedString xtraHeaderu(aExtraHeaders);
		nsEmbedCString xtraHeadera;
		CopyUCS2toASCII(xtraHeaderu, xtraHeadera);

		rv=browserAsPersist->SaveURI(tempUri, nsnull , tempRefUri, postData, xtraHeadera.get(), filePath);
		JREX_LOGLN("SaveURIInternal()--> **** SaveURI rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SaveURI(PRUnichar* uri,PRUnichar* referrer,
									nsIInputStream *postData, PRUnichar* xtraHeaders,
												PRUnichar* saveFile, PRBool addProgListn){
		JREX_LOGLN("SaveURI()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		if(IS_EQT)
			return SaveURIInternal(uri, referrer, postData, xtraHeaders, saveFile, addProgListn);

		nsresult rv=NS_OK;
	   	SaveURIEventData* eventData = new SaveURIEventData;
		if (eventData) {
			JREX_LOGLN("SaveURI()--> **** eventData Created ****")
			eventData->uri=uri;
			eventData->referrer=NOT_NULL(referrer)?referrer:nsnull;
			eventData->postData=postData;
			eventData->headers=NOT_NULL(xtraHeaders)?xtraHeaders:nsnull;
			eventData->saveFile=saveFile;
			eventData->addProgListn=addProgListn;

			rv=ExecInEventQ(this, SAVE_URI, eventData, PR_FALSE, HandlePersistEvent,DestroyPersistEvent, nsnull);
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->uri);
				CRTFREEIF(eventData->referrer);
				CRTFREEIF(eventData->headers);
				CRTFREEIF(eventData->saveFile);
				delete eventData;
			}
			JREX_LOGLN("SaveURI()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;

		return rv;
	}

	nsresult JRexWindow::SaveDocumentInternal(PRUnichar* saveFile, PRUnichar* dataFile,
									PRUnichar* outputContentType, PRUint32 encodingFlags,
										PRUint32 wrapColumn, PRBool addProgListn){
		JREX_LOGLN("SaveDocumentInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsCOMPtr<nsIDOMDocument> doc;
		nsresult rv=mWebNavigation->GetDocument(getter_AddRefs(doc));
		JREX_RETURN_IF_FAILED(rv,"SaveDocumentInternal()--> **** GetDocument")

		nsEmbedString tempSaveFileu(saveFile);
		nsEmbedCString tempSaveFilea;
		NS_CopyUnicodeToNative(tempSaveFileu,tempSaveFilea);

		nsCOMPtr<nsILocalFile> filePath;
		rv=NS_NewNativeLocalFile(tempSaveFilea,PR_TRUE,getter_AddRefs(filePath));
		JREX_RETURN_IF_FAILED(rv,"SaveDocumentInternal()--> **** filePath NS_NewNativeLocalFile")

		nsCOMPtr<nsILocalFile> dataPath;
		if(NOT_NULL(dataFile)){
			nsEmbedString tempDataFileu(dataFile);
			nsEmbedCString tempDataFilea;
			NS_CopyUnicodeToNative(tempDataFileu,tempDataFilea);

			rv=NS_NewNativeLocalFile(tempDataFilea,PR_TRUE,getter_AddRefs(dataPath));
			JREX_RETURN_IF_FAILED(rv,"SaveDocumentInternal()--> **** dataPath NS_NewNativeLocalFile")
		}

		nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"SaveDocumentInternal()--> **** do_GetInterface nsIWebBrowserPersist")

		if(addProgListn){
			nsCOMPtr<nsIWebProgressListener> tempProgListener;
			rv=browserAsPersist->GetProgressListener(getter_AddRefs(tempProgListener));
			JREX_LOGLN("SaveDocumentInternal()--> **** GetProgressListener rv<"<<rv<<"> ****")
			if(this!=tempProgListener){
				nsCOMPtr<nsIWebProgressListener> progListener=NS_REINTERPRET_CAST(nsIWebProgressListener*, this);
				browserAsPersist->SetProgressListener(progListener);
				JREX_LOGLN("SaveDocumentInternal()--> **** SetProgressListener rv<"<<rv<<"> ****")
			}
		}
		nsEmbedString tempCntTypu(outputContentType);
		nsEmbedCString tempCntTypa;
		CopyUCS2toASCII(tempCntTypu, tempCntTypa);

		rv=browserAsPersist->SaveDocument(doc, filePath, dataPath ,tempCntTypa.get(), encodingFlags, wrapColumn);
		JREX_LOGLN("SaveDocumentInternal()--> **** SaveDocument rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::SaveDocument(PRUnichar* saveFile, PRUnichar* dataFile,
							PRUnichar* outputContentType, PRUint32 encodingFlags,
											PRUint32 wrapColumn, PRBool addProgListn){
		JREX_LOGLN("SaveDocument()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		if(IS_EQT)
			return SaveDocumentInternal(saveFile, dataFile, outputContentType, encodingFlags, wrapColumn, addProgListn);

		nsresult rv=NS_OK;
	   	SaveDocumentEventData* eventData = new SaveDocumentEventData;
		if (eventData) {
			JREX_LOGLN("SaveDocument()--> **** eventData Created ****")
			eventData->saveFile=saveFile;
			eventData->dataFile=NOT_NULL(dataFile)?dataFile:nsnull;
			eventData->outputContentType=NOT_NULL(outputContentType)?outputContentType:nsnull;
			eventData->encodingFlags=encodingFlags;
			eventData->wrapColumn=wrapColumn;
			eventData->addProgListn=addProgListn;

			rv=ExecInEventQ(this, SAVE_DOCUMENT, eventData, PR_FALSE, HandlePersistEvent,DestroyPersistEvent, nsnull);
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->saveFile);
				CRTFREEIF(eventData->dataFile);
				CRTFREEIF(eventData->outputContentType);
				delete eventData;
			}
			JREX_LOGLN("SaveDocument()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;

		return rv;
	}

	nsresult JRexWindow::CancelSaveInternal(){
		JREX_LOGLN(" CancelSaveInternal()--> **** I AM HERE ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		PRUint32 currentState=0;
		nsresult rv=GetCurrentStateInternal(&currentState);
		JREX_LOGLN("CancelSaveInternal()--> **** GetCurrentStateInternal rv<"<<rv<<">  currentState<"<<currentState<<">****")
		if(NS_SUCCEEDED(rv) && (currentState==nsIWebBrowserPersist::PERSIST_STATE_SAVING)){
			nsCOMPtr<nsIWebBrowserPersist> browserAsPersist(do_QueryInterface(mWebBrowser,&rv));
			JREX_RETURN_IF_FAILED(rv,"CancelSaveInternal()--> **** do_GetInterface nsIWebBrowserPersist")
			rv=browserAsPersist->CancelSave();
			JREX_LOGLN("CancelSaveInternal()--> **** CancelSave rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::CancelSave(){
		JREX_LOGLN("CancelSave()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		if(IS_EQT)
			return CancelSave();
		nsresult rv=ExecInEventQ(this, CANCEL_SAVE, nsnull, PR_FALSE, HandlePersistEvent,DestroyPersistEvent, nsnull);
		JREX_LOGLN("CancelSave()--> **** ExecPrintEvent rv<"<<rv<<"> ****")
		return rv;
	}

	void* PR_CALLBACK JRexWindow::HandlePersistEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandlePersistEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case GET_PERSIST_FLAGS:
			{
				PRUint32 persistFlags=0;
				rVal->rv=window->GetPersistFlagsInternal(&persistFlags);
				JREX_LOGLN("HandlePersistEvent()--> **** GetPersistFlagsInternal rv<"<<rVal->rv<<"> persistFlags<"<<persistFlags<<"> ****")
				rVal->rData=(void*)persistFlags;
				break;
			}
			case SET_PERSIST_FLAGS:
			{
				PRUint32 persistFlags=(PRUint32)event->eventData;
				JREX_LOGLN("HandlePersistEvent()--> ****  persistFlags<"<<persistFlags<<"> ****")
				rVal->rv=window->SetPersistFlagsInternal(persistFlags);
				JREX_LOGLN("HandlePersistEvent()--> **** SetPersistFlagsInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GET_CURRENT_STATE:
			{
				PRUint32 currentState=0;
				rVal->rv=window->GetCurrentStateInternal(&currentState);
				JREX_LOGLN("HandlePersistEvent()--> **** GetCurrentStateInternal rv<"<<rVal->rv<<"> currentState<"<<currentState<<"> ****")
				rVal->rData=(void*)currentState;
				break;
			}
			case GET_RESULT:
			{
				PRUint32 result=0;
				rVal->rv=window->GetResultInternal(&result);
				JREX_LOGLN("HandlePersistEvent()--> **** GetResultInternal rv<"<<rVal->rv<<"> result<"<<result<<"> ****")
				rVal->rData=(void*)result;
				break;
			}
			case SAVE_URI:
			{
				SaveURIEventData* evtData = NS_REINTERPRET_CAST(SaveURIEventData*, event->eventData);
				JREX_LOGLN("HandlePersistEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=window->SaveURIInternal(evtData->uri, evtData->referrer,
									evtData->postData, evtData->headers,evtData->saveFile, evtData->addProgListn);
				JREX_LOGLN("HandlePersistEvent()--> **** SaveURIInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case SAVE_DOCUMENT:
			{
				SaveDocumentEventData* evtData = NS_REINTERPRET_CAST(SaveDocumentEventData*, event->eventData);
				JREX_LOGLN("HandlePersistEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv=window->SaveDocumentInternal(evtData->saveFile, evtData->dataFile,
													evtData->outputContentType, evtData->encodingFlags,
														evtData->wrapColumn, evtData->addProgListn);
				JREX_LOGLN("HandlePersistEvent()--> **** SaveDocumentInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case CANCEL_SAVE:
			{
				rVal->rv=window->CancelSaveInternal();
				JREX_LOGLN("HandlePersistEvent()--> **** CancelSaveInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandlePersistEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandlePersistEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexWindow::DestroyPersistEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyPersistEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData){
			if(event->eventType==SAVE_URI){
				SaveURIEventData* evtData = NS_REINTERPRET_CAST(SaveURIEventData*, event->eventData);
				delete evtData;
			}else
			if(event->eventType==SAVE_DOCUMENT){
				SaveDocumentEventData* evtData = NS_REINTERPRET_CAST(SaveDocumentEventData*, event->eventData);
				delete evtData;
			}
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
