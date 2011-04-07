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
* A class implementing org.w3c.dom.traversal.DocumentTraversal interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* @see org.w3c.dom.traversal.DocumentTraversal
*/
public class JRexDocumentTraversalImpl implements DocumentTraversal {

	private static final String className	= JRexDocumentTraversalImpl.class.getName();
	private int peerDocTrav=0;

	private JRexDocumentTraversalImpl(){
		if(JRexL.on)JRexL.log(className,"**** JRexDocumentTraversalImpl I AM HERE ****");
	}
    public NodeIterator createNodeIterator(Node root,int whatToShow,NodeFilter filter,
                                           boolean entityReferenceExpansion)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createNodeIterator root<"+root+"> whatToShow<"+whatToShow+"> root<"+filter
									+"> entityReferenceExpansion<"+entityReferenceExpansion+"> ****");
		NodeIterator nodeItr=null;
		try{
			nodeItr=CreateNodeIterator(root,whatToShow,filter,entityReferenceExpansion);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createNodeIterator nodeItr<"+nodeItr+"> ****");
		return nodeItr;
	}

    public TreeWalker createTreeWalker(Node root,int whatToShow,
                                       NodeFilter filter,boolean entityReferenceExpansion)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** createTreeWalker root<"+root+"> whatToShow<"+whatToShow+"> root<"+filter
									+"> entityReferenceExpansion<"+entityReferenceExpansion+"> ****");
		TreeWalker tw=null;
		try{
			tw=CreateTreeWalker(root,whatToShow,filter,entityReferenceExpansion);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** createTreeWalker tw<"+tw+"> ****");
		return tw;
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexDocumentTraversalImpl))
			return false;
		return ((JRexDocumentTraversalImpl)obj).peerDocTrav==peerDocTrav;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerDocTrav;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerDocTrav!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerDocTrav=0;
		}
	}

    private native NodeIterator CreateNodeIterator(Node root,int whatToShow,NodeFilter filter,
                                           boolean entityReferenceExpansion)throws JRexException, DOMException;
    private native TreeWalker CreateTreeWalker(Node root,int whatToShow,NodeFilter filter,
                                       boolean entityReferenceExpansion)throws JRexException, DOMException;
	private native void Finalize()throws JRexException;

}
