/* $Id: INativeJSObject.java,v 1.1 2005/03/17 01:17:09 rgiuli Exp $*/
/**************************************************************************
 * Copyright 2002, 2003 SRI International. All rights reserved.
 *
 * The material contained in this file is confidential and proprietary to SRI
 * International and may not be reproduced, published, or disclosed to others
 * without authorization from SRI International.
 *
 * DISCLAIMER OF WARRANTIES
 *
 * SRI International MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE
 * SUITABILITY OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. SRI International SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING
 * OR DISTRIBUTING THIS SOFTWARE
 **************************************************************************/
package org.mozilla.jrex.liveconnect;

import org.mozilla.jrex.exception.JRexException;

/**
 * Interface for calling native JSObject routines from native code. This
 * should not be used anywhere expect from native code. An exception will be
 * thrown if any of these methods are not called on the JRex event thread.
 * <p>
 * Note that this interface must exist in order for native code to be able to
 * call these methods on the JRexJSObject. This interface is not public.
 * </p>
 */
interface INativeJSObject {
    Object JSObjectGetMember(String name) throws JRexException;
    Object JSObjectGetSlot(int index) throws JRexException;
    void JSObjectSetMember(String name, Object value) throws JRexException;
    void JSObjectSetSlot(int index, Object value) throws JRexException;
    void JSObjectRemoveMember(String name) throws JRexException;
    Object JSObjectCall(String methodName, Object args[]) throws JRexException;
    Object JSObjectEval(String s) throws JRexException;
    String JSObjectToString() throws JRexException;
    void JSObjectFinalize() throws JRexException;
    boolean JSObjectEquals(Object obj) throws JRexException;
}
