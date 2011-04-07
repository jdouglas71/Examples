package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.manager.*;

/**
* IApplicationFrame. This interface allows the various components of an application to gain access to the application's frame.
* Accessed via the IApplicaiton class.
*
* @author Jason Douglas 3/22/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IApplicationFrame
{
	/** Normall application title */
	public static final int MAIN_TITLE	= 0;
	/** Error title */
	public static final int ERROR_TITLE	= 1;
	// Other types???? 
	 
	/** Menu constants */
	/** File menu */
	@Deprecated
	public static final int FILE_MENU 				= 0;
	/** Edit menu */
	@Deprecated
	public static final int EDIT_MENU				= 1;
	/** View menu */
	@Deprecated
	public static final int VIEW_MENU				= 2;
	/** Tools menu */
	@Deprecated
	public static final int TOOLS_MENU				= 3;
	/** Help menu */
	@Deprecated
	public static final int HELP_MENU				= 4;
	/** Manager menu */
	@Deprecated
	public static final int MANAGER_MENU			= 5;

	/** View state constants */
	//JGD NOTE: This is a first pass I did a while ago. Should be revamped to be more view centric and generic. JGD TODO
	/** top level tag name */
	public static final String VIEW_STATE_TAG                                                          		= "ViewState";
	/** Location Element */
	public static final String XML_LOCATION_ELEMENT                                                      	= "ViewLocation";
	/** Size Element */
	public static final String XML_SIZE_ELEMENT                                                          	= "ViewSize";
	/** X Position Attribute */
	public static final String XML_XPOS_ATTRIBUTE                                                        	= "XPos";
	/** Y Position Attribute */
	public static final String XML_YPOS_ATTRIBUTE                                                        	= "YPos";
	/** Width Attribute */
	public static final String XML_WIDTH_ATTRIBUTE                                                       	= "Width";
	/** Heigth Attribute */
	public static final String XML_HEIGHT_ATTRIBUTE                                                      	= "Height";
	/** Show info panel (Soon to become message panel) */
	public static final String XML_SHOW_INFO_PANEL                                                       	= "ShowInfoPanel";
	/** Frame State attribute */
	public static final String XML_FRAME_STATE															  	= "FrameState";  

    /**
    * Returns the Frame object. Typically used for parenting dialogs.
    *
    * @return Frame
    */
    public Frame getFrame();

    /**
    * Get the main application title. 
    *
    * @return String
    */
    public String getTitle();

	/**
	* Get the title of the type specified.
	*
	* @param type int
	*
	* @return String
	*/
	public String getTitle(int type);

    /**
    * Set the wait state for the frame.
    *
    * @param b boolean True means the frame is waiting. Will set cursor, spinner, etc.
    */
    public void setWaitState(boolean b);

    /**
	* Sets the dirty flag for the application (Should be app level?). 
	*  
    *
    * @param b boolean 
    */
    public void setDirtyFlag(boolean b);

    /**
    * Get the state of the global dirty flag.
    *
    * @return boolean 
    */
    public boolean getDirtyFlag();

    /**
    * Set the statusbar text and allows the user to specify whether that text should be "locked" on the status bar or 
    * allowed to timeout.
    *
    * @param text String
    * @param lock boolean
    */
    public void setStatus(String text, boolean lock);

    /**
    * Set the statusbar text. Automatically timesout and is cleared.
    *
    * @param text String
    */
    public void setStatus(String text);

    /** 
    * Set the "Lock" region of the status bar.
    *
    * @param lockit boolean
    * @param text String
    */
    public void setLockStatus(boolean lockit, String text);

	/**
	* Single entry point call for the data commit action. Now that the commit's being done on a worker thread,
	* it's necessary to fold the close functionality into the commit funciton via the closeIt param.
	* 
	* @param manager IFusionManager Specific manager to be committed. If null, commit them ALL!!!!
	* @param closeIt boolean Will call the closeApplication method if true.
	* @param silent boolean When true, the commit occurs without prompting the user. 
	*
	* @return boolean True if successful.
	*/
	public boolean commit(final IFusionManager manager, final boolean closeIt, final boolean silent);

	/**
	* Commit all the managers with out closing.
	* 
	* @return boolean True if successful.
	*/ 
	public boolean commit();

	/**
	* Commit all the managers and close the frame if closeIt is set.
	* 
	* @param closeIt boolean Will call the close method if true.
	*
	* @return boolean True if successful.
	*/
	public boolean commit(boolean closeIt);

    /**
    * Add an IApplicationFrame listener.
    * 
    * @param l IApplicationFrameListener The listener to add. 
    */
    public void addApplicationFrameListener(IApplicationFrameListener l);

    /**
    * Remove a Manager Listener
    *
    * @param l IIApplicationFrameListener The listener to remove. 
    */
    public void removeApplicationFrameListener(IApplicationFrameListener l);
}
