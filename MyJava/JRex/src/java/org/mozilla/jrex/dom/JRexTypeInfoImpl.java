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

import org.w3c.dom.DOMImplementation;
import org.w3c.dom.DOMImplementationList;
import org.w3c.dom.TypeInfo;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.TypeInfo interface. Just a place holder
* as TypeInfo is not implemented by mozilla.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.TypeInfo
*/

public class JRexTypeInfoImpl implements TypeInfo {

	private static final String className = JRexTypeInfoImpl.class.getName();

	private int peerTypeInfo=0;

     /** Intended to be used by JNI */
    private JRexTypeInfoImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexTypeInfoImpl ****");
	}

 	public String getTypeName(){
		if(JRexL.on)JRexL.log(className,"**** getTypeName ****");
		String typeName=null;
		try{
			typeName=GetTypeName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTypeName typeName<"+typeName+"> ****");
		return typeName;
	}

 	public String getTypeNamespace(){
		if(JRexL.on)JRexL.log(className,"**** getTypeName ****");
		String typeNameSp=null;
		try{
			typeNameSp=GetTypeNamespace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTypeNamespace typeNameSp<"+typeNameSp+"> ****");
		return typeNameSp;
	}

 	public boolean isDerivedFrom(String typeNamespaceArg,
 										String typeNameArg, int derivationMethod){
		if(JRexL.on)JRexL.log(className,"**** isDerivedFrom typeNamespaceArg<"
								+typeNamespaceArg+"> typeNameArg<"+typeNameArg
										+"> derivationMethod<"+derivationMethod+">****");
		boolean isDerivedFrom=false;
		try{
			isDerivedFrom=IsDerivedFrom(typeNamespaceArg,typeNameArg, derivationMethod);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** isDerivedFrom isDerivedFrom<"+isDerivedFrom+"> ****");
		return isDerivedFrom;
	}


	public boolean equals(Object obj) {
		return (obj instanceof JRexTypeInfoImpl)?
			this.peerTypeInfo==((JRexTypeInfoImpl)obj).peerTypeInfo:false;
    }

    public int hashCode(){
		return peerTypeInfo;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerTypeInfo!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerTypeInfo=0;
		}
	}

    private native String GetTypeName()throws JRexException;
    private native String GetTypeNamespace()throws JRexException;
	private native boolean IsDerivedFrom(String typeNamespaceArg,String typeNameArg,
                                 						int derivationMethod)throws JRexException;
    private native void Finalize()throws JRexException;
 }