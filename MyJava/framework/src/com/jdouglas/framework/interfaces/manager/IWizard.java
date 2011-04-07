package com.jdouglas.framework.interfaces.manager;

import javax.swing.*;

import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* IWizard. Wizard controller interface for interacting with the IWizardContainer. Basically acts as the parent of the dialog and allows 
* the impl to validate and verify panel changes (veto too).
*
* @author Jason Douglas 9/28/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IWizard
{
	/** Wizard settings xml Document */
	public static final String SETTINGS_XML_DOCUMENT															= "settingsXMLDocument";

    /**
    * Get the next panel in the sequence. If this is the last panel, IEditorPanel.LAST_PANEL should be set in the panel properties.
    *
    * @return IEditorPanel Null if the panel change has been rejected by the Wizard.
    */
    public IEditorPanel nextPanel();

    /**
    * Get the previous panel in the sequence. If this is the first panel, IEditorPanel.FIRST_PANEL should be set in the panel properties.
    *
    * @return IEditorPanel Null if the panel change has been rejected by the wizard.
    */
    public IEditorPanel previousPanel();

    /**
    * Set the IWizardContainer pointer for the wizard. 
    *
    * @param container IWizardContainer
    */
    public void setWizardContainer(IWizardContainer container);

    /** 
    * Set the next and back buttons.
    *
    * @param backButton JButton
    * @param nextButton JButton
    */ 
    public void setButtons(JButton backButton, JButton nextButton);

    /**
    * Set the wizard title. This is the base title used in the wizard dialog. Panel titles will be appended to this 
    * string. 
    *
    * @param title String 
    */ 
    public void setWizardTitle(String title);

    /**
    * Get the wizard title.
    *
    * @return String 
    */ 
    public String getWizardTitle();

	/**
	* Get Wizard Name
	*
	* @return String 
	*/
	public String getWizardName();

	/** 
	* Add a wizard listener.
	* 
	* @param l IWizardListener
	*/
	public void addWizardListener(IWizardListener l);

	/** 
	* Remove a wizard Listener
	* 
	* @param l IWizardListener
	*/
	public void removeWizardListener(IWizardListener l);
}
