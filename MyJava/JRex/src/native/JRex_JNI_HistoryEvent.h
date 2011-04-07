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

#ifndef JRex_JNI_HistoryEvent_h_
#define JRex_JNI_HistoryEvent_h_
#include "JRex_JNI_Event.h"


	namespace JRex_JNI_HistoryEvent{

		enum HistoryEventTypes{	HIS_NEW_ENTRY_EVENT=0U,
								HIS_GO_BACK_EVENT,
								HIS_GO_FORWARD_EVENT,
								HIS_RELOAD_EVENT,
								HIS_GO_TO_INDEX_EVENT,
								HIS_PURGE_EVENT};

		class HistoryEventFields{
			public:
				static jclass	 hisEvtCls;
				static jmethodID cid;

				static jclass	 hisIntPrmCls;
				static jmethodID hisIntCID;

				static jmethodID boolValueID;
		};

		struct BasicHistoryEventParam{
			BasicHistoryEventParam() : target(0), hisEventType(0), uri(NULL){}
			PRUint32  target;
			PRUint32  hisEventType;
			char* uri;
		};

		struct IntHistoryEventParam:BasicHistoryEventParam{
			IntHistoryEventParam() : intData(0){}
			PRUint32 intData;
		};

		jobject createJavaObject(JNIEnv *env, BasicHistoryEventParam* param);
                void deleteEventData(PRUint32  hisEventType, BasicHistoryEventParam* param);
		nsresult getNativeData(JNIEnv *env, jobject jobj, BasicHistoryEventParam* bwParam, void** _result);
		nsresult fireEvent(BasicHistoryEventParam* hParam, PRBool isSync, void **_result);
	}

#endif /* JRex_JNI_HistoryEvent_h_ */
