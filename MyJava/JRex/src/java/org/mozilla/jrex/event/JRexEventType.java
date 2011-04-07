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

package org.mozilla.jrex.event;

/**
* A interface containing the jrex supported event types.
* Presently the constants defined in this interface are also defined in native JNI header.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface JRexEventType{
	/**
	* Event type representing shutdown event.
	* When event manager receives a shutdown event the event manager shut's it self down.
	*/
	public static final int SHUTDOWN_EVENT		= -1;

	/**
	* Event type representing JRex Window event.
	*/
	public static final int WINDOW_EVENT		= 1;

	/**
	* Event type representing JRex History event.
	*/
	public static final int HISTORY_EVENT		= 2;

	/**
	* Event type representing JRex Progress event.
	*/
	public static final int PROGRESS_EVENT		= 3;

	/**
	* Event type representing JRex ContextMenu event.
	*/
	public static final int CONTEXT_MENU_EVENT	= 4;

	/**
	* Event type representing JRex ToolTip event.
	*/
	public static final int TOOL_TIP_EVENT		= 5;

	/**
	* Event type representing JRex Observer event.
	*/
	public static final int OBSERVER_EVENT		= 6;

	/**
	* Event type representing JRex URIContent event.
	*/
	public static final int URICONTENT_EVENT	= 7;

}