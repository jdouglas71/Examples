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

import org.w3c.dom.html2.HTMLTableCellElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
/**
* A class implementing org.w3c.dom.html2.HTMLTableCellElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLTableCellElement
*/
public class JRexHTMLTableCellElementImpl extends JRexHTMLElementImpl implements HTMLTableCellElement {
	private static final String className	= JRexHTMLTableCellElementImpl.class.getName();

	private JRexHTMLTableCellElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLTableCellElementImpl ****");
	}

    public int getCellIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getCellIndex I AM HERE ****");
    	int index = 0;
     	try{
      	   index=GetCellIndex();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCellIndex index<"+index+"> ****");
		return index;
    }


    public String getAbbr(){
    	if(JRexL.on)JRexL.log(className,"**** getAbbr I AM HERE ****");
    	String abbr = null;
     	try{
      	   abbr=GetAbbr();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAbbr abbr<"+abbr+"> ****");
		return abbr;
    }


    public void setAbbr(String abbr){
    	if(JRexL.on)JRexL.log(className,"**** setAbbr abbr<"+abbr+"> ****");
		try{
			SetAbbr(abbr);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
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


    public String getAxis(){
    	if(JRexL.on)JRexL.log(className,"**** getAxis I AM HERE ****");
    	String axis = null;
     	try{
      	   axis=GetAxis();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAxis axis<"+axis+"> ****");
		return axis;
    }


    public void setAxis(String axis){
    	if(JRexL.on)JRexL.log(className,"**** setAxis align<"+axis+"> ****");
		try{
			SetAxis(axis);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getBgColor(){
    	if(JRexL.on)JRexL.log(className,"**** getBgColor I AM HERE ****");
    	String bgc = null;
     	try{
      	   bgc=GetBgColor();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBgColor bgc<"+bgc+"> ****");
		return bgc;
    }

    public void setBgColor(String bgColor){
    	if(JRexL.on)JRexL.log(className,"**** setBgColor bgColor<"+bgColor+"> ****");
		try{
			SetBgColor(bgColor);
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

    public int getColSpan(){
    	if(JRexL.on)JRexL.log(className,"**** getColSpan I AM HERE ****");
    	int span = 0;
     	try{
      	   span=GetColSpan();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getColSpan span<"+span+"> ****");
		return span;
    }


    public void setColSpan(int span){
    	if(JRexL.on)JRexL.log(className,"**** setColSpan span<"+span+"> ****");
		try{
			SetColSpan(span);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getHeaders(){
    	if(JRexL.on)JRexL.log(className,"**** getHeaders I AM HERE ****");
    	String hdrs = null;
     	try{
      	   hdrs=GetHeaders();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHeaders hdrs<"+hdrs+"> ****");
		return hdrs;
    }


    public void setHeaders(String hdrs){
    	if(JRexL.on)JRexL.log(className,"**** setHeaders hdrs<"+hdrs+"> ****");
		try{
			SetHeaders(hdrs);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getHeight(){
    	if(JRexL.on)JRexL.log(className,"**** getHeight I AM HERE ****");
    	String height = null;
     	try{
      	   height=GetHeight();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHeight height<"+height+"> ****");
		return height;
    }


    public void setHeight(String height){
    	if(JRexL.on)JRexL.log(className,"**** setHeight height<"+height+"> ****");
		try{
			SetHeight(height);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	public boolean getNoWrap(){
		if(JRexL.on)JRexL.log(className,"**** getNoWrap I AM HERE ****");
		boolean noWrap=false;
		try{
			noWrap=GetNoWrap();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNoWrap noWrap<"+noWrap+"> ****");
		return noWrap;
	}

	public void setNoWrap(boolean noWrap){
		if(JRexL.on)JRexL.log(className,"**** setNoWrap noWrap<"+noWrap+"> ****");
		try{
			SetNoWrap(noWrap);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public int getRowSpan(){
    	if(JRexL.on)JRexL.log(className,"**** getRowSpan I AM HERE ****");
    	int span = 0;
     	try{
      	   span=GetRowSpan();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRowSpan span<"+span+"> ****");
		return span;
    }


    public void setRowSpan(int span){
    	if(JRexL.on)JRexL.log(className,"**** setRowSpan span<"+span+"> ****");
		try{
			SetRowSpan(span);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getScope(){
    	if(JRexL.on)JRexL.log(className,"**** getScope I AM HERE ****");
    	String scope = null;
     	try{
      	   scope=GetScope();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getScope scope<"+scope+"> ****");
		return scope;
    }


    public void setScope(String scope){
    	if(JRexL.on)JRexL.log(className,"**** setScope scope<"+scope+"> ****");
		try{
			SetScope(scope);
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

	private native int GetCellIndex()throws JRexException;
    private native String GetAbbr()throws JRexException;
    private native void SetAbbr(String align)throws JRexException;
    private native String GetAlign()throws JRexException;
    private native void SetAlign(String align)throws JRexException;
    private native String GetAxis()throws JRexException;
    private native void SetAxis(String align)throws JRexException;
    private native String GetBgColor()throws JRexException;
    private native void SetBgColor(String bgColor)throws JRexException;
    private native String GetCh()throws JRexException;
    private native void SetCh(String ch)throws JRexException;
    private native String GetChOff()throws JRexException;
    private native void SetChOff(String chOff)throws JRexException;
    private native String GetVAlign()throws JRexException;
    private native void SetVAlign(String vAlign)throws JRexException;
    private native int GetColSpan()throws JRexException;
    private native void SetColSpan(int span)throws JRexException;
    private native int GetRowSpan()throws JRexException;
    private native void SetRowSpan(int span)throws JRexException;
    private native String GetHeaders()throws JRexException;
    private native void SetHeaders(String hdrs)throws JRexException;
    private native String GetHeight()throws JRexException;
    private native void SetHeight(String height)throws JRexException;
    private native boolean GetNoWrap()throws JRexException;
    private native void SetNoWrap(boolean noWrap)throws JRexException;
    private native String GetScope()throws JRexException;
    private native void SetScope(String scope)throws JRexException;
    private native String GetWidth()throws JRexException;
    private native void SetWidth(String width)throws JRexException;

}
