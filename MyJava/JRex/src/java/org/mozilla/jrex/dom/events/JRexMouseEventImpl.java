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
* A class implementing org.w3c.dom.events.MouseEvent interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.events.MouseEvent
*/
public class JRexMouseEventImpl extends JRexUIEventImpl implements MouseEvent {
	private static final String className	= JRexMouseEventImpl.class.getName();

	private JRexMouseEventImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexMouseEventImpl I AM HERE ****");
	}

    public int getScreenX(){
		if(JRexL.on)JRexL.log(className,"**** getScreenX ****");
		int X=0;
		try{
			X=GetScreenX();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getScreenX X<"+X+"> ****");
		return X;
	}

    public int getScreenY(){
		if(JRexL.on)JRexL.log(className,"**** getScreenY ****");
		int Y=0;
		try{
			Y=GetScreenY();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getScreenY Y<"+Y+"> ****");
		return Y;
	}

    public int getClientX(){
		if(JRexL.on)JRexL.log(className,"**** getClientX ****");
		int X=0;
		try{
			X=GetClientX();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getClientX X<"+X+"> ****");
		return X;
	}

    public int getClientY(){
		if(JRexL.on)JRexL.log(className,"**** getClientY ****");
		int Y=0;
		try{
			Y=GetClientY();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getClientY Y<"+Y+"> ****");
		return Y;
	}

    public boolean getCtrlKey(){
		if(JRexL.on)JRexL.log(className,"**** getCtrlKey ****");
		boolean isPressed=false;
		try{
			isPressed=GetCtrlKey();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCtrlKey isPressed<"+isPressed+"> ****");
		return isPressed;
	}


    public boolean getShiftKey(){
		if(JRexL.on)JRexL.log(className,"**** getShiftKey ****");
		boolean isPressed=false;
		try{
			isPressed=GetShiftKey();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getShiftKey isPressed<"+isPressed+"> ****");
		return isPressed;
	}

    public boolean getAltKey(){
		if(JRexL.on)JRexL.log(className,"**** getAltKey ****");
		boolean isPressed=false;
		try{
			isPressed=GetAltKey();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAltKey isPressed<"+isPressed+"> ****");
		return isPressed;
	}

    public boolean getMetaKey(){
		if(JRexL.on)JRexL.log(className,"**** getMetaKey ****");
		boolean isPressed=false;
		try{
			isPressed=GetMetaKey();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMetaKey isPressed<"+isPressed+"> ****");
		return isPressed;
	}

    public short getButton(){
		if(JRexL.on)JRexL.log(className,"**** getButton ****");
		short button=0;
		try{
			button=GetButton();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getButton button<"+button+"> ****");
		return button;
	}

    public EventTarget getRelatedTarget(){
		if(JRexL.on)JRexL.log(className,"**** getRelatedTarget ****");
		EventTarget target=null;
		try{
			target=GetRelatedTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRelatedTarget target<"+target+"> ****");
		return target;
	}

    public void initMouseEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
                               AbstractView viewArg,int detailArg,
                               int screenXArg,int screenYArg,int clientXArg,
                               int clientYArg,boolean ctrlKeyArg,boolean altKeyArg,
                               boolean shiftKeyArg,boolean metaKeyArg,short buttonArg, EventTarget relatedTargetArg){
		if(JRexL.on)JRexL.log(className,"**** initEvent typeArg<"+typeArg+
							"> canBubbleArg<"+canBubbleArg+"> cancelableArg<"+cancelableArg+
							"> viewArg<"+viewArg+"> detailArg<"+detailArg+">****");
		try{
			InitMouseEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg,
							screenXArg,screenYArg,clientXArg,clientYArg,ctrlKeyArg,altKeyArg,
								shiftKeyArg,metaKeyArg,buttonArg,relatedTargetArg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    private native int GetScreenX()throws JRexException;
    private native int GetScreenY()throws JRexException;
    private native int GetClientX()throws JRexException;
    private native int GetClientY()throws JRexException;
    private native boolean GetCtrlKey()throws JRexException;
    private native boolean GetShiftKey()throws JRexException;
    private native boolean GetAltKey()throws JRexException;
    private native boolean GetMetaKey()throws JRexException;
    private native short GetButton()throws JRexException;
    private native EventTarget GetRelatedTarget()throws JRexException;
    private native void InitMouseEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
                               AbstractView viewArg,int detailArg,int screenXArg,int screenYArg,
                               int clientXArg,int clientYArg,boolean ctrlKeyArg,boolean altKeyArg,
                               boolean shiftKeyArg,boolean metaKeyArg,short buttonArg,EventTarget relatedTargetArg)throws JRexException;

}
