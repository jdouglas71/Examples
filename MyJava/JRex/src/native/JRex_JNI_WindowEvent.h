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

#ifndef JRex_JNI_WindowEvent_h_
#define JRex_JNI_WindowEvent_h_
#include "JRex_JNI_Event.h"

	namespace JRex_JNI_WindowEvent{

		enum WindowEventTypes{	WIN_CREATE_EVENT=0U,
								WIN_SETMODAL_EVENT,
								WIN_RESIZE_EVENT,
								WIN_DESTROY_EVENT,
								WIN_SET_TITLE_EVENT,
								WIN_CHROME_FLAG_EVENT,
								WIN_REALIZED_EVENT};

		class WindowEventFields{
			public:
				static jclass	 winEvtCls;
				static jmethodID cid;

				static jclass	 winCrtPrmCls;
				static jmethodID winCrtCID;

				static jclass	 winDimPrmCls;
				static jmethodID dimCID;

				static jclass	 winBoolPrmCls;
				static jmethodID boolCID;

				static jclass	 winLongPrmCls;
				static jmethodID longCID;

				static jmethodID intValMID;
		};

		struct BasicWindowEventParam{
			BasicWindowEventParam() : target(0), winEventType(PR_UINT32_MAX){}
			PRUint32  target;
			PRUint32  winEventType;
		};

		struct WindowCreateEventParam:BasicWindowEventParam{
			WindowCreateEventParam() : parentWin(0), chromeFlags(0), contextFlags(0), uri(NULL){}
			PRUint32 parentWin;
			PRUint32 chromeFlags;
			PRUint32 contextFlags;
			char* uri;
		};

		struct WindowSetModalEventParam:BasicWindowEventParam{
			WindowSetModalEventParam() : isModal(PR_FALSE){}
			PRBool	  isModal;
		};

		struct WindowReSizeEventParam:BasicWindowEventParam{
			WindowReSizeEventParam() : xSize(0), ySize(0) {}
			PRUint32  xSize;
			PRUint32  ySize;
		};

		struct WindowTitleEventParam:BasicWindowEventParam{
			WindowTitleEventParam() : title(NULL){}
			char* title;
		};

		struct WindowChromeEventParam:BasicWindowEventParam{
			WindowChromeEventParam() : chromeFlags(0){}
			PRUint32 chromeFlags;
		};


		jobject createJavaObject(JNIEnv *env, BasicWindowEventParam* param);
                 void deleteEventData(PRUint32  winEventType, BasicWindowEventParam* param);
		nsresult getNativeData(JNIEnv *env, jobject jobj, BasicWindowEventParam* bwParam, void** _result);
		nsresult fireEvent(BasicWindowEventParam* wParam, PRBool isSync, void **_result);
	}

#endif /* JRex_JNI_WindowEvent_h_ */
