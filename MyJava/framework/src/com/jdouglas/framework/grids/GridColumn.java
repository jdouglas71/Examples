package com.jdouglas.FusionAE.grids;

import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.enums.data.*;

/**
* GridColumn. Represents a column in a Grid. The type of column is dictated by the enum GridColumnType.
*
* @author Jason Douglas 4/25/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridColumn
    extends FusionData
        implements IGridColumn
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "GridColumn.";

    /** The rows */
    private LinkedHashMap<String,Object> theRows = new LinkedHashMap<String,Object>();

	/**
	* Constructor.
	*
	* @param name String
	* @param type GridColumnType 
	* @param columnClass Class
    * @param rowNames ArrayList<String>
	*/
	protected GridColumn(String name, GridColumnType type, Class columnClass, ArrayList<String> rowNames)
	{
		setProperty( DISPLAY_NAME, name );
		setProperty( COLUMN_TYPE, type );
		setProperty( PRECISION, new Integer(2) );
		setProperty( READ_ONLY, false );
		setProperty( COLUMN_CLASS, columnClass );
		setProperty( COLUMN_VALUE, new Double(0.0) );
		setProperty( PARENT_ROW_ID, -1 );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, false );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, true );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, false );

		Iterator<String> iter = rowNames.iterator();
		while( iter.hasNext() )
		{
			//JGD TODO Some way to pass in reasonable defaults?
			theRows.put( iter.next(), null );
		}
	}

    /**
    * Constructor.
    *
    * @param name String
    * @param type GridColumnType 
	* @param columnClass Class
    */
    public GridColumn(String name, GridColumnType type, Class columnClass)
    {
        setProperty( DISPLAY_NAME, name );
        setProperty( COLUMN_TYPE, type );
        setProperty( PRECISION, new Integer(2) );
        setProperty( READ_ONLY, false );
		setProperty( COLUMN_CLASS, columnClass );
		setProperty( COLUMN_VALUE, new Double(0.0) );
		setProperty( PARENT_ROW_ID, -1 );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, false );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, true );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, false );
    }

	/**
	* Constructor
	*
	* @param name String
	* @param type GridColumnType 
	*/
	public GridColumn(String name, GridColumnType type)
	{
		this( name, type, Double.class );
	}

	/**
	* Constructor.
	*
	* @param col IGridColumn
	* @param rowNames ArrayList<String>
	*/
	protected GridColumn(IGridColumn col, ArrayList<String> rowNames)
	{
		setProperty( DISPLAY_NAME, col.getDisplayName() );
		setProperty( COLUMN_TYPE, col.getColumnType() );
		setProperty( PRECISION,    col.getProperty(PRECISION) );
		setProperty( READ_ONLY,    col.getProperty(READ_ONLY) );
		setProperty( COLUMN_CLASS, col.getProperty(COLUMN_CLASS) );
		setProperty( COLUMN_VALUE, col.getProperty(COLUMN_VALUE) );
		setProperty( PARENT_ROW_ID, col.getProperty(PARENT_ROW_ID) );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, col.getProperty(IGrid.INCLUDE_IN_MAIN_DESIGN) );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, col.getProperty(IGrid.INCLUDE_IN_PLOT_COLLECTIONS) );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, col.getProperty(IGrid.DO_NOT_INCLUDE_IN_ANALYSIS) );
		setProperty( TOKEN, col.getProperty(TOKEN) );
		setProperty( UNITS, col.getProperty(UNITS) );

		//JGD TODO: Should have an internal list of properties we care about. 

		Iterator<String> iter = rowNames.iterator();
		while( iter.hasNext() )
		{
			//JGD TODO Some way to pass in reasonable defaults?
			theRows.put( iter.next(), null );
		}
	}


    //***********************************************************************************************************//
    // IGridColumn impl
    //

    /**
    * Get the type.
    *
    * @return GridColumnType
    */
    public GridColumnType getColumnType()
    {
        return (GridColumnType)getProperty( COLUMN_TYPE );
    }

	/** 
	* Add Row. 
	*
	* @param rowName String
	* @param val Object
	*/ 
	public void addRun(String rowName, Object val)
	{
		String methodName = MODULE_NAME + "addRun(String,Object)";

		theRows.put( rowName, val );
	}

    /** 
    * Add Row. 
    *
    * @param rowName String
    * @param val Object
    */ 
    public void addRow(String rowName, Object val)
    {
		theRows.put( rowName, val );
    }

    /**
    * Get the value for the given row label. Returns null if there is no value for that label in this column.
    *
    * @param rowName String
    *
    * @return Object
    */
    public Object getRow(String rowName)
    {
        return theRows.get( rowName );
    }

    /**
    * Get rows.
    *
    * @return LinkedHashMap<String,Object>
    */
    public LinkedHashMap<String,Object> getRows()
    {
        return new LinkedHashMap<String,Object>(theRows);
    }

	/**
	* Get row Values by Type. Do not modify the returned ArrayList.
	* 
	* @param type GridRowType 
	* 
	* @return ArrayList<object>
	*/
	public ArrayList<Object> getRowValuesByType(GridRowType type)
	{
		String methodName = MODULE_NAME + "getRowValuesByType(GridRowType)";
		ArrayList<Object> retval = new ArrayList<Object>();

		try
		{
			IColumnGrid grid = (IColumnGrid)getParent();
			IGridColumn rowHeader = grid.getGridColumn( IGrid.ROW_LABELS );
			Iterator<Object> iter = rowHeader.getRows().values().iterator();
			while( iter.hasNext() )
			{
				IGridRow r = (IGridRow)iter.next();
				if( r.getRowType() == type )
				{
					retval.add( getRow(r.getDisplayName()) );
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
    * Set Row Value. If the row does not exist, nothing will occur.
	* 
	* @param rowName String
	* @param value Object 
    */
	public void setRowValue(String rowName, Object value)
	{
		String methodName = MODULE_NAME + "setRowValue(String,Object)";

		try
		{
			//We're not allowing this to set a value for a row that does not exist.
			if( theRows.keySet().contains(rowName) )
			{
				theRows.put( rowName, value );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Get Row Value by index.
	* 
	* @param index int
	* 
	* @return Object
	*/
	public Object getRowValue(int index)
	{
		String methodName = MODULE_NAME + "getRowValue(int)";
		Object retval = null;

		try
		{
			ArrayList<Object> valList = new ArrayList<Object>( getRows().values() );
			retval = valList.get( index );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Get Column index. Queries parent grid for row index. Returns -1 if it cannot determine.
	*/
	public int getColumnIndex()
	{
		String methodName = MODULE_NAME + "getColumnIndex()";
		int retval = -1;

		try
		{
			IColumnGrid parentGrid = (IColumnGrid)getParent();
			if( parentGrid != null )
			{
				retval = parentGrid.getGridColumns().indexOf( this );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    /**
    * Get the readonly flag
    *
    * @return boolean 
    */
    public boolean isReadOnly()
    {
        return ((Boolean)getProperty(READ_ONLY)).booleanValue();
    }

	/**
	* String representation of the data. I don't use toString because I need to overload that for display purposes at times.
	* This string will be a listing of all the properties and values so that we can log it for debug purposes.
	*
	* @return String 
	*/
	public String dumpString()
	{
		String methodName = MODULE_NAME + "dumpString()";
		StringBuffer strBuf = new StringBuffer( super.dumpString() );

		try
		{
			Iterator<String> runIter = getRows().keySet().iterator();
			while( runIter.hasNext() )
			{
				String runLabel = runIter.next();
				strBuf.append( runLabel + " " + getRow(runLabel).toString() + "\n" );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
		return strBuf.toString();
	}

	/**
	* Set Temporary Flag. 
	* 
	* @param b boolean
	*/
	public void setTemporaryFlag(boolean b)
	{
		setProperty(iTData.TEMPORARY_FLAG, b);
	}

	/**
	* Get Temporary Flag. 
	* 
	* @return boolean
	*/
	public boolean isTemporary()
	{
		return ((Boolean)getProperty(iTData.TEMPORARY_FLAG)).booleanValue();
	}

    // IGridColumn impl ends
 }
