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

import org.w3c.dom.Document;
import org.w3c.dom.html2.HTMLObjectElement;
import org.w3c.dom.html2.HTMLFormElement;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A class implementing org.w3c.dom.html2.HTMLObjectElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLObjectElement
*/
public class JRexHTMLObjectElementImpl extends JRexHTMLElementImpl implements HTMLObjectElement {
	private static final String className	= JRexHTMLObjectElementImpl.class.getName();

	private JRexHTMLObjectElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLObjectElementImpl ****");
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

	public String getCode(){
		if(JRexL.on)JRexL.log(className,"**** getCode I AM HERE ****");
		String code=null;
		try{
			code=GetCode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCode code<"+code+"> ****");
		return code;
	}

	public void setCode(String code){
		if(JRexL.on)JRexL.log(className,"**** setAccept code<"+code+"> ****");
		try{
			SetCode(code);
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

	public String getArchive(){
		if(JRexL.on)JRexL.log(className,"**** getArchive I AM HERE ****");
		String archive=null;
		try{
			archive=GetArchive();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getArchive archive<"+archive+"> ****");
		return archive;
	}

	public void setArchive(String archive){
		if(JRexL.on)JRexL.log(className,"**** setArchive archive<"+archive+"> ****");
		try{
			SetArchive(archive);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getBorder(){
		if(JRexL.on)JRexL.log(className,"**** getBorder I AM HERE ****");
		String border=null;
		try{
			border=GetBorder();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBorder border<"+border+"> ****");
		return border;
	}

	public void setBorder(String border){
		if(JRexL.on)JRexL.log(className,"**** setBorder border<"+border+"> ****");
		try{
			SetBorder(border);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getCodeBase(){
		if(JRexL.on)JRexL.log(className,"**** getCodeBase I AM HERE ****");
		String codeBase=null;
		try{
			codeBase=GetCodeBase();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCodeBase codeBase<"+codeBase+"> ****");
		return codeBase;
	}

	public void setCodeBase(String codeBase){
		if(JRexL.on)JRexL.log(className,"**** setCodeBase codeBase<"+codeBase+"> ****");
		try{
			SetCodeBase(codeBase);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getCodeType(){
		if(JRexL.on)JRexL.log(className,"**** getCodeType I AM HERE ****");
		String codeType=null;
		try{
			codeType=GetCodeType();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCodeType codeType<"+codeType+"> ****");
		return codeType;
	}

	public void setCodeType(String codeType){
		if(JRexL.on)JRexL.log(className,"**** setCodeType codeType<"+codeType+"> ****");
		try{
			SetCodeType(codeType);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public String getData(){
		if(JRexL.on)JRexL.log(className,"**** getData I AM HERE ****");
		String data=null;
		try{
			data=GetData();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getData data<"+data+"> ****");
		return data;
	}

	public void setData(String data){
		if(JRexL.on)JRexL.log(className,"**** setData data<"+data+"> ****");
		try{
			SetData(data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public boolean getDeclare(){
		if(JRexL.on)JRexL.log(className,"**** getDeclare I AM HERE ****");
		boolean declare=false;
		try{
			declare=GetDeclare();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDeclare declare<"+declare+"> ****");
		return declare;
	}

	public void setDeclare(boolean declare){
		if(JRexL.on)JRexL.log(className,"**** setDeclare declare<"+declare+"> ****");
		try{
			SetDeclare(declare);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public String getHeight(){
    	if(JRexL.on)JRexL.log(className,"**** getHeight I AM HERE ****");
    	String height = null;
     	try{
      	   height=GetHeight();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHeight height<"+height+"> ****");
		return height;
    }


    public void setHeight(String height){
    	if(JRexL.on)JRexL.log(className,"**** setHeight height<"+height+"> ****");
		try{
			SetHeight(height);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	public int getHspace(){
		if(JRexL.on)JRexL.log(className,"**** getHspace I AM HERE ****");
		int hspace=0;
		try{
			hspace=GetHspace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getHspace hspace<"+hspace+"> ****");
		return hspace;
	}

	public void setHspace(int hspace){
		if(JRexL.on)JRexL.log(className,"**** setHspace hspace<"+hspace+"> ****");
		try{
			SetHspace(hspace);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public String getName(){
    	if(JRexL.on)JRexL.log(className,"**** getName I AM HERE ****");
    	String name = null;
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

    public String getStandby(){
    	if(JRexL.on)JRexL.log(className,"**** getStandby I AM HERE ****");
    	String standby = null;
     	try{
      	   standby=GetStandby();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getStandby standby<"+standby+"> ****");
		return standby;
    }


    public void setStandby(String standby){
    	if(JRexL.on)JRexL.log(className,"**** setStandby standby<"+standby+"> ****");
		try{
			SetStandby(standby);
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
    	String type = null;
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
    	String useMap = null;
     	try{
      	   useMap=GetUseMap();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUseMap useMap<"+useMap+"> ****");
		return useMap;
    }


    public void setUseMap(String useMap){
    	if(JRexL.on)JRexL.log(className,"**** setType useMap<"+useMap+"> ****");
		try{
			SetUseMap(useMap);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	public int getVspace(){
		if(JRexL.on)JRexL.log(className,"**** getVspace I AM HERE ****");
		int vspace=0;
		try{
			vspace=GetVspace();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getVspace vspace<"+vspace+"> ****");
		return vspace;
	}

	public void setVspace(int vspace){
		if(JRexL.on)JRexL.log(className,"**** setVspace vspace<"+vspace+"> ****");
		try{
			SetVspace(vspace);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public String getWidth(){
    	if(JRexL.on)JRexL.log(className,"**** getWidth I AM HERE ****");
    	String width = null;
     	try{
      	   width=GetWidth();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getWidth width<"+width+"> ****");
		return width;
    }


    public void setWidth(String width){
    	if(JRexL.on)JRexL.log(className,"**** setWidth width<"+width+"> ****");
		try{
			SetWidth(width);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
    }

	public Document getContentDocument(){
		if(JRexL.on)JRexL.log(className,"**** getContentDocument I AM HERE ****");
		Document doc=null;
		try{
			doc=GetContentDocument();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getContentDocument doc<"+doc+"> ****");
		return doc;
	}

    private native HTMLFormElement GetForm()throws JRexException;
    private native String GetCode()throws JRexException;
    private native void SetCode(String code)throws JRexException;
    private native String GetAlign()throws JRexException;
    private native void SetAlign(String align)throws JRexException;
    private native String GetArchive()throws JRexException;
    private native void SetArchive(String archive)throws JRexException;
    private native String GetBorder()throws JRexException;
    private native void SetBorder(String border)throws JRexException;
    private native String GetCodeBase()throws JRexException;
    private native void SetCodeBase(String codeBase)throws JRexException;
    private native String GetCodeType()throws JRexException;
    private native void SetCodeType(String codeType)throws JRexException;
    private native String GetData()throws JRexException;
    private native void SetData(String data)throws JRexException;
    private native boolean GetDeclare()throws JRexException;
    private native void SetDeclare(boolean declare)throws JRexException;
    private native String GetHeight()throws JRexException;
    private native void SetHeight(String height)throws JRexException;
    private native int GetHspace()throws JRexException;
    private native void SetHspace(int hspace)throws JRexException;
    private native String GetName()throws JRexException;
    private native void SetName(String name)throws JRexException;
    private native String GetStandby()throws JRexException;
    private native void SetStandby(String standby)throws JRexException;
    private native int GetTabIndex()throws JRexException;
    private native void SetTabIndex(int tabIndex)throws JRexException;
    private native String GetType()throws JRexException;
    private native void SetType(String type)throws JRexException;
    private native String GetUseMap()throws JRexException;
    private native void SetUseMap(String useMap)throws JRexException;
    private native int GetVspace()throws JRexException;
    private native void SetVspace(int vspace)throws JRexException;
    private native String GetWidth()throws JRexException;
    private native void SetWidth(String width)throws JRexException;
    private native Document GetContentDocument()throws JRexException;

}
