 # ##### BEGIN LICENSE BLOCK #####
 # Version: MPL 1.1/GPL 2.0/LGPL 2.1
 #
 # The contents of this file are subject to the Mozilla Public
 # License Version 1.1 (the "License"); you may not use this file
 # except in compliance with the License. You may obtain a copy of
 # the License at http://www.mozilla.org/MPL/
 #
 # Software distributed under the License is distributed on an "AS IS" basis,
 # WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 # for the specific language governing rights and limitations under the
 # License.
 #
 # Contributor(s):
 #   C.N Medappa <jrex_moz@yahoo.com>
 #
 # Alternatively, the contents of this file may be used under the terms of
 # either the GNU General Public License Version 2 or later (the "GPL"), or
 # the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 # in which case the provisions of the GPL or the LGPL are applicable instead
 # of those above. If you wish to allow use of your version of this file only
 # under the terms of either the GPL or the LGPL, and not to allow others to
 # use your version of this file under the terms of the NPL, indicate your
 # decision by deleting the provisions above and replace them with the notice
 # and other provisions required by the GPL or the LGPL. If you do not delete
 # the provisions above, a recipient may use your version of this file under
 # the terms of any one of the NPL, the GPL or the LGPL.
 #
 # ##### END LICENSE BLOCK ##### #

DEPTH		= ../../../..
topsrcdir	= ../../../..
srcdir		= .
VPATH		= .

include $(DEPTH)/config/autoconf.mk

LIBRARY_NAME     = jrex
FORCE_SHARED_LIB = 1
GRE_MODULE	 = 1
PACKAGE_FILE 	 = jrex.pkg

REQUIRES	= xpcom \
		  string \
		  docshell \
		  webshell \
		  appshell \
		  necko \
		  widget \
		  dom \
		  xpconnect \
		  gfx \
		  layout \
		  content \
		  uriloader \
		  webbrwsr \
		  webbrowserpersist \
		  shistory \
		  embed_base \
		  pref \
		  windowwatcher \
		  commandhandler \
		  profile \
		  find \
		  $(NULL)

ifeq ($(JREX_LIVECONNECT),1)
REQUIRES+=	js \
		liveconnect \
		caps\
		$(NULL)
endif # JREX_LIVECONNECT

CPPSRCS		= \
		JRexDirectoryServiceProviderImpl.cpp \
		JRexWindowImpl.cpp \
		JRexWindowCreatorImpl.cpp \
		JRexWebBrowserChromeImpl.cpp \
		JRexEmbeddingSiteWindow2Impl.cpp  \
		JRexInterfaceRequestorImpl.cpp    \
		JRexTooltipListenerImpl.cpp \
		JRexWebBrowserChromeFocusImpl.cpp \
		JRexContextMenuListener2Impl.cpp   \
		JRexSHistoryListenerImpl.cpp \
        	JRexWebProgressListenerImpl.cpp \
		JRexNavigationWrapper.cpp \
		JRexInputEventWrapper.cpp \
		JRexURIContentEventWrapper.cpp \
		JRexPrintEventWrapper.cpp \
		JRexInputStream.cpp \
		JRexEditEventWrapper.cpp \
		JRexObserverImpl.cpp \
		JRexInputEventListener.cpp \
		JRexURIContentEventListener.cpp \
		JRexStreamListener.cpp \
		JRexHeaderVisitorImpl.cpp \
		JRexPreferenceWrapper.cpp \
		JRexPersistWrapper.cpp \
		JRexFindWrapper.cpp \
		$(NULL)
ifeq ($(JREX_DOM),1)
CPPSRCS+=	JRexSelectionWrapper.cpp \
		$(NULL)
endif # JREX_DOM
CPPSRCS+=	JRex_JNI_Util.cpp \
		JRex_JNI_Event.cpp \
		JRex_JNI_WindowEvent.cpp \
		JRex_JNI_HistoryEvent.cpp \
		JRex_JNI_ProgressEvent.cpp \
		JRex_JNI_ContextMenuEvent.cpp \
		JRex_JNI_TooltipEvent.cpp \
		JRex_JNI_ObserverEvent.cpp \
		JRex_JNI_URIContentEvent.cpp \
		jni/org_mozilla_jrex_xpcom_JRexXPCOMImpl.cpp \
		jni/org_mozilla_jrex_ui_JRexCanvas.cpp \
		jni/org_mozilla_jrex_event_JRexEventManager.cpp \
		jni/org_mozilla_jrex_navigation_WebNavigationImpl.cpp \
		jni/org_mozilla_jrex_pref_JRexPreference.cpp \
		jni/org_mozilla_jrex_io_JRexInputStream.cpp \
		$(NULL)
ifeq ($(JREX_DOM),1)
CPPSRCS+=	jni/org_mozilla_jrex_selection_JRexSelectionImpl.cpp \
		$(NULL)
endif # JREX_DOM

ifeq ($(JREX_LIVECONNECT),1)
CPPSRCS+=	JRexLiveConnectSession.cpp \
		JRexJSObject.cpp \
		jni/org_mozilla_jrex_liveconnect_JRexLiveConnectSessionImpl.cpp \
		jni/org_mozilla_jrex_liveconnect_JRexJSObject.cpp \
		$(NULL)
endif # JREX_LIVECONNECT



ifeq ($(JREX_DOM),1)
CPPSRCS+=	jni/dom/JRexDOMGlobals.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexNodeImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexDOMImplementationImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexAttrImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexElementImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexCharacterDataImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexCDATASectionImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexCommentImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexDocumentFragmentImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexDocumentImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexEntityImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexEntityReferenceImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexDocumentTypeImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexNodeListImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexNamedNodeMapImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexNotationImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexProcessingInstructionImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_JRexTextImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_ranges_JRexDOMRangeImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_ranges_JRexDocumentRangeImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexEventTargetImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexDocumentEventImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexEventImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexMouseEventImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexMutationEventImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_events_JRexUIEventImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_views_JRexAbstractViewImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_views_JRexDocumentViewImpl.cpp \
		jni/dom/JRexDOMEventListener.cpp \
		jni/dom/JRexDOMUserDataHandler.cpp \
		jni/dom/JRexNodeFilter.cpp \
		jni/dom/org_mozilla_jrex_dom_traversal_JRexDocumentTraversalImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_traversal_JRexNodeIteratorImpl.cpp \
		jni/dom/org_mozilla_jrex_dom_traversal_JRexTreeWalkerImpl.cpp \
		$(NULL)
ifeq ($(JREX_DOM_HTML2),1)
CPPSRCS+=	jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLInputElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLCollectionImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLOptionsCollectionImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLFormElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLDocumentImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLImageElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLOptGroupElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLOptionElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLSelectElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTextAreaElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLAnchorElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLScriptElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableCaptionElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableColElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableSectionElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableRowElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTableCellElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLObjectElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLAppletElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLBRElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLBaseElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLDListElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLDirectoryElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLDivElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLFieldSetElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLFontElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLFrameSetElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLHeadElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLHeadingElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLHtmlElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLIsIndexElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLLIElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLLabelElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLLegendElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLMapElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLMenuElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLModElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLOListElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLParagraphElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLPreElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLQuoteElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLTitleElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLUListElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLAreaElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLFrameElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLIFrameElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLLinkElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLBaseFontElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLBodyElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLButtonElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLHRElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLMetaElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLParamElementImpl.cpp \
		jni/dom/html2/org_mozilla_jrex_dom_html2_JRexHTMLStyleElementImpl.cpp \
		$(NULL)
endif # JREX_DOM_HTML2
endif # JREX_DOM

EXTRA_DSO_LDOPTS= \
          	$(XPCOM_GLUE_LIBS) \
		$(MOZ_UNICHARUTIL_LIBS) \
		$(NSPR_LIBS) \
		$(MOZ_JS_LIBS) \
		$(MOZ_COMPONENT_LIBS) \
		$(DIST)/lib/$(LIB_PREFIX)xpcombase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)embed_base_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)jsdombase_s.$(LIB_SUFFIX) \
		$(NULL)

ifeq ($(JREX_LIVECONNECT),1)
ifeq ($(OS_ARCH),WINNT)
EXTRA_DSO_LDOPTS+= \
                $(DIST)/lib/$(LIB_PREFIX)jsj$(MOZ_BITS)$(VERSION_NUMBER).$(LIB_SUFFIX) \
                ${NULL}
else
EXTRA_DSO_LDOPTS+= \
                -L$(DIST)/lib -ljsj \
                ${NULL}
endif # Linux
endif # JREX_LIVECONNECT

# We don't use actuall EmbedString anymore(after mozilla 1.7b) but xpcomglue uses it.
ifeq ($(JREX_MOZ1_4),1)
EXTRA_DSO_LDOPTS += \
		$(DIST)/lib/$(LIB_PREFIX)embedstring_s.$(LIB_SUFFIX) \
		$(NULL)
endif # JREX_MOZ1_4

ifeq ($(JREX_DOM),1)
SHARED_LIBRARY_LIBS+= \
		$(DIST)/lib/$(LIB_PREFIX)gkhtmlbase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkhtmldoc_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkhtmlforms_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkhtmlstyle_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkhtmltable_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkxulbase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkbase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconbase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconevents_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconhtmlcon_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconhtmldoc_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconhtmlstyle_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxmlcon_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxmldoc_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxbl_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxuldoc_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconshared_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkview_s.$(LIB_SUFFIX) \
		$(NULL)

ifdef MOZ_XUL
SHARED_LIBRARY_LIBS += \
		$(DIST)/lib/$(LIB_PREFIX)gkxultree_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkxulgrid_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxulcon_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconxultmpl_s.$(LIB_SUFFIX) \
		$(NULL)
endif

ifdef MOZ_MATHML
SHARED_LIBRARY_LIBS += \
                $(DIST)/lib/$(LIB_PREFIX)gkmathmlcon_s.$(LIB_SUFFIX) \
                $(DIST)/lib/$(LIB_PREFIX)gkmathmlbase_s.$(LIB_SUFFIX) \
                $(NULL)
endif

ifdef MOZ_SVG
SHARED_LIBRARY_LIBS += \
                $(DIST)/lib/$(LIB_PREFIX)gksvgbase_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkconsvgdoc_s.$(LIB_SUFFIX) \
		$(DIST)/lib/$(LIB_PREFIX)gkcontentsvg_s.$(LIB_SUFFIX) \
                $(NULL)

ifdef MOZ_SVG_RENDERER_GDIPLUS
SHARED_LIBRARY_LIBS += \
                $(DIST)/lib/$(LIB_PREFIX)gksvgrenderergdiplus_s.$(LIB_SUFFIX) \
                $(NULL)

OS_LIBS += \
	Gdiplus.lib \
	$(NULL)
endif
ifdef MOZ_SVG_RENDERER_LIBART
SHARED_LIBRARY_LIBS += \
                $(DIST)/lib/$(LIB_PREFIX)gksvgrendererlibart_s.$(LIB_SUFFIX) \
                $(NULL)
endif
ifdef MOZ_SVG_RENDERER_CAIRO
SHARED_LIBRARY_LIBS += \
                $(DIST)/lib/$(LIB_PREFIX)gksvgrenderercairo_s.$(LIB_SUFFIX) \
                $(NSNULL)
endif
endif

endif # JREX_DOM

ifeq ($(OS_ARCH),WINNT)
EXTRA_DSO_LDOPTS+= \
		$(JAVA_HOME)/lib/$(LIB_PREFIX)jawt.$(LIB_SUFFIX) \
		$(JAVA_HOME)/lib/$(LIB_PREFIX)jvm.$(LIB_SUFFIX) \
		$(NULL)
	ifeq ($(JREX_DOM),1)
		EXTRA_DSO_LDOPTS+= \
                	$(DIST)/lib/$(LIB_PREFIX)gkgfx.$(LIB_SUFFIX) \
			$(NULL)
	endif # JREX_DOM
else
	ifeq ($(OS_ARCH),Darwin)
		AFTER_JAVA_HOME1=../Libraries
		AFTER_JAVA_HOME2=../Libraries
	else
		AFTER_JAVA_HOME1=jre/lib/i386
		AFTER_JAVA_HOME2=jre/lib/i386/client
	endif # Darwin
EXTRA_DSO_LDOPTS+= \
		-L$(JAVA_HOME)/$(AFTER_JAVA_HOME1) \
		-L$(JAVA_HOME)/$(AFTER_JAVA_HOME2) -ljvm -ljawt \
                $(NULL)
	ifeq ($(JREX_DOM),1)
		EXTRA_DSO_LDOPTS+= \
                	-L$(DIST)/lib -lgkgfx \
                $(NULL)
	endif # JREX_DOM
endif # WINNT

include $(topsrcdir)/config/rules.mk

DEFINES	+= -DXPCOM_GLUE=1 $(JREX_DEBUG)

ifeq ($(JREX_DOM),1)
	INCLUDES := $(INCLUDES) -Ijni/dom
	DEFINES	+= -DJREX_DOM
endif # JREX_DOM

ifeq ($(JREX_DOM_HTML2),1)
	INCLUDES := $(INCLUDES) -Ijni/dom/html2
	DEFINES	+= -DJREX_DOM_HTML2
endif # JREX_DOM_HTML2

ifeq ($(JREX_MOZ1_4),1)
	DEFINES	+= -DJREX_MOZ1_4
endif # JREX_MOZ1_4

ifeq ($(OS_ARCH),WINNT)
ALL_TRASH+= \
	$(wildcard *.ilk) \
	$(NULL)
endif # WINNT

ifeq ($(OS_ARCH),WINNT)
ifndef GNU_CC
INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/win32 $(INCLUDES) -I.
CXXFLAGS +=-GX /Zm256
LDFLAGS +=/FORCE:MULTIPLE
	else
		INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/win32 $(INCLUDES) -I.
		CXXFLAGS +=-fexceptions
endif # !GNU_CC
endif # WINNT

ifeq ($(OS_ARCH),Linux)
ifdef GNU_CC
INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux $(INCLUDES) -I.
CXXFLAGS        +=-fexceptions
ifdef MOZ_ENABLE_GTK
CXXFLAGS        += $(MOZ_GTK_CFLAGS)
CFLAGS          += $(MOZ_GTK_CFLAGS)
EXTRA_DSO_LDOPTS+= $(MOZ_GTK_LDFLAGS)
endif # MOZ_ENABLE_GTK
ifdef MOZ_ENABLE_GTK2
CXXFLAGS        += $(MOZ_GTK2_CFLAGS)
CFLAGS          += $(MOZ_GTK2_CFLAGS)
EXTRA_DSO_LDOPTS+= $(MOZ_GTK2_LIBS)
endif # MOZ_ENABLE_GTK2
endif # GNU_CC
endif # Linux

ifeq ($(OS_ARCH),Darwin)
ifdef GNU_CC
INCLUDES := -I$(JAVA_HOME)/include $(INCLUDES) -I.
CXXFLAGS        +=-flat_namespace -ObjC++ -fexceptions
endif # GNU_CC
endif # Mac
