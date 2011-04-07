package com.jdouglas.framework.util.math;

import java.awt.*;
import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.util.*;

/**
* MathResources. Resources common to the framework
*
* @author Jason Douglas 11/14/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class MathResources   
    extends FusionResources
        implements IMathProperties
{
    /** Module Name */
    private static final String MODULE_NAME                                                             = "MathResources.";

    /**
    * Constructor
    */
    protected MathResources()
    {
        try
        {
            setBundleName( BUNDLE_NAME );
			setResourceBaseClass(com.jdouglas.framework.core.FusionApplication.class);

			setDefaultValue( SUM_OF_SQUARES_ERROR, "Sum of Squares for Y divided by the mean of the Y values is less than " );
			setDefaultValue( SUM_OF_SQUARES_MEAN_ERROR, "Sum of Squares for Y divided by the mean of the Y values is less than " );
			setDefaultValue( MISSING_VAL_ERROR, "There is no point for value %VAL% in the target profile." );
			setDefaultValue( LESS_THAN_ZERO_IN_WEIBULL_ERROR, "The Weibull parameters cannot be calculated with values less than zero." );

        }
        catch(Exception e) 
        {
            FusionUtils.logError( MODULE_NAME, "failed", e );
        }
    }

}
