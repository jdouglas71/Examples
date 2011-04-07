package com.jdouglas.framework.interfaces.listeners;

import com.jdouglas.framework.core.events.*;

/**
* IWizardListener. Listener class for the wizards.
* 
* @author Jason Douglas 1/16/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IWizardListener
{
    /**
    * Wizard has completed.
	* 
	* @param evt WizardEvent
    */
    public void wizardFinished(WizardEvent evt);
}

