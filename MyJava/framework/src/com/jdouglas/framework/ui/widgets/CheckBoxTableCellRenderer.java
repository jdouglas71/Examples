package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;

/**
* Table cell renderer that uses checkboxes. It saves the created checkboxes in a map for later access.
* I have to create my own rather than rely on the default tablecellrenderer (which automatically uses 
* a checkbox to display a boolean value) because the default renderer only uses a single JCheckbox object
* to create any and all checkboxes. This precludes attaching a listener to a specific checkbox to catch itemState
* changes (or at least makes it much too convoluted for my tastes). Brute force! That's what I like! 
*
* @author Jason Douglas 3/18/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class CheckBoxTableCellRenderer
        implements TableCellRenderer
{
    //Const
    private static final String MODULE_NAME = "CheckBoxTableCellRenderer.";

    //Data
    private Map<Integer,JCheckBox> theCheckBoxes;

    //Methods
    /**
    * Ctor
    */
    public CheckBoxTableCellRenderer()
    {
        theCheckBoxes = new HashMap<Integer,JCheckBox>();
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
        String methodName = MODULE_NAME + "getTableCellRendererComponent(JTable,Object,boolean,boolean,int,int)";
        Component retval = null;

        JCheckBox checkBox = theCheckBoxes.get( new Integer(row) );

        if( checkBox == null )
        {
            checkBox = new JCheckBox();
            checkBox.setHorizontalAlignment( JLabel.CENTER );
            checkBox.setForeground( table.getForeground() );
            checkBox.setBackground( table.getBackground() );
            theCheckBoxes.put( new Integer(row), checkBox );
        }

        TableModel theModel = table.getModel();
        Object obj = theModel.getValueAt(row,col);
        if(obj instanceof Boolean)
        {
            boolean b = ((Boolean)obj).booleanValue();
            checkBox.setSelected( b );
        }

		if( table.isEnabled() )
		{
			checkBox.setEnabled( theModel.isCellEditable(row,col) );
		}
		else
		{ 
			checkBox.setEnabled( false );
		}

        retval = checkBox;

        return retval;
    }
}

