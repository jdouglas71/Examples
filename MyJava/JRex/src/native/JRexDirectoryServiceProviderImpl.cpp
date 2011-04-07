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


	#include "JRexDirServiceProvider.h"

	/*
	#define APP_REGISTRY_NAME 			NS_EM_LITERAL_CSTRING("registry.dat")
	#define PROFILE_ROOT_DIR_NAME       NS_EM_LITERAL_CSTRING("Profiles")
	#define DEFAULTS_PROFILE_DIR_NAME   NS_EM_LITERAL_CSTRING("profile")
	#define RES_DIR_NAME                NS_EM_LITERAL_CSTRING("res")
	#define DEFAULTS_PREF_DIR_NAME      NS_EM_LITERAL_CSTRING("pref")
	#define DEFAULTS_PROFILE_DIR_NAME   NS_EM_LITERAL_CSTRING("profile")
	*/

	#define REGISTY_FILE_NAME           NS_EM_LITERAL_CSTRING("JRex-BrowserReg.dat")
	#define CHROME_DIR_NAME             NS_EM_LITERAL_CSTRING("chrome")
	#define COMPONENTS_DIR_NAME         NS_EM_LITERAL_CSTRING("components")
	#define PLUGINS_DIR_NAME            NS_EM_LITERAL_CSTRING("plugins")
	#define SEARCH_DIR_NAME	            NS_EM_LITERAL_CSTRING("searchplugins")
	#define DEFAULTS_DIR_NAME           NS_EM_LITERAL_CSTRING("defaults")



	JRexDirServiceProvider::JRexDirServiceProvider(){

	}

	nsresult JRexDirServiceProvider::Initialize(const char* grePath){
		nsEmbedCString tempPath(grePath);
		nsresult rv=NS_NewNativeLocalFile(tempPath,PR_TRUE,getter_AddRefs(greDirPath));
		JREX_RETURN_IF_FAILED(rv,"Initialize()--> **** NS_NewNativeLocalFile ****")
		JREX_LOGLN("Initialize()--> **** NS_NewNativeLocalFile Done GOT THE GRE PATH <"<<greDirPath.get()<<"> ****")
		return rv;
	}

	JRexDirServiceProvider::~JRexDirServiceProvider(){
		greDirPath=nsnull;
	}

	NS_IMPL_THREADSAFE_ISUPPORTS1(JRexDirServiceProvider, nsIDirectoryServiceProvider)

	NS_IMETHODIMP JRexDirServiceProvider::GetFile(const char *prop,
												PRBool *persistant, nsIFile **_retval){
		JREX_LOGLN("GetFile()-->**** PROP REQUESTED <"<<prop<<"> ****")
		if(!greDirPath){
			JREX_LOGLN("GetFile()-->**** ERROR Initialize NOT CALLED ****")
			return NS_ERROR_FAILURE;
		}

		*_retval=nsnull;
		*persistant=PR_TRUE;
		nsresult rv=NS_OK;

		nsCOMPtr<nsIFile> temp;
		rv = greDirPath->Clone(getter_AddRefs(temp));
		JREX_RETURN_IF_FAILED(rv,"GetFile()--> **** greDirPath  Clone ****")

		nsCOMPtr<nsILocalFile> localGre = do_QueryInterface (temp,&rv);
		JREX_RETURN_IF_FAILED(rv,"GetFile()--> **** nsILocalFile  do_QueryInterface ****")

  		if(nsCRT::strcmp(prop, NS_GRE_DIR) == 0
  				||nsCRT::strcmp(prop, NS_APP_USER_PROFILES_ROOT_DIR)==0
  				||nsCRT::strcmp(prop, NS_APP_APPLICATION_REGISTRY_DIR)==0
  				|| nsCRT::strcmp(prop, NS_APP_USER_MIMETYPES_50_FILE)==0){
			//No appened
		}
		else if(nsCRT::strcmp(prop, NS_GRE_COMPONENT_DIR) == 0
					|| nsCRT::strcmp(prop, NS_XPCOM_COMPONENT_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(COMPONENTS_DIR_NAME);
    	}
    	else if(nsCRT::strcmp(prop, NS_APP_APPLICATION_REGISTRY_FILE) == 0){
			rv=localGre->AppendRelativeNativePath(REGISTY_FILE_NAME);
    	}
    	else if(nsCRT::strcmp(prop, NS_APP_CHROME_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(CHROME_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_PLUGINS_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(PLUGINS_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_SEARCH_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(SEARCH_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_DEFAULTS_50_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(DEFAULTS_DIR_NAME);
		}
    	/*
    	else if(nsCRT::strcmp(prop, NS_APP_PREF_DEFAULTS_50_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(DEFAULTS_DIR_NAME);
		    if (NS_SUCCEEDED(rv))
		    	rv=localGre->AppendRelativeNativePath(DEFAULTS_PREF_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_CHROME_DIR) == 0){
		    rv=localGre->AppendRelativeNativePath(CHROME_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_PROFILE_DEFAULTS_50_DIR) == 0 || nsCRT::strcmp(prop, NS_APP_USER_PROFILE_50_DIR) == 0 ){
			rv=localGre->AppendRelativeNativePath(DEFAULTS_DIR_NAME);
			if (NS_SUCCEEDED(rv))
		    	rv=localGre->AppendRelativeNativePath(DEFAULTS_PROFILE_DIR_NAME);
		}
    	else if(nsCRT::strcmp(prop, NS_APP_USER_CHROME_DIR) == 0){
			rv=localGre->AppendRelativeNativePath(DEFAULTS_DIR_NAME);
			if (NS_SUCCEEDED(rv))
		    	rv=localGre->AppendRelativeNativePath(DEFAULTS_PROFILE_DIR_NAME);
		    if (NS_SUCCEEDED(rv))
		    	rv=localGre->AppendRelativeNativePath(CHROME_DIR_NAME);
		}*/else
			rv=NS_ERROR_NOT_IMPLEMENTED;

		if(NS_SUCCEEDED(rv)){
			nsEmbedCString temp;localGre->GetNativePath(temp);
			JREX_LOGLN("GetFile()--> **** RETURNING PATH <"<<temp.get()<<"> FOR PROP<"<<prop<<">")
			rv=localGre->QueryInterface(NS_GET_IID(nsIFile),(void**)_retval);
		}
		/*
		{
			PRBool exists=PR_FALSE;
			localGre->IsDirectory(&exists);
			nsEmbedCString temp;localGre->GetNativePath(temp);
			//if(exists==PR_TRUE){
				JREX_LOGLN("GetFile()--> **** RETURNING PATH <"<<temp.get()<<"> FOR PROP<"<<prop<<">")
				rv=localGre->QueryInterface(NS_GET_IID(nsIFile),(void**)_retval);
			//}else{
			//	JREX_LOGLN("GetFile()--> **** ERROR!!! FILE IN PATH <"<<temp.get()<<"> DOES NOT EXSIST <"<<prop<<">")
			//	rv=NS_ERROR_NOT_IMPLEMENTED;
			//}
		}*/

		return rv;
 	}
