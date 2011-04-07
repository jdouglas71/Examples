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

package org.mozilla.jrex.dom.html2;

import org.w3c.dom.html2.HTMLBaseFontElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLBaseFontElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLBaseFontElement
*/

public class JRexHTMLBaseFontElementImpl extends JRexHTMLElementImpl implements HTMLBaseFontElement {

	private static final String className	= JRexHTMLBaseFontElementImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLBaseFontElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLBaseFontElementImpl ****");
	}

	public String getColor(){
		if(JRexL.on)JRexL.log(className,"**** getColor I AM HERE ****");
		String color=null;
		try{
			color=GetColor();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getColor color<"+color+"> ****");
		return color;
	}

	public void setColor(String color){
		if(JRexL.on)JRexL.log(className,"**** setColor color<"+color+"> ****");
		try{
			SetColor(color);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getFace(){
		if(JRexL.on)JRexL.log(className,"**** getFace I AM HERE ****");
		String face=null;
		try{
			face=GetFace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFace face<"+face+"> ****");
		return face;
	}

	public void setFace(String face){
		if(JRexL.on)JRexL.log(className,"**** setFace face<"+face+"> ****");
		try{
			SetFace(face);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public int getSize(){
		if(JRexL.on)JRexL.log(className,"**** getSize I AM HERE ****");
		int size=0;
		try{
			size=GetSize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSize size<"+size+"> ****");
		return size;
	}

	public void setSize(int size){
		if(JRexL.on)JRexL.log(className,"**** setSize size<"+size+"> ****");
		try{
			SetSize(size);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native String GetColor()throws JRexException;
	private native void SetColor(String color)throws JRexException;
	private native String GetFace()throws JRexException;
	private native void SetFace(String face)throws JRexException;
	private native int GetSize()throws JRexException;
	private native void SetSize(int size)throws JRexException;
}
