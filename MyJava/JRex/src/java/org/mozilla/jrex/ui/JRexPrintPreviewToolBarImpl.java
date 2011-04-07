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
import org.mozilla.jrex.log.JRexL;

/**
* An interface representing JRex PrintPreview ToolBar.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class JRexPrintPreviewToolBarImpl implements JRexPrintPreviewToolBar{

	private static final String className		= JRexPrintPreviewToolBarImpl.class.getName();

	private static final String PRINT			= JRexResource.getString("PT_PRINT");
	private static final String PAGE_SETUP		= JRexResource.getString("PT_PAGE_SETUP");
	private static final String PORTRAIT		= JRexResource.getString("PT_PORTRAIT");
	private static final String LANDSCAPE		= JRexResource.getString("PT_LANDSCAPE");
	private static final String CLOSE			= JRexResource.getString("PT_CLOSE");
	private static final String NO_OF_PAGES		= JRexResource.getString("PT_NO_OF_PAGES");

	private static java.util.Hashtable table=new java.util.Hashtable();

	public JRexPrintPreviewToolBarImpl(){}

	public synchronized void show(JRexCanvas browser, Container browserContainer, Window window){
		JRexPrintPreviewToolBarUI impl=(JRexPrintPreviewToolBarUI)table.get(window);
		if(impl==null){
			impl=(window instanceof Frame)?new JRexPrintPreviewToolBarUI(browser,(Frame)window):
											new JRexPrintPreviewToolBarUI(browser, (Dialog)window);
		}
		table.put(window,impl);
		impl.showUI();
	}


	public synchronized void hide(Window window){
		JRexPrintPreviewToolBarUI impl=(JRexPrintPreviewToolBarUI)table.get(window);
		if(impl!=null){
			impl.hideUI();
		}
	}

	private static class JRexPrintPreviewToolBarUI extends JDialog implements ActionListener{
		private JButton printBtn;
		private JButton pageSetupBtn;
		private JButton lpBtn;
		private JButton closeBtn;
		private JLabel label;

		private JRexCanvas browser;
		private Component northComp;
		private boolean isShowing=false;

		JRexPrintPreviewToolBarUI(JRexCanvas browser, Dialog root){
			super(root,"JRex PrintPreview ToolBar",true);
			this.browser=browser;
			createPrintToolBar();
		}

		JRexPrintPreviewToolBarUI(JRexCanvas browser, Frame root){
			super(root,"JRex PrintPreview ToolBar",true);
			this.browser=browser;
			createPrintToolBar();
		}

		private final void createPrintToolBar(){
			Dimension dim=new Dimension(100,25);
			printBtn=new JButton(PRINT);
			printBtn.setPreferredSize(dim);
			printBtn.addActionListener(this);

			pageSetupBtn=new JButton(PAGE_SETUP);
			pageSetupBtn.setPreferredSize(dim);
			pageSetupBtn.addActionListener(this);

			lpBtn= new JButton(LANDSCAPE);
			lpBtn.setPreferredSize(dim);
			lpBtn.addActionListener(this);

			closeBtn=new JButton(CLOSE);
			closeBtn.setPreferredSize(dim);
			closeBtn.addActionListener(this);

			label=new JLabel();
			label.setPreferredSize(dim);
			getContentPane().setLayout(new FlowLayout());
			getContentPane().add(printBtn);
			getContentPane().add(pageSetupBtn);
			getContentPane().add(lpBtn);
			getContentPane().add(label);
			getContentPane().add(closeBtn);
			addWindowListener(new WindowAdapter(){
				public void windowClosing(WindowEvent we){
					hideUI();
				}
			});
		}

		void showUI(){
			if(isShowing)return;
			try{
				label.setText(NO_OF_PAGES+":"+Integer.toString(browser.getPrintPreviewNumPages()));
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			pack();
			isShowing=true;
			setVisible(true);
		}


		void hideUI(){
			if(isShowing){
				try{
					browser.cancelPrintPreview();
				}catch(JRexException ex){
					JRexL.printStackTrace(ex);
				}
				dispose();
			}
			isShowing=false;
			table.remove(getParent());
		}

		public void actionPerformed(ActionEvent ae){
			String action=ae.getActionCommand();
			if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+"> ****");
			try{
				if(action.equals(PRINT)){
					browser.print(true,true);
				}else
				if(action.equals(PAGE_SETUP)){
					browser.pageSetup();
				}else
				if(action.equals(PORTRAIT)){
					lpBtn.setText(LANDSCAPE);
					browser.printPreview(true,false);
					try{
						while(browser.getPrintPreviewNumPages()==0){
							 try{Thread.sleep(50);}catch(Exception ex){}
						}
						label.setText(NO_OF_PAGES+":"+Integer.toString(browser.getPrintPreviewNumPages()));
					}catch(JRexException ex){
						JRexL.printStackTrace(ex);
					}
				}else
				 if(action.equals(LANDSCAPE)){
					lpBtn.setText(PORTRAIT);
					browser.printPreview(true,true);
					try{
						while(browser.getPrintPreviewNumPages()==0){
							 try{Thread.sleep(50);}catch(Exception ex){}
						}
						label.setText(NO_OF_PAGES+":"+Integer.toString(browser.getPrintPreviewNumPages()));
					}catch(JRexException ex){
						JRexL.printStackTrace(ex);
					}
				}else
				 if(action.equals(CLOSE)){
					hideUI();
				}
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
		}

	}
}