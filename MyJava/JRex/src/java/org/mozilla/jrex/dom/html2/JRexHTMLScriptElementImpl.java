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

import org.w3c.dom.html2.HTMLScriptElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLSciptElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLScriptElement
*/
public class JRexHTMLScriptElementImpl extends JRexHTMLElementImpl implements HTMLScriptElement {
	private static final String className	= JRexHTMLScriptElementImpl.class.getName();

	private JRexHTMLScriptElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLScriptElementImpl ****");
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


    public String getHtmlFor(){
    	if(JRexL.on)JRexL.log(className,"**** getHtmlFor I AM HERE ****");
    	String htmlFor = null;
     	try{
      	   htmlFor=GetHtmlFor();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHtmlFor htmlFor<"+htmlFor+"> ****");
		return htmlFor;
    }


    public void setHtmlFor(String htmlFor){
    	if(JRexL.on)JRexL.log(className,"**** setHtmlFor htmlFor<"+htmlFor+"> ****");
    	try{
			SetHtmlFor(htmlFor);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getEvent(){
    	if(JRexL.on)JRexL.log(className,"**** getEvent I AM HERE ****");
    	String event = null;
     	try{
      	   event=GetEvent();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEvent event<"+event+"> ****");
		return event;
    }


    public void setEvent(String event){
    	if(JRexL.on)JRexL.log(className,"**** setEvent event<"+event+"> ****");
    	try{
			SetEvent(event);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getCharset(){
    	if(JRexL.on)JRexL.log(className,"**** getCharset I AM HERE ****");
    	String charset = null;
     	try{
      	   charset=GetCharset();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCharset charset<"+charset+"> ****");
		return charset;
    }


	public void setCharset(String charset){
		if(JRexL.on)JRexL.log(className,"**** setCharset charset<"+charset+"> ****");
		try{
			SetCharset(charset);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public boolean getDefer(){
    	if(JRexL.on)JRexL.log(className,"**** getDefer I AM HERE ****");
    	boolean defer = false;
     	try{
      	   defer=GetDefer();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDefer defer<"+defer+"> ****");
		return defer;
    }


	public void setDefer(boolean defer){
		if(JRexL.on)JRexL.log(className,"**** setDefer defer<"+defer+"> ****");
		try{
			SetDefer(defer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getSrc(){
    	if(JRexL.on)JRexL.log(className,"**** getSrc I AM HERE ****");
    	String src = null;
     	try{
      	   src=GetSrc();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSrc src<"+src+"> ****");
		return src;
    }


    public void setSrc(String src){
    	if(JRexL.on)JRexL.log(className,"**** setSrc src<"+src+"> ****");
    	try{
			SetSrc(src);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getType(){
    	if(JRexL.on)JRexL.log(className,"**** getType I AM HERE ****");
    	String type = null;
     	try{
      	   type=GetType();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType type<"+type+"> ****");
		return type;
    }


    public void setType(String type){
    	if(JRexL.on)JRexL.log(className,"**** setType type<"+type+"> ****");
    	try{
			SetType(type);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    private native String GetText()throws JRexException;
    private native void SetText(String text)throws JRexException;
    private native String GetHtmlFor()throws JRexException;
    private native void SetHtmlFor(String htmlFor)throws JRexException;
    private native String GetEvent()throws JRexException;
    private native void SetEvent(String event)throws JRexException;
    private native String GetCharset()throws JRexException;
    private native void SetCharset(String charset)throws JRexException;
    private native boolean GetDefer()throws JRexException;
    private native void SetDefer(boolean defer)throws JRexException;
    private native String GetSrc()throws JRexException;
    private native void SetSrc(String src)throws JRexException;
    private native String GetType()throws JRexException;
    private native void SetType(String type)throws JRexException;
}