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

import org.w3c.dom.Entity;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.Entity interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Entity
*/

public class JRexEntityImpl extends JRexNodeImpl implements Entity {

	private static final String className	= JRexEntityImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexEntityImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexEntityImpl ****");
	}

	public String getNotationName(){
		if(JRexL.on)JRexL.log(className,"**** getNotationName ****");
		String notName=null;
		try{
			notName=GetNotationName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNotationName notName<"+notName+"> ****");
		return notName;
	}

	public String getPublicId(){
		if(JRexL.on)JRexL.log(className,"**** getPublicId ****");
		String pubID=null;
		try{
			pubID=GetPublicId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getPublicId pubID<"+pubID+"> ****");
		return pubID;
	}

	public String getSystemId(){
		if(JRexL.on)JRexL.log(className,"**** getSystemId ****");
		String sysID=null;
		try{
			sysID=GetSystemId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSystemId sysID<"+sysID+"> ****");
		return sysID;

	}

	//DOM3
	public String getInputEncoding(){
		if(JRexL.on)JRexL.log(className,"**** getInputEncoding ****");
		String iEncode=null;
		/* Not yet implemented in mozilla
		try{
			iEncode=GetInputEncoding();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getInputEncoding iEncode<"+iEncode+"> ****");
		return iEncode;
	}

	public String getXmlEncoding(){
		if(JRexL.on)JRexL.log(className,"**** getXmlEncoding ****");
		String xmlEncode=null;
		/* Not yet implemented in mozilla
		try{
			xmlEncode=GetXmlEncoding();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getXmlEncoding xmlEncode<"+xmlEncode+"> ****");
		return xmlEncode;
	}

	public String getXmlVersion(){
		if(JRexL.on)JRexL.log(className,"**** getXmlVersion ****");
		String xmlVer=null;
		/* Not yet implemented in mozilla
		try{
			xmlVer=GetXmlVersion();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getXmlVersion xmlVer<"+xmlVer+"> ****");
		return xmlVer;
	}

	private native String GetNotationName()throws JRexException;
	private native String GetPublicId()throws JRexException;
	private native String GetSystemId()throws JRexException;
	//DOM3
	private native String GetInputEncoding()throws JRexException;
	private native String GetXmlEncoding()throws JRexException;
	private native String GetXmlVersion()throws JRexException;
}
