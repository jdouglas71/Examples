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

package org.mozilla.jrex.window;


import java.awt.Window;
import java.awt.Container;
import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.event.window.WindowEvent;
import org.mozilla.jrex.event.window.WindowListener;

/**
* An interface representing JREX Window manager
* It is also represents a listener interface for receiving window events.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.event.window.WindowEvent
*/

public interface JRexWindowManager{
	/**
	* A window mode representing normal browser window.
	*/
	public final static int WINDOW_MODE			= 0;

	/**
	* A window mode representing single browser window.
	* If an application uses this mode, any request to new window from web page will be ignored.
	*/
	public final static int SINGLE_WINDOW_MODE	= 1;

	/**
	* A window mode representing tabbed browser window.
	*/
	public final static int TAB_MODE			= 2;

	/**
	* A window mode representing tabbed browser window.
	* If an application uses this mode, any request to new window from web page will will be opened in new tab.
	*/
	public final static int FORCED_TAB_MODE		= 3;

	/**
	* A window mode representing JInternalPane browser window.
	*/
	public final static int INTERNAL_PANE_MODE	= 4;

	/**
	* Window manager creation function.
	* @param	mode The mode which the window manager should use.
	* @exception	Throws java.lang.IllegalArgumentException if mode is not valid.
	*/
	public void 		create(int mode);

	/**
	* Window manager intialization function, window manager should be created before calling
	* initialize function.
	* @param	parentComponent The parent component where the jrex browser will be attached.
	* The <code>parentComponent</code> should already have a parent window, ie, <code>parentComponent</code> should be added to a Frame/Dialog/Window before being passed to init function.
	* If <code>null</code> is passed a new JFrame window will be used.
	*/
	public void 		init(javax.swing.JComponent parentComponent);

	/**
	* Invoked when an window create request is received.
	*/
	public int			createWindow(WindowEvent event);

	/**
	* Invoked when an dialog needs to be made modal.
	*/
	public void 		setModal(WindowEvent event);

	/**
	* Invoked when an window size needs to be changed.
	*/
	public void 		setSize(WindowEvent event);

	/**
	* Invoked when an window title needs to be changed.
	*/
	public void 		setTitle(WindowEvent event);

	/**
	* Invoked when an chrome flags for a window needs to be changed. Chrome flags help in
	* identifying the type of window to be opened.
	*/
	public void 		setChromeFlags(WindowEvent event);

	/**
	* Invoked when jrex native implementation realizes the browser window.
	* Used to indicate Java implementation about the realization so the event listeners can be added.
	*/
	public void 		setRealized(WindowEvent event);

	/**
	* Invoked when an window destroy request is received.
	*/
	public void 		destroyWindow(WindowEvent event);

	/**
	* Invoked when an open new window request is received. The action taken depends
	* on the mode of the window manager.
	* @param	parentPeer the parent peer window ID which invoked this function,
	* 			Usage depends on window manager mode
	* @param	uri the URI to open.
	* @param	loadFlags the load flags to use for loading the URI.
	* @see 		org.mozilla.jrex.navigation.WebNavigationConstants
	*/
	public void 		openNewWindow(int parentPeer, String uri, int loadFlags);

	/**
	* Invoked when an open new tab request is received. The action taken depends
	* on the mode of the window manager.
	* @param	parentPeer the parent peer window ID which invoked this function,
	* 			Usage depends on window manager mode
	* @param	uri the URI to open.
	* @param	loadFlags the load flags to use for loading the URI.
	* @see 		org.mozilla.jrex.navigation.WebNavigationConstants
	*/
	public void 		openNewTab(int parentPeer, String uri, int loadFlags);

	/**
	* Invoked to remove a tab. The action taken depends on the mode of the window manager.
	* @param	browserPeer the peer browser ID for the tab.
	*/
	public void destroyTab(int browserPeer);

	/**
	* Used to add a window into window manger list of created windows.
	* @param 	browser	the browser component associated window.
	* @param 	parent the Container containing the browser component.
	* @param 	rootParent the rootContainer containing the browser component,
				like the content pane of JFrame or can be parent itself or
	* @param 	window the window containing the browser component.
	* @param 	chromeFlags the Chrome Flags for the window.
	*/
	public void 		addWindow(JRexCanvas browser, Container parent, Container rootParent, Window window, long chromeFlags);

	/**
	* Used to remove a window from window manger list of created windows.
	* @param	peerWindow the peer window ID for the window.
	*/
	public void 		removeWindow(int peerWindow);

	/**
	* Finds and returns the JRexCanvas assocciated with given peer window.
	*/
	public JRexCanvas 	getBrowser(int peerWindow);

	/**
	* Finds and returns the list of JRexCanvas assocciated with given window.
	*/
	public java.util.Iterator getBrowserForWindow(java.awt.Window window);

	/**
	* Finds and returns the list of JRexCanvas assocciated with given rootParent.
	*/
	public java.util.Iterator getBrowserForRootParent(java.awt.Container rootParent);

	/**
	* Finds and returns the JRexCanvas assocciated with given parent.
	*/
	public JRexCanvas getBrowserForParent(java.awt.Container parent);

	/**
	* Finds and returns the Container assocciated with given peer window.
	*/
	public Container 	getBrowserParent(int peerWindow);

	/**
	* Finds and returns the Root Container assocciated with given peer window.
	*/
	public Container 	getBrowserRootParent(int peerWindow);

	/**
	* Finds and returns the Window assocciated with given peer window.
	*/
	public Window 		getBrowserWindow(int peerWindow);

	/**
	* Finds and returns the JRexBrowserData assocciated with given peer window.
	*/
	public JRexBrowserData	getBrowserData(int peerWindow);

	/**
	* Invoked to add JRex WindowListener, which helps in hooking up for window create/destroy request.
	*/
	public void 		addJRexWindowListener(WindowListener wl);

	/**
	* Invoked to remove JRex WindowListener.
	*/
	public void 		removeJRexWindowListener();

	/**
	* Invoked to dispose the window manager with all its child windows.
	*/
	public void 		dispose();
}

