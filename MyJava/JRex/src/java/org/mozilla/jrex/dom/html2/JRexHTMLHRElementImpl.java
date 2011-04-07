/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The types of this file are subject to the Mozilla Public
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
 * Alternatively, the types of this file may be used under the terms of
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

import org.w3c.dom.html2.HTMLHRElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLHRElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLHRElement
*/
public class JRexHTMLHRElementImpl extends JRexHTMLElementImpl implements HTMLHRElement {
	private static final String className	= JRexHTMLHRElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLHRElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLHRElementImpl ****");
	}

    public String getAlign(){
    	if(JRexL.on)JRexL.log(className,"**** getAlign I AM HERE ****");
    	String align = null;
     	try{
      	   align=GetAlign();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAlign align<"+align+"> ****");
		return align;
    }

    public void setAlign(String align){
    	if(JRexL.on)JRexL.log(className,"**** setAlign align<"+align+"> ****");
		try{
			SetAlign(align);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public boolean getNoShade(){
    	if(JRexL.on)JRexL.log(className,"**** getType I AM HERE ****");
    	boolean noShade = false;
     	try{
      	   noShade=GetNoShade();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType noShade<"+noShade+"> ****");
		return noShade;
    }

    public void setNoShade(boolean noShade){
    	if(JRexL.on)JRexL.log(className,"**** setSize noShade<"+noShade+"> ****");
		try{
			SetNoShade(noShade);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getSize(){
    	if(JRexL.on)JRexL.log(className,"**** getSize I AM HERE ****");
    	String size = null;
     	try{
      	   size=GetSize();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSize size<"+size+"> ****");
		return size;
    }

    public void setSize(String size){
    	if(JRexL.on)JRexL.log(className,"**** setSize size<"+size+"> ****");
		try{
			SetSize(size);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getWidth(){
    	if(JRexL.on)JRexL.log(className,"**** getWidth I AM HERE ****");
    	String width = null;
     	try{
      	   width=GetWidth();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getWidth width<"+width+"> ****");
		return width;
    }

    public void setWidth(String width){
    	if(JRexL.on)JRexL.log(className,"**** setWidth width<"+width+"> ****");
		try{
			SetWidth(width);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    private native String GetAlign()throws JRexException;
    private native void SetAlign(String align)throws JRexException;
    private native boolean GetNoShade()throws JRexException;
    private native void SetNoShade(boolean noShade)throws JRexException;
    private native String GetSize()throws JRexException;
    private native void SetSize(String size)throws JRexException;
    private native String GetWidth()throws JRexException;
    private native void SetWidth(String width)throws JRexException;
}