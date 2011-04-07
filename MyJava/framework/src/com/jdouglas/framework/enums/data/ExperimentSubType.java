package com.jdouglas.framework.enums.data;

/**
* ExperimentSubType. An Enumeration for Experiment Types in Fusion AE. Corresponds to the FCExperimentSubTypeEnum defined in
* SMXExt.IActivityControl.
*
* @author Jason Douglas 2/7/08
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum ExperimentSubType
{       
    /** The values */
    UNKNOWN(-1),
	NONE(0),
	RMDP_I(98),
	RMDB_II(99),
	SCREENING(100),
	OPTIMIZATION(101),
	ACCURACY(102),
	LINEARITY_AND_RANGE(103),
	REPEATABILITY(104),
	ACCURACY_LINEARITY_AND_RANGE_REPEATABILITY(105),
	ROBUSTNESS(106),
	INTERMEDIATE_PRECISION_AND_REPRODUCIBILITY(107),
	SYSTEM_SUITABILITY_CHECK(108),
	FILTER_VALIDATION(109),
	SPECIFICITY(110),
	SAMPLE_SOLUTION_STABILITY(111),
	/** This is a placeholder name until RV gives me a real one*/
	INHALER_TESTING(199);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private ExperimentSubType(int _id) 
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
    * @return ExperimentSubType
    */
    public static ExperimentSubType getExperimentSubType(Integer id)
    {
        switch( id.intValue() )
        {
			case 0:
				return NONE;
			case 98:
				return RMDP_I;
			case 99:
				return RMDB_II;
			case 100:
				return SCREENING;
			case 101:
				return OPTIMIZATION;
			case 102:
				return ACCURACY;
			case 103:
				return LINEARITY_AND_RANGE;
			case 104:
				return REPEATABILITY;
			case 105:
				return ACCURACY_LINEARITY_AND_RANGE_REPEATABILITY;
			case 106:
				return ROBUSTNESS;
			case 107:
				return INTERMEDIATE_PRECISION_AND_REPRODUCIBILITY;
			case 108:
				return SYSTEM_SUITABILITY_CHECK;
			case 109:
				return FILTER_VALIDATION;
			case 110:
				return SPECIFICITY;
			case 111:
				return SAMPLE_SOLUTION_STABILITY;
			case 199:
				return INHALER_TESTING;
            default:
                return UNKNOWN;
        }
    }
};

