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
import org.w3c.dom.Node;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;


/**
* A class implementing org.w3c.dom.events.EventTarget interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.events.EventTarget
*/
public class JRexEventTargetImpl implements EventTarget {

	private static final String className	= JRexEventTargetImpl.class.getName();
	private int peerEvtTarget=0;
	private java.util.Hashtable evtListnerTable=new java.util.Hashtable();

	private JRexEventTargetImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexEventTargetImpl I AM HERE ****");
	}

	/**
	* Returns the node corresponding to the EventTarget.
	* @return	the target node.
	*/
    public Node getNode(){
		if(JRexL.on)JRexL.log(className,"**** getNode I AM HERE ****");
		Node myNode=null;
		try{
			myNode=GetNode();
			if(JRexL.on)JRexL.log(className,"**** getNode myNode<"+myNode+"> ****");
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return myNode;
	}

    public void addEventListener(String type,EventListener listener,boolean useCapture){
		if(JRexL.on)JRexL.log(className,"**** addEventListener type<"+type+"> listener<"+listener+"> useCapture<"+useCapture+"> ****");
		try{
			EventListenerWrapper wrapObg=new EventListenerWrapper(type, listener,useCapture);
			Integer listnrPeer=(Integer)evtListnerTable.get(wrapObg);
			if(JRexL.on)JRexL.log(className,"**** addEventListener listnrPeer<"+listnrPeer+"> ****");
			if(listnrPeer!=null && listnrPeer.intValue()>0){
				if(JRexL.on)JRexL.log(className,"**** addEventListener Listener has been already Added!!! ****");
				return;
			}
			int listnrPeerInt=AddEventListener(type,listener,useCapture);
			if(JRexL.on)JRexL.log(className,"**** addEventListener listnrPeerInt<"+listnrPeerInt+"> ****");
			if(listnrPeerInt>0)evtListnerTable.put(wrapObg,new Integer(listnrPeerInt));
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public void removeEventListener(String type,EventListener listener,boolean useCapture){
		if(JRexL.on)JRexL.log(className,"**** removeEventListener type<"+type+"> listener<"+listener+"> useCapture<"+useCapture+"> ****");
		EventListenerWrapper wrapObg=new EventListenerWrapper(type, listener,useCapture);
		try{
			Integer listnrPeer=(Integer)evtListnerTable.get(wrapObg);
			if(JRexL.on)JRexL.log(className,"**** removeEventListener listnrPeer<"+listnrPeer+"> ****");
			if(listnrPeer!=null && listnrPeer.intValue()>0){
				RemoveEventListener(type,listnrPeer.intValue(),useCapture);
			}
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		evtListnerTable.remove(wrapObg);
	}

    public boolean dispatchEvent(Event evt)throws EventException{
		if(JRexL.on)JRexL.log(className,"**** dispatchEvent evt<"+evt+"> ****");
		boolean retVal=false;
		try{
			retVal=DispatchEvent(evt);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** dispatchEvent retVal<"+retVal+"> ****");
		return retVal;
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexEventTargetImpl))
			return false;
		return ((JRexEventTargetImpl)obj).peerEvtTarget==peerEvtTarget;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerEvtTarget;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerEvtTarget!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerEvtTarget=0;
		}
	}

	private class EventListenerWrapper{
		String type;
		EventListener listener;
		boolean useCapture;

		EventListenerWrapper(String type, EventListener listener, boolean useCapture){
			this.type=type;
			this.listener=listener;
			this.useCapture=useCapture;
		}

		public int hashCode(){
			return type.hashCode()+
				listener.hashCode()+
					Boolean.toString(useCapture).hashCode();
		}

		public boolean equals(Object obj){
			if(!(obj instanceof EventListenerWrapper))
				return false;
			return ((EventListenerWrapper)obj).type.equals(type)
					&& ((EventListenerWrapper)obj).listener==listener
					&& ((EventListenerWrapper)obj).useCapture==useCapture;
		}
	}


	private native Node GetNode()throws JRexException;
	private native int AddEventListener(String type,EventListener listener,boolean useCapture)throws JRexException;
	private native void RemoveEventListener(String type,int listenerPeer,boolean useCapture)throws JRexException;
    private native boolean DispatchEvent(Event evt)throws EventException, JRexException;
    private native void Finalize()throws JRexException;
}
