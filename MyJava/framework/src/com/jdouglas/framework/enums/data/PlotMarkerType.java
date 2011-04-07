package com.jdouglas.framework.enums.data;

/**
* PlotMarkerCategory. The types of PlotMarkers available.
*
* @author Jason Douglas 2/16/07
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum PlotMarkerType
{       
    /** The values */
    UNKNOWN(-1),
    CATEGORY(0),
    INTERVAL(1),
    VALUE(2);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private PlotMarkerType(int _id) 
    {
        id = _id;
    }

    /**
    * Gets the id. 
    * @return int The id.
    */
    public int getID()
    {
        return id;
    }

    /**
    * Get the enum value that corresponds to the given Integer. We need this because we store the value
    * as an integer. 
    *
    * @param id Integer (take advantage of autoboxing)
    * @return PlotMarkerType
    */
    public static PlotMarkerType getType(Integer id)
    {
        switch( id.intValue() )
        {
            case 0:
                return CATEGORY;
            case 1:
                return INTERVAL;
            case 2:
                return VALUE;
            default:
                return UNKNOWN;
        }
    }
};

