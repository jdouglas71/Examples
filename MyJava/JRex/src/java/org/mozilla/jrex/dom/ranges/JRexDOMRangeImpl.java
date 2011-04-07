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

package org.mozilla.jrex.dom.ranges;

import org.w3c.dom.*;
import org.w3c.dom.ranges.*;
import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;



/**
* A class implementing org.w3c.dom.ranges.Range interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
* see http://www.w3.org/TR/DOM-Level-2-Traversal-Range/
*/
public class JRexDOMRangeImpl implements Range{

	private static final String className	= JRexDOMRangeImpl.class.getName();
    private int peerRange=0;

    private JRexDOMRangeImpl() {
		if(JRexL.on)JRexL.log(className,"**** JRexDOMRangeImpl I AM HERE ****");
    }

	public Node getStartContainer()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getStartContainer I AM HERE ****");
		Node node=null;
		try{
			node=GetStartContainer();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getStartContainer node<"+node+"> ****");
		return node;
	}

	public int getStartOffset()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getStartOffset I AM HERE ****");
		int startOffSet=0;
		try{
			startOffSet=GetStartOffset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getStartOffset startOffSet<"+startOffSet+"> ****");
		return startOffSet;
	}

	public Node getEndContainer()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getEndContainer I AM HERE ****");
		Node node=null;
		try{
			node=GetEndContainer();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEndContainer node<"+node+"> ****");
		return node;
	}

	public int getEndOffset()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getEndOffset I AM HERE ****");
		int endOffSet=0;
		try{
			endOffSet=GetEndOffset();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getEndOffset endOffSet<"+endOffSet+"> ****");
		return endOffSet;
	}

	public boolean getCollapsed()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getCollapsed I AM HERE ****");
		boolean collapsed=false;
		try{
			collapsed=GetCollapsed();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCollapsed collapsed<"+collapsed+"> ****");
		return collapsed;
	}

	public Node getCommonAncestorContainer()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** getCommonAncestorContainer I AM HERE ****");
		Node node=null;
		try{
			node=GetCommonAncestorContainer();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getCommonAncestorContainer node<"+node+"> ****");
		return node;
	}


	public void setStart(Node node, int offSet)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setStart node<"+node+"> offSet<"+offSet+"> ****");
		try{
			SetStart(node, offSet);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void setEnd(Node node, int offSet)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setEnd node<"+node+"> offSet<"+offSet+"> ****");
		try{
			SetEnd(node, offSet);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void setStartBefore(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setStartBefore node<"+node+"> ****");
		try{
			SetStartBefore(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void setStartAfter(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setStartAfter node<"+node+"> ****");
		try{
			SetStartAfter(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void setEndBefore(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setEndBefore node<"+node+"> ****");
		try{
			SetEndBefore(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void setEndAfter(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** setEndAfter node<"+node+"> ****");
		try{
			SetEndAfter(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void collapse(boolean toStart)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** collapse toStart<"+toStart+"> ****");
		try{
			Collapse(toStart);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void selectNode(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** selectNode node<"+node+"> ****");
		try{
			SelectNode(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void selectNodeContents(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** selectNodeContents node<"+node+"> ****");
		try{
			SelectNodeContents(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public short compareBoundaryPoints(short cmpType, Range srcRange)throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** compareBoundaryPoints cmpType<"+cmpType+"> srcRange<"+srcRange+"> ****");
		short rv=0;
		try{
			rv=CompareBoundaryPoints(cmpType, srcRange);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** compareBoundaryPoints rv<"+rv+"> ****");
		return rv;
	}


	public void deleteContents()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** deleteContents I AM HERE ****");
		try{
			DeleteContents();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public DocumentFragment extractContents()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** extractContents I AM HERE ****");
		DocumentFragment docFrag=null;
		try{
			docFrag=ExtractContents();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** extractContents docFrag<"+docFrag+"> ****");
		return docFrag;
	}


	public DocumentFragment cloneContents()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** cloneContents I AM HERE ****");
		DocumentFragment docFrag=null;
		try{
			docFrag=CloneContents();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** cloneContents docFrag<"+docFrag+"> ****");
		return docFrag;
	}


	public void insertNode(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** insertNode node<"+node+"> ****");
		try{
			InsertNode(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public void surroundContents(Node node)throws RangeException, DOMException{
		if(JRexL.on)JRexL.log(className,"**** surroundContents node<"+node+"> ****");
		try{
			SurroundContents(node);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}


	public Range cloneRange()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** cloneRange I AM HERE ****");
		Range range=null;
		try{
			range=CloneRange();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** cloneRange range<"+range+"> ****");
		return range;
	}


    public String toString()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** toString I AM HERE ****");
		String rv="";
		try{
			rv=ToString();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** toString rv<"+rv+"> ****");
		return rv;
	}


    public void detach()throws DOMException{
		if(JRexL.on)JRexL.log(className,"**** detach ****");
		try{
			Detach();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

    public boolean equals(Object obj) {
		if(JRexL.on)JRexL.log(className,"**** equals obj<"+obj+"> ****");
		if(!(obj instanceof JRexDOMRangeImpl))
			return false;
		return ((JRexDOMRangeImpl)obj).peerRange==peerRange;
	}

    public int hashCode(){
		if(JRexL.on)JRexL.log(className,"**** hashCode ****");
		return peerRange;
    }

    protected void finalize()throws Throwable{
		if(JRexL.on)JRexL.log(className,"**** finalize ****");
		dispose();
		super.finalize();
	}

	/** Function to explicitly disconnect from native DOM Object */
    public void dispose(){
		if(JRexL.on)JRexL.log(className,"**** dispose ****");
		if(peerRange!=0)
		try{
			Finalize();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}finally{
			peerRange=0;
		}
	}

	private native Node GetStartContainer()throws DOMException, JRexException;
	private native int GetStartOffset()throws DOMException, JRexException;
	private native Node GetEndContainer()throws DOMException, JRexException;
	private native int GetEndOffset()throws DOMException, JRexException;
	private native boolean GetCollapsed()throws DOMException, JRexException;
	private native Node GetCommonAncestorContainer()throws DOMException, JRexException;
	private native void SetStart(Node node, int offset)throws RangeException, DOMException, JRexException;
	private native void SetEnd(Node node, int offset)throws RangeException, DOMException, JRexException;
	private native void SetStartBefore(Node node)throws RangeException, DOMException, JRexException;
	private native void SetStartAfter(Node node)throws RangeException, DOMException, JRexException;
	private native void SetEndBefore(Node node)throws RangeException, DOMException, JRexException;
	private native void SetEndAfter(Node node)throws RangeException, DOMException, JRexException;
	private native void Collapse(boolean toStart)throws DOMException, JRexException;
	private native void SelectNode(Node node)throws RangeException, DOMException, JRexException;
	private native void SelectNodeContents(Node node)throws RangeException, DOMException, JRexException;
	private native short CompareBoundaryPoints(int cmpType, Range range)throws DOMException, JRexException;
	private native void DeleteContents()throws DOMException, JRexException;
	private native DocumentFragment ExtractContents()throws DOMException, JRexException;
	private native DocumentFragment CloneContents()throws DOMException, JRexException;
	private native void InsertNode(Node node)throws RangeException, DOMException, JRexException;
	private native void SurroundContents(Node node)throws RangeException, DOMException, JRexException;
	private native Range CloneRange()throws DOMException, JRexException;
	private native String ToString()throws DOMException, JRexException;
	private native void Detach()throws DOMException, JRexException;
	private native void Finalize()throws JRexException;
}
