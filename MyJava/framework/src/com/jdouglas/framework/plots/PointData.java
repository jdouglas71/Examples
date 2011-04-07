package com.jdouglas.framework.plots;

import java.util.*;
import java.awt.*;
import java.awt.geom.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;

/**
* PointData. A FusionData wrapper around a series of XY points.
*
* @author Jason Douglas 1/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PointData
    extends FusionData
        implements IPointData
{
    /** Module name */
    private static final String MODULE_NAME                                                                 = "PointData";

    /** the point */
    private Point2D thePoint;

    /**
    * Ctor.
    * 
    * @param x double
    * @param y double
    */
    public PointData(double x, double y)
    {
        thePoint = new Point2D.Double(x,y);
    }

    //********************************************************************************************//
    // IPointData impl
    /**
    * Get the X value.
    *
    * @return double
    */
    public double getX()
    {
        return thePoint.getX();
    }

    /**
    * Get the Y value.
    *
    * @return double
    */
    public double getY()
    {
        return thePoint.getY();
    }
    // IPointData impl ends

	/**
	* String representation.  
	*  
	* @return String
    */
	public String toString()
	{
		return new String( "(" + getX() + "," + getY() + ")" );
	}
}

