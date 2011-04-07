package com.jdouglas.framework.enums.data;

/**
* ProgramMode. The current running mode of the program. 
*
* @author Jason Douglas 2/7/08
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum ProgramMode
{       
    /** The values */
    UNKNOWN(-1),
	/** Lite */
	LITE(1),
	/** Professional */
	PROFESSIONAL(2);


    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private ProgramMode(int _id) 
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
    * @return ProgramMode
    */
    public static ProgramMode getProgramMode(Integer id)
    {
        switch( id.intValue() )
        {
            case 1:
                return LITE;
            case 2:
                return PROFESSIONAL;
            default:
                return UNKNOWN;
        }
    }
};

