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

package org.mozilla.jrex.event.uricontent;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* The class wrapping the DoContent event parameters.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class CanHandleEventParam{
	private static final String className =CanHandleEventParam.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* Indicates whether content type is preferred.
	*/
	private boolean isContentPreferred;


	/**
	* The content type of the request.
	*/
	private String	contentType;

	/**
	* CanHandleEventParam constructor
	* @param isContentPreferred  <code>true</code> if content type is preferred.
	* @param contentType  content type of the request.
	* @see URIContentEventConstants
	*/
	public CanHandleEventParam(boolean isContentPreferred, String contentType){
		if(JRexL.on)JRexL.log(className,"**** CanHandleEventParam()-->isContentPreferred<"+
								isContentPreferred+"> contentType<"+contentType+"> ****");
		this.isContentPreferred= isContentPreferred;
		this.contentType	= contentType;
	}

	/**
	* Returns whether content type is preferred.
	*/
	public boolean isContentPreferred(){
		return isContentPreferred;
	}

	/**
	* Returns the content type of the request.
	*/
	public String getContentType(){
		return contentType;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\nisContentPreferred <").append(isContentPreferred).append(">\n")
		.append("contentType <").append(contentType).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
