package com.jdouglas.framework.plots;

import java.util.*;
import java.awt.*;
import java.awt.geom.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* PlotCollection. A FusionData wrapper around a collection of plots. 
*
* @author Jason Douglas 1/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotCollection 
    extends FusionData
        implements IPlotCollection
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "PlotCollection.";

    /** Map of the plots */
    private LinkedHashMap<String,IPlotData> thePlots = new LinkedHashMap<String,IPlotData>();
    /** List of Range Markers */
    private ArrayList<IPlotMarker> theRangeMarkers = new ArrayList<IPlotMarker>();
    /** List of domain Markers */
    private ArrayList<IPlotMarker> theDomainMarkers = new ArrayList<IPlotMarker>();

    /**
    * Ctor.
    *
    * @param xAxisTitle String
    * @param yAxisTitle String
    */
    public PlotCollection(String xAxisTitle, String yAxisTitle)
    {
        setProperty( X_AXIS_TITLE, xAxisTitle );
        setProperty( Y_AXIS_TITLE, yAxisTitle );
        setProperty( BACKGROUND_PAINT, Color.white );
        setProperty( GRIDLINE_PAINT, Color.black );
        setProperty( GRIDLINES_VISIBLE, new Boolean(false) );
    }

    /** 
    * Default ctor.
    */
    public PlotCollection()
    {
        this( "", "" );
    }

    //************************************************************************************************************//
    // IPlotCollection impl
    //

    /**
    * Get the IPlotData objects.
    *
    * @return ArrayList<IPlotData>
    */
    public ArrayList<IPlotData> getPlots()
    {
		String methodName = MODULE_NAME + "getPlots()";
		ArrayList<IPlotData> retval = new ArrayList<IPlotData>();

		try
		{
			//Make sure the gold curve is first in the list if it exists. Not restricting a collection to a single gold curve.
			Iterator<IPlotData> iter = thePlots.values().iterator();
			while( iter.hasNext() )
			{
				IPlotData plot = iter.next();
				if( plot.getProperty(GOLD_CURVE) != null )
				{
					retval.add( 0, plot );
				}
				else
				{
					retval.add( plot );
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
    * Add to the plots.
    *
    * @param plot IPlotData
    */
    public void addPlot(IPlotData plot)
    {
        String methodName = MODULE_NAME + "addPlot(IPlotData)";

        //For now, I'm making the assumption that the x/y axis titles of the collection supercede\match the ones in the plots

        plot.setProperty( IPlotData.X_AXIS_TITLE, getStringProperty(X_AXIS_TITLE) );
        plot.setProperty( IPlotData.Y_AXIS_TITLE, getStringProperty(Y_AXIS_TITLE) );

		thePlots.put( plot.getStringProperty(IPlotData.PLOT_NAME), plot );

    }

    /**
    * Remove a plot from the collection.
    *
    * @param plot IPlotData
    */
    public void removePlot(IPlotData plot)
    {
        thePlots.remove( plot.getStringProperty(IPlotData.PLOT_NAME) );
    }

    /**
    * Access a specific plot by NAME.
    *
    * @param name String
    *
    * @return IPlotData. Null if a plot corresponding to the given name does not exist.
    */
    public IPlotData getPlot(String name)
    {
        return thePlots.get( name );
    }

    /** 
    * Returns an ArrayList of range markers for the plot collection.
    *
    * @return ArrayList<IPlotMarker>
    */
    public ArrayList<IPlotMarker> getRangeMarkers()
    {
        return theRangeMarkers;
    }

    /** 
    * Sets the range markers for the plot collection.
    *
    * @param markers ArrayList<org.jfree.chart.Marker>
    */
    public void setRangeMarkers(ArrayList<IPlotMarker> markers)
    {
        theRangeMarkers = markers;
    }

    /** 
    * Returns an ArrayList of domain markers for the plot collection.
    *
    * @return ArrayList<IPlotMarker>
    */
    public ArrayList<IPlotMarker> getDomainMarkers()
    {
        return theDomainMarkers;
    }

    /** 
    * Sets the domain markers for the plot collection.
    *
    * @param markers ArrayList<IPlotMarker>
    */
    public void setDomainMarkers(ArrayList<IPlotMarker> markers)
    {
        theDomainMarkers = markers;
    }

    // IPlotCollection impl ends
}

