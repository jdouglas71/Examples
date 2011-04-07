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

package org.mozilla.jrex.ui;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.log.JRexL;

/**
* A Data class to hold all the find operation related data.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public class JRexFindConfig{
	private static final String className	= JRexFindConfig.class.getName();
	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	/**
	* If string to search.
	*/
	private String	searchString;

	/**
	* If true search direction will be backward.
	*/
	private boolean	findBackwards;

	/**
	* If true search continues after end/begin(in case of backword search) of page.
	*/
	private boolean	wrapFind;

	/**
	* If true search try's to match only complete word.
	*/
	private boolean	entireWord;

	/**
	* If true search is case sensitive.
	*/
	private boolean	matchCase;

	/**
	* If true frames are searched.
	*/
	private boolean	searchFrames;

	/**
	* Constructor to create config for search operation.
	* @param searchString	the string to search.
	* @param findBackwards	If true search direction will be backward.
	* @param wrapFind	If true search continues after end/begin(in case of backward search) of page.
	* @param entireWord	If true search try's to match only complete word.
	* @param matchCase	If true search is case sensitive.
	* @param searchFrames	If true frames are searched.
	*/
	public JRexFindConfig(String searchString, boolean findBackwards, boolean wrapFind,
						boolean entireWord, boolean matchCase, boolean searchFrames){
		if(JRexL.on)JRexL.log(className,"**** JRexFindConfig() -->searchString<"+searchString+
													"> findBackwards<"+findBackwards+
													"> wrapFind<"+wrapFind+
													"> entireWord<"+entireWord+
													"> matchCase<"+matchCase+
													"> searchFrames<"+searchFrames+"> ****");
		this.searchString=searchString;
		this.findBackwards=findBackwards;
		this.wrapFind=wrapFind;
		this.entireWord=entireWord;
		this.matchCase=matchCase;
		this.searchFrames=searchFrames;
	}

	/**
	* Constructor to create config for search operation.
	* @param searchString	the string to search.
	* Note:- rest of the find parameteres are all set to false.
	* @see #JRexFindConfig(String,boolean,boolean,boolean,boolean,boolean)
	*/
	public JRexFindConfig(String searchString){
		this(searchString, false, false, false,false,false);
	}


	/**
	* Returns Search String for the config.
	*/
	public String getSearchString(){
		return 	searchString;
	}

	/**
	* Returns true search direction will be backward.
	*/
	public boolean isFindBackwards(){
		return findBackwards;
	}

	/**
	* Returns true if continues after end/begin(in case of backward search) of page.
	*/
	public boolean isWrapFind(){
		return wrapFind;
	}

	/**
	* Returns true if search try's to match only complete word.
	*/
	public boolean isEntireWord(){
		return entireWord;
	}

	/**
	* Returns true if search is case sensitive.
	*/
	public boolean isMatchCase(){
		return matchCase;
	}

	/**
	* Returns true if frames are searched.
	*/
	public boolean isSearchFrames(){
		return searchFrames;
	}

	StringBuffer buf;
	public String toString(){
		if(buf==null){
			buf=new StringBuffer(128);
			buf.append("\nsearchString <").append(searchString).append(">\n")
			.append("findBackwards <").append(findBackwards).append(">\n")
			.append("wrapFind <").append(wrapFind).append(">\n")
			.append("entireWord <").append(entireWord).append(">\n")
			.append("matchCase <").append(matchCase).append(">\n")
			.append("searchFrames <").append(searchFrames).append(">\n");
		}
		return buf.toString();
	}

	private static native void initIDs()throws JRexException;
}
