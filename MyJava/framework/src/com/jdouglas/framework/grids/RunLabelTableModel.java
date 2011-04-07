package com.jdouglas.FusionAE.grids;

import javax.swing.table.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;

import com.jdouglas.FusionAE.interfaces.data.*;

/**
* RunLabelTableModel. Table model for the header table.
*
* @author Jason Douglas 4/18/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class RunLabelTableModel
    extends AbstractTableModel
{
    /** Module Name */; 
    private static final String MODULE_NAME = "RunLabelTableModel.";

    /** The Grid */
    private IColumnGrid theColGrid;
    /** The Row Header */
    private IGridColumn theRowHeader;
    /** Number of Rows */
    private int rowNum;
    /** number of columns */
    private int colNum;
    /** The column titles */
    private String[] colTitles;
    /** Local dirty flag */
    private boolean isDirty = false;
    /** Editable flag */
    private boolean isEditable = false;
    /** Local copy of the data */
    private Object[][] theData;

    /**
    * Constructor 
    *
    * @param grid IColumnGrid
    */
    protected RunLabelTableModel(IColumnGrid grid)
    {
        theColGrid = grid;
        initData();
    }

    /**
    * Initialize the data. 
    */
    private void initData()
    {
        String methodName = MODULE_NAME + "initData()";
        try
        {
            theRowHeader = theColGrid.getGridColumn(IGrid.ROW_LABELS);
            colNum = 1;
            //Do all GridColumns have the same number of runs? JGD Yes. 4/20/09
            rowNum = theRowHeader.getRows().size();

            theData = new Object[rowNum][colNum];

            for(int i=0; i<rowNum; i++)
            {
                theData[i][0] = theRowHeader.getRows().keySet().toArray()[i];
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Return the number of rows.
    *
    * @return int 
    */
    public int getRowCount()
    {
        return rowNum;
    }

    /**
    * Return the number of columns.
    *
    * @return int 
    */
    public int getColumnCount()
    {
        return colNum;
    }

    /**
    * Get the value at the given position in the table.
    *
    * @param row int
    * @param col int
    *
    * @return Object 
    */
    public Object getValueAt(int row, int col)
    {
        String methodName = MODULE_NAME + "getValueAt(int,int)";
        Object retval = null;

        try
        {
            retval = theData[row][col];
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
        }

        return retval;
    }

    /**
    * Set the value at the given position in the table.
    *
    * @param val Object 
    * @param row int
    * @param col int
    */
    public void setValueAt(Object val, int row, int col)
    {
        String methodName = MODULE_NAME + "setValueAt(Object,int,int)";
        try
        {
            theData[row][col] = val;

            fireTableCellUpdated(row,col);
        }
        catch(Exception e)
        {                      
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Get the column name for the given column number.
    * 
    * @param col int 
    *
    * @return String 
    */
    public String getColumnName(int col)
    {
        String methodName = MODULE_NAME + "getColumnName(int)";
        String retval =  "Column " + col; 

        try
        {
            retval = "Run Number";
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Get the class for the given column number.
    * 
    * @param col int
    *
    * @return Class
    */
    public Class getColumnClass(int col)
    {
        return getValueAt(0,col).getClass();
    }

    /**
    * Tell the table what cells are editable.
    *
    * @param row int
    * @param col int
    *
    * @return boolean 
    */
    public boolean isCellEditable(int row, int col)
    {
        String methodName = MODULE_NAME + "isCellEditable(int,int)";
        boolean retval = isEditable;
        return retval;
    }

    /**
    * Return the state of the model dirty flag.
    *
    * @return boolean 
    */
    public boolean isDirty()
    {
        String methodName = MODULE_NAME + "isDirty()";
        return isDirty;
    }
    
    /**
    * Set the dirty flag for the model
    *
    * @param b boolean 
    */
    public void setDirtyFlag(boolean b)
    {
        String methodName = MODULE_NAME + "setDirtyFlag(boolean)";
        isDirty = b;
    }

    /**
    * Set the editable flag.
    *
    * @param b boolean
    */
    public void setEditable(boolean b)
    {
        isEditable = b;
    }
}

