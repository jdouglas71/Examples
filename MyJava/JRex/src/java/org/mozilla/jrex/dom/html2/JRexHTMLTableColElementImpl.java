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

import org.w3c.dom.html2.HTMLTableColElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLTableColElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLTableColElement
*/
public class JRexHTMLTableColElementImpl extends JRexHTMLElementImpl implements HTMLTableColElement {
	private static final String className	= JRexHTMLTableColElementImpl.class.getName();

	private JRexHTMLTableColElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLTableColElementImpl ****");
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


    public String getCh(){
    	if(JRexL.on)JRexL.log(className,"**** getCh I AM HERE ****");
    	String ch = null;
     	try{
      	   ch=GetCh();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCh ch<"+ch+"> ****");
		return ch;
    }


    public void setCh(String ch){
    	if(JRexL.on)JRexL.log(className,"**** setCh ch<"+ch+"> ****");
		try{
			SetCh(ch);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getChOff(){
    	if(JRexL.on)JRexL.log(className,"**** getChOff I AM HERE ****");
    	String chOff = null;
     	try{
      	   chOff=GetChOff();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getChOff chOff<"+chOff+"> ****");
		return chOff;
    }


    public void setChOff(String chOff){
    	if(JRexL.on)JRexL.log(className,"**** setChOff chOff<"+chOff+"> ****");
		try{
			SetChOff(chOff);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public int getSpan(){
    	if(JRexL.on)JRexL.log(className,"**** getSpan I AM HERE ****");
    	int span = 0;
     	try{
      	   span=GetSpan();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSpan span<"+span+"> ****");
		return span;
    }


    public void setSpan(int span){
    	if(JRexL.on)JRexL.log(className,"**** setSpan span<"+span+"> ****");
		try{
			SetSpan(span);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getVAlign(){
    	if(JRexL.on)JRexL.log(className,"**** getVAlign I AM HERE ****");
    	String vAlign = null;
     	try{
      	   vAlign=GetVAlign();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getVAlign vAlign<"+vAlign+"> ****");
		return vAlign;
    }


    public void setVAlign(String vAlign){
    	if(JRexL.on)JRexL.log(className,"**** setVAlign vAlign<"+vAlign+"> ****");
		try{
			SetVAlign(vAlign);
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
    private native String GetCh()throws JRexException;
    private native void SetCh(String ch)throws JRexException;
    private native String GetChOff()throws JRexException;
    private native void SetChOff(String chOff)throws JRexException;
    private native int GetSpan()throws JRexException;
    private native void SetSpan(int span)throws JRexException;
    private native String GetVAlign()throws JRexException;
    private native void SetVAlign(String vAlign)throws JRexException;
    private native String GetWidth()throws JRexException;
    private native void SetWidth(String width)throws JRexException;
}