package com.jdouglas.framework.interfaces.view;

import java.util.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* IEditorPanelTracker. A tracker object for a toplevel container data object that tracks and sorts any IEditorPanel's 
* associated with or created for the data object or one of it's elements.
*
* @author Jason Douglas 3/15/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IEditorPanelTracker
{
    /**
    * Set the data model. Setting the data model will clear the internal storage of panels.                    
    *
    * @param data iTData
    */
    public void setDataModel(iTData data);

    /**
    * Get the data model.
    *
    * @return iTData
    */
    public iTData getDataModel();

    /**
    * A Set containing all the editor panels for the contained data model.
    *
    * @return Set<IEditorPanel>
    */
    public Set<IEditorPanel> getAllEditorPanels();

    /**
    * Get the Set of IEditorPanels for the given category.
    *
    * @param category String
    * 
    * @return Set<IEditorPanel> 
    */
    public Set<IEditorPanel> getEditorPanels(String category);

    /**
    * Add an editor Panel for the given category.
    *
    * @param panel IEditorPanel
    * @param category String 
    */
    public void addEditorPanel(IEditorPanel panel, String category);

    /**
    * Remove the given panel from the given category.
    *
    * @param panel IEditorPanel
    * @param category String
    *
    * @return boolean True if removal succeeded.
    */
    public boolean removeEditorPanel(IEditorPanel panel, String category);

}
