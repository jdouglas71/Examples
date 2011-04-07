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

import org.w3c.dom.ProcessingInstruction;
import org.w3c.dom.DOMException;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;


/**
* A class implementing org.w3c.dom.ProcessingInstruction interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.ProcessingInstruction
*/

public class JRexProcessingInstructionImpl extends JRexNodeImpl implements ProcessingInstruction {

	private static final String className	= JRexProcessingInstructionImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexProcessingInstructionImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexProcessingInstructionImpl ****");
	}

	public String getData(){
		if(JRexL.on)JRexL.log(className,"**** getData ****");
		String data=null;
		try{
			data=GetData();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getData data<"+data+"> ****");
		return data;
	}

	public String getTarget(){
		if(JRexL.on)JRexL.log(className,"**** getTarget ****");
		String target=null;
		try{
			target=GetData();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTarget target<"+target+"> ****");
		return target;
	}

	public void setData(String data)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setData data<"+data+"> ****");
		try{
			SetData(data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native String GetData()throws JRexException;
	private native String GetTarget()throws JRexException;
	private native void SetData(String data)throws DOMException, JRexException;
}
