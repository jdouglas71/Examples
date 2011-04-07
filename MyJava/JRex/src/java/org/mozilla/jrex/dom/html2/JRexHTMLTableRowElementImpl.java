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

import org.w3c.dom.html2.HTMLTableRowElement;
import org.w3c.dom.html2.HTMLElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
import org.w3c.dom.DOMException;
import org.w3c.dom.html2.HTMLCollection;
/**
* A class implementing org.w3c.dom.html2.HTMLTableRowElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLTableRowElement
*/
public class JRexHTMLTableRowElementImpl extends JRexHTMLElementImpl implements HTMLTableRowElement {
	private static final String className	= JRexHTMLTableRowElementImpl.class.getName();

	private JRexHTMLTableRowElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLTableRowElementImpl ****");
	}

    public int getRowIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getRowIndex I AM HERE ****");
    	int index = 0;
     	try{
      	   index=GetRowIndex();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRowIndex index<"+index+"> ****");
		return index;
    }


    public int getSectionRowIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getSectionRowIndex I AM HERE ****");
    	int index = 0;
     	try{
      	   index=GetSectionRowIndex();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSectionRowIndex index<"+index+"> ****");
		return index;
    }

	public HTMLCollection getCells(){
		if(JRexL.on)JRexL.log(className,"**** getCells I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetCells();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCells htmlCol<"+htmlCol+"> ****");
		return htmlCol;
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

    public HTMLElement insertCell(int index)
                                 throws DOMException{
        HTMLElement cell = null;
    	if(JRexL.on)JRexL.log(className,"**** insertCell() I AM HERE ****");
		try{
			cell = InsertCell(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** insertCell cell<"+cell+"> ****");
		return cell;
	}


    public void deleteCell(int index)
                          throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** deleteCell() I AM HERE ****");
		try{
			DeleteCell(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native int GetRowIndex()throws JRexException;
	private native int GetSectionRowIndex()throws JRexException;
	private native HTMLCollection GetCells()throws JRexException;
    private native String GetAlign()throws JRexException;
    private native void SetAlign(String align)throws JRexException;
    private native String GetBgColor()throws JRexException;
    private native void SetBgColor(String bgColor)throws JRexException;
    private native String GetCh()throws JRexException;
    private native void SetCh(String ch)throws JRexException;
    private native String GetChOff()throws JRexException;
    private native void SetChOff(String chOff)throws JRexException;
    private native String GetVAlign()throws JRexException;
    private native void SetVAlign(String vAlign)throws JRexException;
    private native  HTMLElement InsertCell(int index)throws DOMException,JRexException;
    private native  void DeleteCell(int index)throws DOMException,JRexException;
}
