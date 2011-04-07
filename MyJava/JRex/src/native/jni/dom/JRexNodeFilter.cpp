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

#include "JRexNodeFilter.h"
using namespace JREX_JNI_UTIL;

NS_IMPL_THREADSAFE_ISUPPORTS1(JRexNodeFilter, nsIDOMNodeFilter)

JRexNodeFilter::JRexNodeFilter(jobject jnodeFilter){
    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("JRexNodeFilter()--> **** env<"<<env<<"> ****")
    if(env && jnodeFilter)
		mjnodeFilter=jnodeFilter;//Note:- jnodeFilter object is assumed to be NewGlobalRefed
	else{
		JREX_LOGLN("JRexNodeFilter()--> **** CREATION FAILED!!!!!!!!!****")
		throw NS_ERROR_NULL_POINTER;
	}
	JREX_LOGLN("JRexNodeFilter()--> **** mjnodeFilter<"<<mjnodeFilter<<"> ****")
}

JRexNodeFilter::~JRexNodeFilter(){
	JNIEnv *env = JRex_GetEnv(0);
    JREX_LOGLN("~JRexNodeFilter()--> **** env<"<<env<<"> ****")
    if(env && mjnodeFilter){
		JREX_LOGLN("~JRexNodeFilter()--> **** deleting global ref ****")
		env->DeleteGlobalRef(mjnodeFilter);
	}
	JREX_LOGLN("~JRexNodeFilter()--> **** Done ****")
}

jobject JRexNodeFilter::GetJFilter(){
    JREX_LOGLN("GetJFilter()--> Called Me ****")
    return mjnodeFilter;
}

NS_IMETHODIMP JRexNodeFilter::AcceptNode(nsIDOMNode *node, PRInt16 *_retval){
	if(!JRexDOMGlobals::sIntialized)return NS_OK;
	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("AcceptNode()--> **** env<"<<env<<"> ****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	jobject jevtObj=JRexDOMGlobals::CreateNodeByType(env, node);
	JREX_LOGLN("AcceptNode()--> **** jevtObj<"<<jevtObj<<"> ****")
	if(jevtObj){
		jshort acpt=env->CallShortMethod(mjnodeFilter,JRexDOMGlobals::nodeFilterAcptMID,jevtObj);
		JNI_IF_EXP_DESC_CLR_RET("CallVoidMethod()--> **** acceptNode() Failed with Exception ****",NS_ERROR_FAILURE)
	    *_retval=(PRInt16)acpt;
	}
    JREX_LOGLN("AcceptNode()--> **** FIRED EVENT ****")
    return NS_OK;
}
