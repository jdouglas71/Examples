package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import java.beans.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.data.*;

/**
* IEditorPanel. Interface for the generic editor panels that display some date for editing or viewing.<br><br>
* 
* NOTE: getComponent will provide a JComponent that contains all the various components that make up the 
* editor panel. For most purposes this is sufficient. There are cases, however, where the editor panel consists of 
* a JLabel and some JComponent (e.g. JComboBox or JTextField) and the caller needs access to the individual components
* in order to properly leverage a GridBagLayout and get everything to line up (e.g. the User Tab). In that case, the 
* caller can use the LABEL and LABEL_COMPONENT property to retrieve the individual JComponents (provided, of course, 
* that the implementor has made those properties available). JGD 4/29/04 <br><br>
*
* @author Jason Douglas 10/27/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IEditorPanel
	extends IFusionView
{
	//JGD NOTE: None of these properties are guarenteed to be set. Always test for null return values.
    /** Panel name */
    public static final String PANEL_NAME                       = "PanelName";
    /** Inital Focus property */
    public static final String INIT_FOCUS                       = "InitFocus";
    /** Label component property */
    public static final String LABEL_COMPONENT                  = "LabelComponent";
    /** Data type property */
    public static final String DATA_TYPE                        = "DataType";
    /** Title property */
    public static final String TITLE                            = "Title";
    /** Prompt property */
    public static final String PROMPT                           = "Prompt";
    /** First panel in a wizard sequence */
    public static final String FIRST_PANEL                      = "FirstPanel";
    /** last Panel in a wizard sequence */
    public static final String LAST_PANEL                       = "LastPanel";
    /** Display Name (Used when minimized) */
    public static final String DISPLAY_NAME                     = "DisplayName";
	/** Parent Component */
	public static final String PARENT							= "ParentComponent";
	/** Selected Items. Implementation specific as to what that really means. */
	public static final String SELECTED_ITEMS					= "SelectedItems";
	/** Panel hash key (String) */
	public static final String PANEL_HASH_KEY					= "PanelHashKey";
	/** UPdate required flag */
	public static final String UPDATE_REQUIRED					= "UpdateRequired";
	/** Panel is editing an existing data object */
	public static final String EDITING_EXISTING_DATA 			= "EditingExistingData";

    /**
    * Validate contained portion of the GOO vs data model
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents(boolean forceMsg);

    /**
    * Validate the contents without necessarily forcing a validation message for the user.
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents();

    /**
    * Save the values in the contained GOO elements to the data model.
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents(boolean forceMsg);

    /**
    * Save the contents without forcing a validation message for the user.
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents();

    /**
    * Determine if the data presented to the user by this component has been modified.
    *
    * @return boolean True if contents have been modified by the user. 
    */
    public boolean hasBeenModified();

    /**
    * Set the editable flag on the panel. If false, the input components will be disabled. This is not the same as disabling 
    * the entire panel, which disables ALL components in the panel.
    *
    * @param b boolean
    */
    public void setEditable(boolean b);
                                        
}

