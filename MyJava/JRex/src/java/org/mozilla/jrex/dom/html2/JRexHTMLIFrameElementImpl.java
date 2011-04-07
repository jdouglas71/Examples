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

import org.w3c.dom.html2.HTMLIFrameElement;
import org.w3c.dom.Document;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLIFrameElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLIFrameElement
*/
public class JRexHTMLIFrameElementImpl extends JRexHTMLElementImpl implements HTMLIFrameElement {
	private static final String className	= JRexHTMLIFrameElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLIFrameElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLIFrameElementImpl ****");
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

    public String getFrameBorder(){
    	if(JRexL.on)JRexL.log(className,"**** getFrameBorder I AM HERE ****");
    	String frameBorder = null;
     	try{
      	   frameBorder=GetFrameBorder();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFrameBorder frameBorder<"+frameBorder+"> ****");
		return frameBorder;
    }

    public void setFrameBorder(String frameBorder){
    	if(JRexL.on)JRexL.log(className,"**** setFrameBorder frameBorder<"+frameBorder+"> ****");
		try{
			SetFrameBorder(frameBorder);
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


    public String getLongDesc(){
    	if(JRexL.on)JRexL.log(className,"**** getLongDesc I AM HERE ****");
    	String longDesc = null;
     	try{
      	   longDesc=GetLongDesc();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLongDesc longDesc<"+longDesc+"> ****");
		return longDesc;
    }

    public void setLongDesc(String longDesc){
    	if(JRexL.on)JRexL.log(className,"**** setLongDesc longDesc<"+longDesc+"> ****");
		try{
			SetLongDesc(longDesc);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }


    public String getMarginHeight(){
    	if(JRexL.on)JRexL.log(className,"**** getMarginHeight I AM HERE ****");
    	String marginHeight = null;
     	try{
      	   marginHeight=GetMarginHeight();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMarginHeight marginHeight<"+marginHeight+"> ****");
		return marginHeight;
    }

    public void setMarginHeight(String marginHeight){
    	if(JRexL.on)JRexL.log(className,"**** setMarginHeight marginHeight<"+marginHeight+"> ****");
		try{
			SetMarginHeight(marginHeight);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getMarginWidth(){
    	if(JRexL.on)JRexL.log(className,"**** getMarginWidth I AM HERE ****");
    	String marginWidth = null;
     	try{
      	   marginWidth=GetMarginWidth();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMarginWidth marginWidth<"+marginWidth+"> ****");
		return marginWidth;
    }

    public void setMarginWidth(String marginWidth){
    	if(JRexL.on)JRexL.log(className,"**** setMarginWidth marginWidth<"+marginWidth+"> ****");
		try{
			SetMarginWidth(marginWidth);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getName(){
    	if(JRexL.on)JRexL.log(className,"**** getName I AM HERE ****");
    	String name = null;
     	try{
      	   name=GetName();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getName name<"+name+"> ****");
		return name;
    }

    public void setName(String name){
    	if(JRexL.on)JRexL.log(className,"**** setName name<"+name+"> ****");
		try{
			SetName(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getScrolling(){
    	if(JRexL.on)JRexL.log(className,"**** getScrolling I AM HERE ****");
    	String scrolling = null;
     	try{
      	   scrolling=GetScrolling();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getScrolling scrolling<"+scrolling+"> ****");
		return scrolling;
    }

    public void setScrolling(String scrolling){
    	if(JRexL.on)JRexL.log(className,"**** setScrolling scrolling<"+scrolling+"> ****");
		try{
			SetScrolling(scrolling);
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

	public Document getContentDocument(){
		if(JRexL.on)JRexL.log(className,"**** getContentDocument I AM HERE ****");
		Document doc=null;
		try{
			doc=GetContentDocument();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getContentDocument doc<"+doc+"> ****");
		return doc;
	}

    private native String GetAlign()throws JRexException;
    private native void SetAlign(String frameBorder)throws JRexException;
	private native String GetFrameBorder()throws JRexException;
    private native void SetFrameBorder(String frameBorder)throws JRexException;
    private native String GetHeight()throws JRexException;
    private native void SetHeight(String height)throws JRexException;
    private native String GetLongDesc()throws JRexException;
    private native void SetLongDesc(String longDesc)throws JRexException;
    private native String GetMarginHeight()throws JRexException;
    private native void SetMarginHeight(String marginHeight)throws JRexException;
    private native String GetMarginWidth()throws JRexException;
    private native void SetMarginWidth(String marginWidth)throws JRexException;
    private native String GetName()throws JRexException;
    private native void SetName(String name)throws JRexException;
    private native String GetScrolling()throws JRexException;
    private native void SetScrolling(String scrolling)throws JRexException;
    private native String GetWidth()throws JRexException;
    private native void SetWidth(String width)throws JRexException;
    private native String GetSrc()throws JRexException;
    private native void SetSrc(String src)throws JRexException;
    private native Document GetContentDocument()throws JRexException;
}
