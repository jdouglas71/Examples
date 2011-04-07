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

import org.w3c.dom.DOMConfiguration;
import org.w3c.dom.DOMStringList;
import org.w3c.dom.DOMException;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.DOMConfiguration interface.Just a place holder
* as DOMConfiguration is not implemented by mozilla.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.DOMConfiguration
*/

public class JRexDOMConfigurationImpl implements DOMConfiguration {

	private static final String className	= JRexDOMConfigurationImpl.class.getName();

	private int peerDomCfg=0;

     /** Intended to be used by JNI */
    private JRexDOMConfigurationImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMConfigurationImpl ****");
	}

    public void setParameter(String name, Object value)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setParameter name<"+name+"> value<"+value+"> ****");
		try{
			SetParameter(name, value);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public Object getParameter(String name)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getParameter name<"+name+"> ****");
		Object param=null;
		try{
			param=GetParameter(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getParameter param<"+param+"> ****");
		return param;
	}

 	public boolean canSetParameter(String name, Object value){
		if(JRexL.on)JRexL.log(className,"**** canSetParameter name<"+name+"> value<"+value+"> ****");
		boolean canSetParameter=false;
		try{
			canSetParameter= CanSetParameter(name, value.toString());
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** canSetParameter canSetParameter<"+canSetParameter+"> ****");
		return canSetParameter;
	}

    public DOMStringList getParameterNames()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getParameterNames ****");
		DOMStringList paramList=null;
		try{
			paramList=GetParameterNames();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getParameterNames paramList<"+paramList+"> ****");
		return paramList;
	}

    public boolean equals(Object obj) {
		return (obj instanceof JRexDOMConfigurationImpl)?
			this.peerDomCfg==((JRexDOMConfigurationImpl)obj).peerDomCfg:false;
    }

    public int hashCode(){
		return peerDomCfg;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDomCfg!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDomCfg=0;
		}
	}

    private native void SetParameter(String name,Object value)throws DOMException, JRexException;
    private native String GetParameter(String name)throws DOMException, JRexException;
    private native boolean CanSetParameter(String name, String value)throws JRexException;
	private native DOMStringList GetParameterNames()throws JRexException;
	private native void Finalize()throws JRexException;
}
