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
import java.awt.event.*;
import java.util.Hashtable;
import javax.swing.*;
import javax.swing.event.*;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.ui.*;
import org.mozilla.jrex.event.window.*;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.navigation.WebNavigationConstants;
import org.mozilla.jrex.exception.JRexException;

/**
* A class implementing the behavior of TAB_MODE in JRexWindowManager.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.window.JRexWindowManager
*/
public class JRexTabbedBrowser extends JRexBaseBrowser implements
											ChangeListener,ActionListener{
	private final static String className 	= JRexTabbedBrowser.class.getName();
	private static final String TB_NEW_TAB		= JRexResource.getString("TB_NEW_TAB");
	private static final String TB_RELOAD_TAB	= JRexResource.getString("TB_RELOAD_TAB");
	private static final String TB_CLOSE_TAB	= JRexResource.getString("TB_CLOSE_TAB");
	private static final String TB_CANCEL	= JRexResource.getString("TB_CANCEL");

	private Hashtable dressTable=new Hashtable();

	protected JRexTabbedBrowser(){}

	public void init(JComponent comp){
		if(JRexL.on)JRexL.log(className,"**** init()-->comp<"+comp+">");
		rootComponent=comp;
		if(rootComponent==null){
			if(JRexL.on)JRexL.log(className,"**** init()-->rootComponent is null ");
			JFrame frame=new JFrame(JREXBROWSER);
			frame.setIconImage(org.mozilla.jrex.ui.JRexResource.getIcon("jrex").getImage());
			rootComponent=new JPanel();
			frame.setContentPane(rootComponent);
			rootWindow=frame;
			rootCreated=true;
		}else
			rootWindow=SwingUtilities.windowForComponent(rootComponent);

		rootComponent.setLayout(new BorderLayout());

		JPanel panel=new JPanel();
		final JTabbedPane tabPane=new JTabbedPane();
		final JPopupMenu pMenu=createTabPopupMenu();
		tabPane.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(MouseEvent e) {
				handleIt(e);
			}
            public void mouseReleased(MouseEvent e) {
				handleIt(e);
			}
			private final void handleIt(MouseEvent e){
				if (e.isPopupTrigger()) {
					closeItem.setEnabled(tabPane.getTabCount()>1);
					pMenu.show(tabPane, e.getX(), e.getY());
				}
			}
        });
		tabPane.addChangeListener(this);
		tabPane.addTab("[Untitlied]",panel);
		rootComponent.add(tabPane);
		JRexCanvas browser	= JRexCanvas.createBrowserComponent(WindowEventConstants.CHROME_DEFAULT);
		JRexBrowserData browserData = setupBrowser(panel, rootComponent, rootWindow, WindowEventConstants.CHROME_ALL, browser);
		browserData.setAdditionalData(tabPane);
		dressUP(rootComponent, browserData,JRexWindowManager.TAB_MODE);
		if(JRexL.on)JRexL.log(className,"**** init()-->Dressup Done!!");
		tabPane.addTab("[Untitlied]",new JPanel());//Java 1.5 Hack
		tabPane.setSelectedIndex(1);//Java 1.5 Hack

		EventQueue.invokeLater(new Runnable(){
			public void run(){
				if(rootCreated)
					((Frame)rootWindow).setExtendedState(Frame.MAXIMIZED_BOTH);
				if(!rootWindow.isVisible()){
					rootWindow.setVisible(true);
				}else
					rootWindow.validate();
				if(JRexL.on)JRexL.log(className,"**** init()--> Set visible Done!!");
				tabPane.removeTabAt(1);//Java 1.5 Hack
			}
		});
		if(JRexL.on)JRexL.log(className,"**** init()--> Done!!");
	}

	JMenuItem closeItem;
	private JPopupMenu createTabPopupMenu(){
		JPopupMenu mainPopupMenu =new JPopupMenu();
		mainPopupMenu.setLightWeightPopupEnabled(false);
		JMenuItem item=createMenuItem(TB_NEW_TAB);
		mainPopupMenu.add(item);
		mainPopupMenu.addSeparator();
		item=createMenuItem(TB_RELOAD_TAB);
		mainPopupMenu.add(item);
		closeItem=item=createMenuItem(TB_CLOSE_TAB);
		mainPopupMenu.add(item);
		mainPopupMenu.addSeparator();
		item=createMenuItem(TB_CANCEL);
		mainPopupMenu.add(item);
		return mainPopupMenu;
	}

	private final JMenuItem createMenuItem(String itemCmd){
		JMenuItem menuItem=new JMenuItem(itemCmd);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(itemCmd));
		menuItem.addActionListener(this);
		return menuItem;
	}

	protected void dressUP(JComponent mainPanel, JRexBrowserData browserData, int mode){
		JRexCanvas browser = browserData.getBrowser();
		long chromeFlags = browserData.getChromeFlags();

		Dress dress=(Dress)dressTable.get(browserData.getWindow());
		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Checking for Dress ****");
		if(dress==null){
			if(JRexL.on)JRexL.log(className,"**** dressUP() --> Creating new Dress ****");
			JRexToolBar toolBar=null;
			if((WindowEventConstants.CHROME_TOOLBAR & chromeFlags)==WindowEventConstants.CHROME_TOOLBAR){
				toolBar=(JRexToolBar)org.mozilla.jrex.JRexFactory.
											getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_TOOLBAR);
				toolBar.setModeAndChrome(mode,chromeFlags);
				toolBar.setBrowser(browser);
			}
			JRexMenuBar menuBar=null;
			if((WindowEventConstants.CHROME_MENUBAR & chromeFlags)==WindowEventConstants.CHROME_MENUBAR){
				menuBar=(JRexMenuBar)org.mozilla.jrex.JRexFactory.
											getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_MENUBAR);
				menuBar.setBrowser(browser);
				menuBar.setMode(mode);
			}
			JRexStatusBar statusBar=null;
			if((WindowEventConstants.CHROME_STATUSBAR & chromeFlags)==WindowEventConstants.CHROME_STATUSBAR){
				statusBar=(JRexStatusBar)org.mozilla.jrex.JRexFactory.
											getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_STATUSBAR);
				statusBar.setBrowser(browser);
				statusBar.setMode(mode);
			}

			JRexPopupMenu popupMenu=(JRexPopupMenu)org.mozilla.jrex.JRexFactory.
										getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_POPUPMENU);
			popupMenu.setMode(mode);
			popupMenu.setBrowser(browser);

			dress=new Dress(toolBar,menuBar,statusBar,popupMenu);
			dressTable.put(browserData.getWindow(), dress);
			if(JRexL.on)JRexL.log(className,"**** dressUP() --> Creating new Dress Done****");

		}
		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding Menubar ****");
		JPanel menuPanel =new JPanel(new BorderLayout());
		if((WindowEventConstants.CHROME_MENUBAR & chromeFlags)==WindowEventConstants.CHROME_MENUBAR){
			menuPanel.add(dress.getMenuBar().getMenuBar(),BorderLayout.NORTH);
			dress.getMenuBar().setBrowser(browser);
		}

		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding toolBar ****");
		if((WindowEventConstants.CHROME_TOOLBAR & chromeFlags)==WindowEventConstants.CHROME_TOOLBAR){
			JComponent myToolBar=dress.getToolBar().getToolBar();
			dress.getToolBar().setBrowser(browser);
			if(myToolBar!=null)menuPanel.add(myToolBar);
		}
		if(menuPanel.getComponentCount()>0)
			mainPanel.add(menuPanel,BorderLayout.NORTH);

		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding StatusBar ****");
		if((WindowEventConstants.CHROME_STATUSBAR & chromeFlags)==WindowEventConstants.CHROME_STATUSBAR){
			mainPanel.add(dress.getStatusBar().getStatusBar(),BorderLayout.SOUTH);
			dress.getStatusBar().setBrowser(browser);
		}
		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding PopupMenu ****");
	 	dress.getPopupMenu().setBrowser(browser);
	}


	public void openNewWindow(final int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewWindow()-->parentPeer<"+parentPeer+
														"> uri<"+uri+"> loadFlags<"+loadFlags+">");
		final JFrame frame=new JFrame(JREXBROWSER);
		frame.setIconImage(org.mozilla.jrex.ui.JRexResource.getIcon("jrex").getImage());
		JPanel mainPanel=new JPanel(new BorderLayout());
		mainPanel.setBorder(BorderFactory.createEmptyBorder());
		frame.setContentPane(mainPanel);

		final JTabbedPane tabPane=new JTabbedPane();
		final JPopupMenu pMenu=createTabPopupMenu();
		tabPane.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(MouseEvent e) {
				handleIt(e);
			}
            public void mouseReleased(MouseEvent e) {
				handleIt(e);
			}
			private final void handleIt(MouseEvent e){
				if (e.isPopupTrigger()) {
					closeItem.setEnabled(tabPane.getTabCount()>1);
					pMenu.show(tabPane, e.getX(), e.getY());
				}
			}
        });
		tabPane.addChangeListener(this);
		JPanel panel=new JPanel();
		tabPane.addTab("[Untitlied]",panel);
		mainPanel.add(tabPane);
		JRexCanvas browser	= JRexCanvas.createBrowserComponent(WindowEventConstants.CHROME_DEFAULT);
		JRexBrowserData browserData = setupBrowser(panel, mainPanel, frame, WindowEventConstants.CHROME_ALL, browser);
		browserData.setAdditionalData(tabPane);
		dressUP(mainPanel, browserData,JRexWindowManager.TAB_MODE);
		if(JRexL.on)JRexL.log(className,"**** OpenNewWindow()-->Dressup Done!!");
		tabPane.addTab("[Untitlied]",new JPanel());//Java 1.5 Hack
		tabPane.setSelectedIndex(1);//Java 1.5 Hack

		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(parentPeer));
			if(JRexL.on)JRexL.log(className,"**** OpenNewWindow()-->parentWindow browserData <"+browserData+">");
			Window parent=browserData!=null?browserData.getWindow():rootWindow;
			if(JRexL.on)JRexL.log(className,"**** OpenNewWindow()--> parent <"+parent+">");
			if(parent!=null)
				frame.setLocationRelativeTo(parent);
			frame.setExtendedState(Frame.MAXIMIZED_BOTH);
			frame.setVisible(true);
			tabPane.removeTabAt(1);//Java 1.5 Hack
		}});
		try{
			java.net.URI myURI=new java.net.URI(uri);
			browser.getNavigator().loadURI(myURI.toASCIIString() ,loadFlags,null,null,null);
		}catch(Exception uex){
			if(JRexL.on)JRexL.printStackTrace(uex);
		}
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
		JRexBrowserData browserData = addWindow(browser, panel, parentBrowserData.getParent(),parentBrowserData.getWindow(),
														WindowEventConstants.CHROME_ALL);
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


	public int createWindow(final int parentPeer, long chromeFlags ){
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->parentPeer<"+parentPeer+"> chromeFlags<"+chromeFlags+">");
		if((chromeFlags & WindowEventConstants.CHROME_OPENAS_CHROME)
							==WindowEventConstants.CHROME_OPENAS_CHROME){
			boolean isModal=(chromeFlags & WindowEventConstants.CHROME_MODAL)==WindowEventConstants.CHROME_MODAL;
			if(JRexL.on)JRexL.log(className,"**** createWindow()--> ITS A DIALOG!!!! isModal<"+isModal+">");
			return makeDialog(parentPeer, chromeFlags, isModal);
		}else{
			if(JRexL.on)JRexL.log(className,"**** createWindow()--> ITS A FRAME!!!!");
			final JFrame frame=new JFrame(JREXBROWSER);
			frame.setIconImage(org.mozilla.jrex.ui.JRexResource.getIcon("jrex").getImage());
			JPanel mainPanel=new JPanel(new BorderLayout());
			mainPanel.setBorder(BorderFactory.createEmptyBorder());
			frame.setContentPane(mainPanel);

			final JTabbedPane tabPane=new JTabbedPane();
			final JPopupMenu pMenu=createTabPopupMenu();
			tabPane.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mousePressed(MouseEvent e) {
					handleIt(e);
				}
				public void mouseReleased(MouseEvent e) {
					handleIt(e);
				}
				private final void handleIt(MouseEvent e){
					if (e.isPopupTrigger()) {
						closeItem.setEnabled(tabPane.getTabCount()>1);
						pMenu.show(tabPane, e.getX(), e.getY());
					}
				}
			});
			tabPane.addChangeListener(this);
			JPanel panel=new JPanel();
			tabPane.addTab("[Untitlied]",panel);
			mainPanel.add(tabPane);

			JRexCanvas browser	= JRexCanvas.createBrowserComponent(chromeFlags);
			JRexBrowserData browserData = setupBrowser(panel, mainPanel, frame,chromeFlags, browser);
			browserData.setAdditionalData(tabPane);
			dressUP(mainPanel, browserData,JRexWindowManager.TAB_MODE);
			if(JRexL.on)JRexL.log(className,"**** createWindow()-->Dressup Done!!");
			tabPane.addTab("[Untitlied]",new JPanel());//Java 1.5 Hack
			tabPane.setSelectedIndex(1);//Java 1.5 Hack

			EventQueue.invokeLater(new Runnable(){
			  public void run(){
				JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(parentPeer));
				if(JRexL.on)JRexL.log(className,"**** createWindow()-->parentWindow browserData <"+browserData+">");
				Window parent=browserData!=null?browserData.getWindow():rootWindow;
				if(JRexL.on)JRexL.log(className,"**** createWindow()--> parent <"+parent+">");
				if(parent!=null)
					frame.setLocationRelativeTo(parent);
				frame.setExtendedState(Frame.MAXIMIZED_BOTH);
				frame.setVisible(true);
				tabPane.removeTabAt(1);//Java 1.5 Hack
			}});
			return browser.getJRexPeer();
		}
	}

	public void setTitle(int browserPeer, final String title){
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->browserPeer<"+browserPeer+"> title<"+title+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->browserData<"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		if(!(browserData.getWindow() instanceof Dialog)){
			final JTabbedPane tabPane = (JTabbedPane)browserData.getAdditionalData();
			final int index=getTabIndex(tabPane, browserPeer);
			if(JRexL.on)JRexL.log(className,"**** setTitle()-->index<"+index+">");
			assert index!=-1;
			if(index==-1)return;
			EventQueue.invokeLater(new Runnable(){
			  public void run(){
			tabPane.setTitleAt(index,title);
			}});
			if(index==tabPane.getSelectedIndex())
				super.setTitle(browserPeer, title);
		}else
			super.setTitle(browserPeer, title);
	}

	public void destroyWindow(final int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->browserPeer<"+browserPeer+">");
		final JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->browserData<"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		if(!(browserData.getWindow() instanceof Dialog)){
			JTabbedPane tabPane = (JTabbedPane)browserData.getAdditionalData();
			tabPane.removeChangeListener(this);
			while(tabPane.getTabCount()>0){
				JRexCanvas browser=getBrowserForParent((JPanel)tabPane.getComponentAt(0));
				if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->destroying tab with browserPeer<"+browser.getJRexPeer()+">");
				destroyTab(browser.getJRexPeer());
			}
		}
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->tabPane removeAll() done!!!");
		if(EventQueue.isDispatchThread()){
			destroyWindowInternal(browserData.getWindow(),browserPeer);
		}
		else{
			EventQueue.invokeLater(new Runnable(){
			  public void run(){
				  destroyWindowInternal(browserData.getWindow(),browserPeer);
			}});
		}
	}

	public void destroyTab(int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** destroyTab()-->browserPeer<"+browserPeer+">");
		final JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** destroyTab()-->browserData<"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		JTabbedPane tabPane = (JTabbedPane)browserData.getAdditionalData();
		int index=getTabIndex(tabPane,browserPeer);
		if(JRexL.on)JRexL.log(className,"**** destroyTab()-->index<"+index+">");
		removeWindow(browserPeer);
		if(index>-1)tabPane.remove(index);
	}

	public Container getBrowserParent(int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** getBrowserParent()-->browserPeer<"+browserPeer+">");
		final JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowserParent()-->browserData<"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return null;
		return (Container)browserData.getAdditionalData();
	}

	private final int getTabIndex(JTabbedPane tabPane, int browserPeer){
		int tabCount=tabPane.getTabCount();
		if(JRexL.on)JRexL.log(className,"**** getTabIndex()-->tabCount<"+tabCount+">");
		for(int i=0;i<tabCount;i++){
			JRexCanvas temp=getBrowserForParent((JPanel)tabPane.getComponentAt(i));
			if(JRexL.on)JRexL.log(className,"**** getTabIndex()-->temp<"+temp+">");
			if(temp!=null && browserPeer==temp.getJRexPeer())
				return i;
		}
		return -1;
	}

	public void stateChanged(ChangeEvent e){
		JTabbedPane tabPane = (JTabbedPane)e.getSource();
		int index=tabPane.getSelectedIndex();
		if(JRexL.on)JRexL.log(className,"**** stateChanged()-->index <"+index+">");
		if(index<0)return;
		Component root=SwingUtilities.windowForComponent(tabPane);
		if(root instanceof Frame)
			((Frame)root).setTitle(tabPane.getTitleAt(index));
		else
		if(root instanceof Dialog)
			((Dialog)root).setTitle(tabPane.getTitleAt(index));

		int tabCount=tabPane.getTabCount();
		JRexCanvas browser = getBrowserForParent((JPanel)tabPane.getComponentAt(index));
		if(JRexL.on)JRexL.log(className,"**** stateChanged()--> tabCount <"+tabCount+"> browser <"+browser+">");

		if(browser!=null){
			java.awt.Window window=getBrowserWindow(browser.getJRexPeer());
			Dress dress =(Dress)dressTable.get(window);
			if(dress!=null){
				if(dress.getToolBar()!=null)dress.getToolBar().setBrowser(browser);
				if(dress.getMenuBar()!=null)dress.getMenuBar().setBrowser(browser);
				if(dress.getStatusBar()!=null)dress.getStatusBar().setBrowser(browser);
				if(dress.getPopupMenu()!=null)dress.getPopupMenu().setBrowser(browser);
			}
		}
	}

	public void actionPerformed(ActionEvent ae){
		String action=ae.getActionCommand();
		if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+">  ****");
		try{
			JTabbedPane tabPane= (JTabbedPane)((JPopupMenu)((Component)ae.getSource()).getParent()).getInvoker();
			int index=tabPane.getSelectedIndex();
			if(JRexL.on)JRexL.log(className,"**** actionPerformed()-->index<"+index+">");
			if(index<0)return;
			if(action.equals(TB_NEW_TAB)){
				JRexCanvas temp=getBrowserForParent((JPanel)tabPane.getComponentAt(index));
				if(temp==null)return;
				((JRexWindowManager)JRexFactory.getInstance().
					getImplInstance(JRexFactory.WINDOW_MANAGER)).
						openNewTab(temp.getJRexPeer(),"",WebNavigationConstants.LOAD_FLAGS_NONE);
			}else
			if(action.equals(TB_RELOAD_TAB)){
				JRexCanvas temp=getBrowserForParent((JPanel)tabPane.getComponentAt(index));
				if(temp!=null)temp.getNavigator().reload(WebNavigationConstants.LOAD_FLAGS_NONE);
			}else
			if(action.equals(TB_CLOSE_TAB)){
				JRexCanvas temp=getBrowserForParent((JPanel)tabPane.getComponentAt(index));
				if(temp!=null)destroyTab(temp.getJRexPeer());
			}
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	private static class Dress{
		private JRexToolBar toolBar;
		private JRexMenuBar menuBar;
		private JRexStatusBar statusBar;
		private JRexPopupMenu popupMenu;

		private Dress(JRexToolBar toolBar, JRexMenuBar menuBar, JRexStatusBar statusBar, JRexPopupMenu popupMenu){
			this.toolBar=toolBar;
			this.menuBar=menuBar;
			this.statusBar=statusBar;
			this.popupMenu=popupMenu;
		}

		private JRexToolBar getToolBar(){
			return toolBar;
		}

		private JRexMenuBar getMenuBar(){
			return menuBar;
		}

		private JRexStatusBar getStatusBar(){
			return statusBar;
		}

		private JRexPopupMenu getPopupMenu(){
			return popupMenu;
		}

	}
}

