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

import org.w3c.dom.html2.HTMLLinkElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLLinkElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLLinkElement
*/
public class JRexHTMLLinkElementImpl extends JRexHTMLElementImpl implements HTMLLinkElement {
	private static final String className	= JRexHTMLLinkElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLLinkElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLLinkElementImpl ****");
	}

    public boolean getDisabled(){
    	if(JRexL.on)JRexL.log(className,"**** getDisabled I AM HERE ****");
    	boolean disabled = false;
     	try{
      	   disabled=GetDisabled();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDisabled disabled<"+disabled+"> ****");
		return disabled;
    }

    public void setDisabled(boolean disabled){
    	if(JRexL.on)JRexL.log(className,"**** setDisabled disabled<"+disabled+"> ****");
		try{
			SetDisabled(disabled);
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

    public String getHref(){
    	if(JRexL.on)JRexL.log(className,"**** getHref I AM HERE ****");
    	String href = null;
     	try{
      	   href=GetHref();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHref href<"+href+"> ****");
		return href;
    }

    public void setHref(String href){
    	if(JRexL.on)JRexL.log(className,"**** setHref href<"+href+"> ****");
		try{
			SetHref(href);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getHreflang(){
    	if(JRexL.on)JRexL.log(className,"**** getHreflang I AM HERE ****");
    	String hreflang = null;
     	try{
      	   hreflang=GetHreflang();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHreflang hreflang<"+hreflang+"> ****");
		return hreflang;
    }

    public void setHreflang(String hreflang){
    	if(JRexL.on)JRexL.log(className,"**** setHreflang href<"+hreflang+"> ****");
		try{
			SetHreflang(hreflang);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getMedia(){
    	if(JRexL.on)JRexL.log(className,"**** getMedia I AM HERE ****");
    	String media = null;
     	try{
      	   media=GetMedia();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMedia media<"+media+"> ****");
		return media;
    }

    public void setMedia(String media){
    	if(JRexL.on)JRexL.log(className,"**** setMedia media<"+media+"> ****");
		try{
			SetMedia(media);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getRel(){
    	if(JRexL.on)JRexL.log(className,"**** getRel I AM HERE ****");
    	String rel = null;
     	try{
      	   rel=GetRel();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRel rel<"+rel+"> ****");
		return rel;
    }

    public void setRel(String rel){
    	if(JRexL.on)JRexL.log(className,"**** setRel rel<"+rel+"> ****");
		try{
			SetRel(rel);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getRev(){
    	if(JRexL.on)JRexL.log(className,"**** getRev I AM HERE ****");
    	String rev = null;
     	try{
      	   rev=GetRev();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRev rev<"+rev+"> ****");
		return rev;
    }

    public void setRev(String rev){
    	if(JRexL.on)JRexL.log(className,"**** setRev rev<"+rev+"> ****");
		try{
			SetRev(rev);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getTarget(){
    	if(JRexL.on)JRexL.log(className,"**** getTarget I AM HERE ****");
    	String target = null;
     	try{
      	   target=GetTarget();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTarget target<"+target+"> ****");
		return target;
    }

    public void setTarget(String target){
    	if(JRexL.on)JRexL.log(className,"**** setTarget target<"+target+"> ****");
		try{
			SetTarget(target);
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


    private native boolean GetDisabled()throws JRexException;
    private native void SetDisabled(boolean disabled)throws JRexException;
    private native String GetCharset()throws JRexException;
    private native void SetCharset(String charset)throws JRexException;
    private native String GetHref()throws JRexException;
    private native void SetHref(String href)throws JRexException;
    private native String GetHreflang()throws JRexException;
    private native void SetHreflang(String hreflang)throws JRexException;
    private native String GetMedia()throws JRexException;
    private native void SetMedia(String media)throws JRexException;
    private native String GetRel()throws JRexException;
    private native void SetRel(String rel)throws JRexException;
    private native String GetRev()throws JRexException;
    private native void SetRev(String rev)throws JRexException;
 	private native String GetTarget()throws JRexException;
    private native void SetTarget(String target)throws JRexException;
    private native String GetType()throws JRexException;
    private native void SetType(String type)throws JRexException;
}
