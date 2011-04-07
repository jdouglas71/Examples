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

#include "JRexInputStream.h"
using namespace JREX_JNI_UTIL;

NS_IMPL_THREADSAFE_ISUPPORTS1(JRexInputStream, nsIInputStream)

JRexInputStream::JRexInputStream(jobject stream):mIsClosed(PR_FALSE){
    JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("JRexInputStream()--> **** env<"<<env<<"> ****")
    if(env && stream)
		mJavaInputStream=env->NewGlobalRef(stream);
	else{
		JREX_LOGLN("JRexInputStream()--> **** CREATION FAILED!!!!!!!!!****")
		throw NS_ERROR_NULL_POINTER;
	}
	JREX_LOGLN("JRexInputStream()--> **** mJavaInputStream<"<<mJavaInputStream<<"> ****")
}

JRexInputStream::~JRexInputStream(){
	JNIEnv *env = JRex_GetEnv(0);
    JREX_LOGLN("~JRexInputStream()--> **** env<"<<env<<"> ****")
    if(env && mJavaInputStream){
		if(!mIsClosed)Close();
		JREX_LOGLN("~JRexInputStream()--> **** deleting global ref ****")
		env->DeleteGlobalRef(mJavaInputStream);
	}
	JREX_LOGLN("~JRexInputStream()--> **** Done ****")
}

NS_IMETHODIMP JRexInputStream::Close(){
	mIsClosed=PR_TRUE;
	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("Close()--> **** env<"<<env<<"> ****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	env->CallVoidMethod(mJavaInputStream,closeMID);
	JNI_IF_EXP_DESC_CLR_RET("Close()--> **** Failed with Exception ****",NS_ERROR_FAILURE)
	JREX_LOGLN("Close()--> DONE ****")
	return NS_OK;
}


NS_IMETHODIMP JRexInputStream::Available(PRUint32 *_retval){
	NS_ENSURE_ARG_POINTER(_retval);
	*_retval=0;
	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("Available()--> **** env<"<<env<<"> ****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	jint available=env->CallIntMethod(mJavaInputStream,availableMID);
	JREX_LOGLN("Available()--> **** available<"<<available<<"> ****")
	JNI_IF_EXP_DESC_CLR_RET("Available()--> **** Failed with Exception ****",NS_ERROR_FAILURE)
	*_retval=available;
    JREX_LOGLN("Available()--> **** *_retval<"<<*_retval<<"> ****")
    return NS_OK;
}


NS_IMETHODIMP JRexInputStream::Read(char *aBuf, PRUint32 aCount, PRUint32 *_retval){
	NS_ENSURE_ARG_POINTER(aBuf);
	NS_ENSURE_ARG_POINTER(_retval);

	*_retval=0;
	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("Read()--> **** env<"<<env<<"> aCount<"<<aCount<<">****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	jboolean isCopy=JNI_FALSE;
	jbyte* memArr=NULL;
	jbyteArray myArray=NULL;
	jint bytesRead=0;

	myArray=env->NewByteArray(aCount);
	bytesRead=env->CallIntMethod(mJavaInputStream,readMID,myArray,0,(jint)aCount);
	JREX_LOGLN("Read()--> **** bytesRead <"<<bytesRead<<"> ****")
	JNI_IF_EXP_DESC_CLR_GT("Read()--> **** CallIntMethod read Failed with Exception ****",clean)

	memArr=env->GetByteArrayElements(myArray,&isCopy);
    memcpy(aBuf,memArr,bytesRead);
	env->ReleaseByteArrayElements(myArray,memArr,JNI_ABORT);
	env->DeleteLocalRef(myArray);
    *_retval=bytesRead<0?0:bytesRead;
    return NS_OK;
   clean:
   JREX_LOGLN("Read()--> **** BRANCHED TO CLEAN ****")
	if(myArray)
		env->DeleteLocalRef(myArray);
   	*_retval=0;
   	return NS_OK;
}


NS_IMETHODIMP JRexInputStream::ReadSegments(nsWriteSegmentFun aWriter, void * aClosure, PRUint32 aCount, PRUint32 *_retval){
	NS_ENSURE_ARG_POINTER(_retval);

	JNIEnv *env = JRex_GetEnv(0);
	JREX_LOGLN("ReadSegments()--> **** env<"<<env<<"> aCount<"<<aCount<<">****")
	if(IS_NULL(env))return NS_ERROR_FAILURE;

	nsresult rv=NS_OK;
	PRUint32 rVal=0;

	PRUint32 avail =(PRUint32)env->CallIntMethod(mJavaInputStream, availableMID);
	JREX_LOGLN("ReadSegments()--> **** available count<"<<avail<<"> ****")
	JNI_IF_EXP_DESC_CLR_RET("ReadSegments()--> **** CallIntMethod available with Exception ****",NS_ERROR_FAILURE)
    if(avail<1){
		*_retval=0;
		return NS_OK;
	}
    PRUint32 count=aCount>avail?avail:aCount;
	JREX_LOGLN("ReadSegments()--> **** actaul count<"<<count<<"> ****")

	char* from = (char*)nsMemory::Alloc(count);
	if(!from){
		JREX_LOGLN("ReadSegments()--> **** Alloc FAILED!!! ****")
		rv= NS_ERROR_OUT_OF_MEMORY;
		goto clean;
	}

	rv=Read(from, count, &rVal);
	JREX_LOGLN("ReadSegments()--> **** rv<"<<rv<<"> rVal<"<<rVal<<"> ****")
	if(NS_FAILED(rv) || rVal<1)goto clean;

	rv = aWriter(this, aClosure, from, 0, rVal, _retval);
	JREX_LOGLN("ReadSegments()--> **** rv<"<<rv<<"> _retval<"<<*_retval<<">****")
	if(NS_FAILED(rv))// errors returned from the writer is not propogated.
		*_retval=0;
	nsMemory::Free(from);
	return NS_OK;
clean:
	JREX_LOGLN("ReadSegments()--> **** BRANCHED TO CLEAN ****")
	if(from)nsMemory::Free(from);
	*_retval=0;
	return rv;
}

NS_IMETHODIMP JRexInputStream::IsNonBlocking(PRBool *_retval){
	*_retval = PR_FALSE;
    return NS_OK;
}
