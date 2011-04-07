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

package org.mozilla.jrex.event.window;

/**
* A interface containing the constants related to window events.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface WindowEventConstants{

	/**
	* Set of chrome flags.
	*/
	public static final int PARENT_IS_LOADING_OR_RUNNING_TIMEOUT	= 1;
	public static final int CHROME_DEFAULT 			= 1;
	public static final int CHROME_WINDOW_BORDERS 	= 2;
	public static final int CHROME_WINDOW_CLOSE 	= 4;
	public static final int CHROME_WINDOW_RESIZE 	= 8;
	public static final int CHROME_MENUBAR 			= 16;
	public static final int CHROME_TOOLBAR 			= 32;
	public static final int CHROME_LOCATIONBAR 		= 64;
	public static final int CHROME_STATUSBAR 		= 128;
	public static final int CHROME_PERSONAL_TOOLBAR = 256;
	public static final int CHROME_SCROLLBARS 		= 512;
	public static final int CHROME_TITLEBAR 		= 1024;
	public static final int CHROME_EXTRA 			= 2048;
	public static final int CHROME_WITH_SIZE 		= 4096;
	public static final int CHROME_WITH_POSITION 	= 8192;
	public static final int CHROME_WINDOW_MIN 		= 16384;
	public static final int CHROME_WINDOW_POPUP 	= 32768;
	public static final int CHROME_WINDOW_RAISED 	= 33554432;
	public static final int CHROME_WINDOW_LOWERED 	= 67108864;
	public static final int CHROME_CENTER_SCREEN 	= 134217728;
	public static final int CHROME_DEPENDENT 		= 268435456;
	public static final int CHROME_MODAL 			= 536870912;
	public static final int CHROME_OPENAS_DIALOG 	= 1073741824;
	public static final int CHROME_ALL 				= 4094;
	public static final long CHROME_OPENAS_CHROME 	= 2147483648L;

	/**
	* Create window event type.
	*/
	public static final short WIN_CREATE_EVENT		= 0;

	/**
	* Set modal window event type.
	*/
	public static final short WIN_SETMODAL_EVENT	= 1;

	/**
	* Resize window event type.
	*/
	public static final short WIN_RESIZE_EVENT		= 2;

	/**
	* Dispose window event type.
	*/
	public static final short WIN_DESTROY_EVENT		= 3;

	/**
	* Set title window event type.
	*/
	public static final short WIN_SET_TITLE_EVENT	= 4;

	/**
	* Set chrome flag window event type.
	*/
	public static final short WIN_CHROME_FLAG_EVENT	= 5;

	/**
	* Window Realized window event type.
	*/
	public static final short WIN_REALIZED_EVENT	= 6;
}