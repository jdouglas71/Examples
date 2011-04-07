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

import org.w3c.dom.*;
import org.w3c.dom.ranges.DocumentRange;
import org.w3c.dom.events.DocumentEvent;
import org.w3c.dom.traversal.DocumentTraversal;
import org.w3c.dom.views.DocumentView;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.Document interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Document
*/
public class JRexDocumentImpl extends JRexNodeImpl implements Document{

	private static final String className	= JRexDocumentImpl.class.getName();

    /** Intended to be used by JNI */
    protected JRexDocumentImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDocumentImpl Creation ****");
	}

	public Attr createAttribute(String name)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createAttribute name<"+name+"> ****");
		Attr attr=null;
		try{
			attr=CreateAttribute(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createAttribute attr<"+attr+"> ****");
		return attr;
	}

	public Attr createAttributeNS(String namespaceURI, String qualifiedName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createAttributeNS namespaceURI<"+namespaceURI+"> qualifiedName<"+qualifiedName+"> ****");
		Attr attr=null;
		try{
			attr=CreateAttributeNS(namespaceURI, qualifiedName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createAttributeNS attr<"+attr+"> ****");
		return attr;
	}

	public CDATASection createCDATASection(String data)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createCDATASection data<"+data+"> ****");
		CDATASection dataSec=null;
		try{
			dataSec=CreateCDATASection(data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createCDATASection dataSec<"+dataSec+"> ****");
		return dataSec;
	}

	public Comment createComment(String data){
		if(JRexL.on)JRexL.log(className,"**** createComment data<"+data+"> ****");
		Comment comment=null;
		try{
			comment=CreateComment(data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createComment comment<"+comment+"> ****");
		return comment;
	}

	public DocumentFragment createDocumentFragment(){
		if(JRexL.on)JRexL.log(className,"**** createDocumentFragment ****");
		DocumentFragment docFrag=null;
		try{
			docFrag=CreateDocumentFragment();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createDocumentFragment docFrag<"+docFrag+"> ****");
		return docFrag;
	}

	public Element createElement(String tagName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createElement tagName<"+tagName+"> ****");
		Element ele=null;
		try{
			ele=CreateElement(tagName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createElement ele<"+ele+"> ****");
		return ele;
	}

	public Element createElementNS(String namespaceURI, String qualifiedName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createElementNS namespaceURI<"+namespaceURI+"> qualifiedName<"+qualifiedName+"> ****");
		Element ele=null;
		try{
			ele=CreateElementNS(namespaceURI, qualifiedName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createElementNS ele<"+ele+"> ****");
		return ele;
	}

	public EntityReference createEntityReference(String name)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createEntityReference name<"+name+"> ****");
		EntityReference eRef=null;
		try{
			eRef=CreateEntityReference(name);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createEntityReference eRef<"+eRef+"> ****");
		return eRef;
	}

	public ProcessingInstruction createProcessingInstruction(String target, String data)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createProcessingInstruction target<"+target+"> data<"+data+"> ****");
		ProcessingInstruction procIns=null;
		try{
			procIns=CreateProcessingInstruction(target, data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createProcessingInstruction procIns<"+procIns+"> ****");
		return procIns;
	}

	public Text createTextNode(String data){
		if(JRexL.on)JRexL.log(className,"**** createTextNode data<"+data+"> ****");
		Text text=null;
		try{
			text=CreateTextNode(data);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createTextNode text<"+text+"> ****");
		return text;
	}

	public DocumentType getDoctype(){
		if(JRexL.on)JRexL.log(className,"**** getDoctype ****");
		DocumentType docType=null;
		try{
			docType=GetDoctype();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDoctype docType<"+docType+"> ****");
		return docType;
	}

	public Element getDocumentElement(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentElement ****");
		Element ele=null;
		try{
			ele=GetDocumentElement();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentElement ele<"+ele+"> ****");
		return ele;
	}

	public Element getElementById(String elementId){
		if(JRexL.on)JRexL.log(className,"**** getElementById elementId<"+elementId+"> ****");
		Element ele=null;
		try{
			ele=GetElementById(elementId);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementById ele<"+ele+"> ****");
		return ele;
	}

	public NodeList getElementsByTagName(String tagname){
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagName tagname<"+tagname+"> ****");
		NodeList nList=null;
		try{
			nList=GetElementsByTagName(tagname);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagName nList<"+nList+"> ****");
		return nList;
	}

	public NodeList getElementsByTagNameNS(String namespaceURI, String localName){
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagNameNS namespaceURI<"+namespaceURI+"> localName<"+localName+"> ****");
		NodeList nList=null;
		try{
			nList=GetElementsByTagNameNS(namespaceURI, localName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getElementsByTagNameNS nList<"+nList+"> ****");
		return nList;
	}

	public DOMImplementation getImplementation(){
		if(JRexL.on)JRexL.log(className,"**** getImplementation ****");
		DOMImplementation domImpl=null;
		try{
			domImpl=GetImplementation();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getImplementation domImpl<"+domImpl+"> ****");
		return domImpl;
	}

	public Node importNode(Node importedNode, boolean deep)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** importNode importedNode<"+importedNode+"> deep<"+deep+"> ****");
		Node node=null;
		try{
			node=ImportNode(importedNode, deep);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** importNode node<"+node+"> ****");
		return node;
	}

	public DocumentRange getDocumentRange(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentRange I AM HERE ****");
		DocumentRange docRange=null;
		try{
			docRange=GetDocumentRange();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentRange docRange<"+docRange+"> ****");
		return docRange;
	}

	public DocumentEvent getDocumentEvent(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentEvent I AM HERE ****");
		DocumentEvent docEvent=null;
		try{
			docEvent=GetDocumentEvent();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentEvent docEvent<"+docEvent+"> ****");
		return docEvent;
	}

	public DocumentTraversal getDocumentTraversal(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentTraversal I AM HERE ****");
		DocumentTraversal docTrav=null;
		try{
			docTrav=GetDocumentTraversal();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentTraversal docTrav<"+docTrav+"> ****");
		return docTrav;
	}

	public DocumentView getDocumentView(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentView I AM HERE ****");
		DocumentView docView=null;
		try{
			docView=GetDocumentView();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentView docView<"+docView+"> ****");
		return docView;
	}

	//DOM3
	public String getInputEncoding(){
		if(JRexL.on)JRexL.log(className,"**** getInputEncoding ****");
		String iEncode=null;
		try{
			iEncode=GetInputEncoding();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getInputEncoding iEncode<"+iEncode+"> ****");
		return iEncode;
	}

	public String getXmlEncoding(){
		if(JRexL.on)JRexL.log(className,"**** getXmlEncoding ****");
		String xmlEncode=null;
		try{
			xmlEncode=GetXmlEncoding();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getXmlEncoding xmlEncode<"+xmlEncode+"> ****");
		return xmlEncode;
	}

	public boolean getXmlStandalone(){
		if(JRexL.on)JRexL.log(className,"**** getXmlStandalone ****");
		boolean xmlStndAln=false;
		try{
			xmlStndAln=GetXmlStandalone();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getXmlStandalone xmlStndAln<"+xmlStndAln+"> ****");
		return xmlStndAln;
	}

	public void setXmlStandalone(boolean xmlStandalone)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setXmlStandalone xmlStandalone<"+xmlStandalone+">****");
		try{
			SetXmlStandalone(xmlStandalone);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String getXmlVersion(){
		if(JRexL.on)JRexL.log(className,"**** getXmlVersion ****");
		String xmlVer=null;
		try{
			xmlVer=GetXmlVersion();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getXmlVersion xmlVer<"+xmlVer+"> ****");
		return xmlVer;
	}

    public void setXmlVersion(String xmlVersion)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setXmlVersion xmlVersion<"+xmlVersion+">****");
		try{
			SetXmlVersion(xmlVersion);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public boolean getStrictErrorChecking(){
		if(JRexL.on)JRexL.log(className,"**** getStrictErrorChecking ****");
		boolean strictError=false;
		try{
			strictError=GetStrictErrorChecking();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getStrictErrorChecking strictError<"+strictError+"> ****");
		return strictError;
	}

    public void setStrictErrorChecking(boolean strictErrorChecking){
		if(JRexL.on)JRexL.log(className,"**** setStrictErrorChecking strictErrorChecking<"+strictErrorChecking+">****");
		try{
			SetStrictErrorChecking(strictErrorChecking);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public String getDocumentURI(){
		if(JRexL.on)JRexL.log(className,"**** getDocumentURI ****");
		String docUri=null;
		try{
			docUri=GetXmlVersion();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getDocumentURI docUri<"+docUri+"> ****");
		return docUri;
	}

    public void setDocumentURI(String documentURI){
		if(JRexL.on)JRexL.log(className,"**** setDocumentURI documentURI<"+documentURI+">****");
		try{
			SetDocumentURI(documentURI);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public Node adoptNode(Node source)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** adoptNode source<"+source+"> ****");
		Node node=null;
		try{
			node=AdoptNode(source);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** adoptNode node<"+node+"> ****");
		return node;
	}

    public DOMConfiguration getDomConfig(){
		if(JRexL.on)JRexL.log(className,"**** getDomConfig ****");
		DOMConfiguration config=null;
		//Not implemented in mozilla
		/*try{
			config=GetDomConfig();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}*/
		if(JRexL.on)JRexL.log(className,"**** getDomConfig config<"+config+"> ****");
		return config;
	}

    public void normalizeDocument(){
		if(JRexL.on)JRexL.log(className,"**** normalizeDocument****");
		try{
			NormalizeDocument();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public Node renameNode(Node n, String namespaceURI,String qualifiedName)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** renameNode n<"+n+"> namespaceURI<"
								+namespaceURI+"> qualifiedName<"+qualifiedName+"> ****");
		Node node=null;
		try{
			node=RenameNode(n, namespaceURI, qualifiedName);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** renameNode node<"+node+"> ****");
		return node;
	}

	private native Attr CreateAttribute(String name)throws DOMException, JRexException;
	private native Attr CreateAttributeNS(String namespaceURI, String qualifiedName)throws DOMException, JRexException;
	private native CDATASection CreateCDATASection(String data)throws DOMException, JRexException;
	private native Comment CreateComment(String data)throws JRexException;
	private native DocumentFragment CreateDocumentFragment()throws JRexException;
	private native Element CreateElement(String tagName)throws DOMException, JRexException;
	private native Element CreateElementNS(String namespaceURI, String qualifiedName)throws DOMException, JRexException;
	private native EntityReference CreateEntityReference(String name)throws DOMException, JRexException;
	private native ProcessingInstruction CreateProcessingInstruction(String target, String data)throws DOMException, JRexException;
	private native Text CreateTextNode(String data)throws JRexException;
	private native DocumentType GetDoctype()throws JRexException;
	private native Element GetDocumentElement()throws JRexException;
	private native Element GetElementById(String elementId)throws JRexException;
	private native NodeList GetElementsByTagName(String tagname)throws JRexException;
	private native NodeList GetElementsByTagNameNS(String namespaceURI, String localName)throws JRexException;
	private native DOMImplementation GetImplementation()throws JRexException;
	private native Node ImportNode(Node importedNode, boolean deep)throws DOMException, JRexException;
	private native DocumentRange GetDocumentRange()throws JRexException;
	private native DocumentEvent GetDocumentEvent()throws JRexException;
	private native DocumentTraversal GetDocumentTraversal()throws JRexException;
	private native DocumentView GetDocumentView()throws JRexException;
	//DOM3
	private native String GetInputEncoding()throws JRexException;
	private native String GetXmlEncoding()throws JRexException;
	private native boolean GetXmlStandalone()throws JRexException;
	private native void SetXmlStandalone(boolean xmlStandalone)throws DOMException, JRexException;
	private native String GetXmlVersion()throws JRexException;
        private native void SetXmlVersion(String xmlVersion)throws DOMException,JRexException;
        private native boolean GetStrictErrorChecking()throws JRexException;
        private native void SetStrictErrorChecking(boolean strictErrorChecking)throws JRexException;
        private native String GetDocumentURI()throws JRexException;
        private native void SetDocumentURI(String documentURI)throws JRexException;
        private native Node AdoptNode(Node source)throws DOMException, JRexException;
        private native DOMConfiguration GetDomConfig()throws JRexException;
        private native void NormalizeDocument()throws JRexException;
        private native Node RenameNode(Node n, String namespaceURI,String qualifiedName)throws DOMException, JRexException;

}
