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
* A class implementing org.w3c.dom.events.MutationEvent interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.events.MutationEvent
*/
public class JRexMutationEventImpl extends JRexEventImpl implements MutationEvent {
	private static final String className	= JRexMutationEventImpl.class.getName();

	private JRexMutationEventImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexMutationEventImpl I AM HERE ****");
	}

    public Node getRelatedNode(){
		if(JRexL.on)JRexL.log(className,"**** getRelatedNode ****");
		Node node=null;
		try{
			node=GetRelatedNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRelatedNode node<"+node+"> ****");
		return node;
	}

    public String getPrevValue(){
		if(JRexL.on)JRexL.log(className,"**** getPrevValue ****");
		String value=null;
		try{
			value=GetPrevValue();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getPrevValue value<"+value+"> ****");
		return value;
	}

    public String getNewValue(){
		if(JRexL.on)JRexL.log(className,"**** getNewValue ****");
		String value=null;
		try{
			value=GetNewValue();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNewValue value<"+value+"> ****");
		return value;
	}

    public String getAttrName(){
		if(JRexL.on)JRexL.log(className,"**** getAttrName ****");
		String attrName=null;
		try{
			attrName=GetAttrName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttrName attrName<"+attrName+"> ****");
		return attrName;
	}

    public short getAttrChange(){
		if(JRexL.on)JRexL.log(className,"**** getAttrChange ****");
		short attrChange=0;
		try{
			attrChange=GetAttrChange();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttrChange attrChange<"+attrChange+"> ****");
		return attrChange;
	}

    public void initMutationEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
                                  	Node relatedNodeArg,String prevValueArg,String newValueArg,
                                  		String attrNameArg,short attrChangeArg){
		if(JRexL.on)JRexL.log(className,"**** initMutationEvent typeArg<"+typeArg+
							"> canBubbleArg<"+canBubbleArg+"> cancelableArg<"+cancelableArg+
							"> relatedNodeArg<"+relatedNodeArg+"> prevValueArg<"+prevValueArg+
							"> newValueArg<"+newValueArg+"> attrNameArg<"+attrNameArg+"> attrChangeArg<"+attrChangeArg+"> ****");
		try{
			InitMutationEvent(typeArg, canBubbleArg, cancelableArg, relatedNodeArg,
										prevValueArg, newValueArg, attrNameArg, attrChangeArg );
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    private native Node GetRelatedNode()throws JRexException;
    private native String GetPrevValue()throws JRexException;
    private native String GetNewValue()throws JRexException;
    private native String GetAttrName()throws JRexException;
    private native short GetAttrChange()throws JRexException;
    private native void InitMutationEvent(String typeArg,boolean canBubbleArg,boolean cancelableArg,
                                  	Node relatedNodeArg,String prevValueArg,String newValueArg,
                                  		String attrNameArg,short attrChangeArg)throws JRexException;
}
