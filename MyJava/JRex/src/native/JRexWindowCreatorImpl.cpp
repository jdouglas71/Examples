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

 	#include "JRexWindowCreator.h"
 	#include "JRexWindow.h"
 	#include "JRex_JNI_WindowEvent.h"

 	using namespace JRex_JNI_WindowEvent;

	static NS_DEFINE_CID(kAppShellServiceCID, NS_APPSHELL_SERVICE_CID);

	JRexWindowCreator::JRexWindowCreator(){
		JREX_LOGLN("JRexWindowCreator()--> **** I AM HERE ****")
	}

	JRexWindowCreator::~JRexWindowCreator() {
		JREX_LOGLN("~JRexWindowCreator()--> **** I AM HERE ****")
	}

	NS_IMPL_THREADSAFE_ISUPPORTS2(JRexWindowCreator, nsIWindowCreator, nsIWindowCreator2)

	//1
	/* nsIWebBrowserChrome createChromeWindow (in nsIWebBrowserChrome parent, in PRUint32 chromeFlags); */
	NS_IMETHODIMP JRexWindowCreator::CreateChromeWindow(nsIWebBrowserChrome *parent, PRUint32 chromeFlags, nsIWebBrowserChrome **_retval)
	{
		JREX_LOGLN("CreateChromeWindow()--> *** Inside CreateChromeWindow parent<"<<parent<<"> chromeFlags<"<<chromeFlags<<"> ***")
		if(!gXpcomRunning){
			*_retval = 0;
			return NS_ERROR_FAILURE;
		}
		PRBool cancel=PR_FALSE;
  		return CreateChromeWindow2(parent, chromeFlags, 0, 0, &cancel, _retval);
	}

	/* [noscript] nsIWebBrowserChrome createChromeWindow2 (in nsIWebBrowserChrome parent, in PRUint32 chromeFlags, in PRUint32 contextFlags, in nsIURI uri, out boolean cancel); */
	NS_IMETHODIMP JRexWindowCreator::CreateChromeWindow2(nsIWebBrowserChrome *parent, PRUint32 chromeFlags,
												PRUint32 contextFlags, nsIURI* uri, PRBool *cancel, nsIWebBrowserChrome **_retval)
	{
		JREX_LOGLN("CreateChromeWindow2()--> *** Inside CreateChromeWindow2 parent<"<<parent<<"> chromeFlags<"<<chromeFlags<<"> contextFlags<"<<contextFlags<<">  uri<"<<uri<<"> cancel<"<<(*cancel)<<">***")
		if(!gXpcomRunning){
			*cancel = PR_TRUE;
			*_retval = 0;
			return NS_ERROR_FAILURE;
		}

		NS_ENSURE_ARG_POINTER(cancel);
		NS_ENSURE_ARG_POINTER(_retval);
		*cancel = PR_FALSE;
		*_retval = 0;
		WindowCreateEventParam *wParm=new WindowCreateEventParam;
		if(IS_NULL(wParm))return NS_ERROR_OUT_OF_MEMORY;
		//basic
		wParm->target=nsnull;
		wParm->winEventType=WIN_CREATE_EVENT;
		//extended
		JRexWindow *actualParent=NOT_NULL(parent)?JRexWindow::GetJRexWindow(parent):nsnull;
		//TODO remove this hack, for stoping multiple security alert dialog.
		//<START-HACK>
		if(actualParent){
			if(actualParent->mChildIsModalLooping){
				JREX_LOGLN("CreateChromeWindow2()--> *** HACK STRIKE ***")
				*cancel = PR_TRUE;
				*_retval = 0;
				return NS_OK;
			}
			if(chromeFlags & nsIWebBrowserChrome::CHROME_MODAL)
				actualParent->mChildIsModalLooping=PR_TRUE;
		}
		//<END-HACK>
		wParm->parentWin=NS_PTR_TO_INT32(actualParent);
		JREX_LOGLN("CreateChromeWindow2()--> *** parentWin<"<<wParm->parentWin<<"> ***")
		wParm->chromeFlags=chromeFlags;
		wParm->contextFlags=contextFlags;

		nsresult rv;
		if(NOT_NULL(uri)){
			JREX_LOGLN("CreateChromeWindow2()--> *** NOT_NULL uri ***")
			nsEmbedCString spec;
			rv=uri->GetSpec(spec);
			if(NS_SUCCEEDED(rv))
				wParm->uri=ToNewCString(spec);
			else
				wParm->uri=nsnull;
		}else{
			JREX_LOGLN("CreateChromeWindow2()--> *** NULL uri ***")
			wParm->uri=nsnull;
		}

		PRUint32 tmpWindow=0;
		rv=fireEvent(wParm,PR_TRUE, (void**)&tmpWindow);
		JREX_LOGLN("CreateChromeWindow2()--> *** fireEvent rv<"<<rv<<"> tmpWindow<"<<tmpWindow<<"> ***")

		JRexWindow *newJRexWindow=(JRexWindow *)NS_INT32_TO_PTR(tmpWindow);
		if (NOT_NULL(newJRexWindow)) {
			newJRexWindow->mChromeFlag=chromeFlags;
			newJRexWindow->mParentIntPtr=NS_PTR_TO_INT32(actualParent);
			/*if (chromeFlags & nsIWebBrowserChrome::CHROME_OPENAS_CHROME){
				nsCOMPtr<nsIWebBrowserSetup> webBrowserAsSetup(do_QueryInterface(newJRexWindow->mWebBrowser,&rv));
				JREX_LOGLN("CreateChromeWindow2()--> *** webBrowserAsSetup rv<"<<rv<<"> ***")
				if (webBrowserAsSetup){
					webBrowserAsSetup->SetProperty(nsIWebBrowserSetup::SETUP_IS_CHROME_WRAPPER, PR_TRUE);
					JREX_LOGLN("CreateChromeWindow2()--> **** SETUP_IS_CHROME_WRAPPER rv<"<<rv<<"> ****")
				}
			}*/
			*_retval = NS_STATIC_CAST(nsIWebBrowserChrome *,newJRexWindow);
			NS_IF_ADDREF(*_retval);
		}else{
			*cancel=PR_TRUE;
			rv=NS_OK;
		}
		JREX_LOGLN("CreateChromeWindow2()--> *** nsIWebBrowserChrome <"<<_retval<<"> ***")
		return rv;
	}
