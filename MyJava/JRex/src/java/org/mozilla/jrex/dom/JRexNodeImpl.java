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
import org.w3c.dom.events.EventTarget;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.Node interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.Node
*/

public class JRexNodeImpl implements Node{

	private static final String className	= JRexNodeImpl.class.getName();
    private int peerNode = 0;

    /** Intended to be used by JNI */
    protected JRexNodeImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexNodeImpl I AM HERE ****");
	}

	public Node appendChild(Node newChild)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** appendChild newChild<"+newChild+"> ****");
		Node node=null;
		try{
			node=AppendChild(newChild);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** appendChild node<"+node+"> ****");
		return node;
	}

	public Node cloneNode(boolean deep){
		if(JRexL.on)JRexL.log(className,"**** cloneNode deep<"+deep+"> ****");
		Node node=null;
		try{
			node=CloneNode(deep);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** appendChild node<"+node+"> ****");
		return node;
	}

	public NamedNodeMap getAttributes(){
		if(JRexL.on)JRexL.log(className,"**** getAttributes ****");
		NamedNodeMap nMap=null;
		try{
			nMap=GetAttributes();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAttributes nMap<"+nMap+"> ****");
		return nMap;
	}

	public NodeList getChildNodes(){
		if(JRexL.on)JRexL.log(className,"**** getChildNodes ****");
		NodeList nList=null;
		try{
			nList=GetChildNodes();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getChildNodes nList<"+nList+"> ****");
		return nList;
	}

	public Node getFirstChild(){
		if(JRexL.on)JRexL.log(className,"**** getFirstChild ****");
		Node node=null;
		try{
			node=GetFirstChild();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFirstChild node<"+node+"> ****");
		return node;
	}

	public Node getLastChild(){
		if(JRexL.on)JRexL.log(className,"**** getLastChild ****");
		Node node=null;
		try{
			node=GetLastChild();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLastChild node<"+node+"> ****");
		return node;
	}

	public String getLocalName(){
		if(JRexL.on)JRexL.log(className,"**** getLocalName ****");
		String name=null;
		try{
			name=GetLocalName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getLocalName name<"+name+"> ****");
		return name;
	}

	public String getNamespaceURI(){
		if(JRexL.on)JRexL.log(className,"**** getNamespaceURI ****");
		String name=null;
		try{
			name=GetNamespaceURI();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNamespaceURI name<"+name+"> ****");
		return name;
	}

	public Node getNextSibling(){
		if(JRexL.on)JRexL.log(className,"**** getNextSibling ****");
		Node node=null;
		try{
			node=GetNextSibling();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNextSibling node<"+node+"> ****");
		return node;
	}

	public String getNodeName(){
		if(JRexL.on)JRexL.log(className,"**** getNodeName ****");
		String name=null;
		try{
			name=GetNodeName();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNodeName name<"+name+"> ****");
		return name;
	}

	public short getNodeType(){
		if(JRexL.on)JRexL.log(className,"**** getNodeType ****");
		short nType=0;
		try{
			nType=GetNodeType();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNodeType nType<"+nType+"> ****");
		return nType;
	}

	public String getNodeValue()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getNodeValue ****");
		String value=null;
		try{
			value=GetNodeValue();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getNodeValue value<"+value+"> ****");
		return value;
	}

	public Document getOwnerDocument(){
		if(JRexL.on)JRexL.log(className,"**** getOwnerDocument ****");
		Document doc=null;
		try{
			doc=GetOwnerDocument();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getOwnerDocument doc<"+doc+"> ****");
		return doc;
	}

	public Node getParentNode(){
		if(JRexL.on)JRexL.log(className,"**** getParentNode ****");
		Node node=null;
		try{
			node=GetParentNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getParentNode node<"+node+"> ****");
		return node;
	}

	public String getPrefix(){
		if(JRexL.on)JRexL.log(className,"**** getPrefix ****");
		String prefix=null;
		try{
			prefix=GetPrefix();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getPrefix prefix<"+prefix+"> ****");
		return prefix;
	}

	public Node getPreviousSibling(){
		if(JRexL.on)JRexL.log(className,"**** getPreviousSibling ****");
		Node node=null;
		try{
			node=GetPreviousSibling();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getPreviousSibling node<"+node+"> ****");
		return node;
	}

	public boolean hasAttributes(){
		if(JRexL.on)JRexL.log(className,"**** hasAttributes ****");
		boolean hasAttr=false;
		try{
			hasAttr=HasAttributes();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** hasAttributes hasAttr<"+hasAttr+"> ****");
		return hasAttr;
	}

	public boolean hasChildNodes(){
		if(JRexL.on)JRexL.log(className,"**** hasChildNodes ****");
		boolean hasChild=false;
		try{
			hasChild=HasChildNodes();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** hasChildNodes hasChild<"+hasChild+"> ****");
		return hasChild;
	}

	public Node insertBefore(Node newChild, Node refChild)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** insertBefore newChild<"+newChild+"> refChild<"+refChild+"> ****");
		Node node=null;
		try{
			node=InsertBefore(newChild, refChild);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** insertBefore node<"+node+"> ****");
		return node;
	}

	public boolean isSupported(String feature, String version){
		if(JRexL.on)JRexL.log(className,"**** isSupported feature<"+feature+"> version<"+version+"> ****");
		boolean isSupported=false;
		try{
			isSupported=IsSupported(feature, version);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** isSupported isSupported<"+isSupported+"> ****");
		return isSupported;
	}

	public void normalize(){
		if(JRexL.on)JRexL.log(className,"**** normalize ****");
		try{
			Normalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public Node removeChild(Node oldChild)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** removeChild oldChild<"+oldChild+"> ****");
		Node node=null;
		try{
			node=RemoveChild(oldChild);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** removeChild node<"+node+"> ****");
		return node;
	}

	public Node replaceChild(Node newChild, Node oldChild)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** replaceChild newChild<"+newChild+"> oldChild<"+oldChild+"> ****");
		Node node=null;
		try{
			node=ReplaceChild(newChild, oldChild);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** replaceChild node<"+node+"> ****");
		return node;
	}

	public void setNodeValue(String nodeValue)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setNodeValue nodeValue<"+nodeValue+"> ****");
		try{
			SetNodeValue(nodeValue);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void setPrefix(String prefix)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setPrefix prefix<"+prefix+"> ****");
		try{
			SetPrefix(prefix);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public EventTarget getEventTarget(){
		if(JRexL.on)JRexL.log(className,"**** getEventTarget I AM HERE ****");
		EventTarget evtTarg=null;
		try{
			evtTarg=GetEventTarget();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEventTarget evtTarg<"+evtTarg+"> ****");
		return evtTarg;
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexNodeImpl))
			return false;
		return ((JRexNodeImpl)obj).peerNode==peerNode;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerNode;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerNode!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerNode=0;
		}
	}

    private final static String getNodeTypeString(int type) {
		switch (type) {
			case ATTRIBUTE_NODE:				return "ATTRIBUTE_NODE";
			case CDATA_SECTION_NODE:			return "CDATA_SECTION_NODE";
			case COMMENT_NODE:					return "COMMENT_NODE";
			case DOCUMENT_FRAGMENT_NODE:		return "DOCUMENT_FRAGMENT_NODE";
			case DOCUMENT_NODE:					return "DOCUMENT_NODE";
			case DOCUMENT_TYPE_NODE:			return "DOCUMENT_TYPE_NODE";
			case ELEMENT_NODE: 					return "ELEMENT_NODE";
			case ENTITY_NODE: 					return "ENTITY_NODE";
			case ENTITY_REFERENCE_NODE: 		return "ENTITY_REFERENCE_NODE";
			case NOTATION_NODE: 				return "NOTATION_NODE";
			case PROCESSING_INSTRUCTION_NODE:	return "PROCESSING_INSTRUCTION_NODE";
			case TEXT_NODE: 					return "TEXT_NODE";
			default:							return "UNKNOWN_NODE";
		}
    }

	StringBuffer buf;
	public String toString(){
		if(buf==null){
			buf=new StringBuffer(128);
			buf.append("\nNodePeer <").append(peerNode).append(">\n")
			.append("NodeType <").append(getNodeTypeString(getNodeType())).append(">\n")
			.append("NodeName <").append(getNodeName()).append(">\n")
			.append("LocalName <").append(getLocalName()).append(">\n")
			.append("NamespaceURI <").append(getNamespaceURI()).append(">\n")
			.append("NodeValue <").append(getNodeValue()).append(">\n")
			.append("hasAttributes <").append(hasAttributes()).append(">\n")
			.append("hasChildNodes <").append(hasChildNodes()).append(">\n");
		}
		return buf.toString();
	}

	//DOM3
	public String getBaseURI(){
		if(JRexL.on)JRexL.log(className,"**** getBaseURI ****");
		String baseUri=null;
		try{
			baseUri=GetBaseURI();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getBaseURI baseUri<"+baseUri+"> ****");
		return baseUri;
	}

	public short compareDocumentPosition(Node other)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** compareDocumentPosition ****");
		short cmp=0;
		try{
			cmp=CompareDocumentPosition(other);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** compareDocumentPosition cmp<"+cmp+"> ****");
		return cmp;
	}

	public String getTextContent() throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getTextContent ****");
		String text=null;
		try{
			text=GetTextContent();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getTextContent text<"+text+"> ****");
		return text;
	}

	public void setTextContent(String textContent)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setTextContent textContent<"+textContent+"> ****");
		try{
			SetTextContent(textContent);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}

	}

	public boolean isSameNode(Node other){
		if(JRexL.on)JRexL.log(className,"**** isSameNode other<"+other+">****");
		boolean isSameNode=false;
		try{
			isSameNode=IsSameNode(other);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** isSameNode isSameNode<"+isSameNode+"> ****");
		return isSameNode;
	}

	public String lookupPrefix(String namespaceURI){
		if(JRexL.on)JRexL.log(className,"**** lookupPrefix ****");
		String prefix=null;
		try{
			prefix=LookupPrefix(namespaceURI);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** lookupPrefix prefix<"+prefix+"> ****");
		return prefix;
	}

	public boolean isDefaultNamespace(String namespaceURI){
		if(JRexL.on)JRexL.log(className,"**** isDefaultNamespace namespaceURI<"+namespaceURI+">****");
		boolean isDefaultNamespace=false;
		try{
			isDefaultNamespace=IsDefaultNamespace(namespaceURI);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** isDefaultNamespace isDefaultNamespace<"+isDefaultNamespace+"> ****");
		return isDefaultNamespace;
	}

	public String lookupNamespaceURI(String prefix){
		if(JRexL.on)JRexL.log(className,"**** lookupNamespaceURI ****");
		String nsUri=null;
		try{
			nsUri=LookupNamespaceURI(prefix);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** lookupNamespaceURI nsUri<"+nsUri+"> ****");
		return nsUri;
	}

	public boolean isEqualNode(Node arg){
		if(JRexL.on)JRexL.log(className,"**** isEqualNode arg<"+arg+">****");
		boolean isEqualNode=false;
		try{
			isEqualNode=IsEqualNode(arg);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** isEqualNode isEqualNode<"+isEqualNode+"> ****");
		return isEqualNode;
	}

	public Object getFeature(String feature, String version){
		if(JRexL.on)JRexL.log(className,"**** getFeature feature<"+feature+"> version<"+version+">****");
		Object objFeature=null;
		try{
			objFeature=GetFeature(feature, version);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFeature objFeature<"+objFeature+"> ****");
		return objFeature;
	}

	public Object setUserData(String key, Object data, UserDataHandler handler){
		if(JRexL.on)JRexL.log(className,"**** setUserData key<"+key+"> data<"+
												data+"> handler<"+handler+">****");
		Object objFeature=null;
		try{
			objFeature=SetUserData(key, data.toString(), handler);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** setUserData objFeature<"+objFeature+"> ****");
		return objFeature;
	}

	public Object getUserData(String key){
		if(JRexL.on)JRexL.log(className,"**** getUserData key<"+key+"> ****");
		Object userData=null;
		try{
			userData=GetUserData(key);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getUserData userData<"+userData+"> ****");
		return userData;
	}


	private native Node AppendChild(Node newChild)throws DOMException, JRexException;
	private native Node CloneNode(boolean deep)throws JRexException;
	private native NamedNodeMap GetAttributes()throws JRexException;
	private native NodeList GetChildNodes()throws JRexException;
	private native Node GetFirstChild()throws JRexException;
	private native Node GetLastChild()throws JRexException;
	private native String GetLocalName()throws JRexException;
	private native String GetNamespaceURI()throws JRexException;
	private native Node GetNextSibling()throws JRexException;
	private native String GetNodeName()throws JRexException;
	private native short GetNodeType()throws JRexException;
	private native String GetNodeValue()throws DOMException, JRexException;
	private native Document GetOwnerDocument()throws JRexException;
	private native Node GetParentNode()throws JRexException;
	private native String GetPrefix()throws JRexException;
	private native Node GetPreviousSibling()throws JRexException;
	private native boolean HasAttributes()throws JRexException;
	private native boolean HasChildNodes()throws JRexException;
	private native Node InsertBefore(Node newChild, Node refChild)throws DOMException, JRexException;
	private native boolean IsSupported(String feature, String version)throws JRexException;
	private native void Normalize()throws JRexException;
	private native Node RemoveChild(Node oldChild)throws DOMException, JRexException;
	private native Node ReplaceChild(Node newChild, Node oldChild)throws DOMException, JRexException;
	private native void SetNodeValue(String nodeValue)throws DOMException, JRexException;
	private native void SetPrefix(String prefix)throws DOMException, JRexException;
	private native EventTarget GetEventTarget()throws JRexException;
	private native void Finalize()throws JRexException;
	//DOM3
	private native String GetBaseURI()throws JRexException;
	private native short CompareDocumentPosition(Node other)throws DOMException, JRexException;
	private native String GetTextContent() throws DOMException, JRexException;
	private native void SetTextContent(String textContent)throws DOMException ,JRexException;
	private native boolean IsSameNode(Node other)throws JRexException;
	private native String LookupPrefix(String namespaceURI)throws JRexException;
	private native boolean IsDefaultNamespace(String namespaceURI)throws JRexException;
	private native String LookupNamespaceURI(String prefix)throws JRexException;
	private native boolean IsEqualNode(Node arg)throws JRexException;
	private native Object GetFeature(String feature, String version)throws JRexException;
	private native String SetUserData(String key, String data, UserDataHandler handler)throws JRexException;
	private native String GetUserData(String key)throws JRexException;
}
