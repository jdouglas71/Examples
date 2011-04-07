package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.props.*;


/**
* Table cell renderer for the header that allows multiple lines.
*
* @author Jason Douglas 12/16/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class MultilineHeaderRenderer
	extends JPanel
        implements TableCellRenderer,MouseListener
{
	/** Module name */
    private static final String MODULE_NAME = "MultilineHeaderRenderer.";
	/** Option extra panel of components */
	private JPanel thePanel;
	/** First time thru flag */
	private boolean firstTimeThru = true;

	/**
    * Constructor. 
	* 
	* @param panel JPanel
    */
	public MultilineHeaderRenderer(JPanel panel)
	{
		thePanel = panel;
		addMouseListener( this );
	}

	/**
    * Default Constructor.
    */
	public MultilineHeaderRenderer()
	{
		this(null);
	}

    /**
    *  Returns the component used for drawing the cell.  This method is
    *  used to configure the renderer appropriately before drawing.
    *
    * @param   table       the <code>JTable</code> that is asking the
    *              renderer to draw; can be <code>null</code>
    * @param   value       the value of the cell to be rendered.  It is
    *              up to the specific renderer to interpret
    *              and draw the value.  For example, if
    *              <code>value</code>
    *              is the string "true", it could be rendered as a
    *              string or it could be rendered as a check
    *              box that is checked.  <code>null</code> is a
    *              valid value
    * @param   isSelected  true if the cell is to be rendered with the
    *              selection highlighted; otherwise false
    * @param   hasFocus    if true, render cell appropriately.  For
    *              example, put a special border on the cell, if
    *              the cell can be edited, render in the color used
    *              to indicate editing
    * @param   row         the row index of the cell being drawn.  When
    *              drawing the header, the value of
    *              <code>row</code> is -1
    * @param   col          the column index of the cell being drawn
    */
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int col) 
    {
        String methodName = MODULE_NAME + "getTableCellRendererComponent(JTable,Object,boolean,boolean,int,int)";

		removeAll();
		String[] headerStrs = ((String)value).split("\n");
		int numRows = headerStrs.length;
		if( thePanel != null )
		{
			numRows++;
		}
		setLayout( new GridLayout(numRows, 1) );
		for(String s : headerStrs )
		{
			JLabel label = new JLabel( s, JLabel.LEFT );
            LookAndFeel.installColorsAndFont(label, "TableHeader.background", "TableHeader.foreground", "TableHeader.font");
			add(label);
		}
		if( thePanel != null)
		{
			add(thePanel);
		}
        LookAndFeel.installBorder(this, "TableHeader.cellBorder");

		//Add mouse listener for tableheader
		if( firstTimeThru )
		{
			//table.getTableHeader().addMouseListener( this );
			firstTimeThru = false;
		}

        return this;
    }

	//***********************************************************************************************************//
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
		//Logger.log( methodName + " evt: "+ evt, Logger.DEBUG );

		Object obj = evt.getSource();
		if( obj instanceof JTableHeader )
		{
			JTableHeader tableHeader = (JTableHeader)obj;
			JTable theTable = tableHeader.getTable();
			TableColumnModel tcm = theTable.getColumnModel();
			int col = tcm.getColumnIndexAtX(evt.getX());
		}
	}

	/**
	* Invoked when a mouse button has been pressed on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mousePressed(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mousePressed(MouseEvent)";
		//Logger.log( methodName + " evt: "+ evt, Logger.DEBUG );

		try
		{
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Invoked when a mouse button has been released on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseReleased(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseReleased(MouseEvent)";
		//Logger.log( methodName + " evt: "+ evt, Logger.DEBUG );

		try
		{
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Invoked when the mouse enters a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseEntered(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseEntered(MouseEvent)";
		//Logger.log( methodName + " evt: "+ evt, Logger.DEBUG );
	}

	/**
	* Invoked when the mouse exits a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseExited(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseExited(MouseEvent)";
		//Logger.log( methodName + " evt: "+ evt, Logger.DEBUG );
	}

	// MouseListener impl ends

}

