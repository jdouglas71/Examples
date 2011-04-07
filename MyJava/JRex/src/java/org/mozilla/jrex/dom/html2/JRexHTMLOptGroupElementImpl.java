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

import org.w3c.dom.html2.HTMLSelectElement;
import org.w3c.dom.html2.HTMLOptGroupElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.w3c.dom.html2.HTMLElement;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

import org.w3c.dom.DOMException;

public class JRexHTMLOptGroupElementImpl extends JRexHTMLElementImpl implements HTMLOptGroupElement {
	private static final String className	= JRexHTMLOptGroupElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLOptGroupElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLOptGroupElementImpl ****");
	}

    public boolean getDisabled(){
    	if(JRexL.on)JRexL.log(className,"**** getDisabled I AM HERE ****");
		boolean disabled=false;
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
    public String getLabel(){
    	if(JRexL.on)JRexL.log(className,"**** getLabel I AM HERE ****");
    	String label = null;
     	try{
      	   label=GetLabel();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLabel label<"+label+"> ****");
		return label;
    }
    public void setLabel(String label){
    	if(JRexL.on)JRexL.log(className,"**** setLabel label<"+label+"> ****");
		try{
			SetLabel(label);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }
    private native boolean GetDisabled()throws JRexException;
    private native void SetDisabled(boolean disabled)throws JRexException;
    private native String GetLabel()throws JRexException;
    private native void SetLabel(String label)throws JRexException;
}