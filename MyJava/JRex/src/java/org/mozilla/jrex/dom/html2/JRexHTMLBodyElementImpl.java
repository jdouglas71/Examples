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

import org.w3c.dom.html2.HTMLBodyElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;
/**
* A class implementing org.w3c.dom.html2.HTMLBodyElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLBodyElement
*/
public class JRexHTMLBodyElementImpl extends JRexHTMLElementImpl implements HTMLBodyElement {
	private static final String className	= JRexHTMLBodyElementImpl.class.getName();

	private JRexHTMLBodyElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLBodyElementImpl ****");
	}

    public String getALink(){
    	if(JRexL.on)JRexL.log(className,"**** getALink I AM HERE ****");
    	String aLink = null;
     	try{
      	   aLink=GetALink();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getALink aLink<"+aLink+"> ****");
		return aLink;
    }


    public void setALink(String aLink){
    	if(JRexL.on)JRexL.log(className,"**** setALink aLink<"+aLink+"> ****");
		try{
			SetALink(aLink);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getBackground(){
    	if(JRexL.on)JRexL.log(className,"**** getBackground I AM HERE ****");
    	String background = null;
     	try{
      	   background=GetBackground();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBackground background<"+background+"> ****");
		return background;
    }


    public void setBackground(String background){
    	if(JRexL.on)JRexL.log(className,"**** setBackground background<"+background+"> ****");
		try{
			SetBackground(background);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getBgColor(){
    	if(JRexL.on)JRexL.log(className,"**** getBgColor I AM HERE ****");
    	String bgColor = null;
     	try{
      	   bgColor=GetBgColor();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBgColor bgColor<"+bgColor+"> ****");
		return bgColor;
    }


    public void setBgColor(String bgColor){
    	if(JRexL.on)JRexL.log(className,"**** setBgColor background<"+bgColor+"> ****");
		try{
			SetBgColor(bgColor);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getLink(){
    	if(JRexL.on)JRexL.log(className,"**** getLink I AM HERE ****");
    	String link = null;
     	try{
      	   link=GetLink();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLink link<"+link+"> ****");
		return link;
    }


    public void setLink(String link){
    	if(JRexL.on)JRexL.log(className,"**** setLink link<"+link+"> ****");
		try{
			SetLink(link);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getText(){
    	if(JRexL.on)JRexL.log(className,"**** getText I AM HERE ****");
    	String text = null;
     	try{
      	   text=GetText();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getText text<"+text+"> ****");
		return text;
    }


    public void setText(String text){
    	if(JRexL.on)JRexL.log(className,"**** setText text<"+text+"> ****");
		try{
			SetText(text);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getVLink(){
    	if(JRexL.on)JRexL.log(className,"**** getVLink I AM HERE ****");
    	String vLink = null;
     	try{
      	   vLink=GetVLink();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getVLink vLink<"+vLink+"> ****");
		return vLink;
    }


    public void setVLink(String vLink){
    	if(JRexL.on)JRexL.log(className,"**** setVLink vLink<"+vLink+"> ****");
		try{
			SetVLink(vLink);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	private native String GetALink()throws JRexException;
    private native void SetALink(String aLink)throws JRexException;
    private native String GetBackground()throws JRexException;
    private native void SetBackground(String background)throws JRexException;
    private native String GetBgColor()throws JRexException;
    private native void SetBgColor(String bgColor)throws JRexException;
    private native String GetLink()throws JRexException;
    private native void SetLink(String link)throws JRexException;
    private native String GetText()throws JRexException;
    private native void SetText(String text)throws JRexException;
    private native String GetVLink()throws JRexException;
    private native void SetVLink(String vLink)throws JRexException;


}
