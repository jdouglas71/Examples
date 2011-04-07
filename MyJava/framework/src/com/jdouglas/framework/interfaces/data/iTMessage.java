package com.jdouglas.framework.interfaces.data;

import java.util.*;

import com.jdouglas.framework.enums.data.*;

/**
* IFusionMessage. 
*
* @author Jason Douglas 1/19/10
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionMessage
    extends iTData
{
	/** Message Source */
	public static final String MESSAGE_SOURCE								= "messageSource";

	/**
    * Get the message type.
	* 
	* @return MessageType
    */
	public MessageType getMessageType();

	/**
    * Does the message have child messages?
	* 
	* @return boolean
    */
	public boolean hasChildren();

	/**
    * Get child messages.
	* 
	* @return ArrayList<IFusionMessage>
    */
	public ArrayList<IFusionMessage> getChildMessages();

	/**
    * Add a child message.
	* 
	* @param child IFusionMessage
    */
	public void addChildMessage(IFusionMessage child);

	/**
    * Remove child message.
	* 
	* @param child IFusionMessage
    */
	public void removeChildMessage(IFusionMessage child);
}
