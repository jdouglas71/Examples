package com.jdouglas.framework.core.events;

import java.util.*;
import javax.swing.event.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* WizardEvent. Event wrapper for FusionNavigatorListeners.
*
* @author Jason Douglas 5/14/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class WizardEvent
	extends FusionEvent
{
    /** Module Name */
    private static final String MODULE_NAME                                                                 = "WizardEvent.";

	/** Wizard */
	public static final String WIZARD																	  	= "Wizard";
	/** Wizard Data */
	public static final String WIZARD_DATA																	= "WizardData";

	/** Success flag */
	private boolean successFlag = false;

    /**
    * Constructor
    * 
    * @param wiz IWizard
    * @param data iTData
	* @param success boolean 
    */
    public WizardEvent(IWizard wiz, iTData data, boolean success)
    {
        setProperty( WIZARD, wiz );
        setProperty( WIZARD_DATA, data );
		successFlag = success;
    }

    /**
    * Private default ctor.
    */
    private WizardEvent()
    {   
        //Don't call this
    }

    /**
    * Get the wizard.
    * 
    * @return IWizard
    */
    public IWizard getWizard()
    {
        return (IWizard)getProperty(WIZARD);
    }

    /** 
    * Get the Wizard Data
    *
    * @return iTData
    */
    public iTData getWizardData()
    {
        return (iTData)getProperty(WIZARD_DATA);
    }

	/**
    * Get the state of the success flag. 
	* 
	* @return boolean
    */
	public boolean getSuccessFlag()
	{
		return successFlag;
	}

}

