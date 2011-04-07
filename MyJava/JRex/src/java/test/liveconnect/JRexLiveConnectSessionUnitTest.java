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
package test.liveconnect;

import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.navigation.WebNavigationConstants;
import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.liveconnect.JRexLiveConnectSession;
import org.mozilla.jrex.liveconnect.JRexLiveConnectSessionImpl;
import org.mozilla.jrex.event.window.WindowListener;
import org.mozilla.jrex.event.progress.ProgressListener;
import org.mozilla.jrex.event.progress.ProgressEvent;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.window.JRexWindowManager;

import java.io.File;
import java.io.PrintStream;
import java.io.FileOutputStream;
import java.awt.BorderLayout;
import java.util.Arrays;
import java.util.Vector;
import java.util.Date;
import java.util.ArrayList;
import java.util.List;

import netscape.javascript.JSObject;
import netscape.javascript.JSUtil;
import netscape.javascript.JSException;

import javax.swing.JCheckBox;

/**
 * Unit tests for JRexLiveConnectSession.
 * To test JRexLiveConnectSession, first build JRex. Then cd to the JRex/test
 * directory and run "runLCUnitTests.bat" or "runLCUnitTests.sh". When the tests
 * complete, a report will be loaded into the JRex browser which will state
 * whether or not the tests passed.
 * <p>
 * To test compatibility with java plugins, you can try loading a java plugin
 * after the tests finish. Then, you can click the checkbox "Ok to test" and open
 * a new tab. Whenever "Ok to test" is checked, the next tab opened will run the
 * unit tests. If the java plugin runs fine and the unit tests pass the second
 * time, then this shows JRexLiveConnectSession is compatible with the java
 * plugin.
 * </p>
 *
 * TODO: Run these in JUnit?
 * TODO: Add tests for setMember, slot functions
 */
public class JRexLiveConnectSessionUnitTest implements WindowListener, ProgressListener {
    private JRexWindowManager winManager;
    private String testFile;
    private JRexLiveConnectSession lcSession;
    private JRexCanvas browser;
    private javax.swing.JFrame main;
    // goBox can be used to run further tests. If selected, the next browser
    // which is opened will runt he tests. This is handy for testing with java applets.
    // For example, you might want to run the tests, make sure java applets still
    // work, and then run the tests again.
    private JCheckBox goBox = new JCheckBox("Ok to test");
	private int nIterations, curIteration = 0;

	public JRexLiveConnectSessionUnitTest(int nIterations) {
		this.nIterations = nIterations;
	}

    void debug(String msg) {
        System.out.print("JRexLiveConnectSessionUnitTest["+curIteration+"]::");
        System.out.println(msg);
    }

    public void initJRex(String testFile) throws JRexException {
        System.setProperty("javaplugin.outputfiles.path", "c:\\tmp\\plugin");
        System.setProperty("javaplugin.trace", "true");
        System.setProperty("javaplugin.automation", "true");
        this.testFile = testFile;
		main=new javax.swing.JFrame("MAIN");
		javax.swing.JPanel panel=new javax.swing.JPanel(new BorderLayout());
        main.getContentPane().setLayout(new BorderLayout());
        main.getContentPane().add(panel, BorderLayout.CENTER);
        main.getContentPane().add(goBox, BorderLayout.SOUTH);
		main.setVisible(true);
        goBox.setSelected(true);
		JRexFactory.getInstance().startEngine();

		winManager=(JRexWindowManager)JRexFactory.getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER);
		winManager.create(JRexWindowManager.TAB_MODE);
		//add your jrex windowlistener here
		winManager.addJRexWindowListener(this);
		winManager.init(panel);
    }

	public static void main(String s[])throws Exception{
		int nIterations = 1;
        if (s.length == 0) {
            System.err.println("Usage: java JRexLiveConnectSessionExample <testFile> [nIterations]");
            System.exit(-1);
        }
		if (s.length > 1) {
			nIterations = Integer.parseInt(s[1]);
		}
        new JRexLiveConnectSessionUnitTest(nIterations).initJRex(s[0]);
	}

    public void windowCreated(int jrexPeerID) {
        System.err.println(" windowCreated ##################### jrexPeerID <"+jrexPeerID+">#####################");
        if (goBox.isSelected()) {
            browser = winManager.getBrowser(jrexPeerID);
            browser.addProgressListener(this);
            debug("Loading sample javascript app");
            try {
                browser.getNavigator().loadURI("file:///" + new File(testFile).getCanonicalPath().replace('\\', '/'),
                        WebNavigationConstants.LOAD_FLAGS_NONE, null, null, null);
            } catch (Exception e) {
                System.err.println("ERROR: Failed to load testFile: \"" + testFile + "\"");
                e.printStackTrace();
            }
        }
    }

    public void windowDisposing(int jrexPeerID) {
        System.err.println("windowDisposing ##################### jrexPeerID <"+jrexPeerID+">#####################");
    }

    public void onStateChange(ProgressEvent event) {
        // Check if the document stopped loading. After the document stops loading it is safe to
        // call javascript methods.
        if (goBox.isSelected() && !event.isLoadingDocument()) {
            goBox.setSelected(false);
            new Thread(new Runnable() {
                public void run() {
                    // The document finished loading. It is ok now to call javascript methods
                    debug("Document is loaded");
                    runTests();
                }
            }).start();
        }
    }

    String invokeStringMethod(String funcName, String arg) throws JRexException {
        String ret = lcSession.invokeStringMethod("testStringFunction", "Hello, World!");
        debug("invokeStringMethod: funcName<" + funcName + "> arg<" + arg + "> ret<" + ret + ">");
        return ret;
    }

    public void onProgressChange(ProgressEvent event) {
    }

    public void onLocationChange(ProgressEvent event) {
    }

    public void onStatusChange(ProgressEvent event) {
    }

    public void onSecurityChange(ProgressEvent event) {
    }

    public void onLinkStatusChange(ProgressEvent event) {
    }

    private PrintStream testOut;
    final static String testReportFileName = "lcTests.txt";

    void test_debug(String msg) throws Exception {
        debug(msg);
        testOut.println("["+curIteration+"] "+msg);
        testOut.flush();
    }

    void assertTrue(boolean condition) throws Exception {
        if (!condition) {
            String msg = "Assertion failure. Current Stack:\n" + JSUtil.getStackTrace(new RuntimeException());
            test_debug(msg);
            throw new RuntimeException(msg);
        }
    }

    void runTests() {
        final File reportFile = new File(testReportFileName);
        try {
            testOut = new PrintStream(new FileOutputStream(reportFile));
            test_debug("RUNNING LIVECONNECT UNIT TESTS  " + new Date() + " nIterations<"+nIterations+">");
            test_debug("REPORT FILE = " + testReportFileName);
            lcSession = new JRexLiveConnectSessionImpl(browser);
            lcSession.grantBrowserAccessToJVM();
            // Invoke testInvokeStringMethod, which should work without JSObject being initialized
			for (int r = 0; r < nIterations; r++) {
				curIteration = r;
				testInvokeStringMethod();
				testEvalUntrusted1();
				testEvalUntrusted2();
				testGetJSObject();
                testCallMethodFail();
                testCallMethodNull();
				// garbage collection test... create a lot of large js objects
				for (int j = 0; j < 5; j++) {
					for (int i = 0; i < 10; i++) {
						testCreateNewLargeJSObject();
					}
					Thread.sleep(500L);
				}
				testEval1();
				testEval2();
				testCall1();
				testCall2();
				testCreateListInJavascript2();
				testCreateListInJavascript1();
				// garbage collection test... create a lot of large js objects
				for (int j = 0; j < 5; j++) {
					for (int i = 0; i < 10; i++) {
						testCreateNewLargeJSObject();
					}
					Thread.sleep(500L);
					System.gc();
					System.runFinalization();
				}
                testJSGC();
				// garbage collection test... create a lot of large java objects from js
				for (int j = 0; j < 5; j++) {
					for (int i = 0; i < 5; i++) {
						testCreateNewLargeJavaObject();
					}
					Thread.sleep(500L);
					System.gc();
					System.runFinalization();
				}
				testGetMember();
				testSetGlobalJSVar();
			}
            test_debug("ALL TESTS PASSED");
            testOut.close();
        } catch (Throwable e) {
            try {
				e.printStackTrace();
                test_debug("!!!!!!! TESTS FAILED:\n");
            } catch (Exception e1) {
                // Ignore
            }
            testOut.close();
        }

        // Display the report file but call ina new thread because we are already in a dispatch thread...
        new Thread(new Runnable() {
            public void run() {
                try {
                    browser.getNavigator().loadURI("file:///" + reportFile.getCanonicalPath(),
                            WebNavigationConstants.LOAD_FLAGS_NONE, null, null, null);
                    main.setSize(800, 800);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    void testInvokeStringMethod() throws Exception {
        String ret = invokeStringMethod("testStringFunction", "Hello, World!");
        test_debug("invokeStringMethod: function<testStringFunction> arg<\"Hello, World!\"> res_class<" +
                (ret != null ? ret.getClass().getName() : "NULL") +
                "> ret<" + ret + ">");
        assertTrue(ret != null && ret.equals("Hello, World!_test"));
    }

    void checkEvalUntrusted(String toEval, String expected) throws Exception {
        String res = lcSession.evalUntrusted(toEval);
        testCmp("testEvalUntrusted", toEval, expected, res);
    }

    void testEvalUntrusted1() throws Exception {
        checkEvalUntrusted("(1+2+5-3)/2", "2.5");
    }

    void testEvalUntrusted2() throws Exception {
        checkEvalUntrusted("testStringFunction('Hi there')", "Hi there_test");
    }

    void testGetJSObject() throws Exception {
        JSObject obj = lcSession.getJSWindow();
        assertTrue(obj != null);
    }

    void testCmp(String testName, String dataStr, Object expected, Object res) throws Exception {
        Class expectedClass = expected.getClass();
        test_debug(testName + ": data<" + dataStr + "> result<" + res + "> res_class<" +
                (res != null ? res.getClass().getName() : "NULL") +
                "> expected<" + expected + "> expectedClass<" + expectedClass.getName() + ">");
        assertTrue(res != null);
        assertTrue(expected.equals(res));
    }

    void checkEval(String toEval, Object expected) throws Exception {
        Object res = lcSession.getJSWindow().eval(toEval);
        testCmp("testEval", toEval, expected, res);
    }

    void testEval1() throws Exception {
        checkEval("(1+2+5-3)/2", new Double(2.5));
    }

    void testEval2() throws Exception {
        checkEval("testStringFunction('Hi there')", "Hi there_test");
    }

    void checkCall(String funcName, Object[] args, Object expected) throws Exception {
        Object res = lcSession.getJSWindow().call(funcName, args);
        test_debug("res<"+res+">");
        testCmp("testCall", Arrays.asList(args).toString(), expected, res);
    }

    void testCall1() throws Exception {
        checkCall("testStringFunction", new Object[] { "This is a test str" }, "This is a test str_test");
    }

    void testGetMember() throws Exception {
        Object document = lcSession.getJSWindow().getMember("document");
        test_debug("Got document member = " + document + ", class = " + (document != null ? document.getClass().getName() : "NULL"));
        assertTrue(document instanceof JSObject);
        // In mozilla debug, the toString actually produces an "@ <address>" on the end, so just
        // check that it starts with the right prefix.
        assertTrue(document.toString().startsWith("[object HTMLDocument"));
    }

    void testJSGC() throws Exception {
        lcSession.jsGC();
        test_debug("SUccessfully called jsGC");
    }

    public String getSampleString() {
        return "Sample string from java";
    }

    void testCall2() throws Exception {
        // The javascript actually calls back to the Java method getSampleString() and
        // returns the result.
        checkCall("testCallToJava", new Object[] { this }, getSampleString());
    }

    void checkCreateListInJavascript_cmp(Vector v, int indx, Object expected) throws Exception {
        Object obj = v.get(indx);
        test_debug("    indx<" + indx + "> obj<" + obj + "> obj_class<" +
                (obj != null ? obj.getClass().getName() : "NULL") + "> expected<" +
                expected + "> expected_class<" + expected.getClass().getName() + ">");
    }

    void checkCreateListInJavascript(Object res) throws Exception {
        test_debug("testCreateListInJavascript res<" + res + ">");
        assertTrue(res instanceof Vector);
        Vector v = (Vector)res;
        test_debug("testCreateListInJavascript res.size()<" + v.size() + ">");
        assertTrue(v.size() == 8);
        checkCreateListInJavascript_cmp(v, 0, "one");
        checkCreateListInJavascript_cmp(v, 1, "two");
        checkCreateListInJavascript_cmp(v, 2, "three");
        checkCreateListInJavascript_cmp(v, 3, "four");
        checkCreateListInJavascript_cmp(v, 4, "five");
        checkCreateListInJavascript_cmp(v, 5, "six");
        checkCreateListInJavascript_cmp(v, 6, new Double(7));
        checkCreateListInJavascript_cmp(v, 7, new Double(4.5));
    }

    void testCreateListInJavascript1() throws Exception {
        checkCreateListInJavascript(lcSession.getJSWindow().eval("testCreateList()"));
    }

    void testCreateListInJavascript2() throws Exception {
        List inList = new ArrayList();
        inList.add("one");
        inList.add("two");
        checkCreateListInJavascript(lcSession.getJSWindow().call("testCreateList2", new Object[] {inList}));
    }

    void testCreateLCTestClassInJavascript_cmp(Object obj, Object expected) throws Exception {
        test_debug("    obj<" + obj + "> obj_class<" +
                (obj != null ? obj.getClass().getName() : "NULL") + "> expected<" +
                expected + "> expected_class<" + expected.getClass().getName() + ">");
    }

    void testCreateLCTestClassInJavascript() throws Exception {
        Object res = lcSession.getJSWindow().eval("testCreateLCTestClass()");
        assertTrue(res != null);
        assertTrue(res instanceof LCTestClass);
        LCTestClass testCls = (LCTestClass)res;
        assertTrue(testCls.getTestDataMap().get("fromjavascript.window") != null);
        assertTrue(testCls.getTestDataMap().get("fromjavascript.document") != null);
        test_debug("testCls.getTestDataMap().get(\"fromjavascript.window\") class<" +
                testCls.getTestDataMap().get("fromjavascript.window").getClass().getName() + ">");
        test_debug("testCls.getTestDataMap().get(\"fromjavascript.document\") class<" +
                testCls.getTestDataMap().get("fromjavascript.document").getClass().getName() + ">");
        assertTrue(testCls.getTestDataMap().get("fromjavascript.window") instanceof JSObject);
        assertTrue(testCls.getTestDataMap().get("fromjavascript.document") instanceof JSObject);
        test_debug("testCreateLCTestClassInJavascript testCls_props<" + testCls.getTestDataMap() + ">");
        testCreateLCTestClassInJavascript_cmp(testCls.getTestString(), "Hello, World!");
        testCreateLCTestClassInJavascript_cmp(new Integer(testCls.getTestInt()), new Integer(50));
        testCreateLCTestClassInJavascript_cmp(new Float(testCls.getTestFloat()), new Float(15.5));
        testCreateLCTestClassInJavascript_cmp(new Double(testCls.getTestDouble()), new Double(85.0/2.0));
        testCreateLCTestClassInJavascript_cmp(new Long(testCls.getTestLong()), new Long(123456789));
    }

	int tmpid = 0;
    void testCreateNewLargeJSObject() throws Exception {
        Object ret = lcSession.getJSWindow().call("testCreateNewLargeJSObject", new Object[] {});
        assertTrue(ret instanceof JSObject);
		tmpid++;
		debug("testCreateNewLargeJSObject["+tmpid+"]: DONE");
	}

	int tmpid2 = 0;
	void testCreateNewLargeJavaObject() throws Exception {
		lcSession.getJSWindow().call("testCreateNewLargeJavaObject", new Object[] {this});
		tmpid2++;
		debug("testCreateNewLargeJavaObject["+tmpid2+"]: DONE");
	}

	void testSetGlobalJSVar() throws Exception {
		testSetGlobalJSVar("setGlobalVar1", new LargeJavaObject());
		testSetGlobalJSVar("setGlobalVar1", new Vector());
		testSetGlobalJSVar("setGlobalVar1", new Object[] {new LargeJavaObject()});
		testSetGlobalJSVar("setGlobalVar1", new long[1024]);
	}

	void testSetGlobalJSVar(String method, Object obj) throws Exception {
		lcSession.getJSWindow().call(method, new Object[] {obj});
		// Get the global var
		Object ret = lcSession.getJSWindow().call("g"+method.substring(1), new Object[] {});
		assertTrue(obj.equals(ret));
		test_debug("testSetGlobalJSVar set/get method<" + method + ">");
	}

    void testCallMethodFail() throws Exception {
        // Call a method that calls back to jave which throws a java exception
        try {
            lcSession.getJSWindow().call("throwJavaException", new Object[] {this});
            test_debug("Error in throwJavaException: excepted an exception to be thrown");
            test_debug("To get this unit test running, line 389 of mozilla/js/src/liveconnect/jsj_JSObject.c msu be changed to:");
            test_debug("if (report && (report->flags & JSREPORT_EXCEPTION) && (report->flags & JSREPORT_WARNING))");
            assertTrue(false);
        } catch (JSException e) {
            test_debug("throwJavaException: e<"+e+"> type<"+e.getWrappedExceptionType()+
                    "> wrapped<"+e.getWrappedException()+">");
            assertTrue(e.toString().indexOf("test.liveconnect.JRexLiveConnectSessionUnitTest$TestException: Test Java Exception")>=0);
        }
        // Invoke a bogus js call with a bad parameter
        try {
            lcSession.getJSWindow().call("testCreateList2", new Object[] {});
            test_debug("Error in testCallMethodFail: excepted an exception to be thrown");
            assertTrue(false);
        } catch (JSException e) {
            test_debug("testCallMethodFail: e<"+e+"> type<"+e.getWrappedExceptionType()+
                    "> wrapped<"+e.getWrappedException()+">");
            assertTrue(e.toString().indexOf("theListIn has no properties")>=0);
        }
    }

    public void testCallMethodNull() throws Exception {
        lcSession.getJSWindow().call("setGlobalVar1", null);
        Object ret = lcSession.getJSWindow().call("getGlobalVar1", null);
        test_debug("testCallMethodNull: ret<"+ret+">");
        assertTrue(ret == null);
        test_debug("testCallMethodNull: setGlobalVar1(null) succeeded");
    }

    public void throwJavaException() throws Exception {
        test_debug("throwJavaException called from javascript");
        throw new TestException("Test Java Exception");
    }

	public Object createLargeJavaObjectImpl() {
		return new LargeJavaObject();
	}

	static class LargeJavaObject {
		byte[] data = new byte[1024*1024];

		protected void finalize() throws Throwable {
			System.out.println("Finalizing large Java object");
			super.finalize();
		}
	}

    static class TestException extends Exception {
        public TestException(String msg) {
            super(msg);
        }
    }
}
