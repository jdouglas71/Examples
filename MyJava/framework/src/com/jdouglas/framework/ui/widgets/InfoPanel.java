package com.jdouglas.framework.ui.widgets;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.border.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.data.*;

/**
* InfoPanel. An Information Panel. Can be used as a straight component or via the IEditorPanel interface. 
*
* @author Jason Douglas 5/18/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class InfoPanel
    extends EditorPanel
        implements IEditorPanel
{
	/** Module Name */
    private static final String MODULE_NAME                 = "InfoPanel.";

	/** the text area */
    private JTextArea theArea;

    /**
    * Ctor.
    */
    public InfoPanel()
    {
        super();
        initPanel();
    }

    /**
    * Initialize the panel.
    */
    private void initPanel()
    {
        String methodName = MODULE_NAME + "initPanel()";

        setLayout( new BorderLayout() );

        theArea = new JTextArea();
        theArea.setLineWrap(true);
        theArea.setWrapStyleWord(true);
        theArea.setEditable( false );
        theArea.setMargin( new Insets(1,2,1,1) );
        theArea.setBorder( new EmptyBorder(new Insets(1,1,1,1)) );

        add( new JScrollPane(theArea), BorderLayout.CENTER );
        //add( theArea, BorderLayout.CENTER );
    }

    /**
    * Set the Text.
    * 
    * @param text String 
    */             
    public void setText(String text)
    {
        theArea.setText( text );
    }

    /**
    * Set the title.
    *
    * @param title String 
    */
    public void setTitle(String title)
    {
        setBorder( new TitledBorder( title ) );
    }

    //***********************************************************************************//
    // IEditorPanel impl
    //
    /**
    * Refresh the contained goo elements based on the current configuration/data model.
    */
    public void refreshContents()
    {
        //Nothing to do here. 
    }

    /**
    * Validate contained portion of the GOO vs data model
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents(boolean forceMsg)
    {
        String methodName = MODULE_NAME + "validateContents(boolean)";
        boolean retval = true;

        //Nothing to validate

        return retval;
    }

    /**
    * Validate the contents without necessarily forcing a validation message for the user.
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents()
    {
        return validateContents( false );
    }

    /**
    * Save the values in the contained GOO elements to the data model.
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents(boolean forceMsg)
    {
        String methodName = MODULE_NAME + "saveContents(boolean)";
        boolean retval = true;

        //Nothing to save. This panel is informational only.

        return retval;
    }

    /**
    * Save the contents without forcing a validation message for the user.
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents()
    {
        return saveContents(false);
    }

    /**
    * Resets the panel contents to the values stored in the data model.
    */
    public void resetContents()
    {
        String methodName = MODULE_NAME + "resetContents()";
    }

    /**
    * Determine if the data presented to the user by this component has been modified.
    *
    * @return boolean True if contents have been modified by the user. 
    */
    public boolean hasBeenModified()
    {
        String methodName = MODULE_NAME + "hasBeenModifed()";
        boolean retval = false;

        //Nothing to modify

        return retval;
    }

    /**
    * Get the Component/View.
    * 
    * @return JComponent The view Component. 
    */                 
    public JComponent getComponent()
    {
        return this;
    }

    /**
    * Retrieve the data model.
    * 
    * @return iTData The data model.
    */
    public iTData getDataModel()
    {
        return null;
    }

    /**
    * Set the Data Model.
    * 
    * @param data iTData The Data model.
    */
    public void setDataModel(iTData data)
    {
        //Ignoring.
    }

    /**
    * Enable\Disable the Panel. This means no validation, editing, saving, etc.
    *
    * @param b boolean 
    */
    public void setPanelEnabled(boolean b)
    {
        theArea.setEnabled( b );
    }

    // IEditorPanel Impl ends
}
