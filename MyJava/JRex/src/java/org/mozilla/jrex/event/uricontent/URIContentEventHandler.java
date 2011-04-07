
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

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.ui.JRexCanvas;
import org.mozilla.jrex.event.JRexEvent;
import org.mozilla.jrex.event.JRexEventHandler;
import org.mozilla.jrex.window.JRexWindowManager;
import org.mozilla.jrex.JRexFactory;

/**
* The JRex Event handler for URIContent events.
* Intended to be used by JRex EventManager.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class URIContentEventHandler implements JRexEventHandler{

	private static final String className 		= URIContentEventHandler.class.getName();

	private JRexWindowManager windowManager;

	public URIContentEventHandler(){}

	public Object handleEvent(JRexEvent event){
		if(JRexL.on)JRexL.log(className,"**** handleEvent()-->event <"+event+"> ****");
		assert event!=null;
		if(event==null)return null;
		URIContentEvent uce=(URIContentEvent)event.getData();
		if(JRexL.on)JRexL.log(className,"**** handleEvent()-->uce <"+uce+"> ****");
		assert uce!=null;
		if(uce==null)return null;
		if(windowManager==null)
			windowManager=(JRexWindowManager)JRexFactory.getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER);
		JRexCanvas browser=windowManager.getBrowser(uce.getJRexPeer());
		assert browser!=null;
		if(browser==null)return null;
		return browser.processURIContentEvent(uce);
	}
}