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
import javax.swing.text.*;
import java.io.*;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.navigation.*;
import org.mozilla.jrex.event.window.WindowEventConstants;
import org.mozilla.jrex.event.history.*;
import org.mozilla.jrex.log.JRexL;

/**
* Class implementing JRexToolBar interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.ui.JRexToolBar
*/
public class JRexToolBarImpl implements JRexToolBar,ActionListener,HistoryListener{
	private static final String className	= JRexToolBarImpl.class.getName();
	private static final String homeUrl		= "about:blank";
	private static final String TL_BACK		= JRexResource.getString("TL_BACK");
	private static final String TL_FORWARD	= JRexResource.getString("TL_FORWARD");
	private static final String TL_RELOAD	= JRexResource.getString("TL_RELOAD");
	private static final String TL_STOP		= JRexResource.getString("TL_STOP");
	private static final String TL_HOME		= JRexResource.getString("TL_HOME");
	private static final String TL_PRINT	= JRexResource.getString("TL_PRINT");
	private static final String TL_GO		= JRexResource.getString("TL_GO");
	private static final String LOC_ACT_CMD	= "LOC_ACT_CMD";

	private JButton 	back;
	private JButton 	forward;
	private JButton 	reload;
	private JButton 	stop;
	private JButton		home;
	private JButton 	print;
	private JButton 	go;
	private JComboBox	locationCombo;
	private JTextComponent	locComboEditor;

	private JRexCanvas browser;
	private long chromeFlags;
	private JComponent toolBar;
	private boolean    toolBarCreated=false;

	/**
	* Don't use this function to create a JRexToolBar instance use JRexFactory.
	* @see org.mozilla.jrex.JRexFactory
    */
	public JRexToolBarImpl(){
	}

	public void setModeAndChrome(int mode, long chromeFlags){
		this.chromeFlags=chromeFlags;
	}

	public synchronized void setBrowser(JRexCanvas browser){
		browser.addHistoryListener(this);
		if(this.browser!=null && this.browser!=browser)
			this.browser.removeHistoryListener(this);
		this.browser=browser;
		if(locationCombo!=null){
			locationCombo.removeActionListener(this);
			History his=null;
			try{
				his=browser.getNavigator().getSessionHistory();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			if(JRexL.on)JRexL.log(className,"**** setBrowser() -->his <"+his+">****");
			if(his!=null){
				java.util.Iterator iterator=his.elements().iterator();
				while(iterator.hasNext()){
					HistoryEntry item=(HistoryEntry)iterator.next();
					if(JRexL.on)JRexL.log(className,"**** setBrowser() -->item <"+item+">****");
					if(((DefaultComboBoxModel)locationCombo.getModel()).getIndexOf(item.getURI())<0)
						locationCombo.addItem(item.getURI());
				}
			}
			String currURI="";
			try{
				java.net.URI temp=browser.getNavigator().getCurrentURI();
				currURI=temp==null?"":temp.toString();
			}catch(JRexException ex){
				JRexL.printStackTrace(ex);
			}
			if(JRexL.on)JRexL.log(className,"**** setBrowser() -->currURI <"+currURI+">****");
			locationCombo.setSelectedItem(currURI);
			locationCombo.addActionListener(this);
		}
	}

	public JComponent getToolBar(){
		if(!toolBarCreated)createToolBar();
		return toolBar;
	}

	private void createToolBar(){
		toolBarCreated=true;
		GridBagLayout gbl		= new GridBagLayout();
		GridBagConstraints gbc	= new GridBagConstraints();
		JPanel panel 			= new JPanel(gbl);
		panel.setPreferredSize(new Dimension(200,32));
		int i=0;
		Insets inset=new Insets(0,6,0,0);
		if((WindowEventConstants.CHROME_TOOLBAR & chromeFlags)==WindowEventConstants.CHROME_TOOLBAR){
			addCompToGridBag((back=createButton(TL_BACK)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
			addCompToGridBag((forward=createButton(TL_FORWARD)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
			addCompToGridBag((reload=createButton(TL_RELOAD)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
			addCompToGridBag((stop = createButton(TL_STOP)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
			addCompToGridBag((home=createButton(TL_HOME)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
			addCompToGridBag((print=createButton(TL_PRINT)),panel ,gbc,gbl,i++, 0, 1, 1,0,0,
						GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
		}

		if((WindowEventConstants.CHROME_LOCATIONBAR & chromeFlags)==WindowEventConstants.CHROME_LOCATIONBAR){
			locationCombo=new JComboBox();
			locComboEditor=(JTextComponent)locationCombo.getEditor().getEditorComponent();
			locationCombo.setEditable(true);
			locationCombo.setPreferredSize(new Dimension(200,22));
			locationCombo.addActionListener(this);
			locationCombo.setActionCommand(LOC_ACT_CMD);
			Insets cinset=new Insets(10,10,0,0);
			addCompToGridBag(locationCombo,panel ,gbc,gbl,i++, 0, 1, 1,1,0,
					GridBagConstraints.WEST ,GridBagConstraints.HORIZONTAL,cinset,0,0);
			go=createButton(TL_GO);
			Insets ginset=new Insets(10,2,0,2);
			go.setPreferredSize(new Dimension(22,22));
			addCompToGridBag(go,panel ,gbc,gbl,i++, 0, 1, 1,0,0,
					GridBagConstraints.WEST ,GridBagConstraints.NONE,ginset,0,0);
		}

		if((WindowEventConstants.CHROME_PERSONAL_TOOLBAR & chromeFlags)==WindowEventConstants.CHROME_PERSONAL_TOOLBAR){
			//add personal tool bar here
		}
		toolBar=(panel.getComponentCount()<1)?null:panel;
	}

	private JButton createButton(String name){
		JButton b=new JButton(org.mozilla.jrex.ui.JRexResource.getIcon(name));
		b.setActionCommand(name);
		b.setToolTipText(name);
		b.setPreferredSize(new Dimension(30,30));
		b.setBorderPainted(false);
		b.setFocusable(false);
		b.addActionListener(this);
		return b;
	}

	private static final void addCompToGridBag(Component comp,JPanel panel,GridBagConstraints gbc,GridBagLayout gbl,int gx, int gy, int gw, int gh, double wx, double wy, int anchor, int fill, Insets i, int ix, int iy){
		gbc.gridx=gx;gbc.gridy=gy;
		gbc.gridwidth=gw;gbc.gridheight=gh;
		gbc.weightx=wx;gbc.weighty=wy;
		gbc.anchor=anchor;
		gbc.fill=fill;
		gbc.insets=i;
		gbc.ipadx=ix;gbc.ipady=iy;
		gbl.setConstraints(comp,gbc);
		panel.add(comp);
	}

	private final void processRequest()throws JRexException{
		/*try{
		//InputStream test. does not work
		String url="http://www.mozilla.org/htdig-cgi/htsearch";
		ByteArrayInputStream binp=new ByteArrayInputStream("config=htdig&restrict=&exclude=&words=embedding&method=and&format=builtin-long".getBytes());
		ByteArrayInputStream binh=new ByteArrayInputStream("Content-Type: application/x-www-form-urlencoded\r\n".getBytes());
		browser.getNavigator().loadURI(url.trim(),WebNavigationConstants.LOAD_FLAGS_NONE,null,binp,binh);
		//browser.getNavigator().loadURI(url.trim(),WebNavigationConstants.LOAD_FLAGS_NONE,null,binp,binh);
		}catch(Exception ex){
			ex.printStackTrace();
		}*/
		String url=locComboEditor.getText();
		if(JRexL.on)JRexL.log(className,"**** processRequest() -->url <"+url+">****");
		if((url=url.trim())=="")return;
		try{
			java.net.URI myURI=new java.net.URI(url);
			browser.getNavigator().loadURI(myURI.toASCIIString() ,WebNavigationConstants.LOAD_FLAGS_NONE,null,null,null);
		}catch(java.net.URISyntaxException uex){
			if(JRexL.on)JRexL.printStackTrace(uex);
		}
	}

	public void actionPerformed(ActionEvent ae){
		String action=ae.getActionCommand();
		if(JRexL.on)JRexL.log(className,"**** actionPerformed() -->action <"+action+">****");
		try{
			if(action.equals(TL_BACK)){
				browser.getNavigator().goBack();
			}else
			if(action.equals(TL_FORWARD)){
				browser.getNavigator().goForward();
			}else
			if(action.equals(TL_RELOAD)){
				browser.getNavigator().reload(WebNavigationConstants.LOAD_FLAGS_NONE);
			}else
			 if(action.equals(TL_STOP)){
				browser.getNavigator().stop(WebNavigationConstants.STOP_ALL);
			}else
			 if(action.equals(TL_HOME)){
				browser.getNavigator().loadURI(homeUrl,WebNavigationConstants.LOAD_FLAGS_NONE,null,null,null);
			}else
			 if(action.equals(TL_PRINT)){
				browser.print(true,true);
			}else
			 if(action.equals(TL_GO)){
				processRequest();
			}
			else
			 if(action.equals(LOC_ACT_CMD)){
				 processRequest();
			}
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void addEntry(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** addEntry() -->event<"+event+"> param<"+event.getEventParam()+">****");
		if(locationCombo!=null){
			locationCombo.removeActionListener(this);
			String url=event.getEventParam().toString().trim();
			if(((DefaultComboBoxModel)locationCombo.getModel()).getIndexOf(url)<0)
				locationCombo.addItem(url);
			locationCombo.setSelectedItem(url);
			locationCombo.addActionListener(this);
		}
	}

	public boolean goBack(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** goBack() -->event<"+event+"> param<"+event.getEventParam()+">****");
		if(locComboEditor!=null)
			locComboEditor.setText((String)event.getEventParam());
		return true;
	}

	public boolean goForward(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** goForward() -->event<"+event+"> param<"+event.getEventParam()+">****");
		if(locComboEditor!=null)
			locComboEditor.setText((String)event.getEventParam());
		return true;
	}

	public boolean reload(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** reload() -->event<"+event+"> param<"+event.getEventParam()+">****");
		IntegerEventParam param=(IntegerEventParam)event.getEventParam();
		if(locComboEditor!=null)
			locComboEditor.setText(param.getStringData());
		return true;
	}

	public boolean goToIndex(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** goToIndex() -->event<"+event+"> param<"+event.getEventParam()+">****");
		IntegerEventParam param=(IntegerEventParam)event.getEventParam();
		if(locComboEditor!=null)
			locComboEditor.setText(param.getStringData());
		return true;
	}

	public boolean purge(HistoryEvent event){
		if(JRexL.on)JRexL.log(className,"**** purge() -->event<"+event+"> param<"+event.getEventParam()+">****");
		IntegerEventParam param=(IntegerEventParam)event.getEventParam();
		return true;
	}

}