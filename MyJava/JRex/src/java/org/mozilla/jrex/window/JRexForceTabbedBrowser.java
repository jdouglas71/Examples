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

import java.awt.*;
import javax.swing.*;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.event.window.*;


/**
* A class implementing the behavior of FORCED_TAB_MODE in JRexWindowManager.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.window.JRexWindowManager
*/

public class JRexForceTabbedBrowser extends  JRexTabbedBrowser{
	private final static String className 	= JRexForceTabbedBrowser.class.getName();

	protected JRexForceTabbedBrowser(){}

	public void openNewWindow(final int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewWindow()-->parentPeer<"+parentPeer+
														"> uri<"+uri+"> loadFlags<"+loadFlags+">");
		openNewTab(parentPeer, uri, loadFlags);
	}

	public void openNewTab(int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewTab()-->parentPeer<"+parentPeer+"> uri<"+uri+"> loadFlags<"+loadFlags+">");
		JRexBrowserData parentBrowserData=(JRexBrowserData)windowTable.get(new Integer(parentPeer));
		if(JRexL.on)JRexL.log(className,"**** openNewTab()--> parentBrowserData <"+parentBrowserData+">");
		assert parentBrowserData!=null;
		if(parentBrowserData==null)return;

		JTabbedPane tabPane = (JTabbedPane)parentBrowserData.getAdditionalData();
		JPanel panel=new JPanel(new BorderLayout());
		panel.setBorder(BorderFactory.createEmptyBorder());
		JRexCanvas browser	= JRexCanvas.createBrowserComponent(WindowEventConstants.CHROME_DEFAULT);
		panel.add(browser);
		tabPane.addTab("[Untitlied]",panel);
		parentBrowserData.getWindow().pack();//for addnotify
		JRexBrowserData browserData = addWindow(browser,parentBrowserData.getParent(),parentBrowserData.getRootParent(),
													parentBrowserData.getWindow(),WindowEventConstants.CHROME_ALL);
		browserData.setAdditionalData(tabPane);
		tabPane.setSelectedIndex(tabPane.getTabCount()-1);
		tabPane.validate();


		try{
			java.net.URI myURI=new java.net.URI(uri);
			browser.getNavigator().loadURI(myURI.toASCIIString() ,loadFlags,null,null,null);
		}catch(Exception uex){
			if(JRexL.on)JRexL.printStackTrace(uex);
		}
	}


	public int createWindow(final int parentPeer, long chromeFlags){
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->parentPeer<"+parentPeer+
															"> chromeFlags<"+chromeFlags+">");
		if((chromeFlags & WindowEventConstants.CHROME_OPENAS_CHROME)
							==WindowEventConstants.CHROME_OPENAS_CHROME){
			boolean isModal=(chromeFlags & WindowEventConstants.CHROME_MODAL)==WindowEventConstants.CHROME_MODAL;
			if(JRexL.on)JRexL.log(className,"**** createWindow()--> ITS A DIALOG!!!! isModal<"+isModal+">");
			return makeDialog(parentPeer, chromeFlags, isModal);
		}else{
			if(JRexL.on)JRexL.log(className,"**** OpenNewTab()-->parentPeer<"+parentPeer+"> chromeFlags<"+chromeFlags+">");
			JRexBrowserData parentBrowserData=(JRexBrowserData)windowTable.get(new Integer(parentPeer));
			if(JRexL.on)JRexL.log(className,"**** OpenNewTab()--> parentBrowserData <"+parentBrowserData+">");
			assert parentBrowserData!=null;
			if(parentBrowserData==null)return 0;

			JTabbedPane tabPane = (JTabbedPane)parentBrowserData.getAdditionalData();
			JPanel panel=new JPanel(new BorderLayout());
			panel.setBorder(BorderFactory.createEmptyBorder());
			JRexCanvas browser	= JRexCanvas.createBrowserComponent(chromeFlags);
			panel.add(browser);
			tabPane.addTab("[Untitlied]",panel);
			parentBrowserData.getWindow().pack();//for addnotify
			JRexBrowserData browserData = addWindow(browser,parentBrowserData.getParent(),parentBrowserData.getRootParent(),
												parentBrowserData.getWindow(),chromeFlags);
			browserData.setAdditionalData(tabPane);
			tabPane.setSelectedIndex(tabPane.getTabCount()-1);
			tabPane.validate();
			return browser.getJRexPeer();
		}
	}
}