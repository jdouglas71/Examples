package com.jdouglas.framework.ui.dialogs;

import javax.swing.*;
import java.awt.*;
import java.net.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.listeners.*;


/**
* This is a dialog launcher frame that acts as a workaround for a Java bug. 
* The VM implements dialog's as windows, thus not using the DIALOG window class,
* and that means you can't set an icon for the dialog and you can't see the icon
* in the windows taskbar when the dialog is showing. Very bad for modal dialogs.<br><br>
*
* NOTE: Upon testing, it really seems like this is only an issue for modal dialogs 
* without parents, like the login dialog. Using this as the parent (and remembering 
* to dispose of it after the dialog is closed), gives you TWO icons in the Alt-Tab menu
* and ONE icon on the taskbar. Let's see if the bosses complain about that before trying
* to workaround that hole...
* 
* @author Jason Douglas 3/17/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class DialogFrame
    extends JFrame  
		implements IApplicationFrame
{
	/** Module name */
    private static final String MODULE_NAME = "DialogFrame.";

    /**
    * Constructor
	* 
	* @param title String 
    */
    public DialogFrame(String title)
    {
        String methodName = MODULE_NAME + "Constructor";
        //setBounds(-1000,-1000, 0, 0 );
        setSize(0,0);
        //setLocation( FusionUtils.getCenterPosition(getSize()) );
        setLocation( 10000, 10000 );

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}

		if( title == null )
		{
			if( FusionApplication.getApplicationFrame() != null )
			{
				setTitle( FusionApplication.getApplicationFrame().getTitle() );
			}
			else 
			{
				setTitle( "Fusion AE" );
			}
		}
		else
		{
			setTitle( title );
		}

        setVisible( true );
    }

	/**
    * Constructor
    */
	public DialogFrame()
	{
		this(null);
	}

	//****************************************************************************************//
	// IApplicationFrame impl
	// 

	/**
	* Returns the Frame object. Typically used for parenting dialogs.
	*
	* @return Frame
	*/
	public Frame getFrame()
	{
		return this;
	}

	/**
	* Get the main application title. 
	*
	* @return String
	*/
	public String getTitle()
	{
		return "";
	}

	/**
	* Get the title of the type specified.
	*
	* @param type int
	*
	* @return String
	*/
	public String getTitle(int type)
	{
		return "";
	}

	/**
	* Set the wait state for the frame.
	*
	* @param b boolean True means the frame is waiting. Will set cursor, spinner, etc.
	*/
	public void setWaitState(boolean b)
	{
	}

	/**
	* Sets the dirty flag for the application (Should be app level?). 
	*  
	*
	* @param b boolean 
	*/
	public void setDirtyFlag(boolean b)
	{
	}

	/**
	* Get the state of the global dirty flag.
	*
	* @return boolean 
	*/
	public boolean getDirtyFlag()
	{
		return false;
	}

	/**
	* Set the statusbar text and allows the user to specify whether that text should be "locked" on the status bar or 
	* allowed to timeout.
	*
	* @param text String
	* @param lock boolean
	*/
	public void setStatus(String text, boolean lock)
	{
	}

	/**
	* Set the statusbar text. Automatically timesout and is cleared.
	*
	* @param text String
	*/
	public void setStatus(String text)
	{
	}

	/** 
	* Set the "Lock" region of the status bar.
	*
	* @param lockit boolean
	* @param text String
	*/
	public void setLockStatus(boolean lockit, String text)
	{
	}

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
	public boolean commit(final IFusionManager manager, final boolean closeIt, final boolean silent)
	{
		return true;
	}

	/**
	* Commit all the managers with out closing.
	* 
	* @return boolean True if successful.
	*/ 
	public boolean commit()
	{
		return true;
	}

	/**
	* Commit all the managers and close the frame if closeIt is set.
	* 
	* @param closeIt boolean Will call the close method if true.
	*
	* @return boolean True if successful.
	*/
	public boolean commit(boolean closeIt)
	{
		return true;
	}

	/**
	* Add an IApplicationFrame listener.
	* 
	* @param l IApplicationFrameListener The listener to add. 
	*/
	public void addApplicationFrameListener(IApplicationFrameListener l)
	{
	}

	/**
	* Remove a Manager Listener
	*
	* @param l IIApplicationFrameListener The listener to remove. 
	*/
	public void removeApplicationFrameListener(IApplicationFrameListener l)
	{
	}

	// IApplicationFrame impl ends.
}
