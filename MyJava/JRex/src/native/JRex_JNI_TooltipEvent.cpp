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

#include "JRex_JNI_TooltipEvent.h"
using namespace JRex_JNI_Event;
using namespace JRex_JNI_TooltipEvent;

	jobject JRex_JNI_TooltipEvent::createJavaObject(JNIEnv *env, TooltipEventParam* param){
		jobject jrv=NULL;
		jstring jtoolTip=NULL;
		if(NOT_NULL(param->toolTip)){
			JREX_LOGLN("createJavaObject()--> **** param->toolTip<"<<param->toolTip<<"> ****")
			jtoolTip=env->NewStringUTF(param->toolTip);
			nsMemory::Free(param->toolTip);
		}
		JREX_LOGLN("createJavaObject()--> **** jtoolTip<"<<jtoolTip<<"> ****")
		jrv= env->NewObject(TooltipEventFields::toolTipEvtCls,TooltipEventFields::cid,
								(jint)param->target, (jint)param->eventType, (jint)param->cX, (jint)param->cY, jtoolTip);
		JNI_IF_EXP_DESC_CLR_RET("createJavaObject()--> **** TooltipEvent New jrv Failed with Exception ****", (jobject)NULL)
		if(jtoolTip)env->DeleteLocalRef(jtoolTip);
		JREX_LOGLN("createJavaObject()--> **** jrv<"<<jrv<<"> ****")
		return jrv;
	}

	nsresult JRex_JNI_TooltipEvent::getNativeData(JNIEnv *env, jobject jobj, TooltipEventParam* hsParam, void** _result){
		return NS_ERROR_NOT_IMPLEMENTED;
	}

	nsresult JRex_JNI_TooltipEvent::fireEvent(TooltipEventParam* hParam, PRBool isSync, void **_result){

		JREX_LOGLN("fireEvent()--> **** hParam <"<<hParam<<"> ****")
		if(isSync)
			NS_ENSURE_ARG_POINTER(_result);
		nsresult rv=NS_OK;

    	JRexJavaEvent* event = new JRexJavaEvent;
		if (event) {
			JREX_LOGLN("fireEvent()--> **** JRexJavaEvent Created ****")
			event->eventType=TOOL_TIP_EVENT;
			event->eventData=hParam;
			void* result=nsnull;
			rv=isSync?postSyncJavaEvent(event,(void **)&result):postJavaEvent(event);
			JREX_LOGLN("fireEvent()--> **** postJavaEvent isSync<"<<isSync<<"> rv<"<<rv<<">****")
			if (NS_SUCCEEDED(rv) && isSync){
				*_result=result;
				JREX_LOGLN("fireEvent()--> **** postSyncJavaEvent _result<"<<*_result<<"****")
			}
		}else
			rv=NS_ERROR_OUT_OF_MEMORY;
		return rv;
	}

