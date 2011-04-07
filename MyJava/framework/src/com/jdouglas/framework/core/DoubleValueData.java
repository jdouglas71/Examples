package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.plots.*;
import com.jdouglas.framework.util.*;


/**
* DoubleValueData. Generic Value data class.
*
* @author Jason Douglas 12/3/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class DoubleValueData
    extends ValueData<Double>
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "DoubleValueData.";

    /**
    * Constructor.
    *
	* @param name String 
    * @param val Double
	* @param precision Integer
	* @param units String 
    */
    public DoubleValueData(String name, Double val, Integer precision, String units)
    {
		super(name,val,precision,units);
    }

	/**
	* Get the Value.
	* 
	* @return double
	*/
	public double getValue()
	{
		String methodName = MODULE_NAME + "getValue()";
		double retval = -1.0;

		try
		{
			Double val = (Double)getProperty(DATA_VALUE);
			if( val != null )
			{
				retval = val.doubleValue();
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}
}




