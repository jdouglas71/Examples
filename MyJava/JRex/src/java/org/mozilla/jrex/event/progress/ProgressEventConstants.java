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
* A interface containing the constants related to Progress events.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface ProgressEventConstants{

	/**
	* Progress state transition bits.
	* These flags indicate the various states that documents and requests
	* may transition through as they are being loaded.
	*/
	public static final int STATE_START			= 1;
	public static final int STATE_REDIRECTING	= 2;
	public static final int STATE_TRANSFERRING	= 4;
	public static final int STATE_NEGOTIATING	= 8;
	public static final int STATE_STOP 		 	= 16;

	/**
	* Progress State type bits.
	* These flags indicate whether the transition is occuring on a document
	* or an individual request within the document.
	*/
	public static final int STATE_IS_REQUEST	= 65536;
	public static final int STATE_IS_DOCUMENT	= 131072;
	public static final int STATE_IS_NETWORK 	= 262144;
	public static final int STATE_IS_WINDOW  	= 524288;

	/**
	* Security state bits
	*/
	public static final int STATE_IS_INSECURE	= 4;
	public static final int STATE_IS_BROKEN		= 1;
	public static final int STATE_IS_SECURE 	= 2;
	public static final int STATE_SECURE_HIGH  	= 262144;
	public static final int STATE_SECURE_MED  	= 65536;
	public static final int STATE_SECURE_LOW  	= 131072;

	/**
	* State change event type.
	*/
	public static final short PROG_STATE_CHANGE			= 0;

	/**
	* Progress change event type.
	*/
	public static final short PROG_PROGRESS_CHANGE		= 1;

	/**
	* Location change event type.
	*/
	public static final short PROG_LOC_CHANGE			= 2;

	/**
	* Status change event type.
	*/
	public static final short PROG_STATUS_CHANGE		= 3;

	/**
	* Security state change event type.
	*/
	public static final short PROG_SECURITY_CHANGE		= 4;

	/**
	* Link status change event type.
	*/
	public static final short PROG_LINK_STATUS_CHANGE	= 5;
}