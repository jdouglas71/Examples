package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.listeners.*;

/**
* IFusionNavigator. The navigator interface. A work in progress.
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public interface IFusionNavigator
{
    //Lots of stuff. Definitely a listener interface.

    /**
    * Get the navigator component.
    *
    * @return JComponent The navigator component. 
    */
    public JComponent getNavigatorComponent();

    /**
    * Add a Navigator listener.
    * 
    * @param l IFusionNavigatorListener The listener to add. 
    */
    public void addFusionNavigatorListener(IFusionNavigatorListener l);

    /**
    * Remove a Navigator Listener
    *
    * @param l IFusionNavigatorListener The listener to remove. 
    */
    public void removeFusionNavigatorListener(IFusionNavigatorListener l);

    /**
    * Add a listener to the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void addListener(Object listener, Class listenerType);

    /**
    * Remove a listener to the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void removeListener(Object listener, Class listenerType);
}
