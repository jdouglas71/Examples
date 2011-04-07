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

package org.mozilla.jrex.ui;

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.navigation.*;
import org.mozilla.jrex.selection.*;
import org.mozilla.jrex.event.history.*;
import org.mozilla.jrex.event.uricontent.*;
import org.mozilla.jrex.event.progress.*;
import org.mozilla.jrex.event.context.*;
import org.mozilla.jrex.event.tooltip.*;
import org.w3c.dom.Element;
import org.mozilla.jrex.event.window.WindowEventConstants;


/**
* JRexCanvas is the browser component. This component wraps the <b>nsWebBrowser</b>
* and related interfaces of mozilla embedding.
* It allows listening to follwing events:
* <ul>
* <li><b>ProgressListener</b></li>
* <li><b>ContextMenuListener</b></li>
* <li><b>HistoryListener</b></li>
* <li><b>KeyListener</b></li>
* <li><b>MouseListener</b></li>
* <li><b>MouseMotionListener</b></li>
* <li><b>URIContentListener</b></li>
* </ul>
*
* The Mouse and Key events are posted directly into Java's SystemEvent queue. So there is
* no specific Mouse and Key Listener for JRexCanvas.
* All the event except URIContentListener are mulitcast events. i.e only one URIContentListener
* can be added to a browser component.
* Listening to ToolTip events not enabled at present. It is used only for internal use.
* It allows operation related to Navigation, Edit and Print actions.
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.navigation.WebNavigation
*/

public class JRexCanvas extends java.awt.Canvas {
	private static final String className	= JRexCanvas.class.getName();

	/**
	* PrintPreview Navigation Constants
	*/
	private static final int PRINTPREVIEW_GOTO_PAGENUM	= 0;
	private static final int PRINTPREVIEW_PREV_PAGE 	= 1;
	private static final int PRINTPREVIEW_NEXT_PAGE		= 2;
	private static final int PRINTPREVIEW_HOME 			= 3;
	private static final int PRINTPREVIEW_END 			= 4;

	/**
	* Persist flags:
	*/
	/** No special persistence behaviour.
	*/
	public static final int PERSIST_FLAGS_NONE = 0;

	/** Only use cached data (could result in failure if data is not cached).
	*/
	public static final int PERSIST_FLAGS_FROM_CACHE = 1;

	/** Bypass the cached data.
	*/
	public static final int PERSIST_FLAGS_BYPASS_CACHE = 2;

	/** Ignore any redirected data (usually adverts).
	*/
	public static final int PERSIST_FLAGS_IGNORE_REDIRECTED_DATA = 4;

	/** Ignore IFRAME content (usually adverts).
	*/
	public static final int PERSIST_FLAGS_IGNORE_IFRAMES = 8;

	/** Do not run the incoming data through a content converter.
	* E.g. to decompress it
	*/
	public static final int PERSIST_FLAGS_NO_CONVERSION = 16;

	/** Replace existing files on the disk (use with due diligence!)
	*/
	public static final int PERSIST_FLAGS_REPLACE_EXISTING_FILES = 32;

	/** Don't modify or add base tags.
	*/
	public static final int PERSIST_FLAGS_NO_BASE_TAG_MODIFICATIONS = 64;

	/** Make changes to original dom rather than cloning nodes
	*/
	public static final int PERSIST_FLAGS_FIXUP_ORIGINAL_DOM = 128;

	/** Fix links relative to destination location (not origin)
	*/
	public static final int PERSIST_FLAGS_FIXUP_LINKS_TO_DESTINATION = 256;

	/** Don't make any adjustments to links
	*/
	public static final int PERSIST_FLAGS_DONT_FIXUP_LINKS = 512;

	/** Force serialization of output (one file at a time; not concurrent)
	*/
	public static final int PERSIST_FLAGS_SERIALIZE_OUTPUT = 1024;

	/** Don't make any adjustments to filenames
	*/
	public static final int PERSIST_FLAGS_DONT_CHANGE_FILENAMES = 2048;

	/** Fail on broken inline links
	*/
	public static final int PERSIST_FLAGS_FAIL_ON_BROKEN_LINKS = 4096;

	/**
	* Persist state flags:
	*/
	/** Persister is ready to save data */
	public static final int PERSIST_STATE_READY = 1;

	/** Persister is saving data */
	public static final int PERSIST_STATE_SAVING = 2;

	/** Persister has finished saving data */
	public static final int PERSIST_STATE_FINISHED = 3;

	/**
	* Persist result values
	*/
	/** Persist operation was successful or is still ongoing if Persister is saving. */
	public static final int PERSIST_SUCCESS = 1;

	/** Persist operation was cancled. */
	public static final int PERSIST_ABORTED = 2;

	/** Persist operation encountered a non-specific failure. */
	public static final int PERSIST_FAILURE = 3;

	/**
	* Persist encoding constants.
	*/

	/** Persist encoding Flag to Output only the current selection as opposed to the whole document. */
	public static final int ENCODE_FLAGS_SELECTION_ONLY = 1;

	/**
	* Persist encoding Flag for plaintext output. Convert html to plaintext that looks like the html.
	* Implies wrap (except inside &lt;pre&gt;), since html wraps.
	* HTML output: always do prettyprinting, ignoring existing formatting.
	*/
	public static final int ENCODE_FLAGS_FORMATTED = 2;

	/**
	* Persist encoding Flag to Output without formatting or wrapping the content. This flag
	* may be used to preserve the original formatting as much as possible.
	*/
	public static final int ENCODE_FLAGS_RAW = 4;

	/** Persist encoding Flag to Output only the body section and no HTML tags.
	*/
	public static final int ENCODE_FLAGS_BODY_ONLY = 8;

	/** Persist encoding Flag to Wrap even if when not doing formatted output. E.g. for text fields.
	*/
	public static final int ENCODE_FLAGS_PREFORMATTED = 16;

	/**Persist encoding Flag to Wrap documents at the specified column.
	*/
	public static final int ENCODE_FLAGS_WRAP = 32;

	/**
	* Persist encoding Flag for plaintext output. Output for format flowed (RFC 2646). This is used
	* when converting to text for mail sending. This differs just slightly
	* but in an important way from normal formatted, and that is that
	* lines are space stuffed. This can't (correctly) be done later.
	*/
	public static final int ENCODE_FLAGS_FORMAT_FLOWED = 64;

	/** Persist encoding Flag to Convert links to absolute links where possible.
	*/
	public static final int ENCODE_FLAGS_ABSOLUTE_LINKS = 128;

	/**
	* Persist encoding Flag to Attempt to encode entities standardized at W3C (HTML, MathML, etc).
	* This is a catch-all flag for documents with mixed contents. Beware of
	* interoperability issues. See below for other flags which might likely
	* do what you want.
	*/
	public static final int ENCODE_FLAGS_ENCODE_W3C_ENTITIES = 256;

	/**
	* Persist encoding Flag to Output with carriage return line breaks. May also be combined with
	* ENCODE_FLAGS_LF_LINEBREAKS and if neither is specified, the platform
	* default format is used.
	*/
	public static final int ENCODE_FLAGS_CR_LINEBREAKS = 512;

	/**
	* Persist encoding Flag to Output with linefeed line breaks. May also be combined with
	* ENCODE_FLAGS_CR_LINEBREAKS and if neither is specified, the platform
	* default format is used.
	*/
	public static final int ENCODE_FLAGS_LF_LINEBREAKS = 1024;

	/** Persist encoding Flag for plaintext output. Output the content of noscript elements.
	*/
	public static final int ENCODE_FLAGS_NOSCRIPT_CONTENT = 2048;

	/** Persist encoding Flag for plaintext output. Output the content of noframes elements.
	*/
	public static final int ENCODE_FLAGS_NOFRAMES_CONTENT = 4096;

	/**
	* A Persist encoding Flag to Encode basic entities. E.g. output &nbsp; instead of character code 0xa0.
	* The basic set is just &nbsp; &amp; &lt; &gt; &quot; for interoperability
	* with older products that don't support &alpha; and friends.
	*/
	public static final int ENCODE_FLAGS_ENCODE_BASIC_ENTITIES = 8192;

	/**
	* Persist encoding Flag to Encode Latin1 entities. This includes the basic set and
	* accented letters between 128 and 255.
	*/
	public static final int ENCODE_FLAGS_ENCODE_LATIN1_ENTITIES = 16384;

	/**
	* Persist encoding Flag to Encode HTML4 entities. This includes the basic set, accented
	* letters, greek letters and certain special markup symbols.
	*/
	public static final int ENCODE_FLAGS_ENCODE_HTML_ENTITIES = 32768;


	/**
	* Indicates whether the native initIDs was successfully.
	*/
	//TO DO this should go
	private static boolean inited			= false;

	static{
		try{
			initIDs();
			inited=true;
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* Represents the peer browser component associated with browser component.
	*/
	private int			jrexPeer			= 0;

	/**
	* Indicates whether the peer browser component is realized.
	*/
	private boolean 	realized			= false;

	/**
	* Indicates whether the peer has been notified of the java component peer creation.
	* This is required for *nix, since the java.awt.Component's addnotify function actualy does not create
	* a peer component in *nix(at least in Linux).
	*/
	private boolean 	notifyPeer			= false;

	/**
	* Indicates whether ProgressListener is added for the browser component.
	*/
	private boolean 	progLstnAdded		= false;

	/**
	* Indicates whether ContextMenuListener is added for the browser component.
	*/
	private boolean 	ctxMenuLstnAdded	= false;

	/**
	* Indicates whether HistoryListener is added for the browser component.
	*/
	private boolean 	hisLstnAdded		= false;

	/**
	* Indicates whether KeyListener is added for the browser component.
	*/
	private boolean 	keyLstnAdded		= false;

	/**
	* Indicates whether MouseListener is added for the browser component.
	*/
	private boolean 	mouseLstnAdded		= false;

	/**
	* Indicates whether MouseMotionListener is added for the browser component.
	*/
	private boolean 	mouseMotionLstnAdded= false;

	/**
	* Indicates whether URIContentListener is added for the browser component.
	*/
	private boolean 	uriContentLstnAdded = false;

	/**
	* The browser setup-flag assoicated with the browser.
	*/
	private Hashtable	browserSetupFlags	= null;

	/**
	* Browser navigation interface instance.
	*/
	private WebNavigation navigator			= new WebNavigationImpl();

	/**
	* Browser selection interface instance.
	*/
	private JRexSelection selection			= new JRexSelectionImpl();

	/**
	* A list of ProgressListener added to browser.
	*/
	private Vector progLsnList;

	/**
	* A list of ContextMenuListener added to browser.
	*/
	private Vector ctxMenuLsnList;

	/**
	* A list of HistoryListener added to browser.
	*/
	private Vector hisLsnList;

	/**
	* URIContentListener added to browser.
	*/
	private URIContentListener uriContentListener;

	/**
	* Constructor to create JRexCanvas.
	*/
	protected JRexCanvas(Hashtable browserSetupFlags){
		this.browserSetupFlags=browserSetupFlags;
		setFocusable(true);
		enableEvents(AWTEvent.FOCUS_EVENT_MASK);
	}

	/**
	* Use this function to create a JRexCanvas.
    * If this function is used then Global Setup-Flag is used(if set)
 	* from system property jrex.browser.setupflag, The property should be an integer object.
	*/
	public static JRexCanvas createBrowserComponent(){
		return createBrowserComponent(WindowEventConstants.CHROME_DEFAULT);
	}

	/**
	* Use this function to create a JRexCanvas.
    * If this function is used then Global Setup-Flag is used(if set)
 	* from system property jrex.browser.setupflag, The property should be an integer object.
 	* @param	chromeFlags The chrome falgs to use for canvas creation
	*/
	public static JRexCanvas createBrowserComponent(long chromeFlags){
		String value=System.getProperty("jrex.browser.usesetupflags");
		Hashtable jrexSetupProps=null;
		if(value!=null && value.equals("true")){
			jrexSetupProps=new Hashtable();

			if((value=System.getProperty("jrex.browser.allow.plugin"))!=null)
				jrexSetupProps.put("jrex.browser.allow.plugin",new Boolean(value));

			if((value=System.getProperty("jrex.browser.allow.javascript"))!=null)
				jrexSetupProps.put("jrex.browser.allow.javascript",new Boolean(value));

			if((value=System.getProperty("jrex.browser.allow.metaredirects"))!=null)
				jrexSetupProps.put("jrex.browser.allow.metaredirects",new Boolean(value));

			if((value=System.getProperty("jrex.browser.allow.subframes"))!=null)
				jrexSetupProps.put("jrex.browser.allow.subframes",new Boolean(value));

			if((value=System.getProperty("jrex.browser.allow.images"))!=null)
				jrexSetupProps.put("jrex.browser.allow.images",new Boolean(value));

			if((value=System.getProperty("jrex.browser.ischromewrapper"))!=null)
				jrexSetupProps.put("jrex.browser.ischromewrapper",new Boolean(value));

			if((value=System.getProperty("jrex.browser.useglobalhistory"))!=null)
				jrexSetupProps.put("jrex.browser.useglobalhistory",new Boolean(value));

			if(jrexSetupProps.size()<1)jrexSetupProps=null;
		}
		return createBrowserComponent(chromeFlags, jrexSetupProps);
	}

	/**
	* Use this function to create a JRexCanvas. This function is meant for
	* WindowManger to handle WindowCreation request from embedding engine.
	* @param	browserSetupFlags The list of SETUP-Flags that allow certain properties of a new browser
 	*			object to set before the browser window is created.
 	*			Global Setup-Flag can be set using system property, Below are the list of setup properties.
	*			<ul>
	* 				<li><b>jrex.browser.usesetupflags</b> value should be true/false, Enables/disables usage of setup flags.</li>
	* 				<li><b>jrex.browser.allow.plugin</b> value should be true/false, Enables/disables plugin support for this browser.</li>
	* 				<li><b>jrex.browser.allow.javascript</b> value should be true/false, Enables/disables Javascript support for this browser.</li>
	* 				<li><b>jrex.browser.allow.metaredirects</b> value should be true/false, Enables/disables meta redirect support for this browser.
	* 											Meta redirect timers will be ignored if this option is disabled.</li>
	* 				<li><b>jrex.browser.allow.subframes</b> value should be true/false, Enables/disables subframes support for this browser.</li>
	* 				<li><b>jrex.browser.allow.images</b> value should be true/false, Enables/disables image loading for this browser.</li>
	* 				<li><b>jrex.browser.ischromewrapper</b> value should be true/false, Setting this property to true makes the browser a chrome wrapper.</li>
	* 				<li><b>jrex.browser.useglobalhistory</b> value should be true/false, Enables/disables the use of global history in the browser. Visited
	*												 URLs will not be recorded in the global history when it is disabled.</li>
	* 			</ul>
 	*			Note:- The value in browserSetupFlags is expected to a Boolean object.
	*/
	public static JRexCanvas createBrowserComponent(Hashtable browserSetupFlags){
		return createBrowserComponent(WindowEventConstants.CHROME_DEFAULT,browserSetupFlags);
	}

	/**
	* Use this function to create a JRexCanvas. This function is meant for
	* WindowManger to handle WindowCreation request from embedding engine.
	* @param	browserSetupFlags The list of SETUP-Flags that allow certain properties of a new browser
 	*			object to set before the browser window is created.
 	*			Global Setup-Flag can be set using system property, Below are the list of setup properties.
	*			<ul>
	* 				<li><b>jrex.browser.usesetupflags</b> value should be true/false, Enables/disables usage of setup flags.</li>
	* 				<li><b>jrex.browser.allow.plugin</b> value should be true/false, Enables/disables plugin support for this browser.</li>
	* 				<li><b>jrex.browser.allow.javascript</b> value should be true/false, Enables/disables Javascript support for this browser.</li>
	* 				<li><b>jrex.browser.allow.metaredirects</b> value should be true/false, Enables/disables meta redirect support for this browser.
	* 											Meta redirect timers will be ignored if this option is disabled.</li>
	* 				<li><b>jrex.browser.allow.subframes</b> value should be true/false, Enables/disables subframes support for this browser.</li>
	* 				<li><b>jrex.browser.allow.images</b> value should be true/false, Enables/disables image loading for this browser.</li>
	* 				<li><b>jrex.browser.ischromewrapper</b> value should be true/false, Setting this property to true makes the browser a chrome wrapper.</li>
	* 				<li><b>jrex.browser.useglobalhistory</b> value should be true/false, Enables/disables the use of global history in the browser. Visited
	*												 URLs will not be recorded in the global history when it is disabled.</li>
	* 			</ul>
 	*			Note:- The value in browserSetupFlags is expected to a Boolean object.
 	* @param	chromeFlags The chrome falgs to use for canvas creation
	*/
	public static JRexCanvas createBrowserComponent(long chromeFlags, Hashtable browserSetupFlags){
		if((WindowEventConstants.CHROME_OPENAS_CHROME
					& chromeFlags)==WindowEventConstants.CHROME_OPENAS_CHROME){
			if(browserSetupFlags==null)
				browserSetupFlags=new Hashtable();
			browserSetupFlags.put("jrex.browser.ischromewrapper",new Boolean(true));
		if(JRexL.on)JRexL.log(className,"**** createBrowserComponent aaaa ####################### ****");
		}
		if(inited)
			return new JRexCanvas(browserSetupFlags);
		throw new java.awt.IllegalComponentStateException("Invocation of initIDs Failed!!!");
	}

	/**
	* Return peer component associated with JRexCanvas.
	*/
	public int getJRexPeer(){
		return jrexPeer;
	}

    /**
     * Creates the peer of the JRexCanvas. The native component is realized and made visible.
     * This function is also used to associate the JRex peer with java canvas peer in windows platform.
     * @see     java.awt.Canvas#addNotify()
     */
	public void addNotify(){
		super.addNotify();
		if(JRexL.on)JRexL.log(className,"**** addNotify() -->jrexPeer<"+jrexPeer+"> before CreatePeer ****");
		if(jrexPeer>0)return;
		synchronized (getTreeLock()) {
			try{
				if(JRexL.on)JRexL.log(className,"**** addNotify() -->addNotify currentThread <"+Thread.currentThread()+">****");
				CreatePeer(browserSetupFlags);
				if(JRexL.on)JRexL.log(className,"**** addNotify() -->jrexPeer<"+jrexPeer+"> after CreatePeer **** ");
				RealizePeer();
				browserRealized();
				if(JRexL.on)JRexL.log(className,"**** addNotify() -->RealizePeer done **** ");
				setVisible(super.isVisible());
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
				throw new RuntimeException("**** addNotify() --> createPeer FAILED <"+ex.getMessage()+">****");
			}
		}
	}

	/**
	* Invoked to indicate that browser peer has completed realization.
	* This function is intended to be used by WindowManager.
	*/
	//don't call form outside
	public void browserRealized(){
		if(JRexL.on)JRexL.log(className,"**** browserRealized() -->realized <"+realized+"> **** ");
		if(realized)return;
		realized=true;
		if(progLsnList!=null && progLsnList.size()>0)
			addProgressListenerInternal();
		if(ctxMenuLsnList!=null && ctxMenuLsnList.size()>0)
			addContextMenuListenerInternal();
		if(hisLsnList!=null && hisLsnList.size()>0)
			addHistoryListenerInternal();
		if(uriContentListener!=null)
			addURIContentListenerInternal();
		if(getKeyListeners().length>0)
			addKeyListenerInternal();
		if(getMouseListeners().length>0)
			addMouseListenerInternal();
		if(getMouseMotionListeners().length>0)
			addMouseMotionListenerInternal();
	}

    /**
     * Processes focus events occurring on this component by dispatching them to native peer.
     * @see     java.awt.Component#processFocusEvent(FocusEvent)
     */
	protected void processFocusEvent(final FocusEvent fe){
		if(JRexL.on)JRexL.log(className,"processFocusEvent()-->***** I AM HERE fe<"+fe+">***** ");
		if(fe.isTemporary() || !realized || !isShowing())return;
		if(JRexL.on)JRexL.log(className,"processFocusEvent()-->***** FOCUS_GAINED<"+(fe.getID()==FocusEvent.FOCUS_GAINED)+"> ***** ");

		if(EventQueue.isDispatchThread()){
			try{
				SetFocusPeer(fe.getID()==FocusEvent.FOCUS_GAINED);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			return;
		}
		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			try{
				SetFocusPeer(fe.getID()==FocusEvent.FOCUS_GAINED);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}});
	}

	public boolean isFocusable(){
		return realized;
	}

    /**
     * Paints the JRexCanvas by signalling Repaint to the peer component.
     * This function is also used to associate the JRex peer with java canvas peer in
     * *nix platform. since the java.awt.Component's addnotify function actualy does not create
	 * a java peer component in addnotify call.
     *
     * @param      g   the specified Graphics context
     * @see        java.awt.Component#paint(Graphics)
     */
	public void paint(java.awt.Graphics g){
		if(JRexL.on)JRexL.log(className,"paint()-->***** I AM HERE ***** ");
		Toolkit.getDefaultToolkit().sync();
		if(jrexPeer>0 && !notifyPeer){
			notifyPeer=true;
			try{
				if(JRexL.on)JRexL.log(className,"paint()-->***** Calling GotVisual ***** ");
				synchronized (getTreeLock()) {
					GotVisual();
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		if(!realized || !isShowing())return;
		try{
			if(JRexL.on)JRexL.log(className,"paint()-->***** Calling RepaintPeer ***** ");
			synchronized (getTreeLock()) {
				RepaintPeer(true);
			}
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	/**
	* Simply calls paint function.
	* @param      g   the specified Graphics context
	* @see        #paint(Graphics)
	*/
	public void update(java.awt.Graphics g){
		paint(g);
	}

    /**
     * Destroys the peer of the JRexCanvas.
     * @see     java.awt.Canvas#removeNotify()
     */
	public void removeNotify(){
		if(JRexL.on)JRexL.log(className,"removeNotify()--> ***** jrexPeer<"+jrexPeer+"> before DestroyPeer ****");
		if(jrexPeer>0)
		try{
			DestroyPeer();
			if(JRexL.on)JRexL.log(className,"removeNotify()-->***** jrexPeer <"+jrexPeer+"> after DestroyPeer ****");
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			jrexPeer=0;
		}
		super.removeNotify();
	}


	/**
	* Sets the visible state of the JRexCanvas.
	* @param visible if true, shows this JRexCanvas peer; otherwise, hides it
	*/
	public void setVisible(final boolean visible){
		super.setVisible(visible);
		if(JRexL.on)JRexL.log(className,"setVisible()-->***** visible <"+visible+"> ****");
		if(!realized)return;
		if(EventQueue.isDispatchThread()){
			try{
				SetVisiblePeer(visible);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			return;
		}
		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			try{
				SetVisiblePeer(visible);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}});
	}


	/**
	* Determines whether this component should be visible when its
	* parent is visible.
	* @see #setVisible
	*/
	public boolean isVisible(){
		if(JRexL.on)JRexL.log(className,"isVisible()-->**** I AM HERE ****");
		if(realized){
			try{
				boolean temp= IsVisiblePeer();
				if(JRexL.on)JRexL.log(className,"isPeerVisible()-->***** visible <"+temp+">***** ");
				return temp;
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return super.isVisible();
	}

	/**
	* Enables or disables this component, depending on the value of the
	* parameter <code>enable</code>.
	*/
    public void	setEnabled(final boolean enable){
		if(JRexL.on)JRexL.log(className,"setEnabled()-->***** enable <"+enable+"> ***** ");
		super.setEnabled(enable);
		if(!realized)return;
		if(EventQueue.isDispatchThread()){
			try{
				SetEnabledPeer(enable);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			return;
		}
		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			try{
				SetEnabledPeer(enable);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}});
	}

	/**
	* Determines whether this component is enabled.
	* @see #setEnabled
	*/
    public boolean isEnabled(){
		if(JRexL.on)JRexL.log(className,"isEnabled()-->**** I AM HERE ****");
		if(realized){
			try{
				boolean temp=IsEnabledPeer();
				if(JRexL.on)JRexL.log(className,"IsEnabledPeer()-->**** enable <"+temp+">****");
				return temp;
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return super.isEnabled();
	}

	/**
	* Moves and resizes this component. The new location of the top-left
	* corner is specified by <code>x</code> and <code>y</code>, and the
	* new size is specified by <code>width</code> and <code>height</code>.
	* @param x the new <i>x</i>-coordinate of this component
	* @param y the new <i>y</i>-coordinate of this component
	* @param width the new <code>width</code> of this component
	* @param height the new <code>height</code> of this
	* 		component
	* @see #getBounds
	*/
	public void setBounds(int x, int y, int width, int height){
		if(JRexL.on)JRexL.log(className,"setBounds()-->**** x<"+x+"> y<"+y+"> width<"+width+"> height<"+height+"> ***");
		super.setBounds(x,y,width,height);
		if(!realized)return;
		if(EventQueue.isDispatchThread()){
			try{
				synchronized (getTreeLock()) {
				SetBoundsPeer();
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			return;
		}

		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			try{
				synchronized (getTreeLock()) {
				SetBoundsPeer();
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}});
	}

	/**
	* Gets the bounds of this component in the form of a
	* <code>Rectangle</code> object. The bounds specify this
	* component's width, height, and location relative to
	* its parent.
	* @return a rectangle indicating this component's bounds
	* @see #setBounds
	*/
	public Rectangle getBounds(){
		if(JRexL.on)JRexL.log(className,"getBounds()-->**** I AM HERE ***");
		if(realized){
			try{
				return GetBoundsPeer();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return super.getBounds();
	}

	/**
	* Gets the mininimum size of this component.
	* @see #getSize
	* @see java.awt.LayoutManager
	*/
	public Dimension getMinimumSize(){
		if(JRexL.on)JRexL.log(className,"getMinimumSize()-->**** I AM HERE ***");
		return getSize();
	}

	/**
	* Returns the size of this object in the form of a
	* <code>Dimension</code> object. The height field of the
	* <code>Dimension</code> object contains this objects's
	* height, and the width field of the <code>Dimension</code>
	* object contains this object's width.
	*
	* @return a <code>Dimension</code> object that indicates
	*     the size of this component; <code>null</code> if
	*     this object is not on the screen
	*/
	public Dimension getSize(){
		if(JRexL.on)JRexL.log(className,"getSize()-->**** I AM HERE ***");
		return realized?getBounds().getSize():super.getSize();
	}

	/**
	* Gets the preferred size of this component.
	* @return a dimension object indicating this component's preferred size
	* @see #getSize
	*/
    public Dimension getPreferredSize() {
		if(JRexL.on)JRexL.log(className,"getPreferredSize()-->**** I AM HERE ***");
		return getSize();
    }


	/**
	* Gets the JRex Window Title.
	* @return the tittle associated with the browser component
	* @see #setJRexWindowTitle
	*/
	public String getJRexWindowTitle(){
		if(realized){
			try{
				return GetTitlePeer();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return "";
	}

	/**
	* Sets the JRex Window Title.
	* @param	title the tittle to be associated with the browser component
	* @see #getJRexWindowTitle
	*/
	public void setJRexWindowTitle(String title){
		if(realized){
			try{
				SetTitlePeer(title);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	/**
	* Returns the navigator assocaiated with the browser component.
	* @see org.mozilla.jrex.navigation.WebNavigation
	*/
	public WebNavigation getNavigator(){
		navigator.setJRexPeer(jrexPeer);
		return navigator;
	}

	/**
	* Returns the Selection associated with the browser component.
	* If DOM is not enabled this method returns <code>null</code>
	* @see org.mozilla.jrex.selection.JRexSelection
	*/
	public JRexSelection getSelection(){
		if(!org.mozilla.jrex.JRexFactory.getInstance().isDOMEnabled())return null;
		selection.setJRexPeer(jrexPeer);
		return selection;
	}

	/**
	* Moves the focus from current focused element to next element.
	*@param forward If <code>true</code> focus is moved in foward direction.
	*/
	public void moveFocus(boolean forward){
		if(JRexL.on)JRexL.log(className,"moveFocus()-->**** forward<"+forward+"> ***");
		if(realized){
			try{
				MoveFocusPeer(forward);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	/**
	* Returns the focused DOM element.
	* If DOM is not enabled this method returns <code>null</code>
	*/
	public Element getFocusedElement(){
		if(JRexL.on)JRexL.log(className,"getFocusedElement()-->****I AM HERE ***");
		if(realized && org.mozilla.jrex.JRexFactory.getInstance().isDOMEnabled()){
			try{
				return GetFocusedElement();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
		return null;
	}

	/**
	* Set's the focused DOM element.
	* If DOM is not enabled this method does nothing.
	*/
	public void setFocusedElement(Element ele){
		if(JRexL.on)JRexL.log(className,"setFocusedElement()-->**** ele <"+ele+"> ***");
		if(realized &&
				org.mozilla.jrex.JRexFactory.getInstance().isDOMEnabled()
					&& ele instanceof org.mozilla.jrex.dom.JRexElementImpl){
			try{
				SetFocusedElement(ele);
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	private void addKeyListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addKeyListenerInternal() -->keyLstnAdded <"+keyLstnAdded+"> **** ");
		if(keyLstnAdded)return;
		if(realized){
			try{
				AddKeyListener();
				keyLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addKeyListenerInternal() -->keyLstnAdded <"+keyLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Adds the specified key listener to receive key events from
     * this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    l   the key listener.
     * @see      java.awt.event.KeyEvent
     * @see      java.awt.event.KeyListener
     * @see      #removeKeyListener
     * @see      java.awt.Component#getKeyListeners
     */
	public void addKeyListener(KeyListener l){
		if(JRexL.on)JRexL.log(className,"**** addKeyListener() -->l <"+l+"> **** ");
		if(l==null)return;
		super.addKeyListener(l);
		addKeyListenerInternal();

	}

	private void addMouseListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addMouseListenerInternal() -->mouseLstnAdded <"+mouseLstnAdded+"> **** ");
		if(mouseLstnAdded)return;
		if(realized){
			try{
				AddMouseListener();
				mouseLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addMouseListenerInternal() -->mouseLstnAdded <"+mouseLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Adds the specified mouse listener to receive mouse events from
     * this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    l   the mouse listener
     * @see      java.awt.event.MouseEvent
     * @see      java.awt.event.MouseListener
     * @see      #removeMouseListener
     * @see      java.awt.Component#getMouseListeners
     */
	public void addMouseListener(MouseListener l){
		if(JRexL.on)JRexL.log(className,"**** addMouseListener() -->l <"+l+"> **** ");
		if(l==null)return;
		super.addMouseListener(l);
		addMouseListenerInternal();
	}


	private void addMouseMotionListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addMouseMotionListenerInternal() -->mouseMotionLstnAdded <"+mouseMotionLstnAdded+"> **** ");
		if(mouseMotionLstnAdded)return;
		if(realized){
			try{
				AddMouseMotionListener();
				mouseMotionLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addMouseMotionListenerInternal() -->mouseMotionLstnAdded <"+mouseMotionLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Adds the specified mouse motion listener to receive mouse motion
     * events from this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    l   the mouse motion listener
     * @see      java.awt.event.MouseEvent
     * @see      java.awt.event.MouseMotionListener
     * @see      #removeMouseMotionListener
     * @see      java.awt.Component#getMouseMotionListeners
     */
	public void addMouseMotionListener(MouseMotionListener l){
		if(JRexL.on)JRexL.log(className,"**** addMouseMotionListener() -->l <"+l+"> **** ");
		if(l==null)return;
		super.addMouseMotionListener(l);
		addMouseMotionListenerInternal();
	}


	private void addProgressListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addProgressListenerInternal() -->progLstnAdded <"+progLstnAdded+"> **** ");
		if(progLstnAdded)return;
		if(realized){
			try{
				AddProgressListener();
				progLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addProgressListenerInternal() -->progLstnAdded <"+progLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Adds the specified progress listener to receive progress
     * events from this component.
     * If listener <code>progressListener</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    progressListener the Progress listener
     * @see      org.mozilla.jrex.event.progress.ProgressEvent
     * @see      #removeProgressListener
     * @see      #getProgressListeners
     */
	public void addProgressListener(ProgressListener progressListener){
		if(JRexL.on)JRexL.log(className,"**** addProgressListener() -->progressListener <"+progressListener+"> **** ");
		if(progressListener==null)return;
		if(progLsnList==null)progLsnList=new Vector();
		if(!progLsnList.contains(progressListener))
			progLsnList.add(progressListener);
		addProgressListenerInternal();
	}


	/**
	* Returns an array of all the progress listeners
	* registered on this component.
	*
	* @return all of this component's <code>ProgressListener</code>s
	*         or an empty array if no progress
	*         listeners are currently registered
	*
	* @see      #addProgressListener
	* @see      #removeProgressListener
	*/
    public synchronized ProgressListener[] getProgressListeners() {
		if(progLsnList==null)return new ProgressListener[0];
		ProgressListener[] list= new ProgressListener[progLsnList.size()];
        return (ProgressListener[]) progLsnList.toArray(list);
    }

	private void addContextMenuListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addContextMenuListenerInternal() -->ctxMenuLstnAdded <"+ctxMenuLstnAdded+"> **** ");
		if(ctxMenuLstnAdded)return;
		if(realized){
			try{
				AddContextMenuListener();
				ctxMenuLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addContextMenuListenerInternal() -->ctxMenuLstnAdded <"+ctxMenuLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Adds the specified ContextMenu listener to receive ContextMenu
     * events from this component.
     * If listener <code>contextMenuListener</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    contextMenuListener   the ContextMenu listener
     * @see      org.mozilla.jrex.event.context.ContextMenuEvent
     * @see      #removeContextMenuListener
     * @see      #getContextMenuListeners
     */

	public void addContextMenuListener(ContextMenuListener contextMenuListener){
		if(JRexL.on)JRexL.log(className,"**** addContextMenuListener() -->contextMenuListener <"+contextMenuListener+"> **** ");
		if(contextMenuListener==null)return;
		if(ctxMenuLsnList==null)ctxMenuLsnList=new Vector();
		if(!ctxMenuLsnList.contains(contextMenuListener))
			ctxMenuLsnList.add(contextMenuListener);
		addContextMenuListenerInternal();
	}


	/**
	* Returns an array of all the ContextMenu listeners
	* registered on this component.
	*
	* @return all of this component's <code>ContextMenuListener</code>s
	*         or an empty array if no ContextMenu
	*         listeners are currently registered
	*
	* @see      #addContextMenuListener
	* @see      #removeContextMenuListener
	*/
    public synchronized ContextMenuListener[] getContextMenuListeners() {
		if(ctxMenuLsnList==null)return new ContextMenuListener[0];
		ContextMenuListener[] list= new ContextMenuListener[ctxMenuLsnList.size()];
        return (ContextMenuListener[]) ctxMenuLsnList.toArray(list);
    }



	private void addHistoryListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addHistoryListenerInternal() -->hisLstnAdded <"+hisLstnAdded+"> **** ");
		if(hisLstnAdded)return;
		if(realized){
			try{
				AddHistoryListener();
				hisLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addHistoryListenerInternal() -->hisLstnAdded <"+hisLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}


    /**
     * Adds the specified History listener to receive History
     * events from this component.
     * If listener <code>historyListener</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * @param    historyListener   the History listener
     * @see      org.mozilla.jrex.event.history.HistoryEvent
     * @see      #removeHistoryListener
     * @see      #getHistoryListeners
     */

	public void addHistoryListener(HistoryListener historyListener){
		if(JRexL.on)JRexL.log(className,"**** addHistoryListener() -->historyListener <"+historyListener+"> **** ");
		if(historyListener==null)return;
		if(hisLsnList==null)hisLsnList=new Vector();
		if(!hisLsnList.contains(historyListener))
			hisLsnList.add(historyListener);
		addHistoryListenerInternal();
	}


	/**
	* Returns an array of all the History listeners
	* registered on this component.
	*
	* @return all of this component's <code>HistoryListener</code>s
	*         or an empty array if no History
	*         listeners are currently registered
	*
	* @see      #addHistoryListener
	* @see      #removeHistoryListener
	*/
    public synchronized HistoryListener[] getHistoryListeners() {
		if(hisLsnList==null)return new HistoryListener[0];
		HistoryListener[] list= new HistoryListener[hisLsnList.size()];
        return (HistoryListener[]) ctxMenuLsnList.toArray(list);
    }


	private void addURIContentListenerInternal(){
		if(JRexL.on)JRexL.log(className,"**** addURIContentListener() -->uriContentLstnAdded <"+uriContentLstnAdded+"> **** ");
		if(uriContentLstnAdded)return;
		if(realized){
			try{
				AddURIContentListener();
				uriContentLstnAdded=true;
				if(JRexL.on)JRexL.log(className,"**** addURIContentListener() -->uriContentLstnAdded <"+uriContentLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	/**
	* Adds the specified URIContent listener to receive URIContent
	* events from this component.
	* If listener <code>uriContentListener</code> is <code>null</code>,
	* no exception is thrown and no action is performed.
	* If listener was already added the <code>uriContentListener</code> will relace it.
	*
	* @param    uriContentListener   the URIContent listener
	* @see      org.mozilla.jrex.event.uricontent.URIContentEvent
	* @see      #removeURIContentListener
	*/
	public void addURIContentListener(URIContentListener uriContentListener){
		if(JRexL.on)JRexL.log(className,"**** addURIContentListener() -->uriContentListener <"+uriContentListener+"> **** ");
		if(uriContentListener==null)return;
		this.uriContentListener=uriContentListener;
		addURIContentListenerInternal();
	}


    /**
     * Removes the specified key listener so that it no longer
     * receives key events from this component. This method performs
     * no function, nor does it throw an exception, if the listener
     * specified by the argument was not previously added to this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * If list of KeyListeners is empty, native peer is requested to remove the KeyListener.
     *
     * @param    l   the key listener
     * @see      java.awt.event.KeyEvent
     * @see      java.awt.event.KeyListener
     * @see      #addKeyListener
     * @see      #getKeyListeners
     */

	public void removeKeyListener(KeyListener l){
		super.removeKeyListener(l);
		if(getKeyListeners().length==0 && keyLstnAdded){
			try{
				RemoveKeyListener();
				keyLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeKeyListener() -->mouseLstnAdded <"+mouseLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

    /**
     * Removes the specified mouse listener so that it no longer
     * receives mouse events from this component. This method performs
     * no function, nor does it throw an exception, if the listener
     * specified by the argument was not previously added to this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * If list of MouseListener is empty, native peer is requested to remove the MouseListener.
     *
     * @param    l   the mouse listener
     * @see      java.awt.event.MouseEvent
     * @see      java.awt.event.MouseListener
     * @see      #addMouseListener
     * @see      #getMouseListeners
     */
	public void removeMouseListener(MouseListener l){
		super.removeMouseListener(l);
		if(getMouseListeners().length==0 && realized){
			try{
				RemoveMouseListener();
				mouseLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeMouseListener() -->mouseLstnAdded <"+mouseLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}

	}


    /**
     * Removes the specified mouse motion listener so that it no longer
     * receives mouse motion events from this component. This method performs
     * no function, nor does it throw an exception, if the listener
     * specified by the argument was not previously added to this component.
     * If listener <code>l</code> is <code>null</code>,
     * no exception is thrown and no action is performed.
     *
     * If list of MouseMotionListener is empty, native peer is requested to remove the MouseMotionListener.
     *
     * @param    l   the mouse motion listener
     * @see      java.awt.event.MouseEvent
     * @see      java.awt.event.MouseMotionListener
     * @see      #addMouseMotionListener
     * @see      #getMouseMotionListeners
     */
	public void removeMouseMotionListener(MouseMotionListener l){
		super.removeMouseMotionListener(l);
		if(getMouseMotionListeners().length==0 && mouseMotionLstnAdded){
			try{
				RemoveMouseMotionListener();
				mouseMotionLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeMouseMotionListener() -->mouseMotionLstnAdded <"+mouseMotionLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	/**
	* Removes the specified progress listener so that it no longer
	* receives progress events from this component. This method performs
	* no function, nor does it throw an exception, if the listener
	* specified by the argument was not previously added to this component.
	* If listener <code>progressListener</code> is <code>null</code>,
	* no exception is thrown and no action is performed.
	*
	* If list of ProgressListener is empty, native peer is requested to remove the ProgressListener.
	*
	* @param    progressListener   the progress listener
	* @see      org.mozilla.jrex.event.progress.ProgressEvent
	* @see      #addProgressListener
	* @see      #getProgressListeners
	*/
	public void removeProgressListener(ProgressListener progressListener){
		if(JRexL.on)JRexL.log(className,"**** removeProgressListener() -->progressListener <"+progressListener+"> **** ");
		if(progressListener==null|| progLsnList==null)return;
		progLsnList.remove(progressListener);
		if(progLsnList.size()<1 && progLstnAdded){
			try{
				RemoveProgressListener();
				progLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeProgressListener() -->progLstnAdded <"+progLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	/**
	* Removes the specified ContextMenu listener so that it no longer
	* receives ContextMenu events from this component. This method performs
	* no function, nor does it throw an exception, if the listener
	* specified by the argument was not previously added to this component.
	* If listener <code>contextMenuListener</code> is <code>null</code>,
	* no exception is thrown and no action is performed.
	*
	* If list of ContextMenuListener is empty, native peer is requested to remove the ContextMenuListener.
	*
	* @param    contextMenuListener   the ContextMenu listener
	* @see      org.mozilla.jrex.event.context.ContextMenuEvent
	* @see      #addContextMenuListener
	* @see      #getContextMenuListeners
	*/
	public void removeContextMenuListener(ContextMenuListener contextMenuListener){
		if(JRexL.on)JRexL.log(className,"**** removeContextMenuListener() -->contextMenuListener <"+contextMenuListener+"> **** ");
		if(contextMenuListener==null||ctxMenuLsnList==null)return;
		ctxMenuLsnList.remove(contextMenuListener);
		if(ctxMenuLsnList.size()<1 && ctxMenuLstnAdded){
			try{
				RemoveContextMenuListener();
				ctxMenuLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeContextMenuListener() -->ctxMenuLstnAdded <"+ctxMenuLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}


	/**
	* Removes the specified History listener so that it no longer
	* receives History events from this component. This method performs
	* no function, nor does it throw an exception, if the listener
	* specified by the argument was not previously added to this component.
	* If listener <code>historyListener</code> is <code>null</code>,
	* no exception is thrown and no action is performed.
	*
	* If list of HistoryListener is empty, native peer is requested to remove the HistoryListener.
	*
	* @param    historyListener   the History listener
	* @see      org.mozilla.jrex.event.history.HistoryEvent
	* @see      #addHistoryListener
	* @see      #getHistoryListeners
	*/
	public void removeHistoryListener(HistoryListener historyListener){
		if(JRexL.on)JRexL.log(className,"**** removeHistoryListener() -->historyListener <"+historyListener+"> **** ");
		if(historyListener==null || hisLsnList==null)return;
		hisLsnList.remove(historyListener);
		if(hisLsnList.size()<1 && hisLstnAdded){
			try{
				RemoveHistoryListener();
				hisLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeHistoryListener() -->hisLstnAdded <"+hisLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}


	/**
	* Removes the URIContent listener so that it no longer
	* receives URIContent events from this component. This method performs
	* no function, nor does it throw an exception, if the listener was
	* not previously added to this component.
	*
	* Native peer is requested to remove the URIContentListener.
	*
	* @see      org.mozilla.jrex.event.uricontent.URIContentEvent
	* @see      #addURIContentListener
	*/
	public void removeURIContentListener(){
		if(JRexL.on)JRexL.log(className,"**** removeURIContentListener() -->uriContentListener <"+uriContentListener+"> **** ");
		if(uriContentLstnAdded){
			try{
				RemoveURIContentListener();
				uriContentLstnAdded=false;
				if(JRexL.on)JRexL.log(className,"**** removeURIContentListener() -->uriContentLstnAdded <"+uriContentLstnAdded+"> **** ");
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}


   /**
     * Processes progress events occurring on this browser
     * by dispatching them to any registered
     * <code>ProgressListener</code> objects.
     * <p>
     * This method is not called unless progress events are
     * enabled for this browser. Progress events are enabled
     * when an <code>ProgressListener</code> object is registered
     * via <code>addProgressListener</code>.
     *
     * @param       pe the Progress event
     * @see         org.mozilla.jrex.event.progress.ProgressListener
     */
    public void processProgressEvent(ProgressEvent pe) {
		if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->pe<"+pe+"> ****");
		assert progLsnList!=null && progLsnList.size()>0;
		if(progLsnList==null || progLsnList.size()<1)return;
		Enumeration progEnumeration= progLsnList.elements();
		int progEventType=pe.getEventType();
		switch(progEventType){
			case ProgressEventConstants.PROG_STATE_CHANGE:
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onStateChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onStateChange ****");
				break;

			case ProgressEventConstants.PROG_PROGRESS_CHANGE:
				if(isShowing())
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onProgressChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onProgressChange ****");
				break;

			case ProgressEventConstants.PROG_LOC_CHANGE:
				if(isShowing())
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onLocationChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onLocationChange ****");
				break;

			case ProgressEventConstants.PROG_STATUS_CHANGE:
				if(isShowing())
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onStatusChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onStatusChange ****");
				break;

			case ProgressEventConstants.PROG_LINK_STATUS_CHANGE:
				if(isShowing())
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onLinkStatusChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onStatusChange ****");
				break;

			case ProgressEventConstants.PROG_SECURITY_CHANGE:
				while(progEnumeration.hasMoreElements())
					((ProgressListener)progEnumeration.nextElement()).onSecurityChange(pe);
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()-->onSecurityChange ****");
				break;
			default:
				if(JRexL.on)JRexL.log(className,"**** processProgressEvent()--> UNKNOW TYPE ****");
		};
    }


   /**
     * Processes ContextMenu events occurring on this browser
     * by dispatching them to any registered
     * <code>ContextMenuListener</code> objects.
     * <p>
     * This method is not called unless ContextMenu events are
     * enabled for this browser. ContextMenu events are enabled
     * when an <code>ContextMenuListener</code> object is registered
     * via <code>addContextMenuListener</code>.
     *
     * @param       ce the ContextMenu event
     * @see         org.mozilla.jrex.event.context.ContextMenuListener
     */
    public void processContextMenuEvent(ContextMenuEvent ce){
		if(JRexL.on)JRexL.log(className,"**** processContextMenuEvent()-->ce<"+ce+"> ****");
		assert ctxMenuLsnList!=null && ctxMenuLsnList.size()>0;
		if(ctxMenuLsnList==null || ctxMenuLsnList.size()<1 || !isShowing())return;
		Enumeration ctxMenuEnumeration=ctxMenuLsnList.elements();
		while(ctxMenuEnumeration.hasMoreElements())
			((ContextMenuListener)ctxMenuEnumeration.nextElement()).showContextMenu(ce);
	}


   /**
     * Processes history events occurring on this browser
     * by dispatching them to any registered
     * <code>HistoryListener</code> objects.
     * <p>
     * This method is not called unless history events are
     * enabled for this browser. History events are enabled
     * when an <code>HistoryListener</code> object is registered
     * via <code>addHistoryListener</code>.
     *
     * @param       he the History event
     * @return      Boolean appropriate can's depending on event.
     * @see         org.mozilla.jrex.event.history.HistoryListener
     */
    public Boolean processHistoryEvent(HistoryEvent he) {
		if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->he<"+he+"> ****");
		assert hisLsnList!=null && hisLsnList.size()>0;
		if(hisLsnList==null || hisLsnList.size()<1)return new Boolean(false);
		Enumeration hisEnumeration=hisLsnList.elements();
		int hisEventType=he.getEventType();
		switch(hisEventType){
			case HistoryEventConstants.HIS_NEW_ENTRY_EVENT:
				while(hisEnumeration.hasMoreElements())
					((HistoryListener)hisEnumeration.nextElement()).addEntry(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->addEntry ****");
				break;

			case HistoryEventConstants.HIS_GO_BACK_EVENT:
				boolean canGoBack=true;
				while(hisEnumeration.hasMoreElements())
					canGoBack&=((HistoryListener)hisEnumeration.nextElement()).goBack(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->goBack canGoBack <"+canGoBack+"> ****");
				return new Boolean(canGoBack);

			case HistoryEventConstants.HIS_GO_FORWARD_EVENT:
				boolean canGoForward=true;
				while(hisEnumeration.hasMoreElements())
					canGoForward&=((HistoryListener)hisEnumeration.nextElement()).goForward(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()--> goForward canGoForward <"+canGoForward+"> ****");
				return new Boolean(canGoForward);

			case HistoryEventConstants.HIS_RELOAD_EVENT:
				boolean canReload=true;
				while(hisEnumeration.hasMoreElements())
					canReload&=((HistoryListener)hisEnumeration.nextElement()).reload(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->reload canReload <"+canReload+"> ****");
				return new Boolean(canReload);

			case HistoryEventConstants.HIS_GO_TO_INDEX_EVENT:
				boolean canGoToIndex=true;
				while(hisEnumeration.hasMoreElements())
					canGoToIndex&=((HistoryListener)hisEnumeration.nextElement()).goToIndex(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->goToIndex canGoToIndex <"+canGoToIndex+"> ****");
				return new Boolean(canGoToIndex);

			case HistoryEventConstants.HIS_PURGE_EVENT:
				boolean canPurge=true;
				while(hisEnumeration.hasMoreElements())
					canPurge&=((HistoryListener)hisEnumeration.nextElement()).purge(he);
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()-->purge canPurge <"+canPurge+"> ****");
				return new Boolean(canPurge);

			default:
				if(JRexL.on)JRexL.log(className,"**** processHistoryEvent()--> UNKNOW TYPE ****");
		};
		return null;
	}



   /**
     * Processes URIContent events occurring on this browser
     * by dispatching them to registered
     * <code>URIContentListener</code> object.
     * <p>
     * This method is not called unless URIContent events are
     * enabled for this browser. URIContent events are enabled
     * when an <code>URIContentListener</code> object is registered
     * via <code>addURIContentListener</code>.
     *
     * @param       uce the URIContent event
     * @see         org.mozilla.jrex.event.uricontent.URIContentListener
     */

    public Object processURIContentEvent(URIContentEvent uce) {
		if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()-->uce<"+uce+"> ****");
		assert uriContentListener!=null;
		if(uriContentListener==null)return null;
		int uriCntEventType=uce.getEventType();
		switch(uriCntEventType){
			case URIContentEventConstants.URI_ON_START_EVENT:
			{
				boolean abortLoad=uriContentListener.onStartContent(uce);
				if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()-->onStartContent abortLoad <"+abortLoad+"> ****");
				return new Boolean(abortLoad);
			}
			case URIContentEventConstants.URI_DO_CONTENT:
			{
				URIContentEventRV rval=uriContentListener.doContent(uce);
				if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()-->doContent rval <"+rval+"> ****");
				return rval;
			}
			case URIContentEventConstants.URI_IS_PREFERRED:
			{
				URIContentEventRV rval=uriContentListener.isContentPreferred(uce);
				if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()-->isContentPreferred rval <"+rval+"> ****");
				return rval;
			}
			case URIContentEventConstants.URI_CAN_HANDLE_CONTENT: //doesn't isPreferred get the job done?
			{
				URIContentEventRV rval=uriContentListener.canHandleContent(uce);
				if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()-->canHandleContent rval <"+rval+"> ****");
				return rval;
			}
			case URIContentEventConstants.URI_GET_LOAD_COOKIE:
			case URIContentEventConstants.URI_SET_LOAD_COOKIE:
			default:
				if(JRexL.on)JRexL.log(className,"**** processURIContentEvent()--> UNKNOW TYPE ****");
		};
		return null;
    }



	/**
	* Processes TooltipEvent events occurring on this browser
	* @param       tte the TooltipEvent event
	*/
    private static JWindow toolTipWin;
    private static Point location;
    private static JToolTip toolTip;

    public void processTooltipEvent(TooltipEvent tte){
		if(JRexL.on)JRexL.log(className,"**** TooltipEvent()-->tte<"+tte+"> ****");
		if(!isShowing())return;
		int toolTipEventType=tte.getEventType();
		switch(toolTipEventType){
			case TooltipEventConstants.SHOW_EVENT:
				if(toolTipWin==null){
					toolTipWin=new JWindow(SwingUtilities.getWindowAncestor(this));
					toolTip=new JToolTip();
					toolTipWin.getContentPane().add(toolTip);
					location=new Point();
				}
				Point screenLocation = getLocationOnScreen();
				location.setLocation(tte.getClientX()+screenLocation.x,tte.getClientY()+screenLocation.y+ 20);
				toolTip.setTipText(tte.getToolTip());
				Dimension tipSize = toolTip.getPreferredSize();
				Rectangle bounds= getBounds();
				if (location.x <bounds.x)
					location.x =bounds.x;
				else
				if (location.x -bounds.x + tipSize.width >bounds.width)
					location.x = bounds.x + Math.max(0, bounds.width -tipSize.width);

				if (location.y <bounds.y)
					location.y =bounds.y;
				else
				if (location.y -bounds.y + tipSize.height >bounds.height)
					location.y =bounds.y + Math.max(0,bounds.height - tipSize.height);

				toolTipWin.setBounds(location.x,location.y,tipSize.width,tipSize.height);
			    toolTipWin.setVisible(true);
				break;
			case TooltipEventConstants.HIDE_EVENT:
				if(toolTipWin!=null)
					toolTipWin.setVisible(false);
				break;
			default:
				if(JRexL.on)JRexL.log(className,"**** processTooltipEvent()--> UNKNOW TYPE ****");
		};
	}


	/**
	* Invoked to print the current page shown by the browser
	* @param       prompt If <code>true</code> system will prompt with print dialog.
	* @param       showProgress If <code>true</code> print progress dialog is shown.
	*/
	public void print(boolean prompt, boolean showProgress)throws JRexException{
		Print(prompt, showProgress);
	}

	/**
	* Invoked to cancel an ongoing print request.
	* @see	#isPrinting()
	*/
	public void cancelPrint()throws JRexException{
		CancelPrint();
	}

	/**
	* Indicates whether a print is under progress.
	* @see	#cancelPrint()
	* @see	#print(boolean, boolean)
	*/
	public boolean isPrinting()throws JRexException{
		return IsPrinting();
	}

	/**
	* Invoked to Preview the current page shown by the browser
	* @param       shrinkToFit If <code>true</code> Preview will shrink to fit to the browser component view.
	* @param       isLandScape If <code>true</code> Preview will be in LandScape view.
	* @see	#print(boolean, boolean)
	*/

	public void printPreview(boolean shrinkToFit, boolean isLandScape)throws JRexException{
		PrintPreview(shrinkToFit, isLandScape);
	}

	/**
	* Invoked to cancel an print preview.
	* @see	#isPrintPreviewing()
	*/
	public void cancelPrintPreview()throws JRexException{
		CancelPrintPreview();
	}

	/**
	* Indicates whether a print preview is under progress.
	* @see	#cancelPrintPreview()
	* @see	#printPreview(boolean, boolean)
	*/
	public boolean isPrintPreviewing()throws JRexException{
		return IsPrintPreviewing();
	}

	/**
	* Gets the number of print preview pages.
	* @see	#printPreview(boolean, boolean)
	*/

	public int getPrintPreviewNumPages()throws JRexException{
		return GetPrintPreviewNumPages();
	}

	/**
	* Invoked to nagivate in print preview mode.
	* @param	navType the type of navigation to perform.
	* @param	pageNum the page number to navigate to.
	* @see		#printPreview(boolean, boolean)
	* see		PrintPreview Navigation Constants Above.
	*/
	public void printPreviewNavigate(int navType, int pageNum)throws JRexException{
		PrintPreviewNavigate(navType, pageNum);
	}

	/**
	* Invoked to do print PageSetup.
	* @see		#print(boolean, boolean)
	*/
	public void pageSetup()throws JRexException{
		PageSetup();
	}

	/**
	* Indicates whether an undo operation can be done.
	* @see	#undo()
	*/
	public boolean canUndo()throws JRexException{
		return CanUndo();
	}

	/**
	* Indicates whether an redo operation can be done.
	* @see	#redo()
	*/
	public boolean canRedo()throws JRexException{
		return CanRedo();
	}

	/**
	* Indicates whether an cut operation can be done.
	* @see	#cut()
	*/
	public boolean canCut()throws JRexException{
		return CanCut();
	}

	/**
	* Indicates whether an copy operation can be done.
	* @see	#copy()
	*/
	public boolean canCopy()throws JRexException{
		return CanCopy();
	}

	/**
	* Indicates whether an copy linklocation operation can be done.
	* @see	#copyLinkLocation()
	*/
	public boolean canCopyLinkLocation()throws JRexException{
		return CanCopyLinkLocation();
	}

	/**
	* Indicates whether an copy Imagelocation operation can be done.
	* @see	#copyImageLocation()
	*/
	public boolean canCopyImageLocation()throws JRexException{
		return CanCopyImageLocation();
	}

	/**
	* Indicates whether an copy ImageContents operation can be done.
	* @see	#copyImageContents()
	*/
	public boolean canCopyImageContents()throws JRexException{
		return CanCopyImageContents();
	}


	/**
	* Indicates whether an Paste operation can be done.
	* @see	#paste()
	*/
	public boolean canPaste()throws JRexException{
		return CanPaste();
	}

	/**
	* Indicates whether an Delete operation can be done.
	* @see	#delete()
	*/
	public boolean canDelete()throws JRexException{
		return CanDelete();
	}

	/**
	* Invoked to undo an edit operation.
	*/
	public void undo()throws JRexException{
		Undo();
	}

	/**
	* Invoked to redo an edit operation.
	*/
	public void redo()throws JRexException{
		Redo();
	}

	/**
	* Invoked to cut selected text.
	*/
	public void cut()throws JRexException{
		Cut();
	}

	/**
	* Invoked to copy selected text.
	*/
	public void copy()throws JRexException{
		Copy();
	}

	/**
	* Invoked to copy selected LinkLocation.
	*/
	public void copyLinkLocation()throws JRexException{
		CopyLinkLocation();
	}

	/**
	* Invoked to copy selected ImageLocation.
	*/
	public void copyImageLocation()throws JRexException{
		CopyImageLocation();
	}

	/**
	* Invoked to copy ImageContents.
	*/
	public void copyImageContents()throws JRexException{
		CopyImageContents();
	}

	/**
	* Invoked to paste text from clipboard.
	*/
	public void paste()throws JRexException{
		Paste();
	}

	/**
	* Invoked to select all text in an control.
	*/
	public void selectAll()throws JRexException{
		SelectAll();
	}

	/**
	* Invoked to clear all selection in an control.
	*/
	public void selectNone()throws JRexException{
		SelectNone();
	}

	/**
	* Invoked to delete selected text.
	*/
	public void delete()throws JRexException{
		Delete();
	}

	/**
	* Invoked to find a given text.
	* @return true if a match is found for given config.
	* @see JRexFindConfig
	*/
	public boolean find(JRexFindConfig config)throws JRexException{
		return Find(config);
	}

	/**
	* Invoked to repeat previous find.
	* @return true if a match is found for config set via Find.
	* @see JRexFindConfig
	*/
	public boolean findAgain()throws JRexException{
		return FindAgain();
	}

	/**
	* Returns if Document is being Loaded. Use this in conjunction with ProgressListener's
	* STOP status to find out if document has been loaded.
	* @return true if document is being loaded.
	* @see  org.mozilla.jrex.event.progress.ProgressListener
	*/
	public boolean isLoadingDocument()throws JRexException{
		return IsLoadingDocument();
	}

	/**
	* Returns the find config assocaited the browser component instance.
	* @see JRexFindConfig
	*/
	public JRexFindConfig getFindConfig()throws JRexException{
		return GetFindConfig();
	}

	/**
	* Get the flags governing how data is fetched and saved from the network.
	*/
	public int getPersistFlags()throws JRexException{
		return GetPersistFlags();
	}

	/**
	* Set the flags governing how data is fetched and saved from the network.
	* It is best to set this value explicitly unless you are prepared
	* to accept the default values.
	*/
	public void setPersistFlags(int persistFlags)throws JRexException{
		 SetPersistFlags(persistFlags);
	}

	/**
	* Get the current state of the persister object.
	*/
	public int getCurrentPersistState()throws JRexException{
		return GetCurrentPersistState();
	}

	/**
	* Get the value indicating the success or failure of the persist
	* operation.
	*/
  	public int getPersistResult()throws JRexException{
		return GetPersistResult();
	}

	/**
	* Save the given URI.
	* @param	uri		The URI string to load.
	* @param	referURI	The referring URI.  If this argument is NULL, the
	*                    referring URI will be inferred internally.
	* @param	postData	InputStream containing POST data for the request.
	* @param	extraHeaders String containing extra headers for the request.
	* @param	filePath the complete path where to save the URI.
	* @param	progressListener Callback listener for progress notifications.
	* Note:-	Progress listener is simply added to the browser component, so all progress listener will get
    *			save progress.
    *
	* @see #setPersistFlags(int)
	*/
	public void saveURI(String uri, String referURI, java.io.InputStream postData ,
						String extraHeaders, String filePath, ProgressListener progressListener)throws JRexException{
		if(progressListener!=null)
			addProgressListener(progressListener);
		SaveURI(uri,referURI,postData,extraHeaders,filePath, progressListener!=null);
	}

	/**
	* Save the current DOM document to file. And optionally all linked files
	* (e.g. images, CSS, JS & subframes). Do not call this method until the
	* document has finished loading!
	*
	* @param	filePath the complete path where to save the document.
	* @param dataPath	Path to directory where URIs linked to the document
	*                           are saved or nsnull if no linked URIs should be saved.
	* @param outputContentType The desired MIME type format to save the
	*                           document and all subdocuments into or nsnull to use
	*                           the default behaviour.
	* @param encodingFlags     Flags to pass to the encoder.
	* @param wrapColumn        For text documents, indicates the desired width to
	*                           wrap text at. Parameter is ignored if wrapping is not
	*                           specified by the encoding flags.
	* @param	progressListener Callback listener for progress notifications.
	* Note:-	Progress listener is simply added to the browser component, so all progress listener will get
    *			save progress.
	*/
	public void saveCurrentDocument(String filePath, String dataPath, String outputContentType,
									int encodingFlags, int wrapColumn, ProgressListener progressListener)throws JRexException{
		if(progressListener!=null)
			addProgressListener(progressListener);
		SaveCurrentDocument(filePath,dataPath,outputContentType,encodingFlags,wrapColumn, progressListener!=null);
	}

	/**
	* Cancels the current operation. The caller is responsible for cleaning up
	* partially written files or directories.
	*/
  	public void cancelSave()throws JRexException{
		CancelSave();
	}


	private static native void initIDs()throws JRexException;
	private native void CreatePeer(Hashtable browserSetupFlags)throws JRexException;
	private native void GotVisual()throws JRexException;
	private native void RealizePeer()throws JRexException;
	private native void DestroyPeer()throws JRexException;
	private native void SetBoundsPeer()throws JRexException;
	private native Rectangle GetBoundsPeer()throws JRexException;
	private native void SetVisiblePeer(boolean visible)throws JRexException;
	private native void SetEnabledPeer(boolean visible)throws JRexException;
	private native boolean IsVisiblePeer()throws JRexException;
	private native boolean IsEnabledPeer()throws JRexException;
	private native String GetTitlePeer()throws JRexException;
	private native void SetTitlePeer(String title)throws JRexException;
	private native void RepaintPeer(boolean force)throws JRexException;

	private native void SetFocusPeer(boolean focusGained)throws JRexException;
	private native void MoveFocusPeer(boolean forward)throws JRexException;
	private native Element GetFocusedElement()throws JRexException;
  	private native void SetFocusedElement(Element ele)throws JRexException;

	private native void Print(boolean prompt, boolean showProgress)throws JRexException;
	private native void CancelPrint()throws JRexException;
	private native boolean IsPrinting()throws JRexException;
	private native void PrintPreview(boolean shrinkToFit, boolean isLandScape)throws JRexException;
	private native void CancelPrintPreview()throws JRexException;
	private native int GetPrintPreviewNumPages()throws JRexException;
	private native boolean IsPrintPreviewing()throws JRexException;
	private native void PrintPreviewNavigate(int navType, int pageNum)throws JRexException;

	private native void PageSetup()throws JRexException;


	private native boolean CanUndo();
	private native boolean CanRedo();
	private native boolean CanCut();
	private native boolean CanCopy();
	private native boolean CanCopyLinkLocation();
	private native boolean CanCopyImageLocation();
	private native boolean CanCopyImageContents();
	private native boolean CanPaste();
	private native boolean CanDelete();

	private native void Undo();
	private native void Redo();
	private native void Cut();
	private native void Copy();
	private native void CopyLinkLocation();
	private native void CopyImageLocation();
	private native void CopyImageContents();
	private native void Paste();
	private native void SelectAll();
	private native void SelectNone();
	private native void Delete();

	private native boolean Find(JRexFindConfig config)throws JRexException;
	private native boolean FindAgain()throws JRexException;
	private native boolean IsLoadingDocument()throws JRexException;
	private native JRexFindConfig GetFindConfig()throws JRexException;

	private native int GetPersistFlags()throws JRexException;
	private native void SetPersistFlags(int persistFlags)throws JRexException;
	private native int GetCurrentPersistState()throws JRexException;
  	private native int GetPersistResult()throws JRexException;
	private native void SaveURI(String uri, String referURI, java.io.InputStream postData ,
									String extraHeaders, String filePath, boolean addProgListener)throws JRexException;
	private native void SaveCurrentDocument(String filePath, String dataPath, String outputContentType,
									int encodingFlags, int wrapColumn, boolean addProgListener)throws JRexException;
  	private native void CancelSave()throws JRexException;

	private native void AddProgressListener()throws JRexException;
	private native void AddContextMenuListener()throws JRexException;
	private native void AddHistoryListener()throws JRexException;
	private native void AddKeyListener()throws JRexException;
	private native void AddMouseListener()throws JRexException;
	private native void AddMouseMotionListener()throws JRexException;
	private native void AddURIContentListener()throws JRexException;

	private native void RemoveProgressListener()throws JRexException;
	private native void RemoveContextMenuListener()throws JRexException;
	private native void RemoveHistoryListener()throws JRexException;
	private native void RemoveKeyListener()throws JRexException;
	private native void RemoveMouseListener()throws JRexException;
	private native void RemoveMouseMotionListener()throws JRexException;
	private native void RemoveURIContentListener()throws JRexException;
}