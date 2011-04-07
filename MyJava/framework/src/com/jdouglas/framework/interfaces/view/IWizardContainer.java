package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* IWizardContainer. View container interface for wizards. The impls are most likely limited to a JDialog and a JFrame (for use with VB).
*
* @author Jason Douglas 4/2/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IWizardContainer
	extends KeyListener
{
	/**
	* Show and return the close state
	*
	* @return int 
	*/
	public int showDialog();

	/**
	* The return value of showDialog is the closeState but here's another way to get it. 
	*
	* @return int 
	*/
	public int getCloseState();

	/**
	* Send a message to the MessageView
	*
	* @param message IFusionMessage
	*/
	public void setMessage(IFusionMessage message);

	/** 
	* Remove a message from the message view.
	* 
	* @param message IFusionMessage
	*/
	public void removeMessage(IFusionMessage message);

	/**
	* Set the message pane text.
	*
	* @param text String
	* @param type MessageType The message type.
	*/
	public void setMessageText(String text, MessageType type);

	/**
    * Clear the message area. 
    */
	public void clearMessages();

	/**
    * Get the Window associated with the container. (For parenting)
	* 
	* @return Window
    */
	public Window getWindow();

	/**
	* Set parent HWND
	* 
	* @param parent_HWND int
	*/
	public void setParentHWND(int parent_HWND);

	/**
    * Add wizard container listener.
	* 
	* @param l IWizardContainerListener 
    */
	public void addWizardContainerListener(IWizardContainerListener l);

	/**
	* Remove wizard container listener.
	* 
	* @param l IWizardContainerListener 
	*/
	public void removeWizardContainerListener(IWizardContainerListener l);

}
