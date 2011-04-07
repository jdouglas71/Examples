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

import org.mozilla.jrex.exception.JRexException;
import org.w3c.dom.Node;
import org.w3c.dom.ranges.Range;

/**
* JRexSelection interface defines selection related operations.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface JRexSelection{

 	/**
	* The peer JREX Window on which to select
	* @param	jrexPeer jrex peer window associated with browser component
	*/
	public void setJRexPeer(int jrexPeer);
 	/**
	* Returns the node representing one end of the selection.
	*/
  	public Node getAnchorNode()throws JRexException;

	/**
	* Returns the offset within the (text) node where the selection begins.
	*/
	public int getAnchorOffset()throws JRexException;

 	/**
	* Returns the node with keyboard focus.
	*/
  	public Node getFocusNode()throws JRexException;

	/**
	* Returns the offset within the (text) node where focus starts.
	*/
	public int getFocusOffset()throws JRexException;

	/**
	* Indicates if the selection is collapsed or not.
	*/
	public boolean getIsCollapsed()throws JRexException;

	/**
	*  Returns the number of ranges in the selection.
	*/
	public int getRangeCount()throws JRexException;

 	/**
	* Returns the range at given <code>index</code>.
	* @param index the index of range to retrived.
	*/
  	public Range getRangeAt(int index)throws JRexException;

	/**
	* Collapses the selection to a single point, at the specified offset
	* in the given DOM node. When the selection is collapsed, and the content
	* is focused and editable, the caret will blink there.
	* @param parentNode	The given dom node where the selection will be set
	* @param offset		Where in given dom node to place the selection (the offset into the given node)
	*/
  	public void collapse(Node parentNode, int offset)throws JRexException;

	/**
	* Extends the selection by moving the focus to the specified node and offset,
	* preserving the anchor postion.  The new selection end result will always
	* be from the anchor to the new focus, regardless of direction.
	* @param parentNode      The node where the selection will be extended to
	* @param offset          Where in node to place the offset in the new focused node
	*/
  	public void extend(Node parentNode, int offset)throws JRexException;

	/**
	* Collapses the whole selection to a single point at the start
	* of the current selection (irrespective of direction).  If content
	* is focused and editable, the caret will blink there.
	*/
  	public void collapseToStart()throws JRexException;

	/**
	* Collapses the whole selection to a single point at the end
	* of the current selection (irrespective of direction).  If content
	* is focused and editable, the caret will blink there.
	*/
	public void collapseToEnd()throws JRexException;

	/**
	* The value of entirelyContained determines the detail of the search to determine if
	* the selection contains the node.  If entirelyContained is set to PR_TRUE, t
	* or false if
	* @param node	The node where the selection will be extended to
	* @param entirelyContained	Whether
	*/
  	public boolean containsNode(Node node, boolean entirelyContained)throws JRexException;


	/**
	* Adds all children of the specified node to the selection.
	* @param parentNode  the parent of the children to be added to the selection.
	*/
	public void selectAllChildren(Node parentNode)throws JRexException;

	/**
	* Adds a range to the current selection.
	* @param range	the range to be added.
	*/
	public void addRange(Range range)throws JRexException;

	/**
	* Removes a range from the current selection.
	* @param range	the range to be removed.
	*/
	public void removeRange(Range range)throws JRexException;

	/**
	* Removes all ranges from the current selection.
	*/
  	public void removeAllRanges()throws JRexException;

	/**
	* Deletes this selection from document the nodes belong to.
	*/
  	public void deleteFromDocument()throws JRexException;

	/**
	* Modifies the cursor Bidi level after a change in keyboard direction
	* @param langRTL	is <code>true</code> if the new language is right-to-left or
	*                <code>false</code> if the new language is left-to-right.
	*/
	public void selectionLanguageChange(boolean langRTL)throws JRexException;

	/**
	* Returns the whole selection into a plain text string.
	*/
	public String toString();

}