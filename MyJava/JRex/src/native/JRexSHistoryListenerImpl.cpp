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
 	#include "JRex_JNI_HistoryEvent.h"
 	using namespace JRex_JNI_HistoryEvent;


	/* void OnHistoryNewEntry (in nsIURI aNewURI); */
	NS_IMETHODIMP JRexWindow::OnHistoryNewEntry(nsIURI *aNewURI){
		JREX_LOGLN("OnHistoryNewEntry()--> *** aNewURI<"<<aNewURI<<">***")
		BasicHistoryEventParam *hParm=new BasicHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;

		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_NEW_ENTRY_EVENT;

		nsresult rv;
		if(NOT_NULL(aNewURI)){
			JREX_LOGLN("OnHistoryNewEntry()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=aNewURI->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				hParm->uri=ToNewCString(spec);
			else
				hParm->uri=nsnull;
		}else{
			JREX_LOGLN("OnHistoryNewEntry()--> *** NULL uri ***")
			hParm->uri=nsnull;
		}
		rv=fireEvent(hParm,PR_FALSE, nsnull);
		JREX_LOGLN("OnHistoryNewEntry()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* boolean OnHistoryGoBack (in nsIURI aBackURI); */
	NS_IMETHODIMP JRexWindow::OnHistoryGoBack(nsIURI *aBackURI, PRBool *_retval){
		JREX_LOGLN("OnHistoryGoBack()--> *** aBackURI<"<<aBackURI<<">***")
		BasicHistoryEventParam *hParm=new BasicHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;

		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_GO_BACK_EVENT;

		nsresult rv;
		if(NOT_NULL(aBackURI)){
			JREX_LOGLN("OnHistoryGoBack()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=aBackURI->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				hParm->uri=ToNewCString(spec);
			else
				hParm->uri=nsnull;
		}else{
			JREX_LOGLN("OnHistoryGoBack()--> *** NULL uri ***")
			hParm->uri=nsnull;
		}
		PRBool tempRV=PR_FALSE;
		rv=fireEvent(hParm,PR_TRUE, (void**)&tempRV);
		*_retval=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
		JREX_LOGLN("OnHistoryGoBack()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* boolean OnHistoryGoForward (in nsIURI aForwardURI); */
	NS_IMETHODIMP JRexWindow::OnHistoryGoForward(nsIURI *aForwardURI, PRBool *_retval){
		JREX_LOGLN("OnHistoryGoForward()--> *** aForwardURI<"<<aForwardURI<<">***")

		BasicHistoryEventParam *hParm=new BasicHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;

		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_GO_FORWARD_EVENT;
		nsresult rv;
		if(NOT_NULL(aForwardURI)){
			JREX_LOGLN("OnHistoryGoForward()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=aForwardURI->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				hParm->uri=ToNewCString(spec);
			else
				hParm->uri=nsnull;
		}else{
			JREX_LOGLN("OnHistoryGoForward()--> *** NULL uri ***")
			hParm->uri=nsnull;
		}

		PRBool tempRV=PR_FALSE;
		rv=fireEvent(hParm,PR_TRUE, (void**)&tempRV);
		JREX_LOGLN("OnHistoryGoForward()--> *** fireEvent rv<"<<rv<<"> tempRV<"<<tempRV<<"> ***")
		*_retval=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
		return NS_OK;
	}

	/* boolean OnHistoryReload (in nsIURI aReloadURI, in unsigned long aReloadFlags); */
	NS_IMETHODIMP JRexWindow::OnHistoryReload(nsIURI *aReloadURI, PRUint32 aReloadFlags, PRBool *_retval){
		JREX_LOGLN("OnHistoryReload()--> *** aReloadURI<"<<aReloadURI<<"> aReloadFlags<"<<aReloadFlags<<"> ***")
		IntHistoryEventParam *hParm=new IntHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;

		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_RELOAD_EVENT;
		hParm->intData=aReloadFlags;
		nsresult rv;
		if(NOT_NULL(aReloadURI)){
			JREX_LOGLN("OnHistoryReload()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=aReloadURI->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				hParm->uri=ToNewCString(spec);
			else
				hParm->uri=nsnull;
		}else{
			JREX_LOGLN("OnHistoryReload()--> *** NULL uri ***")
			hParm->uri=nsnull;
		}
		PRBool tempRV=PR_FALSE;
		rv=fireEvent(hParm,PR_TRUE, (void**)&tempRV);
		*_retval=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
		JREX_LOGLN("OnHistoryReload()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* boolean OnHistoryGotoIndex (in long aIndex, in nsIURI aGotoURI); */
	NS_IMETHODIMP JRexWindow::OnHistoryGotoIndex(PRInt32 aIndex, nsIURI *aGotoURI, PRBool *_retval)
	{
		JREX_LOGLN("OnHistoryGotoIndex()--> *** aIndex<"<<aIndex<<"> aGotoURI<"<<aGotoURI<<">***")
		IntHistoryEventParam *hParm=new IntHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;

		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_GO_TO_INDEX_EVENT;
		hParm->intData=aIndex;
		nsresult rv;
		if(NOT_NULL(aGotoURI)){
			JREX_LOGLN("OnHistoryGotoIndex()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=aGotoURI->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				hParm->uri=ToNewCString(spec);
			else
				hParm->uri=nsnull;
		}else{
			JREX_LOGLN("OnHistoryGotoIndex()--> *** NULL uri ***")
			hParm->uri=nsnull;
		}
		PRBool tempRV=PR_FALSE;
		rv=fireEvent(hParm,PR_TRUE, (void**)&tempRV);
		*_retval=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
		JREX_LOGLN("OnHistoryGotoIndex()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

	/* boolean OnHistoryPurge (in long aNumEntries); */
	NS_IMETHODIMP JRexWindow::OnHistoryPurge(PRInt32 aNumEntries, PRBool *_retval){

		JREX_LOGLN("OnHistoryPurge()--> *** aNumEntries<"<<aNumEntries<<">***")
		IntHistoryEventParam *hParm=new IntHistoryEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;
		hParm->target=NS_PTR_TO_INT32(this);
		hParm->hisEventType=HIS_GO_TO_INDEX_EVENT;
		hParm->intData=aNumEntries;
		hParm->uri=nsnull;
		PRBool tempRV=PR_FALSE;
		nsresult rv=fireEvent(hParm,PR_TRUE, (void**)&tempRV);
		*_retval=NS_SUCCEEDED(rv)?tempRV:PR_FALSE;
		JREX_LOGLN("OnHistoryPurge()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}
