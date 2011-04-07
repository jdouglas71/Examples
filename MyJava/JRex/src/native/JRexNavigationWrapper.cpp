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

	NS_IMETHODIMP JRexWindow::GetCanGoBack(PRBool *aCanGoBack) {
		NS_ENSURE_ARG_POINTER(aCanGoBack);
		JREX_LOGLN("GetCanGoBack()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return mWebNavigation->GetCanGoBack(aCanGoBack);
		PRBool canBack=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_BACK,nsnull,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void**)&canBack);
		JREX_LOGLN("GetCanGoBack()--> **** canBack<"<<canBack<<"> ****")
		if (NS_SUCCEEDED(rv))
			*aCanGoBack=canBack;
		JREX_LOGLN("GetCanGoBack()--> **** aCanGoBack<"<<aCanGoBack<<"> ****")
		return rv;
	}


	NS_IMETHODIMP JRexWindow::GetCanGoForward(PRBool *aCanGoForward) {
		NS_ENSURE_ARG_POINTER(aCanGoForward);
		JREX_LOGLN("GetCanGoForward()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return mWebNavigation->GetCanGoForward(aCanGoForward);

		PRBool canForward=PR_FALSE;
		nsresult rv=ExecInEventQ(this,CAN_FORWARD,nsnull,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void**)&canForward);
		JREX_LOGLN("GetCanGoForward()--> **** canForward<"<<canForward<<"> ****")
		if (NS_SUCCEEDED(rv))
			*aCanGoForward=canForward;
		JREX_LOGLN("GetCanGoForward()--> **** aCanGoForward<"<<aCanGoForward<<"> ****")
		return rv;
	}


	NS_IMETHODIMP JRexWindow::GoBack(void) {
		JREX_LOGLN("GoBack()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT){
			PRBool canBack=PR_FALSE;
			mWebNavigation->GetCanGoBack(&canBack);
			if(canBack==PR_TRUE)
				mWebNavigation->GoBack();
			return NS_OK;
		}
		nsresult rv=ExecInEventQ(this,GO_BACK,nsnull,PR_FALSE, HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("GoBack()--> **** rv<"<<rv<<"> ****")
		return rv;
 	}


	NS_IMETHODIMP JRexWindow::GoForward(void) {
		JREX_LOGLN("GoForward()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT){
			PRBool canForward=PR_FALSE;
			mWebNavigation->GetCanGoForward(&canForward);
			if(canForward==PR_TRUE)
				mWebNavigation->GoForward();
			return NS_OK;
		}
		nsresult rv=ExecInEventQ(this,GO_FORWARD,nsnull,PR_FALSE, HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("GoForward()--> **** rv<"<<rv<<"> ****")
		return rv;
	}


	NS_IMETHODIMP JRexWindow::GotoIndex(PRInt32 index) {
		JREX_LOGLN("GotoIndex()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return mWebNavigation->GotoIndex(index);
		nsresult rv=ExecInEventQ(this,GO_TO_INDEX,(void*)index,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("GotoIndex()--> **** rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::LoadURIInternal(PRUnichar* uri, PRUint32 loadFlags, PRUnichar* referrer, nsIInputStream *postData, nsIInputStream *headers){
		nsIURI *refUri=nsnull;
		if(NOT_NULL(referrer)){
			nsCOMPtr<nsIURI> tempRefUri;
			JREX_LOGLN("LoadURIInternal()--> **** referrer NOT NULL ***")
			nsresult rv;
			nsCOMPtr<nsIIOService> service(do_GetService(kIOServiceCID,&rv));
			JREX_LOGLN("LoadURIInternal()--> **** do_GetService rv<"<<rv<<"> ***")
			if (service){
				nsEmbedString specu(referrer);
				nsEmbedCString speca;
				CopyUCS2toASCII(specu, speca);

				rv=service->NewURI(speca, nsnull, nsnull, getter_AddRefs(tempRefUri));
				JREX_LOGLN("LoadURIInternal()--> **** NewURI rv<"<<rv<<"> ***")
				if(NS_SUCCEEDED(rv))
					NS_ADDREF(refUri=tempRefUri.get());
				JREX_LOGLN("LoadURIInternal()--> **** refUri<"<<(PRUint32)refUri<<"> ***")
			}
		}
		return mWebNavigation->LoadURI(uri,loadFlags,refUri,postData,headers);
	}

  	NS_IMETHODIMP JRexWindow::LoadURI(PRUnichar* uri, PRUint32 loadFlags, PRUnichar* referrer, nsIInputStream *postData, nsIInputStream *headers) {
		JREX_LOGLN("LoadURI()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return LoadURIInternal(uri, loadFlags, referrer, postData, headers);

		nsresult rv=NS_OK;
	   	LoadURIEventData* eventData = new LoadURIEventData;
		if (eventData) {
			JREX_LOGLN("LoadURI()--> **** eventData Created ****")
			eventData->uri=uri;
			eventData->loadFlags=loadFlags;
			eventData->referrer=NOT_NULL(referrer)?referrer:nsnull;
			eventData->postData=postData;
			eventData->headers=headers;

			rv=ExecInEventQ(this,LOAD,eventData,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
			JREX_LOGLN("LoadURI()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->uri);
				CRTFREEIF(eventData->referrer);
				delete eventData;
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	nsresult JRexWindow::LoadStreamInternal(nsIInputStream *inStream, PRUnichar* uri, PRUnichar* contType, PRUnichar* charset,
					PRUint32 loadFlags, PRUnichar* referrer, nsISupports* owner, PRBool inhherit,
						PRUnichar* target, nsIInputStream *postStream, nsIInputStream *headerStream){

		nsCOMPtr<nsIDocShell> docShell;
		nsresult rv=GetDocShell(getter_AddRefs(docShell));
		JREX_RETURN_IF_FAILED(rv,"LoadStreamInternal()--> **** GetDocShell")
		if(docShell){
			nsCOMPtr<nsIDocShellLoadInfo> loadInfo;
			rv=docShell->CreateLoadInfo(getter_AddRefs(loadInfo));
			JREX_RETURN_IF_FAILED(rv,"LoadStreamInternal()--> **** CreateLoadInfo")

			if(NOT_NULL(referrer)){
				JREX_LOGLN("LoadStreamInternal()--> **** referrer NOT NULL ***")
				nsCOMPtr<nsIIOService> service(do_GetService(kIOServiceCID,&rv));
				JREX_LOGLN("LoadStreamInternal()--> **** do_GetService rv<"<<rv<<"> ***")
				if (service){
					nsCOMPtr<nsIURI> tempRefUri;
					nsEmbedString specu(referrer);
					nsEmbedCString speca;
					CopyUCS2toASCII(specu, speca);

					rv=service->NewURI(speca, nsnull, nsnull, getter_AddRefs(tempRefUri));
					JREX_LOGLN("LoadStreamInternal()--> **** NewURI rv<"<<rv<<"> ***")
					if(NS_SUCCEEDED(rv)){
						nsIURI *refUri=nsnull;
						NS_IF_ADDREF(refUri=tempRefUri.get());
						loadInfo->SetReferrer(refUri);
					}
				}
			}
			if(NOT_NULL(owner))
				loadInfo->SetOwner(owner);
			loadInfo->SetInheritOwner(inhherit);
			loadInfo->SetLoadType(loadFlags);
			//loadInfo->SetSHEntry(aSHEntry);
			if(NOT_NULL(target)){
				loadInfo->SetTarget(target);
			}
			if(NOT_NULL(postStream))
				loadInfo->SetPostDataStream(postStream);
			if(NOT_NULL(headerStream))
				loadInfo->SetHeadersStream(headerStream);

			nsIURI *myuri=nsnull;
			if(NOT_NULL(uri)){
				JREX_LOGLN("LoadStreamInternal()--> **** uri NOT NULL ***")
				nsCOMPtr<nsIIOService> service(do_GetService(kIOServiceCID,&rv));
				JREX_LOGLN("LoadStreamInternal()--> **** do_GetService rv<"<<rv<<"> ***")
				if (service){
					nsCOMPtr<nsIURI> tempUri;
					nsEmbedString specu(uri);
					nsEmbedCString speca;
					CopyUCS2toASCII(specu, speca);

					rv=service->NewURI(speca, nsnull, nsnull, getter_AddRefs(tempUri));
					JREX_LOGLN("LoadStreamInternal()--> **** NewURI rv<"<<rv<<"> ***")
					if(NS_SUCCEEDED(rv))
						NS_IF_ADDREF(myuri=tempUri.get());
				}
			}

			nsEmbedString myContTypeu(contType);
			nsEmbedCString myContTypea;
			CopyUCS2toASCII(myContTypeu, myContTypea);

			nsEmbedString myCharsetu(charset);
			nsEmbedCString myCharseta;
			CopyUCS2toASCII(myCharsetu, myCharseta);

			rv=docShell->LoadStream(inStream, myuri, myContTypea, myCharseta, loadInfo);
			JREX_LOGLN("LoadStreamInternal()--> **** LoadStream rv<"<<rv<<"> ****")
		}
		return rv;
	}

	nsresult JRexWindow::LoadStream(nsIInputStream *inStream, PRUnichar* uri, PRUnichar* contType, PRUnichar* charset,
					PRUint32 loadFlags, PRUnichar* referrer, nsISupports* owner,PRBool inhherit,
						PRUnichar* target, nsIInputStream *postStream, nsIInputStream *headerStream){
		JREX_LOGLN("LoadStream()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return LoadStreamInternal(inStream, uri, contType,charset,loadFlags, referrer, owner,
						inhherit, target, postStream, headerStream);

		nsresult rv=NS_OK;
	   	LoadStreamEventData* eventData = new LoadStreamEventData;
		if (eventData) {
			JREX_LOGLN("LoadStream()--> **** eventData Created ****")
			eventData->inStream=inStream;
			eventData->uri=NOT_NULL(uri)?uri:nsnull;
			eventData->contType=NOT_NULL(contType)?contType:nsnull;
			eventData->charset=NOT_NULL(charset)?charset:nsnull;
			eventData->loadFlags=loadFlags;
			eventData->referrer=NOT_NULL(referrer)?referrer:nsnull;
			eventData->owner=owner;
			eventData->inhherit=inhherit;
			eventData->target=NOT_NULL(target)?target:nsnull;
			eventData->postStream=postStream;
			eventData->headerStream=headerStream;

			rv=ExecInEventQ(this,LOAD_STREAM,eventData,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
			JREX_LOGLN("LoadStream()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->uri);
				CRTFREEIF(eventData->contType);
				CRTFREEIF(eventData->charset);
				CRTFREEIF(eventData->referrer);
				CRTFREEIF(eventData->target);
				delete eventData;
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;

	}



	NS_IMETHODIMP JRexWindow::OpenWindow(PRUint16 type, const char *uri, const char *referrer, const char *windowName, const char *feature){
		JREX_LOGLN("OpenWindow()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		nsresult rv=NS_OK;
		if(IS_EQT){
			nsCOMPtr<nsIDOMWindow> newWindow;
			return OpenWindowInternal(type, uri, referrer, windowName, feature, getter_AddRefs(newWindow));
		}
	   	OpenWindowEventData* eventData = new OpenWindowEventData;
		if (eventData) {
			JREX_LOGLN("OpenWindow()--> **** eventData Created ****")
			eventData->type=type;

			nsEmbedCString tempUri(uri);
			eventData->uri=ToNewCString(tempUri);

			if(NOT_NULL(referrer)){
				nsEmbedCString tempReferrer(referrer);
				eventData->referrer=ToNewCString(tempReferrer);
			}else
				eventData->referrer=nsnull;

			if(NOT_NULL(windowName)){
				nsEmbedCString tempWindowName(windowName);
				eventData->windowName=ToNewCString(tempWindowName);
			}else
				eventData->windowName=nsnull;

			if(NOT_NULL(feature)){
				nsEmbedCString tempFeature(feature);
				eventData->feature=ToNewCString(tempFeature);
			}else
				eventData->feature=nsnull;

			rv=ExecInEventQ(this,OPEN_WINDOW,eventData,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
			JREX_LOGLN("OpenWindow()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->uri);
				CRTFREEIF(eventData->referrer);
				CRTFREEIF(eventData->windowName);
				CRTFREEIF(eventData->feature);
				delete eventData;
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}


	NS_IMETHODIMP JRexWindow::Reload(PRUint32 reloadFlags) {
		JREX_LOGLN("Reload()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return mWebNavigation->Reload(reloadFlags);
		nsresult rv=ExecInEventQ(this,RELOAD,(void*)reloadFlags,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("Reload()--> **** rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GoToAnchorInternal(PRUnichar* anchorName, PRBool shouldScroll) {
        nsCOMPtr<nsIDocShell> pIDocShell;
        nsresult rv = GetDocShell(getter_AddRefs(pIDocShell));
        JREX_RETURN_IF_FAILED(rv,"GoToAnchorInternal()--> **** Getting nsIDocShell")
        nsCOMPtr<nsIPresShell> pIPresShell;
        rv = pIDocShell->GetPresShell(getter_AddRefs(pIPresShell));
        JREX_RETURN_IF_FAILED(rv,"GoToAnchorInternal()--> **** Getting nsIPresShell")
        nsEmbedString myAnchorName(anchorName);
        rv=pIPresShell->GoToAnchor(myAnchorName, shouldScroll);
        JREX_LOGLN("GoToAnchorInternal()--> **** GoToAnchor rv<"<<rv<<"> ****")
        return rv;
	}

	NS_IMETHODIMP JRexWindow::GoToAnchor(PRUnichar* anchorName, PRBool shouldScroll) {
		JREX_LOGLN("GoToAnchor()--> **** mBrowCreated<"<<mBrowCreated<<"> anchorName<"<<anchorName<<"> shouldScroll<"<<shouldScroll<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GoToAnchorInternal(anchorName, shouldScroll);

		nsresult rv=NS_OK;
	   	GoToAnchorEventData* eventData = new GoToAnchorEventData;
		if (eventData) {
			JREX_LOGLN("GoToAnchor()--> **** eventData Created ****")
			eventData->anchorName=anchorName;
			eventData->shouldScroll=shouldScroll;

			rv=ExecInEventQ(this,GO_TO_ANCHOR,eventData,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
			JREX_LOGLN("GoToAnchor()--> **** ExecInEventQ rv<"<<rv<<"> Created ****")
			if (NS_FAILED(rv)){
				CRTFREEIF(eventData->anchorName);
				delete eventData;
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

	NS_IMETHODIMP JRexWindow::Stop(PRUint32 stopFlags) {
		JREX_LOGLN("Stop()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return mWebNavigation->Reload(stopFlags);

		nsresult rv=ExecInEventQ(this,STOP,(void*)stopFlags,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("Stop()--> **** rv<"<<rv<<"> ****")
		return rv;
	}

	NS_IMETHODIMP JRexWindow::GetDocument(nsIDOMDocument * *aDocument) {
		JREX_LOGLN("GetDocument()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return mWebNavigation->GetDocument(aDocument);

		nsIDOMDocument* mydoc=nsnull;
		nsresult rv=ExecInEventQ(this,GET_DOC,nsnull,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void **)&mydoc);
		JREX_LOGLN("GetDocument()--> **** rv<"<<rv<<"> mydoc<"<<mydoc<<">****")
		if (NS_SUCCEEDED(rv))
			*aDocument=mydoc;
		return rv;
	}

	nsresult JRexWindow::GetContentStringInternal(PRUnichar** retContent, PRUnichar* contType, PRUint32 outFlag){
		NS_ENSURE_ARG_POINTER(retContent);
		nsresult rv = NS_OK;

		nsEmbedString myContTypeu(contType);
		nsEmbedCString myContTypea;
		CopyUCS2toASCII(myContTypeu, myContTypea);

		nsEmbedCString formatType(NS_DOC_ENCODER_CONTRACTID_BASE);
		formatType.Append(myContTypea.get());
  		nsCOMPtr<nsIDocumentEncoder> encoder = do_CreateInstance(formatType.get(), &rv);
  		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** do_CreateInstance nsIDocumentEncoder")

		nsCOMPtr<nsIDOMWindow> parent;
		rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(parent));
		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** mWebBrowser GetContentDOMWindow ")

		nsCOMPtr<nsIDOMDocument> domDoc;
		rv=parent->GetDocument(getter_AddRefs(domDoc));
		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** GetDocument")

		nsCOMPtr<nsIDocument> doc=do_QueryInterface(domDoc,&rv);
		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** do_QueryInterface nsIDocument")

		nsEmbedString readstring;
		readstring.AssignWithConversion(myContTypea.get());
		rv = encoder->Init(doc, readstring, outFlag);
		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** encoder Init")

		nsISelection *tempSel=nsnull;
		rv=GetSelectionInternal(&tempSel);
		JREX_LOGLN("GetContentStringInternal()--> **** GetSelectionInternal rv<"<<rv<<"> tempSel<"<<tempSel<<">***")
		if(tempSel){
			encoder->SetSelection(tempSel);
			JREX_LOGLN("GetContentStringInternal()--> **** SetSelection rv<"<<rv<<"> ***")
		}

		nsEmbedString tmp;
		rv = encoder->EncodeToString(tmp);
		JREX_RETURN_IF_FAILED(rv,"GetContentStringInternal()--> **** encoder EncodeToString")
  		*retContent = ToNewUnicode(tmp);
  		return rv;
	}

	nsresult JRexWindow::GetContentString(PRUnichar** retContent, PRUnichar* contType, PRUint32 outFlag) {
		JREX_LOGLN("GetContentString()--> **** mBrowCreated<"<<mBrowCreated<<"> contType<"<<contType<<"> outFlag<"<<outFlag<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GetContentStringInternal(retContent, contType, outFlag);

		nsresult rv=NS_OK;
	   	GetContentStringEventData* eventData = new GetContentStringEventData;
		if (eventData) {
			JREX_LOGLN("GetContentString()--> **** eventData Created ****")
			eventData->contType=contType;
			eventData->outFlag=outFlag;

			PRUnichar* tmpContent=nsnull;
			nsresult rv=ExecInEventQ(this,GET_CONTENT_STRING,eventData,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void**)&tmpContent);
			JREX_LOGLN("GetContentString()--> **** ExecInEventQ rv<"<<rv<<"> tmpContent<"<<(PRUint32)tmpContent<<"> Created ****")
			if (NS_SUCCEEDED(rv))
				*retContent=tmpContent;
			else
				delete eventData;
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}


	NS_IMETHODIMP JRexWindow::GetCurrentURI(nsIURI * *aCurrentURI) {
		JREX_LOGLN("GetCurrentURI()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return mWebNavigation->GetCurrentURI(aCurrentURI);

		nsIURI* myURI;
		nsresult rv=ExecInEventQ(this,GET_CUR_URI,nsnull,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void**)&myURI);
		JREX_LOGLN("GetCurrentURI()--> **** rv<"<<rv<<"> myURI<"<<(PRUint32)myURI<<">****")
		if (NS_SUCCEEDED(rv))
			*aCurrentURI=myURI;
		return rv;
	}

	NS_IMETHODIMP JRexWindow::GetReferringURI(nsIURI * *aReferringURI) {
		JREX_LOGLN("GetReferringURI()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return mWebNavigation->GetReferringURI(aReferringURI);

		nsCOMPtr<nsIURI> myURI;
		nsresult rv=ExecInEventQ(this,GET_REF_URI,nsnull,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,getter_AddRefs(myURI));
		JREX_LOGLN("GetReferringURI()--> **** rv<"<<rv<<"> myURI<"<<myURI.get()<<">****")
		if (NS_SUCCEEDED(rv))
			*aReferringURI=myURI.get();
		return rv;
	}

	NS_IMETHODIMP JRexWindow::GetSessionHistory(nsVoidArray* hisArray, PRInt32* maxLength) {
		JREX_LOGLN("GetSessionHistory()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_ERROR_NOT_INITIALIZED;
		if(IS_EQT)
			return GetSessionHistoryInternal(hisArray,maxLength);

		PRInt32 tempMaxLen=0;
		nsresult rv=ExecInEventQ(this,GET_SESSION,hisArray,PR_TRUE,HandleNavigationEvent,DestroyNavigationEvent,(void**)&tempMaxLen);
		JREX_LOGLN("GetSessionHistory()--> **** rv<"<<rv<<"> tempMaxLen<"<<tempMaxLen<<">****")
		if (NS_SUCCEEDED(rv))
			*maxLength=tempMaxLen;
		return rv;
	}

	NS_IMETHODIMP JRexWindow::SetSessionHistory(nsISHistory* aSessionHistory) {
		JREX_LOGLN("SetSessionHistory()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		return NS_OK;
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return mWebNavigation->SetSessionHistory(aSessionHistory);

		nsresult rv=ExecInEventQ(this,SET_SESSION,aSessionHistory,PR_FALSE,HandleNavigationEvent,DestroyNavigationEvent,nsnull);
		JREX_LOGLN("SetSessionHistory()--> **** rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetSessionHistoryInternal(nsVoidArray* hisArray, PRInt32* maxLength) {
		NS_ENSURE_ARG_POINTER(hisArray);
		nsCOMPtr<nsISHistory> history;
		nsresult rv=mWebNavigation->GetSessionHistory(getter_AddRefs(history));
		JREX_LOGLN("GetSessionHistoryInternal()--> **** GetSessionHistory rv<"<<rv<<"> ****")
		if (NS_FAILED(rv) || IS_NULL(history))
			return rv;
		JREX_LOGLN("GetSessionHistoryInternal()--> **** GetSessionHistory Done!!! ****")

		PRInt32 count=0;
		rv=history->GetCount(&count);
		JREX_LOGLN("GetSessionHistoryInternal()--> **** GetCount rv<"<<rv<<"> count<"<<count<<"> ****")
		if(count<=0)return rv;

		rv=history->GetMaxLength(maxLength);
		JREX_LOGLN("GetSessionHistoryInternal()--> *** GetMaxLength rv<"<<rv<<"> maxLength<"<<(*maxLength)<<"> ***")

		PRBool hasElem = PR_FALSE;
		nsCOMPtr<nsISimpleEnumerator> sEnum;
		rv=history->GetSHistoryEnumerator(getter_AddRefs(sEnum));
		JREX_LOGLN("GetSessionHistoryInternal()--> **** GetSHistoryEnumerator rv<"<<rv<<"> ****")
		if (NS_FAILED(rv))return rv;
		JREX_LOGLN("GetSessionHistoryInternal()--> **** GetSHistoryEnumerator Done!!! ****")

		rv=sEnum->HasMoreElements(&hasElem);
		while(NS_SUCCEEDED(rv) && hasElem==PR_TRUE){
			nsCOMPtr<nsISupports> entry;
			rv=sEnum->GetNext(getter_AddRefs(entry));
			JREX_LOGLN("GetSessionHistoryInternal()--> **** GetNext rv<"<<rv<<"> ****")
			if (NS_FAILED(rv))continue;

			nsCOMPtr<nsIHistoryEntry> hisEntry=do_QueryInterface(entry,&rv);
			JREX_LOGLN("GetSessionHistoryInternal()--> *** do_QueryInterface rv<"<<rv<<"> ***")

			if(NS_SUCCEEDED(rv) && NOT_NULL(hisEntry)){
				HistoryEntry *myEntry= new HistoryEntry;
				if(IS_NULL(myEntry))continue;

				nsCOMPtr<nsIURI> myUri;
				rv=hisEntry->GetURI(getter_AddRefs(myUri));
				JREX_LOGLN("GetSessionHistoryInternal()--> *** GetURI rv<"<<rv<<"> ***")

				if(NS_SUCCEEDED(rv) && NOT_NULL(myUri)){
					JREX_LOGLN("GetSessionHistoryInternal()--> *** NOT_NULL uri ***")
					nsEmbedCString spec;
					rv=myUri->GetSpec(spec);
					JREX_LOGLN("GetSessionHistoryInternal()--> *** GetSpec rv<"<<rv<<"> ***")
					myEntry->uri=NS_SUCCEEDED(rv)?ToNewUnicode(spec):nsnull;
				}else
					myEntry->uri=nsnull;
				JREX_LOGLN("GetSessionHistoryInternal()--> *** myEntry->uri<"<<(PRUint32)myEntry->uri<<"> ***")

				nsXPIDLString title;
				rv=hisEntry->GetTitle(getter_Copies(title));
				JREX_LOGLN("GetSessionHistoryInternal()--> *** GetTitle rv<"<<rv<<"> ***")
				myEntry->title=NS_SUCCEEDED(rv)?ToNewUnicode(title):nsnull;
				JREX_LOGLN("GetSessionHistoryInternal()--> *** myEntry->title<"<<myEntry->title<<"> ***")

				rv=hisEntry->GetIsSubFrame(&myEntry->isSubFrame);
				JREX_LOGLN("GetSessionHistoryInternal()--> *** rv<"<<rv<<"> isSubFrame<"<<(myEntry->isSubFrame==PR_TRUE)<<"> ***")
				hisArray->AppendElement(myEntry);
			}
			rv=sEnum->HasMoreElements(&hasElem);
			JREX_LOGLN("GetSessionHistoryInternal()--> *** hasElem<"<<(hasElem==PR_TRUE?"TRUE":"FALSE")<<"> ***")
		}
		return NS_OK;
	}


	nsresult JRexWindow::OpenWindowInternal(PRUint16 type,const char *aUrl, const char *ref,
											const char *aName, const char *aFeatures, nsIDOMWindow **_retval){
		NS_ENSURE_ARG_POINTER(_retval);
		nsresult rv;
		nsCOMPtr<nsISupportsArray> block;
		switch(type){
			case TYPE_PAGE_INFO:
			{
				block=do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
				JREX_LOGLN("OpenWindowInternal()--> **** do_CreateInstance nsISupportsArray rv<"<<rv<<"> ****")

				nsCOMPtr<nsIDOMWindow> parent;
				rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(parent));
				JREX_LOGLN("OpenWindowInternal()--> **** GetContentDOMWindow rv<"<<rv<<"> ****")
				if (NS_FAILED(rv))return rv;

				nsCOMPtr<nsIDOMDocument> doc;
				rv=parent->GetDocument(getter_AddRefs(doc));
				JREX_LOGLN("OpenWindowInternal()--> **** GetDocument rv<"<<rv<<"> ****")
				if (NS_FAILED(rv))return rv;
				rv=block->InsertElementAt(nsnull,0);
				rv|=block->InsertElementAt(doc,0);
				JREX_LOGLN("OpenWindowInternal()--> **** InsertElementAt rv<"<<rv<<"> ****")
				if (NS_FAILED(rv))return rv;
				break;
			}
			default:
				return NS_OK;
		};
		nsCOMPtr<nsIWindowWatcher> windowWatcher = do_GetService(NS_WINDOWWATCHER_CONTRACTID, &rv);
		JREX_LOGLN("OpenWindowInternal()--> **** do_GetService windowWatcher rv<"<<rv<<"> ****")
		if (NS_FAILED(rv))return rv;

		nsCOMPtr<nsIDOMWindow> parent;
		rv=mWebBrowser->GetContentDOMWindow(getter_AddRefs(parent));
		JREX_LOGLN("OpenWindowInternal()--> **** GetContentDOMWindow rv<"<<rv<<"> ****")
		if (NS_FAILED(rv))return rv;

		nsCOMPtr<nsIDOMWindow> newWindow;
		rv=windowWatcher->OpenWindow(parent,aUrl,aName,aFeatures,block,getter_AddRefs(newWindow));
		JREX_LOGLN("OpenWindowInternal()--> **** windowWatcher OpenWindow rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			NS_IF_ADDREF(*_retval=newWindow.get());
		return *_retval ? NS_OK : NS_ERROR_FAILURE;
	}



	void* PR_CALLBACK JRexWindow::HandleNavigationEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleNavigationEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;
		switch(event->eventType){
			case LOAD:
			{
				LoadURIEventData* evtData = NS_REINTERPRET_CAST(LoadURIEventData*, event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv =window->LoadURIInternal(evtData->uri, evtData->loadFlags, evtData->referrer,
														evtData->postData, evtData->headers);
				JREX_LOGLN("HandleNavigationEvent()--> **** LoadURIInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case LOAD_STREAM:
			{
				LoadStreamEventData* evtData = NS_REINTERPRET_CAST(LoadStreamEventData*, event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv =window->LoadStreamInternal(evtData->inStream, evtData->uri, evtData->contType,evtData->charset,
						evtData->loadFlags, evtData->referrer, evtData->owner, evtData->inhherit, evtData->target,
							evtData->postStream, evtData->headerStream);
				JREX_LOGLN("HandleNavigationEvent()--> **** LoadStreamInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case CAN_BACK:
			{
				PRBool canBack=PR_FALSE;
				rVal->rv=window->mWebNavigation->GetCanGoBack(&canBack);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetCanGoBack canBack<"<<(canBack==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)canBack;
				break;
			}
			case CAN_FORWARD:
			{
				PRBool canForward=PR_FALSE;
				rVal->rv=window->mWebNavigation->GetCanGoForward(&canForward);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetCanGoForward canForward<"<<(canForward==PR_TRUE)<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)canForward;
				break;
			}
			case GO_BACK:
			{
				PRBool canBack=PR_FALSE;
				rVal->rv=window->mWebNavigation->GetCanGoBack(&canBack);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation canBack <"<<(canBack==PR_TRUE)<<"> ****")
				if(canBack==PR_TRUE)
					rVal->rv=window->mWebNavigation->GoBack();
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GoBack rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GO_FORWARD:
			{
				PRBool canForward=PR_FALSE;
				rVal->rv=window->mWebNavigation->GetCanGoForward(&canForward);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation canForward <"<<(canForward==PR_TRUE)<<"> ****")
				if(canForward==PR_TRUE)
					rVal->rv=window->mWebNavigation->GoForward();
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GoForward rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GO_TO_INDEX:
			{
				rVal->rv=window->mWebNavigation->GotoIndex((PRInt32)event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GotoIndex index<"<<event->eventData<<"> rv<"<<rVal->rv<<"> ****")
				break;
			}
			case RELOAD:
			{
				rVal->rv=window->mWebNavigation->Reload((PRInt32)event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation Reload flags<"<<event->eventData<<"> rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GO_TO_ANCHOR:
			{
				GoToAnchorEventData* evtData = NS_REINTERPRET_CAST(GoToAnchorEventData*, event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv =window->GoToAnchorInternal(evtData->anchorName, evtData->shouldScroll);
				JREX_LOGLN("HandleNavigationEvent()--> **** GoToAnchorInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			case STOP:
			{
				rVal->rv=window->mWebNavigation->Stop((PRInt32)event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation Stop flags<"<<event->eventData<<"> rv<"<<rVal->rv<<"> ****")
				break;
			}
			case GET_CUR_URI:
			{
				nsCOMPtr<nsIURI> myURI;
				rVal->rv=window->mWebNavigation->GetCurrentURI(getter_AddRefs(myURI));
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetCurrentURI myURI<"<<myURI<<"> rv<"<<rVal->rv<<"> ****")
				nsIURI* temp=nsnull;
				if(NS_SUCCEEDED(rVal->rv))
					NS_IF_ADDREF(temp=myURI.get());
				rVal->rData=temp;
				break;
			}
			case GET_REF_URI:
			{
				nsCOMPtr<nsIURI> myURI;
				rVal->rv=window->mWebNavigation->GetReferringURI(getter_AddRefs(myURI));
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetReferringURI myURI<"<<myURI<<"> rv<"<<rVal->rv<<"> ****")
				nsIURI* temp=nsnull;
				if(NS_SUCCEEDED(rVal->rv))
					NS_IF_ADDREF(temp=myURI.get());
				rVal->rData=temp;
				break;
			}
			case GET_DOC:
			{
				nsCOMPtr<nsIDOMDocument> myDoc;
				rVal->rv=window->mWebNavigation->GetDocument(getter_AddRefs(myDoc));
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetDocument myDoc<"<<myDoc<<"> rv<"<<rVal->rv<<"> ****")
				nsIDOMDocument* temp=nsnull;
				if(NS_SUCCEEDED(rVal->rv))
					NS_IF_ADDREF(temp=myDoc.get());
				rVal->rData=temp;
				break;
			}
			case GET_CONTENT_STRING:
			{
				PRUnichar* retContent=nsnull;
				GetContentStringEventData* evtData = NS_REINTERPRET_CAST(GetContentStringEventData*, event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** evtData <"<<evtData<<"> ****")
				rVal->rv =window->GetContentStringInternal(&retContent, evtData->contType, evtData->outFlag);
				JREX_LOGLN("HandleNavigationEvent()--> **** GetContentStringInternal rv<"<<rVal->rv<<"> retContent<"<<(PRUint32)retContent<<"> ****")
				rVal->rData=retContent;
				break;
			}
			case GET_SESSION:
			{
				PRInt32 maxLen=0;
				nsVoidArray* vArray = NS_REINTERPRET_CAST(nsVoidArray*, event->eventData);
				rVal->rv=window->GetSessionHistoryInternal(vArray, &maxLen);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation GetSessionHistoryInternal eventData<"<<event->eventData<<"> rv<"<<rVal->rv<<"> ****")
				rVal->rData=(void*)maxLen;
				break;
			}
			case SET_SESSION:
			{
				rVal->rv=window->mWebNavigation->SetSessionHistory((nsISHistory *)event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** mWebNavigation SetSessionHistory eventData<"<<event->eventData<<"> rv<"<<rVal->rv<<"> ****")
				break;
			}
			case OPEN_WINDOW:
			{
				OpenWindowEventData* evtData = NS_REINTERPRET_CAST(OpenWindowEventData*, event->eventData);
				JREX_LOGLN("HandleNavigationEvent()--> **** type<"<<evtData->type<<"> uri<"
											<<(PRUint32)evtData->uri<<"> referrer<"
											<<(PRUint32)evtData->referrer<<"> windowName<"
											<<(PRUint32)evtData->windowName<<"> feature<"
											<<(PRUint32)evtData->feature<<"> ****")

				nsCOMPtr<nsIDOMWindow> newWindow;
				rVal->rv=window->OpenWindowInternal(evtData->type, evtData->uri, evtData->referrer, evtData->windowName, evtData->feature, getter_AddRefs(newWindow));
				JREX_LOGLN("HandleNavigationEvent()--> **** OpenWindowInternal rv<"<<rVal->rv<<"> ****")
				break;
			}
			default:
			{
				JREX_LOGLN("HandleNavigationEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		};
		JREX_LOGLN("HandleNavigationEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK  JRexWindow::DestroyNavigationEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyNavigationEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData){
			if(event->eventType==LOAD){
				LoadURIEventData* evtData = NS_REINTERPRET_CAST(LoadURIEventData*, event->eventData);
				delete evtData;
			}else
			if(event->eventType==LOAD_STREAM){
				LoadStreamEventData* evtData = NS_REINTERPRET_CAST(LoadStreamEventData*, event->eventData);
				delete evtData;
			}else
			if(event->eventType==OPEN_WINDOW){
				OpenWindowEventData* evtData = NS_REINTERPRET_CAST(OpenWindowEventData*, event->eventData);
				delete evtData;
			}else
			if(event->eventType==GO_TO_ANCHOR){
				GoToAnchorEventData* evtData = NS_REINTERPRET_CAST(GoToAnchorEventData*, event->eventData);
				delete evtData;
			}else
			if(event->eventType==GET_CONTENT_STRING){
				GetContentStringEventData* evtData = NS_REINTERPRET_CAST(GetContentStringEventData*, event->eventData);
				delete evtData;
			}
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}


