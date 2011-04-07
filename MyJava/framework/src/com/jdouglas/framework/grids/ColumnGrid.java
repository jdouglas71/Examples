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

import com.jdouglas.FusionAE.*;
import com.jdouglas.FusionAE.wizards.ResponseReduction.*;
import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.interfaces.props.*;
import com.jdouglas.FusionAE.enums.data.*;

/**
* ColumnGrid. An FAE Column-based Grid.
*
*
* @author Jason Douglas 3/12/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ColumnGrid
    extends FusionData
        implements IColumnGrid
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "ColumnGrid.";

	/** The super secret column of row information associated with the ColumnGrid */
	private IGridColumn theRowHeader = new GridColumn(IGrid.ROW_LABELS,GridColumnType.HEADER);

	/** Column List */
	private LinkedList<IGridColumn> theColumns = new LinkedList<IGridColumn>();
	/** the Plot Collection */
	private IPlotCollection thePlots;

	/** The resources */
	private GridResources theResources = (GridResources)FusionAE.getResources(IGridProperties.class);

    /**
    * Constructor.
    *
    * @param name String
	* @param rows ArrayList<IGridRow>
    */
    public ColumnGrid(String name, ArrayList<IGridRow> rows)
    {
        setProperty( DISPLAY_NAME, name );
        setProperty( X_AXIS_TITLE, "X-Axis" );
        setProperty( Y_AXIS_TITLE, "Y-Axis" );
		setProperty( GRID_TYPE, COL_BASED );

		Iterator<IGridRow> iter = rows.iterator();
		while( iter.hasNext() )
		{
			IGridRow r = iter.next();
			theRowHeader.addRow( r.getDisplayName(), r );
		}
	}

	/**
	* Constructor.
	*
	* @param name String
	* @deprecated This constructor is going away.
	*/
	@Deprecated 
	public ColumnGrid(String name)
	{
		this( name, new ArrayList<IGridRow>() );
	}

	/**
    * Constructor 
	* 
	* @param rowGrid IRowGrid
    */
	public ColumnGrid(IRowGrid rowGrid)
	{
		setProperty( DISPLAY_NAME, rowGrid.getDisplayName() );
		setProperty( X_AXIS_TITLE, rowGrid.getStringProperty(X_AXIS_TITLE) );
		setProperty( Y_AXIS_TITLE, rowGrid.getStringProperty(Y_AXIS_TITLE) );
		setProperty( GRID_TYPE, COL_BASED );
		setProperty( TESTING_DESIGN_TYPE, rowGrid.getProperty(TESTING_DESIGN_TYPE) );

		//Create the header based on the rows
		ArrayList<String> rowNames = new ArrayList<String>();
		Iterator<IGridRow> iter = rowGrid.getGridRows().iterator();
		while( iter.hasNext() )
		{
			IGridRow r = iter.next();
			theRowHeader.addRow( r.getDisplayName(), r );
			rowNames.add( r.getDisplayName() );
		}

		//Now create the cols from header of the row grid
		IGridRow colHeader = rowGrid.getGridRow(IGrid.COLUMN_LABELS);
		Iterator<Object> colIter = colHeader.getColumns().values().iterator();
		while( colIter.hasNext() )
		{
			IGridColumn c = (IGridColumn)colIter.next();
			IGridColumn newCol = new GridColumn( c, rowNames );

			//Populate the row from the rowGrid
			iter = rowGrid.getGridRows().iterator();
			while( iter.hasNext() )
			{
				IGridRow r = iter.next();
				newCol.setRowValue( r.getDisplayName(), r.getColumns().get(newCol.getDisplayName()) );
			}

			addGridColumn( newCol );
		}
	}

	/**
    * Constructor.
	* 
	* @param doc Document
    */
	public ColumnGrid(Document doc)
	{
		String methodName = MODULE_NAME + "ColumnGrid(Document)";
		try
		{
			Element tdElem = (Element)doc.getFirstChild();

			//Extract the attributes I care about. 
			setProperty( DISPLAY_NAME, tdElem.getAttribute(iTData.DISPLAY_LABEL) );
			setProperty( GRID_TYPE, COL_BASED );
			setProperty( X_AXIS_TITLE, tdElem.getAttribute(X_AXIS_TITLE) );
			setProperty( Y_AXIS_TITLE, tdElem.getAttribute(Y_AXIS_TITLE) );
			setProperty( COMPOUND_PARENT, tdElem.getAttribute(COMPOUND_PARENT) );
			String tdType = tdElem.getAttribute( IGrid.TARGET_OPERATION );
			Logger.log( methodName + " tdType: " + tdType, Logger.DEBUG );
			if( tdType.intern() == OPTION_STANDARD_LC.intern() )
			{
				setProperty( TESTING_DESIGN_TYPE, TestingDesignType.TDT_STANDARD_LC );
			}
			else if( tdType.intern() == OPTION_TIME_SERIES.intern() )
			{
				setProperty( TESTING_DESIGN_TYPE, TestingDesignType.TDT_TIME_SERIES );
			}
			else if( tdType.intern() == OPTION_DESCRIPTIVE_STATISTICS.intern() )
			{
				setProperty( TESTING_DESIGN_TYPE, TestingDesignType.TDT_DESCRIPTIVE_STATISTICS );
			}
			else if( tdType.intern() == OPTION_DISSOLUTION.intern() )
			{
				setProperty( TESTING_DESIGN_TYPE, TestingDesignType.TDT_DISSOLUTION );
			}

			//Get the Row labels.
			String selStr = "/TableData/Column[@token='ROW_LABELS']";
			Element rowLabelElem = (Element)FusionUtils.findNodes(selStr, tdElem).item(0);
			NodeList rowList = rowLabelElem.getElementsByTagName( IGrid.DATA_XML_ELEMENT );
			for(int i=0; i<rowList.getLength(); i++)
			{
				Element rowElem = (Element)rowList.item(i);
				String rowName = FusionUtils.getNodeValue( rowElem );
				GridRowType rowType = GridRowType.valueOf(rowElem.getAttribute(IGridRow.ROW_TYPE));
				String sampleId = rowElem.getAttribute(IGridRow.SAMPLE_ID);
				String parentId = rowElem.getAttribute(IGridRow.PARENT_ROW_ID );

				IGridRow r = new GridRow( rowName, rowType );
				r.setProperty( IGridRow.SAMPLE_ID, sampleId );
				r.setProperty( IGridRow.PARENT_ROW_ID, parentId );
				theRowHeader.addRow( r.getDisplayName(), r );
			}

			//Get the Columns
			NodeList colList = tdElem.getElementsByTagName( IGrid.COLUMN_XML_ELEMENT );
			//Skip first one, it's the row labels.
			for(int i=1; i<colList.getLength(); i++)
			{
				Element colElem = (Element)colList.item(i);
				String colName = colElem.getAttribute( iTData.DISPLAY_LABEL );
				//JGD TODO: Get the column type here. Process INCLUDE_IN_PLOT_COLLECTIONS
				IGridColumn col = createGridColumn( colName, GridColumnType.VARIABLE );
				col.setProperty( iTData.TOKEN, colElem.getAttribute(iTData.TOKEN) );
				col.setProperty( iTData.PRECISION, colElem.getAttribute(iTData.PRECISION) );
				col.setProperty( iTData.UNITS, colElem.getAttribute(iTData.UNITS) );

				String colVal = colElem.getAttribute(IGridColumn.COLUMN_VALUE);
				if( colVal != null && FusionUtils.isDouble(colVal) )
				{
					col.setProperty( IGridColumn.COLUMN_VALUE, new Double(colVal) );
				}

				String colToken = col.getStringProperty(iTData.TOKEN);
				if( colToken.startsWith("RESULT") )
				{
					col.setProperty(IGrid.INCLUDE_IN_PLOT_COLLECTIONS,false);
					col.setProperty(IGridColumn.COLUMN_TYPE, GridColumnType.RESULT);
				}

				//Get data for columns if exists. 
				ArrayList<String> rowNames = new ArrayList<String>( col.getRows().keySet() );
				selStr = "./Data";
				NodeList dataList = XPathUtils.findNodes( selStr, colElem );
				for(int j=0; j<dataList.getLength(); j++)
				{
					String dataVal = FusionUtils.getNodeValue(dataList.item(j));
					if( dataVal != null && !dataVal.equals("") )
					{
						col.setRowValue( rowNames.get(j), new Double(dataVal) );
					}
				}
				addGridColumn( col );
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    //***********************************************************************************************************//
    // IColumnGrid impl
    //

	/**
	* Create a new IGridColumn for this grid using the given name, type, and class.
	* The column will *not* be automatically inserted into the Grid, but will be populated with
	* the grid's current rows.
	* 
	* @param name String
	* @param type GridColumnType
	* @param colClass Class
	* 
	* @return IGridColumn
	*/
	public IGridColumn createGridColumn(String name, GridColumnType type, Class colClass)
	{
		String methodName = MODULE_NAME + "createGridColumn(String,GridColumnType, Class)";
		IGridColumn retval = null;

		try
		{
			ArrayList<String> rowNames = new ArrayList<String>();
			Iterator<Object> iter = theRowHeader.getRows().values().iterator();
			while( iter.hasNext() )
			{
				IGridRow r = (IGridRow)iter.next();
				rowNames.add( r.getDisplayName() );
			}

			retval = new GridColumn( name, type, colClass, rowNames );
		} 
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Create a new IGridColumn for this grid using the given name and type and the default column class of Double.
	* The column will *not* be automatically inserted into the Grid, but will be populated with
	* the grid's current rows.
	* 
	* @param name String
	* @param type GridColumnType
	* 
	* @return IGridColumn
	*/
	public IGridColumn createGridColumn(String name, GridColumnType type)
	{
		return createGridColumn( name, type, Double.class );
	}

    /**
    * Get the GridColumns. 
    *
    * @return ArrayList<IGridColumn>
    */
    public ArrayList<IGridColumn> getGridColumns()
    {
        String methodName = MODULE_NAME + "getGridColumns()";
        ArrayList<IGridColumn> retval = new ArrayList<IGridColumn>(theColumns);
        return retval;
    }

    /** 
    * Get the GridColumn by name.
    *
    * @param name String
    *
    * @return IGridColumn
    */
    public IGridColumn getGridColumn(String name)
    {
		String methodName = MODULE_NAME + "getGridColumn(String)";
		IGridColumn retval = null;

		try
		{
			if( name.intern() == IGrid.ROW_LABELS.intern() )
			{
				return theRowHeader;
			}

			Iterator<IGridColumn> iter = theColumns.iterator();
			while( iter.hasNext() )
			{
				IGridColumn col = iter.next();
				if( col.getDisplayName().intern() == name.intern() )
				{
					retval = col;
					break;
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
    * Get Columns by type. Note that the returned list has no bearing on the overall placement of the 
	* contained column objects.
	* 
	* @param type GridColumnType
	* 
	* @return ArrayList<IGridColumn>
    */
	public ArrayList<IGridColumn> getColumnByType(GridColumnType type)
	{
		String methodName = MODULE_NAME + "getColumnByType(GridColumnType)";
		ArrayList<IGridColumn> retval = new ArrayList<IGridColumn>();

		try
		{
			if( type == GridColumnType.ALL )
			{
				retval = getGridColumns();
			}
			else
			{
				Iterator<IGridColumn> iter = getGridColumns().iterator();
				while( iter.hasNext() )
				{
					IGridColumn col = iter.next();
					if( col.getColumnType() == type  )
					{
						retval.add( col );
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
	* Get Columns by types. Note that the returned list has no bearing on the overall placement of the 
	* contained column objects.
	* 
	* @param types EnumSet<GridColumnType>
	* 
	* @return ArrayList<IGridColumn>
	*/
	public ArrayList<IGridColumn> getColumnByType(EnumSet<GridColumnType> types)
	{
		String methodName = MODULE_NAME + "getColumnByType(GridColumnType)";
		ArrayList<IGridColumn> retval = new ArrayList<IGridColumn>();

		try
		{
			if( types.contains(GridColumnType.ALL) )
			{
				retval = getGridColumns();
			}
			else
			{
				Iterator<IGridColumn> iter = getGridColumns().iterator();
				while( iter.hasNext() )
				{
					IGridColumn col = iter.next();
					if( types.contains(col.getColumnType()) )
					{
						retval.add( col );
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
    * Add a GridColumn
    *
    * @param gc IGridColumn
    */
    public void addGridColumn(IGridColumn gc)
    {
		String methodName = MODULE_NAME + "addGridColumn(IGridColumn)";

		try
		{
			gc.setParent( this );
			theColumns.add( gc );

			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
    }

	/**
	* Insert a column before the given column name.
	* 
	* @param col IGridColumn
	* @param colName String 
	*/
	public void insertColumnBefore(IGridColumn col, String colName)
	{
		String methodName = MODULE_NAME + "insertColumnBefore(IGridColumn,String)";

		try
		{
			int index = theColumns.indexOf( getGridColumn(colName) );
			theColumns.add( index, col );
			col.setParent( this );

			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a column before the given index.
	* 
	* @param col IGridColumn
	* @param index int
	*/
	public void insertColumnBefore(IGridColumn col, int index)
	{
		String methodName = MODULE_NAME + "insertColumnBefore(IGridColumn,int)";

		try
		{
			theColumns.add( index, col );
			col.setParent( this );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a column after the given column name.
	* 
	* @param col IGridColumn 
	* @param colName String 
	*/
	public void insertColumnAfter(IGridColumn col, String colName)
	{
		String methodName = MODULE_NAME + "insertColumnAfter(IGridColumn,String)";

		try
		{
			int index = theColumns.indexOf( getGridColumn(colName) ) + 1;
			if( index == theColumns.size() )
			{
				theColumns.addLast( col );
			}
			else
			{
				theColumns.add( index, col );
			}
			col.setParent( this );

			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Insert a column after the given index.
	* 
	* @param col IGridColumn 
	* @param _index int
	*/
	public void insertColumnAfter(IGridColumn col, int _index)
	{
		String methodName = MODULE_NAME + "insertColumnAfter(IGridColumn,int)";

		try
		{
			int index = _index + 1;
			if( index == theColumns.size() )
			{
				theColumns.addLast( col );
			}
			else
			{
				theColumns.add( index, col );
			}
			col.setParent( this );

			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    /**
    * Remove a GridColumn by name.
    *
    * @param name String 
    */
    public void removeGridColumn(String name)
    {
		String methodName = MODULE_NAME + "removeGridColumn(String)";

		try
		{
			IGridColumn col = getGridColumn( name );
			if( col != null )
			{
				col.setParent( null );
				theColumns.remove( col );
				thePlots = null;
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
    }

    /** 
    * Remove a GridColumn by object 
    * 
    * @param dc IGridColumn
    */
    public void removeGridColumn(IGridColumn dc)
    {
		String methodName = MODULE_NAME + "removeGridColumn(IGridColumn)";

		try
		{
			dc.setParent( null );
			theColumns.remove( dc );
			thePlots = null;
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
    }

	/** 
	* Remove a GridColumn by index. 
	* 
	* @param index int
	*/
	public void removeGridColumn(int index)
	{
		String methodName = MODULE_NAME + "removeGridColumn(int)";

		try
		{
			IGridColumn col = theColumns.get(index);
			if( col != null )
			{
				col.setParent( null );
				theColumns.remove( col );
				thePlots = null;
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    /**
    * Generate an IPlotCollection from the Grid.
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
				Iterator<IGridColumn> vIter = getGridColumns().iterator();
				while( vIter.hasNext() )
				{
					IGridColumn col = vIter.next();
					Double tVal = (Double)col.getProperty(IGridColumn.COLUMN_VALUE);
					Boolean includeInPlotCollection = (Boolean)col.getProperty(INCLUDE_IN_PLOT_COLLECTIONS);
	
					Iterator<Map.Entry<String,Object>> runIter = col.getRows().entrySet().iterator();
					while( runIter.hasNext() )
					{
						Map.Entry<String,Object> entry = runIter.next();
						String runName = entry.getKey();
						IPlotData plot = retval.getPlot( runName );
						if( plot == null )
						{
							plot = new PlotData(runName);
							//plot.setProperty(IPlotData.SHAPES_VISIBLE, false );
							//plot.setProperty(IPlotData.PAINT, Color.BLACK );
							retval.addPlot( plot );
						}
	
						if( (entry != null) && (entry.getValue() != null) && (tVal != null) && (includeInPlotCollection == true) )
						{
							plot.getPoints().add( new PointData( tVal.doubleValue(), ((Double)entry.getValue()).doubleValue() ) );
						}
					}
				}

				//Restore data for the Response Reduction wizard if present 
				IPlotData goldCurve = (IPlotData)getProperty(IPlotCollection.GOLD_CURVE);
				if( goldCurve != null )
				{
					retval.addPlot( goldCurve );
				}

				if( getProperty(ResponseReductionWizard.SEGMENT1) != null )
				{
					IPlotMarker marker1 = (IPlotMarker)getProperty(ResponseReductionWizard.SEGMENT1);
					retval.getDomainMarkers().add( marker1 );
				}

				if( getProperty(ResponseReductionWizard.SEGMENT2) != null )
				{
					//Logger.log( methodName + " Adding marker.", Logger.DEBUG );
					IPlotMarker marker2 = (IPlotMarker)getProperty(ResponseReductionWizard.SEGMENT2);
					retval.getDomainMarkers().add( marker2 );
				}

				if( getProperty(ResponseReductionWizard.SEGMENT3) != null )
				{
				   // Logger.log( methodName + " Adding marker.", Logger.DEBUG );
					IPlotMarker marker3 = (IPlotMarker)getProperty(ResponseReductionWizard.SEGMENT3);
					retval.getDomainMarkers().add( marker3 );
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
			Element rootElem = doc.createElement( "FusionAE" );
            doc.appendChild(rootElem);
            appendToXMLDocument(doc, rootElem, type);
			retval = FusionUtils.getXMLString( rootElem.getFirstChild(), true );
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    public void appendToXMLDocument(Document doc, Element parent, int type)
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
					rootElem.setAttribute( iTData.DISPLAY_LABEL, getDisplayName() );
					rootElem.setAttribute( IGrid.MASTER_TOKEN, IGrid.COLUMN_XML_ELEMENT );
					rootElem.setAttribute( IGrid.X_AXIS_TITLE, getStringProperty(IGrid.X_AXIS_TITLE) );
					rootElem.setAttribute( IGrid.Y_AXIS_TITLE, getStringProperty(IGrid.Y_AXIS_TITLE) );
					rootElem.setAttribute( IGrid.COMPOUND_PARENT, getStringProperty(IGrid.COMPOUND_PARENT) );
                    parent.appendChild(rootElem);

					ArrayList<IGridColumn> cols = getGridColumns();
					Integer colCount = new Integer( cols.size() + 1 ); //Have to account for the row labels column.
					Integer rowCount = new Integer( theRowHeader.getRows().size() );
		
					rootElem.setAttribute( IGrid.MASTER_COUNT, colCount.toString() );
					rootElem.setAttribute( IGrid.CHILD_COUNT, rowCount.toString() );

					TestingDesignType dType = (TestingDesignType)getProperty(TESTING_DESIGN_TYPE);
					Logger.log( methodName + " dType: " + dType, Logger.DEBUG );
					if( dType != null )
					{
						switch( dType )
						{
							case TDT_STANDARD_LC:
								rootElem.setAttribute( IGrid.TARGET_OPERATION, IGrid.OPTION_STANDARD_LC );
								//Override for Standard LC.
								rootElem.setAttribute( IGrid.MASTER_COUNT, "1" );
								break;
							case TDT_DESCRIPTIVE_STATISTICS:
								rootElem.setAttribute( IGrid.TARGET_OPERATION, IGrid.OPTION_DESCRIPTIVE_STATISTICS );
								rootElem.setAttribute( IGrid.TEMPLATE_FLAG, "true" );
								break;
							case TDT_DISSOLUTION:
								rootElem.setAttribute( IGrid.TARGET_OPERATION, IGrid.OPTION_DISSOLUTION );
								rootElem.setAttribute( IGrid.TEMPLATE_FLAG, "true" );
								break;
							case TDT_TIME_SERIES:
							default:
								rootElem.setAttribute( IGrid.TARGET_OPERATION, IGrid.OPTION_TIME_SERIES );
								rootElem.setAttribute( IGrid.TEMPLATE_FLAG, "true" );
								break;
						}
					}
		
					//Create Row Labels
					Element colElem = doc.createElement(IGrid.COLUMN_XML_ELEMENT);
					colElem.setAttribute( iTData.TYPE, "DATA" );
					colElem.setAttribute( iTData.TOKEN, IGrid.ROW_LABELS );
					colElem.setAttribute( iTData.DISPLAY_LABEL, getStringProperty("RowDisplayLabel")); // TODO: theResources.getResourceString(IGridProperties.RUN_COLUMN_LABEL)
					colElem.setAttribute( iTData.DATA_TYPE, "STRING" );
					colElem.setAttribute( iTData.POSITION, "1" );
					colElem.setAttribute( iTData.READ_ONLY, "True" );

					//ArrayList<String> sampleIds = (ArrayList<String>)getProperty(IGrid.SAMPLE_IDS);
					Iterator<Object> iter = theRowHeader.getRows().values().iterator();
					int i = 0;
					while( iter.hasNext() )
					{
						IGridRow row = (IGridRow)iter.next();
						Element dataElem = doc.createElement(IGrid.DATA_XML_ELEMENT);
						dataElem.appendChild( doc.createTextNode( row.getDisplayName() ) );
						dataElem.setAttribute( iTData.POSITION, new Integer(i+1).toString() );
						dataElem.setAttribute( iTData.ID, new Integer(i+1).toString() );
						dataElem.setAttribute( iTData.SAMPLE_ID, row.getStringProperty(iTData.SAMPLE_ID) );
						dataElem.setAttribute( IGridRow.ROW_TYPE, row.getStringProperty(IGridRow.ROW_TYPE) );
						dataElem.setAttribute( IGridRow.PARENT_ROW_ID, row.getStringProperty(IGridRow.PARENT_ROW_ID) );
						colElem.appendChild( dataElem );
						i++;
					}

					rootElem.appendChild( colElem );

					Iterator<IGridColumn> colIter = cols.iterator();
					i = 2;
					while( colIter.hasNext() )
					{
						IGridColumn col = colIter.next();
						colElem = doc.createElement( IGrid.COLUMN_XML_ELEMENT );
						colElem.setAttribute( iTData.TYPE, "DATA" );
						colElem.setAttribute( iTData.DATA_TYPE, "DOUBLE" );
						colElem.setAttribute( iTData.POSITION, new Integer(i).toString() );
						colElem.setAttribute( iTData.TOKEN, col.getDisplayName() ); //col.getStringProperty(iTData.TOKEN)
						colElem.setAttribute( iTData.DISPLAY_LABEL, col.getDisplayName() );
						colElem.setAttribute( iTData.PRECISION, col.getStringProperty(iTData.PRECISION) );
						colElem.setAttribute( iTData.UNITS, col.getStringProperty(iTData.UNITS) );
						colElem.setAttribute( IGridColumn.COLUMN_TYPE, col.getStringProperty(IGridColumn.COLUMN_TYPE) );
						if( col.getProperty(IGridColumn.COLUMN_VALUE) != null )
						{
							colElem.setAttribute( IGridColumn.COLUMN_VALUE, col.getStringProperty(IGridColumn.COLUMN_VALUE) );
						}

						//JGD NOTE: For brevity's sake, do we not want to tack on a bunch of data child elements for columns that have no data? 
						//JGD NOTE: Maybe a dirty flag? 
						iter = col.getRows().values().iterator();
						int j = 0;
						while( iter.hasNext() )
						{
							Object obj = iter.next();
							Element dataElem = doc.createElement(IGrid.DATA_XML_ELEMENT);
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
							colElem.appendChild( dataElem );
							j++;
						}
						rootElem.appendChild( colElem );
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
					retval = getXMLString(IGrid.TABLE_DATA_XML_COL);
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
    // IColumnGrid impl ends
}


