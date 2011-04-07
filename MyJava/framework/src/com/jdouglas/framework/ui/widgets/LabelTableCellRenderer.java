package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;
import java.awt.*;
import java.util.*;
import java.text.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* Table cell renderer that uses JLabel
*
* @author Jason Douglas 3/18/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class LabelTableCellRenderer
        implements TableCellRenderer
{
    /** Module name */
    private static final String MODULE_NAME = "LabelTableCellRenderer.";

    /** the Labels */
    private Map<Integer,JLabel> theLabels;
    /** Foreground Color */
    private Color fgColor;
    /** Background Color */
    private Color bgColor;
    /** Border used (if non-null) */
    private Border theBorder;
	/** Use readonly colors */
	private boolean useReadOnlyColors = true;
	/** Label text position */
	private int labelTextPosition = SwingConstants.LEFT;
	/** Format doubles flag */
	private boolean formatDoubles = false;
	/** Precision to use when formatting doubles */
	private int precision = 1;
	/** Row Col pairs of "Bad" cells */
	private ArrayList<Point> theBadCells = new ArrayList<Point>();
	/** Show dirty icon */
	private boolean showDirtyIcon = false;
	/** Dirty Icon */
	private Icon dirtyIcon;
	/** Resources */
	private FrameworkResources theResources;

    /**
	* Constructor 
	*  
	* @param useROColors boolean
	* @param textPos int
	* @param showDirty boolean
    */
    public LabelTableCellRenderer(boolean useROColors, int textPos, boolean showDirty)
    {
        theLabels = new HashMap<Integer,JLabel>();
        bgColor = Color.white;
		useReadOnlyColors = useROColors;
		labelTextPosition = textPos;
		theResources = (FrameworkResources)FusionApplication.getResources(IFrameworkProperties.class);
		dirtyIcon = theResources.getResourceIcon( IFrameworkProperties.DIRTY_ICON );
		showDirtyIcon = showDirty;
    }

	/**
	* Constructor 
	*  
	* @param useROColors boolean
	*/
	public LabelTableCellRenderer(boolean useROColors)
	{
		this( useROColors, SwingConstants.LEFT, false );
	}

	/**
	* Constructor 
	*/
	public LabelTableCellRenderer()
	{
		this( true, SwingConstants.LEFT, false );
	}

    /**
    * Set the foreground color used for the label.
    *
    * @param fgc Color
    */
    public void setForeground(Color fgc)
    {
        fgColor = fgc;
    }

    /**
    * Set the background color used for the label.
    *
    * @param bgc Color
    */
    public void setBackground(Color bgc)
    {
        bgColor = bgc;
    }

    /**
    * Set the border used. 
    *
    * @param b Border
    */
    public void setBorder(Border b)
    {
        theBorder = b;
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
    * Add "Bad" cell.
	* 
	* @param row int
	* @param col int
    */
	public void addBadCell(int row, int col)
	{
		Point p = new Point(row, col);
		if( !theBadCells.contains(p) )
		{
			theBadCells.add( p );
		}
	}

	/**
    * Remove "Bad" cell.
	* 
	* @param row int
	* @param col int
    */
	public void removeBadCell(int row, int col)
	{
		theBadCells.remove( new Point(row,col) );
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

		JLabel label = theLabels.get( new Integer(row) );

        try
        {
			TableModel theModel = table.getModel();
			Object obj = theModel.getValueAt(row,col);

            if( label == null )
            {
                label = new JLabel();
				label.setHorizontalAlignment( labelTextPosition );

                theLabels.put( new Integer(row), label );
            }

            if( isSelected )
            {
                label.setForeground( table.getSelectionForeground() );
                label.setBackground( table.getSelectionBackground() );
            }
            else
            {
				if( theModel.isCellEditable(row,col) || !useReadOnlyColors )
				{
					//Set foreground color
					if( fgColor == null )
					{
						label.setForeground( table.getForeground() );
					}
					else
					{
						label.setForeground( fgColor );
					}

					//Set background color
					if( bgColor == null )
					{
						label.setBackground( table.getBackground() );
					}
					else
					{
						label.setOpaque( true );
						label.setBackground( bgColor );
					}
				}
				else
				{
					label.setBackground( Color.lightGray );
					label.setOpaque( true );
					label.setForeground( Color.black );
				}
            }

            //Logger.log( methodName + " obj class: " + obj.getClass().getName(), Logger.DEBUG );
            //Logger.log( "obj toString: " + obj.toString(), Logger.DEBUG );
            if( obj instanceof String )
            {
                //JGD Add some padding in the front of the string.
                label.setText(" " + (String)obj);
                label.setToolTipText( (String)obj );
            }
            else if( obj instanceof iTData )
            {
                iTData data = (iTData)obj;
                ImageIcon icon = (ImageIcon)data.getProperty( iTData.ICON );
                if( icon != null )
                {
					if( showDirtyIcon && data.isDirty() )
					{
						label.setIcon( new CompoundIcon( icon, dirtyIcon ) );
					}
					else
					{
						label.setIcon( icon );
					}
                }
				else if( showDirtyIcon && data.isDirty() ) 
				{
					label.setIcon( dirtyIcon );
				}
				else
				{
					label.setIcon(null);
				}
                // Add some padding 
				//JGD: Why TYPE_NAME???? Why not DISPLAY_NAME?
                label.setText( " " + data.getDisplayName() );
                label.setToolTipText( data.getDisplayName() );
            }
			else if( obj instanceof Double && formatDoubles )
			{
				DecimalFormat df = FusionUtils.getDecimalFormat( precision );
				label.setText( " " + df.format((Double)obj) );
			}
			else if( obj != null )
			{
				label.setText( " " + obj.toString() );
				label.setToolTipText( obj.toString() );
			}
			else
			{
				label.setText( "" );
				label.setToolTipText( "null" );
			}


			//Border 
			if( theBadCells.contains(new Point(row,col)) )
			{
				label.setBorder( new LineBorder(Color.RED) );
			}
			else if( theBorder != null )
			{
				label.setBorder( theBorder );
			}
			else
			{
				label.setBorder( null );
			}

        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        label.setEnabled( table.isEnabled() );

        retval = label;
        
        return retval;
    }
}

