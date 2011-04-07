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
import org.mozilla.jrex.event.progress.*;
import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.dom.*;
import org.w3c.dom.events.*;
import org.w3c.dom.*;
//import org.w3c.dom.views.*;

/**
* Class implementing JRexStatusBar interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.mozilla.jrex.ui.JRexStatusBar
*/

public class JRexStatusBarImpl implements JRexStatusBar, ActionListener, ProgressListener{
	private static final String className	= JRexStatusBarImpl.class.getName();
	private static final String ACT_CMD_PI	= JRexResource.getString("ACT_CMD_PI");
	private static final String LBL_DONE	= JRexResource.getString("LBL_DONE");

	private JPanel	statusPanel 		= null;
	private JButton	pageInfoBtn			= null;
	private JLabel	statusLabel 		= null;
	private JProgressBar progressBar	= null;
	private JPanel		 progressPanel	= null;
	private JRexCanvas browser			= null;
	private JComponent statusBar		= null;

	/**
	* Don't use this function to create a JRexToolBar instance use JRexFactory.
	* @see org.mozilla.jrex.JRexFactory
    */
	public JRexStatusBarImpl(){
		createStatusBar();
	}

	public synchronized void setBrowser(JRexCanvas browser){
		browser.addProgressListener(this);
		if(this.browser!=null  && this.browser!=browser)
			this.browser.removeProgressListener(this);
		statusLabel.setText("");
		progressBar.setValue(0);
		progressBar.setIndeterminate(false);
		progressPanel.remove(progressBar);
		this.browser=browser;
	}

	public void setMode(int mode){

	}

	public JComponent getStatusBar(){
		if(statusBar==null)createStatusBar();
		return statusBar;
	}

	private void createStatusBar(){
		GridBagLayout gbl		= new GridBagLayout();
		GridBagConstraints gbc	= new GridBagConstraints();
		statusPanel				= new JPanel(gbl);

		pageInfoBtn	= new JButton(org.mozilla.jrex.ui.JRexResource.getIcon(ACT_CMD_PI));
		pageInfoBtn.setActionCommand(ACT_CMD_PI);
		pageInfoBtn.addActionListener(this);
		pageInfoBtn.setPreferredSize(new Dimension(20, 20));
		pageInfoBtn.setBorderPainted(false);
		pageInfoBtn.setFocusable(false);

		statusLabel = new JLabel();
		statusLabel.setForeground(Color.black);
		statusLabel.setPreferredSize(new Dimension(200, 20));
		statusLabel.setBorder(BorderFactory.createLoweredBevelBorder());

		progressBar	= new JProgressBar();
		progressBar.setPreferredSize(new Dimension(100, 20));

		Insets inset=new Insets(0,2,0,0);
		addCompToGridBag(pageInfoBtn,statusPanel ,gbc,gbl,0, 0, 1, 1,0,0,
					GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);

		addCompToGridBag(statusLabel,statusPanel ,gbc,gbl,1, 0, 1, 1,0.8,0,
					GridBagConstraints.WEST , GridBagConstraints.HORIZONTAL,inset,0,0);

		progressPanel=new JPanel(new BorderLayout());
		addCompToGridBag(progressPanel,statusPanel ,gbc,gbl,2, 0, 1, 1,0,0,
					GridBagConstraints.WEST , GridBagConstraints.NONE,inset,0,0);
		statusBar=statusPanel;
	}


	private static final void addCompToGridBag(Component comp,JPanel panel,GridBagConstraints gbc,GridBagLayout gbl,int gx, int gy, int gw, int gh, double wx, double wy, int anchor, int fill, Insets i, int ix, int iy){
		gbc.gridx=gx;
		gbc.gridy=gy;
		gbc.gridwidth=gw;
		gbc.gridheight=gh;
		gbc.weightx=wx;
		gbc.weighty=wy;
		gbc.anchor=anchor;
		gbc.fill=fill;
		gbc.insets=i;
		gbc.ipadx=ix;
		gbc.ipady=iy;
		gbl.setConstraints(comp,gbc);
		panel.add(comp);
	}

	public void actionPerformed(ActionEvent ae){
		try{
			browser.getNavigator().openWindow(WebNavigationConstants.TYPE_PAGE_INFO,"chrome://navigator/content/pageInfo.xul",null,"JRexCanvas - ","centerscreen,chrome,modal,titlebar");
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void  onStateChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onStateChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
		StateChangeEventParam scep=(StateChangeEventParam)event.getEventTypeParam();
		int statusFlag=scep.getStateFlags();
		if((statusFlag & ProgressEventConstants.STATE_START)==ProgressEventConstants.STATE_START
			||(statusFlag & ProgressEventConstants.STATE_IS_REQUEST)==ProgressEventConstants.STATE_IS_REQUEST){
			progressBar.setValue(0);
			progressBar.setIndeterminate(true);
			if(progressPanel.getComponents().length==0){
				progressPanel.add(progressBar);
				statusPanel.validate();
			}
		}else
		if(((statusFlag & ProgressEventConstants.STATE_STOP)==ProgressEventConstants.STATE_STOP||
			(statusFlag & ProgressEventConstants.STATE_IS_NETWORK)==ProgressEventConstants.STATE_IS_NETWORK)
			||(statusFlag & ProgressEventConstants.STATE_IS_REQUEST)==ProgressEventConstants.STATE_IS_REQUEST){
			progressBar.setIndeterminate(false);
			progressPanel.remove(progressBar);
			statusPanel.validate();
			statusLabel.setText(LBL_DONE);
			//doDOMClick();
/*			try{
				JRexDocumentImpl myDoc =(JRexDocumentImpl)browser.getNavigator().getDocument();
				if(JRexL.on)JRexL.log(className,"**** onStateChange() -->myDoc<"+myDoc+"> ****");
				dumpNodes1(myDoc);
			}catch(Exception ex){
				ex.printStackTrace();
			}*/
		}
	}

	private void dumpNodes1(Node node)throws Exception{
		NodeList list=node.getChildNodes();
		int len=list.getLength();
		if(JRexL.on)JRexL.log(className,"**** dumpNodes() -->len<"+len+"> ****");
		for(int i=0;i<len;i++){
			if(JRexL.on)JRexL.log(className,"**** dumpNodes() -->list<"+i+"> item<"+list.item(i)+"> ****");
			if(list.item(i) instanceof JRexElementImpl){
				//JRexBoxObject jobj=((JRexElementImpl)list.item(i)).getBoxObject();
				Object jobj=list.item(i);
				if(JRexL.on)JRexL.log(className,"**** dumpNodes() -->jobj<"+jobj+"> ****");
			}
			dumpNodes1(list.item(i));
		}
	}

	private Node dumpNodes(Node node, String name)throws Exception{
		NodeList list=node.getChildNodes();
		int len=list.getLength();
		if(JRexL.on)JRexL.log(className,"**** dumpNodes() -->len<"+len+"> ****");
		for(int i=0;i<len;i++){
			if(JRexL.on)JRexL.log(className,"**** dumpNodes() -->list<"+i+"> item<"+list.item(i)+"> ****");
			if(list.item(i).getNodeName().equalsIgnoreCase(name))
				return list.item(i);
			Node bullNode= dumpNodes(list.item(i),name);
			if(bullNode!=null){
				if(JRexL.on)JRexL.log(className,"**** %%%%%%%%%%%%%%%%%%%%%%%% MATCH %%%%%%%%%%%%%%%%%%%%%%%% ****");
				return bullNode;
			}
		}
		return null;
	}

	private void doDOMClick(){
		try{
			JRexDocumentImpl myDoc =(JRexDocumentImpl)browser.getNavigator().getDocument();
			if(JRexL.on)JRexL.log(className,"**** doDOMClick() -->myDoc<"+myDoc+"> ****");
			org.mozilla.jrex.dom.JRexNodeImpl myNode=(org.mozilla.jrex.dom.JRexNodeImpl)dumpNodes(myDoc,"FORM");
			if(JRexL.on)JRexL.log(className,"**** doDOMClick() -->myNode<"+myNode+"> ****");
			if(myNode==null)myNode=myDoc;

			EventTarget relatedEventTarget =myNode.getEventTarget();
			if(JRexL.on)JRexL.log(className,"**** doDOMClick() -->relatedEventTarget<"+relatedEventTarget+"> ****");
			DocumentEvent docEvent = myDoc.getDocumentEvent();
			if(JRexL.on)JRexL.log(className,"**** doDOMClick() -->docEvent<"+docEvent+"> ****");
  			final org.w3c.dom.events.Event mEvent =(org.w3c.dom.events.Event)docEvent.createEvent("HTMLEvents");
  			if(JRexL.on)JRexL.log(className,"**** doDOMClick() -->mEvent<"+mEvent+"> ****");
			mEvent.initEvent("submit",true,true);
			relatedEventTarget.dispatchEvent(mEvent);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}

	public void  onLocationChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onLocationChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
	}

	public void  onStatusChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onStatusChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
		StatusChangeEventParam scev=(StatusChangeEventParam)event.getEventTypeParam();
		statusLabel.setText(scev.getStatusMessage());
	}

	public void  onSecurityChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onSecurityChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
	}

	public void  onProgressChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onProgressChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
		ProgressChangeEventParam pcep =(ProgressChangeEventParam)event.getEventTypeParam();
		int maxVal=pcep.getMaximumSelfProgress();
		if(maxVal==-1){
			progressBar.setIndeterminate(true);
			return;
		}else
			progressBar.setIndeterminate(false);
		progressBar.setMaximum(maxVal);
		progressBar.setValue(pcep.getCurrentSelfProgress());
	}

	public void  onLinkStatusChange(ProgressEvent event){
		if(JRexL.on)JRexL.log(className,"**** onLinkStatusChange() -->event<"+event+"> param<"+event.getEventTypeParam()+">****");
		StatusChangeEventParam scep=(StatusChangeEventParam)event.getEventTypeParam();
		statusLabel.setText(scep.getStatusMessage());
	}
}