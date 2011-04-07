package com.jdouglas.framework.ui.widgets;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.data.*;

/**
* TableScrollPane. An Information Panel. Can be used as a straight component or via the IEditorPanel interface. 
*
* @author Jason Douglas 5/18/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class TableScrollPane
    extends JScrollPane
        implements ComponentListener
{
	/** Module Name */
    private static final String MODULE_NAME                 = "TableScrollPane.";

	/**
    * Constructor. 
	* 
	* @param view The component to display in the scrollpane's viewport.
    */
	public TableScrollPane(Component view)
	{
        super(view, VERTICAL_SCROLLBAR_AS_NEEDED, HORIZONTAL_SCROLLBAR_AS_NEEDED);

		addComponentListener( this );
	}

	//************************************************************************************************************//
	// ComponentListener impl
	// 

	/**
	* Invoked when the component's size changes.
	* 
	* @param evt ComponentEvent
	*/
	public void componentResized(ComponentEvent evt)
	{
		String methodName = MODULE_NAME + "componentResized(ComponentEvent)";

		try
		{
			if( evt.getSource() instanceof JScrollPane )
			{
				JScrollPane scroller = (JScrollPane)evt.getSource();
				if( scroller.getViewport().getView() instanceof JTable )
				{
					JTable table = (JTable)scroller.getViewport().getView();
					if( table.getPreferredSize().width <= scroller.getViewport().getExtentSize().width )
					{
						table.setAutoResizeMode( JTable.AUTO_RESIZE_ALL_COLUMNS );
					}
					else
					{
						table.setAutoResizeMode( JTable.AUTO_RESIZE_OFF );
					}
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Invoked when the component's position changes.
	* 
	* @param evt ComponentEvent
	*/    
	public void componentMoved(ComponentEvent evt)
	{
	}

	/**
	* Invoked when the component has been made visible.
	* 
	* @param evt ComponentEvent
	*/
	public void componentShown(ComponentEvent evt)
	{
	}

	/**
	* Invoked when the component has been made invisible.
	* 
	* @param evt ComponentEvent
	*/
	public void componentHidden(ComponentEvent evt)
	{
	}

	// ComponentListener impl ends
}
