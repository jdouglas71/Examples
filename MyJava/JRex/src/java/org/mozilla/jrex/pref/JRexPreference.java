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

package org.mozilla.jrex.pref;

import java.util.ArrayList;
import java.util.Collection;
import org.mozilla.jrex.exception.JRexException;

/**
* JRexPreference wraps the <b>nsIPref</b>. This class is used read and write embedded engine
* Preferences.
* @author <a href="mailto:jrex_moz@yahoo.com">C.N.Medappa</a>
* @version 1.0
*/

public class JRexPreference {
	private final static String className = JRexPreference.class.getName();

	/** A contant representing  invalid preference type */
	public final static int PREF_INVALID	=0;

	/** A contant representing  string preference type */
	public final static int PREF_STRING		=32;

	/** A contant representing  int preference type */
	public final static int PREF_INT		=64;

	/** A contant representing  boolean preference type */
	public final static int PREF_BOOL		=128;

	/** A JRexPreference instance*/
	private static final JRexPreference instance = new JRexPreference();

	private JRexPreference(){}

	/**
	* Returns an JRexPreference instance.
	*/
	public static JRexPreference getInstance(){
		return instance;
	}

	/**
	* Reads user preference from given file.
	*
	* @param	file The complete path of file from which preference should be read.
	*/
	public void readUserPrefs(String file)throws JRexException{
		ReadUserPrefs(file);
	}

	/**
	* Called to reset preferences
	*/
	public void resetPrefs()throws JRexException{
		ResetPrefs();
	}

	/**
	* Called to reset user  preferences
	*/
	public void resetUserPrefs()throws JRexException{
		ResetUserPrefs();
	}

	/**
	* Saves the preference to given file.
	*
	* @param	file The complete path of file to which preference should be saved.
	*/
	public void savePrefFile(String file)throws JRexException{
		SavePrefFile(file);
	}

	/**
	* Called to get the root on which this branch is based, such as
	* "browser.startup."
	*/
	public String getRoot()throws JRexException{
		return GetRoot();
	}

	/**
	* Called to determine the type of a specific preference.
	*
	* @param	prefName The preference to get the type of.
	*
	* @return	long     A value representing the type of the preference. This
	*                  value will be PREF_STRING, PREF_INT, or PREF_BOOL.
	*/
   	public long getPrefType(String prefName)throws JRexException{
		return GetPrefType(prefName);
   	}


	/**
	* Called to get the state of an individual boolean preference.
	*
	* @param	prefName The boolean preference to get the state of.
	*
	* @return	boolean  The value of the requested boolean preference.
	*
	* @see #setBoolPref
	*/
	public boolean getBoolPref(String prefName)throws JRexException{
		return GetBoolPref(prefName);
	}


	/**
	* Called to set the state of an individual boolean preference.
	*
	* @param	prefName The boolean preference to set the state of.
	* @param	value    The boolean value to set the preference to.
	*
	* @see #getBoolPref
	*/
	public void setBoolPref(String prefName, boolean value)throws JRexException{
		SetBoolPref(prefName, value);
	}


	/**
	* Called to get the state of an individual string preference.
	*
	* @param prefName The string preference to retrieve.
	*
	* @return	The value of the requested string preference.
	*
	* @see #setCharPref
	*/
	public String getCharPref(String prefName)throws JRexException{
		return GetCharPref(prefName);
	}

	/**
	* Called to set the state of an individual string preference.
	*
	* @param prefName The string preference to set.
	* @param value    The string value to set the preference to.
	*
	* @see #getCharPref
	*/

	public void setCharPref(String prefName, String value)throws JRexException{
		SetCharPref(prefName, value);
	}

	/**
	* Called to get the state of an individual integer preference.
	*
	* @param	prefName The integer preference to get the value of.
	*
	* @return	The value of the requested integer preference.
	*
	* @see #setIntPref
	*/
  	public long getIntPref(String prefName)throws JRexException{
		return GetIntPref(prefName);
	}

	/**
	* Called to set the state of an individual integer preference.
	*
	* @param	prefName The integer preference to set the value of.
	* @param	value    The integer value to set the preference to.
	*
	* @see #getIntPref
	*/
	public void setIntPref(String prefName, long value)throws JRexException{
		SetIntPref(prefName, value);
	}

	/**
	* Called to clear a user set value from a specific preference. This will, in
	* effect, reset the value to the default value. If no default value exists
	* the preference will cease to exist.
	*
	* @param	prefName The preference to be cleared.
	*
	* Note:- 	This method does nothing if this object is a default branch.
	*
	*/
	public void clearUserPref(String prefName)throws JRexException{
		ClearUserPref(prefName);
	}


	/**
	* Called to get the state of is  preference is locked.
	*
	* @param	prefName The boolean preference to get the state of.
	*
	* @return	<code>true</code> if preference is locked else false.
	*/
	public boolean isPrefLocked(String prefName)throws JRexException{
		return IsPrefLocked(prefName);
	}

	/**
	* Called to lock a specific preference. Locking a preference will cause the
	* preference service to always return the default value regardless of
	* whether there is a user set value or not.
	*
	* @param	prefName The preference to be locked.
	*
	* Note:- This method can be called on either a default or user branch but, in
	* effect, always operates on the default branch.
	*
	*
	* @see #unlockPref
	*/
	public void lockPref(String prefName)throws JRexException{
		LockPref(prefName);
	}

	/**
	* Called to unlock a specific preference. Unlocking a previously locked
	* preference allows the preference service to once again return the user set
	* value of the preference.
	*
	* @param	prefName The preference to be unlocked.
	*
	* Note:- This method can be called on either a default or user branch but, in
	* effect, always operates on the default branch.
	*
	*
	* @see #lockPref
	*/
	public void unlockPref(String prefName)throws JRexException{
		UnLockPref(prefName);
	}

	/**
	* Called to check if a specific preference has a user value associated to
	* it.
	*
	* @param	aPrefName The preference to be tested.
	*
	* Note:- This method can be called on either a default or user branch but, in
	* effect, always operates on the user branch.
	*
	* @return <code>true</code>  The preference has a user set value.
	*                  false The preference only has a default value.
	*/
	//public boolean prefHasUserValue(String prefName)throws JRexException{
	//	return PrefHasUserValue(prefName);
	//}

	/**
	* Called to get the state of an Default individual boolean preference.
	*
	* @param	prefName The boolean preference to get the state of.
	*
	* @return	The value of the requested boolean preference.
	*
	* @see #setBoolPref
	*/
	public boolean getDefaultBoolPref(String prefName)throws JRexException{
		return GetDefaultBoolPref(prefName);
	}


	/**
	* Called to set the state of an Default individual boolean preference.
	*
	* @param	prefName The boolean preference to set the state of.
	* @param	value    The boolean value to set the preference to.
	*
	* @see #getBoolPref
	*/
	public void setDefaultBoolPref(String prefName, boolean value)throws JRexException{
		SetDefaultBoolPref(prefName, value);
	}


	/**
	* Called to get the state of an Default individual string preference.
	*
	* @param	prefName The string preference to retrieve.
	*
	* @return	The value of the requested string preference.
	*
	* @see #setCharPref
	*/
	public String getDefaultCharPref(String prefName)throws JRexException{
		return GetDefaultCharPref(prefName);
	}

	/**
	* Called to set the state of an Default individual string preference.
	*
	* @param	prefName The string preference to set.
	* @param	value    The string value to set the preference to.
	*
	* @see #getCharPref
	*/

	public void setDefaultCharPref(String prefName, String value)throws JRexException{
		SetDefaultCharPref(prefName, value);
	}

	/**
	* Called to get the state of an Default individual integer preference.
	*
	* @param	prefName The integer preference to get the value of.
	*
	* @return	The value of the requested integer preference.
	*
	* @see #setIntPref
	*/
  	public long getDefaultIntPref(String prefName)throws JRexException{
		return GetDefaultIntPref(prefName);
	}

	/**
	* Called to set the state of an Default individual integer preference.
	*
	* @param	prefName The integer preference to set the value of.
	* @param	value    The integer value to set the preference to.
	* @see #getIntPref
	*/
	public void setDefaultIntPref(String prefName, long value)throws JRexException{
		SetDefaultIntPref(prefName, value);
	}

	/**
	* Called to get the list of preferences.
	* @param	parentPrefName The parent preference to be enumerated.
	*
	* @return	The list children for give parent.
	*/
	public Collection getPrefChildren(String parentPrefName)throws JRexException{
		return GetPrefChildren(parentPrefName);
	}

	private native void ReadUserPrefs(String file)throws JRexException;
	private native void ResetPrefs()throws JRexException;
	private native void ResetUserPrefs()throws JRexException;
	private native void SavePrefFile(String file)throws JRexException;
	private native String GetRoot()throws JRexException;
	private native long GetPrefType(String prefName)throws JRexException;
	private native boolean GetBoolPref(String prefName)throws JRexException;
	private native void SetBoolPref(String prefName, boolean value)throws JRexException;
	private native String GetCharPref(String prefName)throws JRexException;
	private native void SetCharPref(String prefName, String value)throws JRexException;
	private native long GetIntPref(String prefName)throws JRexException;
	private native void SetIntPref(String prefName, long value)throws JRexException;
	private native void ClearUserPref(String prefName)throws JRexException;
	private native boolean IsPrefLocked(String prefName)throws JRexException;
	private native void LockPref(String prefName)throws JRexException;
	private native void UnLockPref(String prefName)throws JRexException;
	//private native boolean PrefHasUserValue(String prefName)throws JRexException;
	private native boolean GetDefaultBoolPref(String prefName)throws JRexException;
	private native void SetDefaultBoolPref(String prefName, boolean value)throws JRexException;
	private native String GetDefaultCharPref(String prefName)throws JRexException;
	private native void SetDefaultCharPref(String prefName, String value)throws JRexException;
	private native long GetDefaultIntPref(String prefName)throws JRexException;
	private native void SetDefaultIntPref(String prefName, long value)throws JRexException;
	private native ArrayList GetPrefChildren(String parentPrefName)throws JRexException;
}
