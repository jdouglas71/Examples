package com.jdouglas.framework.core.events;

import java.util.*;
import javax.swing.event.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* NavigatorChangeEvent. Event wrapper for FusionNavigatorListeners.
*
* @author Jason Douglas 5/14/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class NavigatorChangeEvent
	extends FusionEvent
{
    /** Module Name */
    private static final String MODULE_NAME                                                                 = "NavigatorChangeEvent.";

    /** The originating event */
    public static final String EVENT                                                                        = "TheEvent";
    /** The originating navigator */
    public static final String NAVIGATOR                                                                    = "theNavigator";
	/** The parent */
	public static final String PARENT																		= "theParent";

    /**
    * Constructor
    * 
    * @param nav IFusionNavigator
    * @param ev EventObject
    */
    public NavigatorChangeEvent(IFusionNavigator nav, EventObject ev)
    {
        setProperty( NAVIGATOR, nav );
        setProperty( EVENT, ev );
    }

    /**
    * Private default ctor.
    */
    private NavigatorChangeEvent()
    {   
        //Don't call this
    }

    /**
    * Get the initial event object that triggered this event.
    * 
    * @return EventObject
    */
    public EventObject getEvent()
    {
        return (EventObject)getProperty(EVENT);
    }

    /** 
    * Get the navigator for this event.
    *
    * @return IFusionNavigator
    */
    public IFusionNavigator getNavigator()
    {
        return (IFusionNavigator)getProperty( NAVIGATOR );
    }

}

