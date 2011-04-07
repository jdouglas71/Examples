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

import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.event.window.*;
import org.mozilla.jrex.log.JRexL;

/**
* Class implementing JRexWindowManager interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.window.JRexWindowManager
*/

public class JRexWindowManagerImpl implements JRexWindowManager{

	private final static String className 	= JRexWindowManagerImpl.class.getName();

	private JRexBaseBrowser browser=null;

	/**
	* Don't use this function to create a windomanager instance use JRexFactory.
	* @see org.mozilla.jrex.JRexFactory
    */
	public JRexWindowManagerImpl(){}

	//TO DO INTERNAL_PANE_MODE ??
	public void create(int mode){
		if(JRexL.on)JRexL.log(className,"**** create()--> mode<"+mode+">");
		if(mode<WINDOW_MODE || mode>INTERNAL_PANE_MODE)
			throw new IllegalArgumentException("invalid window mode");
		switch(mode){
			case SINGLE_WINDOW_MODE:
				browser = new JRexSingleWindowBrowser();
				break;

			case TAB_MODE:
				browser = new JRexTabbedBrowser();
				break;

			case FORCED_TAB_MODE:
				browser = new JRexForceTabbedBrowser();
				break;

			case WINDOW_MODE:
			default:
				browser = new JRexWindowBrowser();
				break;
		};
	}

	public void init(javax.swing.JComponent parentComponent){
		if(JRexL.on)JRexL.log(className,"**** init()--> parentComponent<"+parentComponent+">");
		if(browser==null)throw new NullPointerException("browser not created!!!");
		browser.init(parentComponent);
	}

	public void openNewWindow(int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewWindow()-->parentPeer<"+parentPeer+
														"> uri<"+uri+"> loadFlags<"+loadFlags+">");
		if(browser!=null)
			browser.openNewWindow(parentPeer,uri,loadFlags);
	}

	public void openNewTab(int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewTab()-->parentPeer<"+parentPeer+
														"> uri<"+uri+"> loadFlags<"+loadFlags+">");
		if(browser!=null)
			browser.openNewTab(parentPeer,uri,loadFlags);
	}


	public int createWindow(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->event <"+event+"> ****");
		if(browser==null)return 0;
		CreateEventParam wcparam=(CreateEventParam)event.getEventParam();
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->wcparam <"+wcparam+"> ****");
		assert wcparam!=null;
		if(wcparam==null)return 0;
		int parentPeer=wcparam.getParentWindow();
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->parentPeer <"+parentPeer+">");
		return browser.createWindow(parentPeer, wcparam.getChromeFlags());
	}


	public void addWindow(JRexCanvas browserComp, java.awt.Container parent, java.awt.Container rootParent, java.awt.Window window, long chromeFlags){
		if(JRexL.on)JRexL.log(className,"**** addWindow()-->browserComp<"+browserComp+
												"> parent<"+parent+"> rootParent<"+rootParent+"> chromeFlags<"+
												chromeFlags+">");
		if(browser!=null)
			browser.addWindow(browserComp, parent,rootParent, window, chromeFlags);
	}


	public void removeWindow(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** removeWindow()-->peerWindow<"+peerWindow+">");
		if(browser!=null)
			browser.removeWindow(peerWindow);
	}


	public void setModal(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** setModal()-->event <"+event+">");

		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** setModal()-->peerWindow <"+peerWindow+">");
		Boolean modal=(Boolean)event.getEventParam();
		if(JRexL.on)JRexL.log(className,"**** setModal()-->modal <"+modal+">");
		if(browser!=null)
			browser.setModal(peerWindow, modal.booleanValue());
	}


	public void setSize(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** setSize()-->event <"+event+">");
		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** setSize()-->peerWindow <"+peerWindow+">");
		java.awt.Dimension dim=(java.awt.Dimension)event.getEventParam();
		if(JRexL.on)JRexL.log(className,"**** setSize()-->dim <"+dim+">");
		if(browser!=null)
			browser.setSize(peerWindow,dim);
	}


	public void setTitle(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->event <"+event+">");
		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->peerWindow <"+peerWindow+">");
		String  title=(String)event.getEventParam();
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->title <"+title+">");
		if(browser!=null)
			browser.setTitle(peerWindow,title);
	}


	public void setChromeFlags(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** setChromeFlags()-->event <"+event+">");
		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** setChromeFlags()-->peerWindow <"+peerWindow+">");
		Long  chromeFlags=(Long)event.getEventParam();//it Should be long?
		if(JRexL.on)JRexL.log(className,"**** setChromeFlags()-->chromeFlags <"+chromeFlags+">");
		if(browser!=null)
			browser.setChromeFlags(peerWindow,chromeFlags.longValue());
	}


	public void setRealized(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** setRealized()-->event <"+event+">");
		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** setRealized()-->peerWindow <"+peerWindow+">");
		if(browser!=null)
			browser.setRealized(peerWindow);
	}


	public void destroyWindow(WindowEvent event){
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->event <"+event+">");
		int peerWindow=event.getJRexPeer();
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->peerWindow <"+peerWindow+">");
		if(browser!=null)
			browser.destroyWindow(peerWindow);
	}

	public void destroyTab(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** destroyTab()-->peerWindow <"+peerWindow+">");
		if(browser!=null)
			browser.destroyTab(peerWindow);
	}

	public JRexCanvas getBrowser(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** getBrowser()-->peerWindow <"+peerWindow+">");
		return browser!=null?browser.getBrowser(peerWindow):null;
	}

	public java.util.Iterator getBrowserForWindow(java.awt.Window window){
		if(JRexL.on)JRexL.log(className,"**** getBrowserForWindow()-->window <"+window+">");
		return browser!=null?browser.getBrowserForWindow(window):null;
	}

	public java.util.Iterator getBrowserForRootParent(java.awt.Container rootParent){
		if(JRexL.on)JRexL.log(className,"**** getBrowserRootParent()-->rootParent <"+rootParent+">");
		return browser!=null?browser.getBrowserForRootParent(rootParent):null;
	}

	public JRexCanvas getBrowserForParent(java.awt.Container parent){
		if(JRexL.on)JRexL.log(className,"**** getBrowserForParent()-->parent <"+parent+">");
		return browser!=null?browser.getBrowserForParent(parent):null;
	}

	public java.awt.Container getBrowserParent(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** getBrowserParent()-->peerWindow <"+peerWindow+">");
		return browser!=null?browser.getBrowserParent(peerWindow):null;
	}

	public java.awt.Container getBrowserRootParent(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** getBrowserParent()-->peerWindow <"+peerWindow+">");
		return browser!=null?browser.getBrowserParent(peerWindow):null;
	}

	public java.awt.Window getBrowserWindow(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** getBrowserWindow()-->peerWindow <"+peerWindow+">");
		return browser!=null?browser.getBrowserWindow(peerWindow):null;
	}


	public JRexBrowserData getBrowserData(int peerWindow){
		if(JRexL.on)JRexL.log(className,"**** getBrowserData()-->peerWindow <"+peerWindow+">");
		return browser!=null?browser.getBrowserData(peerWindow):null;
	}


	public void	addJRexWindowListener(WindowListener wl){
		if(JRexL.on)JRexL.log(className,"**** addJRexWindowListener()-->wl <"+wl+">");
		if(browser!=null)
			browser.addJRexWindowListener(wl);
	}


	public void	removeJRexWindowListener(){
		if(JRexL.on)JRexL.log(className,"**** removeJRexWindowListener()");
		if(browser!=null)
			browser.removeJRexWindowListener();
	}


	public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose()-->");
		if(browser!=null)
			browser.dispose();
	}
}

