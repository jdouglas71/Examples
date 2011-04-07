package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;
import java.text.*;

import com.jdouglas.framework.util.*;

/**
* Table cell renderer for the header that pretty much just adds a space in front of the 
* header title so it's prettier.
*
* @author Jason Douglas 3/18/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class LabelHeaderRenderer
        implements TableCellRenderer
{
	/** Module name */
    private static final String MODULE_NAME = "LabelHeaderRenderer.";

	/** The headers */
    private Map<Integer,JPanel> theHeaders;
	/** the labels */
    private Map<Integer,JLabel> theLabels;
	/** Use only the label, not the header */
    private boolean useLabelOnly = false;
	/** Format doubles flag */
	private boolean formatDoubles = false;
	/** Precision to use when formatting doubles */
	private int precision = 1;

    /**
    * Constructor
	*
	* @param _useLabelOnly boolean 
    */
    public LabelHeaderRenderer(boolean _useLabelOnly)
    {
        theHeaders = new HashMap<Integer,JPanel>();
        theLabels = new HashMap<Integer,JLabel>();
        useLabelOnly = _useLabelOnly;
    }

    /**
    * Constructor.
    */
    public LabelHeaderRenderer()
    {
        this(true);
    }

	/**
    * Set the precsion.
	* 
	* @param prec int
    */
	public void setPrecision(int prec)
	{
		precision = prec;
	}

	/**
    * Set the formatDoubles flag.
	* 
	* @param b boolean
    */
	public void setFormatDoublesFlag(boolean b)
	{
		formatDoubles = b;
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
        Component retval = null;

        JPanel header = theHeaders.get( new Integer(col) );
        JLabel label = theLabels.get( new Integer(col) ) ;

        if( header == null || label == null )
        {
            header = new JPanel();
            header.setBorder(UIManager.getBorder("TableHeader.cellBorder"));

            label = new JLabel( value.toString(), SwingConstants.CENTER );
            if( useLabelOnly )
            {
                label.setBorder(UIManager.getBorder("TableHeader.cellBorder"));
            }

			if( formatDoubles && value instanceof Double )
			{
				DecimalFormat df = FusionUtils.getDecimalFormat( precision );
				label.setText( df.format((Double)value) );
			}

            if( col > 1 ) 
            {
                //label.setForeground((Color.YELLOW).brighter());
				//label.setBackground((Color.BLUE).darker().darker() );
				//label.setOpaque( true );

                //JGD Not messing with the font right now, but this is pretty cool. 6/4/03
                Font font = label.getFont();
                //label.setFont( font.deriveFont(Font.ITALIC|Font.BOLD) );
                //label.setBackground( (Color.BLUE).darker().darker() );           
            }
            //checkBox.setForeground( table.getForeground() );
            //checkBox.setBackground( table.getBackground() );

            header.add( label );
            theHeaders.put( new Integer(col), header );
            theLabels.put( new Integer(col), label );
        }


        if( useLabelOnly )
        {
            retval = label;
        }
        else
        {
            retval = header;
        }

        return retval;
    }
}

