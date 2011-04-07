package com.jdouglas.FusionAE.grids;

import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.enums.data.*;

/**
* GridRow. Represents a row in a Grid. The type of row is dictated by the enum GridRowType.
*
* @author Jason Douglas 3/9/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridRow
    extends FusionData
        implements IGridRow
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "GridRow.";

    /** The rows */
    private LinkedHashMap<String,Object> theCols = new LinkedHashMap<String,Object>();

	/**
	* Constructor.
	*
	* @param name String
	* @param type GridRowType 
	* @param rowClass Class
	* @param colNames ArrayList<String>
	*/
	public GridRow(String name, GridRowType type, Class rowClass, ArrayList<String> colNames)
	{
		setProperty( DISPLAY_NAME, name );
		setProperty( ROW_TYPE, type );
		setProperty( PRECISION, new Integer(2) );
		setProperty( READ_ONLY, false );
		setProperty( ROW_CLASS, rowClass );
		setProperty( ROW_VALUE, new Double(0.0) );
		setProperty( PARENT_ROW_ID, -1 );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, false );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, true );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, false );

		Iterator<String> iter = colNames.iterator();
		while( iter.hasNext() )
		{
			//JGD TODO Some way to pass in reasonable defaults?
			theCols.put( iter.next(), null );
		}
	}

    /**
    * Constructor.
    *
    * @param name String
    * @param type GridRowType 
	* @param rowClass Class
    */
    public GridRow(String name, GridRowType type, Class rowClass)
    {
        setProperty( DISPLAY_NAME, name );
        setProperty( ROW_TYPE, type );
        setProperty( PRECISION, new Integer(2) );
        setProperty( READ_ONLY, false );
		setProperty( ROW_CLASS, rowClass );
		setProperty( ROW_VALUE, new Double(0.0) );
		setProperty( PARENT_ROW_ID, -1 );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, false );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, true );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, false );
    }

	/**
	* Constructor
	*
	* @param name String
	* @param type GridRowType 
	*/
	public GridRow(String name, GridRowType type)
	{
		this( name, type, Double.class );
	}

	/**
    * Constructor for creating new GridRow's from existing ones. 
	* 
	* @param row IGridRow
	* @param colNames ArrayList<String>
    */
	protected GridRow(IGridRow row, ArrayList<String> colNames)
	{
		setProperty( DISPLAY_NAME, row.getDisplayName() );
		setProperty( ROW_TYPE, row.getRowType() );
		setProperty( PRECISION, row.getProperty(PRECISION) );
		setProperty( READ_ONLY, row.getProperty(READ_ONLY) );
		setProperty( ROW_CLASS, row.getProperty(ROW_CLASS) );
		setProperty( ROW_VALUE, row.getProperty(ROW_VALUE) );
		setProperty( IGrid.INCLUDE_IN_MAIN_DESIGN, row.getProperty(IGrid.INCLUDE_IN_MAIN_DESIGN) );
		setProperty( IGrid.INCLUDE_IN_PLOT_COLLECTIONS, row.getProperty(IGrid.INCLUDE_IN_PLOT_COLLECTIONS) );
		setProperty( IGrid.DO_NOT_INCLUDE_IN_ANALYSIS, row.getProperty(IGrid.DO_NOT_INCLUDE_IN_ANALYSIS) );
		setProperty( TOKEN, row.getProperty(TOKEN) );
		setProperty( SAMPLE_ID, row.getProperty(SAMPLE_ID) );
		setProperty( PARENT_ROW_ID, row.getProperty(PARENT_ROW_ID) );
		setProperty( UNITS, row.getProperty(UNITS) );

		//JGD TODO: Should have an internal list of properties we care about. 

		Iterator<String> iter = colNames.iterator();
		while( iter.hasNext() )
		{
			//JGD TODO Some way to pass in reasonable defaults?
			theCols.put( iter.next(), null );
		}
	}

    //***********************************************************************************************************//
    // IGridRow impl
    //

    /**
    * Get the type.
    *
    * @return GridRowType
    */
    public GridRowType getRowType()
    {
        return (GridRowType)getProperty( ROW_TYPE );
    }

    /** 
    * Add Column. 
    *
    * @param colName String
    * @param val Object
    */ 
    public void addColumn(String colName, Object val)
    {
		theCols.put( colName, val );
    }

    /**
    * Get the value for the given column label. Returns null if there is no value for that label in this row.
    *
    * @param rowName String
    *
    * @return Object
    */
    public Object getColumn(String rowName)
    {
        return theCols.get( rowName );
    }

    /**
    * Get columns.
    *
    * @return LinkedHashMap<String,Object>
    */
    public LinkedHashMap<String,Object> getColumns()
    {
        return new LinkedHashMap<String,Object>(theCols);
    }

	/**
	* Get Column Values by Type. Do not modify the returned ArrayList.
	* 
	* @param type GridColumnType 
	*/
	public ArrayList<Object> getColumnValuesByType(GridColumnType type)
	{
		String methodName = MODULE_NAME + "getColumnValuesByType(GridColumnType)";
		ArrayList<Object> retval = new ArrayList<Object>();

		try
		{
			IRowGrid grid = (IRowGrid)getParent();
			if( grid != null )
			{
				IGridRow colHeader = grid.getGridRow( IGrid.COLUMN_LABELS );
				Iterator<Object> iter = colHeader.getColumns().values().iterator();
				while( iter.hasNext() )
				{
					IGridColumn col = (IGridColumn)iter.next();
					if( col.getColumnType() == type )
					{
						retval.add( getColumn(col.getDisplayName()) );
					}
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
	* Get Column Value by index.
	* 
	* @param index int
	* 
	* @return Object
	*/
	public Object getColumnValue(int index)
	{
		String methodName = MODULE_NAME + "getColumnValue(int)";
		Object retval = null;

		try
		{
			ArrayList<Object> valList = new ArrayList<Object>( getColumns().values() );
			retval = valList.get( index );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Set Column Value. If the column does not exist, nothing will occur.
	* 
	* @param colName String
	* @param value Object 
	*/
	public void setColumnValue(String colName, Object value)
	{
		String methodName = MODULE_NAME + "setColumnValue(String,Object)";

		try
		{
			//We're not allowing this to set a value for a col that does not exist.
			if( theCols.keySet().contains(colName) )
			{
				theCols.put( colName, value );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Get Row index. Queries parent grid for row index. Returns -1 if it cannot determine.
	*/
	public int getRowIndex()
	{
		String methodName = MODULE_NAME + "getRowIndex()";
		int retval = -1;

		try
		{
			IRowGrid parentGrid = (IRowGrid)getParent();
			if( parentGrid != null )
			{
				retval = parentGrid.getGridRows().indexOf( this );
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
    * Get Child Rows
	* 
	* @return ArrayList<IGridRow> 
    */
	public ArrayList<IGridRow> getChildRows()
	{
		String methodName = MODULE_NAME + "getChildRows()";
		ArrayList<IGridRow> retval = new ArrayList<IGridRow>();

		try
		{
			int myID = ((Integer)getProperty(SAMPLE_ID)).intValue();
			IRowGrid parentGrid = (IRowGrid)getParent();
			if( parentGrid != null )
			{
				Iterator<IGridRow> iter = parentGrid.getGridRows().iterator();
				while( iter.hasNext() )
				{
					IGridRow r = iter.next();
					int parentRowId = ((Integer)r.getProperty(PARENT_ROW_ID)).intValue();
					if( parentRowId == myID )
					{
						retval.add( r );
					}
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
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
			Iterator<String> runIter = getColumns().keySet().iterator();
			while( runIter.hasNext() )
			{
				String runLabel = runIter.next();
				strBuf.append( runLabel + " " + getColumn(runLabel).toString() + "\n" );
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

    // IGridRow impl ends
}
