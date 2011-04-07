package com.jdouglas.FusionAE.grids;

import javax.swing.table.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;

import com.jdouglas.FusionAE.interfaces.data.*;

/**
* GridTableModel. Table model for the GridEditorPanel.
*
* @author Jason Douglas 4/18/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridTableModel
    extends AbstractTableModel
{
    /** Module Name */; 
    private static final String MODULE_NAME = "GridTableModel.";

    /** The Grid */
    private IColumnGrid theGrid;
    /** The GridColumns (sugar) */
    private ArrayList<IGridColumn> theGridColumns;
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
    protected GridTableModel(IColumnGrid grid)
    {
        theGrid = grid;
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
            theGridColumns = theGrid.getGridColumns();
            //Add an extra column for the run labels.
            colNum = theGridColumns.size();
            //Do all variables have the same number of runs? JGD: YES. Base Asssumption. Can have null values. 4/20/09
			if( colNum > 0 )
			{
				rowNum = theGridColumns.get(0).getRows().values().size();
			}
			else
			{
				rowNum = 0;
			}

            theData = new Object[rowNum][colNum];

            int row=0,col=0;

            Iterator<IGridColumn> iter = theGridColumns.iterator();
            while( iter.hasNext() )
            {
                IGridColumn dCol = iter.next();
                Iterator<Object> dIter = dCol.getRows().values().iterator();
                while( dIter.hasNext() )
                {
                    Object obj = dIter.next();
                    //Logger.log( methodName + " Setting row: " + row + " and col: " + col + " val: " + obj.toString(), Logger.DEBUG );
                    theData[row][col] = obj;
                    row++;
                }
                col++;
                row=0;
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
            //Logger.log( methodName + " Val.class= " + val.getClass().getDisplayName(), Logger.DEBUG );

            theData[row][col] = val;

            fireTableCellUpdated(row,col);
            setDirtyFlag( true );
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
            retval = theGridColumns.get(col).getDisplayName();
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
        String methodName = MODULE_NAME + "getColumnClass(int)";
        Class retval = Double.class;

        try
        {
            //In the event that the value is null, we're going to default to Double. A null value allows us to give 
            //RV his "blank" cell and having the model return the class as Double gives us the proper CellEditor for the table.
            //I still can't stop myself from being as generic as possible and returning the class of Object in the data array. ;)
            if( getValueAt(0,col) != null )
            {
                retval = getValueAt(0,col).getClass();
            }

        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
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

        //Column override
        if( isEditable )
        {
            IGridColumn dCol = theGridColumns.get( col );
            retval = !dCol.isReadOnly();
        }

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

    /**
    * Save the contents of the raw data matrix to the underlying objects.
    */ 
    public void saveContents()
    {
        String methodName = MODULE_NAME + "saveContents()";

		Logger.log( methodName, Logger.DEBUG );
        try
        {
            for(int col=0; col<colNum; col++)
            {
                IGridColumn dCol = theGridColumns.get(col);
				Iterator<String> iter = dCol.getRows().keySet().iterator();
				int row = 0;
				while( iter.hasNext() )
				{
					String rowName = iter.next();
					//Logger.log( methodName + " Setting row: " + rowName + " to " + theData[row][col].toString(), Logger.DEBUG );
					dCol.getRows().put( rowName, (Double)theData[row][col] );
					row++;
				}
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }
}

