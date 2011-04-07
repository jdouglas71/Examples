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
package test;
import org.mozilla.jrex.JRexFactory;
import org.mozilla.jrex.window.JRexWindowManager;

public class JRexExample {
	public static void main(String s[])throws Exception{
		/*
		javax.swing.JFrame main=new javax.swing.JFrame("MAIN");
		javax.swing.JPanel panel=new javax.swing.JPanel(new java.awt.BorderLayout());
		main.setContentPane(panel);
		main.setSize(400,400);
		main.setVisible(true);*/
        //Uncomment WEBSTART SECTION below for webstart deployement
        //-------- WEBSTART SECTION START -------------------
		/*String installPath=System.getProperty("user.home");
		if(!installPath.endsWith(java.io.File.separator))
			installPath += java.io.File.separator;
		System.setProperty("jrex.gre.path",installPath+"jrex_gre");*/
		//-------- WEBSTART SECTION END -------------------

		JRexFactory.getInstance().startEngine();
		//java.util.ArrayList list=(java.util.ArrayList)org.mozilla.jrex.pref.JRexPreference.getInstance().getPrefChildren("");
		//for(int i=0;i<list.size();i++){
		//	System.err.println("Pref ["+i+"]"+	list.get(i));
		//}

		//USING PROXY?
		//org.mozilla.jrex.pref.JRexPreference prefs=org.mozilla.jrex.pref.JRexPreference.getInstance();
		//prefs.setDefaultCharPref("network.proxy.http","192.168.144.007");
		//prefs.setDefaultIntPref("network.proxy.http_port",3128);
		//prefs.setDefaultIntPref("network.proxy.type", 1);

		JRexWindowManager winManager=(JRexWindowManager)JRexFactory.getInstance().getImplInstance(JRexFactory.WINDOW_MANAGER);
		winManager.create(JRexWindowManager.TAB_MODE);
		//add your jrex windowlistener here
		winManager.addJRexWindowListener(new org.mozilla.jrex.event.window.WindowListener(){
			public void windowCreated(int jrexPeerID){
				System.err.println(" windowCreated ##################### jrexPeerID <"+jrexPeerID+">#####################");
			}
			public void windowDisposing(int jrexPeerID){
				System.err.println("windowDisposing ##################### jrexPeerID <"+jrexPeerID+">#####################");
			}
		});
		winManager.init(null);
	}
}
