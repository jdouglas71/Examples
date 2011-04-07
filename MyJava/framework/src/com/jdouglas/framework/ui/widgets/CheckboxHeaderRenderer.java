package com.jdouglas.framework.ui.widgets;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;

import com.jdouglas.framework.util.*;

/**
* CheckboxHeaderRenderer. Adds a "Select All/None" checkbox to the table column header. 
* 
* @author Jason Douglas 3/18/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class CheckboxHeaderRenderer
        implements TableCellRenderer,MouseListener 
{
	/** Module name */
    private static final String MODULE_NAME = "CheckboxHeaderRenderer.";

	/** The headers */
    private Map<Integer,JPanel> theHeaderPanels;
	/** the labels */
    private Map<Integer,JLabel> theLabels;
	/** The checkboxes */
	private Map<Integer,JCheckBox> theCheckers;
	/** Layout constriants */
	private GridBagConstraints gbc = new GridBagConstraints();
	/** String to differientiate objects of this type. Used only for debugging */
	private String myName; 
	/** First time thru sentry */
	private boolean firstTimeThru = true;

    /**
    * Constructor.
    */
    public CheckboxHeaderRenderer()
    {
        theHeaderPanels = new HashMap<Integer,JPanel>();
        theLabels = new HashMap<Integer,JLabel>();
		theCheckers = new HashMap<Integer,JCheckBox>();

		gbc.anchor = GridBagConstraints.CENTER;
		gbc.gridwidth = GridBagConstraints.REMAINDER;

		myName = MODULE_NAME + FusionUtils.generateHashKey();
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
    public Component getTableCellRendererComponent(JTable table, Object value, 
                                                   boolean isSelected, boolean hasFocus, 
                                                   int row, int col) 
    {
        String methodName = MODULE_NAME + "getTableCellRendererComponent(JTable,Object,boolean,boolean,int,int) " + myName;
        Component retval = null;

		//Logger.log( methodName + " value: " + value + " row: " + row + " col: " + col, Logger.DEBUG );

        JPanel headerPanel = theHeaderPanels.get( new Integer(col) );
        JLabel label = theLabels.get( new Integer(col) ) ;
		JCheckBox cb = theCheckers.get( new Integer(col) );

		//We're missing the controls for this column, so create them 
        if( headerPanel == null || label == null || cb == null )
        {
			//Logger.log( methodName + " Creating new controls for col: " + col, Logger.DEBUG );
			//Create the controls 
            headerPanel = new JPanel();
            headerPanel.setBorder(UIManager.getBorder("TableHeader.cellBorder"));
			headerPanel.setLayout( new GridBagLayout() );

            label = new JLabel( value.toString(), SwingConstants.CENTER );
			cb = new JCheckBox( "Select All" );

			//Layout the controls 
            headerPanel.add( label, gbc );
			headerPanel.add( cb, gbc );

			//Store the controls 
            theHeaderPanels.put( new Integer(col), headerPanel );
            theLabels.put( new Integer(col), label );
			theCheckers.put( new Integer(col), cb );

			//Add mouse listener for tableheader
			if( firstTimeThru )
			{
				table.getTableHeader().addMouseListener( this );
				firstTimeThru = false;
			}
        }

		cb.setEnabled( table.isEnabled() );

        retval = headerPanel;

        return retval;
    }

	//**********************************************************************************************//
	// MouseListener impl
	// 
	/**
	* Invoked when the mouse button has been clicked (pressed
	* and released) on a component.
	* 
	* @param e MouseEvent
	*/
	public void mouseClicked(MouseEvent e)
	{
		String methodName = MODULE_NAME + "mouseClicked(MouseEvent) " + myName;
		Logger.log( methodName + " e: " + e, Logger.DEBUG);

		try
		{
			Object obj = e.getSource();
			if( obj instanceof JTableHeader )
			{
				JTableHeader tableHeader = (JTableHeader)obj;
				JTable theTable = tableHeader.getTable();
				TableColumnModel tcm = theTable.getColumnModel();
				int col = tcm.getColumnIndexAtX(e.getX());
				JCheckBox cb = theCheckers.get( new Integer(col) );
				if( cb != null )
				{
					if( cb.isEnabled() )
					{
						cb.setSelected( !cb.isSelected() );
						tableHeader.repaint();
					}
				}
			}
		}
		catch( Exception x )
		{
			FusionUtils.logError( methodName, "Failed", x );
		}
	}

	/**
	* Invoked when a mouse button has been pressed on a component.
	* 
	* @param e MouseEvent
	*/
	public void mousePressed(MouseEvent e)
	{
		String methodName = MODULE_NAME + "mousePressed(MouseEvent)";
	}

	/**
	* Invoked when a mouse button has been released on a component.
	* 
	* @param e MouseEvent
	*/
	public void mouseReleased(MouseEvent e)
	{
		String methodName = MODULE_NAME + "mouseReleased(MouseEvent)";
	}

	/**
	* Invoked when the mouse enters a component.
	* 
	* @param e MouseEvent
	*/
	public void mouseEntered(MouseEvent e)
	{
		String methodName = MODULE_NAME + "mouseEntered(MouseEvent)";
	}

	/**
	* Invoked when the mouse exits a component.
	* 
	* @param e MouseEvent
	*/
	public void mouseExited(MouseEvent e)
	{
		String methodName = MODULE_NAME + "mouseExited(MouseEvent)";
	}

	// MouseListener impl ends 
}

