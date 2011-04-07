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

import org.w3c.dom.html2.HTMLImageElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.w3c.dom.html2.HTMLElement;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

import org.w3c.dom.DOMException;

/**
* A class implementing org.w3c.dom.html2.JRexHTMLImageElementImpl interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.JRexHTMLImageElementImpl
*/

public class JRexHTMLImageElementImpl extends JRexHTMLElementImpl implements HTMLImageElement {
    private static final String className	= JRexHTMLImageElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLImageElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLImageElementImpl ****");
	}

    public String getName()
    {
     	if(JRexL.on)JRexL.log(className,"**** getName I AM HERE ****");
		String name=null;
		try{
			name=GetName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getName name<"+name+"> ****");
		return name;
    }

    public void setName(String name)
    {
      	if(JRexL.on)JRexL.log(className,"**** setName name<"+name+"> ****");
		try{
			SetName(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public String getAlign()
    {
       if(JRexL.on)JRexL.log(className,"**** getAlign I AM HERE ****");
		String align=null;
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

    public String getAlt(){
       if(JRexL.on)JRexL.log(className,"**** getAlt I AM HERE ****");
		String alt=null;
		try{
			alt=GetAlt();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAlt alt<"+alt+"> ****");
		return alt;
	}

    public void setAlt(String alt){
      	if(JRexL.on)JRexL.log(className,"**** setAlt alt<"+alt+"> ****");
		try{
			SetAlt(alt);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public String getBorder(){
       if(JRexL.on)JRexL.log(className,"**** getBorder I AM HERE ****");
		String border=null;
		try{
			border=GetBorder();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBorder border<"+border+"> ****");
		return border;
	}

    public void setBorder(String border){
      	if(JRexL.on)JRexL.log(className,"**** setBorder border<"+border+"> ****");
		try{
			SetBorder(border);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public int getHeight(){
       if(JRexL.on)JRexL.log(className,"**** getHeight I AM HERE ****");
		int height=0;
		try{
			height=GetHeight();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHeight height<"+height+"> ****");
		return height;
	}

    public void setHeight(int height){
      	if(JRexL.on)JRexL.log(className,"**** setHeight height<"+height+"> ****");
		try{
			SetHeight(height);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public int getHspace(){
       if(JRexL.on)JRexL.log(className,"**** getHspace I AM HERE ****");
		int hspace=0;
		try{
			hspace=GetHspace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHspace hspace<"+hspace+"> ****");
		return hspace;
	}

    public void setHspace(int hspace){
      	if(JRexL.on)JRexL.log(className,"**** setHspace hspace<"+hspace+"> ****");
		try{
			SetHspace(hspace);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public boolean getIsMap(){
       if(JRexL.on)JRexL.log(className,"**** getIsMap I AM HERE ****");
		boolean isMap=false;
		try{
			isMap=GetIsMap();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getIsMap isMap<"+isMap+"> ****");
		return isMap;
	}


    public void setIsMap(boolean isMap){
      	if(JRexL.on)JRexL.log(className,"**** setIsMap isMap<"+isMap+"> ****");
		try{
			SetIsMap(isMap);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public String getLongDesc(){
       if(JRexL.on)JRexL.log(className,"**** getLongDesc I AM HERE ****");
		String longDesc=null;
		try{
			longDesc=GetLongDesc();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLongDesc LongDesc<"+longDesc+"> ****");
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

    public String getSrc(){
       if(JRexL.on)JRexL.log(className,"**** getSrc I AM HERE ****");
		String src=null;
		try{
			src=GetSrc();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSrc src<"+src+"> ****");
		return src;
	}

    public void setSrc(String src){
      	if(JRexL.on)JRexL.log(className,"**** setSrc Src<"+src+"> ****");
		try{
			SetSrc(src);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public String getUseMap(){
       if(JRexL.on)JRexL.log(className,"**** getUseMap I AM HERE ****");
		String useMap=null;
		try{
			useMap=GetUseMap();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUseMap useMap<"+useMap+"> ****");
		return useMap;
	}

    public void setUseMap(String useMap){
      	if(JRexL.on)JRexL.log(className,"**** setUseMap UseMap<"+useMap+"> ****");
		try{
			SetUseMap(useMap);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public int getVspace(){
       if(JRexL.on)JRexL.log(className,"**** getVspace I AM HERE ****");
		int vspace=0;
		try{
			vspace=GetVspace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getVspace Vspace<"+vspace+"> ****");
		return vspace;
	}

    public void setVspace(int vspace){
      	if(JRexL.on)JRexL.log(className,"**** setVspace Vspace<"+vspace+"> ****");
		try{
			SetVspace(vspace);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

    public int getWidth(){
       if(JRexL.on)JRexL.log(className,"**** getWidth I AM HERE ****");
		int width=0;
		try{
			width=GetWidth();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getWidth Width<"+width+"> ****");
		return width;
	}

    public void setWidth(int width){
      	if(JRexL.on)JRexL.log(className,"**** setWidth width<"+width+"> ****");
		try{
			SetWidth(width);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

    }

	 private native String GetName()throws JRexException;
	 private native String GetAlign()throws JRexException;
	 private native String GetAlt()throws JRexException;
	 private native String GetBorder()throws JRexException;
	 private native int    GetHeight()throws JRexException;
	 private native int GetHspace()throws JRexException;
	 private native boolean GetIsMap()throws JRexException;
	 private native String GetLongDesc()throws JRexException;
	 private native String GetSrc()throws JRexException;
	 private native String GetUseMap()throws JRexException;
	 private native int GetVspace()throws JRexException;
	 private native int GetWidth()throws JRexException;

	 public native void SetAlign(String align)throws JRexException;
	 public native void SetAlt(String alt)throws JRexException;
	 public native void SetBorder(String border)throws JRexException;
	 public native void SetHeight(int height)throws JRexException;
	 public native void SetHspace(int hspace)throws JRexException;
	 public native void SetIsMap(boolean isMap)throws JRexException;
	 public native void SetLongDesc(String longDesc)throws JRexException;
	 public native void SetName(String name)throws JRexException;
	 public native void SetSrc(String src)throws JRexException;
	 public native void SetUseMap(String useMap)throws JRexException;
	 public native void SetVspace(int vspace)throws JRexException;
	 public native void SetWidth(int width)throws JRexException;

}