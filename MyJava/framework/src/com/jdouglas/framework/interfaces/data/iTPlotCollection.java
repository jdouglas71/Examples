package com.jdouglas.framework.interfaces.data;

import java.util.*;

/**
* IPlotCollection. A collection of IPlotData objects. The JFreeChart control can display multiple plots so we need a 
* iTData object to contain the data. Plot objects are stored in a map using their NAME property.
*
* @author Jason Douglas 1/18/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IPlotCollection
    extends iTData
{
    /** THe chart title */
    public static final String CHART_TITLE                              = "ChartTitle";
    /** the chart subtitle */
    public static final String CHART_SUB_TITLE                          = "ChartSubTitle";
    /** The source title */
    public static final String CHART_SOURCE_TITLE                       = "ChartSourceTitle";
    /** X-Axis title */
    public static final String X_AXIS_TITLE                             = "XAxisTitle";
    /** Y-Axis title */
    public static final String Y_AXIS_TITLE                             = "YAxisTitle";
    /** Plot background paint. java.awt.Paint */
    public static final String BACKGROUND_PAINT                         = "BackgroundPaint";
    /** Gridline paint. java.awt.Paint */
    public static final String GRIDLINE_PAINT                           = "GridlinePaint";
    /** Gridlines visible. Boolean */
    public static final String GRIDLINES_VISIBLE                        = "GridlinesVisible";
    /** RangeMarkers (yAxis) for the plot. ArrayList<org.jfree.chart.Marker> */
    public static final String RANGE_MARKERS                            = "RangeMarkers";
    /** Domain Markers (xAxis) for the plot. ArrayList<org.jfree.chart.Marker> */
    public static final String DOMAIN_MARKERS                           = "DomainMarkers";
    /** Gold Curve IPlotData */
    public static final String GOLD_CURVE                               = "GoldCurve";

    /**
    * Get the IPlotData objects.
    *
    * @return ArrayList<IPlotData>
    */
    public ArrayList<IPlotData> getPlots();

    /**
    * Add to the plots.
    *
    * @param plot IPlotData
    */
    public void addPlot(IPlotData plot);

    /**
    * Remove a plot from the collection.
    *
    * @param plot IPlotData
    */
    public void removePlot(IPlotData plot);

    /**
    * Access a specific plot by NAME.
    *
    * @param name String
    *
    * @return IPlotData. Null if a plot corresponding to the given name does not exist.
    */
    public IPlotData getPlot(String name);

    /** 
    * Returns an ArrayList of range (Y-axis) markers for the plot collection.
    *
    * @return ArrayList<org.jfree.chart.Marker>
    */
    public ArrayList<IPlotMarker> getRangeMarkers();

    /** 
    * Sets the range (y-axis) markers for the plot collection.
    *
    * @param markers ArrayList<org.jfree.chart.Marker>
    */
    public void setRangeMarkers(ArrayList<IPlotMarker> markers);

    /** 
    * Returns an ArrayList of domain (x-axis) markers for the plot collection.
    *
    * @return ArrayList<org.jfree.chart.Marker>
    */
    public ArrayList<IPlotMarker> getDomainMarkers();

    /** 
    * Sets the domain (x-axis) markers for the plot collection.
    *
    * @param markers ArrayList<org.jfree.chart.Marker>
    */
    public void setDomainMarkers(ArrayList<IPlotMarker> markers);
}
