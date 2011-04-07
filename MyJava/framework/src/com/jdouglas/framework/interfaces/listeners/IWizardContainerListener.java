package com.jdouglas.framework.interfaces.listeners;

import com.jdouglas.framework.core.events.*;

/**
* IWizardContainerListener. Listener class for the wizard container..
* 
* @author Jason Douglas 4/2/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IWizardContainerListener
{
    /**
    * Wizard Container has closed.
	* 
	* @param evt WizardContainerEvent
    */
    public void wizardContainerClosed(WizardContainerEvent evt);
}

