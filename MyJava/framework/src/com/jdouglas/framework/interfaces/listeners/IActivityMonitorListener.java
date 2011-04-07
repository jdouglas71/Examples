package com.jdouglas.framework.interfaces.listeners;

import com.jdouglas.framework.interfaces.manager.*;

/**
* IActivityMonitorListener. Listener class for the managers. Mostly a way for interdependent managers to broadcast updates.
* 
* @author Jason Douglas 9/28/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IActivityMonitorListener
{
    /**
    * The timeout has occurred
    */
    public void timeout();
}

