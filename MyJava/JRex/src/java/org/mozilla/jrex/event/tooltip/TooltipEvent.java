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

package org.mozilla.jrex.event.tooltip;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* A class representing JRex Tooltip Event.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class TooltipEvent{

	private static final String className =TooltipEvent.class.getName();

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The target browser component to which the event belongs.
	*/
	private int 	jrexPeer;

	/**
	* The tool tip event type.
	*/
	private int 	eventType;

	/**
	* The tool tip window x co-ordinate.
	*/
	private int 	cX;

	/**
	* The tool tip window y co-ordinate.
	*/
	private int 	cY;

	/**
	* The tool tip string to be shown.
	*/
	private String	toolTip;

	/**
	* WindowEvent constructor
	* @param jrexPeer  target browser component to which the event belongs
	* @param eventType  type of tool tip event.
	* @param cX  tool tip window x co-ordinate.
	* @param cY  tool tip window y co-ordinate.
	* @param toolTip  tool tip string to be shown.
	* @see TooltipEventConstants
	*/
	public TooltipEvent(int jrexPeer,int eventType, int cX, int cY, String toolTip){
		if(JRexL.on)JRexL.log(className,"**** TooltipEvent()-->jrexPeer<"+jrexPeer+
									"> cX<"+cX+">cY<"+cY+
										"> toolTip<"+toolTip+"> ****");
		this.jrexPeer	= jrexPeer;
		this.eventType=eventType;
		this.cX=cX;
		this.cY=cY;
		this.toolTip=toolTip;
	}

	/**
	* Returns the target browser component to which the event belongs.
	*/
	public int getJRexPeer(){
		return jrexPeer;
	}

	/**
	* Returns the tooltip event type.
	*/
	public int getEventType(){
		return eventType;
	}

	/**
	* Returns the x co-ordinate where tool tip should be shown.
	*/
	public int getClientX(){
		return cX;
	}

	/**
	* Returns the y co-ordinate where tool tip should be shown.
	*/
	public int getClientY(){
		return cY;
	}

	/**
	* Returns the tool tip string to be shown.
	*/
	public String getToolTip(){
		return toolTip;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\njrexPeer <").append(jrexPeer).append(">\n")
		.append("cX <").append(cX).append(">\n")
		.append("cY <").append(cY).append(">\n")
		.append("toolTip <").append(toolTip).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}