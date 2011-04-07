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

package org.mozilla.jrex;

import  java.io.*;
import  java.net.*;
import 	java.util.*;
import  java.util.zip.*;

import 	java.lang.reflect.Method;
import 	org.mozilla.jrex.log.JRexL;
import 	org.mozilla.jrex.exception.JRexException;
import 	org.mozilla.jrex.window.JRexWindowManager;

/** A factory class for initialization of XPCOM and JRex interface implementers
* The implementor's for any interface in JRex is mapped in 'jrex.impl' file.
* Which will be loaded at startup and intialized, if you want to replace any of the
* interface implementation with yours put your implementation calss against interface key in
* 'jrex.impl' file.
* Note:- All the implementation classes should have no param constructor.
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public final class JRexFactory{
	/**
	* The class name string for logging.
	*/
	private static final String className					= JRexFactory.class.getName();

	/**
	* Key for WindowManager implementer retrival.
	*/
	public static final String WINDOW_MANAGER				= "WindowManager";

	/**
	* Key for WindowEventHandler implementer retrival.
	*/
	public static final String WINDOW_EVENT_HANDLER			= "WindowEventHandler";

	/**
	* Key for HistoryEventHandler implementer retrival.
	*/
	public static final String HISTORY_EVENT_HANDLER		= "HistoryEventHandler";

	/**
	* Key for ProgressEventHandler implementer retrival.
	*/
	public static final String PROGRESS_EVENT_HANDLER		= "ProgressEventHandler";

	/**
	* Key for ContextMenuEventHandler implementer retrival.
	*/
	public static final String CONTEXTMENU_EVENT_HANDLER	= "ContextMenuEventHandler";

	/**
	* Key for TooltipEventHandler implementer retrival.
	*/
	public static final String TOOLTIP_EVENT_HANDLER		= "TooltipEventHandler";

	/**
	* Key for ObserverEventHandler implementer retrival.
	*/
	public static final String OBSERVER_EVENT_HANDLER		= "ObserverEventHandler";

	/**
	* Key for URIContentEventHandler implementer retrival.
	*/
	public static final String URICONTENT_EVENT_HANDLER		= "URIContentEventHandler";

	/**
	* Key for JRexMenuBar implementer retrival.
	*/
	public static final String JREX_MENUBAR					= "JRexMenuBar";

	/**
	* Key for JRexStatusBar implementer retrival.
	*/
	public static final String JREX_STATUSBAR				= "JRexStatusBar";

	/**
	* Key for JRexToolBar implementer retrival.
	*/
	public static final String JREX_TOOLBAR					= "JRexToolBar";

	/**
	* Key for JRexPopupMenu implementer retrival.
	*/
	public static final String JREX_POPUPMENU				= "JRexPopupMenu";

	/**
	* Key for JRexPrintPreviewToolBar implementer retrival.
	*/
	public static final String JREX_PRINTPREVIEWTOOLBAR		= "JRexPrintPreviewToolBar";

	/**
	* Singleton instance of the factory.
	*/
	private static final JRexFactory instance	= new JRexFactory();


	/**
	* The JRex interface implementation instance Map.
	*/
	private Map implInstTable = Collections.synchronizedMap(new HashMap(10));

	/**
	* The JRex interface implementation Map.
	*/
	private Properties implTable		= new Properties();

	/**
	* Indicates if XPCOM engine is started.
	*/
	private boolean  engineStarted		= false;

	/**
	* Shutdown hook thread instance.
	*/
	private Thread 	 hookThread			= null;

	/**
	* Indicates if DOM is enabled, to enable DOM set "jrex.dom.enable" system property to true.
	*/
	private boolean isDOMEnabled		= false;

	/**
	* Indicates if XPCOM should be auto shutdown when <code>root</code> window closes.
	*/
	private boolean autoShutdown		= true;


	/**
	* Disable light weight popup and load interface implemenation classes
	*/
	static{
		javax.swing.JPopupMenu.setDefaultLightWeightPopupEnabled(false);
		if(JRexL.on)JRexL.log(className,"static()--> **** loading implementers ****");
		instance.loadImplementers();
	}

	private JRexFactory(){}

	/**
	* This function returns JRexFactory instance.
	*/
	public static JRexFactory getInstance(){
		return instance;
	}

	/**
	* This function returns new implemenation instance for give interface key.
	* Use this function for non singleton instance creation.
	* @param key The interface key.
	* @return <code>Object</code> the Instance of the interface.
	*/
	public Object getImplNewInstance(String key){
		if(JRexL.on)JRexL.log(className,"**** getImplNewInstance()-->key <"+key+">");
		String value=(String)implTable.get(key);
		if(JRexL.on)JRexL.log(className,"getImplNewInstance()--> Class value<"+value+"> ");
		Object rValue=null;
		try{
			Class myClass=Class.forName(value);
			if(JRexL.on)JRexL.log(className,"getImplNewInstance()--> **** myClass <"+myClass+">***");
			rValue=myClass.newInstance();
			if(JRexL.on)JRexL.log(className,"getImplNewInstance()--> **** created instance <"+rValue+"> of <"+value+">***");
		}catch(Exception ex){
			JRexL.printStackTrace(ex);
		}
		return rValue;
	}

	/**
	* This function returns implemenation instance for give interface key.
	* @param key The interface key.
	* @return <code>Object</code> the Instance of the interface.
	*/
	public Object getImplInstance(String key){
		if(JRexL.on)JRexL.log(className,"**** getImplInstance()-->key <"+key+">");
		if(implInstTable.containsKey(key))return implInstTable.get(key);
		Object inst=getImplNewInstance(key);
		implInstTable.put(key,inst);
		return inst;
	}

	/**
	* This function Starts the XPCOM Engine and JRexEventManager.
	* This function also adds a shutdown hook for shutting down xpcom in
	* case it was not shutdown.
	*/
	public synchronized void startEngine()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** startEngine()-->engineStarted <"+engineStarted+">");
		if(engineStarted)return;
		org.mozilla.jrex.xpcom.JRexXPCOMImpl.getInstance().startXPCOM();
		if(JRexL.on)JRexL.log(className,"**** startEngine()-->startXPCOM done");
		org.mozilla.jrex.event.JRexEventManager.getInstance().startEventManager();
		if(JRexL.on)JRexL.log(className,"**** startEngine()-->startEventManager done");
		Runtime.getRuntime().addShutdownHook(hookThread=new Thread(){
			public void run(){
				if(JRexL.on)JRexL.log(className,"**** run()-->Shutdown hook called engineStarted <"+engineStarted+">");
				try{
					shutdownEngine();
				}catch(Exception ex){
					JRexL.printStackTrace(ex);
				}
				if(JRexL.on)JRexL.log(className,"**** run()-->Shutdown hook done");
			}
		});
		if(JRexL.on)JRexL.log(className,"**** startEngine()-->addShutdownHook done");
		engineStarted=true;
		String initDOM=System.getProperty("jrex.dom.enable");
		if(JRexL.on)JRexL.log(className,"**** startEngine()--> initDOM<"+initDOM+">");
		isDOMEnabled=initDOM!=null && initDOM.trim().equals("true");
		if(JRexL.on)JRexL.log(className,"**** startEngine()--> isDOMEnabled<"+isDOMEnabled+">");
		if(isDOMEnabled){
			isDOMEnabled=org.mozilla.jrex.dom.JRexDOMImplementationImpl.initialize();
			if(JRexL.on)JRexL.log(className,"startEngine()--> **** JRexDOMImplementationImpl Initialize done isDOMEnabled<"+isDOMEnabled+"> ***");
		}
	}

	/**
	* If set to <code>true</code> then XPCOM will be auto shutdown when Root-Window closes.
	* Root-Window will be parent window of component passed to WindowManager init method.
	* If <code>null</code> is passed to init method the JFrame window created by window manger
	* will be Root-Window. Default value is set to <code>true</code>.
	* @see org.mozilla.jrex.window.JRexWindowManager#init(javax.swing.JComponent)
	*/
	public void setAutoShutdown(boolean autoShutdown){
		this.autoShutdown=autoShutdown;
	}

	/**
	* Returns <code>true</code> if XPCOM will be auto shutdown when Root-Window closes.
	* @see #setAutoShutdown(boolean)
	*/
	public boolean getAutoShutdown(){
		return autoShutdown;
	}

	/**
	* Returns <code>true</code> if DOM is enabled.
	* To enable JRex DOM set "jrex.dom.enable" system property to true before starting XPCOM engine.
	*/
	public boolean isDOMEnabled(){
		return isDOMEnabled;
	}

	/**
	* Returns <code>true</code> if current thread is ShutdownHook that was registered when
	* XPCOM was started.
	* @see	#startEngine()
	*/
	public boolean isShutdownHook(){
		return Thread.currentThread()==hookThread;
	}

	/**
	* This function Stops the XPCOM engine and JRexEventManager.
	* It also closes all browser windows opened.
	*/
	public synchronized void shutdownEngine()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** shutdownEngine()-->engineStarted <"+engineStarted+">");
		if(engineStarted){
			((JRexWindowManager)implInstTable.get(WINDOW_MANAGER)).dispose();
			if(JRexL.on)JRexL.log(className,"**** shutdownEngine()-->WINDOW_MANAGER dispose done!!!");
			org.mozilla.jrex.event.JRexEventManager.getInstance().stopEventManager();
			if(isDOMEnabled){
				org.mozilla.jrex.dom.JRexDOMImplementationImpl.unInitialize();
				if(JRexL.on)JRexL.log(className,"shutdownEngine()--> **** JRexDOMImplementationImpl unInitialize done ***");
			}
			if(JRexL.on)JRexL.log(className,"**** shutdownEngine()-->stopEventManager done");
			org.mozilla.jrex.xpcom.JRexXPCOMImpl.getInstance().stopXPCOM();
			if(JRexL.on)JRexL.log(className,"**** shutdownEngine()-->stopXPCOM done");
			engineStarted=false;
		}
	}


	/**
	* This function loads the implementation classes from the jrex.impl file.
	* All the implementation classes should have no param constructor.
	*/
	private void loadImplementers(){
		try{
			implTable.load(JRexFactory.class.getClassLoader().getResourceAsStream("jrex.impl"));
		}catch(Exception ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"loadImplementers()--> **** impl TABLE<"+implTable+">***");
	}
			}
