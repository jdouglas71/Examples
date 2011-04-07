package com.jdouglas.framework.plots;

import java.util.*;
import java.awt.*;
import java.awt.geom.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;

/**
* PlotData. A FusionData wrapper around a series of XY points.
*
* @author Jason Douglas 1/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotData
    extends FusionData
        implements IPlotData
{
    /** Module name */
    private static final String MODULE_NAME                                                                 = "PlotData";

    /** the points array */
    private ArrayList<IPointData> thePoints = new ArrayList<IPointData>();

    /**
    * Ctor.
    * 
    * @param name String
    */
    public PlotData(String name)
    {
        setProperty( PLOT_NAME, name );
		setProperty( DISPLAY_NAME, name );
        setProperty( STROKE, null );
        setProperty( OUTLINE_STROKE, null );
        setProperty( LINES_VISIBLE, new Boolean(true) );
        setProperty( SHAPES_VISIBLE, new Boolean(true) );
        setProperty( SHAPE, null );
        setProperty( VISIBLE_IN_LEGEND, new Boolean(true) );
    }

    //********************************************************************************************//
    // IPlotData impl
    //
    /**
    * Get the points in the plot.
    * 
    * @return ArrayList<IPointData>
    */
    public ArrayList<IPointData> getPoints()
    {
        return thePoints;
    }

    /**
    * Set the points for this plot.
    *
    * @param points ArrayList<IPointData>
    */
    public void setPoints(ArrayList<IPointData> points)
    {
        thePoints = points;
    }

	/**
	* Find the Point in this plot for the given X value, if it exists.
	*
	* @param x double 
	*  
	* @return IPointData
	*/
	public IPointData findPointForX(double x)
	{
		String methodName = MODULE_NAME + "findPointForX(double)";
		IPointData retval = null;

		Iterator<IPointData> iter = thePoints.iterator();
		while( iter.hasNext() )
		{
			IPointData pt = iter.next();
			if( pt.getX() == x )
			{
				retval = pt;
				break;
			}
		}

		return retval;
	}



    // IPlotData impl ends

    /**
    * String representation
    * 
    * @return String
    */
    public String toString()
    {
        return getStringProperty( PLOT_NAME );
    }
}

