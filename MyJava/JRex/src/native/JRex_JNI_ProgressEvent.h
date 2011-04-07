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

#ifndef JRex_JNI_ProgressEvent_h_
#define JRex_JNI_ProgressEvent_h_
#include "JRex_JNI_Event.h"
#include "JRexHeaderVisitor.h"

	namespace JRex_JNI_ProgressEvent{

		enum ProgressEventTypes{	PROG_STATE_CHANGE=0U,
									PROG_PROGRESS_CHANGE,
									PROG_LOC_CHANGE,
									PROG_STATUS_CHANGE,
									PROG_SECURITY_CHANGE,
									PROG_LINK_STATUS_CHANGE};

		class ProgressEventFields{
			public:
				static jclass	 progEvtCls;
				static jmethodID cid;

				static jclass	 stateChangePrmCls;
				static jmethodID stateChangeCID;

				static jclass	 progressChangePrmCls;
				static jmethodID progressChangeCID;

				static jclass	 statusChangePrmCls;
				static jmethodID statusChangeCID;
		};

		struct BasicProgressEventParam{
			BasicProgressEventParam() : target(0), progEventType(PR_UINT32_MAX), isLoadingDoc(PR_FALSE),
										reqName(NULL), reqStatus(NS_ERROR_FAILURE), isReqPending(PR_FALSE){}
			PRUint32  target;
			PRUint32  progEventType;
			PRBool  isLoadingDoc;
			char* 	reqName;
			nsresult reqStatus;
			PRBool  isReqPending;
		};

		struct StateChangeProgressEventParam : BasicProgressEventParam{
			StateChangeProgressEventParam() : stateFlags(0), status(NS_ERROR_FAILURE), request(nsnull){}
			PRUint32  stateFlags;
			nsresult status;
			nsIRequest *request;
		};

		struct ProgressChangeProgressEventParam : BasicProgressEventParam{
			ProgressChangeProgressEventParam() : curSelfProgress(0), maxSelfProgress(0), curTotalProgress(0), maxTotalProgress(0){}
			PRInt32 curSelfProgress;
			PRInt32 maxSelfProgress;
			PRInt32 curTotalProgress;
			PRInt32 maxTotalProgress;
		};

		struct LocationChangeProgressEventParam : BasicProgressEventParam{
			LocationChangeProgressEventParam() : loc(NULL){}
			char* loc;
		};

		struct StatusChangeProgressEventParam : BasicProgressEventParam{
			StatusChangeProgressEventParam() : statusMessage(NULL), status(NS_ERROR_FAILURE){}
			char* statusMessage;
			nsresult status;
		};

		jobject createJavaObject(JNIEnv *env, BasicProgressEventParam* param);
		void deleteEventData(PRUint32  progEventType, BasicProgressEventParam* param);
		nsresult getNativeData(JNIEnv *env, jobject jobj, BasicProgressEventParam* param, void** _result);
		nsresult fireEvent(BasicProgressEventParam* hParam, PRBool isSync, void **_result);
		void SetCommonParam(BasicProgressEventParam* sParm, nsIWebProgress *aWebProgress, nsIRequest *aRequest);
	}

#endif /* JRex_JNI_ProgressEvent_h_ */
