package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.plots.*;
import com.jdouglas.framework.util.*;


/**
* IntegerValueData. 
* 
* @author Jason Douglas 12/3/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class IntegerValueData
    extends ValueData<Integer>
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "IntegerValueData.";

    /**
    * Constructor.
    *
	* @param name String 
    * @param val Integer
	* @param precision Integer
	* @param units String 
    */
    public IntegerValueData(String name, Integer val, Integer precision, String units)
    {
		super(name,val,precision,units);
    }

	/**
	* Get the Value.
	* 
	* @return int
	*/
	public int getValue()
	{
		String methodName = MODULE_NAME + "getValue()";
		int retval = -1;

		try
		{
			Integer val = (Integer)getProperty(DATA_VALUE);
			if( val != null )
			{
				retval = val.intValue();
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}
}




