package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.plots.*;
import com.jdouglas.framework.util.*;


/**
* ValueData. Generic Value data class.
*
* @author Jason Douglas 12/3/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ValueData<V>
    extends FusionData
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "ValueData.";

    /**
    * Constructor.
    *
	* @param name String 
    * @param val V
	* @param precision Integer
	* @param units String 
    */
    public ValueData(String name, V val, Integer precision, String units)
    {
		setProperty( DISPLAY_NAME, name );
		setProperty( DATA_VALUE, val );
		setProperty( PRECISION, precision );
		setProperty( UNITS, units );
    }

	/**
	* Get the Value.
	* 
	* @return V
	*/
	@SuppressWarnings("unchecked")
	public V getLDataValue()
	{
		String methodName = MODULE_NAME + "getDataValue()";
		V retval = null;

		try
		{
			V val = (V)getProperty(DATA_VALUE);
			if( val != null )
			{
				retval = val;
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}
}




