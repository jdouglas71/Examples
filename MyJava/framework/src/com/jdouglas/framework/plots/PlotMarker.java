package com.jdouglas.framework.plots;

import java.util.*;
import java.awt.*;
import java.awt.geom.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.enums.data.*;

import org.jfree.chart.plot.*;

/**
* PlotMarker. A FusionData wrapper around a JFreeChart Marker
*
* @author Jason Douglas 1/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotMarker
    extends FusionData
        implements IPlotMarker
{
    /** Module name */
    private static final String MODULE_NAME                                                                 = "PlotMarker";

    /** the Marker */
    private Marker theMarker;

	/** the type */
	private PlotMarkerType theType;

    /**
    * Ctor.
    * 
    * @param marker Marker
    */
    public PlotMarker(Marker marker)
    {
        theMarker = marker;
    }

    //********************************************************************************************//
    // IPlotMarker impl
    //

    /**
    * Get the Marker object.
    * 
    * @return Marker
    */
    public Marker getMarker()
    {
        return theMarker;
    }

    // IPlotMarker impl ends
}

