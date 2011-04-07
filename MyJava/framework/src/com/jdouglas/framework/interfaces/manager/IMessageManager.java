package com.jdouglas.framework.interfaces.manager;

import java.util.*;

import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.ui.widgets.TabPage;

/**
* IMessageManager interface.
*
* @author Jason Douglas 6//19/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IMessageManager    
    extends IFusionManager
{
    /** Manager name */
    public static final String MANAGER_NAME                                                             = "MessageManager";


	/** 
	* Get the tab for the given type. Aren't necessarily separate 
	* components. 
	* 
	* @param type MessageType
	* 
	* @return TabPage
	*/ 
	public TabPage getTabPage(MessageType type);

	/**
    * Get a message view associated with the given string. If the view hasn't been created, it will be.
	* 
	* @param context String
	* 
	* @return IMessageView
    */
	public IMessageView getMessageView(String context);

	/**
    * Create a message with the given parameters.
	* 
	* @param text String
	* @param type MessageType
	* @param sourceData HashMap<String,Object>
	* 
	* @return IFusionMessage
    */
	public IFusionMessage createMessage(String text, MessageType type, HashMap<String,Object> sourceData);

}
