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

package org.mozilla.jrex.dom.traversal;

import org.w3c.dom.Node;
import org.w3c.dom.DOMException;
import org.w3c.dom.traversal.*;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;


/**
* A class implementing org.w3c.dom.traversal.TreeWalker interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.traversal.TreeWalker
*/
public class JRexTreeWalkerImpl implements TreeWalker {

	private static final String className	= JRexTreeWalkerImpl.class.getName();
	private int peerTreeWkr;;

    public Node getRoot(){
		if(JRexL.on)JRexL.log(className,"**** getRoot ****");
		Node node=null;
		try{
			node=GetRoot();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRoot node<"+node+"> ****");
		return node;
	}

    public int getWhatToShow(){
		if(JRexL.on)JRexL.log(className,"**** getWhatToShow ****");
		int what=0;
		try{
			what= GetWhatToShow();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getWhatToShow what<"+what+"> ****");
		return what;
	}

    public NodeFilter getFilter(){
		if(JRexL.on)JRexL.log(className,"**** getFilter ****");
		NodeFilter nodeFlt=null;
		try{
			nodeFlt=GetFilter();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFilter nodeFlt<"+nodeFlt+"> ****");
		return nodeFlt;
	}

    public boolean getExpandEntityReferences(){
		if(JRexL.on)JRexL.log(className,"**** getExpandEntityReferences I AM HERE ****");
		boolean expand=false;
		try{
			expand=GetExpandEntityReferences();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getExpandEntityReferences expand<"+expand+"> ****");
		return expand;
	}

    public Node getCurrentNode(){
		if(JRexL.on)JRexL.log(className,"**** getCurrentNode ****");
		Node node=null;
		try{
			node=GetCurrentNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCurrentNode node<"+node+"> ****");
		return node;
	}

    public void setCurrentNode(Node currentNode)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** setCurrentNode currentNode<"+currentNode+"> ****");
		try{
			SetCurrentNode(currentNode);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public Node parentNode(){
		if(JRexL.on)JRexL.log(className,"**** parentNode ****");
		Node node=null;
		try{
			node=ParentNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** parentNode node<"+node+"> ****");
		return node;
	}

    public Node firstChild(){
		if(JRexL.on)JRexL.log(className,"**** firstChild ****");
		Node node=null;
		try{
			node=FirstChild();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** firstChild node<"+node+"> ****");
		return node;
	}

    public Node lastChild(){
		if(JRexL.on)JRexL.log(className,"**** lastChild ****");
		Node node=null;
		try{
			node=LastChild();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** lastChild node<"+node+"> ****");
		return node;
	}

    public Node previousSibling(){
		if(JRexL.on)JRexL.log(className,"**** previousSibling ****");
		Node node=null;
		try{
			node=PreviousSibling();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** previousSibling node<"+node+"> ****");
		return node;

	}

    public Node nextSibling(){
		if(JRexL.on)JRexL.log(className,"**** nextSibling ****");
		Node node=null;
		try{
			node=NextSibling();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** nextSibling node<"+node+"> ****");
		return node;

	}

    public Node nextNode()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** nextNode ****");
		Node node=null;
		try{
			node=NextNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** nextNode node<"+node+"> ****");
		return node;
	}

    public Node previousNode()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** previousNode ****");
		Node node=null;
		try{
			node=PreviousNode();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** previousNode node<"+node+"> ****");
		return node;
	}

    public boolean equals(Object obj) {
		return (obj instanceof JRexTreeWalkerImpl)?
				this.peerTreeWkr==((JRexTreeWalkerImpl)obj).peerTreeWkr:false;
    }

    public int hashCode(){
		return peerTreeWkr;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerTreeWkr!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerTreeWkr=0;
		}
	}

    private native Node GetRoot()throws JRexException;
    private native int GetWhatToShow()throws JRexException;
    private native NodeFilter GetFilter()throws JRexException;
    private native boolean GetExpandEntityReferences()throws JRexException;
    private native Node GetCurrentNode()throws JRexException;
    private native void SetCurrentNode(Node currentNode)throws DOMException, JRexException;
    private native Node ParentNode()throws JRexException;
    private native Node FirstChild()throws JRexException;
    private native Node LastChild()throws JRexException;
    private native Node PreviousSibling()throws JRexException;
    private native Node NextSibling()throws JRexException;
    private native Node PreviousNode()throws JRexException;
    private native Node NextNode()throws JRexException;
    private native void Finalize()throws JRexException;
}
