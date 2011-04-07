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

import org.w3c.dom.html2.HTMLInputElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLInputElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLInputElement
*/

public class JRexHTMLInputElementImpl extends JRexHTMLElementImpl implements HTMLInputElement {

	private static final String className	= JRexHTMLInputElementImpl.class.getName();

     /** Intended to be used by JNI */
    private JRexHTMLInputElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLInputElementImpl ****");
	}

	public String getDefaultValue(){
		if(JRexL.on)JRexL.log(className,"**** getDefaultValue I AM HERE ****");
		String defaultValue=null;
		try{
			defaultValue=GetDefaultValue();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDefaultValue defaultValue<"+defaultValue+"> ****");
		return defaultValue;
	}

	public void setDefaultValue(String defaultValue){
		if(JRexL.on)JRexL.log(className,"**** setDefaultValue defaultValue<"+defaultValue+"> ****");
		try{
			SetDefaultValue(defaultValue);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public boolean getDefaultChecked(){
		if(JRexL.on)JRexL.log(className,"**** getDefaultChecked I AM HERE ****");
		boolean defaultChecked=false;
		try{
			defaultChecked=GetDefaultChecked();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDefaultChecked defaultChecked<"+defaultChecked+"> ****");
		return defaultChecked;
	}

	public void setDefaultChecked(boolean defaultChecked){
		if(JRexL.on)JRexL.log(className,"**** setDefaultChecked defaultChecked<"+defaultChecked+"> ****");
		try{
			SetDefaultChecked(defaultChecked);
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

	public String getAccept(){
		if(JRexL.on)JRexL.log(className,"**** getAccept I AM HERE ****");
		String accept=null;
		try{
			accept=GetAccept();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAccept accept<"+accept+"> ****");
		return accept;
	}

	public void setAccept(String accept){
		if(JRexL.on)JRexL.log(className,"**** setAccept accept<"+accept+"> ****");
		try{
			SetAccept(accept);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getAccessKey(){
		if(JRexL.on)JRexL.log(className,"**** getAccessKey I AM HERE ****");
		String accessKey=null;
		try{
			accessKey=GetAccessKey();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAccessKey accessKey<"+accessKey+"> ****");
		return accessKey;
	}

	public void setAccessKey(String accessKey){
		if(JRexL.on)JRexL.log(className,"**** setAccept accessKey<"+accessKey+"> ****");
		try{
			SetAccessKey(accessKey);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getAlign(){
		if(JRexL.on)JRexL.log(className,"**** getAlign I AM HERE ****");
		String align=null;
		try{
			align=GetAlign();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAlign align<"+align+"> ****");
		return align;
	}

	public void setAlign(String align){
		if(JRexL.on)JRexL.log(className,"**** setAlign align<"+align+"> ****");
		try{
			SetAlign(align);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getAlt(){
		if(JRexL.on)JRexL.log(className,"**** getAlt I AM HERE ****");
		String alt=null;
		try{
			alt=GetAlt();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAlt alt<"+alt+"> ****");
		return alt;
	}

	public void setAlt(String alt){
		if(JRexL.on)JRexL.log(className,"**** setAlt alt<"+alt+"> ****");
		try{
			SetAlt(alt);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public boolean getChecked(){
		if(JRexL.on)JRexL.log(className,"**** getChecked I AM HERE ****");
		boolean checked=false;
		try{
			checked=GetChecked();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getChecked checked<"+checked+"> ****");
		return checked;
	}

	public void setChecked(boolean checked){
		if(JRexL.on)JRexL.log(className,"**** setChecked checked<"+checked+"> ****");
		try{
			SetChecked(checked);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
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

	public int getMaxLength(){
		if(JRexL.on)JRexL.log(className,"**** getMaxLength I AM HERE ****");
		int maxLength=0;
		try{
			maxLength=GetMaxLength();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getMaxLength maxLength<"+maxLength+"> ****");
		return maxLength;
	}

	public void setMaxLength(int maxLength){
		if(JRexL.on)JRexL.log(className,"**** setMaxLength maxLength<"+maxLength+"> ****");
		try{
			SetMaxLength(maxLength);
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

	public boolean getReadOnly(){
		if(JRexL.on)JRexL.log(className,"**** getReadOnly I AM HERE ****");
		boolean readOnly=false;
		try{
			readOnly=GetReadOnly();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getReadOnly readOnly<"+readOnly+"> ****");
		return readOnly;
	}

	public void setReadOnly(boolean readOnly){
		if(JRexL.on)JRexL.log(className,"**** setReadOnly readOnly<"+readOnly+"> ****");
		try{
			SetReadOnly(readOnly);
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

	public String getSrc(){
		if(JRexL.on)JRexL.log(className,"**** getSrc I AM HERE ****");
		String src=null;
		try{
			src=GetSrc();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSrc src<"+src+"> ****");
		return src;
	}

	public void setSrc(String src){
		if(JRexL.on)JRexL.log(className,"**** setSrc src<"+src+"> ****");
		try{
			SetSrc(src);
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

	public String getType(){
		if(JRexL.on)JRexL.log(className,"**** getType I AM HERE ****");
		String type=null;
		try{
			type=GetType();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getType type<"+type+"> ****");
		return type;
	}

	public void setType(String type){
		if(JRexL.on)JRexL.log(className,"**** setType type<"+type+"> ****");
		try{
			SetType(type);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getUseMap(){
		if(JRexL.on)JRexL.log(className,"**** getUseMap I AM HERE ****");
		String useMap=null;
		try{
			useMap=GetUseMap();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUseMap useMap<"+useMap+"> ****");
		return useMap;
	}

	public void setUseMap(String useMap){
		if(JRexL.on)JRexL.log(className,"**** setUseMap useMap<"+useMap+"> ****");
		try{
			SetUseMap(useMap);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getValue(){
		if(JRexL.on)JRexL.log(className,"**** getValue I AM HERE ****");
		String value=null;
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

	public void select(){
		if(JRexL.on)JRexL.log(className,"**** select() I AM HERE ****");
		try{
			Select();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void click(){
		if(JRexL.on)JRexL.log(className,"**** click() I AM HERE ****");
		try{
			Click();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    private native String GetDefaultValue()throws JRexException;
    private native void SetDefaultValue(String defaultValue)throws JRexException;
    private native boolean GetDefaultChecked()throws JRexException;
    private native void SetDefaultChecked(boolean defaultChecked)throws JRexException;
    private native HTMLFormElement GetForm()throws JRexException;
    private native String GetAccept()throws JRexException;
    private native void SetAccept(String accept)throws JRexException;
    private native String GetAccessKey()throws JRexException;
    private native void SetAccessKey(String accessKey)throws JRexException;
    private native String GetAlign()throws JRexException;
    private native void SetAlign(String align)throws JRexException;
    private native String GetAlt()throws JRexException;
    private native void SetAlt(String alt)throws JRexException;
    private native boolean GetChecked()throws JRexException;
    private native void SetChecked(boolean checked)throws JRexException;
    private native boolean GetDisabled()throws JRexException;
    private native void SetDisabled(boolean disabled)throws JRexException;
    private native int GetMaxLength()throws JRexException;
    private native void SetMaxLength(int maxLength)throws JRexException;
    private native String GetName()throws JRexException;
    private native void SetName(String name)throws JRexException;
    private native boolean GetReadOnly()throws JRexException;
    private native void SetReadOnly(boolean readOnly)throws JRexException;
    private native int GetSize()throws JRexException;
    private native void SetSize(int size)throws JRexException;
    private native String GetSrc()throws JRexException;
    private native void SetSrc(String src)throws JRexException;
    private native int GetTabIndex()throws JRexException;
    private native void SetTabIndex(int tabIndex)throws JRexException;
    private native String GetType()throws JRexException;
    private native void SetType(String type)throws JRexException;
    private native String GetUseMap()throws JRexException;
    private native void SetUseMap(String useMap)throws JRexException;
    private native String GetValue()throws JRexException;
    private native void SetValue(String value)throws JRexException;
    private native void Blur()throws JRexException;
    private native void Focus()throws JRexException;
    private native void Select()throws JRexException;
    private native void Click()throws JRexException;
}


