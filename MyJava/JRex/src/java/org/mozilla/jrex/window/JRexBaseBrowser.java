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
import java.util.Hashtable;
import java.util.Iterator;
import java.util.ArrayList;
import javax.swing.*;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.ui.*;
import org.mozilla.jrex.event.window.*;
import org.mozilla.jrex.ui.JRexPopupMenu;

/**
* A class implementing the common behavior of all modes in JRexWindowManager.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.window.JRexWindowManager
*/

public abstract class JRexBaseBrowser {
	protected final static String 	className 	= JRexBaseBrowser.class.getName();
	protected final static String 	JREXBROWSER = "JRex - ";
	protected final Hashtable 		windowTable = new Hashtable();
    protected final Dimension 		screenSize	= Toolkit.getDefaultToolkit().getScreenSize();

	protected JComponent 		rootComponent	= null;
	protected Window	  		rootWindow		= null;
	protected boolean	  		rootCreated		= false;
    protected WindowListener	jrexWinListener	= null;

	protected JRexBaseBrowser(){}

	public void init(JComponent comp){
		if(JRexL.on)JRexL.log(className,"**** init()-->comp<"+comp+">");

	}

	public void openNewWindow(int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewWindow()-->parentPeer<"+parentPeer+"> uri<"+uri+"> loadFlags<"+loadFlags+">");
	}

	public void openNewTab(int parentPeer, String uri, int loadFlags){
		if(JRexL.on)JRexL.log(className,"**** openNewTab()-->parentPeer<"+parentPeer+"> uri<"+uri+"> loadFlags<"+loadFlags+">");

	}

	public JRexBrowserData addWindow(JRexCanvas browser, Container parent, Container rootParent, Window window, long chromeFlags){
		if(JRexL.on)JRexL.log(className,"**** addWindow()-->browser<"+browser+"> parent<"+parent+"> chromeFlags<"+chromeFlags+">");
		JRexBrowserData browserData = new JRexBrowserData(browser, parent, rootParent, window, chromeFlags);
		windowTable.put(new Integer(browser.getJRexPeer()),browserData);
		if(jrexWinListener!=null)jrexWinListener.windowCreated(browser.getJRexPeer());
		return browserData;
	}


	public void removeWindow(int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** removeWindow()-->browserPeer<"+browserPeer+">");
		Integer browserPeerInt= new Integer(browserPeer);
		if(windowTable.containsKey(browserPeerInt)){
			if(jrexWinListener!=null)
				jrexWinListener.windowDisposing(browserPeer);
			windowTable.remove(browserPeerInt);
		}
	}

	protected JRexBrowserData setupBrowser(JComponent browserContainer, JComponent rootContainer, java.awt.Window window,
														long chromeFlags, final JRexCanvas browser){
		browserContainer.setLayout(new BorderLayout());
		browserContainer.setBorder(BorderFactory.createEmptyBorder());
		JPanel panel=new JPanel(new BorderLayout());
		panel.setBorder(BorderFactory.createEmptyBorder());//This is important
		panel.add(browser);
		browserContainer.add(panel);

		if((window instanceof Frame) && !window.isDisplayable())
			((Frame)window).setUndecorated((WindowEventConstants.CHROME_TITLEBAR
					& chromeFlags)!=WindowEventConstants.CHROME_TITLEBAR);
		window.pack();//for addnotify
		window.addWindowListener(new java.awt.event.WindowAdapter(){
			public void windowClosing(java.awt.event.WindowEvent we){
				if(JRexL.on)JRexL.log(className,"**** setupBrowser()-->windowClosing AWTWindowEvent<"+we+">****");
				//destroyWindowInternal(we.getWindow(),browser.getJRexPeer());
				Iterator itr=getBrowserForWindow(we.getWindow());
				if(itr.hasNext())
					destroyWindow(((JRexCanvas)itr.next()).getJRexPeer());
			}
		});
		return addWindow(browser,browserContainer,rootContainer,window,chromeFlags);
	}


	protected void dressUP(JComponent mainPanel, JRexBrowserData browserData, int mode){
		JRexCanvas browser = browserData.getBrowser();
		long chromeFlags = browserData.getChromeFlags();

		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding Menubar ****");
		JPanel menuPanel =new JPanel(new BorderLayout());
		if((WindowEventConstants.CHROME_MENUBAR & chromeFlags)==WindowEventConstants.CHROME_MENUBAR){
			JRexMenuBar menuBar=(JRexMenuBar)org.mozilla.jrex.JRexFactory.
										getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_MENUBAR);
			menuBar.setMode(mode);
			menuBar.setBrowser(browser);
			menuPanel.add(menuBar.getMenuBar(),BorderLayout.NORTH);
		}


		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding toolBar ****");
		if((WindowEventConstants.CHROME_TOOLBAR & chromeFlags)==WindowEventConstants.CHROME_TOOLBAR){
			JRexToolBar toolBar=(JRexToolBar)org.mozilla.jrex.JRexFactory.
										getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_TOOLBAR);
			toolBar.setModeAndChrome(mode,chromeFlags);
			toolBar.setBrowser(browser);
			JComponent myToolBar=toolBar.getToolBar();
			if(myToolBar!=null)menuPanel.add(myToolBar);
		}
		if(menuPanel.getComponentCount()>0)
			mainPanel.add(menuPanel,BorderLayout.NORTH);

		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding StatusBar ****");
		if((WindowEventConstants.CHROME_STATUSBAR & chromeFlags)==WindowEventConstants.CHROME_STATUSBAR){
			JRexStatusBar statusBar=(JRexStatusBar)org.mozilla.jrex.JRexFactory.
										getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_STATUSBAR);
			statusBar.setMode(mode);
			statusBar.setBrowser(browser);
			mainPanel.add(statusBar.getStatusBar(),BorderLayout.SOUTH);
		}

		if(JRexL.on)JRexL.log(className,"**** dressUP() --> Adding PopupMenu ****");
		JRexPopupMenu popupMenu=(JRexPopupMenu)org.mozilla.jrex.JRexFactory.
									getInstance().getImplNewInstance(org.mozilla.jrex.JRexFactory.JREX_POPUPMENU);
		popupMenu.setMode(mode);
		popupMenu.setBrowser(browser);
	}

	public int createWindow(int parentPeer, long chromeFlags){
		if(JRexL.on)JRexL.log(className,"**** createWindow()-->parentPeer<"+parentPeer+
															"> chromeFlags<"+chromeFlags+">");
		return 0;
	}

	protected int makeDialog(int parentPeer, long chromeFlags, boolean modal){
		if(JRexL.on)JRexL.log(className,"**** makeDialog()--> parentPeer<"+parentPeer+"> chromeFlags<"+chromeFlags+"> ****");

		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(parentPeer));
		if(JRexL.on)JRexL.log(className,"**** makeDialog()-->parentWindow browserData <"+browserData+">");

		Window parent=browserData!=null?browserData.getWindow():rootWindow;
		if(JRexL.on)JRexL.log(className,"**** makeDialog()--> parent <"+parent+">");

		JDialog dialog =(parent instanceof JDialog)?new JDialog((Dialog)parent,JREXBROWSER,modal)
															:new JDialog((Frame)parent,modal);
		if(JRexL.on)JRexL.log(className,"**** makeDialog()-->JDialog created ****");
		final JRexCanvas browser	= JRexCanvas.createBrowserComponent(chromeFlags);
		JPanel panel 		= new JPanel(new BorderLayout());
		panel.add(browser);
		dialog.setContentPane(panel);
		if(!dialog.isDisplayable())
			dialog.setUndecorated((WindowEventConstants.CHROME_TITLEBAR
								& chromeFlags)!=WindowEventConstants.CHROME_TITLEBAR);
			dialog.pack();//required for addNotify
			dialog.setLocationRelativeTo(parent);
			dialog.addWindowListener(new java.awt.event.WindowAdapter(){
			public void windowClosing(java.awt.event.WindowEvent we){
				if(JRexL.on)JRexL.log(className,"**** makeDialog()-->windowClosing AWTWindowEvent<"+we+">****");
				//destroyWindowInternal(we.getWindow(),browser.getJRexPeer());
				destroyWindow(browser.getJRexPeer());
			}
		});
		addWindow(browser,panel,panel,dialog,chromeFlags);
		if(JRexL.on)JRexL.log(className,"**** makeDialog()-->Done ****");
		return browser.getJRexPeer();
	}


	public void setModal(int browserPeer, final boolean modal){
		if(JRexL.on)JRexL.log(className,"**** setModal()-->browserPeer<"+browserPeer+"> modal<"+modal+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setModal()-->browserData <"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		JRexCanvas browser=browserData.getBrowser();

		final Dialog d=(Dialog)browserData.getWindow();
		if(modal && d.isModal())return;

		EventQueue.invokeLater(new Runnable(){
		  public void run(){
			if(JRexL.on)JRexL.log(className,"**** setModal()-->Setting Modal...");
			d.setModal(modal);
			if(d.isVisible()){
				d.setVisible(false);
				d.setVisible(true);
			}
			if(JRexL.on)JRexL.log(className,"**** setModal()-->Setting Modal done!!!");
		}});
		if(JRexL.on)JRexL.log(className,"**** returning from  setModal()");
	}

	public void setSize(int browserPeer, Dimension dim){
		if(JRexL.on)JRexL.log(className,"**** setSize()-->browserPeer<"+browserPeer+"> dim<"+dim+">");

		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setSize()-->browserData <"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		final JRexCanvas browser=browserData.getBrowser();

		final Window window=browserData.getWindow();
		Insets in=window.getInsets();
		window.setSize(new Dimension(dim.width+in.left+in.right+1,dim.height+in.top+in.bottom+1));
		if(window instanceof Dialog){
			window.setLocationRelativeTo(window.getOwner());
		}else{
			int x=(int)screenSize.width / 2 - dim.width / 2;
			int y=(int)screenSize.height / 2 - dim.height / 2;
			window.setLocation(x<0?0:x,y<0?0:y);
		}
		if(JRexL.on)JRexL.log(className,"**** setSize()--> Setting size and location done!!!!.");
		EventQueue.invokeLater(new Runnable(){
			public void run(){
				window.validate();
				if(JRexL.on)JRexL.log(className,"**** setSize()--> isVisible<"+window.isVisible()+">");
				if(!window.isVisible())
					window.setVisible(true);
				if(JRexL.on)JRexL.log(className,"**** setSize()--> Set cvisible done");
			}
		});
	}

	public void setTitle(int browserPeer, String title){
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->browserPeer<"+browserPeer+"> title<"+title+">");

		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setTitle()-->browserData <"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		JRexCanvas browser=browserData.getBrowser();

		Window window=browserData.getWindow();
		if(window instanceof Frame)
			((Frame)window).setTitle(JREXBROWSER+title);
		else
		if(window instanceof Dialog)
			((Dialog)window).setTitle(JREXBROWSER+title);
		window.validate();
	}


	public void setChromeFlags(int browserPeer, long chromeFlags){
		if(JRexL.on)JRexL.log(className,"**** setChromeFlags()-->browserPeer<"+browserPeer+
																"> chromeFlags<"+chromeFlags+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setChromeFlags()-->browserData <"+browserData+">");
		if(browserData!=null)
			browserData.setChromeFlags(chromeFlags);
	}


	public void setRealized(int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** setRealized()-->browserPeer<"+browserPeer+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** setRealized()-->browserData <"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		browserData.getBrowser().browserRealized();
		if(JRexL.on)JRexL.log(className,"**** setRealized Done !!!");
	}

	public void destroyTab(int browserPeer){
		destroyWindow(browserPeer);
	}

	public void destroyWindow(final int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->browserPeer<"+browserPeer+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->browserData <"+browserData+">");
		assert browserData!=null;
		if(browserData==null)return;
		JRexCanvas browser=browserData.getBrowser();
		final Window window=browserData.getWindow();
		if(JRexL.on)JRexL.log(className,"**** destroyWindow()-->window <"+window+">");

		if(EventQueue.isDispatchThread()){
			destroyWindowInternal(window ,browserPeer);
		}
		else{
			EventQueue.invokeLater(new Runnable(){
			  public void run(){
				  destroyWindowInternal(window ,browserPeer);
			}});
		}
	}

	protected void destroyWindowInternal(final Window window, int browserPeer){
		removeWindow(browserPeer);
		if(JRexL.on)JRexL.log(className,"**** destroyWindowInternal()-->removed browserPeer <"+browserPeer+">");
		window.dispose();
		if(JRexL.on)JRexL.log(className,"**** destroyWindowInternal()-->dispose done");
		if(window==rootWindow &&
			org.mozilla.jrex.JRexFactory.getInstance().getAutoShutdown()){
			try{
				org.mozilla.jrex.JRexFactory.getInstance().shutdownEngine();
			}catch(Exception ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	public JRexCanvas getBrowser(int browserPeer){
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowser()-->browserData <"+browserData+">");
		if(browserData!=null)
			return browserData.getBrowser();
		return null;
	}

	public Iterator getBrowserForWindow(java.awt.Window window){
		if(JRexL.on)JRexL.log(className,"**** getBrowserForWindow()-->window <"+window+">");
		ArrayList list=new ArrayList();
		for(Iterator itr=windowTable.values().iterator();itr.hasNext();){
			JRexBrowserData browserData=(JRexBrowserData)itr.next();
			if(browserData.getWindow()==window)
				list.add(browserData.getBrowser());
		}
		if(JRexL.on)JRexL.log(className,"**** getBrowserForWindow()-->size <"+list.size()+">");
		return list.iterator();
	}

	public Iterator getBrowserForRootParent(java.awt.Container rootParent){
		if(JRexL.on)JRexL.log(className,"**** getBrowserRootParent()-->rootParent <"+rootParent+">");
		ArrayList list=new ArrayList();
		for(Iterator itr=windowTable.values().iterator();itr.hasNext();){
			JRexBrowserData browserData=(JRexBrowserData)itr.next();
			if(browserData.getRootParent()==rootParent)
				list.add(browserData.getBrowser());
		}
		if(JRexL.on)JRexL.log(className,"**** getBrowserRootParent()-->size <"+list.size()+">");
		return list.iterator();
	}

	public JRexCanvas getBrowserForParent(java.awt.Container parent){
		if(JRexL.on)JRexL.log(className,"**** getBrowserForParent()-->parent <"+parent+">");
		for(Iterator itr=windowTable.values().iterator();itr.hasNext();){
			JRexBrowserData browserData=(JRexBrowserData)itr.next();
			if(browserData.getParent()==parent){
				if(JRexL.on)JRexL.log(className,"**** getBrowserForParent()-->MATCHED!!!");
				return browserData.getBrowser();
			}
		}
		return null;
	}

	public Container getBrowserParent(int browserPeer){
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowserParent()-->browserData <"+browserData+">");
		if(browserData!=null)
			return browserData.getParent();
		return null;
	}

	public java.awt.Container getBrowserRootParent(int browserPeer){
		if(JRexL.on)JRexL.log(className,"**** getBrowserRootParent()-->browserPeer <"+browserPeer+">");
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowserRootParent()-->browserData <"+browserData+">");
		if(browserData!=null)
			return browserData.getRootParent();
		return null;
	}

	public Window getBrowserWindow(int browserPeer){
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowserWindow()-->browserData <"+browserData+">");
		if(browserData!=null)
			return browserData.getWindow();
		return null;
	}

	public JRexBrowserData getBrowserData(int browserPeer){
		JRexBrowserData browserData=(JRexBrowserData)windowTable.get(new Integer(browserPeer));
		if(JRexL.on)JRexL.log(className,"**** getBrowserData()-->browserData <"+browserData+">");
		return browserData;
	}


	public void	addJRexWindowListener(WindowListener wl){
		jrexWinListener=wl;
	}


	public void	removeJRexWindowListener(){
		jrexWinListener=null;
	}

	private void disposeInternal(){
		if(JRexL.on)JRexL.log(className,"**** disposeInternal()-->");
		java.util.Iterator windows=windowTable.values().iterator();
		while(windows.hasNext()){
			JRexBrowserData browserData=(JRexBrowserData)windows.next();
			if(JRexL.on)JRexL.log(className,"**** disposeInternal()-->browserData <"+browserData+">");
			Window temp=browserData.getWindow();
			if(!rootCreated && temp==rootWindow){
				rootComponent.removeAll();
			}else{
				temp.removeAll();
				temp.dispose();
			}
		}
	}


	public void dispose(){
		try{
			if(JRexL.on)JRexL.log(className,"**** dispose()--> I AM HERE");
			if(!org.mozilla.jrex.JRexFactory.getInstance().isShutdownHook()){
				if(JRexL.on)JRexL.log(className,"**** dispose()--> not isShutdownHook");
				if(java.awt.EventQueue.isDispatchThread()){
					disposeInternal();
				}else{
					try{
						java.awt.EventQueue.invokeAndWait(new Runnable(){
							public void run(){
								if(JRexL.on)JRexL.log(className,"**** dispose()--> doing invokeAndWait  disposeInternal() ");
								disposeInternal();
								if(JRexL.on)JRexL.log(className,"****dispose()--> invokeAndWait disposeInternal done!!!");
						}});
					}catch(Exception ex){}
				}
			}
		}finally{
			windowTable.clear();
		}
	}
 }

