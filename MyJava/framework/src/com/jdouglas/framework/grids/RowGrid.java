package com.jdouglas.FusionAE.grids;

import java.awt.*;
import java.util.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;
import org.w3c.dom.*;
import org.xml.sax.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.plots.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.enums.data.*;

import com.jdouglas.FCAdmin.interfaces.data.*;

import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.enums.data.*;

/**
* RowGrid. An FAE row based Grid.
*
*
* @author Jason Douglas 3/12/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class RowGrid
    extends FusionData
        implements IRowGrid
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "RowGrid.";

	/** The super secret list of column information associated with the RowGrid */
	private IGridRow theColumnHeader = new GridRow(IGrid.COLUMN_LABELS,GridRowType.HEADER);

	/** Row List */
	private LinkedList<IGridRow> theRows = new LinkedList<IGridRow>();
	/** the Plot Collection */
	private IPlotCollection thePlots;

    /**
    * Constructor.
    *
    * @param name String
	* @param cols ArrayList<IGridColumn>
    */
    public RowGrid(String name, ArrayList<IGridColumn> cols)
    {
        setProperty( DISPLAY_NAME, name );
        setProperty( X_AXIS_TITLE, "X-Axis" );
        setProperty( Y_AXIS_TITLE, "Y-Axis" );
		setProperty( GRID_TYPE, ROW_BASED );

		Iterator<IGridColumn> iter = cols.iterator();
		while( iter.hasNext() )
		{
			IGridColumn c = iter.next();
			theColumnHeader.addColumn( c.getDisplayName(), c );
		}
    }

	/**
	* Constructor.
	*
	* @param name String
	* @deprecated This constructor is going away.
	*/
	@Deprecated
	public RowGrid(String name)
	{
		this( name, new ArrayList<IGridColumn>() );
	}

	/**
    * Constructor 
	* 
	* @param colGrid IColumnGrid
    */
	public RowGrid(IColumnGrid colGrid)
	{
		setProperty( DISPLAY_NAME, colGrid.getDisplayName() );
		setProperty( X_AXIS_TITLE, colGrid.getStringProperty(X_AXIS_TITLE) );
		setProperty( Y_AXIS_TITLE, colGrid.getStringProperty(Y_AXIS_TITLE) );
		setProperty( GRID_TYPE, ROW_BASED );
		setProperty( TESTING_DESIGN_TYPE, colGrid.getProperty(TESTING_DESIGN_TYPE) );

		//Create the header based on the columns
		ArrayList<String> colNames = new ArrayList<String>();
		Iterator<IGridColumn> iter = colGrid.getGridColumns().iterator();
		while( iter.hasNext() )
		{
			IGridColumn c = iter.next();
			theColumnHeader.addColumn( c.getDisplayName(), c );
			colNames.add( c.getDisplayName() );
		}

		//Now create the rows from header of the column grid
		IGridColumn rowHeader = colGrid.getGridColumn(IGrid.ROW_LABELS);
		Iterator<Object> rowIter = rowHeader.getRows().values().iterator();
		while( rowIter.hasNext() )
		{
			IGridRow r = (IGridRow)rowIter.next();
			IGridRow newRow = new GridRow( r, colNames );

			//Populate the row from the colGrid
			iter = colGrid.getGridColumns().iterator();
			while( iter.hasNext() )
			{
				IGridColumn c = iter.next();
				newRow.setColumnValue( c.getDisplayName(), c.getRows().get(newRow.getDisplayName()) );
			}

			addGridRow( newRow );
		}
	}

	//JGD TODO: Constructor that takes TableData XML and parses it. 

    //***********************************************************************************************************//
    // IRowGrid impl
    //

	/**
	* Create a new IGridRow for this grid using the given name, type, and class.
	* The row will *not* be automatically inserted into the Grid, but will be populated with
	* the grid's current columns.
	* 
	* @param name String
	* @param type GridRowType
	* @param rowClass Class
	* 
	* @return IGridRow
	*/
	public IGridRow createGridRow(String name, GridRowType type, Class rowClass)
	{
		String methodName = MODULE_NAME + "createGridRow(String,GridRowType, Class)";
		IGridRow retval = null;

		try
		{
			ArrayList<String> colNames = new ArrayList<String>();
			Iterator<Object> iter = theColumnHeader.getColumns().values().iterator();
			while( iter.hasNext() )
			{
				IGridColumn c = (IGridColumn)iter.next();
				colNames.add( c.getDisplayName() );
			}

			retval = new GridRow( name, type, rowClass, colNames );
		} 
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}


	/**
	* Create a new IGridRow for this grid using the given name and type and the default row class of Double.
	* The row will *not* be automatically inserted into the Grid, but will be populated with
	* the grid's current columns.
	* 
	* @param name String
	* @param type GridRowType
	* 
	* @return IGridRow
	*/
	public IGridRow createGridRow(String name, GridRowType type)
	{
		return createGridRow( name, type, Double.class );
	}

	/**
	* Get the GridRows associated with the grid.
	*
	* @return ArrayList<IGridRow>
	*/
	public ArrayList<IGridRow> getGridRows()
	{
		String methodName = MODULE_NAME + "getGridRows()";
		ArrayList<IGridRow> retval = new ArrayList<IGridRow>(theRows);

		try
		{
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}


		return retval;
	}

	/**
	* Add a GridRow to the grid.
	* 
	* @param row IGridRow
	*/
	public void addGridRow(IGridRow row)
	{
		String methodName = MODULE_NAME + "addGridRow(IGridRow)";

		try
		{
			theRows.add( row );
			row.setParent( this );
			thePlots = null;
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a row before the given row name.
	* 
	* @param row IGridRow
	* @param rowName String 
	*/
	public void insertRowBefore(IGridRow row, String rowName)
	{
		String methodName = MODULE_NAME + "insertRowBefore(IGridRow, String)";

		try
		{
			int index = theRows.indexOf( getGridRow(rowName) );
			theRows.add( index, row );
			row.setParent( this );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a row before the row at the given index. 
	* If there is no row at the given index, the row is placed at the end of the list.
	* 
	* @param row IGridRow
	* @param index int
	*/
	public void insertRowBefore(IGridRow row, int index)
	{
		String methodName = MODULE_NAME + "insertRowBefore(IGridRow, String)";

		try
		{
			theRows.add( index, row );
			row.setParent( this );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a row after the given row name.
	* 
	* @param row IGridRow 
	* @param rowName String 
	*/
	public void insertRowAfter(IGridRow row, String rowName)
	{
		String methodName = MODULE_NAME + "insertRowAfter(IGridRow, String)";

		try
		{
			int index = theRows.indexOf( getGridRow(rowName) ) + 1;
			if( index == theRows.size() )
			{
				theRows.addLast( row );
			}
			else
			{
				theRows.add( index, row );
			}
			row.setParent( this );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a row after the row at the given index. 
	* If there is no row at the given index, the row is placed at the end of the list.
	* 
	* @param row IGridRow
	* @param _index int
	*/
	public void insertRowAfter(IGridRow row, int _index)
	{
		String methodName = MODULE_NAME + "insertRowAfter(IGridRow, int)";

		try
		{
			int index = _index + 1;
			if( index == theRows.size() )
			{
				theRows.addLast( row );
			}
			else
			{
				theRows.add( index, row );
			}
			row.setParent( this );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/** 
	* Get the GridRow by name.
	*
	* @param name String
	*
	* @return IGridRow
	*/
	public IGridRow getGridRow(String name)
	{
		String methodName = MODULE_NAME + "getGridRow(String)";
		IGridRow retval = null;

		try
		{
			if( name.intern() == IGrid.COLUMN_LABELS.intern() )
			{
				return theColumnHeader;
			}

			Iterator<IGridRow> iter = theRows.iterator();
			while( iter.hasNext() )
			{
				IGridRow row = iter.next();
				if( row.getDisplayName().intern() == name.intern() )
				{
					retval = row;
					break;
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
	* Get Rows by type. Note that the returned list has no bearing on the overall placement of the 
	* contained row objects.
	* 
	* @param type GridRowType
	* 
	* @return ArrayList<IGridRow>
	*/
	public ArrayList<IGridRow> getRowByType(GridRowType type)
	{
		String methodName = MODULE_NAME + "getRowByType(GridColumnType)";
		ArrayList<IGridRow> retval = new ArrayList<IGridRow>();

		try
		{
			if( type == GridRowType.ALL )
			{
				retval = getGridRows();
			}
			else
			{
				Iterator<IGridRow> iter = getGridRows().iterator();
				while( iter.hasNext() )
				{
					IGridRow row = iter.next();
					if( row.getRowType() == type )
					{
						retval.add( row );
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
	* Get Rows by types. Note that the returned list has no bearing on the overall placement of the 
	* contained row objects.
	* 
	* @param types EnumSet<GridRowType>
	* 
	* @return ArrayList<IGridRow>
	*/
	public ArrayList<IGridRow> getRowByType(EnumSet<GridRowType> types)
	{
		String methodName = MODULE_NAME + "getRowByType(EnumSet<GridColumnType>)";
		ArrayList<IGridRow> retval = new ArrayList<IGridRow>();

		try
		{
			if( types.contains(GridRowType.ALL) )
			{
				retval = getGridRows();
			}
			else
			{
				Iterator<IGridRow> iter = getGridRows().iterator();
				while( iter.hasNext() )
				{
					IGridRow row = iter.next();
					if( types.contains(row.getRowType()) )
					{
						retval.add( row );
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
	* Remove a GridRow by name.
	*
	* @param name String 
	*/
	public void removeGridRow(String name)
	{
		String methodName = MODULE_NAME + "removeGridRow(String)";

		try
		{
			IGridRow row = getGridRow( name );
			row.setParent( null );
			theRows.remove( row );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Remove a GridRow by object.
	*
	* @param row IGridRow
	*/
	public void removeGridRow(IGridRow row)
	{
		String methodName = MODULE_NAME + "removeGridRow(IGridRow)";

		try
		{
			row.setParent( null );
			theRows.remove( row );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* REmove a GridRow by index.
	*
	* @param index int
	*/
	public void removeGridRow(int index)
	{
		String methodName = MODULE_NAME + "removeGridRow(int)";

		try
		{
			IGridRow row = theRows.get(index);
			if( row != null )
			{
				row.setParent( null );
				theRows.remove( row );
				thePlots = null;
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    /**
    * Generate an IPlotCollection from the RowGrid.
    *
    * @return IPlotCollection
    */
    private IPlotCollection getPlotCollection()
    {
        String methodName = MODULE_NAME + "getPlotCollection()";
        IPlotCollection retval = thePlots;

		//Logger.log( methodName , Logger.DEBUG );
        try
        {
			if( retval == null )
			{
				retval = new PlotCollection( getStringProperty(IGrid.X_AXIS_TITLE),
											 getStringProperty(IGrid.Y_AXIS_TITLE) );
	
				retval.setProperty( IPlotCollection.CHART_SOURCE_TITLE, getDisplayName() );
	
				//Create plots for each run
				Iterator<IGridRow> rIter = getGridRows().iterator();
				while( rIter.hasNext() )
				{
					IGridRow row = rIter.next();
					Double xVal = (Double)row.getProperty(IGridRow.ROW_VALUE);
					Boolean includeInPlotCollection = (Boolean)row.getProperty(INCLUDE_IN_PLOT_COLLECTIONS);

					IPlotData plot = retval.getPlot( getDisplayName() );
					if( plot == null )
					{
						plot = new PlotData(getDisplayName());   
						retval.addPlot( plot );
					}
	
					Iterator<Map.Entry<String,Object>> colIter = row.getColumns().entrySet().iterator();
					while( colIter.hasNext() )
					{
						Map.Entry<String,Object> entry = colIter.next();
						if( (entry != null) && (entry.getValue() != null) && (xVal != null) && (includeInPlotCollection == true) )
						{
							plot.getPoints().add( new PointData( xVal.doubleValue(), ((Double)entry.getValue()).doubleValue() ) );
						}
					}
				}

				thePlots = retval;
			}
        }
        catch(Exception e)
        {
			Logger.log( getDisplayName(), Logger.DEBUG );
            FusionUtils.logError( methodName, getDisplayName(), e );
        }

        return retval;
    }

	/**
	* Return an XML string of the given type.
	* 
	* @param type int 
	*
	* @return String
	*/
	@SuppressWarnings("unchecked")
	public String getXMLString(int type)
	{
		String methodName = MODULE_NAME + "getXMLString(int)";
		String retval = null;

		Logger.log( methodName, Logger.DEBUG );
		try
		{
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document doc = db.newDocument();

			//FOR VB
			switch( type )
			{
				case TABLE_DATA_XML_ROW:
				default:
				{
                    Element rootElem = doc.createElement( "FusionAE" );
                    doc.appendChild(rootElem);
                    appendToXMLDocument(doc, rootElem, type, true);
                    retval = FusionUtils.getXMLString( rootElem.getFirstChild(), true );
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    public void appendToXMLDocument(Document doc, Element parent, int type, boolean includeRowLabels)
	{
		String methodName = MODULE_NAME + "appendToXMLDocument(int)";

		Logger.log( methodName, Logger.DEBUG );
		try
		{
			switch( type )
			{
				case TABLE_DATA_XML_COL:
				default:
				{
					Element rootElem = doc.createElement( IGrid.TABLE_DATA_XML_ELEMENT );
					rootElem.setAttribute( iTData.TOKEN, getDisplayName() );
					rootElem.setAttribute( IGrid.MASTER_TOKEN, IGrid.ROW_XML_ELEMENT );
					rootElem.setAttribute( IGrid.X_AXIS_TITLE, getStringProperty(IGrid.X_AXIS_TITLE) );
					rootElem.setAttribute( IGrid.Y_AXIS_TITLE, getStringProperty(IGrid.Y_AXIS_TITLE) );
					rootElem.setAttribute( IGrid.COMPOUND_PARENT, getStringProperty(IGrid.COMPOUND_PARENT) );
                    parent.appendChild(rootElem);

                    //Create the header based on these rows
                    Iterator<IGridRow> firstColIter = getGridRows().iterator();

					Integer rowCount = new Integer( getGridRows().size() + 1); //Have to account for the row labels.

					rootElem.setAttribute( IGrid.MASTER_COUNT, rowCount.toString() );

					//Create the First Row
                    Element firstRowElem = doc.createElement(IGrid.ROW_XML_ELEMENT);
                    firstRowElem.setAttribute( iTData.TYPE, "STATIC" );
                    firstRowElem.setAttribute( iTData.TOKEN, IGrid.COLUMN_LABELS );
                    firstRowElem.setAttribute( iTData.DATA_TYPE, "STRING" );
                    firstRowElem.setAttribute( iTData.POSITION, "1" );
                    firstRowElem.setAttribute( iTData.READ_ONLY, "True" );
                    rootElem.appendChild( firstRowElem );

                    IGridRow colHeader = getGridRow(IGrid.COLUMN_LABELS);
                    Iterator<Object> colIter = colHeader.getColumns().values().iterator();

					Integer colCount = new Integer( colHeader.getColumns().size());
                    rootElem.setAttribute( IGrid.CHILD_COUNT, colCount.toString() );

                    int i = 1;
                    Element dataElem;
                    //Loop first to create all of the "Column" headers
                    if(includeRowLabels)
                    {
                        dataElem = doc.createElement( IGrid.DATA_XML_ELEMENT );
                        dataElem.setAttribute( iTData.TYPE, "STATIC" );
                        dataElem.setAttribute( iTData.DATA_TYPE, "STRING" );
                        dataElem.setAttribute( iTData.POSITION, new Integer(1).toString() );
                        dataElem.setAttribute( iTData.ID, new Integer(1).toString() );
                        dataElem.setAttribute( iTData.TOKEN, IGrid.ROW_LABELS);
                        firstRowElem.appendChild( dataElem );
                        i = 2;
                    }

                    //Loop to create all of the other "Column" headers
					while( colIter.hasNext() )
					{
						IGridColumn col = (IGridColumn)colIter.next();
						dataElem = doc.createElement( IGrid.DATA_XML_ELEMENT );
						dataElem.setAttribute( iTData.TYPE, "DATA" );
						dataElem.setAttribute( iTData.DATA_TYPE, "DOUBLE" );
						dataElem.setAttribute( iTData.POSITION, new Integer(i).toString() );
						dataElem.setAttribute( iTData.ID, new Integer(i).toString() );
						dataElem.setAttribute( iTData.TOKEN, col.getDisplayName()); //col.getStringProperty(iTData.TOKEN)
						//dataElem.setAttribute( iTData.DISPLAY_LABEL, col.getDisplayName() );
						dataElem.setAttribute( iTData.PRECISION, col.getStringProperty(iTData.PRECISION) );
						dataElem.setAttribute( iTData.UNITS, col.getStringProperty(iTData.UNITS) );
						dataElem.setAttribute( IGridColumn.COLUMN_TYPE, col.getStringProperty(IGridColumn.COLUMN_TYPE) );
						firstRowElem.appendChild( dataElem );
                        i++;
                    }

                    i = 2;
                    int additionalCount = 2;
                    if(!includeRowLabels)
                    {
                        additionalCount = 1;
                    }
                    //Now create a Row element and fill with the actual data.
                    while( firstColIter.hasNext() )
                    {
                        Element rowElem = doc.createElement(IGrid.ROW_XML_ELEMENT);
                        rowElem.setAttribute( iTData.POSITION, new Integer(i).toString() );
                        rootElem.appendChild( rowElem );

                        IGridRow row = firstColIter.next();
                        if(includeRowLabels)
                        {
                            dataElem = doc.createElement(IGrid.DATA_XML_ELEMENT);
                            dataElem.appendChild( doc.createTextNode( row.getDisplayName()));
                            dataElem.setAttribute( iTData.ID, new Integer(1).toString() );
                            dataElem.setAttribute( iTData.POSITION, new Integer(1).toString() );
                            rowElem.appendChild( dataElem );
                        }
                        int counter = row.getColumns().size();
                        for(int count = 0; count < counter; count++)
                        {
                            Object obj = row.getColumnValue(count);
                            dataElem = doc.createElement(IGrid.DATA_XML_ELEMENT);
                            if( obj != null )
                            {
                                dataElem.appendChild( doc.createTextNode(obj.toString()) );
                            }
                            else
                            {
                                dataElem.appendChild( doc.createTextNode("") );
                            }
                            dataElem.setAttribute( iTData.POSITION, new Integer(count + additionalCount).toString() );
                            dataElem.setAttribute( iTData.ID, new Integer(count + additionalCount).toString() ); 
                            rowElem.appendChild( dataElem );
                        }
                        /*
						Iterator<Object> iter = row.getColumns().values().iterator();
						int j = 0;
						while( iter.hasNext() )
						{
							Object obj = iter.next();
							dataElem = doc.createElement(IGrid.DATA_XML_ELEMENT);
							if( obj != null )
							{
								dataElem.appendChild( doc.createTextNode(obj.toString()) );
							}
							else
							{
								dataElem.appendChild( doc.createTextNode("") );
							}
							dataElem.setAttribute( iTData.POSITION, new Integer(j+1).toString() );
							dataElem.setAttribute( iTData.ID, new Integer(j+1).toString() ); 
							rowElem.appendChild( dataElem );
							j++;
						}
                        */
                        i++;
                    }
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Transform the grid based on the value of GridTransforms param.
	* 
	* @param type GridTransforms
	* 
	* @return Object
	*/
	public Object transformGrid(GridTransforms type)
	{
		String methodName = MODULE_NAME + "transformGrid(GridTransforms)";
		Object retval = null;

		try
		{
			switch(type)
			{
				case TABLE_DATA_XML:
					retval = getXMLString(IGrid.TABLE_DATA_XML_ROW);
					break;
				case MEAN_REDUCED_GRID:
					break;
				case PLOT_COLLECTION:
					retval = getPlotCollection();
					break;
				default:

			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}


		return retval;
	}

    // IRowGrid impl ends
}


