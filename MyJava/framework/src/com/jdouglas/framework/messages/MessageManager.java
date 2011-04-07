package com.jdouglas.framework.messages;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;

import javax.swing.*;
import javax.swing.event.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.enums.view.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.ui.widgets.InfoTab;
import com.jdouglas.framework.ui.widgets.TabPage;
import com.jdouglas.framework.util.*;

/**
* MessageManager. The manager interface for the internal  
* framework messaging system. This is a work in progress, but
* the goal is to route all error and informational messages away
* from message boxes and into a message pane, where they can be
* stored, viewed and saved.
* 
* @author Jason Douglas 6/19/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class MessageManager
	extends FusionManager
		implements IMessageManager
{
	/** Module name */
	private static final String MODULE_NAME																	= "MessageManager.";

	/** Error Tab */
	private ErrorTab errorTab;
	/** info tab */
	private InfoTab infoTab;
	/** message tab */
	private MessageTab messageTab;

	/** THe message View Map */
	private HashMap<String,IMessageView> theMessageViewMap = new HashMap<String,IMessageView>();

	/**
	* Constructor/
    */
	public MessageManager()
	{
		super(MANAGER_NAME);
		init();
	}

	/** 
	* Create the tabs and any other components.  
    */
	private void init()
	{
		String methodName = MODULE_NAME + "init()";

		try
		{
			errorTab = new ErrorTab();
			infoTab = new InfoTab();
			messageTab = new MessageTab();
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}


	//*****************************************************************************************************************************//
	// IFusionManager impl
	// 

	/**
	* A name string associated with the manager. Used to hash the manager. 
	*
	* @return String The manager name. 
	*/
	public String getManagerName()
	{
		return MANAGER_NAME;
	}

	/**
	* Get any menuitems associated with the standard frame menus.
	* 
	* @param menuID MenuID
	* 
	* @return ArrayList<JMenuItem>
	*/
	public ArrayList<JMenuItem> getMenuItems(MenuID menuID)
	{
		//JGD NOTE: TEMPORARY! Just here while I update all the manager classes.
		String methodName = MODULE_NAME + "getMenuItems(int)";
		ArrayList<JMenuItem> retval = new ArrayList<JMenuItem>();

		return retval;
	}


	//*****************************************************************************************************************************//
	// MessageManager impl
	// 
	/** 
	* Get the tab for the given type. Aren't necessarily separate 
	* components. 
	* 
	* @param type MessageType
	* 
	* @return TabPage
	*/ 
	public TabPage getTabPage(MessageType type)
	{
		String methodName = MODULE_NAME + "getTabPage(MessageType)";
		TabPage retval = null;

		try
		{
			switch( type )
			{
				case INFO:
					retval = messageTab;
					break;
				case WARNING:
				case ERROR:
				default:                                                     
					retval = errorTab;
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Post a message.
	* 
	* @param message String
	* @param type MessageType
	*/
	//public void postMessage(String message, MessageType type)
	//{
	//	String methodName = MODULE_NAME + "postMessage(String,MessageType)";


	//	switch( type )
	//	{
	//		case INFO:
	//			messageTab.setInfoText( message );
	//			break;
	//		case WARNING:
	//		case ERROR:
	//		default:
	//			errorTab.setInfoText( message );
	//	}
	//}

	/**
	* Get a message view associated with the given string. If the view hasn't been created, it will be.
	* 
	* @param context String
	* 
	* @return IMessageView
	*/
	public IMessageView getMessageView(String context)
	{
		String methodName = MODULE_NAME + "getMessageView(String)";
		IMessageView retval = null;

		try
		{
			retval = theMessageViewMap.get( context );
			if( retval == null )
			{
				retval = new MessageView(this);
				theMessageViewMap.put( context, retval );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Create a message with the given parameters.
	* 
	* @param text String
	* @param type MessageType
	* @param sourceData HashMap<String,Object>
	* 
	* @return IFusionMessage
	*/
	public IFusionMessage createMessage(String text, MessageType type, HashMap<String,Object> sourceData)
	{
		//JGD TODO Tracking?????
		return new FusionMessage( text, type, sourceData );
	}

	// IMessageManager impl ends
	// IFusionManager impl ends
}


