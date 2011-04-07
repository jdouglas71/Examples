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

import org.w3c.dom.DOMLocator;
import org.w3c.dom.DOMError;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.DOMError interface. Just a place holder
* as DOMError is not implemented by mozilla.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DOMError
*/

public class JRexDOMErrorImpl implements DOMError {

	private static final String className = JRexDOMErrorImpl.class.getName();

	private int peerDOMError=0;

     /** Intended to be used by JNI */
    private JRexDOMErrorImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMErrorImpl ****");
	}

 	public short getSeverity(){
		if(JRexL.on)JRexL.log(className,"**** getSeverity ****");
		short svr=0;
		try{
			svr= GetSeverity();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSeverity svr<"+svr+"> ****");
		return svr;
	}

 	public String getMessage(){
		if(JRexL.on)JRexL.log(className,"**** getMessage ****");
		String msg=null;
		try{
			msg=GetMessage();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMessage msg<"+msg+"> ****");
		return msg;
	}

 	public String getType(){
		if(JRexL.on)JRexL.log(className,"**** getType ****");
		String type=null;
		try{
			type=GetType();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType type<"+type+"> ****");
		return type;
	}

 	public Object getRelatedException(){
		if(JRexL.on)JRexL.log(className,"**** getRelatedException ****");
		Object exp=null;
		try{
			exp=GetRelatedException();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRelatedException exp<"+exp+"> ****");
		return exp;
	}

 	public Object getRelatedData(){
		if(JRexL.on)JRexL.log(className,"**** getRelatedData ****");
		Object data=null;
		try{
			data=GetRelatedData();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRelatedData data<"+data+"> ****");
		return data;
	}

 	public DOMLocator getLocation(){
		if(JRexL.on)JRexL.log(className,"**** getLocation ****");
		DOMLocator data=null;
		try{
			data=GetLocation();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLocation data<"+data+"> ****");
		return data;
	}

    public boolean equals(Object obj) {
		return (obj instanceof JRexDOMErrorImpl)?
			this.peerDOMError==((JRexDOMErrorImpl)obj).peerDOMError:false;
    }

    public int hashCode(){
		return peerDOMError;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDOMError!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDOMError=0;
		}
	}

    private native short GetSeverity()throws JRexException;
    private native String GetMessage()throws JRexException;
    private native String GetType()throws JRexException;
    private native Object GetRelatedException()throws JRexException;
    private native Object GetRelatedData()throws JRexException;
    private native DOMLocator GetLocation()throws JRexException;
    private native void Finalize()throws JRexException;
}
