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

import java.io.InputStream;

import org.mozilla.jrex.exception.JRexException;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.log.JRexL;


/**
* Class implementing WebNavigation interface.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class WebNavigationImpl implements WebNavigation{
	private static final String className =WebNavigationImpl.class.getName();

	static{
		try{
			initIDs();
		}catch(JRexException ex){
			JRexL.printStackTrace(ex);
			throw new RuntimeException(ex);
		}
	}

	private int jrexPeer=0;

	public void setJRexPeer(int jrexPeer){
		this.jrexPeer=jrexPeer;
	}

	public boolean canGoBack()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** canGoBack jrexPeer<"+jrexPeer+"> ****");
		return CanGoBack(jrexPeer);
	}


	public boolean canGoForward()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** canGoForward jrexPeer<"+jrexPeer+"> ****");
		return CanGoForward(jrexPeer);
	}

	public boolean goBack()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** goBack jrexPeer<"+jrexPeer+"> ****");
		return GoBack(jrexPeer);
	}


	public boolean goForward()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** goForward jrexPeer<"+jrexPeer+"> ****");
		return GoForward(jrexPeer);
	}

	public boolean goToIndex(int index)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** goToIndex jrexPeer<"+jrexPeer+"> index<"+index+"> ****");
		return GoToIndex(jrexPeer,index);
	}

	public  void loadURI(java.net.URI uri, int loadFlags,
					java.net.URI referrer, InputStream postData, InputStream headers)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** loadURI-URI jrexPeer<"+jrexPeer+"> loadFlags<"+loadFlags+"> uri<"+uri+
										">postData<"+postData+"> headers<"+headers+"> ****");
		loadURI(uri.normalize().toString(), loadFlags, (referrer==null?null:referrer.normalize().toString()),postData, headers);
	}

	public  void loadURI(String uri, int loadFlags, String referrer, InputStream postData, InputStream headers)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** loadURI jrexPeer<"+jrexPeer+"> loadFlags<"+loadFlags+"> uri<"+uri+
										">postData<"+postData+"> headers<"+headers+"> ****");
		LoadURI(jrexPeer,uri, loadFlags, referrer,postData, headers);
	}

	public void loadStream(InputStream inStream, String uri, String contentType, String charset,int loadFlags,
							String referURI, Object owner, boolean inheritOwner,String target,
								InputStream postData, InputStream headers)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** loadStream jrexPeer<"+jrexPeer+"> uri<"+uri+"> contentType<"+contentType+"> charset<"+charset+
										">loadFlags<"+loadFlags+"> referURI<"+referURI+"> inheritOwner<"+inheritOwner+
										"> target<"+target+"> ****");
		LoadStream(jrexPeer, inStream, uri, contentType, charset,loadFlags, referURI, owner,
					inheritOwner, target, postData, headers);
	}


	public  void openWindow(short type, String uri, String referrer, String windowName, String features)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** openWindow jrexPeer<"+jrexPeer+"> type<"+type+
										">uri<"+uri+"> referrer<"+referrer+
										">windowName<"+windowName+"> features<"+features+"> ****");
		OpenWindow(jrexPeer, type, uri, referrer, windowName, features);
	}

	public void reload(int reloadFlags)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** reload jrexPeer<"+jrexPeer+"> reloadFlags<"+reloadFlags+"> ****");
		Reload(jrexPeer,reloadFlags);
	}

    public void goToAnchor(String anchorName, boolean shouldScroll)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** goToAnchor jrexPeer<"+jrexPeer+"> anchorName<"+anchorName+"> shouldScroll<"+shouldScroll+"> ****");
		GoToAnchor(jrexPeer,anchorName,shouldScroll);
    }

    public String getContentString(String contType, int outFlag)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getContentString jrexPeer<"+jrexPeer+"> contType<"+contType+"> outFlag<"+outFlag+"> ****");
		return GetContentString(jrexPeer,contType,outFlag);
    }

    public void stop(int stopFlags)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** stop jrexPeer<"+jrexPeer+"> stopFlags<"+stopFlags+"> ****");
		Stop(jrexPeer,stopFlags);
	}

	public org.w3c.dom.Document getDocument()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getDocument jrexPeer<"+jrexPeer+"> ****");
		return JRexFactory.getInstance().isDOMEnabled()?GetDocument(jrexPeer):null;
	}

	public java.net.URI getCurrentURI()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getCurrentURI jrexPeer<"+jrexPeer+"> ****");
		String sURI=GetCurrentURI(jrexPeer);
		if(JRexL.on)JRexL.log(className,"getCurrentURI sURI<"+sURI+">");
		try{
			return sURI==null?null:new java.net.URI(sURI);
		}catch(Exception ex){
			JRexL.printStackTrace(ex);
			throw new JRexException("creating uri failed <"+ex.getMessage()+">");
		}
	}

	public java.net.URI getReferringURI()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getReferringURI jrexPeer<"+jrexPeer+"> ****");
		String rURI=GetReferringURI(jrexPeer);
		if(JRexL.on)JRexL.log(className,"getReferringURI rURI<"+rURI+">");
		try{
			return rURI==null?null:new java.net.URI(rURI);
		}catch(Exception ex){
			JRexL.printStackTrace(ex);
			throw new JRexException("creating ref uri failed <"+ex.getMessage()+">");
		}
	}

	public History getSessionHistory()throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** getSessionHistory jrexPeer<"+jrexPeer+"> ****");
		return GetSessionHistory(jrexPeer);
	}

	public void setSessionHistory(History his)throws JRexException{
		if(JRexL.on)JRexL.log(className,"**** setSessionHistory jrexPeer<"+jrexPeer+"> his<"+his+"> ****");
		SetSessionHistory(jrexPeer,his);
	}

	private static native void initIDs()throws JRexException;
	private native boolean CanGoBack(int jrexPeer)throws JRexException;
	private native boolean CanGoForward(int jrexPeer)throws JRexException;
	private native boolean GoBack(int jrexPeer)throws JRexException;
	private native boolean GoForward(int jrexPeer)throws JRexException;
	private native boolean GoToIndex(int jrexPeer,int index)throws JRexException;
	private native  void LoadURI(int jrexPeer, String uri, int loadFlags, String referURI,
									InputStream postData, InputStream headers)throws JRexException;
	private native void LoadStream(int jrexPeer,InputStream inStream, String uri, String contentType,
							String charset,int loadFlags, String referURI, Object owner,
								boolean inheritOwner, String target,
								InputStream postData, InputStream headers)throws JRexException;
	private native void OpenWindow(int jrexPeer, short type, String uri, String referrer, String windowName, String features)throws JRexException;
	private native void Reload(int jrexPeer,int reloadFlags)throws JRexException;
    private native void GoToAnchor(int jrexPeer, String anchorName, boolean shouldScroll);
    private native String GetContentString(int jrexPeer, String contType, int outFlag);
	private native void Stop(int jrexPeer,int stopFlags)throws JRexException;
	private native org.w3c.dom.Document GetDocument(int jrexPeer)throws JRexException;
	private native String GetCurrentURI(int jrexPeer)throws JRexException;
	private native String GetReferringURI(int jrexPeer)throws JRexException;
	private native History GetSessionHistory(int jrexPeer)throws JRexException;
	private native void SetSessionHistory(int jrexPeer,History his)throws JRexException;
}
