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

package org.mozilla.jrex.dom;

import org.w3c.dom.Text;
import org.w3c.dom.DOMException;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;


/**
* A class implementing org.w3c.dom.Text interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Text
*/

public class JRexTextImpl extends JRexCharacterDataImpl implements Text {

	private static final String className	= JRexTextImpl.class.getName();

     /** Intended to be used by JNI */
    protected JRexTextImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexTextImpl ****");
	}

	public Text splitText(int offset)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** splitText offset<"+offset+"> ****");
		Text text=null;
		try{
			text=SplitText(offset);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** splitText text<"+text+"> ****");
		return text;
	}

	//DOM3
	public boolean isElementContentWhitespace(){
		if(JRexL.on)JRexL.log(className,"**** isElementContentWhitespace ****");
		boolean isElementContentWhitespace=false;
		/* Not yet implemented in mozilla
		try{
			isElementContentWhitespace=IsElementContentWhitespace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** isElementContentWhitespace isElementContentWhitespace<"+isElementContentWhitespace+"> ****");
		return isElementContentWhitespace;
	}

	public String getWholeText(){
		if(JRexL.on)JRexL.log(className,"**** getWholeText ****");
		String text=null;
		/* Not yet implemented in mozilla
		try{
			text=GetWholeText();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getWholeText text<"+text+"> ****");
		return text;
	}

	public Text replaceWholeText(String content)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** replaceWholeText content<"+content+"> ****");
		Text text=null;
		/* Not yet implemented in mozilla
		try{
			text=ReplaceWholeText(content);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** replaceWholeText text<"+text+"> ****");
		return text;
	}

	private native Text SplitText(int offset)throws DOMException, JRexException;
	//DOM3
	private native boolean IsElementContentWhitespace()throws JRexException;
	private native String GetWholeText()throws JRexException;
	private native Text ReplaceWholeText(String content)throws JRexException, DOMException;

}

