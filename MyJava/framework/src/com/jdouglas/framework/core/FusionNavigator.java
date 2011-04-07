package com.jdouglas.framework.core;

import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.events.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* FusionNavigator. Abstract Base class for IFusionNavigator derivatives.
*
* @author Jason Douglas 5/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionNavigator
        implements IFusionNavigator
{
    /** Module Name */
    private static final String MODULE_NAME               = "FusionNavigator.";

    /** Navigator listeners */
    protected ArrayList<IFusionNavigatorListener> theListeners = new ArrayList<IFusionNavigatorListener>();
    /** dirty flag */
    protected boolean theDirtyFlag = false;

    //********************************************************************************************//
    // IFusionNavigator impl (partial)
    //

    /**
    * Add a Navigator listener.
    * 
    * @param l IFusionNavigatorListener The listener to add. 
    */
    public void addFusionNavigatorListener(IFusionNavigatorListener l) 
    {
        theListeners.add( l );
    }

    /**
    * Remove a Navigator Listener
    *
    * @param l IFusionNavigatorListener The listener to remove. 
    */
    public void removeFusionNavigatorListener(IFusionNavigatorListener l) 
    {
        theListeners.remove( l );
    }

    // IFusionNavigator impl ends 

    /**
    * Fire an selection change event.
    *
    * @param nce NavigatorChangeEvent
    */
    public void fireNavigatorSelectionChange(NavigatorChangeEvent nce)
    {
        String methodName = MODULE_NAME + "fireNavigatorSelectionChange(NavigatorChangeEvent)";

        try
        {
            Iterator<IFusionNavigatorListener> iter = theListeners.iterator();
            while( iter.hasNext() )
            {
                IFusionNavigatorListener l = iter.next();
                l.navigatorSelectionChanged( nce );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Add a listener to the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void addListener(Object listener, Class listenerType)
    {
        String methodName = MODULE_NAME + "setListener(Object,Class)";

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Remove a listener from the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void removeListener(Object listener, Class listenerType)
    {
        String methodName = MODULE_NAME + "removeListener(Object,Class)";

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

	// IFusionNavigator impl endsl


 }
