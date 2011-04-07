
  /* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
* A interface containing the constants related to URIContent events.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface URIContentEventConstants{

	/**
	* OnStartUri event type.
	*/
	public static final short URI_ON_START_EVENT	= 0;

	/**
	* DoContent event type.
	*/
	public static final short URI_DO_CONTENT		= 1;

	/**
	* IsPreferred event type.
	*/
	public static final short URI_IS_PREFERRED		= 2;

	/**
	* CanHandle event type.
	*/
	public static final short URI_CAN_HANDLE_CONTENT= 3;

	/**
	* Get cookie event type. Not used
	*/
	public static final short URI_GET_LOAD_COOKIE	= 4;

	/**
	* Get cookie event type. Not used
	*/
	public static final short URI_SET_LOAD_COOKIE	= 5;
}