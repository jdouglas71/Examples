package com.jdouglas.framework.util.models;

import javax.swing.table.*;
import java.util.*;

import com.jdouglas.framework.util.*;

/**
* MatrixTableModel. Generic table model for a matrix of the same class.
*
* @author Jason Douglas 5/9/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class MatrixTableModel
    extends AbstractTableModel
{
    /** Module Name */; 
    private static final String MODULE_NAME                                                         = "MatrixTableModel.";

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
    /** Raw data passed in */
    private Object[][] rawData;
    /** Local copy of the data */
    private Object[][] theData;
    /** Base object class (defaults to Double)*/
    private Class theClass = Double.class;
    /** Column names */
    private String[] theColNames;

    /**
    * Constructor 
    *
    * @param data Object[][]
    * @param colNames String[]
    * @param _class Class
    */
    public MatrixTableModel(Object[][] data, String[] colNames, Class _class)
    {
        rawData = data;
        theColNames = colNames;
        theClass = _class;
        initData();
    }

    /**
    * Constructor. Default to Double as the base class.
    *
    * @param data Object[][]
    * @param colNames String[]
    */
    public MatrixTableModel(Object[][] data, String[] colNames)
    {
        this( data, colNames, Double.class );
    }

    /**
    * Initialize the data. 
    */
    private void initData()
    {
        String methodName = MODULE_NAME + "initData()";
        try
        {
			Logger.log( methodName + " Row Num: " + rawData.length, Logger.DEBUG );
            rowNum = rawData.length;
            colNum = rawData[0].length;

            theData = new Object[rowNum][colNum];

            for(int i=0; i<rowNum; i++)
            {
                for(int j=0; j<colNum; j++)
                {
                    theData[i][j] = rawData[i][j];
                }
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
			//Logger.log( methodName + " Val.class= " + val.getClass().getName(), Logger.CONFIG );

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
            retval = theColNames[col];
        }
        catch(Exception e)
        {
            //This will happen if theColNames doesn't have enuf values for the number of columns. 
            retval = "UNKNOWN";
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
        Class retval = theClass;

        //Hardcoding the class lets us use null's for data balues (thus getting the blank cells so coveted by RV) and still
        //get the correct editor/renderers provided by the default table impl.

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
    * Get the model data.
    *
    * @return Object[][]
    */
    public Object[][] getModelData()
    {
        return theData;
    }
}

