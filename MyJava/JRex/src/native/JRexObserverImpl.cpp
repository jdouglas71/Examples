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

//	#include "JRexWindow.h"
 	#include "JRexObserver.h"
 	#include "JRex_JNI_ObserverEvent.h"

	using namespace JRex_JNI_ObserverEvent;


	JRexObserver::JRexObserver(){
		JREX_LOGLN("JRexObserver()--> **** I AM HERE ****")
	}

	JRexObserver::~JRexObserver() {
		JREX_LOGLN("~JRexObserver()--> **** I AM HERE ****")
	}

	NS_IMPL_THREADSAFE_ISUPPORTS1(JRexObserver, nsIObserver)

	/* void observe (in nsISupports aSubject, in string aTopic, in wstring aData); */
	NS_IMETHODIMP JRexObserver::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
	{
		JREX_LOGLN("Observe()--> **** aTopic<"<<aTopic<<"> aData<"<<aData<<"> ****")
		ObserverEventParam *hParm=new ObserverEventParam;
		if(IS_NULL(hParm))return NS_ERROR_OUT_OF_MEMORY;
		if(NOT_NULL(aTopic)){
			JREX_LOGLN("Observe()--> *** NOT_NULL aTopic ***")
			nsEmbedCString temp(aTopic);
			hParm->topic=ToNewCString(temp);
		}else{
			JREX_LOGLN("Observe()--> *** NULL aTopic ***")
			hParm->topic=nsnull;
		}
		if(NOT_NULL(aData)){
			JREX_LOGLN("Observe()--> *** NOT_NULL data ***")
			nsEmbedString temp(aData);
			hParm->data=ToNewUTF8String(temp);
		}else{
			JREX_LOGLN("Observe()--> *** NULL data ***")
			hParm->data=nsnull;
		}
		nsresult rv=fireEvent(hParm,PR_FALSE, nsnull);
		JREX_LOGLN("Observe()--> *** fireEvent rv<"<<rv<<"> ***")
		return NS_OK;
	}

