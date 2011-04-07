package com.jdouglas.framework.plots;

import javax.swing.*;
import javax.swing.table.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;

/**
* PlotDataTableModel. Table model for the PlotDataTableEditor.
* 
* @author Jason Douglas 2/1/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotDataTableModel
    extends AbstractTableModel
{
    /** Module name */
    private static final String MODULE_NAME = "PlotDataTableModel.";

    /** Number of Cols */
    private static final int NUM_COLS = 3;

    /** Column numbers */
    protected static final int INCLUDED = 0;
    protected static final int X_POINT = 1;
    protected static final int Y_POINT = 2;

    /** The data */
    private Object[][] theData;
    private IPlotData plotData;
    /** Row num */
    private int rowNum;
    /** Col num */
    private int colNum;
    /** Column titles */
    private String[] colTitles;
    /** Dirty flag */
    private boolean isDirty = false;
    /** Enabled flag */
    private boolean isEnabled = true;

    /**
    * Ctor
    *
    * @param data IPlotData
    */
    protected PlotDataTableModel(IPlotData data)
    {
        plotData = data;
        initData();
    }

    /**
    * Extract the data for the table.
    */
    private void initData()
    {
        String methodName = MODULE_NAME + "initData()";
        try
        {
            rowNum = plotData.getPoints().size();
            colNum = NUM_COLS; 

            //Extract the data 
            theData = new Object[rowNum][colNum];

            for(int i=0; i<rowNum; i++)
            {
                IPointData point = plotData.getPoints().get(i);
                theData[i][INCLUDED] = new Boolean(point.isVisible());
                theData[i][X_POINT] = new Double(point.getX());
                theData[i][Y_POINT] = new Double(point.getY());
            }

            //Set up the column titles
            colTitles = new String[NUM_COLS];
            colTitles[INCLUDED] = "Included"; //JGD TODO Resources 
            colTitles[X_POINT] = plotData.getStringProperty(IPlotData.X_AXIS_TITLE);
            colTitles[Y_POINT] = plotData.getStringProperty(IPlotData.Y_AXIS_TITLE);

        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Get the number of rows.
    *
    * @return int 
    */
    public int getRowCount()
    {
        return rowNum;
    }

    /**
    * Get the number of col's
    *
    * @return int 
    */
    public int getColumnCount()
    {
        return colNum;
    }

    /**
    * Get the object associated with the given row and col.
    *
    * @param row int
    * @param col int 
    *
    * @return Object
    */
    public Object getValueAt(int row, int col)
    {
        String methodName = MODULE_NAME + "getValueAt(int,int)";
        Object retval = theData[row][col];

        return retval;
    }

    /**
    * Set the value. We only allow the ASSIGN value to change.
    *
    * @param row int
    * @param col int 
    */
    public void setValueAt(Object val, int row, int col)
    {
        String methodName = MODULE_NAME + "setValueAt(Object,int,int)";
        try
        {
            //Can only change INLCUDED 
            if( col == INCLUDED && val instanceof Boolean )
            {
                theData[row][col] = (Boolean)val;
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Get the column name.
    *
    * @param col int
    *
    * @return String 
    */
    public String getColumnName(int col)
    {
        String methodName = MODULE_NAME + "getColumnName(int)";
        String retval =  "Column " + col; 

        if( (col >= 0) && (col < colTitles.length) )
        {
            retval = colTitles[col];
        }

        Logger.log( methodName + "--->>> " + retval, Logger.FINEST );
        return retval;
    }

    /**
    * Get the column class
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
    * Disable the other columns if the enabled flag for the row is not set.
    *
    * @param row int
    * @param col int
    *
    * @return boolean
    */
    public boolean isCellEditable(int row, int col)
    {
        String methodName = MODULE_NAME + "isCellEditable(int,int)";
        boolean retval = false;

        //Can only edit the included 
        if( col == INCLUDED )
        {
            retval = true;
        }

        return retval;
    }

    /**
    * Dirty, dirty tabel model.
    *
    * @return boolean 
    */
    public boolean isDirty()
    {
        String methodName = MODULE_NAME + "isDirty()";
        return isDirty;
    }
    
    /**
    * Set the local dirty flag
    *
    * @param b boolean 
    */
    public void setDirtyFlag(boolean b)
    {
        String methodName = MODULE_NAME + "setDirtyFlag(boolean)";
        isDirty = b;
    }

    /**
    * Set the enabled flag for the model. If the model is not enabled, the cells are not
    * editable.
    *
    * @param b boolean 
    */
    public void setEnabled(boolean b)
    {
        isEnabled = b;
    }

    /**
    * Save the changes in the table data to the data model.
    */
    public void saveChanges()
    {
        String methodName = MODULE_NAME + "saveChanges()";

        try
        {
            Iterator<IPointData> iter = plotData.getPoints().iterator();
            int i = 0;
            while( iter.hasNext() )
            {
                iter.next().setVisible( ((Boolean)theData[i][INCLUDED]).booleanValue() );
                i++;
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

}

