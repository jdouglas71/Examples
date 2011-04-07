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

#include "JRexDOMUserDataHandler.h"
using namespace JREX_JNI_UTIL;

NS_IMPL_THREADSAFE_ISUPPORTS1(JRexDOMUserDataHandler, nsISupports)

JRexDOMUserDataHandler::JRexDOMUserDataHandler(jobject jdataHandler){
    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("JRexDOMUserDataHandler()--> **** env<"<<env<<"> ****")
    if(env && jdataHandler)
		mJdataHandler=jdataHandler;//Note:- jdataHandler object is assumed to be NewGlobalRefed
	else{
		JREX_LOGLN("JRexDOMUserDataHandler()--> **** CREATION FAILED!!!!!!!!!****")
		throw NS_ERROR_NULL_POINTER;
	}
	JREX_LOGLN("JRexDOMUserDataHandler()--> **** mJdataHandler<"<<mJdataHandler<<"> ****")
}

JRexDOMUserDataHandler::~JRexDOMUserDataHandler(){
	JNIEnv *env = JRex_GetEnv(0);
    JREX_LOGLN("~JRexDOMUserDataHandler()--> **** env<"<<env<<"> ****")
    if(env && mJdataHandler){
		JREX_LOGLN("~JRexDOMUserDataHandler()--> **** deleting global ref ****")
		env->DeleteGlobalRef(mJdataHandler);
	}
	JREX_LOGLN("~JRexDOMUserDataHandler()--> **** Done ****")
}


NS_IMETHODIMP JRexDOMUserDataHandler::Handle(PRUint16 operation,
		const nsAString & key, nsIVariant *data, nsIDOMNode *src, nsIDOMNode *dst){
	if(!JRexDOMGlobals::sIntialized)return NS_OK;
	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("Handle()--> **** env<"<<env<<"> ****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	jstring jkey=NULL;
	NS_STR_TO_JSTR(env,key,jkey)
	jobject jsrcNode=JRexDOMGlobals::CreateNodeByType(env, src,PR_TRUE);
	jobject jdstNode=JRexDOMGlobals::CreateNodeByType(env, dst,PR_TRUE);
	jstring jdata=NULL;
	if(NOT_NULL(data)){
		nsXPIDLString temp;
		nsresult rv=data->GetAsWString(getter_Copies(temp));
		JREX_LOGLN("Handle()--> **** GetAsWString rv<"<<rv<<"> ****")
		if(NS_SUCCEEDED(rv)){
			NS_STR_TO_JSTR(env,temp,jdata)
		}
	}
	JREX_LOGLN("Handle()--> **** jsrcNode<"<<jsrcNode<<"> jdstNode<"<<jdstNode<<"> ****")

	if(jkey){
		env->CallVoidMethod(mJdataHandler, JRexDOMGlobals::usrDataHndlMID,
			(jshort)operation, jkey, jdata, jsrcNode, jdstNode);
		JNI_IF_EXP_DESC_CLR_RET("CallVoidMethod()--> **** Handle() Failed with Exception ****",NS_ERROR_FAILURE)
		env->DeleteLocalRef(jkey);
		if(jdata)env->DeleteLocalRef(jdata);
	}
    JREX_LOGLN("Handle()--> **** FIRED ****")
    return NS_OK;
}
