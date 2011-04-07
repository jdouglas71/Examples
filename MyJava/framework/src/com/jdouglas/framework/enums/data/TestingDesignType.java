package com.jdouglas.framework.enums.data;

/**
* TestingDesignType. Enum describing the state of an IVariable. 
*
* @author Jason Douglas 9/12/07
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum TestingDesignType
{       
    /** The values */
    UNKNOWN(-1),
    /** Standard LC (1)*/
    TDT_STANDARD_LC(1),
    /** DISSOLUTION (2) */
    TDT_DISSOLUTION(2),
	/** Description Statistics (3) */
	TDT_DESCRIPTIVE_STATISTICS(3),
	/** Time Series (4) */
	TDT_TIME_SERIES(4);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private TestingDesignType(int _id) 
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
    * @return TestingDesignType
    */
    public static TestingDesignType getTestingDesignType(Integer id)
    {
        switch( id.intValue() )
        {
            case 1:
                return TDT_STANDARD_LC;
            case 2:
                return TDT_DISSOLUTION;
			case 3:
				return TDT_DESCRIPTIVE_STATISTICS;
			case 4:
				return TDT_TIME_SERIES;
			default:
                return UNKNOWN;
        }
    }
};

