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


	#include "JRexPreference.h"
	using namespace JRexPreference;

	static NS_DEFINE_CID(kPrefServiceCID, NS_PREF_CID);

	nsresult JRexPreference::ReadUserPrefs(const char* file){
		JREX_LOGLN("ReadUserPrefs()--> **** file"<<file<<" ****")
		nsCOMPtr<nsILocalFile> tempPath;
		nsEmbedCString  filePath;filePath.Assign(file);
		nsresult rv=NS_NewNativeLocalFile(filePath,PR_TRUE,getter_AddRefs(tempPath));
		JREX_LOGLN("ReadUserPrefs()--> **** NS_NewNativeLocalFile rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv)){
			nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
			JREX_LOGLN("ReadUserPrefs()--> **** do_GetService rv"<<rv<<" ****")
			if(NS_SUCCEEDED(rv))
				rv=prefs->ReadUserPrefs(tempPath);
			JREX_LOGLN("ReadUserPrefs()--> **** ReadUserPrefs rv"<<rv<<" ****")
		}
		return rv;
	}

	nsresult JRexPreference::ResetPrefs(){
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("ResetPrefs()--> **** do_GetService rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->ResetPrefs();
		JREX_LOGLN("ResetPrefs()--> **** ReadUserPrefs rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::ResetUserPrefs(){
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("ResetUserPrefs()--> **** do_GetService rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->ResetUserPrefs();
		JREX_LOGLN("ResetUserPrefs()--> **** ReadUserPrefs rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::SavePrefFile(const char* file){
		JREX_LOGLN("SavePrefFile()--> **** file"<<file<<" ****")
		nsCOMPtr<nsILocalFile> tempPath;
		nsEmbedCString  filePath;filePath.Assign(file);
		nsresult rv=NS_NewNativeLocalFile(filePath,PR_TRUE,getter_AddRefs(tempPath));
		JREX_LOGLN("SavePrefFile()--> **** NS_NewNativeLocalFile rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv)){
			nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
			JREX_LOGLN("SavePrefFile()--> **** do_GetService rv"<<rv<<" ****")
			if(NS_SUCCEEDED(rv))
				rv=prefs->SavePrefFile(tempPath);
			JREX_LOGLN("SavePrefFile()--> **** SavePrefFile rv"<<rv<<" ****")
		}
		return rv;
	}

	nsresult JRexPreference::GetRoot(char * *aRoot){
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetRoot()--> **** do_GetService rv"<<rv<<" ****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetRoot(aRoot);
		JREX_LOGLN("GetRoot()--> **** GetRoot rv"<<rv<<" Root"<<(*aRoot)<<" ****")
		return rv;
	}

	nsresult JRexPreference::GetPrefType(const char *aPrefName, PRInt32 *_retval){
		JREX_LOGLN("GetPrefType()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetPrefType()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetPrefType(aPrefName,_retval);
		JREX_LOGLN("GetPrefType()--> **** GetPrefType rv"<<rv<<" PrefType"<<(*_retval)<<" ****")
		return rv;
	}

	nsresult JRexPreference::GetBoolPref(const char *aPrefName, PRBool *_retval){
		JREX_LOGLN("GetBoolPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetBoolPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetBoolPref(aPrefName,_retval);
		JREX_LOGLN("GetBoolPref()--> **** GetBoolPref rv"<<rv<<" BoolPref"<<(_retval)<<" ****")
		return rv;
	}

	nsresult JRexPreference::SetBoolPref(const char *aPrefName, PRInt32 aValue){
		JREX_LOGLN("SetBoolPref()--> **** aPrefName "<<aPrefName<<" aValue "<<aValue<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetBoolPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetBoolPref(aPrefName,aValue);
		JREX_LOGLN("SetBoolPref()--> **** SetBoolPref rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::GetCharPref(const char *aPrefName, char **_retval){
		JREX_LOGLN("GetCharPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetCharPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetCharPref(aPrefName,_retval);
		JREX_LOGLN("GetCharPref()--> **** GetCharPref rv"<<rv<<" CharPref"<<(*_retval)<<" ****")
		return rv;
	}

	nsresult JRexPreference::SetCharPref(const char *aPrefName, const char *aValue){
		JREX_LOGLN("SetCharPref()--> **** aPrefName "<<aPrefName<<" aValue "<<aValue<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetCharPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetCharPref(aPrefName,aValue);
		JREX_LOGLN("SetCharPref()--> **** SetCharPref rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::GetIntPref(const char *aPrefName, PRInt32 *_retval){
		JREX_LOGLN("GetIntPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetIntPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetBoolPref(aPrefName,_retval);
		JREX_LOGLN("GetIntPref()--> **** GetIntPref rv"<<rv<<" IntPref"<<(_retval)<<" ****")
		return rv;
	}

	nsresult JRexPreference::SetIntPref(const char *aPrefName, PRInt32 aValue){
		JREX_LOGLN("SetIntPref()--> **** aPrefName "<<aPrefName<<" aValue "<<aValue<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetIntPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetIntPref(aPrefName,aValue);
		JREX_LOGLN("SetIntPref()--> **** SetIntPref rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::ClearUserPref(const char *aPrefName){
		JREX_LOGLN("ClearUserPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("ClearUserPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->ClearUserPref(aPrefName);
		JREX_LOGLN("ClearUserPref()--> **** ClearUserPref rv"<<rv<<"****")
		return rv;
	}

	nsresult JRexPreference::IsPrefLocked(const char *aPrefName, PRBool *_retval){
		JREX_LOGLN("IsPrefLocked()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("IsPrefLocked()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->PrefIsLocked(aPrefName,_retval);
		JREX_LOGLN("IsPrefLocked()--> **** PrefIsLocked rv"<<rv<<"IsPrefLocked"<<(_retval)<<"****")
		return rv;
	}

	nsresult JRexPreference::LockPref(const char *aPrefName){
		JREX_LOGLN("LockPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("LockPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->LockPref(aPrefName);
		JREX_LOGLN("LockPref()--> **** LockPref rv"<<rv<<"****")
		return rv;

	}

	nsresult JRexPreference::UnlockPref(const char *aPrefName){
		JREX_LOGLN("UnlockPref()--> **** aPrefName "<<aPrefName<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("UnlockPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->UnlockPref(aPrefName);
		JREX_LOGLN("UnlockPref()--> **** UnlockPref rv"<<rv<<"****")
		return rv;

	}

	/*nsresult JRexPreference::PrefHasUserValue(const char *pref, PRBool *_retval){
		JREX_LOGLN("PrefHasUserValue()--> **** pref "<<pref<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("PrefHasUserValue()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->PrefHasUserValue(pref,_retval);
		JREX_LOGLN("PrefHasUserValue()--> **** PrefHasUserValue rv"<<rv<<" HasUserValue"<<(_retval)<<"****")
		return rv;
	}*/

	nsresult JRexPreference::GetDefaultBoolPref(const char *pref, PRBool *_retval){
		JREX_LOGLN("GetDefaultBoolPref()--> **** pref "<<pref<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetDefaultBoolPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetDefaultBoolPref(pref,_retval);
		JREX_LOGLN("GetDefaultBoolPref()--> **** GetDefaultBoolPref rv"<<rv<<" DefaultBoolPref"<<(_retval)<<" ****")
		return rv;

	}

	nsresult JRexPreference::GetDefaultIntPref(const char *pref, PRInt32 *_retval){
		JREX_LOGLN("GetDefaultIntPref()--> **** pref "<<pref<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetDefaultIntPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->GetDefaultIntPref(pref,_retval);
		JREX_LOGLN("GetDefaultIntPref()--> **** GetDefaultIntPref rv"<<rv<<" DefaultIntPref"<<(_retval)<<" ****")
		return rv;

	}

	nsresult JRexPreference::GetDefaultCharPref(const char *pref, char **_retval){
		JREX_LOGLN("GetDefaultCharPref()--> **** pref "<<pref<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetDefaultCharPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->CopyDefaultCharPref(pref,_retval);
		JREX_LOGLN("GetDefaultCharPref()--> **** CopyDefaultCharPref rv"<<rv<<" DefaultCharPref"<<(*_retval)<<" ****")
		return rv;

	}

	nsresult JRexPreference::SetDefaultBoolPref(const char *pref, PRBool value){
		JREX_LOGLN("SetDefaultBoolPref()--> **** pref "<<pref<<" value "<<value<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetDefaultBoolPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetDefaultBoolPref(pref,value);
		JREX_LOGLN("SetDefaultBoolPref()--> **** SetDefaultBoolPref rv"<<rv<<" ****")
		return rv;
	}

	nsresult JRexPreference::SetDefaultIntPref(const char *pref, PRInt32 value){
		JREX_LOGLN("SetDefaultIntPref()--> **** pref "<<pref<<" value "<<value<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetDefaultIntPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetDefaultIntPref(pref,value);
		JREX_LOGLN("SetDefaultIntPref()--> **** SetDefaultIntPref rv"<<rv<<" ****")
		return rv;

	}

	nsresult JRexPreference::SetDefaultCharPref(const char *pref, const char *value){
		JREX_LOGLN("SetDefaultCharPref()--> **** pref "<<pref<<" value "<<value<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("SetDefaultCharPref()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->SetDefaultCharPref(pref,value);
		JREX_LOGLN("SetDefaultCharPref()--> **** SetDefaultCharPref rv"<<rv<<" ****")
		return rv;

	}

	static void DoPrefEnumeration(const char *child, void *data){
		JREX_LOGLN("DoPrefEnumeration()--> **** child "<<child<<"****")
		nsVoidArray* childArray = NS_REINTERPRET_CAST(nsVoidArray*, data);
		nsEmbedCString embedChild(child);
		nsresult rv=childArray->AppendElement(ToNewCString(embedChild));
		JREX_LOGLN("DoPrefEnumeration()--> **** AppendElement rv "<<rv<<"****")
	}

	nsresult JRexPreference::GetPrefChildren(const char *parentPref, nsVoidArray* childArray){
		JREX_LOGLN("GetPrefChildren()--> **** parentPref "<<(PRInt32)parentPref<<"****")
		nsresult rv;
		nsCOMPtr<nsIPref> prefs(do_GetService(kPrefServiceCID,&rv));
		JREX_LOGLN("GetPrefChildren()--> **** do_GetService rv "<<rv<<"****")
		if(NS_SUCCEEDED(rv))
			rv=prefs->EnumerateChildren(parentPref,DoPrefEnumeration,childArray);
		JREX_LOGLN("GetPrefChildren()--> **** EnumerateChildren rv"<<rv<<" ****")
		return rv;
	}

