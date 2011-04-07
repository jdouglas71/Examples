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

#ifndef JRexIncludes_h_
		#define JRexIncludes_h_

		#include<iostream>
		// core Includes
		#include "nscore.h"
		#include "nsCRT.h"
		#include "nsCOMPtr.h"
		//TODO un comment this once String mod in 1.7b is stabilized
		//#include "nsEmbedString.h"
		#include "nsReadableUtils.h"
		#include "nsXPCOMGlue.h"

		//interfaces implementaion includes.
		#include "nsIBaseWindow.h"
		#include "nsIWebBrowser.h"
		#include "nsCWebBrowser.h"
		#include "nsIWebNavigation.h"
		#include "nsIWebBrowserPersist.h"
		#include "nsIWebBrowserFocus.h"
		#include "nsIWebBrowserSetup.h"
		#include "nsIWebBrowserFind.h"
		#include "nsISound.h"
		#include "nsIDocShellTreeItem.h"
		#include "nsIScrollable.h"
		#include "nsITextScroll.h"
		#include "nsIInterfaceRequestor.h"
		#include "nsIInterfaceRequestorUtils.h"

		#include "nsIWebBrowserChrome.h"
		#include "nsIWebBrowserChromeFocus.h"

		#include "nsIEmbeddingSiteWindow.h"
		#include "nsIEmbeddingSiteWindow2.h"
		#include "nsITooltipListener.h"
		#include "nsIContextMenuListener2.h"
		#include "nsWeakReference.h" //not nsIWeakReference for nsSupportsWeakReference

		#include "nsIWebProgressListener.h"
		#include "nsISHistoryListener.h"
		#include "nsIObserver.h"
		#include "nsIWindowCreator2.h"
		#include "nsIDirectoryService.h"
		#include "nsILocalFile.h"
		#include "nsDirectoryServiceDefs.h"
		#include "nsNativeCharsetUtils.h"
		#include "nsIHttpHeaderVisitor.h"

		#include "nsIXULWindow.h"
		#include "nsIAppShellService.h"
		#include "nsAppShellCIDs.h"
		#include "nsWidgetsCID.h"
		#include "nsIPref.h"
		#include "nsVoidArray.h"
		#include "nsIAppShell.h"
		#include "nsIGenericFactory.h"
		#include "nsIComponentRegistrar.h"
		#include "nsIProfile.h"
		#include "nsAppDirectoryServiceDefs.h"
		#include "nsIWindowWatcher.h"
		#include "nsEmbedAPI.h"
		#include "nsIWidget.h"
		#include "nsIJSContextStack.h"
		#include "nsIEventQueueService.h"
		#include "nsIEventQueue.h"
		#include "plevent.h"
		#include "nsIURI.h"
		#include "nsIDOMWindow.h"
		#include "nsIWebProgress.h"
		#include "nsIRequest.h"

		#include "nsIDOMEvent.h"
		#include "nsIDOMKeyEvent.h"
		#include "nsIDOMMouseEvent.h"
		#include "nsIDOMNode.h"
		#include "nsNetUtil.h"
		#include "nsIIOService.h"
		#include "nsNetCID.h"
		#include "nsIInputStream.h"
		#include "nsCURILoader.h"
		#include "nsIDOMDocument.h"
		#include "nsISHistory.h"
		#include "nsIHistoryEntry.h"
		#include "nsISupportsArray.h"
		#include "nsIDOMWindowInternal.h"
		#include "nsIWebBrowserPrint.h"
		#include "nsIPrintSettings.h"
		#include "nsIPrintingPromptService.h"
		#include "nsIDOMKeyListener.h"
		#include "nsIDOMMouseListener.h"
		#include "nsIDOMMouseMotionListener.h"
		#include "nsIURIContentListener.h"
		#include "nsIDOMEventReceiver.h"
		#include "nsPIDOMWindow.h"
		#include "nsIChromeEventHandler.h"
		#include "nsISelection.h"
		//#include "prlock.h"
		//#include "prtime.h"
		#include "prmem.h"
		#include "nsIClipboardCommands.h"
		#include "nsICommandManager.h"
		#include "nsICommandParams.h"
		#include "nsIFocusController.h"
#define id Id
		#include "nsDataHashtable.h"
#undef id
		//#include "nsRect.h"
		#include "nsIScriptGlobalObject.h"
		#include "nsIDocShell.h"
		#include "nsIDocShellLoadInfo.h"
		#include "nsIDocumentEncoder.h"
		//#include "nsIPresContext.h"
		#include "nsIDocShellTreeOwner.h"
		#include "nsIPresShell.h"
		//#include "nsHTMLReflowState.h"
		#include "nsIEventListenerManager.h"
		//DOM Stuff
		#include "nsIDOMNamedNodeMap.h"
		#include "nsIDOMNodeList.h"
		#include "nsIPrivateDOMImplementation.h"
		#include "nsIDOMDOMImplementation.h"
		#include "nsIDOMDocumentType.h"
		#include "nsIDOMDocument.h"
		#include "nsIDOMAttr.h"
		#include "nsIDOMElement.h"
		#include "nsIDOMCharacterData.h"
		#include "nsIDOMEntity.h"
		#include "nsIDOMEntityReference.h"
		#include "nsIDOMCDATASection.h"
		#include "nsIDOMComment.h"
		#include "nsIDOMDocumentFragment.h"
		#include "nsIDOMProcessingInstruction.h"
		#include "nsIDOMText.h"
		#include "nsIDOMNotation.h"
		#include "nsIDOMRange.h"
		#include "nsIDOMDocumentRange.h"
		#include "nsIDOMEventTarget.h"
		#include "nsIDOMDocumentEvent.h"
		#include "nsIDOMAbstractView.h"
		#include "nsIDOMDocumentView.h"
		#include "nsIDOMMutationEvent.h"
		#include "nsIDOMUIEvent.h"
		#include "nsIDOMNodeIterator.h"
		#include "nsIDOMNodeFilter.h"
		#include "nsIDOMDocumentTraversal.h"
		#include "nsIDOMTreeWalker.h"

		//DOM HTML2 includes
		#include "nsIDOMHTMLElement.h"
		#include "nsIDOMHTMLInputElement.h"
		#include "nsIDOMHTMLButtonElement.h"
		#include "nsIDOMHTMLOptionElement.h"
		#include "nsIDOMHTMLParamElement.h"
		#include "nsIDOMHTMLSelectElement.h"
		#include "nsIDOMHTMLTextAreaElement.h"
		#include "nsIDOMHTMLLIElement.h"
		#include "nsIDOMHTMLAnchorElement.h"
		#include "nsIDOMHTMLAppletElement.h"
		#include "nsIDOMHTMLAreaElement.h"
		#include "nsIDOMHTMLBaseElement.h"
		#include "nsIDOMHTMLBaseFontElement.h"
		#include "nsIDOMHTMLBodyElement.h"
		#include "nsIDOMHTMLBRElement.h"
		#include "nsIDOMHTMLCollection.h"
		#include "nsIDOMHTMLDirectoryElement.h"
		#include "nsIDOMHTMLDivElement.h"
		#include "nsIDOMHTMLDListElement.h"
		#include "nsIDOMHTMLDocument.h"
		#include "nsIDOMHTMLFieldSetElement.h"
		#include "nsIDOMHTMLFontElement.h"
		#include "nsIDOMHTMLFormElement.h"
		#include "nsIDOMHTMLFrameElement.h"
		#include "nsIDOMHTMLFrameSetElement.h"
		#include "nsIDOMHTMLHeadElement.h"
		#include "nsIDOMHTMLHeadingElement.h"
		#include "nsIDOMHTMLHRElement.h"
		#include "nsIDOMHTMLHtmlElement.h"
		#include "nsIDOMHTMLIFrameElement.h"
		#include "nsIDOMHTMLImageElement.h"
		#include "nsIDOMHTMLIsIndexElement.h"
		#include "nsIDOMHTMLLabelElement.h"
		#include "nsIDOMHTMLLegendElement.h"
		#include "nsIDOMHTMLLinkElement.h"
		#include "nsIDOMHTMLMapElement.h"
		#include "nsIDOMHTMLMenuElement.h"
		#include "nsIDOMHTMLMetaElement.h"
		#include "nsIDOMHTMLModElement.h"
		#include "nsIDOMHTMLObjectElement.h"
		#include "nsIDOMHTMLOListElement.h"
		#include "nsIDOMHTMLOptGroupElement.h"
		#include "nsIDOMHTMLOptionsCollection.h"
		#include "nsIDOMHTMLParagraphElement.h"
		#include "nsIDOMHTMLPreElement.h"
		#include "nsIDOMHTMLQuoteElement.h"
		#include "nsIDOMHTMLScriptElement.h"
		#include "nsIDOMHTMLStyleElement.h"
		#include "nsIDOMHTMLTableCaptionElem.h"
		#include "nsIDOMHTMLTableCellElement.h"
		#include "nsIDOMHTMLTableColElement.h"
		#include "nsIDOMHTMLTableElement.h"
		#include "nsIDOMHTMLTableRowElement.h"
		#include "nsIDOMHTMLTableSectionElem.h"
		#include "nsIDOMHTMLTitleElement.h"
		#include "nsIDOMHTMLUListElement.h"
		//DOM3 includes
		#include "nsIDOM3Document.h"
		#include "nsIDOM3EventTarget.h"
		#include "nsIDOM3DocumentEvent.h"
		#include "nsIDOM3Node.h"
		#include "nsIDOMDOMConfiguration.h"
		#include "nsIDOMDOMStringList.h"
		#include "nsIVariant.h"
		#include "nsIDOMUserDataHandler.h"

		#include "jawt_md.h"
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
		#include <X11/Shell.h>
		#include <gtk/gtk.h>
		#include <gdk/gdk.h>
		#include <gdk/gdkx.h>
#endif
		//TODO Remove this once String mod in 1.7b is stabilized
		typedef nsAutoString nsEmbedString;
		typedef nsCAutoString nsEmbedCString;


		#define IS_NULL(obj)				!(obj)
		#define NOT_NULL(obj)				(obj)

		#define NS_EM_LITERAL_CSTRING(s)	nsEmbedCString(s, PRUint32(sizeof(s)-1))
		#define NS_EM_LITERAL_STRING(s)     nsEmbedString(s, PRUint32(sizeof(s)-1))

		#define JREX_LOGLN_ERR(s)			std::cout<<s<<std::endl;

		#ifdef JREX_DEBUG
			#define JREX_LOGL(s)			std::cout<<s;
		#else
			#define JREX_LOGL(s)
		#endif

		#ifdef JREX_DEBUG
			#define JREX_LOGLN(s)			std::cout<<s<<std::endl;
		#else
			#define JREX_LOGLN(s)
		#endif

		#define JREX_TRY					try{

		#define JREX_CATCH(env)				}catch(int i){ \
												JNIEnv *myenv=env; \
												if(IS_NULL(myenv)) \
													myenv=JRex_GetEnv(JAWT_VERSION_1_4); \
												if(NOT_NULL(myenv)) \
													ThrowJRexException(myenv, "UNHANDLED C++ EXCEPTION OCCURED!!!",i); \
												else {\
													JREX_LOGLN_ERR("***** UNHANDLED C++ EXCEPTION OCCURED!!! ******") \
												}\
											}catch(...){ \
												JNIEnv *myenv=env; \
												if(IS_NULL(myenv)) \
													myenv=JRex_GetEnv(JAWT_VERSION_1_4); \
												if(NOT_NULL(myenv)) \
													ThrowJRexException(myenv, "UNHANDLED C++ EXCEPTION OCCURED!!!",0); \
												else {\
													JREX_LOGLN_ERR("***** UNHANDLED C++ EXCEPTION OCCURED!!! ******") \
												}\
											}


		#define JREX_RETURN_IF_FAILED(rv,s)	if(NS_FAILED(rv)){ \
												JREX_LOGLN_ERR(#s" Failed!!! ****") \
												return rv; \
											}else{\
												JREX_LOGLN(#s" Done ****") \
											}

		#define JREX_EXP(rv,s)				if(NS_FAILED(rv)){ \
												JREX_LOGLN_ERR(s) \
												throw rv; \
											}


		#define JREX_FAILED_GOTO(rv,s,n)	if(NS_FAILED(rv)){ \
												JREX_LOGLN_ERR(s) \
												goto n; \
											}

		extern nsIEventQueue* 	gEventQ;
		extern nsIAppShell* 	gAppShell;
		extern PRThread* 		gThread;
		extern PRBool			gXpcomRunning;

		#define IS_EQT			(PR_GetCurrentThread()==gThread)

		struct JRexEventRV{
			JRexEventRV () : rv(NS_ERROR_FAILURE), rData(NULL) {}
			nsresult rv;
			void* rData;// This data is not deleted when event is destroyed.
		};

		struct JRexBasicEvent : PLEvent{
			JRexBasicEvent() : target(nsnull), eventType(PR_UINT16_MAX), eventData(nsnull), isSync(PR_FALSE), eRV(nsnull){}
			void* target;
			PRUint16 eventType;
			void* eventData;// will be deleted when event is destroyed.
			PRBool isSync;
			JRexEventRV* eRV;
		};

		inline nsresult ExecInEventQ(void* target, PRUint16 eventType,void* eventData, PRBool isSync,
								PLHandleEventProc handler, PLDestroyEventProc destructor, void** _result){
			JREX_LOGLN("ExecInEventQ()--> **** eventType<"<<eventType<<">  eventData<"<<eventData<<">****")
			if(!gXpcomRunning)return NS_OK;
			if(isSync)
				NS_ENSURE_ARG_POINTER(_result);

			JRexBasicEvent* event = new JRexBasicEvent;
			nsresult rv=NS_OK;
			nsresult crv=NS_ERROR_FAILURE;
			if (event){
				JREX_LOGLN("ExecInEventQ()--> **** gEventQ JRexBasicEvent Created ****")
				event->isSync=isSync;
				rv=gEventQ->InitEvent(NS_REINTERPRET_CAST(PLEvent*, event),
											nsnull,handler,destructor);
				JREX_LOGLN("ExecInEventQ()--> **** gEventQ InitEvent rv<"<<rv<<">  ****")
				if(NS_SUCCEEDED(rv)){
					event->target=target;
					event->eventType=eventType;
					event->eventData=eventData;
					rv = gEventQ->EnterMonitor();
					if(NS_SUCCEEDED(rv)){
						if(isSync){
							JRexEventRV* rVal=nsnull;
							rv = gEventQ->PostSynchronousEvent(NS_REINTERPRET_CAST(PLEvent*, event),(void**)&rVal);
							JREX_LOGLN("ExecInEventQ()--> **** gEventQ  PostSynchronousEvent rv<"<<rv<<"> rVal<"<<rVal<<"> ****")
							if(NS_SUCCEEDED(rv) && rVal){
								crv=rVal->rv;
								*_result=rVal->rData;
								JREX_LOGLN("ExecInEventQ()--> **** gEventQ  crv<"<<crv<<"> _result<"<<*_result<<"> ****")
								delete rVal;
							}
						}else{
							rv = gEventQ->PostEvent(NS_REINTERPRET_CAST(PLEvent*, event));
							JREX_LOGLN("ExecInEventQ()--> **** gEventQ  PostEvent rv<"<<rv<<"> ****")
							crv=rv;
						}
					}
					gEventQ->ExitMonitor();
				}
				if (NS_FAILED(rv)){
					JREX_LOGLN("ExecInEventQ()--> **** POSTING EVENT FAILED rv<"<<rv<<"> ****")
					PR_DELETE(event);
				}
			}else
				crv=NS_ERROR_OUT_OF_MEMORY;
			JREX_LOGLN("ExecInEventQ()--> **** returning crv<"<<crv<<"> ****")
			return crv;
		}

#endif//JRexIncludes_h_
