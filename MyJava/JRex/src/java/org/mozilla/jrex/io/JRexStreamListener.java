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

package org.mozilla.jrex.io;

/**
* JRexStreamListener interface is java counter part of nsIStreamListener.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface JRexStreamListener{
	/**
    * Called to signify the beginning of an asynchronous request.
    *
	* @param	requestURI request URI corresponding to the source of the data
	* @param	requestStatus request Status corresponding to the source of the data
	* @param	isRequestPending request pending corresponding to the source of the data
	* @param	ctxt user defined context
	* @param	conInfo List additional information for request, E.g. the response headers for the corresponding http transaction.
    *
    * @return boolean return <code>false</code> to cancel the request.
    */
	public boolean onStartRequest(String  requestURI, int requestStatus, boolean isRequestPending, Object ctxt, java.util.Hashtable conInfo);

  	/**
     * Called to signify the end of an asynchronous request.  This
     * call is always preceded by a call to onStartRequest.
     *
     * @param	requestURI request URI corresponding to the source of the data
	 * @param	requestStatus request Status corresponding to the source of the data
	 * @param	isRequestPending request pending corresponding to the source of the data
	 * @param	ctxt user defined context
     * @param	statusCode reason for stopping, NS_OK if successful.
     */
	public void onStopRequest(String  requestURI, int requestStatus, boolean isRequestPending, Object ctxt, int statusCode);

	/**
	* Called when the next chunk of data (corresponding to the request) may
	* be read without blocking the calling thread.  The onDataAvailable impl
	* must read exactly |len| bytes of data before returning.
	*
	* @param	requestURI request URI corresponding to the source of the data
	* @param	requestStatus request Status corresponding to the source of the data
	* @param	isRequestPending request pending corresponding to the source of the data
	* @param	ctxt user defined context
	* @param	in input stream containing the data chunk
	* @param	off current stream position
	* @param	len number of bytes available in the stream
	*
	* @return	return <code>false</code> to cancel the request.
	*/
	public boolean onDataAvailable(String  requestURI, int requestStatus, boolean isRequestPending, Object ctxt, JRexInputStream in, int off, int len);

}
