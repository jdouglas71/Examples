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

import org.w3c.dom.html2.HTMLAreaElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLAreaElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLAreaElement
*/
public class JRexHTMLAreaElementImpl extends JRexHTMLElementImpl implements HTMLAreaElement {
	private static final String className	= JRexHTMLAreaElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLAreaElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLAreaElementImpl ****");
	}

	public String getAccessKey(){
		if(JRexL.on)JRexL.log(className,"**** getAccessKey I AM HERE ****");
    	String accessKey = null;
     	try{
      	   accessKey=GetAccessKey();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAccessKey accessKey<"+accessKey+"> ****");
		return accessKey;
	}

    public void setAccessKey(String accessKey){
    	if(JRexL.on)JRexL.log(className,"**** setAccessKey accessKey<"+accessKey+"> ****");
		try{
			SetAccessKey(accessKey);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getAlt(){
    	if(JRexL.on)JRexL.log(className,"**** getAlt I AM HERE ****");
    	String alt = null;
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

    public String getCoords(){
    	if(JRexL.on)JRexL.log(className,"**** getCoords I AM HERE ****");
    	String coords = null;
     	try{
      	   coords=GetCoords();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCoords coords<"+coords+"> ****");
		return coords;
    }

    public void setCoords(String coords){
		if(JRexL.on)JRexL.log(className,"**** setCoords coords<"+coords+"> ****");
		try{
			SetCoords(coords);
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

    public boolean getNoHref(){
    	if(JRexL.on)JRexL.log(className,"**** getNoHref I AM HERE ****");
    	boolean noHref = false;
     	try{
      	   noHref=GetNoHref();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNoHref noHref<"+noHref+"> ****");
		return noHref;
    }

    public void setNoHref(boolean noHref){
    	if(JRexL.on)JRexL.log(className,"**** setNoHref noHref<"+noHref+"> ****");
		try{
			SetNoHref(noHref);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getShape(){
    	if(JRexL.on)JRexL.log(className,"**** getShape I AM HERE ****");
    	String shape = null;
     	try{
      	   shape=GetShape();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getShape shape<"+shape + "****");
		return shape;
    }

    public void setShape(String shape){
    	if(JRexL.on)JRexL.log(className,"**** setShape shape<"+shape+"> ****");
		try{
			SetShape(shape);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public int getTabIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getTabIndex I AM HERE ****");
    	int tabIndex = 0;
     	try{
      	   tabIndex=GetTabIndex();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTabIndex tabIndex<"+tabIndex+"> ****");
		return tabIndex;
    }

    public void setTabIndex(int tabIndex){
    	if(JRexL.on)JRexL.log(className,"**** setTabIndex tabIndex<"+tabIndex+"> ****");
		try{
			SetTabIndex(tabIndex);
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

    private native String GetAccessKey()throws JRexException;
    private native void SetAccessKey(String accessKey)throws JRexException;
    private native String GetAlt()throws JRexException;
    private native void SetAlt(String alt)throws JRexException;
    private native String GetCoords()throws JRexException;
    private native void SetCoords(String coords)throws JRexException;
    private native String GetHref()throws JRexException;
    private native void SetHref(String href)throws JRexException;
    private native boolean GetNoHref()throws JRexException;
    private native void SetNoHref(boolean noHref)throws JRexException;
    private native String GetShape()throws JRexException;
    private native void SetShape(String shape)throws JRexException;
    private native int GetTabIndex()throws JRexException;
    private native void SetTabIndex(int tabIndex)throws JRexException;
    private native String GetTarget()throws JRexException;
    private native void SetTarget(String target)throws JRexException;
}

