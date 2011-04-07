package com.jdouglas.framework.util.models;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

import com.jdouglas.framework.util.*;

/**
* SortTableModel.<br><br>
* A sorting table model based on the code in example 19-21 of Graphic Java Vol 3 (ISBN 0-13-079667-0).
* I like this because it allows us to sort, without actually changing the underlying datamodel. We're 
* cheating by adding another layer over the table model and just "sorting" the row indices based on whatever
* column we care about. Then we can use the sorted indices to override the model's getValueAt and setValueAt
* methods and never change the underlying model. We're currently sorting on the toString return values for the
* model Objects. 
*
* @author Jason Douglas 5/26/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class SortTableModel
        implements TableModel, TableModelListener
{
    //Const 
    private static final String MODULE_NAME             = "SortTableModel.";

    /** Sort Decending flag */
    public static final int SORT_DECENDING              = -1;
    /** Sort ascending flag */
    public static final int SORT_ASCENDING              = 1;

    //Data
    private TableModel theRealModel;
    private int[] sortedIndices;
    private int sortDirection = SORT_DECENDING;
    private int sortColumn = -1;

    /**
    * Ctor
    * 
    * @param model TableModel
    */
    public SortTableModel(TableModel model)
    {
        if( model == null )
        {
            throw new IllegalArgumentException("The model must be non-null");
        }

        theRealModel = model;
        theRealModel.addTableModelListener( this );
        refresh();
    }

    /**
    * Return the sort direction.
    *
    * @return int 
    */
    public int getSortDirection()
    {
        return sortDirection;
    }

    /**
    * Return the last col sorted (-1 if unsorted)
    *
    * @return int 
    */
    public int getSortedColumn()
    {
        return sortColumn;
    }

    /**
    * Refresh the sorted indices. 
    */
    private void refresh()
    {
        sortedIndices = new int[getRowCount()];

        for(int i=0; i<sortedIndices.length; i++)
        {
            sortedIndices[i] = i;
        }
        
        sortDirection = SORT_DECENDING;
        sortColumn = -1;
    }

    /**
    * Sort on the string value of the stored object.
    *
    * @param col int
    */
    public void sortTable(int col)
    {
        String methodName = MODULE_NAME + "sortTable(int)";

        Logger.log( methodName + " sorting column: " + col, Logger.CONFIG );

        try
        {
            //If the col is new, the sort is new and we start with decending.
            if( col != sortColumn )
            {
                sortDirection = SORT_DECENDING;
            }
            else
            {
                //Toggle the sort direction.
                sortDirection = ( (sortDirection == SORT_ASCENDING) ? SORT_DECENDING : SORT_ASCENDING );
            }

            Logger.log( methodName + " direction: " + sortDirection, Logger.FINE );

            int rowCount = getRowCount();

            for(int i=0; i<rowCount; i++)
            {
                for(int j=i+1; j < rowCount; j++)
                {
                    if( sortDirection == SORT_DECENDING )
                    {
                        if( compare(sortedIndices[i], sortedIndices[j], col) < 0 )
                        {
                            swap(i,j);
                        }
                    }
                    if( sortDirection == SORT_ASCENDING )
                    {
                        if( compare(sortedIndices[i], sortedIndices[j], col) > 0 )
                        {
                            swap(i,j);
                        }
                    }
                }
            }

            //Save off the sort column
            sortColumn = col;
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Resort the table without changing the col or direction.
    */
    public void resortTable()
    {
        String methodName = MODULE_NAME + "resortTable()";

        if( sortColumn < 0 )
        {
            return;
        }

        try
        {
            Logger.log( methodName + " sorting column: " + sortColumn, Logger.CONFIG );
            Logger.log( methodName + " direction: " + sortDirection, Logger.CONFIG );

            int rowCount = getRowCount();

            for(int i=0; i<rowCount; i++)
            {
                for(int j=i+1; j < rowCount; j++)
                {
                    if( sortDirection == SORT_DECENDING )
                    {
                        if( compare(sortedIndices[i], sortedIndices[j], sortColumn) < 0 )
                        {
                            swap(i,j);
                        }
                    }
                    if( sortDirection == SORT_ASCENDING )
                    {
                        if( compare(sortedIndices[i], sortedIndices[j], sortColumn) > 0 )
                        {
                            swap(i,j);
                        }
                    }
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Swap the values in the sortedIndices array.
    *
    * @param i int
    * @param j int 
    */
    private void swap(int i, int j)
    {
        int tmp = sortedIndices[i];
        sortedIndices[i] = sortedIndices[j];
        sortedIndices[j] = tmp;
    }

    /**
    * Compare the string representations of the column objects.
    *
    * @param i int
    * @param j int
    * @param col int
    *
    * @return int 
    */
    @SuppressWarnings("unchecked")
    private int compare(int i, int j, int col)
    {
        String methodName = MODULE_NAME + "compare(int,int,int)";
        int retval = 0;

        try
        {
            Object iObj = theRealModel.getValueAt(i,col);
            Object jObj = theRealModel.getValueAt(j,col);

            if( (iObj != null) && (jObj != null) )
            {
                int c = 0;
                if( (iObj instanceof Comparable) && (jObj instanceof Comparable) )
                {
                    c = ((Comparable)jObj).compareTo( iObj );
                }
                else 
                {
                    c = jObj.toString().compareTo(iObj.toString());
                }

                retval = (c<0) ? -1 : ((c>0) ? 1 : 0);
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }


    //*******************************************************************************//
    // TableModel impl
    // 
    /**
    * Here's where the magic happens. We cheat and use the sortedIndices array to determine 
    * what value to return.
    *
    * Returns the value for the cell at <code>columnIndex</code> and
    * <code>rowIndex</code>.
    *
    * @param   rowIndex    the row whose value is to be queried
    * @param   columnIndex     the column whose value is to be queried
    * @return  the value Object at the specified cell
    */
    public Object getValueAt(int rowIndex, int columnIndex)
    {
        return theRealModel.getValueAt( sortedIndices[rowIndex], columnIndex );
    }

    /**
    * More magic. We cheat and use the sortedIndices array to determine what they *really* mean.
    * Sets the value in the cell at <code>columnIndex</code> and
    * <code>rowIndex</code> to <code>aValue</code>.
    *
    * @param   aValue       the new value
    * @param   rowIndex     the row whose value is to be changed
    * @param   columnIndex      the column whose value is to be changed
    * @see #getValueAt
    * @see #isCellEditable
    */
    public void setValueAt(Object aValue, int rowIndex, int columnIndex)
    {
        theRealModel.setValueAt( aValue, sortedIndices[rowIndex], columnIndex );
    }

    /**
    * Pass thru to Real model
    *
    * Returns the number of rows in the model. A
    * <code>JTable</code> uses this method to determine how many rows it
    * should display.  This method should be quick, as it
    * is called frequently during rendering.
    *
    * @return the number of rows in the model
    * @see #getColumnCount
    *
    */
    public int getRowCount()
    {
        return theRealModel.getRowCount();
    }

    /**
    * Pass thru to Real model
    *
    * Returns the number of columns in the model. A
    * <code>JTable</code> uses this method to determine how many columns it
    * should create and display by default.
    *
    * @return the number of columns in the model
    * @see #getRowCount
    */
    public int getColumnCount()
    {
        return theRealModel.getColumnCount();
    }

    /**
    * Pass thru to Real model
    *
    * Returns the name of the column at <code>columnIndex</code>.  This is used
    * to initialize the table's column header name.  Note: this name does
    * not need to be unique; two columns in a table can have the same name.
    *
    * @param   columnIndex the index of the column
    * @return  the name of the column
    */
    public String getColumnName(int columnIndex)
    {
        return theRealModel.getColumnName(columnIndex);
    }

    /**
    * Pass thru to Real model
    * Returns the most specific superclass for all the cell values 
    * in the column.  This is used by the <code>JTable</code> to set up a 
    * default renderer and editor for the column.
    *
    * @param columnIndex  the index of the column
    * @return the common ancestor class of the object values in the model.
    */
    public Class getColumnClass(int columnIndex)
    {
        return theRealModel.getColumnClass(columnIndex);
    }

    /**
    * Be sure and use the sortIndices to return the correct value.
    * Returns true if the cell at <code>rowIndex</code> and
    * <code>columnIndex</code>
    * is editable.  Otherwise, <code>setValueAt</code> on the cell will not
    * change the value of that cell.
    *
    * @param   rowIndex    the row whose value to be queried
    * @param   columnIndex the column whose value to be queried
    * @return  true if the cell is editable
    * @see #setValueAt
    */
    public boolean isCellEditable(int rowIndex, int columnIndex)
    {
        return theRealModel.isCellEditable(sortedIndices[rowIndex],columnIndex);
    }

    /**
    * Pass thru to Real model
    * Adds a listener to the list that is notified each time a change
    * to the data model occurs.
    *
    * @param   l       the TableModelListener
    */
    public void addTableModelListener(TableModelListener l)
    {
        theRealModel.addTableModelListener( l );
    }

    /**
    * Pass thru to Real model
    * Removes a listener from the list that is notified each time a
    * change to the data model occurs.
    *
    * @param   l       the TableModelListener
    */
    public void removeTableModelListener(TableModelListener l)
    {
        theRealModel.removeTableModelListener( l );
    }
    // TableModel impl ends


    //******************************************************************************//
    // TableModelListener impl 
    //
    /**
    * This fine grain notification tells listeners the exact range
    * of cells, rows, or columns that changed.
    *
    * @param e TableModelEvent
    */
    public void tableChanged(TableModelEvent e)
    {
        //refresh();
    }
    // TableModelListener impl ends
}
