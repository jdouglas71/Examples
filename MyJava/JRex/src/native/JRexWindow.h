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
 * in which  the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef JRexWindow_h_
	#define JRexWindow_h_
	#include "JRexIncludes.h"
	#include "JRexWindowCreator.h"

	#define WINDOW_NOT_VALID	(mBrowCreated==PR_FALSE || mBeingDisposed==PR_TRUE)

	class JRexWindowCreator;

	class JRexWindow :	public nsIWebBrowserChrome,
						public nsIWebBrowserChromeFocus,
						public nsIWebProgressListener,
						public nsIEmbeddingSiteWindow2,
						public nsITooltipListener,
						public nsIContextMenuListener2,
						public nsISHistoryListener,
						public nsIDOMKeyListener,
						public nsIDOMMouseListener,
						public nsIDOMMouseMotionListener,
						public nsIURIContentListener,
						public nsSupportsWeakReference,
						public nsIInterfaceRequestor
		{
			public:
				JRexWindow(nsNativeWidget mainWnd, nsDataHashtable<nsUint32HashKey, PRUint32> *browserSetupFlags);
				virtual ~JRexWindow();
				nsresult Show(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height);
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
				nsresult GotVisual(nsNativeWidget);
#endif
				nsresult SetBounds(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height);
				nsresult GetBounds(PRInt32 *, PRInt32 *, PRInt32 *,PRInt32 *);
				nsresult Dispose();
				nsresult SetVisible(PRBool);
				nsresult IsVisible(PRBool*);
				nsresult SetEnabled(PRBool);
				nsresult IsEnabled(PRBool*);
				nsresult GetBaseTitle(PRUnichar * *aTitle);
				nsresult SetBaseTitle(const PRUnichar * aTitle);
				nsresult Repaint(PRBool);
				nsresult GetSelection(nsISelection * *selection);

				nsresult ChangeFocus(PRBool focusGained);
				nsresult GrabFocus();
				nsresult MoveFocus(PRBool forward);
				nsresult GetFocusedElement(nsIDOMElement** aResult);
				nsresult SetFocusedElement(nsIDOMElement* aElement);

				nsresult CanUndo(PRBool *_retval);
				nsresult CanRedo(PRBool *_retval);
				nsresult CanCut(PRBool *_retval);
				nsresult CanCopy(PRBool *_retval);
				nsresult CanCopyLinkLocation(PRBool *_retval);
				nsresult CanCopyImageLocation(PRBool *_retval);
				nsresult CanCopyImageContents(PRBool *_retval);
				nsresult CanPaste(PRBool *_retval);
				nsresult CanDelete(PRBool *_retval);

				nsresult Undo();
				nsresult Redo();
				nsresult Cut();
				nsresult Copy();
				nsresult CopyLinkLocation();
				nsresult CopyImageLocation();
				nsresult CopyImageContents();
				nsresult Paste();
				nsresult SelectAll();
				nsresult SelectNone();
				nsresult Delete();

				nsresult Print(PRBool prompt,PRBool showProgress);
				nsresult PrintPreview(PRBool shrinkToFit, PRBool isLandScape);
				nsresult PageSetup();
				nsresult CancelPrint();
				nsresult CancelPrintPreview();
				nsresult GetPrintPreviewNumPages(PRInt32 *aPrintPreviewNumPages);
				nsresult PrintPreviewNavigate(PRInt16 aNavType, PRInt32 aPageNum);
				nsresult IsPrinting(PRBool*);
				nsresult IsPrintPreviewing(PRBool*);

				nsresult GetPersistFlags(PRUint32 *aPersistFlags);
				nsresult SetPersistFlags(PRUint32 aPersistFlags);
				nsresult GetCurrentState(PRUint32 *aCurrentState);
				nsresult GetResult(PRUint32 *aResult);
				nsresult SaveURI(PRUnichar* uri, PRUnichar* referrer, nsIInputStream *postData, PRUnichar* aExtraHeaders, PRUnichar* saveFile, PRBool addProgListn);
				nsresult SaveDocument(PRUnichar* saveFile, PRUnichar* dataFile, PRUnichar* aOutputContentType, PRUint32 aEncodingFlags, PRUint32 aWrapColumn, PRBool addProgListn);
				nsresult CancelSave();

				nsresult Find(const PRUnichar *searchString, PRBool aFindBackwards, PRBool aWrapFind, PRBool aEntireWord, PRBool aMatchCase, PRBool aSearchFrames, PRBool *isFound);
				nsresult FindNext(PRBool *isFound);
				nsresult GetFindConfig(PRUnichar* *searchString, PRBool *aFindBackwards, PRBool *aWrapFind, PRBool *aEntireWord, PRBool *aMatchCase, PRBool *aSearchFrames);

				nsresult AddProgressListener();
				nsresult AddContextMenuListener();
				nsresult AddHistoryListener();
				nsresult RemoveProgressListener();
				nsresult RemoveContextMenuListener();
				nsresult RemoveHistoryListener();

				nsresult AddKeyListener();
			    nsresult AddMouseListener();
				nsresult AddMouseMotionListener();
				nsresult RemoveKeyListener();
				nsresult RemoveMouseListener();
				nsresult RemoveMouseMotionListener();
				nsresult AddURIContentListener();
				nsresult RemoveURIContentListener();
				nsresult GetDocShell(nsIDocShell **_result);
				nsresult GetRootDocShell(nsIDocShell **_result);
				nsresult GetIsLoadingDocument(PRBool *);

				//static nsresult ExecInEventQ(JRexWindow *window, PRUint16 eventType,
				//						void* eventData, PRBool isSync, PLHandleEventProc handler,
				//							PLDestroyEventProc destructor, void** _result);
				static PRBool IsWindowAvailable(JRexWindow*);
				static JRexWindow* GetJRexWindow(nsIWebBrowserChrome *chrome);
				static void SayGoodBye();

				enum OpenWindowType{TYPE_PAGE_INFO=0,TYPE_SEC_INFO};

				//navigation function wrappers
				struct HistoryEntry{
					HistoryEntry() : uri(nsnull), title(nsnull), isSubFrame(PR_FALSE){}
					PRUnichar* uri;
					PRUnichar* title;
					PRBool isSubFrame;
				};

				NS_IMETHOD GetCanGoBack(PRBool *aCanGoBack);
				NS_IMETHOD GetCanGoForward(PRBool *aCanGoForward);
				NS_IMETHOD GoBack(void);
				NS_IMETHOD GoForward(void);
				NS_IMETHOD GotoIndex(PRInt32 index);
				NS_IMETHOD LoadURI(PRUnichar* uri, PRUint32 loadFlags, PRUnichar* referrer, nsIInputStream *postData, nsIInputStream *headers);
				nsresult   LoadStream(nsIInputStream *inStream, PRUnichar* uri, PRUnichar* contType, PRUnichar* charset,
								PRUint32 loadFlags, PRUnichar* referrer, nsISupports* owner,PRBool inhherit,
									PRUnichar* target, nsIInputStream *postStream, nsIInputStream *headerStream);
				NS_IMETHOD OpenWindow(PRUint16 type, const char* uri, const char* referrer, const char* windowName, const char* feature);
				NS_IMETHOD Reload(PRUint32 reloadFlags);
				NS_IMETHOD GoToAnchor(PRUnichar* anchorName, PRBool shouldScroll);
				nsresult   GetContentString(PRUnichar** retContent, PRUnichar* contType, PRUint32 outFlag);
				NS_IMETHOD Stop(PRUint32 stopFlags);
				NS_IMETHOD GetDocument(nsIDOMDocument * *aDocument);
				NS_IMETHOD GetCurrentURI(nsIURI * *aCurrentURI);
				NS_IMETHOD GetReferringURI(nsIURI * *aReferringURI);
				NS_IMETHOD GetSessionHistory(nsVoidArray* hisArray, PRInt32* maxLength);
				NS_IMETHOD SetSessionHistory(nsISHistory* aSessionHistory);

				NS_DECL_ISUPPORTS
				NS_DECL_NSIINTERFACEREQUESTOR
				NS_DECL_NSIWEBBROWSERCHROME
				NS_DECL_NSIWEBBROWSERCHROMEFOCUS
				NS_DECL_NSIWEBPROGRESSLISTENER
				NS_DECL_NSIEMBEDDINGSITEWINDOW
				NS_DECL_NSIEMBEDDINGSITEWINDOW2
				NS_DECL_NSITOOLTIPLISTENER
				NS_DECL_NSICONTEXTMENULISTENER2
				NS_DECL_NSISHISTORYLISTENER
				NS_DECL_NSIURICONTENTLISTENER

				// nsIDOMEventListener
				NS_IMETHOD HandleEvent(nsIDOMEvent* aEvent);
				// nsIDOMKeyListener
				NS_IMETHOD KeyDown(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD KeyUp(nsIDOMEvent* aDOMEvent);
//x11 KeyPress macro causes compilation problem with nsIDOMKeyListener function KeyPress.
#define MyKeyPress KeyPress
#undef KeyPress
				NS_IMETHOD KeyPress(nsIDOMEvent* aDOMEvent);
#define KeyPress MyKeyPress
#undef MyKeyPress
				// nsIDOMMouseListener
				NS_IMETHOD MouseDown(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD MouseUp(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD MouseClick(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD MouseDblClick(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD MouseOver(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD MouseOut(nsIDOMEvent* aDOMEvent);
				// nsIDOMMouseMotionListener
				NS_IMETHOD MouseMove(nsIDOMEvent* aDOMEvent);
				NS_IMETHOD DragMove(nsIDOMEvent* aDOMEvent);


				nsresult IsCommandSupported(const char *aCommand, PRBool *retval);
				nsresult IsCommandEnabled(const char *aCommand, PRBool *retval);
				nsresult DoCommand(const char *aCommand, nsICommandParams *aCommandParams);
				nsresult ObserverCommand(const char *aCommandToObserve);
				nsresult UnObserverCommand(const char *aCommandObserved);

			private:
				//key event maks, see Event.java
				enum{SHIFT_MASK	= 1U << 0};
				enum{CTRL_MASK	= 1U << 1};
				enum{META_MASK	= 1U << 2};
				enum{ALT_MASK	= 1U << 3};

				enum KeyMode{	KEY_TYPED=400,KEY_PRESSED,KEY_RELEASED};

				enum MouseMode{	MOUSE_CLICKED=500,MOUSE_PRESSED,MOUSE_RELEASED,
								MOUSE_MOVED_OVER,MOUSE_ENTERED,MOUSE_EXITED,
								MOUSE_DRAGGED,MOUSE_WHEEL};

				//Basic event types
				enum BasicEventTypes{	JREX_CREATE=0U,
										JREX_SHOW,
										JREX_DISPOSE,
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
										JREX_GOT_VISUAL,
										JREX_CREATE_GTK,
#endif
										JREX_GET_BOUNDS,
										JREX_SET_BOUNDS,
										JREX_IS_VISIBLE,
										JREX_SET_VISIBLE,
										JREX_IS_ENABLED,
										JREX_SET_ENABLED,
										JREX_REPAINT,
										JREX_CHANGE_FOCUS,
										JREX_GRAB_FOCUS,
										JREX_MOVE_FOCUS,
										JREX_GET_FOCUSED_ELE,
										JREX_SET_FOCUSED_ELE,
										JREX_SET_TITLE,
										JREX_GET_TITLE,
										JREX_GET_SELECTION,
										JREX_GET_DOC_SHELL,
										JREX_GET_ROOT_DOC_SHELL,
										JREX_GET_IS_DOC_LOADING,
										JREX_DUMMY};

				static void* PR_CALLBACK HandleBasicEvent(PLEvent* aEvent);
				static void PR_CALLBACK  DestroyBasicEvent(PLEvent* aEvent);

				//event types for print
				enum PrintEventTypes{JREX_PRINT=0U,
								JREX_PRINT_PREVIEW,
								JREX_DOING_PRINT,
								JREX_DOING_PREVIEW,
								JREX_CANCEL_PRINT,
								JREX_CANCEL_PREVIEW,
								JREX_PREVIEW_PAGES,
								JREX_NAV_PREVIEW,
								JREX_PAGE_SETUP};

				static void* PR_CALLBACK HandlePrintEvent(PLEvent* aEvent);
				static void PR_CALLBACK  DestroyPrintEvent(PLEvent* aEvent);


				//event types for listener
				enum EventListenerTypes{ADD_KEY_LISTENER=0U,
										ADD_MOUSE_LISTENER,
										ADD_MOUSE_MOTION_LISTENER,
										ADD_HISTORY_LISTENER,
										ADD_CTX_MENU_LISTENER,
										REMOVE_KEY_LISTENER,
										REMOVE_MOUSE_LISTENER,
										REMOVE_MOUSE_MOTION_LISTENER,
										REMOVE_HISTORY_LISTENER,
										REMOVE_CTX_MENU_LISTENER};

				static void* PR_CALLBACK HandleListenerEvent(PLEvent* aEvent);
				static void PR_CALLBACK DestroyListenerEvent(PLEvent* aEvent);


				//event types for navigation
				enum NavigationEventTypes{	LOAD=0U,
											LOAD_STREAM,
											CAN_BACK,
											CAN_FORWARD,
											GO_BACK,
											GO_FORWARD,
											GO_TO_INDEX,
											RELOAD,
											STOP,
											GET_CUR_URI,
											GET_REF_URI,
											GET_DOC,
											GET_SESSION,
											SET_SESSION,
											OPEN_WINDOW,
											GO_TO_ANCHOR,
											GET_CONTENT_STRING};

				struct LoadURIEventData{
					LoadURIEventData() : uri(nsnull), loadFlags(0), referrer(nsnull), postData(nsnull), headers(nsnull) {}
					PRUnichar* uri;
					PRUint32 loadFlags;
					PRUnichar* referrer;
					nsIInputStream *postData;
					nsIInputStream *headers;
				};

				struct LoadStreamEventData{
					LoadStreamEventData() : inStream(nsnull), uri(nsnull), contType(nsnull), charset(nsnull), loadFlags(0)
											, referrer(nsnull), owner(nsnull), inhherit(PR_FALSE),
											target(nsnull), postStream(nsnull), headerStream(nsnull){}
					nsIInputStream *inStream;
					PRUnichar* uri;
					PRUnichar* contType;
					PRUnichar* charset;
					PRUint32 loadFlags;
					PRUnichar* referrer;
					nsISupports *owner;
					PRBool inhherit;
					PRUnichar* target;
					nsIInputStream *postStream;
					nsIInputStream *headerStream;
				};

				struct OpenWindowEventData{
					OpenWindowEventData() : type(PR_UINT16_MAX), uri(nsnull), referrer(nsnull), windowName(nsnull), feature(nsnull) {}
					PRUint16 type;
					char* uri;
					char* referrer;
					char* windowName;
					char* feature;
				};

				struct GoToAnchorEventData{
					GoToAnchorEventData() : shouldScroll(PR_FALSE), anchorName(nsnull){}
					PRBool shouldScroll;
					PRUnichar* anchorName;
				};

				struct GetContentStringEventData{
					GetContentStringEventData() : contType(nsnull), outFlag(0){}
					PRUnichar *contType;
					PRUint32 outFlag;
				};

				static void* PR_CALLBACK HandleNavigationEvent(PLEvent* aEvent);
				static void PR_CALLBACK  DestroyNavigationEvent(PLEvent* aEvent);


				enum EditEventTypes{	CAN_UNDO=0U,
										CAN_REDO,
										CAN_CUT,
										CAN_COPY,
										CAN_COPY_LINK_LOC,
										CAN_COPY_IMG_LOC,
										CAN_COPY_IMG_CONT,
										CAN_PASTE,CAN_DELETE,
										UNDO,
										REDO,
										CUT,
										COPY,
										COPY_LINK_LOC,
										COPY_IMG_LOC,
										COPY_IMG_CONT,
										PASTE,
										SELECT_ALL,
										SELECT_NONE,
										DELETE_ALL,
										CMD_SUP,
										CMD_ENABLE,
										DO_CMD};

				struct CommandEventData{
					CommandEventData() : cmd(nsnull), cmdParams(nsnull){}
					const char* cmd;
					nsICommandParams *cmdParams;
				};

				static void* PR_CALLBACK HandleEditEvent(PLEvent* aEvent);
				static void PR_CALLBACK  DestroyEditEvent(PLEvent* aEvent);

				//uri content event types for listener
				enum URIContentEventTypes{ADD_URI_CONTENT_LISTENER=0U,
										REMOVE_URI_CONTENT_LISTENER};

				static void* PR_CALLBACK HandleURIListenerEvent(PLEvent* aEvent);
				static void PR_CALLBACK DestroyURIListenerEvent(PLEvent* aEvent);

				//event types for Persist
				enum PersistEventTypes{	GET_PERSIST_FLAGS=0U,
											SET_PERSIST_FLAGS,
											GET_CURRENT_STATE,
											GET_RESULT,
											SAVE_URI,
											SAVE_DOCUMENT,
											CANCEL_SAVE};

				struct SaveURIEventData{
					SaveURIEventData() : uri(nsnull), referrer(nsnull), postData(nsnull),
											headers(nsnull), saveFile(nsnull), addProgListn(PR_FALSE){}
					PRUnichar* uri;
					PRUnichar* referrer;
					nsIInputStream *postData;
					PRUnichar* headers;
					PRUnichar* saveFile;
					PRBool addProgListn;
				};

				struct SaveDocumentEventData{
					SaveDocumentEventData() : saveFile(nsnull), dataFile(nsnull), outputContentType(nsnull),
											encodingFlags(0), wrapColumn(PR_UINT32_MAX), addProgListn(PR_FALSE){}
					PRUnichar* saveFile;
					PRUnichar* dataFile;
					PRUnichar* outputContentType;
					PRUint32 encodingFlags;
					PRUint32 wrapColumn;
					PRBool addProgListn;
				};

				static void* PR_CALLBACK HandlePersistEvent(PLEvent* aEvent);
				static void PR_CALLBACK DestroyPersistEvent(PLEvent* aEvent);

				//event types for Find
				enum FindEventTypes{	JREX_FIND=0U,
											JREX_FIND_NEXT,
											JREX_GET_CONFIG};

				struct FindConfig{
					FindConfig() : searchString(nsnull), findBackwards(PR_FALSE), wrapFind(PR_FALSE),
												entireWord(PR_FALSE), matchCase(PR_FALSE), searchFrames(PR_FALSE){}

					PRUnichar *searchString;
					PRBool findBackwards;
					PRBool wrapFind;
					PRBool entireWord;
					PRBool matchCase;
					PRBool searchFrames;
				};

				static void* PR_CALLBACK HandleFindEvent(PLEvent* aEvent);
				static void PR_CALLBACK DestroyFindEvent(PLEvent* aEvent);

				nsresult GetPIDOMWindow(nsPIDOMWindow **_result);
				nsresult Init();
				static nsresult InternalInit();
				nsresult ShowInternal(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height);
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
				nsresult GotVisualInternal(nsNativeWidget);
#endif
				nsresult DisposeInternal();
				nsresult SetBoundsInternal(PRInt32 x, PRInt32 y, PRInt32 width,PRInt32 height);
				nsresult IsVisibleInternal(PRBool*);
				nsresult GetSelectionInternal(nsISelection * *selection);

				nsresult ChangeFocusInternal(PRBool focusGained);
				nsresult GrabFocusInternal();
				nsresult MoveFocusInternal(PRBool forward);
				nsresult GetFocusedElementInternal(nsIDOMElement** aResult);
				nsresult SetFocusedElementInternal(nsIDOMElement* aElement);

				nsresult PrintInternal(PRBool prompt,PRBool showProgress);
				nsresult PrintPreviewInternal(PRBool shrinkToFit, PRBool isLandScape);
			    nsresult PageSetupInternal();
				nsresult CancelPrintInternal();
				nsresult CancelPrintPreviewInternal();
				nsresult GetPrintPreviewNumPagesInternal(PRInt32 *aPrintPreviewNumPages);
				nsresult PrintPreviewNavigateInternal(PRInt16 aNavType, PRInt32 aPageNum);
				nsresult IsPrintingInternal(PRBool *);
				nsresult IsPrintPreviewingInternal(PRBool *);
				nsresult fireKeyEvent(nsIDOMEvent* aDOMEvent, PRUint16 eventID);
				nsresult fireMouseEvent(nsIDOMEvent* aDOMEvent, PRUint16 eventID, PRUint16 clickCount );

				nsresult GetPersistFlagsInternal(PRUint32 *aPersistFlags);
				nsresult SetPersistFlagsInternal(PRUint32 aPersistFlags);
				nsresult GetCurrentStateInternal(PRUint32 *aCurrentState);
				nsresult GetResultInternal(PRUint32 *aResult);
				nsresult SaveURIInternal(PRUnichar* uri, PRUnichar* referrer, nsIInputStream *postData, PRUnichar* aExtraHeaders, PRUnichar* saveFile, PRBool addProgListn);
				nsresult SaveDocumentInternal(PRUnichar* saveFile, PRUnichar* dataFile, PRUnichar* aOutputContentType, PRUint32 aEncodingFlags, PRUint32 aWrapColumn, PRBool addProgListn);
				nsresult CancelSaveInternal();

				nsresult FindInternal(const PRUnichar *searchString, PRBool aFindBackwards, PRBool aWrapFind, PRBool aEntireWord, PRBool aMatchCase, PRBool aSearchFrames, PRBool *isFound);
				nsresult FindNextInternal(PRBool *isFound);
				nsresult GetFindConfigInternal(PRUnichar* *searchString, PRBool *aFindBackwards, PRBool *aWrapFind, PRBool *aEntireWord, PRBool *aMatchCase, PRBool *aSearchFrames);

				nsresult AddContextMenuListenerInternal();
				nsresult AddHistoryListenerInternal();
				nsresult AddKeyListenerInternal();
				nsresult AddMouseListenerInternal();
				nsresult AddMouseMotionListenerInternal();
				nsresult AddURIContentListenerInternal();
				nsresult RemoveKeyListenerInternal();
				nsresult RemoveMouseListenerInternal();
				nsresult RemoveMouseMotionListenerInternal();
				nsresult RemoveURIContentListenerInternal();
				nsresult RemoveContextMenuListenerInternal();
				nsresult RemoveHistoryListenerInternal();
				nsresult GetDocShellInternal(nsIDocShell **_result);
				nsresult GetRootDocShellInternal(nsIDocShell **_result);
				nsresult GetIsLoadingDocumentInternal(PRBool *);
				nsresult IsCommandSupportedInternal(const char *aCommand, PRBool *retval);
				nsresult IsCommandEnabledInternal(const char *aCommand, PRBool *retval);
				nsresult DoCommandInternal(const char *aCommand, nsICommandParams *aCommandParams);

				nsresult CanUndoInternal(PRBool *_retval);
				nsresult CanRedoInternal(PRBool *_retval);
				nsresult CanCutInternal(PRBool *_retval);
				nsresult CanCopyInternal(PRBool *_retval);
				nsresult CanCopyLinkLocationInternal(PRBool *_retval);
				nsresult CanCopyImageLocationInternal(PRBool *_retval);
				nsresult CanCopyImageContentsInternal(PRBool *_retval);
				nsresult CanPasteInternal(PRBool *_retval);
				nsresult CanDeleteInternal(PRBool *_retval);
				nsresult UndoInternal();
				nsresult RedoInternal();
				nsresult CutInternal();
				nsresult CopyInternal();
				nsresult CopyLinkLocationInternal();
				nsresult CopyImageLocationInternal();
				nsresult CopyImageContentsInternal();
				nsresult PasteInternal();
				nsresult SelectAllInternal();
				nsresult SelectNoneInternal();
				nsresult DeleteInternal();

				nsresult GetSessionHistoryInternal(nsVoidArray* hisArray, PRInt32* maxLength);
				nsresult LoadURIInternal(PRUnichar* uri, PRUint32 loadFlags, PRUnichar* referrer, nsIInputStream *postData, nsIInputStream *headers);
				nsresult LoadStreamInternal(nsIInputStream *inStream, PRUnichar* uri, PRUnichar* contType, PRUnichar* charset,
								PRUint32 loadFlags, PRUnichar* referrer, nsISupports* owner,PRBool inhherit,
									PRUnichar* target, nsIInputStream *postStream, nsIInputStream *headerStream);

				nsresult OpenWindowInternal(PRUint16 type,const char* aUrl, const char* ref, const char* aName, const char* aFeatures, nsIDOMWindow **_retval);
				nsresult GoToAnchorInternal(PRUnichar* anchorName, PRBool shouldScroll);
				nsresult GetContentStringInternal(PRUnichar** retContent, PRUnichar* contType, PRUint32 outFlag);

  			  	static nsVoidArray				*sWindowList;
  			  	static JRexWindowCreator		*sJRexWindowCreator;
				nsNativeWidget					mMainWnd;
#if defined(MOZ_WIDGET_GTK) || defined(MOZ_WIDGET_GTK2)
				PRBool 							mSignaled;
#endif
				//Use a GRIP of type base nsISupports for WebChrome.
				nsCOMPtr<nsISupports>			mChromeGrip;
				nsCOMPtr<nsIWebBrowser>			mWebBrowser;
				nsCOMPtr<nsIBaseWindow>			mBaseWindow;
				nsCOMPtr<nsIWebNavigation>		mWebNavigation;
				nsCOMPtr<nsIDOMEventReceiver> 	mEventReceiver;
				nsCOMPtr<nsICommandManager> 	mCmdManager;

				nsDataHashtable<nsUint32HashKey, PRUint32> *mBrowserSetupFlags;
				PRBool							mBrowCreated;
				PRBool							mIsVisible;
				PRUnichar						*mTitle;

				PRUint32 						mChromeFlag;
				nsresult						mModalStatus;
				PRBool 							mIsModal;
				PRBool 							mInModalLoop;
				PRBool 							mBeingDisposed;

				PRBool 							mProgListenerAdded;
				PRBool 							mContextListenerAdded;
				PRBool 							mHistoryListenerAdded;

				PRBool							mKeyListenerAdded;
				PRBool							mMouseListenerAdded;
				PRBool							mMouseMotionListenerAdded;
				PRBool							mURIContentListenerAdded;
				PRBool 							mPersistProgListenerAdded;
				PRBool 							mChildIsModalLooping;
				PRUint32	 					mParentIntPtr;
				friend class					JRexWindowCreator;
				friend class					JRexSelection;
		};

	#endif//#define JRexWindow_h_
