package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import java.beans.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.data.*;

/**
* IMessageView. Interface for the message view component.
*
* @author Jason Douglas 1/19/10
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IMessageView
	extends IFusionView
{
	/**
    * Add a message.
	* 
	* @param message IFusionMessage
    */
	public void addMessage(IFusionMessage message);

	/**
	* Remove a message.
	* 
	* @param message IFusionMessage
	*/
	public void removeMessage(IFusionMessage message);

	/**
    * Clear all messages.
    */
	public void clearMessages();

	/**
    * Returns true if the message view contains an error.
	* 
	* @return boolean
    */
	public boolean hasErrors();
}

