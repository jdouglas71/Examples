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

import java.util.*;
import org.mozilla.jrex.log.JRexL;

/** ResourceBundle helper class. The resource string can contain '&' and '@'
* '&' is used to represent Mnemonic, the character immediately after '&' will become the Mnemonic.
* '@' is used to represent Accelerator, the character immediately after '@' will become the Accelerator.
* E.g. Property file entry <FL_NEW_WINDOW	=&New Window @B>
* The Mnemonic will be 'N', Accelerator char will be 'B' and
* Resource String will be 'New Window'
* Note:- The ACCELCHAR '@' should be always at the end after Resource String
*
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public final class JRexResource {
	private static final String className 		= JRexResource.class.getName();
	private static final char		MNEMONICCHAR= '&';
	private static final char 		ACCELCHAR 	= '@';
	private static final String		MNEMONICSTR = "&";
	private static final String		ACCELSTR 	= "@";

    private static ResourceBundle	rBundle		= null;

	static{
        try{
            rBundle=ResourceBundle.getBundle("jrex",Locale.getDefault(),JRexResource.class.getClassLoader());
        }catch(Exception ex){
			JRexL.printStackTrace(ex);
       }
    }

	private JRexResource(){}


	/**
	 * Used to retrieve a string for a specified key from the resource file,
	 * the first occurrence of 'MNEMONICCHAR' is removed.
	 * This method is used to retrieve a string which is used for a mnemonic field.
	 * The resource file has the form TestkeyResource.<locale>
	 *
	 * @param  resourceId Key for the string to be loaded from the resource file.
	 * @return The requested string.
	 * @see JRexResource#getMnemonic
	 */
	public static String getString(String resourceId) {
		StringBuffer  resource = null;
		try {
			resource = new StringBuffer(rBundle.getString(resourceId));
		} catch (MissingResourceException e) {
			if(JRexL.on)JRexL.log(className,"**** getString() MissingResourceException <"+e.getMessage()+"> ****");
		}
		if(resource!=null){
			int index=resource.indexOf(MNEMONICSTR);
			if(index!=-1)
				resource.deleteCharAt(index);
			index=resource.lastIndexOf(ACCELSTR);
			return index==-1?resource.toString().trim():resource.substring(0,index).trim();
		}
		return resourceId;
	}

	/**
	 * Used to retrieve the mnemonic character of a string for a specified key from the resource file.
	 * The mnemonic character is marked by an leading ampersand
	 * which is removed when retrieving the String with getString
	 * @see JRexResource#getString
	 * @param	resourceId Key of the string to get the Mnemonic for.
	 * @return	The mnemonic character of the string if found otherwise \u0000.
	 */
	public static char getMnemonic(String resourceId) {
		String resource=null;
		try {
			resource = rBundle.getString(resourceId);
		} catch (MissingResourceException e) {
			if(JRexL.on)JRexL.log(className,"**** getMnemonic() MissingResourceException <"+e.getMessage()+"> ****");
		}
		return resource==null?'\0':getMnemonicChar(resource);
	}

	/**
	 * Used to retrieve the mnemonic character of a string for a specified key from the resource file.
	 * The mnemonic character is marked by an leading ampersand
	 * which is removed when retrieving the String with getString
	 * @see JRexResource#getString
	 * @param	resourceId Key of the string to get the Mnemonic for.
	 * @return	The mnemonic character of the string if found otherwise \u0000.
	 */
	public static char getAccelerator(String resourceId) {
		String resource=null;
		try {
			resource = rBundle.getString(resourceId);
		} catch (MissingResourceException e) {
			if(JRexL.on)JRexL.log(className,"**** getMnemonic() MissingResourceException <"+e.getMessage()+"> ****");
		}
		return resource==null?'\0':getMnemonicChar(resource);
	}

    /**
     * Returns the character just after the MNEMONICCHAR symbol.
     */
    public static char getMnemonicChar(String resStr) {
		int index=resStr.indexOf(MNEMONICCHAR);
		return index==-1?'\0':resStr.charAt(index+1);
    }

    /**
     * Returns the character just after the ACCELCHAR symbol.
     */
    public static char getAcceleratorChar(String resStr) {
		int index=resStr.lastIndexOf(ACCELCHAR);
		return index==-1?'\0':resStr.charAt(index+1);
    }

    /**
     * Retrieves image icon for given image name
     * @param   iconName   name of the image file
     * @return  the imageicon for given iconName
    */
    public static javax.swing.ImageIcon getIcon(String iconName){
        java.net.URL imgURL=JRexResource.class.getClassLoader().getResource("icons/"+iconName+".gif");
        return imgURL==null?null:new javax.swing.ImageIcon(imgURL);
    }


    /**
     * An utility function to show information message.
     * @param   parent the parent for the message dialog.
     * @param   message the message to be shown
     * @param   suppress true to suppress the information message dialog.
    */
    public static void showInfoMessage(java.awt.Component parent,
                							String message,boolean suppress){
        javax.swing.JOptionPane.showMessageDialog(parent,message,
                    getString("INFO_TITLE"),javax.swing.JOptionPane.INFORMATION_MESSAGE) ;
    }

    /**
     * An utility function to show warning message.
     * @param   parent the parent for the message dialog.
     * @param   message the message to be shown
     * @param   suppress true to suppress the warning message dialog.
    */
    public static void showWarningMessage(java.awt.Component parent,
              								  String message,boolean suppress){
        javax.swing.JOptionPane.showMessageDialog(parent,message,getString("WAR_TITLE"),javax.swing.JOptionPane.WARNING_MESSAGE) ;
    }

    /**
     * An utility function to show information message.
     * @param   parent the parent for the message dialog.
     * @param   message the message to be shown
     * @param   suppress true to suppress the error message dialog.
    */
    public static void showErrorMessage(java.awt.Component parent,
                							String message,boolean suppress){
       	javax.swing.JOptionPane.showMessageDialog(parent,message,getString("ERR_TITLE"),
        							                javax.swing.JOptionPane.ERROR_MESSAGE) ;
    }


    /**
     * An utility function to show formatted warning message.
     * @param   parent the parent for the message dialog.
     * @param   message the message to be shown
     * @param   formatArray the message format parameters.
     * @param   suppress true to suppress the warning message dialog.
     */
    public static void showFormattedWarningMessage(java.awt.Component parent,
                										String message,Object[] formatArray, boolean suppress){
        javax.swing.JOptionPane.showMessageDialog(parent,new java.text.MessageFormat(message).format(formatArray),
                    									getString("WAR_TITLE"),javax.swing.JOptionPane.WARNING_MESSAGE);
    }
}
