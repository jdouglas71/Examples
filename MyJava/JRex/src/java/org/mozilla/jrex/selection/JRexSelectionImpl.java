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

package org.mozilla.jrex.selection;

import org.w3c.dom.Node;
import org.w3c.dom.ranges.Range;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* JRexSelectionImpl implements JRexSelection interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class JRexSelectionImpl implements JRexSelection{

	private static final String className =JRexSelectionImpl.class.getName();
	private int jrexPeer=0;

	public void setJRexPeer(int jrexPeer){
		this.jrexPeer=jrexPeer;
	}

  	public Node getAnchorNode()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getAnchorNode jrexPeer<"+jrexPeer+"> ****");
		Node node=null;
		try{
			node=GetAnchorNode(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAnchorNode node<"+node+"> ****");
		return node;
	}

	public int getAnchorOffset()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getAnchorOffset jrexPeer<"+jrexPeer+"> ****");
		int offset=0;
		try{
			offset=GetAnchorOffset(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getAnchorOffset offset<"+offset+"> ****");
		return offset;
	}

  	public Node getFocusNode()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getFocusNode jrexPeer<"+jrexPeer+"> ****");
		Node node=null;
		try{
			node=GetFocusNode(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFocusNode node<"+node+"> ****");
		return node;
	}

	public int getFocusOffset()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getFocusOffset jrexPeer<"+jrexPeer+"> ****");
		int offset=0;
		try{
			offset=GetFocusOffset(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getFocusOffset offset<"+offset+"> ****");
		return offset;
	}

	public boolean getIsCollapsed()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getIsCollapsed jrexPeer<"+jrexPeer+"> ****");
		boolean collapsed=false;
		try{
			collapsed=GetIsCollapsed(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getIsCollapsed collapsed<"+collapsed+"> ****");
		return collapsed;
	}

	public int getRangeCount()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getRangeCount jrexPeer<"+jrexPeer+"> ****");
		int count=0;
		try{
			count=GetRangeCount(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRangeCount count<"+count+"> ****");
		return count;
	}

  	public Range getRangeAt(int index)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getRangeAt jrexPeer<"+jrexPeer+"> index<"+index+"> ****");
		Range range=null;
		try{
			range=GetRangeAt(jrexPeer,index);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** getRangeAt range<"+range+"> ****");
		return range;
	}

  	public void collapse(Node parentNode, int offset)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** collapse jrexPeer<"+jrexPeer+"> parentNode<"+parentNode+"> offset<"+offset+"> ****");
		try{
			Collapse(jrexPeer, parentNode, offset);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

  	public void extend(Node parentNode, int offset)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** extend jrexPeer<"+jrexPeer+"> parentNode<"+parentNode+"> offset<"+offset+"> ****");
		try{
			Extend(jrexPeer, parentNode, offset);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

  	public void collapseToStart()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** collapseToStart jrexPeer<"+jrexPeer+"> ****");
		try{
			CollapseToStart(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void collapseToEnd()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** collapseToEnd jrexPeer<"+jrexPeer+"> ****");
		try{
			CollapseToEnd(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

  	public boolean containsNode(Node node, boolean entirelyContained)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** containsNode jrexPeer<"+jrexPeer+"> node<"+node+"> entirelyContained<"+entirelyContained+"> ****");
		boolean contains=false;
		try{
			contains=ContainsNode(jrexPeer, node, entirelyContained);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** containsNode jrexPeer<"+jrexPeer+"> contains<"+contains+"> ****");
		return contains;
	}


	public void selectAllChildren(Node parentNode)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** selectAllChildren jrexPeer<"+jrexPeer+"> parentNode<"+parentNode+"> ****");
		try{
			SelectAllChildren(jrexPeer, parentNode);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void addRange(Range range)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** addRange jrexPeer<"+jrexPeer+"> range<"+range+"> ****");
		try{
			AddRange(jrexPeer, range);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void removeRange(Range range)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** removeRange jrexPeer<"+jrexPeer+"> range<"+range+"> ****");
		try{
			RemoveRange(jrexPeer, range);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

  	public void removeAllRanges()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** removeAllRanges jrexPeer<"+jrexPeer+"> ****");
		try{
			RemoveAllRanges(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

  	public void deleteFromDocument()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** deleteFromDocument jrexPeer<"+jrexPeer+"> ****");
		try{
			DeleteFromDocument(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public void selectionLanguageChange(boolean langRTL)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** selectionLanguageChange jrexPeer<"+jrexPeer+"> langRTL<"+langRTL+"> ****");
		try{
			SelectionLanguageChange(jrexPeer, langRTL);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
	}

	public String toString(){
		if(JRexL.on)JRexL.log(className,"**** toString jrexPeer<"+jrexPeer+"> ****");
		String string=null;
		try{
			string=ToString(jrexPeer);
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
		}
		if(JRexL.on)JRexL.log(className,"**** toString string<"+string+"> ****");
		return string;
	}

  	private native Node GetAnchorNode(int jrexPeer)throws JRexException;
	private native int GetAnchorOffset(int jrexPeer)throws JRexException;
  	private native Node GetFocusNode(int jrexPeer)throws JRexException;
	private native int GetFocusOffset(int jrexPeer)throws JRexException;
	private native boolean GetIsCollapsed(int jrexPeer)throws JRexException;
	private native int GetRangeCount(int jrexPeer)throws JRexException;
  	private native Range GetRangeAt(int jrexPeer, int index)throws JRexException;
  	private native void Collapse(int jrexPeer, Node parentNode, int offset)throws JRexException;
  	private native void Extend(int jrexPeer, Node parentNode, int offset)throws JRexException;
  	private native void CollapseToStart(int jrexPeer)throws JRexException;
	private native void CollapseToEnd(int jrexPeer)throws JRexException;
  	private native boolean ContainsNode(int jrexPeer, Node node, boolean entirelyContained)throws JRexException;
	private native void SelectAllChildren(int jrexPeer, Node parentNode)throws JRexException;
	private native void AddRange(int jrexPeer, Range range)throws JRexException;
	private native void RemoveRange(int jrexPeer, Range range)throws JRexException;
  	private native void RemoveAllRanges(int jrexPeer)throws JRexException;
  	private native void DeleteFromDocument(int jrexPeer)throws JRexException;
	private native void SelectionLanguageChange(int jrexPeer, boolean langRTL)throws JRexException;
	private native String ToString(int jrexPeer)throws JRexException;

}

