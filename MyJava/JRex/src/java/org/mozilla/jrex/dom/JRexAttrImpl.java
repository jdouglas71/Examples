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

import org.w3c.dom.Attr;
import org.w3c.dom.Element;
import org.w3c.dom.TypeInfo;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* A class implementing org.w3c.dom.Attr interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Attr
*/
public class JRexAttrImpl extends JRexNodeImpl implements Attr {

	private static final String className	= JRexAttrImpl.class.getName();

	/** Intended to be used by JNI */
	private JRexAttrImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexAttrImpl Creation ****");
	}

	public String getName(){
		String name=null;
		try{
			name=GetName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getName name<"+name+"> ****");
		return name;
	}

    public Element getOwnerElement(){
		Element element=null;
		try{
			element= GetOwnerElement();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getOwnerElement element<"+element+"> ****");
		return element;
	}

    public boolean getSpecified(){
		boolean isSpecified=false;
		try{
			isSpecified=GetSpecified();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSpecified isSpecified<"+isSpecified+"> ****");
		return isSpecified;
	}

    public String getValue(){
		String value=null;
		try{
			value=GetValue();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getValue value<"+value+"> ****");
		return value;
	}

    public void setValue(String value)throws org.w3c.dom.DOMException{
		if(JRexL.on)JRexL.log(className,"**** setValue value<"+value+"> ****");
		try{
			SetValue(value);
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

	public boolean isId(){
		boolean isId=false;
		/* Not yet implemented in mozilla
		try{
			isId=IsId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** isId isId<"+isId+"> ****");
		return isId;
	}

	private native String GetName()throws JRexException;
	private native Element GetOwnerElement()throws JRexException;
    private native boolean GetSpecified()throws JRexException;
    private native String GetValue()throws JRexException;
    private native void SetValue(String value)throws org.w3c.dom.DOMException, JRexException;
	//DOM3
    private native TypeInfo GetSchemaTypeInfo()throws JRexException;
    private native boolean IsId()throws JRexException;
}
