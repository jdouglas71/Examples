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
* A class implementing org.w3c.dom.Element interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Element
*/

public class JRexElementImpl extends JRexNodeImpl implements Element {

	private static final String className	= JRexElementImpl.class.getName();

     /** Intended to be used by JNI */
    protected JRexElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexElementImpl ****");
	}

	public String getAttribute(String name){
		if(JRexL.on)JRexL.log(className,"**** getAttribute name<"+name+"> ****");
		String attr=null;
		try{
			attr=GetAttribute(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttribute attr<"+attr+"> ****");
		return attr;
	}

	public Attr getAttributeNode(String name){
		if(JRexL.on)JRexL.log(className,"**** getAttributeNode name<"+name+"> ****");
		Attr attr=null;
		try{
			attr=GetAttributeNode(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttributeNode attr<"+attr+"> ****");
		return attr;
	}

	public Attr getAttributeNodeNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** getAttributeNodeNS namespaceURI<"+namespaceURI+">  localName<"+localName+"> ****");
		Attr attr=null;
		try{
			attr=GetAttributeNodeNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttributeNodeNS attr<"+attr+"> ****");
		return attr;
	}

	public String getAttributeNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** getAttributeNode namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		String attrNS=null;
		try{
			attrNS=GetAttributeNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttributeNode attrNS<"+attrNS+"> ****");
		return attrNS;
	}

	public NodeList getElementsByTagName(String name){
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagName name<"+name+"> ****");
		NodeList nList=null;
		try{
			nList=GetElementsByTagName(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagName nList<"+nList+"> ****");
		return nList;
	}

	public NodeList getElementsByTagNameNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagNameNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		NodeList nListNS=null;
		try{
			nListNS=GetElementsByTagNameNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagNameNS nListNS<"+nListNS+"> ****");
		return nListNS;
	}

	public String getTagName(){
		if(JRexL.on)JRexL.log(className,"**** getTagName ****");
		String name=null;
		try{
			name=GetTagName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTagName name<"+name+"> ****");
		return name;
	}

	public boolean hasAttribute(String name){
		if(JRexL.on)JRexL.log(className,"**** hasAttribute name<"+name+"> ****");
		boolean hasAttr=false;
		try{
			hasAttr=HasAttribute(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** hasAttribute hasAttr<"+hasAttr+"> ****");
		return hasAttr;
	}

	public boolean hasAttributeNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** hasAttributeNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		boolean hasAttrNS=false;
		try{
			hasAttrNS=HasAttributeNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** hasAttributeNS hasAttrNS<"+hasAttrNS+"> ****");
		return hasAttrNS;
	}

	public void removeAttribute(String name)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeAttribute name<"+name+"> ****");
		try{
			RemoveAttribute(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public Attr removeAttributeNode(Attr oldAttr)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeAttributeNode oldAttr<"+oldAttr+"> ****");
		Attr attr=null;
		try{
			attr=RemoveAttributeNode(oldAttr);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** removeAttributeNode attr<"+attr+"> ****");
		return attr;
	}

	public void removeAttributeNS(String namespaceURI, String localName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeAttributeNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		try{
			RemoveAttributeNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void setAttribute(String name, String value)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setAttribute name<"+name+"> value<"+value+"> ****");
		try{
			SetAttribute(name, value);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public Attr setAttributeNode(Attr newAttr)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setAttributeNode newAttr<"+newAttr+"> ****");
		Attr attr=null;
		try{
			attr=SetAttributeNode(newAttr);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** setAttributeNode attr<"+attr+"> ****");
		return attr;
	}

	public Attr setAttributeNodeNS(Attr newAttr)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setAttributeNodeNS newAttr<"+newAttr+"> ****");
		Attr attrNS=null;
		try{
			attrNS=SetAttributeNodeNS(newAttr);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** setAttributeNodeNS attrNS<"+attrNS+"> ****");
		return attrNS;
	}

	public void setAttributeNS(String namespaceURI, String qualifiedName, String value)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setAttributeNS namespaceURI<"+namespaceURI+"> qualifiedName<"+qualifiedName+"> value<"+value+"> ****");
		try{
			SetAttributeNS(namespaceURI, qualifiedName, value);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	//DOM3
	public TypeInfo getSchemaTypeInfo(){
		TypeInfo info=null;
		/* Not yet implemented in mozilla
		try{
			info= GetSchemaTypeInfo();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getSchemaTypeInfo info<"+info+"> ****");
		return info;
	}

    public void setIdAttribute(String name, boolean isId)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setIdAttribute name<"+name+"> isId<"+isId+">****");
		/* Not yet implemented in mozilla
		try{
			SetIdAttribute(name, isId);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
	}

    public void setIdAttributeNS(String namespaceURI,String localName,boolean isId)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setIdAttributeNS namespaceURI<"+namespaceURI+
									"> localName<"+localName+"> isId<"+isId+"> ****");
		/* Not yet implemented in mozilla
		try{
			SetIdAttributeNS(namespaceURI, localName, isId);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
	}

    public void setIdAttributeNode(Attr idAttr,boolean isId)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setAttributeNS idAttr<"+idAttr+"> isId<"+isId+">****");
		/* Not yet implemented in mozilla
		try{
			SetIdAttributeNode(idAttr, isId);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
	}


	private native String GetAttribute(String name)throws JRexException;
	private native Attr GetAttributeNode(String name)throws JRexException;
	private native Attr GetAttributeNodeNS(String namespaceURI, String localName)throws JRexException;
	private native String GetAttributeNS(String namespaceURI, String localName)throws JRexException;
	private native NodeList GetElementsByTagName(String name)throws JRexException;
	private native NodeList GetElementsByTagNameNS(String namespaceURI, String localName)throws JRexException;
	private native String GetTagName()throws JRexException;
	private native boolean HasAttribute(String name)throws JRexException;
	private native boolean HasAttributeNS(String namespaceURI, String localName)throws JRexException;
	private native void RemoveAttribute(String name)throws DOMException, JRexException;
	private native Attr RemoveAttributeNode(Attr oldAttr)throws DOMException, JRexException;
	private native void RemoveAttributeNS(String namespaceURI, String localName)throws DOMException, JRexException;
	private native void SetAttribute(String name, String value)throws DOMException, JRexException;
	private native Attr SetAttributeNode(Attr newAttr)throws DOMException, JRexException;
	private native Attr SetAttributeNodeNS(Attr newAttr)throws DOMException, JRexException;
	private native void SetAttributeNS(String namespaceURI, String qualifiedName, String value)throws DOMException, JRexException;
	//DOM3
	private native TypeInfo GetSchemaTypeInfo()throws JRexException;
        private native void SetIdAttribute(String name,boolean isId)throws DOMException, JRexException;
        private native void SetIdAttributeNS(String namespaceURI,String localName,boolean isId)throws DOMException, JRexException;
        private native void SetIdAttributeNode(Attr idAttr,boolean isId)throws DOMException, JRexException;

}
