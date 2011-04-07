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

import org.w3c.dom.html2.HTMLFormElement;
import org.w3c.dom.html2.HTMLCollection;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLFormElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLFormElement
*/

public class JRexHTMLFormElementImpl extends JRexHTMLElementImpl implements HTMLFormElement {

	private static final String className	= JRexHTMLFormElementImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLFormElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLFormElementImpl ****");
	}

	public HTMLCollection getElements(){
		if(JRexL.on)JRexL.log(className,"**** getElements I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetElements();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElements htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}


	public int getLength(){
		if(JRexL.on)JRexL.log(className,"**** getLength I AM HERE ****");
		int len=0;
		try{
			len=GetLength();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLength len<"+len+"> ****");
		return len;
	}

	public String getName(){
		if(JRexL.on)JRexL.log(className,"**** getName I AM HERE ****");
		String name=null;
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

	public String getAcceptCharset(){
		if(JRexL.on)JRexL.log(className,"**** getAcceptCharset I AM HERE ****");
		String acceptCharset=null;
		try{
			acceptCharset=GetAcceptCharset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAcceptCharset acceptCharset<"+acceptCharset+"> ****");
		return acceptCharset;
	}

	public void setAcceptCharset(String acceptCharset){
		if(JRexL.on)JRexL.log(className,"**** setAcceptCharset acceptCharset<"+acceptCharset+"> ****");
		try{
			SetAcceptCharset(acceptCharset);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getAction(){
		if(JRexL.on)JRexL.log(className,"**** getAction I AM HERE ****");
		String action=null;
		try{
			action=GetAction();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAction action<"+action+"> ****");
		return action;
	}

	public void setAction(String action){
		if(JRexL.on)JRexL.log(className,"**** setAction action<"+action+"> ****");
		try{
			SetAction(action);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getEnctype(){
		if(JRexL.on)JRexL.log(className,"**** getEnctype I AM HERE ****");
		String enctype=null;
		try{
			enctype=GetEnctype();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEnctype enctype<"+enctype+"> ****");
		return enctype;
	}

	public void setEnctype(String enctype){
		if(JRexL.on)JRexL.log(className,"**** setEnctype enctype<"+enctype+"> ****");
		try{
			SetEnctype(enctype);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getMethod(){
		if(JRexL.on)JRexL.log(className,"**** getMethod I AM HERE ****");
		String method=null;
		try{
			method=GetMethod();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMethod method<"+method+"> ****");
		return method;
	}

	public void setMethod(String method){
		if(JRexL.on)JRexL.log(className,"**** setMethod method<"+method+"> ****");
		try{
			SetMethod(method);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getTarget(){
		if(JRexL.on)JRexL.log(className,"**** getTarget I AM HERE ****");
		String target=null;
		try{
			target=GetTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTarget target<"+target+"> ****");
		return target;
	}

	public void setTarget(String target){
		if(JRexL.on)JRexL.log(className,"**** setTarget target<"+target+"> ****");
		try{
			SetTarget(target);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void submit(){
		if(JRexL.on)JRexL.log(className,"**** submit I AM HERE ****");
		try{
			Submit();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void reset(){
		if(JRexL.on)JRexL.log(className,"**** reset I AM HERE ****");
		try{
			Reset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    private native  HTMLCollection GetElements()throws JRexException;
    private native  int GetLength()throws JRexException;
    private native  String GetName()throws JRexException;
    private native  void SetName(String name)throws JRexException;
    private native  String GetAcceptCharset()throws JRexException;
    private native  void SetAcceptCharset(String acceptCharset)throws JRexException;
    private native  String GetAction()throws JRexException;
    private native  void SetAction(String action)throws JRexException;
    private native  String GetEnctype()throws JRexException;
    private native  void SetEnctype(String enctype)throws JRexException;
    private native  String GetMethod()throws JRexException;
    private native  void SetMethod(String method)throws JRexException;
    private native  String GetTarget()throws JRexException;
    private native  void SetTarget(String target)throws JRexException;
    private native  void Submit()throws JRexException;
    private native  void Reset()throws JRexException;
}


