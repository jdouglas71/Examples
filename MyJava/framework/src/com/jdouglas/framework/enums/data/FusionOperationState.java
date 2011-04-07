package com.jdouglas.framework.enums.data;

/**
* FusionOperationState. An Enumeration for Operation states in Fusion AE. Corresponds to the FusionOperationState enum defined in
* SMXExt.IActivityControl.
*
* @author Jason Douglas 2/7/08
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum FusionOperationState
{       
	/** Locked */
    LOCKED(-1),
    /** Incomplete */
	INCOMPLETE(0),
	/** Review Pending */
	REVIEW_PENDING(1),
	/** Review Rejected */
	REVIEW_REJECTED(2),
	/** Review Accepted */
	REVIEW_ACCEPTED(3),
	/** Approval Pending */
	APPROVAL_PENDING(4),
	/** Approval Rejected */
	APPROVAL_REJECTED(5),
	/** Approval Accepted */
	APPROVAL_ACCEPTED(6),
    /** Successful */
	SUCCESSFUL(7);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private FusionOperationState(int _id) 
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
    * @return FusionOperationState
    */
    public static FusionOperationState getOperationState(Integer id)
    {
        switch( id.intValue() )
        {
			case -1:
				return LOCKED;
			case 0:
				return INCOMPLETE;
			case 1:
				return REVIEW_PENDING;
			case 2:
				return REVIEW_REJECTED;
			case 3:
				return REVIEW_ACCEPTED;
			case 4:
				return APPROVAL_PENDING;
			case 5:
				return APPROVAL_REJECTED;
			case 6:
				return APPROVAL_ACCEPTED;
			case 7:
				return SUCCESSFUL;
			default:
				return LOCKED;
        }
    }
};

