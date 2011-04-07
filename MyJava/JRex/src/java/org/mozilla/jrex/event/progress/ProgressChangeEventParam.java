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
* The class wrapping the progress change progress event parameters.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class ProgressChangeEventParam{
	private static final String className =ProgressChangeEventParam.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}


	/**
	* The current progress for request.
	*/
	private int curSelfProgress;

	/**
	* The maximum progress for request
	*/
	private int maxSelfProgress;

	/**
	* The current progress for all the requests
	*/
	private int curTotalProgress;

	/**
	* The total progress for all the requests being monitored.
	*/
	private int maxTotalProgress;

	/**
	* ProgressChangeEventParam constructor
	* @param curSelfProgress    The current progress for request.
	*
	* @param maxSelfProgress    The maximum progress for request.  If this
	*                            value is not known then -1 is passed.
	*
	* @param curTotalProgress   The current progress for all the requests
	*                            being monitored.
	*
	* @param maxTotalProgress   The total progress for all the requests being
	*                            monitored.  If this value is not known then
	*                            -1 is passed.
	* @see ProgressEventConstants
	*/
	public ProgressChangeEventParam(int curSelfProgress, int maxSelfProgress,
										int curTotalProgress,int maxTotalProgress){
		if(JRexL.on)
			JRexL.log(className,"**** ProgressChangeEventParam()-->curSelfProgress<"+curSelfProgress+
										"> maxSelfProgress<"+maxSelfProgress+
										"> curTotalProgress<"+curTotalProgress+
										"> maxTotalProgress<"+maxTotalProgress+"> ****");
		this.curSelfProgress= curSelfProgress;
		this.maxSelfProgress= maxSelfProgress;
		this.curTotalProgress= curTotalProgress;
		this.maxTotalProgress= maxTotalProgress;

	}

	/**
	* Returns the current progress for request.
	*/
	public int getCurrentSelfProgress(){
		return curSelfProgress;
	}

	/**
	* Returns the maximum progress for request
	*/
	public int getMaximumSelfProgress(){
		return maxSelfProgress;
	}

	/**
	* Returns the current progress for all the requests
	*/
	public int getCurrentTotalProgress(){
		return curTotalProgress;
	}

	/**
	* Returns the total progress for all the requests being monitored.
	*/
	public int getMaximumTotalProgress(){
		return maxTotalProgress;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\ncurSelfProgress <").append(curSelfProgress).append(">\n")
		.append("maxSelfProgress <").append(maxSelfProgress).append(">\n")
		.append("curTotalProgress <").append(curTotalProgress).append(">\n")
		.append("maxTotalProgress <").append(maxTotalProgress).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
