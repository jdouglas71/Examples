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

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.navigation.WebNavigationConstants;
import org.mozilla.jrex.window.JRexWindowManager;
import org.mozilla.jrex.window.JRexBrowserData;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.log.JRexL;

/**
* Class implementing JRexMenuBar interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.ui.JRexMenuBar
*/
public class JRexMenuBarImpl implements JRexMenuBar{
	private static final String className 		= JRexMenuBarImpl.class.getName();

	private static final String FL_FILE			= JRexResource.getString("FL_FILE");
	private static final String FL_NEW_WINDOW	= JRexResource.getString("FL_NEW_WINDOW");
	private static final String FL_NEW_TAB		= JRexResource.getString("FL_NEW_TAB");
	private static final String FL_OPEN_FILE	= JRexResource.getString("FL_OPEN_FILE");
	private static final String FL_CLOSE		= JRexResource.getString("FL_CLOSE");
	private static final String FL_CLOSE_TAB	= JRexResource.getString("FL_CLOSE_TAB");
	private static final String FL_CLOSE_WINDOW	= JRexResource.getString("FL_CLOSE_WINDOW");

	private static final String FL_SAVE_PAGE	= JRexResource.getString("FL_SAVE_PAGE");
	private static final String FL_SEND_PAGE	= JRexResource.getString("FL_SEND_PAGE");
	private static final String FL_PAGE_SETUP	= JRexResource.getString("FL_PAGE_SETUP");
	private static final String FL_PRINT_PREVIEW= JRexResource.getString("FL_PRINT_PREVIEW");
	private static final String FL_PRINT		= JRexResource.getString("FL_PRINT");
	private static final String FL_EXIT			= JRexResource.getString("FL_EXIT");

	private static final String ED_EDIT			= JRexResource.getString("ED_EDIT");
	private static final String ED_UNDO			= JRexResource.getString("ED_UNDO");
	private static final String ED_REDO			= JRexResource.getString("ED_REDO");
	private static final String ED_CUT			= JRexResource.getString("ED_CUT");
	private static final String ED_COPY			= JRexResource.getString("ED_COPY");
	private static final String ED_PASTE		= JRexResource.getString("ED_PASTE");
	private static final String ED_DELETE 		= JRexResource.getString("ED_DELETE");
	private static final String ED_SELECT_ALL	= JRexResource.getString("ED_SELECT_ALL");
	private static final String ED_SELECT_NONE	= JRexResource.getString("ED_SELECT_NONE");
	private static final String ED_FIND			= JRexResource.getString("ED_FIND");
	private static final String ED_FIND_AGAIN	= JRexResource.getString("ED_FIND_AGAIN");

	private static final String VW_VIEW			= JRexResource.getString("VW_VIEW");
	private static final String VW_TOOLBARS		= JRexResource.getString("VW_TOOLBARS");
	private static final String VW_TOOL_NAV		= JRexResource.getString("VW_TOOL_NAV");
	private static final String VW_TOOL_BOOKMARK= JRexResource.getString("VW_TOOL_BOOKMARK");
	private static final String VW_TOOL_CUST	= JRexResource.getString("VW_TOOL_CUST");
	private static final String VW_STATUS_BAR	= JRexResource.getString("VW_STATUS_BAR");
	private static final String VW_SIDE_BAR		= JRexResource.getString("VW_SIDE_BAR");
	private static final String VW_SIDE_DOWNLOAD= JRexResource.getString("VW_SIDE_DOWNLOAD");
	private static final String VW_SIDE_BOOKMARK= JRexResource.getString("VW_SIDE_BOOKMARK");
	private static final String VW_SIDE_HISTORY	= JRexResource.getString("VW_SIDE_HISTORY");
	private static final String VW_STOP 		= JRexResource.getString("VW_STOP");
	private static final String VW_RELOAD		= JRexResource.getString("VW_RELOAD");
	private static final String VW_INC_TEXT_SIZE= JRexResource.getString("VW_INC_TEXT_SIZE");
	private static final String VW_DEC_TEXT_SIZE= JRexResource.getString("VW_DEC_TEXT_SIZE");
	private static final String VW_PAGE_SRC		= JRexResource.getString("VW_PAGE_SRC");
	private static final String VW_FULL_SCREEN	= JRexResource.getString("VW_FULL_SCREEN");

	private static final String GO_GO			= JRexResource.getString("GO_GO");
	private static final String GO_BACK			= JRexResource.getString("GO_BACK");
	private static final String GO_FORWARD		= JRexResource.getString("GO_FORWARD");
	private static final String GO_HOME			= JRexResource.getString("GO_HOME");
	private static final String GO_HISTORY		= JRexResource.getString("GO_HISTORY");
	private static final int	GO_DYN_INDEX	= 4;

	private static final String BOOKMARK		= JRexResource.getString("BOOKMARK");
	private static final String ADD_TO_BOOKMARK	= JRexResource.getString("ADD_TO_BOOKMARK");
	private static final String MANAGE_BOOKMARK	= JRexResource.getString("MANAGE_BOOKMARK");

	private static final String TOOLS			= JRexResource.getString("TOOLS");
	private static final String TOOL_JS_CONSOLE = JRexResource.getString("TOOL_JS_CONSOLE");
	private static final String TOOL_PAGE_INFO	= JRexResource.getString("TOOL_PAGE_INFO");
	private static final String TOOL_OPTIONS	= JRexResource.getString("TOOL_OPTIONS");

	private static final String HELP			= JRexResource.getString("HELP");
	private static final String HELP_REL_NOTES	= JRexResource.getString("HELP_REL_NOTES");
	private static final String HELP_ABOUT		= JRexResource.getString("HELP_ABOUT");
	private static final String HELP_OK			= JRexResource.getString("HELP_OK");


	private FileMenuActionListener		fileMenuAL;
	private EditMenuActionListener		editMenuAL;
	private ViewMenuActionListener		viewMenuAL;
	private GoMenuActionListener 		goMenuAL;
	private BookmarksMenuActionListener bookmarksMenuAL;
	private ToolsMenuActionListener 	toolsMenuAL;
	private HelpMenuActionListener 		helpMenuAL;

	private JRexCanvas browser;
	private int mode;
	private JRexWindowManager windowManager=((JRexWindowManager)JRexFactory.
												getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER));

	private JMenuBar menuBar;

	/**
	* Don't use this function to create a JRexToolBar instance use JRexFactory.
	* @see org.mozilla.jrex.JRexFactory
    */
	public JRexMenuBarImpl(){
		fileMenuAL		= new FileMenuActionListener(this);
		editMenuAL		= new EditMenuActionListener(this);
		viewMenuAL		= new ViewMenuActionListener();
		goMenuAL		= new GoMenuActionListener();
		bookmarksMenuAL	= new BookmarksMenuActionListener();
		toolsMenuAL		= new ToolsMenuActionListener();
		helpMenuAL		= new HelpMenuActionListener(this);
	}

	public synchronized void setBrowser(JRexCanvas browser){
		this.browser=browser;
	}

	public void setMode(int mode){
		this.mode=mode;
	}

	public JMenuBar getMenuBar(){
		if(menuBar==null)createMenuBar();
		return menuBar;
	}

	private void createMenuBar(){
		menuBar=new JMenuBar() ;
		menuBar.add(createFileMenu());
		menuBar.add(createEditMenu());
		menuBar.add(createViewMenu());
		menuBar.add(createGoMenu());
		menuBar.add(createBookmarksMenu());
		menuBar.add(createToolsMenu());
		menuBar.add(createHelpMenu());
	}

	private JMenu createFileMenu(){
		JMenu fileMenu=new JMenu(FL_FILE);
		JMenuItem menuItem=new JMenuItem(FL_NEW_WINDOW);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_NEW_WINDOW));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(FL_NEW_WINDOW),ActionEvent.CTRL_MASK));
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_NEW_TAB);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_NEW_TAB));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
										getAcceleratorChar(FL_NEW_TAB),ActionEvent.CTRL_MASK));
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_OPEN_FILE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_OPEN_FILE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(FL_OPEN_FILE),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(fileMenuAL);
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_CLOSE);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_CLOSE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(FL_CLOSE),ActionEvent.CTRL_MASK));
		fileMenu.add(menuItem);


		/*menuItem=new JMenuItem(FL_CLOSE_TAB);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_CLOSE_TAB));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(FL_CLOSE_TAB),ActionEvent.CTRL_MASK));
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_CLOSE_WINDOW);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_CLOSE_WINDOW));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(FL_CLOSE_WINDOW),ActionEvent.CTRL_MASK & ActionEvent.SHIFT_MASK ));
		fileMenu.add(menuItem);*/
		fileMenu.addSeparator();


		menuItem=new JMenuItem(FL_SAVE_PAGE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_SAVE_PAGE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
											getAcceleratorChar(FL_SAVE_PAGE),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(fileMenuAL);
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_SEND_PAGE);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_SEND_PAGE));
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_PAGE_SETUP);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_PAGE_SETUP));
		menuItem.addActionListener(fileMenuAL);
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_PRINT_PREVIEW);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_PRINT_PREVIEW));
		fileMenu.add(menuItem);

		menuItem=new JMenuItem(FL_PRINT);
		menuItem.addActionListener(fileMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_PRINT));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.getAcceleratorChar(FL_PRINT),ActionEvent.CTRL_MASK));
		fileMenu.add(menuItem);
		fileMenu.addSeparator();

		menuItem=new JMenuItem(FL_EXIT);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(FL_EXIT));
		menuItem.addActionListener(fileMenuAL);
		fileMenu.add(menuItem);
		return fileMenu;
	}


	private JMenu createEditMenu(){
		JMenu editMenu=new JMenu(ED_EDIT);
		editMenu.setMnemonic(JRexResource.getMnemonicChar(ED_EDIT));
		JMenuItem menuItem=new JMenuItem(ED_UNDO);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_UNDO));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_UNDO),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);

		menuItem=new JMenuItem(ED_REDO);
		menuItem.addActionListener(editMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_REDO));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_REDO),ActionEvent.CTRL_MASK));
		editMenu.add(menuItem);
		editMenu.addSeparator();

		menuItem=new JMenuItem(ED_CUT);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_CUT));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_CUT),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);

		menuItem=new JMenuItem(ED_COPY);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_COPY));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_COPY),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);


		menuItem=new JMenuItem(ED_PASTE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_PASTE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_PASTE),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);

		menuItem=new JMenuItem(ED_DELETE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_DELETE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_DELETE,0));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);
		editMenu.addSeparator();

		menuItem=new JMenuItem(ED_SELECT_ALL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_SELECT_ALL));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_SELECT_ALL),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);

		menuItem=new JMenuItem(ED_SELECT_NONE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_SELECT_NONE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_SELECT_NONE),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);
		editMenu.addSeparator();

		menuItem=new JMenuItem(ED_FIND);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_FIND));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_FIND),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);

		menuItem=new JMenuItem(ED_FIND_AGAIN);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ED_FIND_AGAIN));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ED_FIND_AGAIN),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(editMenuAL);
		editMenu.add(menuItem);
		return editMenu;
	}

	private JMenu createViewMenu(){
		JMenu viewMenu=new JMenu(VW_VIEW);
		viewMenu.setMnemonic(JRexResource.getMnemonicChar(VW_VIEW));
		JMenu viewToolMenu=new JMenu(VW_TOOLBARS);
		viewToolMenu.setMnemonic(JRexResource.getMnemonicChar(VW_TOOLBARS));
		viewMenu.add(viewToolMenu);

		JMenuItem menuItem=new JCheckBoxMenuItem(VW_TOOL_NAV);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_TOOL_NAV));
		viewToolMenu.add(menuItem);

		menuItem=new JCheckBoxMenuItem(VW_TOOL_BOOKMARK);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_TOOL_BOOKMARK));
		viewToolMenu.add(menuItem);
		viewToolMenu.addSeparator();

		menuItem=new JMenuItem(VW_TOOL_CUST);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_TOOL_CUST));
		menuItem.addActionListener(viewMenuAL);
		viewToolMenu.add(menuItem);

		menuItem=new JCheckBoxMenuItem(VW_STATUS_BAR);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_STATUS_BAR));
		menuItem.addActionListener(viewMenuAL);
		viewMenu.add(menuItem);

		JMenu viewSideBarMenu=new JMenu(VW_SIDE_BAR);
		viewSideBarMenu.setMnemonic(JRexResource.getMnemonicChar(VW_SIDE_BAR));
		viewMenu.add(viewSideBarMenu);
		viewMenu.addSeparator();

		menuItem=new JCheckBoxMenuItem(VW_SIDE_DOWNLOAD);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_SIDE_DOWNLOAD));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_SIDE_DOWNLOAD),ActionEvent.CTRL_MASK));
		viewSideBarMenu.add(menuItem);

		menuItem=new JCheckBoxMenuItem(VW_SIDE_BOOKMARK);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_SIDE_BOOKMARK));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_SIDE_BOOKMARK),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(viewMenuAL);
		viewSideBarMenu.add(menuItem);
		viewMenu.addSeparator();

		menuItem=new JCheckBoxMenuItem(VW_SIDE_HISTORY);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_SIDE_HISTORY));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_SIDE_HISTORY),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(viewMenuAL);
		viewSideBarMenu.add(menuItem);

		menuItem=new JMenuItem(VW_STOP);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_STOP));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE,0));
		menuItem.addActionListener(viewMenuAL);
		viewMenu.add(menuItem);

		menuItem=new JMenuItem(VW_RELOAD);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_RELOAD));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_RELOAD),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(viewMenuAL);
		viewMenu.add(menuItem);
		viewMenu.addSeparator();

		menuItem=new JMenuItem(VW_INC_TEXT_SIZE);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_INC_TEXT_SIZE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_INC_TEXT_SIZE),ActionEvent.CTRL_MASK));
		viewMenu.add(menuItem);

		menuItem=new JMenuItem(VW_DEC_TEXT_SIZE);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_DEC_TEXT_SIZE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_DEC_TEXT_SIZE),ActionEvent.CTRL_MASK));
		viewMenu.add(menuItem);
		viewMenu.addSeparator();

		menuItem=new JMenuItem(VW_PAGE_SRC);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(VW_PAGE_SRC));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(VW_PAGE_SRC),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(viewMenuAL);
		viewMenu.add(menuItem);

		menuItem=new JMenuItem(VW_FULL_SCREEN);
		menuItem.addActionListener(viewMenuAL);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F11,0));
		viewMenu.add(menuItem);
		return viewMenu;
	}


	private JMenu createGoMenu(){
		JMenu goMenu=new JMenu(GO_GO);
		goMenu.setMnemonic(JRexResource.getMnemonicChar(GO_GO));
		JMenuItem menuItem=new JMenuItem(GO_BACK);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(GO_BACK));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_KP_LEFT ,ActionEvent.ALT_MASK));
		menuItem.addActionListener(goMenuAL);
		goMenu.add(menuItem);

		menuItem=new JMenuItem(GO_FORWARD);
		menuItem.addActionListener(goMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(GO_FORWARD));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_KP_RIGHT,ActionEvent.ALT_MASK));
		goMenu.add(menuItem);

		menuItem=new JMenuItem(GO_HOME);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(GO_HOME));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_HOME,ActionEvent.ALT_MASK));
		menuItem.addActionListener(goMenuAL);
		goMenu.add(menuItem);

		goMenu.addSeparator();
		goMenu.addSeparator();

		menuItem=new JMenuItem(GO_HISTORY);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(GO_HISTORY));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(GO_HISTORY),ActionEvent.CTRL_MASK));
		menuItem.addActionListener(goMenuAL);
		goMenu.add(menuItem);
		return goMenu;
	}

	private void addDynamicGoMenu(JMenu goMenu){
		//goMenu.add(menuItem,GO_DYN_INDEX);
	}

	private void removeDynamicGoMenu(JMenu goMenu){

	}

	private JMenu createBookmarksMenu(){
		JMenu bookMarksMenu=new JMenu(BOOKMARK);
		bookMarksMenu.setMnemonic(JRexResource.getMnemonicChar(BOOKMARK));
		JMenuItem menuItem=new JMenuItem(ADD_TO_BOOKMARK);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(ADD_TO_BOOKMARK));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(ADD_TO_BOOKMARK) ,ActionEvent.CTRL_MASK));
		menuItem.addActionListener(bookmarksMenuAL);
		bookMarksMenu.add(menuItem);

		menuItem=new JMenuItem(MANAGE_BOOKMARK);
		menuItem.addActionListener(bookmarksMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(MANAGE_BOOKMARK));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(MANAGE_BOOKMARK),ActionEvent.CTRL_MASK));
		bookMarksMenu.add(menuItem);
		bookMarksMenu.addSeparator();
		addDynamicBookmarksMenu(bookMarksMenu);
		return bookMarksMenu;
	}

	private void addDynamicBookmarksMenu(JMenu bookMarksMenu){

	}


	private JMenu createToolsMenu(){
		JMenu toolsMenu=new JMenu(TOOLS);
		toolsMenu.setMnemonic(JRexResource.getMnemonicChar(TOOLS));
		JMenuItem menuItem=new JMenuItem(TOOL_JS_CONSOLE);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(TOOL_JS_CONSOLE));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(TOOL_JS_CONSOLE) ,ActionEvent.CTRL_MASK));
		menuItem.addActionListener(toolsMenuAL);
		toolsMenu.add(menuItem);

		menuItem=new JMenuItem(TOOL_PAGE_INFO);
		menuItem.addActionListener(toolsMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(TOOL_PAGE_INFO));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(TOOL_PAGE_INFO),ActionEvent.CTRL_MASK));
		toolsMenu.add(menuItem);
		toolsMenu.addSeparator();

		menuItem=new JMenuItem(TOOL_OPTIONS);
		menuItem.addActionListener(toolsMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(TOOL_OPTIONS));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(TOOL_OPTIONS),ActionEvent.CTRL_MASK));
		toolsMenu.add(menuItem);
		return toolsMenu;

	}

	private JMenu createHelpMenu(){
		JMenu helpMenu=new JMenu(HELP);
		helpMenu.setMnemonic(JRexResource.getMnemonicChar(HELP));
		JMenuItem menuItem=new JMenuItem(HELP_REL_NOTES);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(HELP_REL_NOTES));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(HELP_REL_NOTES) ,ActionEvent.CTRL_MASK));
		menuItem.addActionListener(helpMenuAL);
		helpMenu.add(menuItem);

		menuItem=new JMenuItem(HELP_ABOUT);
		menuItem.addActionListener(helpMenuAL);
		menuItem.setMnemonic(JRexResource.getMnemonicChar(HELP_ABOUT));
		menuItem.setAccelerator(KeyStroke.getKeyStroke(JRexResource.
									getAcceleratorChar(HELP_ABOUT),ActionEvent.CTRL_MASK));
		helpMenu.add(menuItem);
		helpMenu.addSeparator();
		return helpMenu;
	}


	private static class FileMenuActionListener implements ActionListener{
		String className =FileMenuActionListener.class.getName();
		JRexMenuBarImpl menuBar;
		FileMenuActionListener(JRexMenuBarImpl menuBar){
			this.menuBar=menuBar;
		}

		public void actionPerformed(ActionEvent ae){
			String action=ae.getActionCommand();
			if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+"> ****");
			try{
				if(action.equals(FL_NEW_WINDOW)){
					menuBar.windowManager.openNewWindow(menuBar.browser.getJRexPeer(),"",WebNavigationConstants.LOAD_FLAGS_NONE);
				}else
				if(action.equals(FL_NEW_TAB)){
					menuBar.windowManager.openNewTab(menuBar.browser.getJRexPeer(),"",WebNavigationConstants.LOAD_FLAGS_NONE);
				}else
				if(action.equals(FL_OPEN_FILE)){
				}else
				 if(action.equals(FL_CLOSE)){
				}else
				 if(action.equals(FL_CLOSE_TAB)){

				}else
				 if(action.equals(FL_CLOSE_WINDOW)){

				}else
				 if(action.equals(FL_SAVE_PAGE)){
					//menuBar.browser.saveURI(menuBar.browser.getNavigator().getCurrentURI().toString(),null,null,null,"C:\\cat.html",null);
					menuBar.browser.saveCurrentDocument("C:\\boot.html","C:\\boot",null,0,0,null);
				}else
				 if(action.equals(FL_SEND_PAGE)){
				}else
				 if(action.equals(FL_PAGE_SETUP)){
					 menuBar.browser.pageSetup();
				}else
				 if(action.equals(FL_PRINT_PREVIEW)){
					 menuBar.browser.printPreview(true,false);
					 boolean isPrev=menuBar.browser.isPrintPreviewing();
					 while(isPrev &&
					 		menuBar.browser.getPrintPreviewNumPages()==0){
						 try{Thread.sleep(100);}catch(Exception ex){}
					 }
					 JRexBrowserData data=menuBar.windowManager.getBrowserData(menuBar.browser.getJRexPeer());
					 ((JRexPrintPreviewToolBar)org.mozilla.jrex.JRexFactory.
					 	getInstance().getImplInstance(JRexFactory.JREX_PRINTPREVIEWTOOLBAR)).show(menuBar.browser,data.getRootParent(),data.getWindow());
				}else
				 if(action.equals(FL_PRINT)){
					menuBar.browser.print(true,true);
				}else
				 if(action.equals(FL_EXIT)){
					org.mozilla.jrex.JRexFactory.getInstance().shutdownEngine();
					System.exit(0);
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	private static class EditMenuActionListener implements ActionListener{
		String className =EditMenuActionListener.class.getName();
		JRexMenuBarImpl menuBar;

		EditMenuActionListener(JRexMenuBarImpl menuBar){
			this.menuBar=menuBar;
		}

		public void actionPerformed(ActionEvent ae){
			String action=ae.getActionCommand();
			if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+"> ****");
			try{
				if(action.equals(ED_UNDO)){
					menuBar.browser.undo();
				}else
				if(action.equals(ED_REDO)){
					menuBar.browser.redo();

				}else
				if(action.equals(ED_CUT)){
					menuBar.browser.cut();
				}else
				 if(action.equals(ED_COPY)){
					 menuBar.browser.copy();
				}else
				 if(action.equals(ED_PASTE)){
					 menuBar.browser.paste();
				}else
				 if(action.equals(ED_DELETE)){
					 menuBar.browser.delete();
				}else
				 if(action.equals(ED_SELECT_ALL)){
					 menuBar.browser.selectAll();
				}else
				 if(action.equals(ED_SELECT_NONE)){
					 menuBar.browser.selectNone();
					 //JRexFindConfig conf=menuBar.browser.getFindConfig();
					 //if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->JRexFindConfig conf<"+conf+"> ****");
				}else
				 if(action.equals(ED_FIND)){
					 JRexFindConfig conf=new JRexFindConfig("to");
					 boolean found=menuBar.browser.find(conf);
					 if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->ED_FIND found<"+found+"> ****");
				}else
				 if(action.equals(ED_FIND_AGAIN)){
					 boolean found=menuBar.browser.findAgain();
					 if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->ED_FIND_AGAIN found<"+found+"> ****");
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}
	}

	private static class ViewMenuActionListener implements ActionListener{
		ViewMenuActionListener(){
		}
		public void actionPerformed(ActionEvent ae){
		}
	}

	private static class GoMenuActionListener implements ActionListener{
		GoMenuActionListener(){
		}
		public void actionPerformed(ActionEvent ae){
		}
	}

	private static class BookmarksMenuActionListener implements ActionListener{
		BookmarksMenuActionListener(){
		}
		public void actionPerformed(ActionEvent ae){
		}
	}

	private static class ToolsMenuActionListener implements ActionListener{
		ToolsMenuActionListener(){
		}
		public void actionPerformed(ActionEvent ae){
		}
	}


	private static class HelpMenuActionListener implements ActionListener{
		JRexMenuBarImpl menuBar;

		HelpMenuActionListener(JRexMenuBarImpl menuBar){
			this.menuBar=menuBar;
		}

		public void actionPerformed(ActionEvent ae){
			String action=ae.getActionCommand();
			if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+"> HELP_ABOUT <"+HELP_ABOUT+"> ****");
			if(action.equals(HELP_ABOUT)){
				Frame frame= (Frame)menuBar.windowManager.getBrowserWindow(menuBar.browser.getJRexPeer());
				final JDialog hlpDlg =new JDialog(frame,"About JRex",true);
				hlpDlg.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
				JPanel panel =new JPanel(new BorderLayout());
				panel.add(new JLabel(JRexResource.getIcon("jrex_main")));
				JButton btn=new JButton(HELP_OK);
				btn.addActionListener(new ActionListener(){
					public void actionPerformed(ActionEvent ae){
						hlpDlg.dispose();
					}
				});
				JPanel btnPanel =new JPanel();
				btnPanel.setBackground(Color.white);
				btn.setBackground(Color.white);
				btnPanel.add(btn);
				panel.add(btnPanel,BorderLayout.SOUTH);
				hlpDlg.setContentPane(panel);
				hlpDlg.pack();
				hlpDlg.setLocationRelativeTo(frame);
				hlpDlg.setVisible(true);
			}
		}
	}
}