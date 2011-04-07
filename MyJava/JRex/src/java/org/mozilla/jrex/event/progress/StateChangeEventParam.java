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

package org.mozilla.jrex.event.progress;

import java.util.Hashtable;
import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* The class wrapping the state change progress event parameters.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class StateChangeEventParam{
	private static final String className =StateChangeEventParam.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The state flags associated with the event.
	*/
	private int stateFlags;

	/**
	* The status associated with the event.
	*/
	private int status;

	/**
	* The Request Headers associated with the Loading Page.
	*/
	private Hashtable reqHeaders;

	/**
	* The Response Headers associated with Loading Page.
	*/
	private Hashtable respHeaders;

	/**
	* StateChangeEventParam constructor
	* @param stateFlags   state flags associated with the event.
	* @param status  status associated with the event.
	* @param reqHeaders  List of Request Headers associated with the Loading Page.
	* @param respHeaders  List of Response Headers associated with the Loading Page.
	* @see ProgressEventConstants
	*/
	public StateChangeEventParam(int stateFlags, int status, Hashtable reqHeaders, Hashtable respHeaders){
		if(JRexL.on)
			JRexL.log(className,"**** StateChangeEventParam()-->stateFlags<"+stateFlags+
										"> status<"+status+"> reqHeaders<"+reqHeaders+
										"> respHeaders<"+respHeaders+">****");
		this.stateFlags	= stateFlags;
		this.status	= status;
		this.reqHeaders = reqHeaders;
		this.respHeaders = respHeaders;
	}

	/**
	* Returns the state flags associated with the event.
	*/
	public int getStateFlags(){
		return stateFlags;
	}

	/**
	* Returns the status associated with the event.
	*/
	public int getStatus(){
		return status;
	}

	/**
	* Returns the Request Headers associated with the Loading Page.
	*/
	public Hashtable getRequestHeaders(){
		return reqHeaders;
	}

	/**
	* Returns the Response Headers associated with the Loading Page.
	*/
	public Hashtable getResponseHeaders(){
		return respHeaders;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\nstateFlags <").append(stateFlags).append(">\n")
		.append("status <").append(status).append(">\n")
		.append("reqHeaders <").append(reqHeaders).append(">\n")
		.append("respHeaders <").append(respHeaders).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
