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

import org.w3c.dom.DocumentType;
import org.w3c.dom.NamedNodeMap;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;


/**
* A class implementing org.w3c.dom.DocumentType interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DocumentType
*/
public class JRexDocumentTypeImpl extends JRexNodeImpl implements DocumentType {

	private static final String className	= JRexDocumentTypeImpl.class.getName();
    /** Intended to be used by JNI */
    private JRexDocumentTypeImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDocumentTypeImpl Creation ****");
	}

	public NamedNodeMap getEntities(){
		if(JRexL.on)JRexL.log(className,"**** getEntities ****");
		NamedNodeMap nodeMap=null;
		try{
			nodeMap=GetEntities();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEntities nodeMap<"+nodeMap+"> ****");
		return nodeMap;
	}

 	public String getInternalSubset(){
		if(JRexL.on)JRexL.log(className,"**** getInternalSubset ****");
		String intSubset=null;
		try{
			intSubset=GetInternalSubset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getInternalSubset intSubset<"+intSubset+"> ****");
		return intSubset;
	}

 	public String getName(){
		if(JRexL.on)JRexL.log(className,"**** getName ****");
		String name=null;
		try{
			name=GetName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getName name<"+name+"> ****");
		return name;
	}

 	public NamedNodeMap getNotations(){
		if(JRexL.on)JRexL.log(className,"**** getNotations ****");
		NamedNodeMap nodeMap=null;
		try{
			nodeMap=GetNotations();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNotations nodeMap<"+nodeMap+"> ****");
		return nodeMap;
	}

 	public String getPublicId(){
		if(JRexL.on)JRexL.log(className,"**** getPublicId ****");
		String publicId=null;
		try{
			publicId=GetPublicId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getPublicId publicId<"+publicId+"> ****");
		return publicId;
	}

 	public String getSystemId(){
		if(JRexL.on)JRexL.log(className,"**** getSystemId ****");
		String systemId=null;
		try{
			systemId=GetSystemId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSystemId systemId<"+systemId+"> ****");
		return systemId;
	}

	private native NamedNodeMap GetEntities()throws JRexException;
 	private native String GetInternalSubset()throws JRexException;
 	private native String GetName()throws JRexException;
 	private native NamedNodeMap GetNotations()throws JRexException;
 	private native String GetPublicId()throws JRexException;
 	private native String GetSystemId()throws JRexException;
}
