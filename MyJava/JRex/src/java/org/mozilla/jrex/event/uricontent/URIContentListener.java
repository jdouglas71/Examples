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

/**
* The JRex URIContentListener interface, This listener can be added to listen to any uri related
* events.
* @see org.mozilla.jrex.ui.JRexCanvas#addURIContentListener(org.mozilla.jrex.event.uricontent.URIContentListener)
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface URIContentListener{

	/**
	* Gives the content listener first crack at stopping a load before it happens.
	* @return       <code>false</code> if the load can continue;
	*               <code>true</code> if the load should be aborted.
	* @see	URIContentEvent
	*/
	public boolean onStartContent(URIContentEvent event);

	/**
	* Notifies the content listener to hook up an StreamListener capable of consuming the data stream.
	* @see	URIContentEvent
	* @see	DoContentEventParam
	* @see	URIContentEventRV
	*/
	public URIContentEventRV doContent(URIContentEvent event);

	/**
	* Gives the content listener to say whether the content type for load is 'preferred content'
	* @see  #canHandleContent(URIContentEvent)
	* @see	URIContentEvent
	* @see	URIContentEventRV
	*/
	public URIContentEventRV isContentPreferred(URIContentEvent event);

	/**
	* When given a uri to dispatch, if the URI is not specified as 'preferred
	* content' then the uri loader calls canHandleContent to see if the content
	* listener is capable of handling the content.
	* @see	URIContentEvent
	* @see	URIContentEventRV
	* @see	CanHandleEventParam
	*/
	public URIContentEventRV canHandleContent(URIContentEvent event);//doesn't isPreferred get the job done?
}
