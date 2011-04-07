package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.util.models.*;

/**
* Table cell renderer for the header that pretty much just adds a space in front of the 
* header title so it's prettier.
*
* @author Jason Douglas 3/18/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class SortLabelHeaderRenderer
        implements TableCellRenderer
{
    //Const
    private static final String MODULE_NAME = "SortLabelHeaderRenderer.";

    //Data
    private Map<Integer,JLabel> theLabels = new HashMap<Integer,JLabel>();
    private SortTableModel theModel;
    private Icon upIcon, downIcon;

    /**
    * Ctor
    */
    public SortLabelHeaderRenderer(SortTableModel model, Icon _upIcon, Icon _downIcon)
    {
        theModel = model;
        upIcon = _upIcon;
        downIcon = _downIcon;
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

        JLabel label = theLabels.get( new Integer(col) ) ;

        if( label == null )
        {
            label = new JLabel( value.toString(), SwingConstants.CENTER );
            label.setBorder(UIManager.getBorder("TableHeader.cellBorder"));
            label.setHorizontalTextPosition( SwingConstants.LEFT );
            theLabels.put( new Integer(col), label );
        }

        //Logger.log( methodName + " theModel.getSortedColumn() = " + theModel.getSortedColumn() );
        //Logger.log( methodName + " col = " + col );

        if( theModel.getSortedColumn() == col )
        {
            if( theModel.getSortDirection() == SortTableModel.SORT_DECENDING )
            {
                label.setIcon( downIcon );
            }
            else 
            {
                label.setIcon( upIcon );
            }
        }
        else
        {
            label.setIcon( null );
        }

        retval = label;

        return retval;
    }
}

