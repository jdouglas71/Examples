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

package org.mozilla.jrex.event.context;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;
import org.w3c.dom.Node;

/**
* A class representing JRex ContextMenu Event.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class ContextMenuEvent{

	private static final String className =ContextMenuEvent.class.getName();

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The target browser component to which the event belongs.
	*/
	private int 	jrexPeer;

	/**
	* The context flags for the event.
	*/
	private int 	contextFlags;

	/**
	* The x co-ordinate where context menu should be displayed.
	*/
	private int 	cX;

	/**
	* The y co-ordinate where context menu should be displayed.
	*/
	private int 	cY;

	/**
	* The node for the event.
	*/
	private Node	targetNode;

	/**
	* The node type for the event.
	*/
	private int 	nodeType;

	/**
	* The uri for the event.
	*/
	private String	uri;

	/**
	* The image uri for the event, if any.
	*/
	private String	imgUri;

	/**
	* ContextMenuEvent constructor
	* @param jrexPeer  target browser component to which the event belongs
	* @param contextFlags  context flags for the event.
	* @param cX  x co-ordinate where context menu should be displayed.
	* @param cY  y co-ordinate where context menu should be displayed.
	* @param nodeType node type for the event.
	* @param uri  uri for the event.
	* @param imgUri  image uri for the event, if any.
	* @see ContextMenuEventConstants
	*/
	public ContextMenuEvent(int jrexPeer,int contextFlags,int cX, int cY,
												Node targetNode, int nodeType, String uri, String imgUri){
		if(JRexL.on)JRexL.log(className,"**** ContextMenuEvent()-->jrexPeer<"+jrexPeer+
									">contextFlags<"+contextFlags+"> cX<"+cX+">cY<"+cY+
										"> targetNode<"+targetNode+"> nodeType<"+nodeType+"> uri<"+uri+"> imgUri<"+imgUri+"> ****");
		this.jrexPeer	= jrexPeer;
		this.contextFlags=contextFlags;
		this.cX=cX;
		this.cY=cY;
		this.targetNode=targetNode;
		this.nodeType=nodeType;
		this.uri=uri;
		this.imgUri=imgUri;
	}

	/**
	* Returns the target browser component to which the ContextMenu event belongs.
	*/
	public int getJRexPeer(){
		return jrexPeer;
	}

	/**
	* Returns context flags for the event.
	*/
	public int getContextFlags(){
		return contextFlags;
	}

	/**
	* Returns x co-ordinate where context menu should be displayed.
	*/
	public int getClientX(){
		return cX;
	}

	/**
	* Returns y co-ordinate where context menu should be displayed.
	*/
	public int getClientY(){
		return cY;
	}

	/**
	* Returns node for the event. Will be <code>null</code> if DOM is not enabled.
	*/
	public Node getTargetNode(){
		return targetNode;
	}

	/**
	* Returns node type for the event.
	*/
	public int getNodeType(){
		return nodeType;
	}

	/**
	* Returns uri for the event.
	*/
	public String getURI(){
		return uri;
	}

	/**
	* Returns mage uri for the event, if any.
	*/
	public String getImageURI(){
		return imgUri;
	}

	public String toString(){
		StringBuffer buf=new StringBuffer(512);
		buf.append("\njrexPeer <").append(jrexPeer).append(">\n")
		.append("contextFlags <").append(contextFlags).append(">\n")
		.append("cX <").append(cX).append(">\n")
		.append("cY <").append(cY).append(">\n")
		.append("targetNode <").append(targetNode).append(">\n")
		.append("nodeType <").append(nodeType).append(">\n")
		.append("uri <").append(uri).append(">\n")
		.append("imgUri <").append(imgUri).append(">\n");
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}