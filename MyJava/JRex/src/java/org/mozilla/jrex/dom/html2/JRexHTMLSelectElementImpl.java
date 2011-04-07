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

import org.w3c.dom.html2.HTMLSelectElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.w3c.dom.html2.HTMLOptionsCollection;
import org.w3c.dom.html2.HTMLElement;
import org.w3c.dom.html2.HTMLOptionElement;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

import org.w3c.dom.DOMException;
/**
* A class implementing org.w3c.dom.html2.HTMLSelectElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLSelectElement
*/
public class JRexHTMLSelectElementImpl extends JRexHTMLElementImpl implements HTMLSelectElement {
	private static final String className	= JRexHTMLSelectElementImpl.class.getName();

	/** Intended to be used by JNI */
    private JRexHTMLSelectElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLSelectElementImpl ****");
	}

    public String getType()
    {
    	if(JRexL.on)JRexL.log(className,"**** getType I AM HERE ****");
    	String type = null;
     	try{
      	   type=GetType();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType type<"+type+"> ****");
		return type;
    }

    public int getSelectedIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getSelectedIndex I AM HERE ****");
    	int index = 0;
     	try{
      	   index=GetSelectedIndex();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSelectedIndex index<"+index+"> ****");
		return index;
    }

    public void setSelectedIndex(int selectedIndex){
    	if(JRexL.on)JRexL.log(className,"**** setSelectedIndex selectedIndex<"+selectedIndex+"> ****");
		try{
			SetSelectedIndex(selectedIndex);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public String getValue(){
       	if(JRexL.on)JRexL.log(className,"**** getValue I AM HERE ****");
    	String value = null;
     	try{
      	   value=GetValue();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getValue value<"+value+"> ****");
		return value;
    }

    public void setValue(String value){
    	if(JRexL.on)JRexL.log(className,"**** setValue value<"+value+"> ****");
		try{
			SetValue(value);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public int getLength(){
    	if(JRexL.on)JRexL.log(className,"**** getLength I AM HERE ****");
    	int length = 0;
     	try{
      	   length=GetLength();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLength length<"+length+"> ****");
		return length;
    }

    public void setLength(int length)
                      throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** setLength length<"+length+"> ****");
		try{
			SetLength(length);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public HTMLFormElement getForm(){
    	if(JRexL.on)JRexL.log(className,"**** getForm I AM HERE ****");
		HTMLFormElement form=null;
		try{
			form=GetForm();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getForm form<"+form+"> ****");
		return form;
    }


    public HTMLOptionsCollection getOptions(){
    	if(JRexL.on)JRexL.log(className,"**** getOptions I AM HERE ****");
		HTMLOptionsCollection options=null;
		try{
			options=GetOptions();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getOptions options<"+options+"> ****");
		return options;
    }

    public boolean getDisabled(){
    	if(JRexL.on)JRexL.log(className,"**** getDisabled I AM HERE ****");
		boolean disabled=false;
		try{
			disabled=GetDisabled();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDisabled disabled<"+disabled+"> ****");
		return disabled;
    }

    public void setDisabled(boolean disabled){
    	if(JRexL.on)JRexL.log(className,"**** setDisabled disabled<"+disabled+"> ****");
		try{
			SetDisabled(disabled);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public boolean getMultiple(){
    	if(JRexL.on)JRexL.log(className,"**** getMultiple I AM HERE ****");
		boolean multiple=false;
		try{
			multiple=GetMultiple();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMultiple multiple<"+multiple+"> ****");
		return multiple;
   	}

    public void setMultiple(boolean multiple){
    	if(JRexL.on)JRexL.log(className,"**** setMultiple multiple<"+multiple+"> ****");
		try{
			SetMultiple(multiple);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
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

    public int getSize(){
    	if(JRexL.on)JRexL.log(className,"**** getSize I AM HERE ****");
		int size=0;
		try{
			size=GetSize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSize size<"+size+"> ****");
		return size;
    }

    public void setSize(int size){
    	if(JRexL.on)JRexL.log(className,"**** setSize size<"+size+"> ****");
		try{
			SetSize(size);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public int getTabIndex(){
    	if(JRexL.on)JRexL.log(className,"**** getTabIndex I AM HERE ****");
		int tabIndex=0;
		try{
			tabIndex=GetTabIndex();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTabIndex tabIndex<"+tabIndex+"> ****");
		return tabIndex;
    }

    public void setTabIndex(int tabIndex){
    	if(JRexL.on)JRexL.log(className,"**** setTabIndex tabIndex<"+tabIndex+"> ****");
		try{
			SetTabIndex(tabIndex);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

     public void add(HTMLElement element,
                    HTMLElement before)
                    throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** add() I AM HERE ****");
		try{
			Add(element, before);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

    public void remove(int index){
    	if(JRexL.on)JRexL.log(className,"**** remove index<"+index+"> ****");
		try{
			Remove(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

     public void blur(){
    	if(JRexL.on)JRexL.log(className,"**** blur() I AM HERE ****");
		try{
			Blur();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

     public void focus(){
    	if(JRexL.on)JRexL.log(className,"**** focus() I AM HERE ****");
		try{
			Focus();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	private native int GetSelectedIndex()throws JRexException;
	private native String GetType()throws JRexException;
	private native void SetSelectedIndex(int selectedIndex)throws JRexException;
	private native String GetValue()throws JRexException;
	private native void SetValue(String value)throws JRexException;
	private native void GetType(String value)throws JRexException;
	private native int GetLength()throws JRexException;
	private native void SetLength(int length)throws DOMException,JRexException;
	private native HTMLFormElement GetForm()throws JRexException;
	private native HTMLOptionsCollection GetOptions()throws JRexException;
	private native boolean GetDisabled()throws JRexException;
	private native void SetDisabled(boolean disabled)throws JRexException;
	private native boolean GetMultiple()throws JRexException;
	private native void SetMultiple(boolean multiple)throws JRexException;
	private native String GetName()throws JRexException;
	private native void SetName(String name)throws JRexException;
	private native int GetSize()throws JRexException;
	private native void SetSize(int size)throws JRexException;
	private native int GetTabIndex()throws JRexException;
	private native void SetTabIndex(int tabIndex)throws JRexException;
	private native void Add(HTMLElement element, HTMLElement before)throws DOMException,JRexException;
	private native void Remove(int index)throws JRexException;
	private native void Blur()throws JRexException;
	private native void Focus()throws JRexException;

}
