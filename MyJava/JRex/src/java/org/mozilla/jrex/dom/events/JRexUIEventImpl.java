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

package org.mozilla.jrex.dom.events;

import org.w3c.dom.events.*;
import org.w3c.dom.views.AbstractView;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;


/**
* A class implementing org.w3c.dom.events.UIEvent interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.events.UIEvent
*/
public class JRexUIEventImpl extends JRexEventImpl implements UIEvent {
	private static final String className	= JRexUIEventImpl.class.getName();

	protected JRexUIEventImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexUIEventImpl I AM HERE ****");
	}

    public AbstractView getView(){
		if(JRexL.on)JRexL.log(className,"**** getView ****");
		AbstractView view=null;
		try{
			view=GetView();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getView view<"+view+"> ****");
		return view;
	}

    public int getDetail(){
		if(JRexL.on)JRexL.log(className,"**** getDetail ****");
		int detail=0;
		try{
			detail=GetDetail();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDetail detail<"+detail+"> ****");
		return detail;
	}

    public void initUIEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
    						AbstractView viewArg,int detailArg){
		if(JRexL.on)JRexL.log(className,"**** initEvent typeArg<"+typeArg+
							"> canBubbleArg<"+canBubbleArg+"> cancelableArg<"+cancelableArg+
							"> viewArg<"+viewArg+"> detailArg<"+detailArg+">****");
		try{
			InitUIEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native AbstractView GetView()throws JRexException;
	private native int GetDetail()throws JRexException;
	private native void InitUIEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
    						AbstractView viewArg,int detailArg)throws JRexException;
}
