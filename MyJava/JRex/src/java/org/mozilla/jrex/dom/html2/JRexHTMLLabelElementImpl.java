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

import org.w3c.dom.html2.HTMLLabelElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLLabelElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLLabelElement
*/

public class JRexHTMLLabelElementImpl extends JRexHTMLElementImpl implements HTMLLabelElement {

	private static final String className	= JRexHTMLLabelElementImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLLabelElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLLabelElementImpl ****");
	}

	public HTMLFormElement getForm(){
		if(JRexL.on)JRexL.log(className,"**** getForm I AM HERE ****");
		HTMLFormElement form=null;
		try{
			form=GetForm();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getForm form<"+form+"> ****");
		return form;
	}

	public String getAccessKey(){
		if(JRexL.on)JRexL.log(className,"**** getAccessKey I AM HERE ****");
		String accessKey=null;
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

	public String getHtmlFor(){
		if(JRexL.on)JRexL.log(className,"**** getHtmlFor I AM HERE ****");
		String htmlFor=null;
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

	private native HTMLFormElement GetForm()throws JRexException;
	private native String GetAccessKey()throws JRexException;
	private native void SetAccessKey(String accessKey)throws JRexException;
	private native String GetHtmlFor()throws JRexException;
	private native void SetHtmlFor(String htmlFor)throws JRexException;
}

