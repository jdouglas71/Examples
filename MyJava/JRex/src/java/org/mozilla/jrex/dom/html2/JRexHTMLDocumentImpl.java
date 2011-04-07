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

import org.w3c.dom.html2.HTMLDocument;
import org.w3c.dom.html2.HTMLElement;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.DOMException;
import org.w3c.dom.html2.HTMLCollection;
import org.mozilla.jrex.dom.JRexDocumentImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLDocument interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLDocument
*/

public class JRexHTMLDocumentImpl extends JRexDocumentImpl implements HTMLDocument {

	private static final String className	= JRexHTMLDocumentImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLDocumentImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLDocumentImpl ****");
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

	public void setTitle(String title){
		if(JRexL.on)JRexL.log(className,"**** setTitle title<"+title+"> ****");
		try{
			SetTitle(title);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getReferrer(){
		if(JRexL.on)JRexL.log(className,"**** getReferrer I AM HERE ****");
		String refr=null;
		try{
			refr=GetReferrer();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getReferrer refr<"+refr+"> ****");
		return refr;
	}

	public String getDomain(){
		if(JRexL.on)JRexL.log(className,"**** getDomain I AM HERE ****");
		String domain=null;
		try{
			domain=GetDomain();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDomain domain<"+domain+"> ****");
		return domain;
	}

	public String getURL(){
		if(JRexL.on)JRexL.log(className,"**** getURL I AM HERE ****");
		String url=null;
		try{
			url=GetURL();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getURL url<"+url+"> ****");
		return url;
	}

	public HTMLElement getBody(){
		if(JRexL.on)JRexL.log(className,"**** getBody I AM HERE ****");
		HTMLElement body=null;
		try{
			body=GetBody();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBody body<"+body+"> ****");
		return body;
	}

	public void setBody(HTMLElement body){
		if(JRexL.on)JRexL.log(className,"**** setBody body<"+body+"> ****");
		try{
			SetBody(body);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public HTMLCollection getImages(){
		if(JRexL.on)JRexL.log(className,"**** getImages I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetImages();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getImages htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}

	public HTMLCollection getApplets(){
		if(JRexL.on)JRexL.log(className,"**** getApplets I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetApplets();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getApplets htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}

	public HTMLCollection getLinks(){
		if(JRexL.on)JRexL.log(className,"**** getLinks I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetLinks();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLinks htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}

	public HTMLCollection getForms(){
		if(JRexL.on)JRexL.log(className,"**** getForms I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetForms();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getForms htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}

	public HTMLCollection getAnchors(){
		if(JRexL.on)JRexL.log(className,"**** getAnchors I AM HERE ****");
		HTMLCollection htmlCol=null;
		try{
			htmlCol=GetAnchors();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAnchors htmlCol<"+htmlCol+"> ****");
		return htmlCol;
	}

	public String getCookie(){
		if(JRexL.on)JRexL.log(className,"**** getCookie I AM HERE ****");
		String cookie=null;
		try{
			cookie=GetCookie();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCookie cookie<"+cookie+"> ****");
		return cookie;
	}

	public void setCookie(String cookie)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setCookie cookie<"+cookie+"> ****");
		try{
			SetCookie(cookie);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void open()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** open I AM HERE ****");
		try{
			Open();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void close()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** close I AM HERE ****");
		try{
			Close();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void write(String text)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** write text<"+text+"> ****");
		try{
			Write(text);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void writeln(String text)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** writeln text<"+text+"> ****");
		try{
			Writeln(text);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public NodeList getElementsByName(String elementName){
		if(JRexL.on)JRexL.log(className,"**** getElementsByName elementName<"+elementName+"> ****");
		NodeList list=null;
		try{
			list=GetElementsByName(elementName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementsByName list<"+list+"> ****");
		return list;
	}

    private native String GetTitle()throws JRexException;
    private native void SetTitle(String title)throws JRexException;
    private native String GetReferrer()throws JRexException;
    private native String GetDomain()throws JRexException;
    private native String GetURL()throws JRexException;
    private native HTMLElement GetBody()throws JRexException;
    private native void SetBody(HTMLElement body)throws JRexException;
    private native HTMLCollection GetImages()throws JRexException;
    private native HTMLCollection GetApplets()throws JRexException;
    private native HTMLCollection GetLinks()throws JRexException;
    private native HTMLCollection GetForms()throws JRexException;
    private native HTMLCollection GetAnchors()throws JRexException;
    private native String GetCookie()throws JRexException;
    private native void SetCookie(String cookie)throws DOMException, JRexException;
    private native void Open()throws DOMException, JRexException;
    private native void Close()throws DOMException, JRexException;
    private native void Write(String text)throws DOMException, JRexException;
    private native void Writeln(String text)throws DOMException, JRexException;
    private native NodeList GetElementsByName(String elementName)throws JRexException;
}
