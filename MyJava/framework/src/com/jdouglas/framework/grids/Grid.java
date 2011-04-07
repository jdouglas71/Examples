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

import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.enums.data.*;

/**
* Grid. An FAE Grid. First pass
*
* @author Jason Douglas 4/16/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class Grid
    extends FusionData
        implements IGrid
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "Grid.";

    /**
    * Constructor.
    *
    * @param name String
    */
    public Grid(String name)
    {
        setProperty( DISPLAY_NAME, name );
        setProperty( X_AXIS_TITLE, "X-Axis" );
        setProperty( Y_AXIS_TITLE, "Y-Axis" );
    }

    //***********************************************************************************************************//
    // IGrid impl
    //

    // IGrid impl ends
}


