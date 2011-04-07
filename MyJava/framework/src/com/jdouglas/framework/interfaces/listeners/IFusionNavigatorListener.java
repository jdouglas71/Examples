package com.jdouglas.framework.interfaces.listeners;

import java.util.*;

import com.jdouglas.framework.core.events.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* IFusionNavigatorListener. Listener class for the navigators. Allows the navigator component to be anything, and the navigator
* can internally handle the specific change events and then broadcast it's own events. I think that's cool!
* 
* @author Jason Douglas 5/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionNavigatorListener
{
    /**
    * The navigator selection has been changed. 
    *
    * @param nce NavigatorChangeEvent
    */
    public void navigatorSelectionChanged(NavigatorChangeEvent nce);
}

