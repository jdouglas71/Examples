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

import org.w3c.dom.html2.HTMLModElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLModElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLModElement
*/

public class JRexHTMLModElementImpl extends JRexHTMLElementImpl implements HTMLModElement {

	private static final String className	= JRexHTMLModElementImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLModElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLModElementImpl ****");
	}

	public String getCite(){
		if(JRexL.on)JRexL.log(className,"**** getCite I AM HERE ****");
		String cite=null;
		try{
			cite=GetCite();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCite cite<"+cite+"> ****");
		return cite;
	}

	public void setCite(String cite){
		if(JRexL.on)JRexL.log(className,"**** setCite cite<"+cite+"> ****");
		try{
			SetCite(cite);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getDateTime(){
		if(JRexL.on)JRexL.log(className,"**** getDateTime I AM HERE ****");
		String dateTime=null;
		try{
			dateTime=GetDateTime();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDateTime dateTime<"+dateTime+"> ****");
		return dateTime;
	}

	public void setDateTime(String dateTime){
		if(JRexL.on)JRexL.log(className,"**** setDateTime dateTime<"+dateTime+"> ****");
		try{
			SetDateTime(dateTime);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native String GetCite()throws JRexException;
	private native void SetCite(String cite)throws JRexException;
	private native String GetDateTime()throws JRexException;
	private native void SetDateTime(String dateTime)throws JRexException;

}
