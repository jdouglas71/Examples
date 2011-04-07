package com.jdouglas.framework.ui.widgets;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

import com.jdouglas.framework.util.*;

/**
* Generic border class that displays a component and ensures that it gets MouseEvents. Borders are not components, so you
* can't just add a component to it and have it work correctly. The border must paint the component directly and pass along
* events from the border container. Currently only passing along mouse events. The class is flexible in that it works with
* any component and border combonation.
* 
* @author Jason Douglas 9/21/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ComponentBorder 
    extends AbstractBorder
		implements MouseListener
{
	/** Module name */
    private static final String MODULE_NAME = "ComponentBorder.";
	/** Component offset */
	private static final int OFFSET = 5;

	/** the component */
	private Component theComponent;
	/** Base Border */
	private Border theBorder;
	/** Component rectangle */
	private Rectangle componentRect;
	/** Border container */
	private Container theContainer;

    /**
    * Constructor.
	* 
	* @param border Border
	* @param container Container (e.g. the panel)
	* @param comp Component (e.g. JCheckBox)
    */
    public ComponentBorder(Border border, Container container, Component comp)
    {
		theBorder = border;
		theContainer = container;
		theComponent = comp;
		theContainer.addMouseListener( this );
    }

    /**
    * Paint the border
    */
    public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) 
    {
        String methodName = MODULE_NAME + "paintBorder(Component,Graphics,int,int,int,int)";

		Insets borderInsets = theBorder.getBorderInsets( c );
		Insets insets = getBorderInsets(c);
		int temp = (insets.top-borderInsets.top)/2;

		theBorder.paintBorder( c, g, x, y+temp, width, height-temp );

		Dimension theComponentSize = theComponent.getPreferredSize();
		componentRect = new Rectangle( OFFSET, 0, theComponentSize.width, theComponentSize.height );
		//Logger.log( methodName + " Painting component.", Logger.DEBUG );
		SwingUtilities.paintComponent( g, theComponent, (Container)c, componentRect );
    }

	/**
    * Calculate the insets.
	* 
	* @param comp Component
	* 
	* @return Insets
    */
	public Insets getBorderInsets(Component comp)
	{
		String methodName = MODULE_NAME + "getBorderInsets(Component)";
		Insets retval = theBorder.getBorderInsets( comp );
		retval.top = Math.max( retval.top, theComponent.getPreferredSize().height );
		return retval;
	}

	/** 
	* Always true.
	* 
	* @return boolean
	*/
    public boolean isBorderOpaque()
	{
		return true;
	}

	/** 
	* Pass along the mouse event. 
	* 
	* @param me MouseEvent
	*/
	private void dispatchEvent(MouseEvent me)
	{ 
		String methodName = MODULE_NAME + "dispatchEvent(MouseEvent)";

		if( componentRect!=null && componentRect.contains(me.getX(), me.getY()))
		{ 
			//Logger.log( methodName + " Passing along the mouseEvent.", Logger.DEBUG );
			Point pt = me.getPoint();
			pt.translate(-OFFSET, 0); 

			theComponent.setBounds(componentRect);

			MouseEvent newEvt = new MouseEvent(theComponent, me.getID(), me.getWhen(), me.getModifiers(), pt.x, pt.y, me.getClickCount(), me.isPopupTrigger(), me.getButton());
			theComponent.dispatchEvent( newEvt ); 

			if(!theComponent.isValid()) 
			{
			   	theContainer.repaint(); 
			}
		} 
    } 

	//*****************************************************************************************//
	// MouseListener impl
	// 
	/**
	* Invoked when the mouse button has been clicked (pressed
	* and released) on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseClicked(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseClicked(MouseEvent)";

		//Logger.log( methodName, Logger.DEBUG );

		dispatchEvent( evt );
	}

	/**
	* Invoked when a mouse button has been pressed on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mousePressed(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mousePressed(MouseEvent)";

		//Logger.log( methodName, Logger.DEBUG );

		dispatchEvent( evt );
	}

	/**
	* Invoked when a mouse button has been released on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseReleased(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseReleased(MouseEvent)";

		//Logger.log( methodName, Logger.DEBUG );

		dispatchEvent( evt );
	}

	/**
	* Invoked when the mouse enters a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseEntered(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseEntered(MouseEvent)";

		//Logger.log( methodName, Logger.DEBUG );

		dispatchEvent( evt );
	}

	/**
	* Invoked when the mouse exits a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseExited(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseExited(MouseEvent)";

		//Logger.log( methodName, Logger.DEBUG );

		dispatchEvent( evt );
	}
	// MouseListener impl ends
}
