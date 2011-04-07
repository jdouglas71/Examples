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

import org.w3c.dom.DOMLocator;
import org.w3c.dom.Node;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.DOMLocator interface. Just a place holder
* as DOMLocator is not implemented by mozilla.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DOMLocator
*/

public class JRexDOMLocatorImpl implements DOMLocator {

	private static final String className = JRexDOMLocatorImpl.class.getName();

	private int peerDOMLocator=0;

     /** Intended to be used by JNI */
    private JRexDOMLocatorImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMLocatorImpl ****");
	}

 	public int getLineNumber(){
		if(JRexL.on)JRexL.log(className,"**** getLineNumber ****");
		int lineNumber=0;
		try{
			lineNumber= GetLineNumber();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLineNumber lineNumber<"+lineNumber+"> ****");
		return lineNumber;
	}

 	public int getColumnNumber(){
		if(JRexL.on)JRexL.log(className,"**** getColumnNumber ****");
		int colNumber=0;
		try{
			colNumber= GetColumnNumber();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getColumnNumber colNumber<"+colNumber+"> ****");
		return colNumber;
	}

 	public int getByteOffset(){
		if(JRexL.on)JRexL.log(className,"**** getByteOffset ****");
		int byteOffset=0;
		try{
			byteOffset= GetByteOffset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getByteOffset byteOffset<"+byteOffset+"> ****");
		return byteOffset;
	}

    public int getUtf16Offset(){
		if(JRexL.on)JRexL.log(className,"**** getUtf16Offset ****");
		int utf16Offset=0;
		try{
			utf16Offset= GetUtf16Offset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUtf16Offset utf16Offset<"+utf16Offset+"> ****");
		return utf16Offset;
	}

 	public Node getRelatedNode(){
		if(JRexL.on)JRexL.log(className,"**** getRelatedNode ****");
		Node node=null;
		try{
			node=GetRelatedNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMessage node<"+node+"> ****");
		return node;
	}

 	public String getUri(){
		if(JRexL.on)JRexL.log(className,"**** getUri ****");
		String uri=null;
		try{
			uri=GetUri();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUri uri<"+uri+"> ****");
		return uri;
	}

    public boolean equals(Object obj) {
		return (obj instanceof JRexDOMLocatorImpl)?
			this.peerDOMLocator==((JRexDOMLocatorImpl)obj).peerDOMLocator:false;
    }

    public int hashCode(){
		return peerDOMLocator;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDOMLocator!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDOMLocator=0;
		}
	}

    private native int GetLineNumber()throws JRexException;
    private native int GetColumnNumber()throws JRexException;
    private native int GetByteOffset()throws JRexException;
    private native int GetUtf16Offset()throws JRexException;
    private native Node GetRelatedNode()throws JRexException;
    private native String GetUri()throws JRexException;
    private native void Finalize()throws JRexException;
 }
