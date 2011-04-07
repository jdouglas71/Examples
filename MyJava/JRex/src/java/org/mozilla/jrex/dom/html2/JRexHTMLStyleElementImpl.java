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

import org.w3c.dom.html2.HTMLStyleElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLStyleElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLStyleElement
*/
public class JRexHTMLStyleElementImpl extends JRexHTMLElementImpl implements HTMLStyleElement {
	private static final String className	= JRexHTMLStyleElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLStyleElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLStyleElementImpl ****");
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
    private native String GetMedia()throws JRexException;
    private native void SetMedia(String media)throws JRexException;
    private native String GetType()throws JRexException;
    private native void SetType(String type)throws JRexException;
}

