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
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.DOMImplementationList interface. Just a place holder
* as DOMImplementationList is not implemented by mozilla.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DOMImplementationList
*/

public class JRexDOMImplementationListImpl implements DOMImplementationList {

	private static final String className = JRexDOMImplementationListImpl.class.getName();

	private int peerDOMImplementationList=0;

     /** Intended to be used by JNI */
    private JRexDOMImplementationListImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMImplementationListImpl ****");
	}

 	public DOMImplementation item(int index){
		if(JRexL.on)JRexL.log(className,"**** item index<"+index+"> ****");
		DOMImplementation item=null;
		try{
			item=Item(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** item item<"+item+"> ****");
		return item;
	}

 	public int getLength(){
		if(JRexL.on)JRexL.log(className,"**** getLength ****");
		int length=0;
		try{
			length= GetLength();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLength length<"+length+"> ****");
		return length;
	}


    public boolean equals(Object obj) {
		return (obj instanceof JRexDOMImplementationListImpl)?
			this.peerDOMImplementationList==((JRexDOMImplementationListImpl)obj).peerDOMImplementationList:false;
    }

    public int hashCode(){
		return peerDOMImplementationList;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDOMImplementationList!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDOMImplementationList=0;
		}
	}

	private native DOMImplementation Item(int index)throws JRexException;
    private native int GetLength()throws JRexException;
    private native void Finalize()throws JRexException;
 }

