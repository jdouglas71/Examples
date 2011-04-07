package com.jdouglas.framework.interfaces.data;

import java.awt.*;
import java.awt.geom.*;
import java.util.*;

/**
* IPlotData. Interface for a data object representing a series of points that can plotted on a graph/chart. The NAME property
* will be used to track individual plots and should be set.
*
* @author Jason Douglas 1/18/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IPlotData
    extends iTData
{
    /** The following are plot attributes used when displaying the plot in a chart. */

    /** Plot name */
    public static final String PLOT_NAME                                = "PlotName";
    /** The java.awt.Stroke object used to create the line from point to point */
    public static final String STROKE                                   = "Stroke";
    /** the java.awt.Stroke object used to outline the point shapes */
    public static final String OUTLINE_STROKE                           = "OutlineStroke";
    /** Determines if the lines btwn the points are drawn. Boolean */
    public static final String LINES_VISIBLE                            = "LinesVisible";
    /** The java.awt.Shape object used to draw the points */
    public static final String SHAPE                                    = "Shape";
    /** Determines whether or not the plot is shown in the legend. Boolean */
    public static final String VISIBLE_IN_LEGEND                        = "VisibleInLegend";
    /** the Paint object used to paint the plot */
    public static final String PAINT                                    = "Paint";
    /** Determine whether or not to show the shapes for the plot, Boolean */
    public static final String SHAPES_VISIBLE                           = "ShapesVisible";
    /** Annotation information. org.jfree.chart.annotation.XYAnnotation */
    public static final String ANNOTATION                               = "Annotation";
    /** X-Axis title */
    public static final String X_AXIS_TITLE                             = "XAxisTitle";
    /** Y-Axis title */
    public static final String Y_AXIS_TITLE                             = "YAxisTitle";
    

	//JGD LAZY PROGRAMMER!!! Need adders and removers so we can track changes.

    /**
    * Get the points in the plot.
    * 
    * @return ArrayList<IPointData>
    */
    public ArrayList<IPointData> getPoints();

    /**
    * Set the points for this plot.
    *
    * @param points ArrayList<IPointData>
    */
    public void setPoints(ArrayList<IPointData> points);

	/**
    * Find the Point in this plot for the given X value, if it exists.
	*
	* @param x double
	*  
	* @return IPointData
    */
	public IPointData findPointForX(double x);
}
