package com.jdouglas.framework.enums.data;

import java.util.*;

import com.jdouglas.framework.util.*;

/**
* InstrumentType. The supported instrument types for FA\FAE.
*
* @author Jason Douglas 8/2/07
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum InstrumentType
{       
    /** The values */
    UNKNOWN(-1),
	/** Includes all types */
	ALL(0),
	/** High Performance Liquid Chromotograhpy */
    HPLC(1), 
	/** Gas Chromotograhpy */
    GC(2), 
	/** Dissolution */
	DISSOLUTION(3),
	/** Impactor @deprecated */ 
	@Deprecated
	IMPACTOR(4),
	/** Impinger @deprecated */
	@Deprecated
	IMPINGER(5),
	/** RRLC */
	RRLC(6),
	/** UPLC */
	UPLC(7),
	/** Generic */
	GENERIC(8),
	/** Tablet Press*/
	TABLET_PRESS(9),
	/** Tablet Coater*/
	TABLET_COATER(10),
	/** Synthetic Chemistry Reactor */ 
	SYNTHETIC_CHEMISTRY_REACTOR(11),
	/** Solid Phase Extraction Apparatus */
	SPEA(12),
	/** USP Apparatus 1 */
	FIT_USP_APPARATUS_1(13),
	/** USP Apparatus 2 MODEL 160*/
	FIT_USP_APPARATUS_2_MODEL_160(14),
	/** USP Apparatus 3 */
	FIT_USP_APPARATUS_3(15),
	/** USP Apparatus 4 */
	FIT_USP_APPARATUS_4(16),
	/** USP Apparatus 5 */
	FIT_USP_APPARATUS_5(17),
	/** USP Apparatus 6 */
	FIT_USP_APPARATUS_6(18),
	/** Pheur Apparatus A */
	FIT_PHEUR_APPARATUS_A(19),
	/** Dissolution USP Apparatus 1 (Basket) */
	DISSOLUTION_USP_APPARATUS_1(20),
	/** Dissolution USP Apparatus 2 (Paddle) */
	DISSOLUTION_USP_APPARATUS_2(21),
	/** CSR Reactor */
	CSR_REACTOR(22),
	/** USP Apparatus 2 MODEL 150*/
	FIT_USP_APPARATUS_2_MODEL_150(23),
	/** USP Apparatus 2 MODEL 150P*/
	FIT_USP_APPARATUS_2_MODEL_150P(24);

	/** Module name */
	private static final String MODULE_NAME = "InstrumentType";
	/** We need a representation that can be saved in the database */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private InstrumentType(int _id) 
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
    public static InstrumentType getInstrumentType(Integer id)
    {
        switch( id.intValue() )
        {
			case 0:
				return ALL;
			case 1:
                return HPLC;
            case 2:
                return GC;
			case 3:
				return DISSOLUTION;
			case 4:
				return IMPACTOR;
			case 5:
				return IMPINGER;
			case 6:
				return RRLC;
			case 7:
				return UPLC;
			case 8:
				return GENERIC;
			case 9:
				return TABLET_PRESS;
			case 10:
				return TABLET_COATER;
			case 11:
				return SYNTHETIC_CHEMISTRY_REACTOR;
			case 12:
				return SPEA;
			case 13:
				return FIT_USP_APPARATUS_1;
			case 14:
				return FIT_USP_APPARATUS_2_MODEL_160;
			case 15:
				return FIT_USP_APPARATUS_3;
			case 16:
				return FIT_USP_APPARATUS_4;
			case 17:
				return FIT_USP_APPARATUS_5;
			case 18:
				return FIT_USP_APPARATUS_6;
			case 19:
				return FIT_PHEUR_APPARATUS_A;
			case 20:
				return DISSOLUTION_USP_APPARATUS_1;
			case 21:
				return DISSOLUTION_USP_APPARATUS_2;
			case 22:
				return CSR_REACTOR;
			case 23:
				return FIT_USP_APPARATUS_2_MODEL_150;
			case 24:
				return FIT_USP_APPARATUS_2_MODEL_150P;
			default:
                return UNKNOWN;
        }
    }
};

