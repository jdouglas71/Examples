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

package org.mozilla.jrex.event.history;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* The class wrapping the interger type history event parameters.
* Intended to be used by GoToIndex like events.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class IntegerEventParam{
	private static final String className =IntegerEventParam.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The int data of the event.
	*/
	private int 	intData;

	/**
	* The uri associated with the event.
	*/
	private String	uri;

	/**
	* IntegerEventParam constructor
	* @param intData   int data of the event.
	* @param uri  uri associated with the event.
	* @see HistoryEventConstants
	*/
	public IntegerEventParam(int intData, String uri){
		if(JRexL.on)JRexL.log(className,"**** IntegerEventParam()-->intData<"+
								intData+"> uri<"+uri+"> ****");
		this.intData= intData;
		this.uri	= uri;
	}

	/**
	* Returns the int data of the event.
	*/
	public int getIntData(){
		return intData;
	}

	/**
	* Returns the uri associated with the event.
	*/
	public String getStringData(){
		return uri;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\nintData <").append(intData).append(">\n")
		.append("uri <").append(uri).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
