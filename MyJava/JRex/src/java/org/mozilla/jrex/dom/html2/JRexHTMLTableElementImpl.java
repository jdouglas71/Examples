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

import org.w3c.dom.html2.HTMLTableElement;
import org.w3c.dom.html2.HTMLTableSectionElement;
import org.w3c.dom.html2.HTMLCollection;
import org.w3c.dom.html2.HTMLTableCaptionElement;
import org.w3c.dom.html2.HTMLElement;
import org.mozilla.jrex.dom.JRexElementImpl;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

import org.w3c.dom.DOMException;
/**
* A class implementing org.w3c.dom.html2.HTMLTableElement interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.html2.HTMLTableElement
*/
public class JRexHTMLTableElementImpl extends JRexHTMLElementImpl implements HTMLTableElement {
	private static final String className	= JRexHTMLTableElementImpl.class.getName();

	private JRexHTMLTableElementImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexHTMLTableElementImpl ****");
	}


	public HTMLTableCaptionElement getCaption(){
		if(JRexL.on)JRexL.log(className,"**** getCaption I AM HERE ****");
    	HTMLTableCaptionElement caption = null;
     	try{
      	   caption=GetCaption();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCaption caption<"+caption+"> ****");
		return caption;
	}


    public void setCaption(HTMLTableCaptionElement caption)
                          throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** setCaption caption<"+caption+"> ****");
		try{
			SetCaption(caption);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLTableSectionElement getTHead(){
    	if(JRexL.on)JRexL.log(className,"**** getTHead I AM HERE ****");
    	HTMLTableSectionElement tHead = null;
     	try{
      	   tHead=GetTHead();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTHead tHead<"+tHead+"> ****");
		return tHead;
	}


    public void setTHead(HTMLTableSectionElement tHead)
                          throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** setTHead tHead<"+tHead+"> ****");
		try{
			SetTHead(tHead);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLTableSectionElement getTFoot(){
    	if(JRexL.on)JRexL.log(className,"**** getTFoot I AM HERE ****");
    	HTMLTableSectionElement tFoot = null;
     	try{
      	   tFoot=GetTFoot();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on) JRexL.log(className,"**** getTFoot tFoot<"+tFoot+"> ****");
		return tFoot;
	}


    public void setTFoot(HTMLTableSectionElement tFoot)
                          throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** setTFoot tFoot<"+tFoot+"> ****");
		try{
			SetTFoot(tFoot);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLCollection getRows(){
    	if(JRexL.on)JRexL.log(className,"**** getRows I AM HERE ****");
    	HTMLCollection rows = null;
     	try{
      	   rows=GetRows();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRows rows<"+rows+"> ****");
		return rows;
	}


    public HTMLCollection getTBodies(){
    	if(JRexL.on)JRexL.log(className,"**** getTBodies I AM HERE ****");
    	HTMLCollection tBodies = null;
     	try{
      	   tBodies=GetTBodies();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTBodies tBodies<"+tBodies+"> ****");
		return tBodies;
	}


    public String getAlign(){
    	if(JRexL.on)JRexL.log(className,"**** getAlign I AM HERE ****");
    	String align = null;
     	try{
      	   align=GetAlign();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAlign align"+align+"> ****");
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


    public String getBgColor(){
    	if(JRexL.on)JRexL.log(className,"**** getBgColor I AM HERE ****");
    	String bgColor = null;
     	try{
      	   bgColor=GetBgColor();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBgColor bgColor<"+bgColor+"> ****");
		return bgColor;
	}


    public void setBgColor(String bgColor){
    	if(JRexL.on)JRexL.log(className,"**** setBgColor bgColor<"+bgColor+"> ****");
		try{
			SetBgColor(bgColor);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getBorder(){
    	if(JRexL.on)JRexL.log(className,"**** getBorder I AM HERE ****");
    	String border = null;
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


    public String getCellPadding(){
    	if(JRexL.on)JRexL.log(className,"**** getCellPadding I AM HERE ****");
    	String cellPadding = null;
     	try{
      	   cellPadding=GetCellPadding();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCellPadding cellPadding<"+cellPadding+"> ****");
		return cellPadding;
	}


    public void setCellPadding(String cellPadding){
    	if(JRexL.on)JRexL.log(className,"**** setCellPadding cellPadding<"+cellPadding+"> ****");
		try{
			SetCellPadding(cellPadding);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getCellSpacing(){
    	if(JRexL.on)JRexL.log(className,"**** getCellSpacing I AM HERE ****");
    	String cellSpacing = null;
     	try{
      	   cellSpacing=GetCellSpacing();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCellSpacing cellSpacing<"+cellSpacing+"> ****");
		return cellSpacing;
	}


    public void setCellSpacing(String cellSpacing){
    	if(JRexL.on)JRexL.log(className,"**** setCellSpacing cellSpacing<"+cellSpacing+"> ****");
		try{
			SetCellSpacing(cellSpacing);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getFrame(){
    	if(JRexL.on)JRexL.log(className,"**** getFrame I AM HERE ****");
    	String frame = null;
     	try{
      	   frame=GetFrame();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFrame frame<"+frame+"> ****");
		return frame;
	}


    public void setFrame(String frame){
    	if(JRexL.on)JRexL.log(className,"**** setFrame frame<"+frame+"> ****");
		try{
			SetFrame(frame);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getRules(){
    	if(JRexL.on)JRexL.log(className,"**** getRules I AM HERE ****");
    	String rules = null;
     	try{
      	   rules=GetRules();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRules rules<"+rules+"> ****");
		return rules;
	}


    public void setRules(String rules){
    	if(JRexL.on)JRexL.log(className,"**** setRules rules<"+rules+"> ****");
		try{
			SetRules(rules);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public String getSummary(){
    	if(JRexL.on)JRexL.log(className,"**** getSummary I AM HERE ****");
    	String summary = null;
     	try{
      	   summary=GetSummary();
      	}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getSummary summary<"+summary+"> ****");
		return summary;
	}


    public void setSummary(String summary){
    	if(JRexL.on)JRexL.log(className,"**** setSummary summary<"+summary+"> ****");
		try{
			SetSummary(summary);
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


    public HTMLElement createTHead(){
    	HTMLElement tHead = null;
    	if(JRexL.on)JRexL.log(className,"**** createTHead() I AM HERE ****");
		try{
			tHead = CreateTHead();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return tHead;
	}


    public void deleteTHead(){
    	if(JRexL.on)JRexL.log(className,"**** deleteTHead() I AM HERE ****");
		try{
			DeleteTHead();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLElement createTFoot(){
    	HTMLElement tFoot = null;
    	if(JRexL.on)JRexL.log(className,"**** createTFoot() I AM HERE ****");
		try{
			tFoot = CreateTFoot();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return tFoot;
	}


    public void deleteTFoot(){
    	if(JRexL.on)JRexL.log(className,"**** deleteTFoot() I AM HERE ****");
		try{
			DeleteTFoot();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLElement createCaption(){
    	HTMLElement caption = null;
    	if(JRexL.on)JRexL.log(className,"**** createCaption() I AM HERE ****");
		try{
			caption = CreateCaption();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return caption;
	}


    public void deleteCaption(){
    	if(JRexL.on)JRexL.log(className,"**** deleteCaption() I AM HERE ****");
		try{
			DeleteCaption();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


    public HTMLElement insertRow(int index)
                                 throws DOMException{
        HTMLElement row = null;
    	if(JRexL.on)JRexL.log(className,"**** insertRow() I AM HERE ****");
		try{
			row = InsertRow(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		return row;
	}


    public void deleteRow(int index)
                          throws DOMException{
    	if(JRexL.on)JRexL.log(className,"**** DeleteRow() I AM HERE ****");
		try{
			DeleteRow(index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	private native  HTMLTableCaptionElement GetCaption()throws JRexException;
    private native  void SetCaption(HTMLTableCaptionElement caption)throws DOMException,JRexException;
    private native  HTMLTableSectionElement GetTHead()throws JRexException;
    private native  void SetTHead(HTMLTableSectionElement tHead)throws DOMException,JRexException;
	private native  HTMLTableSectionElement GetTFoot()throws JRexException;
    private native  void SetTFoot(HTMLTableSectionElement tFoot)throws DOMException,JRexException;
    private native  HTMLCollection GetRows()throws JRexException;
    private native  HTMLCollection GetTBodies()throws JRexException;
    private native  String GetAlign()throws JRexException;
    private native  void SetAlign(String align)throws JRexException;
    private native  String GetBgColor()throws JRexException;
    private native  void SetBgColor(String bgColor)throws JRexException;
    private native  String GetBorder()throws JRexException;
    private native  void SetBorder(String border)throws JRexException;
    private native  String GetCellPadding()throws JRexException;
    private native  void SetCellPadding(String cellPadding)throws JRexException;
    private native  String GetCellSpacing()throws JRexException;
    private native  void SetCellSpacing(String cellSpacing)throws JRexException;
    private native  String GetFrame()throws JRexException;
    private native  void SetFrame(String frame)throws JRexException;
    private native  String GetRules()throws JRexException;
    private native  void SetRules(String rules)throws JRexException;
    private native  String GetSummary()throws JRexException;
    private native  void SetSummary(String summary)throws JRexException;
    private native  String GetWidth()throws JRexException;
    private native  void SetWidth(String width)throws JRexException;
    private native  HTMLElement CreateTHead()throws JRexException;
    private native  void DeleteTHead()throws JRexException;
    private native  HTMLElement CreateTFoot()throws JRexException;
    private native  void DeleteTFoot()throws JRexException;
    private native  HTMLElement CreateCaption()throws JRexException;
    private native  void DeleteCaption()throws JRexException;
    private native  HTMLElement InsertRow(int index)throws DOMException,JRexException;
    private native  void DeleteRow(int index)throws DOMException,JRexException;
}