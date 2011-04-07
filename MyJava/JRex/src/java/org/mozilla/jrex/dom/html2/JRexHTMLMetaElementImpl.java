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

import org.w3c.dom.html2.HTMLMetaElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLMetaElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLMetaElement
*/
public class JRexHTMLMetaElementImpl extends JRexHTMLElementImpl implements HTMLMetaElement {
	private static final String className	= JRexHTMLMetaElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLMetaElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLMetaElementImpl ****");
	}

    public String getContent(){
    	if(JRexL.on)JRexL.log(className,"**** getContent I AM HERE ****");
    	String content = null;
     	try{
      	   content=GetContent();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getContent content<"+content+"> ****");
		return content;
    }

    public void setContent(String content){
    	if(JRexL.on)JRexL.log(className,"**** setHttpEquiv content<"+content+"> ****");
		try{
			SetContent(content);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getHttpEquiv(){
    	if(JRexL.on)JRexL.log(className,"**** getHttpEquiv I AM HERE ****");
    	String httpEquiv = null;
     	try{
      	   httpEquiv=GetHttpEquiv();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHttpEquiv httpEquiv<"+httpEquiv+"> ****");
		return httpEquiv;
    }

    public void setHttpEquiv(String httpEquiv){
    	if(JRexL.on)JRexL.log(className,"**** setHttpEquiv httpEquiv<"+httpEquiv+"> ****");
		try{
			SetHttpEquiv(httpEquiv);
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

    public String getScheme(){
    	if(JRexL.on)JRexL.log(className,"**** getScheme I AM HERE ****");
    	String scheme = null;
     	try{
      	   scheme=GetScheme();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getScheme scheme<"+scheme+"> ****");
		return scheme;
    }

    public void setScheme(String scheme){
    	if(JRexL.on)JRexL.log(className,"**** setScheme scheme<"+scheme+"> ****");
		try{
			SetScheme(scheme);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    private native String GetContent()throws JRexException;
    private native void SetContent(String content)throws JRexException;
    private native String GetHttpEquiv()throws JRexException;
    private native void SetHttpEquiv(String httpEquiv)throws JRexException;
    private native String GetName()throws JRexException;
    private native void SetName(String name)throws JRexException;
    private native String GetScheme()throws JRexException;
    private native void SetScheme(String scheme)throws JRexException;
}
