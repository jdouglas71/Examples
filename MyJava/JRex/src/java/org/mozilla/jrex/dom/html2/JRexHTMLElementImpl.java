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

import org.w3c.dom.html2.HTMLElement;
import org.w3c.dom.DOMException;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLElement
*/

public class JRexHTMLElementImpl extends JRexElementImpl implements HTMLElement {

	private static final String className	= JRexHTMLElementImpl.class.getName();

     /** Intended to be used by JNI */
    protected JRexHTMLElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLElementImpl ****");
	}

	public String getId(){
		if(JRexL.on)JRexL.log(className,"**** getId I AM HERE ****");
		String eid=null;
		try{
			eid=GetId();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getId eid<"+eid+"> ****");
		return eid;
	}

	public void setId(String eid)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setId eid<"+eid+"> ****");
		try{
			SetId(eid);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getTitle(){
		if(JRexL.on)JRexL.log(className,"**** getTitle I AM HERE ****");
		String title=null;
		try{
			title=GetTitle();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTitle title<"+title+"> ****");
		return title;
	}

	public void setTitle(String title)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setTitle title<"+title+"> ****");
		try{
			SetTitle(title);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getLang(){
		if(JRexL.on)JRexL.log(className,"**** getLang I AM HERE ****");
		String lang=null;
		try{
			lang=GetLang();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLang lang<"+lang+"> ****");
		return lang;
	}

	public void setLang(String lang)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setLang lang<"+lang+"> ****");
		try{
			SetLang(lang);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getDir(){
		if(JRexL.on)JRexL.log(className,"**** getDir I AM HERE ****");
		String dir=null;
		try{
			dir=GetDir();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDir dir<"+dir+"> ****");
		return dir;
	}

	public void setDir(String dir)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setDir dir<"+dir+"> ****");
		try{
			SetDir(dir);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getClassName(){
		if(JRexL.on)JRexL.log(className,"**** getClassName I AM HERE ****");
		String className=null;
		try{
			className=GetClassName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getClassName className<"+className+"> ****");
		return className;
	}

	public void setClassName(String className)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setClassName className<"+className+"> ****");
		try{
			SetClassName(className);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    private native String GetId()throws JRexException;
    private native void SetId(String id)throws DOMException, JRexException;
    private native String GetTitle()throws JRexException;
    private native void SetTitle(String title)throws DOMException, JRexException;
    private native String GetLang()throws JRexException;
    private native void SetLang(String lang)throws DOMException, JRexException;
    private native String GetDir()throws JRexException;
    private native void SetDir(String dir)throws DOMException, JRexException;
    private native String GetClassName()throws JRexException;
    private native void SetClassName(String className)throws DOMException, JRexException;
}
