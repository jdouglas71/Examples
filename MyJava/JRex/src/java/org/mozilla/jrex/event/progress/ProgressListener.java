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

/**
* The JRex ProgressListener interface, This listener can be added to listen to any
* progress related events.
* @see org.mozilla.jrex.ui.JRexCanvas#addProgressListener(org.mozilla.jrex.event.progress.ProgressListener)
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface ProgressListener{

	/**
	* Notification indicating the state has changed for one of the requests
	* associated with the document loaded.
	*
	* For this event the ProgressEvent's getEventParam will return StateChangeEventParam instance.
	*
	* @param event    The ProgressEvent
	* @see			ProgressEvent
	* @see			StateChangeEventParam
	*/
	public void  onStateChange(ProgressEvent event);

	/**
	* Notification that the progress has changed for one of the requests being
	* monitored.
	*
	* For this event the ProgressEvent's getEventParam will return ProgressChangeEventParam instance.
	*
	* @param event    The ProgressEvent
	* @see			ProgressEvent
	* @see			ProgressChangeEventParam
	*/
	public void  onProgressChange(ProgressEvent event);

	/**
	* Called when the window being watched changes the location that is currently.
	* This is not when a load is requested, but rather once it is verified that
	* the load is going to occur in the given window.  For instance, a load that
	* starts in a window might send progress and status messages, for the new site
	* but it will not send the onLocationChange until we are sure we are loading
	* this new page here.
	*
	* For this event the ProgressEvent's getEventParam will return URI of the location
	* that is being loaded.
	*
	* @param event  The ProgressEvent
	* @see			ProgressEvent
	*/
	public void  onLocationChange(ProgressEvent event);

	/**
	* Notification that the status has changed. The status message is usually
	* printed in the status bar of the browser.
	*
	* For this event the ProgressEvent's getEventParam will return StatusChangeEventParam instance.
	*
	* @param event    The ProgressEvent
	* @see			ProgressEvent
	* @see			StatusChangeEventParam
	*/
	public void  onStatusChange(ProgressEvent event);

	/**
	* Notification called for security progress.
	* This method will be called on security transitions (eg HTTP -> HTTPS,
	* HTTPS -> HTTP, FOO -> https) and after document load completion.
	* It might also be called if an error occurs during network loading.
	*
	* For this event the ProgressEvent's getEventParam will return StatusChangeEventParam instance.
	*
	* These notification will only occur if a security package is installed.
	*
	* @param event  The ProgressEvent
	* @see			ProgressEvent
	* @see			StatusChangeEventParam
	*/
	public void  onSecurityChange(ProgressEvent event);

	/**
	* This is an additional event to set of progress event, this event occurs when mouse is rolled over a
	* link which is usually printed in the status bar of the browser.
	*
	* For this event the ProgressEvent's getEventParam will return string representation
	* of URI under question.
	*
	* @param event  The ProgressEvent
	* @see			ProgressEvent
	*/
	public void  onLinkStatusChange(ProgressEvent event);

}

