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

import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
import netscape.javascript.JSObject;

/**
 * Implementation of JRexLiveConnectSession. JRexLiveConnectSessionImpl is
 * public for accesibility from jni.
 *
 * @see JRexLiveConnectSession
 */
public final class JRexLiveConnectSessionImpl implements JRexLiveConnectSession {
	private static final String className	= JRexLiveConnectSessionImpl.class.getName();

    private int sessionID;
    private int jrexPeer;
    private JSObject jsObject = null;
    private static boolean inited = false;
    private boolean valid = false;
    private boolean liveConnectStarted = false;
    private static Object staticSync = new Object();

	static{
		try{
		    if(JRexL.on)JRexL.log(className,"**** initIDs ****");
			initIDs();
			inited=true;
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

    /**
     * Creates an instance of JRexLiveConnectSessionImpl. The method
     * {@link #setBrowser} must be called before any javascript can be invoked.
     */
    public JRexLiveConnectSessionImpl() {
    }

    /**
     * Creates an instance of JRexLiveConnectSessionImpl and invokes setBrowser.
     *
     * @param browser the JRexCanvas used to access javascript
     * @throws JRexException if an error occurs while initializing the javascript
     *  bridge.
     */
    public JRexLiveConnectSessionImpl(JRexCanvas browser) throws JRexException {
        setBrowser(browser);
    }

    /**
     * Creates an instance of JRexLiveConnectSessionImpl and invokes setBrowser.
     *
     * @param browser the JRexCanvas used to access javascript
     * @param useRootDocShell whether or not to use the root doc shell, or the primary content doc shell
     * @throws JRexException if an error occurs while initializing the javascript
     *  bridge.
     */
    public JRexLiveConnectSessionImpl(JRexCanvas browser, boolean useRootDocShell) throws JRexException {
        setBrowser(browser, useRootDocShell);
    }

    void checkValid() throws JRexException {
        if (!valid) {
            throw new JRexException("JRexLiveConnectSession has not been intialized. Call setBrowser first.");
        }
    }

    public int getSessionID() {
        return sessionID;
    }

    public int getJRexPeerID() {
        return jrexPeer;
    }

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexLiveConnectSessionImpl))
			return false;
		return ((JRexLiveConnectSessionImpl)obj).sessionID==sessionID;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return sessionID;
    }

    protected void finalize(){
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public void setBrowser(JRexCanvas browser) throws JRexException {
        setBrowser(browser, false);
    }

    public void setBrowser(JRexCanvas browser, boolean useRootDocShell) throws JRexException {
        if(JRexL.on)JRexL.log(className,"**** setBrowser browser<" + browser.getJRexPeer() + "> ****");
        if (inited) {
            jrexPeer = browser.getJRexPeer();
            sessionID = Init(useRootDocShell);
            valid = true;
        } else {
		    throw new java.awt.IllegalComponentStateException("Invocation of initIDs Failed!!!");
        }
    }

    public void grantBrowserAccessToJVM() throws JRexException {
        startupLiveConnect();
    }

    public String invokeStringMethod(String functionName, String arg) throws JRexException {
		if(JRexL.on)JRexL.log(className,"**** invokeStringMethod functionName<" + functionName +
                "> arg<" + arg + "> ****");
        checkValid();
        return InvokeStringMethod(functionName, arg);
    }

    public String evalUntrusted(String script) throws JRexException {
		if(JRexL.on)JRexL.log(className,"**** evalUntrusted ****");
        checkValid();
        return EvalUntrusted(script);
    }

    public JSObject getJSWindow() throws JRexException {
		if(JRexL.on)JRexL.log(className,"**** getJSWindow ****");
        checkValid();
        if (!liveConnectStarted) {
            throw new SecurityException("Browser does not have access to the JVM. Please call grantBrowserAccessToJVM() first.");
        }
        // A staic sync is needed because static variables are set in the library
        synchronized (staticSync) {
            if (jsObject == null) {
                jsObject = JRexJSObject.getWindowForSession(this);
            }
            return jsObject;
        }
    }

    public void jsGC() throws JRexException {
		if(JRexL.on)JRexL.log(className,"**** jsGC ****");
        checkValid();
        JS_GC();
    }

    private void startupLiveConnect() throws JRexException {
        if (!liveConnectStarted) {
            StartupLiveConnect();
            liveConnectStarted = true;
        }
    }

    private static native void initIDs() throws JRexException;

    native int Init(boolean useRootDocShell) throws JRexException;

    native void StartupLiveConnect() throws JRexException;

    native String InvokeStringMethod(String functionName, String arg) throws JRexException;

    native String EvalUntrusted(String script) throws JRexException;

    native void JS_GC() throws JRexException;

    native void Finalize() throws JRexException;
}
