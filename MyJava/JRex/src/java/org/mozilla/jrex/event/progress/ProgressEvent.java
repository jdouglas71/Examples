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

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* A class representing JRex Progress Event.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class ProgressEvent{
	private static final String className = ProgressEvent.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The target browser component to which the event belongs.
	*/
	private int 	jrexPeer;

	/**
	* The progress event type.
	*/
	private int 	eventType;

	/**
	* Indicates whether document is loading.
	*/
	private	boolean isLoadingDoc;

	/**
	* The request URI.
	*/
	private	String  reqName;

	/**
	* The status of request.
	*/
	private	int  	reqStatus;

	/**
	* Indicates whether request is pending.
	*/
	private	boolean isReqPending;

	/**
	* The progress event param.
	*/
	private Object	eventParam;

	/**
	* ProgressEvent constructor
	* @param jrexPeer  target browser component to which the event belongs
	* @param eventType  type of Progress event
	* @param isLoadingDoc  <code>true</code> if document is loading.
	* @param reqName  request URI.
	* @param reqStatus  status of request.
	* @param isReqPending <code>true</code> if request is pending.
	* @param eventParam  data associated to the Progress event
	* @see ProgressEventConstants
	*/
	public ProgressEvent(int jrexPeer,int eventType, boolean isLoadingDoc ,
								String reqName, int reqStatus, boolean  isReqPending, Object eventParam){
		if(JRexL.on)
			JRexL.log(className,"**** ProgressEvent()-->jrexPeer<"+jrexPeer+
									">eventType<"+eventType+
									">isLoadingDoc<"+isLoadingDoc+
									">reqName<"+reqName+
									">reqStatus<"+reqStatus+
									">isReqPending<"+isReqPending+
									"> eventParam<"+eventParam+">****");
		this.jrexPeer		= jrexPeer;
		this.eventType		= eventType;
		this.isLoadingDoc	= isLoadingDoc;
		this.reqName		= reqName;
		this.reqStatus		= reqStatus;
		this.isReqPending	= isReqPending;
		this.eventParam		= eventParam;
	}

	/**
	* Returns the target browser component to which the URIContent event belongs.
	*/
	public int getJRexPeer(){
		return jrexPeer;
	}

	/**
	* Returns the Progress event type.
	*/
	public int getEventType(){
		return eventType;
	}

	/**
	* Returns <code>true</code> if document is loading.
	*/
	public boolean isLoadingDocument(){
		return isLoadingDoc;
	}

	/**
	* Returns the request URI.
	*/
	public String getRequestName(){
		return reqName;
	}

	/**
	* Returns the status of request.
	*/
	public int getRequestStatus(){
		return reqStatus;
	}

	/**
	* Returns <code>true</code> if request is pending.
	*/
	public boolean isRequestPending(){
		return isReqPending;
	}

	/**
	* Returns the progress event param.
	*/
	public Object getEventTypeParam(){
		return eventParam;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\njrexPeer <").append(jrexPeer).append(">\n")
		.append("eventType <").append(eventType).append(">\n")
		.append("isLoadingDoc <").append(isLoadingDoc).append(">\n")
		.append("reqName <").append(reqName).append(">\n")
		.append("reqStatus <").append(reqStatus).append(">\n")
		.append("isReqPending <").append(isReqPending).append(">\n")
		.append("eventParam <").append(eventParam).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
