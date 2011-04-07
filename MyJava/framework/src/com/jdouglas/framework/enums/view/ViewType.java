package com.jdouglas.framework.enums.view;

/**
* View types. This is just a first pass. 
* 
* @author Jason Douglas 8/15/07
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum ViewType
{       
    /** The values */
    UNKNOWN(-1),
	/** Generic */
    GENERIC(0),
	/** View only */
	VIEW_ONLY(1),
	/** Editor */
	EDITOR(2),
	/** Tree view */
	TREE(3),
	/** Table view */
	TABLE(4),
	/** Dialog view */
	DIALOG(5);
	

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private ViewType(int _id) 
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
    public static ViewType getICP(Integer id)
    {
        switch( id.intValue() )
        {
            case 0:
                return GENERIC;
            case 1:
                return VIEW_ONLY;
            case 2:
                return EDITOR;
            case 3:
                return TREE;
            case 4:
                return TABLE;
            case 5:
                return DIALOG;
            default:
                return UNKNOWN;
        }
    }
};

