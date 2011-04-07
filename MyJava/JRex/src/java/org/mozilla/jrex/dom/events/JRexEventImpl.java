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

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;


/**
* A class implementing org.w3c.dom.events.Event interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.events.Event
*/
public class JRexEventImpl implements Event {

	private static final String className	= JRexEventImpl.class.getName();
	private int peerEvent = 0;

	protected JRexEventImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexEventImpl I AM HERE ****");
	}

    public String getType(){
		if(JRexL.on)JRexL.log(className,"**** getType ****");
		String type=null;
		try{
			type=GetType();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType type<"+type+"> ****");
		return type;
	}


    public EventTarget getTarget(){
		if(JRexL.on)JRexL.log(className,"**** getTarget ****");
		EventTarget target=null;
		try{
			target=GetTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTarget target<"+target+"> ****");
		return target;
	}

    public EventTarget getCurrentTarget(){
		if(JRexL.on)JRexL.log(className,"**** getCurrentTarget ****");
		EventTarget currTarget=null;
		try{
			currTarget=GetCurrentTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCurrentTarget currTarget<"+currTarget+"> ****");
		return currTarget;
	}

	/** The original target of the event, before any retargetings. */
    public EventTarget getOriginalTarget(){
		if(JRexL.on)JRexL.log(className,"**** getOriginalTarget ****");
		EventTarget origTraget=null;
		try{
			origTraget=GetOriginalTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getOriginalTarget origTraget<"+origTraget+"> ****");
		return origTraget;
	}

	/**
	* The explicit original target of the event.  If the event was retargeted
	* for some reason other than an anonymous boundary crossing, this will be set
	* to the target before the retargeting occurs.  For example, mouse events
	* are retargeted to their parent node when they happen over text nodes (bug
	* 185889), and in that case .target will show the parent and
	* .explicitOriginalTarget will show the text node.
	* .explicitOriginalTarget differs from .originalTarget in that it will never
	* contain anonymous content.
	*/
    public EventTarget getExplicitOriginalTarget(){
		if(JRexL.on)JRexL.log(className,"**** getExplicitOriginalTarget ****");
		EventTarget exOrigTraget=null;
		try{
			exOrigTraget=GetExplicitOriginalTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getExplicitOriginalTarget exOrigTraget<"+exOrigTraget+"> ****");
		return exOrigTraget;
	}

    public short getEventPhase(){
		if(JRexL.on)JRexL.log(className,"**** getEventPhase ****");
		short phase=0;
		try{
			phase=GetEventPhase();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEventPhase phase<"+phase+"> ****");
		return phase;
	}

    public boolean getBubbles(){
		if(JRexL.on)JRexL.log(className,"**** getBubbles ****");
		boolean bubbles=false;
		try{
			bubbles=GetBubbles();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBubbles bubbles<"+bubbles+"> ****");
		return bubbles;
	}

    public boolean getCancelable(){
		if(JRexL.on)JRexL.log(className,"**** getCancelable ****");
		boolean canCancel=false;
		try{
			canCancel=GetCancelable();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCancelable canCancel<"+canCancel+"> ****");
		return canCancel;
	}

    public long getTimeStamp(){
		if(JRexL.on)JRexL.log(className,"**** getTimeStamp ****");
		long tStamp=0;
		try{
			tStamp=GetTimeStamp();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTimeStamp tStamp<"+tStamp+"> ****");
		return tStamp;
	}

    public void stopPropagation(){
		if(JRexL.on)JRexL.log(className,"**** stopPropagation ****");
		try{
			StopPropagation();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public void preventDefault(){
		if(JRexL.on)JRexL.log(className,"**** preventDefault ****");
		try{
			PreventDefault();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public void initEvent(String eventTypeArg, boolean canBubbleArg,boolean cancelableArg){
		if(JRexL.on)JRexL.log(className,"**** initEvent eventTypeArg<"+eventTypeArg+
							"> canBubbleArg<"+canBubbleArg+"> cancelableArg<"+cancelableArg+"> ****");
		try{
			InitEvent(eventTypeArg, canBubbleArg, cancelableArg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexEventImpl))
			return false;
		return ((JRexEventImpl)obj).peerEvent==peerEvent;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerEvent;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerEvent!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerEvent=0;
		}
	}

    private native String GetType()throws JRexException;
    private native EventTarget GetTarget()throws JRexException;
    private native EventTarget GetCurrentTarget()throws JRexException;
    private native EventTarget GetOriginalTarget()throws JRexException;
    private native EventTarget GetExplicitOriginalTarget()throws JRexException;
    private native short GetEventPhase()throws JRexException;
    private native boolean GetBubbles()throws JRexException;
    private native boolean GetCancelable()throws JRexException;
    private native long GetTimeStamp()throws JRexException;
    private native void StopPropagation()throws JRexException;
    private native void PreventDefault()throws JRexException;
    private native void InitEvent(String eventTypeArg,
    						boolean canBubbleArg,boolean cancelableArg)throws JRexException;
	private native void Finalize()throws JRexException;
}
