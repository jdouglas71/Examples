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

import org.mozilla.jrex.exception.JRexException;

/**
* WebNavigation interface defines navigation related operations.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/
public interface WebNavigation{

 	/**
	* The peer JREX Window on which to navigate
	* @param	jrexPeer jrex peer window associated with browser component
	*/
	public void setJRexPeer(int jrexPeer);

	/**
	* Indicates if the object can go back.  If true this indicates that
	* there is back session history available for navigation.
	*/
	public boolean canGoBack()throws JRexException;

	/**
	* Indicates if the object can go forward.  If true this indicates that
	* there is forward session history available for navigation
	*/

	public boolean canGoForward()throws JRexException;

	/**
	* Tells the object to navigate to the previous session history item.  When
	* a page is loaded from session history, all content is loaded from the
	* cache (if available) and page state (such as form values, scroll position)
	* is restored.
	*
	* @return true               - Backward navigation was successful.
	*         false - This call was unexpected at this time.  Most
	*                               likely you can't go back right now.
	*/
	public boolean goBack()throws JRexException;

	/**
	* Tells the object to navigate to the next Forward session history item.
	* When a page is loaded from session history, all content is loaded from
	* the cache (if available) and page state (such as form values, scroll
	* position) is restored.
	*
	* @return true               - Forward was successful.
	*         false - This call was unexpected at this time.  Most
	*                               likely you can't go forward right now.
	*/
	public boolean goForward()throws JRexException;


	/**
	* Tells the object to navigate to the session history item at index.
	*
	* @return true -               GotoIndex was successful.
	*         false - This call was unexpected at this time.  Most
	*                               likely you can't goto that index
	*/
	public boolean goToIndex(int index)throws JRexException;


	/**
	* Loads a given URI.  This will give priority to loading the requested URI
	* in the object implementing	this interface.  If it can't be loaded here
	* however, the URL dispatcher will go through its normal process of content
	* loading.
	*
	* @param	uri			The URI string to load.
	* @param	loadFlags	Flags modifying load behaviour. Generally you will pass
	*                   				 LOAD_FLAGS_NONE for this parameter.
	* @param	referURI	The referring URI.  If this argument is NULL, the
	*                    				referring URI will be inferred internally.
	* @param	postData	InputStream containing POST data for the request.
	* @param	headers		InputStream containing POST headers for the request.
	* @see WebNavigationConstants
	*/
	public  void loadURI(java.net.URI uri, int loadFlags, java.net.URI referURI, java.io.InputStream postData, java.io.InputStream headers)throws JRexException;

	/**
	* Loads a given URI.  This will give priority to loading the requested URI
	* in the object implementing	this interface.  If it can't be loaded here
	* however, the URL dispatcher will go through its normal process of content
	* loading.
	*
	* @param	uri      	The URI string to load.
	* @param	loadFlags	Flags modifying load behaviour. Generally you will pass
	*                    LOAD_FLAGS_NONE for this parameter.
	* @param	referURI	The referring URI.  If this argument is NULL, the
	*                    referring URI will be inferred internally.
	* @param	postData	InputStream containing POST data for the request.
	* @param	headers		InputStream containing POST headers for the request.
	*/
	public  void loadURI(String uri, int loadFlags, String referURI, java.io.InputStream postData, java.io.InputStream headers)throws JRexException;

	/**
	* Loads a given stream. This will give priority to loading the requested
	* stream in the object implementing this interface. If it can't be loaded
	* here however, the URL dispatched will go through its normal process of
	* content loading.
	*
	* @param inStream	The input stream that provides access to the data to be loaded.
	* 						This must be a blocking stream.
	* @param uri		The URI representing the stream, or <code>null</code>
	* @param contentType	The type (MIME) of data being loaded, <code>null</code> if unknown.
	* @param charset	The charset of the data being loaded, <code>null</code> if unknown.
        * @param loadFlags	Flags to modify load behaviour. Flags are defined in WebNavigationConstants
     							Use loadStream() specific flags.
	* @param referURI	The referring URI for the load.
	* @param owner	Owner (security principal), for now it is just a place holder, set it to <code>null</code>.
	* @param inheritOwner	If true owner inherits the owner from the referring document.
	* @param target	Target for load, like _content, _blank etc.
	* @param postData	InputStream containing POST data for the request.
	* @param headers		InputStream containing POST headers for the request.
	*/
	public void loadStream(java.io.InputStream inStream, String uri, String contentType, String charset,
							int loadFlags, String referURI, Object owner, boolean inheritOwner, String target,
								java.io.InputStream postData, java.io.InputStream headers)throws JRexException;

	/**
	* Open a new window.
	* @param	type the type of window
	* @param	uri to which to open the new window. Must already be
	*	 		escaped if applicable. can be null.
	* @param	referrer the refence uri to be used.
	* @param	windowName window name from JS window.open. can be null.
	* @param	features window features from JS window.open. can be null.
	* Note:- The window attached to this navigator will be parent.
	* @see WebNavigationConstants
	*/
	public  void openWindow(short type, String uri, String referrer, String windowName, String features)throws JRexException;


	/**
	* Tells the Object to reload the current page.
	*
	* @param	reloadFlags - Flags modifying reload behaviour. Generally you will
	*                      pass LOAD_FLAGS_NONE for this parameter.
	*/
	public void reload(int reloadFlags)throws JRexException;

	/**
    * Informs the pres shell that the document is now at the anchor with
    * the given name.  If |shouldScroll| is true, scrolls the view of the
    * document so that the anchor with the specified name is displayed at
    * the top of the window.  If |anchorName| is empty, then this informs
    * the pres shell that there is no current target, and |shouldScroll| must
    * be false.
	*
	* @param	anchorName the name of the new anchor tag for the current document
	* @param	shouldScroll specifies whether or not to scroll the anchor to the top of
     * the window.
	*/
    public void goToAnchor(String anchorName, boolean shouldScroll)throws JRexException;

	/**
    * Returns the string representation of loaded Content.
	*
	* @param	contType The Content type to be used.
	* @param	outFlag specifies how the content should be converted to string,
    * @see WebNavigationConstants
	*/
    public String getContentString(String contType, int outFlag)throws JRexException;

	/**
	* Stops a load of a URI.
	*
	* @param	stopFlags - Flags indicating the stop behavior.
	*/
	public void stop(int stopFlags)throws JRexException;

	/**
	* Retrieves the current DOM document for the frame, or lazily creates a
	* blank document if there is none. This attribute never returns null except
	* for unexpected error situations.
	*/
	public org.w3c.dom.Document getDocument()throws JRexException;

	/**
	* Get the currently loaded URI or null.
	*/
	public java.net.URI getCurrentURI()throws JRexException;

	/**
	* Get the referring URI for the current open page.
	*/
	public java.net.URI getReferringURI()throws JRexException;

	/**
	* Get the session history object used to store the session history for the
	* session.
	* @return	The Session history object.
	*/
	public History getSessionHistory()throws JRexException;

	/**
	* Set the session history object used to store the session history for the
	* session.
	* @param	his - The Session history object.
	*/
	public void setSessionHistory(History his)throws JRexException;
}




