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

package org.mozilla.jrex.navigation;

import java.util.ArrayList;
import java.util.Collection;

import org.mozilla.jrex.log.JRexL;
import org.mozilla.jrex.exception.JRexException;

/**
* History data wrapper class.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class History{

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* The index of this selected history entry.
	*/
	private int currIndex;

	/**
	* No of history entries in the History.
	*/
	private int maxLength;

	/**
	* List of history entries in the History.
	*/
	private ArrayList list=new ArrayList(10);

	public History(){}

	/**
	* Returns the number of history entries in the History.
	*/
	public int getCount(){
		return list.size();
	}

	/**
	* Returns the selected history entry index.
	*/
	public int getSelectedIndex(){
		return currIndex;
	}

	/**
	* Returns the maximum number of history entries allowed.
	*/
	public int getMaxLength(){
		return maxLength;
	}

	/**
	* Sets the maximum number of history entries allowed.
	*/
	public void setMaxLength(int length){
		this.maxLength=length;
	}

	/**
	* Called to obtain HistoryEntry at a given index.
	*
	* @param	index	The index value whose entry is requested.
	* @param	modifyIndex	If <code>true</code> indicates the current
	*                          index of session history should be modified
	*                          to the parameter <code>index</code>.
	*
	* @return	HistoryEntry at a given index.
	*/
	public HistoryEntry getEntryAtIndex(int index, boolean modifyIndex){
		if(modifyIndex)
			currIndex=index;
		return (HistoryEntry)list.get(index);
	}

	/**
	* Called to purge older HistoryEntry from history.
	* HistoryEntry's can be removed from session history for various
	* reasons. For example to  control memory usage of the browser, to
	* prevent users from loading documents from history, to erase evidence of
	* prior page loads etc...
	*
	* @param numEntries        The number of toplevel HistoryEntry's to be
	*                          purged from history. During purge operation,
	*                          the latest HistoryEntry's are maintained and older
	*                          'numEntries' HistoryEntry's are removed from history.
	*
	* Note:- presently this function does nothing.
	*/
	public void purgeHistory(int numEntries){

	}

	/**
	* Called to obtain a list for all the  HistoryEntry's stored in
	* session history.
	*/
	public Collection elements(){
		return list;
	}

	private static native void initIDs()throws JRexException;
}

