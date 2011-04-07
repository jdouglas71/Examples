package com.jdouglas.framework.interfaces.listeners;

import com.jdouglas.framework.interfaces.manager.*;

/**
* IFusionManagerListener. Listener class for the managers. Mostly a way for interdependent managers to broadcast updates.
* 
* @author Jason Douglas 5/27/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionManagerListener
{
    /**
    * The manager's internal state (meaning its contained objects) has been updated.
    *
    * @param man IFusionManager The manager that was updated. 
    */
    public void managerUpdated(IFusionManager man);
}

