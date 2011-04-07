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

package org.mozilla.jrex.event.history;

/**
* The JRex HistoryListener interface, This listener can be added to listen to any
* History related events.
* @see org.mozilla.jrex.ui.JRexCanvas#addHistoryListener(org.mozilla.jrex.event.history.HistoryListener)
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface HistoryListener{

	/**
	* called to notify a listener when a new document is
	* added to session history. New documents are added to
	* session history by docshell when new pages are loaded
	* in a frame or content area.
	* For this event the HistoryEvent's getEventParam will return uri of the document to be
	* added to session history
	* @see	HistoryEvent#getEventParam()
	*/
	public void    addEntry(HistoryEvent event);

	/**
	* called to notify a listener when the user presses the 'back' button
	* of the browser OR when the user attempts to go back one page
	* in history thro' other means, from javascript or using nsIWebNavigation
	*
	* For this event the HistoryEvent's getEventParam will return uri of the previous page
	* which is to be loaded.
	*
	* @return A boolean flag returned by the listener to
	*         indicate if the back operation is to be aborted
	*         or continued.  If the listener returns <code>true</code>, it indicates
	*         that the back operation can be continued else back operation will be aborted.
	*         This is a mechanism for the listener to control user's operations with history.
	* @see	HistoryEvent#getEventParam()
	*/
	public boolean goBack(HistoryEvent event);

	/**
	* called to notify a listener when the user presses the 'forward' button
	* of the browser OR when the user attempts to go forward one page
	* in history thro' other means, from javascript or using nsIWebNavigation
	*
	* For this event the HistoryEvent's getEventParam will return uri of the next page
	* which is to be loaded.
	*
	* @return A boolean flag returned by the listener to
	*         indicate if the forward operation is to be aborted
	*         or continued.  If the listener returns <code>true</code>, it indicates
	*         that the forward operation can be continued else forward operation will be aborted.
	*         This is a mechanism for the listener to control user's operations with history.
	* @see	HistoryEvent#getEventParam()
	*/
	public boolean goForward(HistoryEvent event);

	/**
	* called to notify a listener when the user presses the 'reload' button
	* of the browser OR when the user attempts to reload the current document
	* through other means, like from javascript or using nsIWebNavigation
	*
	* For this event the HistoryEvent's getEventParam will return IntegerEventParam instance
	* with 'int' data containing reloadFlags and 'uri' containing uri of the current document
	* to be reloaded.
	* @return A boolean flag returned by the listener to
	*         indicate if the reload operation is to be aborted
	*         or continued.  If the listener returns <code>true</code>, it indicates
	*         that the reload operation can be continued else reload operation will be aborted.
	*         This is a mechanism for the listener to control user's operations with history.
	*
	* @see	IntegerEventParam
	* @see	HistoryEvent#getEventParam()
	*/
	public boolean reload(HistoryEvent event);

	/**
	* called to notify a listener when the user visits a page using the 'Go' menu
	* of the browser OR when the user attempts to go to a page at a particular index
	* through other means, like from javascript or using nsIWebNavigation
	*
	* For this event the HistoryEvent's getEventParam will return IntegerEventParam instance
	* with 'int' data containing index in history of the document to be loaded and 'uri'
	* containing uri of the document to be loaded.
	*
	* @return A boolean flag returned by the listener to
	*         indicate if the GotoIndex operation is to be aborted
	*         or continued.  If the listener returns <code>true</code>, it indicates
	*         that the GotoIndex operation can be continued else GotoIndex operation will be aborted.
	*         This is a mechanism for the listener to control user's operations with history.
	*
	* @see	IntegerEventParam
	* @see	HistoryEvent#getEventParam()
	*/
	public boolean goToIndex(HistoryEvent event);

	/**
	* called to notify a listener when documents are removed from session
	* history. Documents can be removed from session history for various
	* reasons. For example to control the memory usage of the browser, to
	* prevent users from loading documents from history, to erase evidence of
	* prior page loads etc...
	*
	* For this event the HistoryEvent's getEventParam will return IntegerEventParam instance
	* with 'int' data containing number of documents to be removed from session history.
	*
	* @return A boolean flag returned by the listener to
	*         indicate if the purge operation is to be aborted
	*         or continued.  If the listener returns <code>true</code>, it indicates
	*         that the purge operation can be continued else purge operation will be aborted.
	*         This is a mechanism for the listener to control user's operations with history.
	* @see	HistoryEvent#getEventParam()
	*
	* Note:-         While purging history, the older documents are removed
	*                and newly loaded documents are kept. For example  if there
	*                are 5 documents in history, and purge is called with 3 entries
	* 				 to be removed, then document 1, 2 and 3 are removed from history
	*                and most recently loaded document 4 and 5 are kept.
	*/
	public boolean purge(HistoryEvent event);
}
