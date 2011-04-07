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
	#include "JRex_JNI_ContextMenuEvent.h"
#if defined(JREX_DOM)
	#include "JRexDOMGlobals.h"
#endif
 	using namespace JRex_JNI_ContextMenuEvent;

	NS_IMETHODIMP JRexWindow::OnShowContextMenu(PRUint32 aContextFlags, nsIContextMenuInfo *aUtils)
	{
		JREX_LOGLN("OnShowContextMenu()--> *** aContextFlags <"<<aContextFlags<<">***")

		nsCOMPtr<nsIDOMEvent> domEvent;
		nsresult rv=aUtils->GetMouseEvent(getter_AddRefs(domEvent));
		JREX_LOGLN("OnShowContextMenu()--> *** GetMouseEvent rv<"<<rv<<">***")
		if(NS_FAILED(rv))return rv;

		nsCOMPtr<nsIDOMMouseEvent> mouseEvent(do_QueryInterface(domEvent));
		if(IS_NULL(mouseEvent))return NS_ERROR_NULL_POINTER;

		PRUint16 phase=0;
		mouseEvent->GetEventPhase(&phase);
		JREX_LOGLN("OnShowContextMenu()--> *** GetEventPhase phase<"<<phase<<">***")
		if(phase==nsIDOMEvent::CAPTURING_PHASE)return NS_OK;

		PRInt32 cX=0;
		PRInt32 cY=0;
		mouseEvent->GetClientX(&cX);
		mouseEvent->GetClientY(&cY);
		JREX_LOGLN("OnShowContextMenu()--> *** cX<"<<cX<<"> cY<"<<cY<<"> ***")

		nsCOMPtr<nsIDOMNode> domNode;
		rv=aUtils->GetTargetNode(getter_AddRefs(domNode));
		JREX_LOGLN("OnShowContextMenu()--> *** GetTargetNode rv<"<<rv<<">***")

		jobject jdomNode=NULL;
#if defined(JREX_DOM)
			if(NS_SUCCEEDED(rv) && domNode){
				JREX_LOGLN("OnShowContextMenu()--> *** NOT_NULL domNode ***")
				jdomNode=JRexDOMGlobals::CreateNodeByType(NULL, domNode);
			}
#endif

		PRUint16 nodeType;
		if(NS_SUCCEEDED(rv) && NOT_NULL(domNode))
			domNode->GetNodeType(&nodeType);
		JREX_LOGLN("OnShowContextMenu()--> *** nodeType <"<<nodeType<<">***")

		char* tempUri=nsnull;
		if (aContextFlags & CONTEXT_LINK){
			nsEmbedString link;
			rv=aUtils->GetAssociatedLink(link);
			if(NS_SUCCEEDED(rv))
				tempUri=ToNewUTF8String(link);
			JREX_LOGLN("OnShowContextMenu()--> *** CONTEXT_LINK tempUri<"<<tempUri<<">***")
		}

		char* tempImgUri=nsnull;
		if(aContextFlags & CONTEXT_IMAGE){
			nsCOMPtr<nsIURI> linkUri;
			rv=aUtils->GetImageSrc(getter_AddRefs(linkUri));
			if(NS_SUCCEEDED(rv)){
				nsEmbedCString spec;
				rv=linkUri->GetSpec(spec);
				if(NS_SUCCEEDED(rv))
					tempImgUri=ToNewCString(spec);
			}
			JREX_LOGLN("OnShowContextMenu()--> *** CONTEXT_IMAGE tempImgUri<"<<tempImgUri<<">***")
		}else
		if(aContextFlags & CONTEXT_BACKGROUND_IMAGE){
			nsCOMPtr<nsIURI> linkUri;
			rv=aUtils->GetBackgroundImageSrc(getter_AddRefs(linkUri));
			if(NS_SUCCEEDED(rv)){
				nsEmbedCString spec;
				rv=linkUri->GetSpec(spec);
				if(NS_SUCCEEDED(rv))
					tempImgUri=ToNewCString(spec);
			}
			JREX_LOGLN("OnShowContextMenu()--> *** CONTEXT_BACKGROUND_IMAGE tempImgUri<"<<tempImgUri<<">***")
		}

		ContextMenuEventParam *cParm=new ContextMenuEventParam;
		if(IS_NULL(cParm))return NS_ERROR_OUT_OF_MEMORY;
		cParm->target=NS_PTR_TO_INT32(this);
		cParm->contextFlags=aContextFlags;
		cParm->cX=cX;
		cParm->cY=cY;
		cParm->jdomNode=jdomNode;
		cParm->nodeType=nodeType;
		cParm->uri=tempUri;
		cParm->imgUri=tempImgUri;
		rv=fireEvent(cParm,PR_FALSE, nsnull);
		JREX_LOGLN("OnShowContextMenu()--> *** fireWindowEvent rv<"<<rv<<"> ***")
		if(jdomNode){
			JNIEnv* env=JRex_GetEnv(0);
			env->DeleteLocalRef(jdomNode);
		}
		return NS_OK;
	}

