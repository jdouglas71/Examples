package com.jdouglas.framework.core.events;

import java.util.*;
import javax.swing.event.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* WizardContainerEvent. Event wrapper for FusionNavigatorListeners.
*
* @author Jason Douglas 5/14/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class WizardContainerEvent
	extends FusionEvent
{
    /** Module Name */
    private static final String MODULE_NAME                                                                 = "WizardContainerEvent.";

	/** Wizard Container */
	public static final String WIZARD_CONTAINER															  	= "WizardContainer";

    /**
    * Constructor
    * 
    * @param container IWizardContainer
    */
    public WizardContainerEvent(IWizardContainer container)
    {
        setProperty( WIZARD_CONTAINER, container );
    }

    /**
    * Private default constructor.
    */
    private WizardContainerEvent()
    {   
        //Don't call this
    }

    /**
    * Get the wizard Container.
    * 
    * @return IWizardContainer
    */
    public IWizardContainer getWizardContainer()
    {
        return (IWizardContainer)getProperty(WIZARD_CONTAINER);
    }
}

