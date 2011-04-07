package com.jdouglas.framework.interfaces.data;

import java.util.*;

import org.jfree.chart.plot.*;

/**
* IPlotMarker. A wrapper around the Marker objects used in JFreeChart. 
*
* @author Jason Douglas 2/16/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IPlotMarker
    extends iTData
{
    /**
    * Get the Marker.
    * 
    * @return Marker
    */
    public Marker getMarker();
}
