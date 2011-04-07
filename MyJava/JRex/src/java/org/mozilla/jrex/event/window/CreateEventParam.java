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

package org.mozilla.jrex.event.window;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* The class wrapping the create window event parameters.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class CreateEventParam{
	private static final String className =CreateEventParam.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The parent browser component of the  browser to be created.
	*/
	private int 	parentWindow;

	/**
	* The chrome flags to used for window creation.
	*/
	private long	chromeFlags;

	/**
	* The context flags to used for window creation.
	*/
	private int 	contextFlags;

	/**
	* The uri for which window creation is requested.
	*/
	private String	uri;

	/**
	* CreateEventParam constructor
	* @param parentWindow  parent browser component of the  browser to be created.
	* @param chromeFlags  chrome flags to used for window creation.
	* @param contextFlags  context flags to used for window creation.
	* @param uri  uri for which window creation is requested.
	* @see WindowEventConstants
	*/
	public CreateEventParam(int parentWindow, long chromeFlags,
									int contextFlags, String uri){
		if(JRexL.on)
			JRexL.log(className,"**** CreateEventParam()-->parentWindow<"+parentWindow+
										"> chromeFlags<"+chromeFlags+
										"> contextFlags<"+contextFlags+"> uri<"+uri+"> ****");
		this.parentWindow	= parentWindow;
		this.chromeFlags	= chromeFlags;
		this.contextFlags	= contextFlags;
		this.uri			= uri;

	}

	/**
	* Returns the parent browser component of the  browser to be created.
	*/
	public int getParentWindow(){
		return parentWindow;
	}

	/**
	* Returns the chrome flags to used for window creation.
	*/
	public long getChromeFlags(){
		return chromeFlags;
	}

	/**
	* Returns context flags to used for window creation.
	*/
	public int getContextFlags(){
		return contextFlags;
	}

	/**
	* Returns the uri for which window creation is requested.
	*/
	public String getURI(){
		return uri;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\nparentWindow <").append(parentWindow).append(">\n")
		.append("chromeFlags <").append(chromeFlags).append(">\n")
		.append("contextFlags <").append(contextFlags).append(">\n")
		.append("uri <").append(uri).append(">\n");
		return buf.toString();
	}
	private static native void initIDs()throws JRexException;
}
