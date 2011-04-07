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

	static NS_DEFINE_IID(kSoundCID, NS_SOUND_CID);

	nsresult JRexWindow::FindInternal(const PRUnichar *searchString, PRBool findBackwards,
							PRBool wrapFind, PRBool entireWord, PRBool matchCase,
											PRBool searchFrames, PRBool *isFound){
		JREX_LOGLN("FindInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv;
		nsCOMPtr<nsIWebBrowserFind> browserAsFind(do_GetInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"FindInternal()--> **** do_GetInterface nsIWebBrowserFind")

        rv=browserAsFind->SetSearchString(searchString);
        rv|=browserAsFind->SetFindBackwards(findBackwards);
        rv|=browserAsFind->SetWrapFind(wrapFind);
        rv|=browserAsFind->SetEntireWord(entireWord);
        rv|=browserAsFind->SetMatchCase(matchCase);
        rv|=browserAsFind->SetSearchFrames(searchFrames);
        JREX_LOGLN("FindInternal()--> **** SetProps rv<"<<rv<<"> ****")

        PRBool found=PR_FALSE;
        rv = browserAsFind->FindNext(&found);
        JREX_LOGLN("FindInternal()--> **** FindNext rv<"<<rv<<"> found<"<<found<<"> ****")
        if(!found){
			nsCOMPtr<nsISound>  sound;
			rv = nsComponentManager::CreateInstance(kSoundCID,nsnull, NS_GET_IID(nsISound),getter_AddRefs(sound));
			JREX_LOGLN("FindInternal()--> **** CreateInstance soundInterface rv<"<<rv<<"> ****")
			if (NS_SUCCEEDED(rv))
				sound->Beep();
		}
		*isFound=found;
		return rv;
	}

	nsresult JRexWindow::Find(const PRUnichar *searchString, PRBool findBackwards,
							PRBool wrapFind, PRBool entireWord, PRBool matchCase,
											PRBool searchFrames, PRBool *isFound){
		JREX_LOGLN("Find()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID || IS_NULL(searchString))return NS_OK;
		if(IS_EQT)
			return FindInternal(searchString, findBackwards, wrapFind, entireWord,
														matchCase, searchFrames, isFound);
		nsresult rv;
	   	FindConfig* eventData = new FindConfig;
		if (eventData) {
			JREX_LOGLN("Find()--> **** eventData Created ****")
			nsEmbedString tempSrch(searchString);
			eventData->searchString=ToNewUnicode(tempSrch);
			eventData->findBackwards=findBackwards;
			eventData->wrapFind=wrapFind;
			eventData->entireWord=entireWord;
			eventData->matchCase=matchCase;
			eventData->searchFrames=searchFrames;

			PRBool found=PR_FALSE;
			rv=ExecInEventQ(this, JREX_FIND, eventData, PR_TRUE, HandleFindEvent,DestroyFindEvent, (void**)&found);
			JREX_LOGLN("Find()--> **** ExecInEventQ rv<"<<rv<<"> ****")

			if(NS_SUCCEEDED(rv)){
				*isFound=found;
			}else{
				nsMemory::Free(eventData->searchString);
				delete eventData;
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;

		JREX_LOGLN("Find()--> **** isFound <"<<*isFound<<"> ****")
		return rv;
	}

	nsresult JRexWindow::FindNextInternal(PRBool *isFound){
		JREX_LOGLN("FindNextInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv;
		nsCOMPtr<nsIWebBrowserFind> browserAsFind(do_GetInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"FindNextInternal()--> **** do_GetInterface nsIWebBrowserFind")

        PRBool found=PR_FALSE;
        rv = browserAsFind->FindNext(&found);
        JREX_LOGLN("FindNextInternal()--> **** FindNext rv<"<<rv<<"> found<"<<found<<"> ****")
        if(!found){
			nsCOMPtr<nsISound>  sound;
			rv = nsComponentManager::CreateInstance(kSoundCID,nsnull, NS_GET_IID(nsISound),getter_AddRefs(sound));
			JREX_LOGLN("FindNextInternal()--> **** CreateInstance soundInterface rv<"<<rv<<"> ****")
			if (NS_SUCCEEDED(rv))
				sound->Beep();
		}
		*isFound=found;
		return rv;
	}

	nsresult JRexWindow::FindNext(PRBool *isFound){
		JREX_LOGLN("FindNext()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return FindNextInternal(isFound);

		PRBool found=PR_FALSE;
		nsresult rv=ExecInEventQ(this, JREX_FIND_NEXT, nsnull, PR_TRUE, HandleFindEvent,DestroyFindEvent, (void**)&found);
		JREX_LOGLN("FindNext()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv))
			*isFound=found;
		JREX_LOGLN("FindNext()--> **** isFound <"<<*isFound<<"> ****")
		return rv;
	}


	nsresult JRexWindow::GetFindConfigInternal(PRUnichar* *searchString, PRBool *findBackwards,
							PRBool *wrapFind, PRBool *entireWord, PRBool *matchCase,
											PRBool *searchFrames){
		JREX_LOGLN("GetFindConfigInternal()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;

		nsresult rv;
		nsCOMPtr<nsIWebBrowserFind> browserAsFind(do_GetInterface(mWebBrowser,&rv));
		JREX_RETURN_IF_FAILED(rv,"GetFindConfigInternal()--> **** do_GetInterface nsIWebBrowserFind")

        rv=browserAsFind->GetSearchString(searchString);
        rv|=browserAsFind->GetFindBackwards(findBackwards);
        rv|=browserAsFind->GetWrapFind(wrapFind);
        rv|=browserAsFind->GetEntireWord(entireWord);
        rv|=browserAsFind->GetMatchCase(matchCase);
        rv|=browserAsFind->GetSearchFrames(searchFrames);
        JREX_LOGLN("GetFindConfigInternal()--> **** GetProps rv<"<<rv<<"> ****")
		return rv;
	}

	nsresult JRexWindow::GetFindConfig(PRUnichar* *searchString, PRBool *findBackwards,
							PRBool *wrapFind, PRBool *entireWord, PRBool *matchCase,
											PRBool *searchFrames){
		JREX_LOGLN("GetFindConfig()--> **** mBrowCreated<"<<mBrowCreated<<"> ****")
		if(WINDOW_NOT_VALID)return NS_OK;
		if(IS_EQT)
			return GetFindConfigInternal(searchString, findBackwards, wrapFind, entireWord,
														matchCase, searchFrames);
		nsresult rv;
	   	FindConfig* eventData = nsnull;
		rv=ExecInEventQ(this, JREX_GET_CONFIG, eventData, PR_TRUE, HandleFindEvent,DestroyFindEvent, (void**)&eventData);
		JREX_LOGLN("Find()--> **** ExecInEventQ rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv) && eventData){
			*searchString=eventData->searchString;
			*findBackwards=eventData->findBackwards;
			*wrapFind=eventData->wrapFind;
			*entireWord=eventData->entireWord;
			*matchCase=eventData->matchCase;
			*searchFrames=eventData->searchFrames;
			delete eventData;
		}
		return rv;
	}

	void* PR_CALLBACK JRexWindow::HandleFindEvent(PLEvent* aEvent){
		JRexEventRV* rVal=nsnull;
		if(!gXpcomRunning || !(rVal=new JRexEventRV))return nsnull;

		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JRexWindow* window = NS_STATIC_CAST(JRexWindow*, event->target);
		//Assign this so that it can be deleted in proper place.
		event->eRV=rVal;

		rVal->rv=NS_OK;
		JREX_LOGLN("HandleFindEvent()--> **** JRexWindow <"<<window<<"> ****")
		if(JRexWindow::IsWindowAvailable(window)==PR_FALSE)
			return rVal;

		switch(event->eventType){
			case JREX_FIND:
			{
				FindConfig* evtData = NS_REINTERPRET_CAST(FindConfig*, event->eventData);
				PRBool found=PR_FALSE;
				rVal->rv=window->FindInternal(evtData->searchString,evtData->findBackwards,
											evtData->wrapFind,evtData->entireWord,
											evtData->matchCase,evtData->searchFrames,&found);
				JREX_LOGLN("HandleFindEvent()--> **** FindInternal rv<"<<rVal->rv<<"> found<"<<found<<"> ****")
				rVal->rData=(void*)found;
				break;
			}
			case JREX_FIND_NEXT:
			{
				PRBool found=PR_FALSE;
				rVal->rv=window->FindNextInternal(&found);
				JREX_LOGLN("HandleFindEvent()--> **** FindNextInternal rv<"<<rVal->rv<<"> found<"<<found<<"> ****")
				rVal->rData=(void*)found;
				break;
			}
			case JREX_GET_CONFIG:
			{
				FindConfig* evtData = new FindConfig;
				if(evtData){
					JREX_LOGLN("HandleFindEvent()--> **** JREX_GET_CONFIG eventData Created ****")
					rVal->rv=window->GetFindConfigInternal(&evtData->searchString,&evtData->findBackwards,
										&evtData->wrapFind,&evtData->entireWord,
											&evtData->matchCase,&evtData->searchFrames);
					JREX_LOGLN("HandleFindEvent()--> **** GetConfigInternal rv<"<<rVal->rv<<"> ****")

				}
				rVal->rData=evtData;
				break;
			}
			default:
			{
				JREX_LOGLN("HandleFindEvent()--> **** EVENT TYPE<"<<event->eventType<<"> not handled!!! ****")
			}
		}
		JREX_LOGLN("HandleFindEvent()--> **** returning rVal<"<<rVal<<"> ****")
		return rVal;
	}

	void PR_CALLBACK JRexWindow::DestroyFindEvent(PLEvent* aEvent){
		JRexBasicEvent* event = NS_REINTERPRET_CAST(JRexBasicEvent*, aEvent);
		JREX_LOGLN("DestroyFindEvent()--> **** event <"<<event<<"> ****")
		if(event->eventData){
			if(event->eventType==JREX_FIND){
				FindConfig* evtData = NS_REINTERPRET_CAST(FindConfig*, event->eventData);
				nsMemory::Free(evtData->searchString);
				delete evtData;
			}
		}
		if((event->isSync==PR_FALSE) && event->eRV)//Delete eRV of Non-Sync Event Here
			delete event->eRV;
		delete event;
	}
