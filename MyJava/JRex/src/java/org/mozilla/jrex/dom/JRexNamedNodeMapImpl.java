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

package org.mozilla.jrex.dom;

import org.w3c.dom.*;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;


/**
* A class implementing org.w3c.dom.NamedNodeMap interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.NamedNodeMap
*/

public class JRexNamedNodeMapImpl implements NamedNodeMap {

	private static final String className	= JRexNamedNodeMapImpl.class.getName();

	private int peerNodeMap=0;

     /** Intended to be used by JNI */
    private JRexNamedNodeMapImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexNamedNodeMapImpl ****");
	}

	public int getLength(){
		if(JRexL.on)JRexL.log(className,"**** getLength ****");
		int len=0;
		try{
			len= GetLength();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLength len<"+len+"> ****");
		return len;
	}

	public Node getNamedItem(String name){
		if(JRexL.on)JRexL.log(className,"**** getNamedItem name<"+name+"> ****");
		Node node=null;
		try{
			node=GetNamedItem(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNamedItem node<"+node+"> ****");
		return node;
	}

	public Node getNamedItemNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** getNamedItemNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		Node node=null;
		try{
			node=GetNamedItemNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNamedItemNS node<"+node+"> ****");
		return node;
	}

	public Node item(int index){
		if(JRexL.on)JRexL.log(className,"**** getNamedItem index<"+index+"> ****");
		Node node=null;
		try{
			node=Item(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNamedItem node<"+node+"> ****");
		return node;
	}

	public Node removeNamedItem(String name)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeNamedItem name<"+name+"> ****");
		Node node=null;
		try{
			node=RemoveNamedItem(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** removeNamedItem node<"+node+"> ****");
		return node;
	}

	public Node removeNamedItemNS(String namespaceURI, String localName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeNamedItemNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		Node node=null;
		try{
			node=RemoveNamedItemNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** removeNamedItemNS node<"+node+"> ****");
		return node;
	}

	public Node setNamedItem(Node arg)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setNamedItem arg<"+arg+"> ****");
		Node node=null;
		try{
			node=SetNamedItem(arg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** setNamedItem node<"+node+"> ****");
		return node;
	}

	public Node setNamedItemNS(Node arg)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setNamedItemNS arg<"+arg+"> ****");
		Node node=null;
		try{
			node=SetNamedItemNS(arg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** setNamedItemNS node<"+node+"> ****");
		return node;
	}

    public boolean equals(Object obj) {
		return (obj instanceof JRexNamedNodeMapImpl)?this.peerNodeMap==((JRexNamedNodeMapImpl)obj).peerNodeMap:false;
    }

    public int hashCode(){
		return peerNodeMap;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerNodeMap!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerNodeMap=0;
		}
	}

	private native int GetLength()throws JRexException;
	private native Node GetNamedItem(String name)throws JRexException;
	private native Node GetNamedItemNS(String namespaceURI, String localName)throws JRexException;
	private native Node Item(int index)throws JRexException;
	private native Node RemoveNamedItem(String name)throws DOMException, JRexException;
	private native Node RemoveNamedItemNS(String namespaceURI, String localName)throws DOMException, JRexException;
	private native Node SetNamedItem(Node arg)throws DOMException, JRexException;
	private native Node SetNamedItemNS(Node arg)throws DOMException, JRexException;
	private native void Finalize()throws JRexException;
}
