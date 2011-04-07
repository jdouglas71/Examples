package com.jdouglas.framework.enums.data;

/**
* FusionApplicationModule. The enumeration for Fusion Application Modules (FAM). 
* 
* @author Jason Douglas 11/2/06
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum FusionApplicationModule
{       
    /** Unknown (-1) */
    UNKNOWN(-1),
    /** There in case we need it. Not really used at this point. (0)*/
    ALL_MODULES(0), 
    /** Method Development Professional (1)*/
    METHOD_DEVELOPMENT_PRO(1), 
    /** Method Validation Professional (2)*/
    METHOD_VALIDATION_PRO(2),
	/** Fusion Synthesis (3)*/
	FUSION_SYNTHESIS(3),
	/** Tableting R&D  (Tucker Demo for RV, Not currently production level) (4)*/
	TABLETING_RnD(4),
	/** Tablet Coating (Tucker Demo for RV, Not currently production level) (5)*/
	TABLET_COATING(5),
	/** Inhaler Testing Professional (6)*/
	INHALER_TESTING_PRO(6),
	/** Inhaler Testing Lite (7)*/
	INHALER_TESTING_LITE(7),
	/** Method Developement Lite (8)*/
	METHOD_DEVELOPMENT_LITE(8),
	/** Method Validation Lite (9)*/
	METHOD_VALIDATION_LITE(9),
	/** Fusion Product Development */
	FUSION_PRO(10), //JGD TODO: Change
	/** Fusion Product Development Lite */
	FUSION_PRO_LITE(11); //JGD TODO: Change 

    //Coming soon, Process development (various types), Fusion Pro

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private FusionApplicationModule(int _id) 
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
    * @return FusionApplicationModule
    */
    public static FusionApplicationModule getFAM(Integer id)
    {
        switch( id.intValue() )
        {
            case 0:
                return ALL_MODULES;
            case 1:
                return METHOD_DEVELOPMENT_PRO;
            case 2:
                return METHOD_VALIDATION_PRO;
			case 3:
				return FUSION_SYNTHESIS;
			case 4:
				return TABLETING_RnD;
			case 5:
				return TABLET_COATING;
			case 6:
				return INHALER_TESTING_PRO;
			case 7:
				return INHALER_TESTING_LITE;
			case 8:
				return METHOD_DEVELOPMENT_LITE;
			case 9:
				return METHOD_VALIDATION_LITE;
			case 10:
				return FUSION_PRO;
			case 11:
				return FUSION_PRO_LITE;
            default:
                return UNKNOWN;
        }
    }
};

