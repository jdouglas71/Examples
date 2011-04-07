/* -*- Mode: Java; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * ***** BEGIN LICENSE BLOCK *****
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
 *   Original code is from mozilla 1.7RC1
 *   Added JRex changes: Rich Giuli <richard.giuli@sri.com>
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

package org.mozilla.jrex.liveconnect;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
import netscape.javascript.JSObject;
import netscape.javascript.JSException;

import java.util.Map;
import java.util.HashMap;
import java.lang.ref.WeakReference;
import java.lang.ref.Reference;

/**
 * JSObject allows Java to manipulate objects that are
 * defined in JavaScript.
 * Values passed from Java to JavaScript are converted as
 * follows:<ul>
 * <li>JSObject is converted to the original JavaScript object
 * <li>Any other Java object is converted to a JavaScript wrapper,
 *   which can be used to access methods and fields of the java object.
 *   Converting this wrapper to a string will call the toString method
 *   on the original object, converting to a number will call the
 *   doubleValue method if possible and fail otherwise.  Converting
 *   to a boolean will try to call the booleanValue method in the
 *   same way.
 * <li>Java arrays are wrapped with a JavaScript object that understands
 *   array.length and array[index]
 * <li>A Java boolean is converted to a JavaScript boolean
 * <li>Java byte, char, short, int, long, float, and double are converted
 *   to JavaScript numbers
 * </ul>
 * Values passed from JavaScript to Java are converted as follows:<ul>
 * <li>objects which are wrappers around java objects are unwrapped
 * <li>other objects are wrapped with a JSObject
 * <li>strings, numbers and booleans are converted to String, Double,
 *   and Boolean objects respectively
 * </ul>
 * This means that all JavaScript values show up as some kind
 * of java.lang.Object in Java.  In order to make much use of them,
 * you will have to cast them to the appropriate subclass of Object,
 * e.g. <code>(String) window.getMember("name");</code> or
 * <code>(JSObject) window.getMember("document");</code>.
 */
final class JRexJSObject extends JSObject implements INativeJSObject {
	private static final String className	= JRexJSObject.class.getName();

    final static String UNDEFINED="undefined";

    /* the internal object data */
    private int                               internal;
    private int                               jrexLCSession;
    private JRexLiveConnectSessionImpl        lcSession;

    private static Map jrexjsobjects = new HashMap();

    /**
     * it is illegal to construct a JSObject manually
     */
    private JRexJSObject(int jsobj_addr, int jrexLCSession) {
        internal = jsobj_addr;
        this.jrexLCSession = jrexLCSession;
    }

    /**
     * Preserves JRexJSObject identity.
     */
    private static JRexJSObject newJRexJSObject(int jsobj_addr, int jrexLCSession) {
        Integer key = new Integer(jsobj_addr);
        synchronized (jrexjsobjects) {
            Reference ref = (Reference)jrexjsobjects.get(key);
            Object ret = (ref != null ? ref.get() : null);
            if (ret == null) {
                jrexjsobjects.put(key, new WeakReference(ret = new JRexJSObject(jsobj_addr, jrexLCSession)));
            }
            return (JRexJSObject)ret;
        }
    }

    private static final Object checkUndefined(Object obj) {
        if (obj instanceof String && UNDEFINED.equals(obj)) {
            return null;
        }
        return obj;
    }

    /**
     * Retrieves a named member of a JavaScript object.
     * Equivalent to "this.<i>name</i>" in JavaScript.
     */
    public Object getMember(String name) {
        try {
            if (name == null) {
                throw new IllegalArgumentException("jsobject getMember: name cannot be null");
            }
            return checkUndefined(JRexGetMember(name));
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native Object JRexGetMember(String name) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native Object JSObjectGetMember(String name) throws JRexException;

    /**
     * Retrieves an indexed member of a JavaScript object.
     * Equivalent to "this[<i>index</i>]" in JavaScript.
     */
//    public Object		getMember(int index) { return getSlot(index); }
    public Object getSlot(int index) {
        try {
            return checkUndefined(JRexGetSlot(index));
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native Object JRexGetSlot(int index) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native Object JSObjectGetSlot(int index) throws JRexException;

    /**
     * Sets a named member of a JavaScript object.
     * Equivalent to "this.<i>name</i> = <i>value</i>" in JavaScript.
     */
    public void setMember(String name, Object value) {
        try {
            if (name == null) {
                throw new IllegalArgumentException("jsobject setMember: name cannot be null");
            }
            JRexSetMember(name, value);
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native void JRexSetMember(String name, Object value) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native void JSObjectSetMember(String name, Object value) throws JRexException;

    /**
     * Sets an indexed member of a JavaScript object.
     * Equivalent to "this[<i>index</i>] = <i>value</i>" in JavaScript.
     */
//    public void 		setMember(int index, Object value) {
//        setSlot(index, value);
//    }
    public void setSlot(int index, Object value) {
        try {
            JRexSetSlot(index, value);
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native void JRexSetSlot(int index, Object value) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native void JSObjectSetSlot(int index, Object value) throws JRexException;

    /**
     * Removes a named member of a JavaScript object.
     */
    public void removeMember(String name) {
        try {
            if (name == null) {
                throw new IllegalArgumentException("jsobject removeMember: name cannot be null");
            }
            JRexRemoveMember(name);
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native void JRexRemoveMember(String name) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native void JSObjectRemoveMember(String name) throws JRexException;

    /**
     * Calls a JavaScript method.
     * Equivalent to "this.<i>methodName</i>(<i>args</i>[0], <i>args</i>[1], ...)" in JavaScript.
     */
    public Object call(String methodName, Object args[]) {
        try {
            // In mozilla debug, an error occurs if an empty object array is passed.
            // This is due to an malloc of 0 bytes internal to the js code.
            if (args != null && args.length == 0) {
                args = null;
            }
            if (args != null) {
                // a null value will crash liveconnecy
                for (int i = 0; i < args.length; i++) {
                    Object arg = args[i];
                    if (arg == null) {
                        throw new IllegalArgumentException("jsobject call: argument "+i+" cannot be null");
                    }
                }
            }
            return checkUndefined(JRexCall(methodName, args));
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native Object JRexCall(String methodName, Object args[]) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native Object JSObjectCall(String methodName, Object args[]) throws JRexException;

    /**
     * Evaluates a JavaScript expression. The expression is a string
     * of JavaScript source code which will be evaluated in the context
     * given by "this".
     */
    public Object eval(String evalStr) {
        try {
            if (evalStr == null) {
                throw new IllegalArgumentException("jsobject eval: evalStr cannot be null");
            }
            return checkUndefined(JRexEval(evalStr));
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native Object JRexEval(String s) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native Object JSObjectEval(String s) throws JRexException;

    /**
     * Converts a JSObject to a String.
     */
    public String toString() {
        try {
            return JRexToString();
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native String JRexToString() throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native String JSObjectToString() throws JRexException;

    public static JSObject getWindowForSession(JRexLiveConnectSessionImpl lcSession) throws JRexException {
        if (lcSession == null) {
            throw new IllegalArgumentException();
        }
        JRexJSObject ret = GetWindowForSession(lcSession);
        if (ret == null) {
            throw new JRexException("Failed to create an instance of " + JRexJSObject.class.getName());
        }
        ret.jrexLCSession = lcSession.getSessionID();
        // This reference is maintained to ensure that lcSession doesn't garbage collect
        // if there are still JRexJSObjects out there.
        ret.lcSession = lcSession;
        return ret;
    }

    private static native JRexJSObject GetWindowForSession(JRexLiveConnectSessionImpl lcSession) throws JSException;

    protected void finalize(){
        if(JRexL.on)JRexL.log(className,"**** finalize ****");
        try{
            Finalize();
        }catch(JRexException ex){
            JRexL.printStackTrace(ex);
        }
        synchronized (jrexjsobjects) {
            jrexjsobjects.remove(new Integer(internal));
        }
	}

    private native void Finalize() throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native void JSObjectFinalize() throws JRexException;

    /**
     * Override java.lang.Object.equals() because identity is not preserved
     * with instances of JSObject.
     */
    public boolean equals(Object cmpObj) {
        try {
            if (cmpObj == null) {
                throw new IllegalArgumentException("jsobject equals: cmpObj cannot be null");
            }
            return JRexEquals(cmpObj);
        } catch (JRexException e) {
            JSException jsex = new JSException(e.getMessage());
            jsex.initCause(e);
            throw jsex;
        }
    }

    private native boolean JRexEquals(Object obj) throws JRexException;
    // JSObject equivalent, called from native code on the event thread
    public native boolean JSObjectEquals(Object obj) throws JRexException;
}
