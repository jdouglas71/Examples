package com.jdouglas.framework.messages;

import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* ErrorTab. Skeleton impl for now using an infopanel. Soon to be a tree. 
*
* @author Jason Douglas 4/10/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class ErrorTab    
	extends TabPage
        implements IFusionTab
{
    /** module name */
    private static final String MODULE_NAME                                                         = "ErrorTab.";

    /** the info panel */
    private InfoPanel infoPanel = new InfoPanel();

	/**
	* Default Ctor
	*/
	public ErrorTab()
	{
		super( "Error", 'E', null, null );
		tabElementName = MODULE_NAME;
		tabComponent = infoPanel;
	}

    /**
    * Set the text of the infopanel
    *
    * @param text String
    */
    public void setInfoText(String text)
    {
        infoPanel.setText( text );
    }

	//************************************************************************************************//
	// IFusionTab impl 
	// 

    //************************************************************************************************//
    // IApplicationFrameListener impl
    //
    /**
    * Let the listeners know that the wait state has been changed to the given value.
    * 
    * @param waitState boolean The current value of the frame's waitState.
    */
    public void waitStateChanged(boolean waitState)
    {

    }
    // IApplicationFrameListener impl ends

    //*************************************************************************************************//
    // IValidator impl
    //
    /**
    * This call comes from a selection model. The params Map allows various information to be passed to the valiators. 
    * Returning false will cause the selection model from blocking the change of selection indices, so use the power wisely.
    * 
    * @param params Map<Object,Object> Constraints and other types of information necessary to validate.
    *
    * @return boolean True if the validation passed. 
    */
    public boolean validateContents(java.util.Map<Object,Object> params)
    {
        return true;
    }
    // IValidator impl ends

    //************************************************************************************************//
    // ChangeListener impl
    //
    /**
    * Invoked when the target of the listener has changed its state.
    *
    * @param e  a ChangeEvent object
    */
    public void stateChanged(ChangeEvent e)
    {
    }
    // ChangeListener impl 
    // IFusionTab impl ends
}
