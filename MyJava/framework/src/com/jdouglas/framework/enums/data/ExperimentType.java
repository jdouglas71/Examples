package com.jdouglas.framework.enums.data;

/**
* ExperimentType. An Enumeration for Experiment Types in Fusion AE. Corresponds to the FCExperimentTypeEnum defined in
* SMXExt.IActivityControl.
*
* @author Jason Douglas 2/7/08
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum ExperimentType
{       
    /** The values */
    UNKNOWN(-1),
	/** Method Development */
	METHOD_DEVELOPMENT(1),
	/** Final Phase */
	METHOD_VALIDATION_FINAL_PHASE(2),
	/** Early Phase */
	METHOD_VALIDATION_EARLY_PHASE(3),
	/** Fusion Pro */
	STANDARD_DOE(4),
	/** THis name is just a placeholder until RV gives me a real name.*/
	INHALER_TESTING(6),
	/** Fusion Pro */
	FUSION_PRO(10);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private ExperimentType(int _id) 
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
    * @return ExperimentType
    */
    public static ExperimentType getExperimentType(Integer id)
    {
        switch( id.intValue() )
        {
            case 1:
                return METHOD_DEVELOPMENT;
            case 2:
                return METHOD_VALIDATION_FINAL_PHASE;
			case 3:
				return METHOD_VALIDATION_EARLY_PHASE;
			case 4:
				return STANDARD_DOE;
			case 6:
				return INHALER_TESTING;
			case 10:
				return FUSION_PRO;
            default:
                return UNKNOWN;
        }
    }
};

