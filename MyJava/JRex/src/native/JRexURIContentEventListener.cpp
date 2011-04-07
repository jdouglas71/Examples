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
#include "JRex_JNI_URIContentEvent.h"
using namespace JRex_JNI_URIContentEvent;

NS_IMETHODIMP JRexWindow::OnStartURIOpen(nsIURI   *aURI, PRBool *aAbortOpen){
	JREX_LOGLN("OnStartURIOpen()--> *** I AM HERE***")
	NS_ENSURE_ARG_POINTER(aAbortOpen);
	*aAbortOpen = PR_FALSE;

	OnStartEventParam *osParm=new OnStartEventParam;
	if(IS_NULL(osParm))return NS_ERROR_OUT_OF_MEMORY;
	osParm->target=NS_PTR_TO_INT32(this);
	osParm->uriEventType=URI_ON_START_EVENT;

	nsresult rv;
	if(NOT_NULL(aURI)){
		JREX_LOGLN("OnStartURIOpen()--> *** NOT_NULL uri ***")
		nsEmbedCString spec;
		rv=aURI->GetSpec(spec);
		if(NS_SUCCEEDED(rv))
			osParm->uri=ToNewCString(spec);
		else
			osParm->uri=nsnull;
	}else{
		JREX_LOGLN("OnStartURIOpen()--> *** NULL uri ***")
		osParm->uri=nsnull;
	}

	PRBool tempRV=PR_FALSE;
	rv=fireEvent(osParm,PR_TRUE, (void**)&tempRV);
	*aAbortOpen=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
	JREX_LOGLN("OnStartURIOpen()--> *** fireEvent rv<"<<rv<<"> ***")
	return NS_OK;
}


NS_IMETHODIMP JRexWindow::DoContent(const char	*aContentType, PRBool aIsContentPreferred,
										nsIRequest         *aRequest,
										nsIStreamListener **aContentHandler,
										PRBool             *aAbortProcess){
	JREX_LOGLN("DoContent()--> *** I AM HERE***")
	NS_ENSURE_ARG_POINTER(aAbortProcess);
	*aAbortProcess = PR_FALSE;

	DoContentEventParam *dcParm=new DoContentEventParam;
	if(IS_NULL(dcParm))return NS_ERROR_OUT_OF_MEMORY;
	dcParm->target=NS_PTR_TO_INT32(this);
	dcParm->uriEventType=URI_DO_CONTENT;
	dcParm->isContentPreferred=aIsContentPreferred;

	nsresult rv;
	if(NOT_NULL(aContentType)){
		JREX_LOGLN("DoContent()--> *** NOT_NULL aContentType ***")
		nsEmbedCString contTypStr(aContentType);
		char* temp=ToNewCString(contTypStr);
		JREX_LOGLN("DoContent()--> ***  contTypStr<"<<temp<<"> ***")
		dcParm->contentType=temp;
	}else
		dcParm->contentType=nsnull;

	if(NOT_NULL(aRequest)){
		JREX_LOGLN("DoContent()--> *** NOT_NULL aRequest ***")
		nsEmbedCString temp;
		nsresult rv=aRequest->GetName(temp);
		if(NS_SUCCEEDED(rv))
			dcParm->reqName=ToNewCString(temp);
		else
			dcParm->reqName=nsnull;

		JREX_LOGLN("DoContent()--> ***  dcParm->reqName<"<<(PRUint32)dcParm->reqName<<"> ***")

		aRequest->GetStatus(&rv);
		dcParm->reqStatus=rv;

		PRBool isReqPending=PR_FALSE;
		aRequest->IsPending(&isReqPending);
		dcParm->isReqPending=isReqPending;
	}else{
		JREX_LOGLN("DoContent()--> *** NULL aRequest ***")
		dcParm->reqName=nsnull;
		dcParm->reqStatus=NS_OK;
		dcParm->isReqPending=PR_FALSE;
	}
	URIContentRV* tempRV=nsnull;
	rv=fireEvent(dcParm,PR_TRUE, (void**)&tempRV);
	JREX_LOGLN("DoContent()--> *** fireEvent rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv)){
		*aAbortProcess=tempRV->boolRV;
		if(NOT_NULL(tempRV->data)){
			JREX_LOGLN("DoContent()--> *** tempRV->data !NULL ***")
			nsIStreamListener* tempStreamLis= NS_REINTERPRET_CAST(nsIStreamListener*, tempRV->data);
			NS_IF_ADDREF(*aContentHandler=tempStreamLis);
		}
	}
	return rv;
}

NS_IMETHODIMP JRexWindow::IsPreferred(const char *aContentType,char **aDesiredContentType,
				  						PRBool *aCanHandleContent){
	JREX_LOGLN("IsPreferred()--> *** I AM HERE***")
	NS_ENSURE_ARG_POINTER(aCanHandleContent);
	*aCanHandleContent = PR_FALSE;

	IsPreferredEventParam *ipParm=new IsPreferredEventParam;
	if(IS_NULL(ipParm))return NS_ERROR_OUT_OF_MEMORY;
	ipParm->target=NS_PTR_TO_INT32(this);
	ipParm->uriEventType=URI_IS_PREFERRED;

	nsresult rv;
	if(NOT_NULL(aContentType)){
		JREX_LOGLN("IsPreferred()--> *** NOT_NULL aContentType ***")
		nsEmbedCString contTypStr(aContentType);
		char* temp=ToNewCString(contTypStr);
		JREX_LOGLN("IsPreferred()--> ***  contTypStr<"<<temp<<"> ***")
		ipParm->contentType=temp;
	}else
		ipParm->contentType=nsnull;

	URIContentRV* tempRV=nsnull;
	rv=fireEvent(ipParm,PR_TRUE, (void**)&tempRV);
	JREX_LOGLN("IsPreferred()--> *** fireEvent rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv)){
		//Contributed by Bill Filler <bfiller@pepper.com>
		*aCanHandleContent=!(tempRV->boolRV);
		if(NOT_NULL(tempRV->data)){
			JREX_LOGLN("IsPreferred()--> *** tempRV->data !NULL ***")
			char* tempContTyp= NS_REINTERPRET_CAST(char*, tempRV->data);
			*aDesiredContentType=tempContTyp;
		}
	}
	return rv;

}

NS_IMETHODIMP JRexWindow::CanHandleContent(const char *aContentType, PRBool aIsContentPreferred, char **aDesiredContentType, PRBool *canHandleContent){
	JREX_LOGLN("CanHandleContent()--> *** I AM HERE***")
	NS_ENSURE_ARG_POINTER(canHandleContent);
	*canHandleContent = PR_FALSE;

	CanHandleEventParam *chParm=new CanHandleEventParam;
	if(IS_NULL(chParm))return NS_ERROR_OUT_OF_MEMORY;
	chParm->target=NS_PTR_TO_INT32(this);
	chParm->uriEventType=URI_CAN_HANDLE_CONTENT;
	chParm->isContentPreferred=aIsContentPreferred;

	nsresult rv;
	if(NOT_NULL(aContentType)){
		JREX_LOGLN("CanHandleContent()--> *** NOT_NULL aContentType ***")
		nsEmbedCString contTypStr(aContentType);
		char* temp=ToNewCString(contTypStr);
		JREX_LOGLN("CanHandleContent()--> ***  contTypStr<"<<temp<<"> ***")
		chParm->contentType=temp;
	}else
		chParm->contentType=nsnull;

	URIContentRV* tempRV=nsnull;
	rv=fireEvent(chParm,PR_TRUE, (void**)&tempRV);
	JREX_LOGLN("CanHandleContent()--> *** fireEvent rv<"<<rv<<"> ***")
	if(NS_SUCCEEDED(rv)){
		//Contributed by Bill Filler <bfiller@pepper.com>
		*canHandleContent= !(tempRV->boolRV);
		if(NOT_NULL(tempRV->data)){
			JREX_LOGLN("CanHandleContent()--> *** tempRV->data !NULL ***")
			char* tempContTyp= NS_REINTERPRET_CAST(char*, tempRV->data);
			*aDesiredContentType=tempContTyp;
		}
	}
	return rv;
}

NS_IMETHODIMP JRexWindow::GetLoadCookie(nsISupports **aLoadCookie){
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP JRexWindow::SetLoadCookie(nsISupports *aLoadCookie){
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP JRexWindow::GetParentContentListener(nsIURIContentListener **aParent){
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP JRexWindow::SetParentContentListener(nsIURIContentListener *aParent){
	return NS_ERROR_NOT_IMPLEMENTED;
}

