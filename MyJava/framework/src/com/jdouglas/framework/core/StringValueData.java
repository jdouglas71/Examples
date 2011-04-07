package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.plots.*;
import com.jdouglas.framework.util.*;


/**
* StringValueData. Generic Value data class.
*
* @author Jason Douglas 12/3/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class StringValueData
    extends ValueData<String>
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "StringValueData.";

    /**
    * Constructor.
    *
	* @param name String 
    * @param val String
	* @param precision Integer
	* @param units String 
    */
    public StringValueData(String name, String val, Integer precision, String units)
    {
		super(name,val,precision,units);
    }

	/**
	* Get the Value.
	* 
	* @return String
	*/
	public String getValue()
	{
		String methodName = MODULE_NAME + "getValue()";
		String retval = "";

		try
		{
			retval = getStringProperty(DATA_VALUE);
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}
}




