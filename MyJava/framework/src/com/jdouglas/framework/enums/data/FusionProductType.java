package com.jdouglas.framework.enums.data;

/**
* FusionProductType. An enum describing the Products of FusionAE.
*
* @author Jason Douglas 8/2/07
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum FusionProductType
{       
    /** The values */
    UNKNOWN(-1),
	/** Value to represent all products*/
	ALL(0),
	/** Analytical R&D */
    ANALYTICAL_RnD(1), 
	/** Drug Product R&D */
    DRUG_PRODUCT_RnD(2), 
	/** Chemical R&D */
    CHEMICAL_RnD(3),
	/** Quality Assurance */
	QUALITY_ASSURANCE(4),
	/** General Applications */
	GENERAL_APPLICATIONS(5);

	/** Use an int internally so we have something concrete to save\restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private FusionProductType(int _id) 
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
    * @return FusionProductType
    */
    public static FusionProductType getProduct(Integer id)
    {
        switch( id.intValue() )
        {
			case 0:
				return ALL;
			case 1:
                return ANALYTICAL_RnD;
            case 2:
                return DRUG_PRODUCT_RnD;
            case 3:
                return CHEMICAL_RnD;
			case 4:
				return QUALITY_ASSURANCE;
			case 5:
				return GENERAL_APPLICATIONS;
            default:
                return UNKNOWN;
        }
    }
};

