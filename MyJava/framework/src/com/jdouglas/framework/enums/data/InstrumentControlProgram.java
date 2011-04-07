package com.jdouglas.framework.enums.data;

/**
* InstrumentControlProgram. The enumeration for InstrumentControlPrograms.
*
* @author Jason Douglas 10/30/06
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum InstrumentControlProgram
{       
    /** Unknown (-1)*/
    UNKNOWN(-1),
    /** Formerly "FLAVORLESS". Unused at this time. (0)*/
    GENERIC(0), 
    /** TotalChrom (1)*/
    TOTALCHROM(1), 
    /** Empower and Millenniuum (2)*/
    EMPOWER(2), 
    /** Varian Galaxie (3)*/
    GALAXIE(3), 
    /** Tablet coater (Created for RV for demo purposes) (4)*/
	@Deprecated
    TUCKER_TABLET(4), 
    /** Chemical (Created for RV for demo purposes) (5)*/
	@Deprecated
    TUCKER_CHEMICAL(5),
	/** Inhaler Testing for Andersen Analysis (6)*/
	INHALER(6),
	/** Tablet */
	TABLET(7),
	/** Chemical Synthesis Reactor */
	CSR(8),
	/** Dissolution */ 
	DISSOLUTION(9),
	/** Solid Phase Extraction */
	SPEA(10),
	/** Dionex Chromeleon*/
	CHROMELEON(11);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private InstrumentControlProgram(int _id) 
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
    * @return ICP
    */
    public static InstrumentControlProgram getICP(Integer id)
    {
        switch( id.intValue() )
        {
            case 0:
                return GENERIC;
            case 1:
                return TOTALCHROM;
            case 2:
                return EMPOWER;
            case 3:
                return GALAXIE;
            case 4:
                return TUCKER_TABLET;
            case 5:
                return TUCKER_CHEMICAL;
			case 6:
				return INHALER;
			case 7:
				return TABLET;
			case 8:
				return CSR;
			case 9:
				return DISSOLUTION;
			case 10:
				return SPEA;
			case 11:
				return CHROMELEON;
            default:
                return UNKNOWN;
        }
    }
};

