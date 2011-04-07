package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* WizardData. A data class to be used in Wizard classes. We really don't need wizard specific classes. It ties us to specific application impl's 
* that tie us to specific application impl. 
* 
* @author Jason Douglas 5/1/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class WizardData
    extends FusionData
{
    /** Mod name */
    private static final String MODULE_NAME                                                                     	= "WizardData.";

	/** THe wizard worker thread. */
	public static final String WIZARD_WORKER																		= "WizardWorker";

    /**
    * Constructor
    */
    public WizardData()
    {
    }
}
