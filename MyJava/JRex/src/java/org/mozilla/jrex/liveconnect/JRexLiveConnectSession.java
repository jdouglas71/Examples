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
 *   Rich Giuli <richard.giuli@sri.com>
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
import org.mozilla.jrex.ui.JRexCanvas;
import netscape.javascript.JSObject;

/**
 * LiveConnect support for JRex. JRexLiveConnectSession provides a LiveConnect
 * bridge between the JREX JVM and javascript.
 *
 * <h3>Usage</h3>
 * <p><b>
 * JRexLiveConnectSession should only be used on a browser loaded with a web page you
 * trust. This is because the web page will have unrestricted access to the JRex JVM.
 * A typical usage of JRexLiveConnectSession is to use it with a custom XUL app or
 * html page that is owned by the application.
 * </b></p>
 * To get LiveConnect support for JRex, be sure to edit JRex.properties and set
 * "jrex.liveconnect" to 1 before compiling. To create an instance of
 * JRexLiveConnectSession, create an instance of the class {@link JRexLiveConnectSessionImpl}.
 * Before you can use JRexLiveConnectSession, first set the JRexCanvas using the
 * method {@link #setBrowser}. Alternatively, you can pass the browser to the
 * constructor for {@link JRexLiveConnectSessionImpl}.
 * <p>
 * The method {@link #invokeStringMethod} is provided as a simple javascript invocation.
 * This method is used for testing. Most often the caller will want to obtain the
 * JSObject using the method {@link #getJSWindow} and evaluate javascript using it.
 * For example, invoking <code>getJSObject().eval("1+1+2")</code> will return a
 * java.lang.Double object with the value 4.
 * </p>
 * <p>
 * Note that JRex defines its own JSObject class. It is important to make sure
 * JRex's JSObject class is loaded instead of the sun plugin's JSObject class.
 * To be sure of this, always put plugin.jar <i>after</i> JRex.jar in the
 * classpath.
 * </p>
 *
 * <h3>Security</h3>
 * <p>
 * By default the JRexCanvas is <i>untrusted</i> and therefore the javascript cannot
 * create or access java objects in the JRex JVM. This is done to safegaurd against
 * a malicious javascript application.
 * </p>
 * <p>
 * The method {@link #grantBrowserAccessToJVM} is used to let JRexLiveConnectSession
 * know that it is ok for the browser to create and access java objects in the JRex JVM.
 * This method must be called before the method {@link #getJSWindow()} is called.
 * This method exists for the case that a browser window is loaded that is not trusted.
 * In this case, all the methods of JRexLiveConnectSession will work expect for
 * {@link #getJSWindow()}. Only call the method {@link #grantBrowserAccessToJVM} if the
 * browser is trusted by your java application.
 * </p>
 *
 * <h3>Testing</h3>
 * See {@link test.liveconnect.JRexLiveConnectSessionUnitTest} for unit tests. This class
 * also serves as an example of using JRexLiveConnectSession.
 *
 * <h3>Tips</h3>
 * <p>
 * Never return a local variable in javascript which refers to a java function.
 * For example:
 * <blockquote><pre>
function testCreateList() {
    var theList = java.lang.Class.forName("java.util.Vector").newInstance();
    return theList;
}
 * </pre></blockquote>
 * In the above example, "theList" could be garbage collected by javascript
 * before a reference is obtained to the java object it points to, which causes
 * the reference to get muched. Instead call:
 * <blockquote><pre>
var theList = null;
function testCreateList() {
    theList = java.lang.Class.forName("java.util.Vector").newInstance();
    return theList;
}
 * </pre></blockquote>
 * </p>
 * <p>
 * Currently JRexLiveConnectSession must be initialized after the browser
 * is completely loaded, and recreated each time the browser is reloaded.
 * See the unit test for an example. This requirement may change in the future
 * if a way can be found to re-initialize the session on each reload.
 * </p>
 *
 * <h3>JDK Compatibility</h3>
 * JRexLiveConnectSession has been tested on Windows and Linux using jdk 1.4.2
 * and jdk 1.5.0. On Windows, it is recommended that jdk 1.5.0 be used if java
 * plugins are going to be run.
 *
 * @see JRexLiveConnectSessionImpl
 * @see test.liveconnect.JRexLiveConnectSessionUnitTest
 */
public interface JRexLiveConnectSession {
    /**
     * Sets the browser and intializes live connect for the browser. This
     * method initializes the JRexLiveConnectSession to only work with the
     * document's primary content nsIDocShell.
     *
     * @param browser the JRexCanvas, which must already be initialized
     * @throws JRexException if an error occurs while initializing live connect
     * @see #setBrowser(JRexCanvas, boolean)
     */
    void setBrowser(JRexCanvas browser) throws JRexException;

    /**
     * Sets the browser and intializes live connect for the browser. This method
     * also lets you speicfy whether or not to use the root doc shell, or
     * the primary content doc shell.
     *
     * @param browser the JRexCanvas, which must already be initialized
     * @param useRootDocShell if <code>true</code>, then the document's root nsIDocShell
     *  is used. If <code>false</code>, then the nsIDocShell for the primary content is used.
     *  If using JRexLiveConnectSession on a XUL window, and you want to invoke javascript
     *  on the XUL top-level window, this argument must be <code>true</code>. Otherwise,
     * if you have an html document, or you only want to use JRexLiveConnectSession on the
     * primary content, set this argument to <code>False</code>. Note that the primary content
     * in a XUL window is the browser or editor tagged with "content-primary".
     * @throws JRexException if an error occurs while initializing live connect
     */
    void setBrowser(JRexCanvas browser, boolean useRootDocShell) throws JRexException;

    /**
     * Makes the LiveConnectSession a 2-way session. Before this method is called,
     * the LiveConnect session is only one-way, meaning that Java can call into
     * javascript using any of the methods defined in this interface except for
     * {@link #getJSWindow}. After this method is invoked, the javascript will be
     * able to create java objects and invoke methods on those objects, and the
     * caller will be able to use the method {@link #getJSWindow} to retrieve the
     * JSObject instance for the javascript window.
     * <p>
     * <b>
     * Only call this method if the web page loaded into the JRexCanvas is trusted.
     * </b>
     * </p>
     *
     * @throws JRexException if an error occurs while granting access to the JRex JVM
     */
    void grantBrowserAccessToJVM() throws JRexException;

    /**
     * Invokes a javascript method which accepts a single string and returns a string.
     * This method is provided as a simple way of invoking a javascript method and
     * is useful for testing the JRexLiveConnectSession code. Note that for
     * more complex javascript evaulations, the method {@link #evalUntrusted} should
     * be used for untrusted javascript, and the JSObject class returned from
     * {@link #getJSWindow} should be used for trusted javascript.
     *
     * @param functionName the name of the javascript function
     * @param arg the argument to pass to the javascript function
     * @return the result from the javascript function call, or null if the call failed
     * @throws JRexException if an error occurs while invoking the javascript
     * @see #getJSWindow
     */
    String invokeStringMethod(String functionName, String arg) throws JRexException;

    /**
     * Evaluates javascript in the browser. This method will evaluate unstrusted javascript
     * and return the string result. If the javascript is trusted, it is better to call
     * {@link #grantBrowserAccessToJVM} followed by {@link #getJSWindow} and invoke the
     * eval method on the JSObject instance. Only use this method if the javascript is not
     * trusted.
     *
     * @param script the javascript to evaluate
     * @return the result of the evaulation as a string
     * @throws JRexException if an error occurs while evaulating
     */
    String evalUntrusted(String script) throws JRexException;

    /**
     * Retrieves a JSObject implementation for the JRexCanvas window. The return
     * JSObject can be used to make function calls and evaluate javascript.
     * This method must be invoked after the document has been fully loaded
     * into the browser. Failure to do so will result in unexpected errors.
     * <p>
     * Note that this method will throw a security violation exception unless the
     * method {@link #grantBrowserAccessToJVM} is invoked before this method.
     * Make sure to invoke {@link #grantBrowserAccessToJVM} before invoking this
     * method.
     * </p>
     *
     * @return a JSObject for invoking and manipulating javascript
     * @throws JRexException if an error prevents the JSObject from being created
     * @throws SecurityException if grantBrowserAccessToJVM has not been called yet
     * @see #grantBrowserAccessToJVM
     */
    JSObject getJSWindow() throws JRexException, SecurityException;

    /**
     * Invokes js garbage collection on the JSContext. grantBrowserAccessToJVM
     * does *not* need to be called before calling this method.
     *
     * @throws JRexException if an error occurs during js garbage collection
     */
    void jsGC() throws JRexException;
}
