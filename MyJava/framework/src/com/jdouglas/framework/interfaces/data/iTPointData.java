package com.jdouglas.framework.interfaces.data;

/**
* IPointData. iTData wrapper around an X, Y point. Not more than a thin wrapper around the Point class, but I needed a
* visible flag and that's built into iTData so I wrapped it.
*
* @author Jason Douglas 1/30/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IPointData 
    extends iTData
{

    /**
    * Get the X value.
    *
    * @return double
    */
    public double getX();

    /**
    * Get the Y value.
    *
    * @return double
    */
    public double getY();
}

