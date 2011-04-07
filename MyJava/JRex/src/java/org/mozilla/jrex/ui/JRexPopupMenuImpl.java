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
import java.util.ArrayList;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.navigation.*;
import org.mozilla.jrex.window.JRexWindowManager;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.event.context.*;
import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.dom.JRexDocumentImpl;
import org.mozilla.jrex.dom.events.*;
/**
* Class implementing JRexPopupMenu interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.ui.JRexPopupMenu
*/

public class JRexPopupMenuImpl implements JRexPopupMenu,ActionListener,ContextMenuListener{
	private static final String className		= JRexPopupMenuImpl.class.getName();

	private static final String PM_BACK			= JRexResource.getString("TL_BACK");
	private static final String PM_FORWARD		= JRexResource.getString("TL_FORWARD");
	private static final String PM_RELOAD		= JRexResource.getString("TL_RELOAD");
	private static final String PM_STOP			= JRexResource.getString("TL_STOP");

	private static final String PM_BOOK_MARK	= JRexResource.getString("PM_BOOK_MARK");
	private static final String PM_SAVE_PAGE	= JRexResource.getString("FL_SAVE_PAGE");
	private static final String PM_SEND_PAGE	= JRexResource.getString("FL_SEND_PAGE");
	private static final String PM_PAGE_SRC		= JRexResource.getString("VW_PAGE_SRC");
	private static final String PM_VIEW_BG_IMG	= JRexResource.getString("PM_VIEW_BG_IMG");
	private static final String PM_PAGE_INFO	= JRexResource.getString("TOOL_PAGE_INFO");

	private static final String PM_OPEN_WIN		= JRexResource.getString("PM_OPEN_WIN");
	private static final String PM_OPEN_TAB		= JRexResource.getString("PM_OPEN_TAB");
	private static final String PM_SAVE_LINK	= JRexResource.getString("PM_SAVE_LINK");
	private static final String PM_SEND_LINK	= JRexResource.getString("PM_SEND_LINK");
	private static final String PM_CPY_LINK_LOC	= JRexResource.getString("PM_CPY_LINK_LOC");

	private static final String PM_UNDO			= JRexResource.getString("ED_UNDO");
	private static final String PM_REDO			= JRexResource.getString("ED_REDO");
	private static final String PM_CUT			= JRexResource.getString("ED_CUT");
	private static final String PM_COPY			= JRexResource.getString("ED_COPY");
	private static final String PM_PASTE		= JRexResource.getString("ED_PASTE");
	private static final String PM_DELETE 		= JRexResource.getString("ED_DELETE");
	private static final String PM_SELECT_ALL	= JRexResource.getString("ED_SELECT_ALL");

	private static final String PM_VIEW_IMG		= JRexResource.getString("PM_VIEW_IMG");
	private static final String PM_CPY_IMG_LOC	= JRexResource.getString("PM_CPY_IMG_LOC");
	private static final String PM_CPY_IMG_CONT= JRexResource.getString("PM_CPY_IMG_CONT");
	private static final String PM_SAVE_IMG		= JRexResource.getString("PM_SAVE_IMG");
	private static final String PM_SEND_IMG		= JRexResource.getString("PM_SEND_IMG");
	private static final String PM_SET_WAL_PPER	= JRexResource.getString("PM_SET_WAL_PPER");
	private static final String PM_BLOCK_IMG	= JRexResource.getString("PM_BLOCK_IMG");
	private static final String PM_PROPERTIES	= JRexResource.getString("PM_PROPERTIES");

	private ArrayList linkPopupItems;
	private ArrayList imgPopupItems;
	private ArrayList docPopupItems;
	private ArrayList textPopupItems;

	private JPopupMenu mainPopup =new JPopupMenu("Context Menu");

	private JRexCanvas browser;
	private ContextMenuEvent event;
	private int mode;
	private JRexWindowManager windowManager=((JRexWindowManager)JRexFactory.
												getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER));
	/**
	* Don't use this function to create a JRexToolBar instance use JRexFactory.
	* @see org.mozilla.jrex.JRexFactory
    */
	public JRexPopupMenuImpl(){
	}

	public synchronized void setBrowser(JRexCanvas browser){
		browser.addContextMenuListener(this);
		if(this.browser!=null  && this.browser!=browser)
			this.browser.removeContextMenuListener(this);
		this.browser=browser;
	}

	public void setMode(int mode){
		this.mode=mode;
	}

	private final JMenuItem createMenuItem(String itemCmd){
		JMenuItem menuItem=new JMenuItem(itemCmd);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(itemCmd));
		menuItem.addActionListener(this);
		return menuItem;
	}

	private final void addLinkPopupMenu(){
		if(linkPopupItems==null){
			linkPopupItems=new ArrayList(9);
			linkPopupItems.add(createMenuItem(PM_OPEN_WIN));
			linkPopupItems.add(createMenuItem(PM_OPEN_TAB));
			//linkPopupItems.add(new JPopupMenu.Separator());
			linkPopupItems.add(createMenuItem(PM_BOOK_MARK));
			linkPopupItems.add(createMenuItem(PM_SAVE_LINK));
			linkPopupItems.add(createMenuItem(PM_SEND_LINK));
			linkPopupItems.add(createMenuItem(PM_CPY_LINK_LOC));
			//linkPopupItems.add(new JPopupMenu.Separator());
			linkPopupItems.add(createMenuItem(PM_PROPERTIES));
		}
		int len=linkPopupItems.size();
		for(int i=0;i<len;i++){
			if(i==2 || i==6)
				mainPopup.addSeparator();
			mainPopup.add((JMenuItem)linkPopupItems.get(i));
		}
	}

	private final void addDocumentPopupMenu(boolean isBGImg){
		if(docPopupItems==null){
			docPopupItems=new ArrayList(9);
			docPopupItems.add(createMenuItem(PM_BACK));
			docPopupItems.add(createMenuItem(PM_FORWARD));
			docPopupItems.add(createMenuItem(PM_RELOAD));
			docPopupItems.add(createMenuItem(PM_STOP));
			//docPopupItems.addSeparator();
			docPopupItems.add(createMenuItem(PM_BOOK_MARK));
			docPopupItems.add(createMenuItem(PM_SAVE_PAGE));
			docPopupItems.add(createMenuItem(PM_SEND_PAGE));
			//docPopupItems.addSeparator();
			docPopupItems.add(createMenuItem(PM_VIEW_BG_IMG));
			//docPopupItems.addSeparator();
			docPopupItems.add(createMenuItem(PM_PAGE_SRC));
			docPopupItems.add(createMenuItem(PM_PAGE_INFO));
		}
		int len=docPopupItems.size();
		for(int i=0;i<len;i++){
			if(i==4 || i==7 || i==8)
				mainPopup.addSeparator();
			mainPopup.add((JMenuItem)docPopupItems.get(i));
		}
		((JMenuItem)docPopupItems.get(7)).setEnabled(isBGImg);
	}

	private final void addImagePopupMenu(){
		if(imgPopupItems==null){
			imgPopupItems=new ArrayList(10);
			imgPopupItems.add(createMenuItem(PM_VIEW_IMG));
			imgPopupItems.add(createMenuItem(PM_CPY_IMG_LOC));
			imgPopupItems.add(createMenuItem(PM_CPY_IMG_CONT));
			//imgPopupItems.addSeparator();
			imgPopupItems.add(createMenuItem(PM_SAVE_IMG));
			imgPopupItems.add(createMenuItem(PM_SEND_IMG));
			imgPopupItems.add(createMenuItem(PM_SET_WAL_PPER));
			imgPopupItems.add(createMenuItem(PM_BLOCK_IMG));
			//imgPopupItems.addSeparator();
			imgPopupItems.add(createMenuItem(PM_PROPERTIES));
		}
		int len=imgPopupItems.size();
		for(int i=0;i<len;i++){
			if(i==3 || i==7)
				mainPopup.addSeparator();
			mainPopup.add((JMenuItem)imgPopupItems.get(i));
		}
	}

	private final void addTextAreaPopupMenu(){
		if(textPopupItems==null){
			textPopupItems=new ArrayList(9);
			textPopupItems.add(createMenuItem(PM_UNDO));
			textPopupItems.add(createMenuItem(PM_REDO));
			//textPopupItems.addSeparator();
			textPopupItems.add(createMenuItem(PM_CUT));
			textPopupItems.add(createMenuItem(PM_COPY));
			textPopupItems.add(createMenuItem(PM_PASTE));
			textPopupItems.add(createMenuItem(PM_DELETE));
			//textPopupItems.addSeparator();
			textPopupItems.add(createMenuItem(PM_SELECT_ALL));
		}
		int len=textPopupItems.size();
		for(int i=0;i<len;i++){
			if(i==2 || i==6)
				mainPopup.addSeparator();
			mainPopup.add((JMenuItem)textPopupItems.get(i));
		}
	}

	public void showContextMenu(ContextMenuEvent ce){
		if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->ce <"+ce+"> ****");
		this.event=ce;
		int ctxtFlags=event.getContextFlags();
		if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->ctxtFlags <"+ctxtFlags+"> ****");

		if(mainPopup.isVisible() || ctxtFlags==ContextMenuEventConstants.CONTEXT_NONE)return;

		mainPopup.removeAll();
		if((ctxtFlags & ContextMenuEventConstants.CONTEXT_LINK)
						==ContextMenuEventConstants.CONTEXT_LINK){
				if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->CONTEXT_LINK ****");
			addLinkPopupMenu();
		}

		if((ctxtFlags & ContextMenuEventConstants.CONTEXT_IMAGE)
						==ContextMenuEventConstants.CONTEXT_IMAGE){
			if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->CONTEXT_IMAGE ****");
			addImagePopupMenu();
		}

		if((ctxtFlags & ContextMenuEventConstants.CONTEXT_DOCUMENT)
						==ContextMenuEventConstants.CONTEXT_DOCUMENT){
			boolean isBGImg=((ctxtFlags & ContextMenuEventConstants.CONTEXT_BACKGROUND_IMAGE)
								==ContextMenuEventConstants.CONTEXT_BACKGROUND_IMAGE);
			if(JRexL.on)JRexL.log(className,"**** showContextMenu() --> isBGImg <"+isBGImg+"> CONTEXT_DOCUMENT ****");
			addDocumentPopupMenu(isBGImg);
		}

		if((ctxtFlags & ContextMenuEventConstants.CONTEXT_TEXT)
						==ContextMenuEventConstants.CONTEXT_TEXT){
			if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->CONTEXT_TEXT ****");
			addTextAreaPopupMenu();
		}

		if((ctxtFlags & ContextMenuEventConstants.CONTEXT_INPUT)
						==ContextMenuEventConstants.CONTEXT_INPUT){
			if(JRexL.on)JRexL.log(className,"**** showContextMenu() -->CONTEXT_INPUT ****");
			addDocumentPopupMenu(false);
		}
		EventQueue.invokeLater(new Runnable(){
			public void run(){
				mainPopup.show(browser,event.getClientX(),event.getClientY());
			}
		});
	}

	public void actionPerformed(ActionEvent ae){
		String action=ae.getActionCommand();
		if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+"> event<"+event+"> ****");
		try{
			if(action.equals(PM_BACK)){
				browser.getNavigator().goBack();
			}else
			if(action.equals(PM_FORWARD)){
				browser.getNavigator().goForward();
			}else
			if(action.equals(PM_RELOAD)){
				browser.getNavigator().reload(WebNavigationConstants.LOAD_FLAGS_NONE);
			}else
			 if(action.equals(PM_STOP)){
				browser.getNavigator().stop(WebNavigationConstants.STOP_ALL);
			}else
			 if(action.equals(PM_BOOK_MARK)){

			}else
			 if(action.equals(PM_SAVE_PAGE)){
				JRexDocumentImpl myDoc =(JRexDocumentImpl)browser.getNavigator().getDocument();
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->DOC <"+myDoc+"> ****");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->RANGE <"+myDoc.getDocumentRange()+"> ****");
				JRexEventTargetImpl trgImpl=(JRexEventTargetImpl)myDoc.getEventTarget();
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->TARGET <"+trgImpl+"> ****");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->TARGET NODE <"+trgImpl.getNode()+"> ****");
			}else
			 if(action.equals(PM_SEND_PAGE)){
				//if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->NODE <"+browser.getSelection().getAnchorNode()+"> ****");
				org.w3c.dom.events.MouseEvent mouseEvent = (org.w3c.dom.events.MouseEvent)
                           ((JRexDocumentImpl)browser.getNavigator().getDocument()).getDocumentEvent().createEvent("MouseEvents");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->MouseEvents <"+mouseEvent+"> ****");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->MutationEvents <"+((JRexDocumentImpl)browser.getNavigator().getDocument()).getDocumentEvent().createEvent("MutationEvents")+"> ****");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->Events <"+((JRexDocumentImpl)browser.getNavigator().getDocument()).getDocumentEvent().createEvent("Events")+"> ****");
				if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->View <"+((JRexDocumentImpl)browser.getNavigator().getDocument()).getDocumentView()+"> ****");
			}else
			 if(action.equals(PM_PAGE_SRC)){

			}else
			 if(action.equals(PM_VIEW_BG_IMG)){

			}else
			 if(action.equals(PM_OPEN_WIN)){
				windowManager.openNewWindow(browser.getJRexPeer(),(event!=null?event.getURI():""),WebNavigationConstants.LOAD_FLAGS_NONE);
			}else
			 if(action.equals(PM_OPEN_TAB)){
				Container parent=windowManager.getBrowserParent(browser.getJRexPeer());
				int selIndex=-1;
				if(parent instanceof JTabbedPane){
					selIndex=((JTabbedPane)parent).getSelectedIndex();
				}
				windowManager.openNewTab(browser.getJRexPeer(),
						(event!=null?event.getURI():""),WebNavigationConstants.LOAD_FLAGS_NONE);
				if(selIndex!=-1)
					((JTabbedPane)parent).setSelectedIndex(selIndex);
			}else
			 if(action.equals(PM_SAVE_LINK)){

			}else
			 if(action.equals(PM_SEND_LINK)){
				 String data=event!=null?event.getURI():"";
				browser.getNavigator().loadURI("mailto:?subject="+data+"&body="+data,WebNavigationConstants.LOAD_FLAGS_NONE,null,null,null);
			}else
			 if(action.equals(PM_CPY_LINK_LOC)){
				browser.copyLinkLocation();
			}else
			 if(action.equals(PM_UNDO)){
				browser.undo();
			}else
			 if(action.equals(PM_REDO)){
				browser.redo();
			}else
			 if(action.equals(PM_CUT)){
				 browser.cut();
			}else
			 if(action.equals(PM_COPY)){
				browser.copy();
			}else
			 if(action.equals(PM_PASTE)){
				browser.paste();
			}else
			 if(action.equals(PM_DELETE)){
				browser.delete();
			}else
			 if(action.equals(PM_SELECT_ALL)){
				browser.selectAll();
			}else
			 if(action.equals(PM_VIEW_IMG)){
				browser.copyLinkLocation();
			}else
			 if(action.equals(PM_CPY_IMG_LOC)){
				 browser.copyImageLocation();

			}else
			 if(action.equals(PM_SAVE_IMG)){

			}else
			 if(action.equals(PM_SEND_IMG)){

			}else
			 if(action.equals(PM_SET_WAL_PPER)){

			}else
			 if(action.equals(PM_BLOCK_IMG)){

			}else
			 if(action.equals(PM_PROPERTIES)){

			}
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}
}