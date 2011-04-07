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
import java.awt.Window;
import java.awt.Container;

/**
* A data class to hold all the browser component related data.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class JRexBrowserData{
	/**
	* The JRexCanvas browser component in question.
	*/
	private JRexCanvas	browser;

	/**
	* The window containing the JRexCanvas.
	*/
	private Window 		window;

	/**
	* The Root Container containing the JRexCanvas, the child component very next to window (E.g content pane)
	*/
	private Container 		rootParent;

	/**
	* The Container containing the JRexCanvas.
	*/
	private Container 		parent;

	/**
	* The Chrome Flags for the browser component.
	*/
	private long  		chromeFlags;

	/**
	* Any additional data that may be associated with the browser component.
	*/
	private Object 		addData;

	public JRexBrowserData(JRexCanvas browser, Container parent, Container rootParent, Window window, long chromeFlags, Object addData){
		this.browser=browser;
		this.parent=parent;
		this.rootParent=rootParent==null?parent:rootParent;
		this.window=window;
		this.chromeFlags=chromeFlags;
		this.addData=addData;
	}

	public JRexBrowserData(JRexCanvas browser, Container parent, Container rootParent, Window window, long chromeFlags){
		this(browser,parent, rootParent, window, chromeFlags,null);
	}

	/**
	* Get JRexCanvas browser component of JRexBrowserData.
	*/
	public JRexCanvas getBrowser(){
		return 	browser;
	}

	/**
	* Get the window containing the JRexCanvas.
	*/
	public Window getWindow(){
		return 	window;
	}

	/**
	* Get the Parent Container containing the JRexCanvas.
	*/
	public Container getParent(){
		return 	parent;
	}

	/**
	* Get the root Parent Container containing the JRexCanvas.
	*/
	public Container getRootParent(){
		return 	rootParent;
	}

	/**
	* Get the Chrome Flags for the browser component.
	*/
	public long getChromeFlags(){
		return	chromeFlags;
	}

	/**
	* Set the Chrome Flags for the browser component.
	*/
	public void setChromeFlags(long chromeFlags){
		this.chromeFlags=chromeFlags;
	}

	/**
	* Get any additional data that may be associated with the browser component.
	*/
	public Object getAdditionalData(){
		return	addData;
	}

	/**
	* Set any additional data that may be associated with the browser component.
	*/
	public void setAdditionalData(Object addData){
		this.addData=addData;
	}

	StringBuffer buf;
	public String toString(){
		if(buf==null){
			buf=new StringBuffer(128);
			buf.append("\nbrowser <").append(browser.getJRexPeer()).append(">\n")
			.append("parent <").append(parent).append(">\n")
			.append("window <").append(window).append(">\n")
			.append("chromeFlags <").append(chromeFlags).append(">\n")
			.append("addData <").append(addData).append(">\n");
		}
		return buf.toString();
	}
}