package com.jdouglas.framework.interfaces.props;

import java.util.*;

/**
* IUtilConstants. Common constants.
* @author Jason Douglas
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IUtilConstants
{
    /** Close States and Button Constants */
    public static final int ID_FAILED                                       = -1;
    public static final int ID_OK                                           = 0;
    public static final int ID_CANCEL                                       = 1;
    public static final int ID_HELP                                         = 2;
    public static final int ID_YES                                          = 3;
    public static final int ID_NO                                           = 4;
    public static final int ID_NEXT                                         = 5;
    public static final int ID_BACK                                         = 6;
    public static final int ID_FINISH                                       = 7;
    public static final int ID_APPLY                                        = 8;
	public static final int ID_TIMEOUT										= 9;
	public static final int ID_EXIT											= 10;

    /** Message types */
    public static final int NORMAL_MESSAGE                                  = 0;
    public static final int ERROR_MESSAGE                                   = 1;

	/** Exit codes */
	public static final int NORMAL_EXIT										= 0;
	public static final int ERROR_EXIT										= 1;
	public static final int LOCKDOWN_EXIT									= 2;

	/** Version attribute */
	public static final String PROGRAM_VERSION								= "ProgramVersion";
}
