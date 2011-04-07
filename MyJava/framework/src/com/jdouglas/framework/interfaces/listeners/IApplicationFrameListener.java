package com.jdouglas.framework.interfaces.listeners;

/**
* IApplicationFrameListener. Listener class for the ApplicationFrame. 
* 
* @author Jason Douglas 3/22/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IApplicationFrameListener
{
    /**
    * Let the listeners know that the wait state has been changed to the given value.
    * 
    * @param waitState boolean The current value of the frame's waitState.
    */
    public void waitStateChanged(boolean waitState);
}
