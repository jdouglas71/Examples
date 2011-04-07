package com.jdouglas.framework.util;

import java.util.*;
import java.awt.*;
import java.awt.event.*;

import com.jdouglas.framework.interfaces.listeners.*;

/**
* ActivityMonitor. Monitors activity on the AWT thread and notifies any listeners when activity has ceased for 
* the given period.
* 
* @author Jason Douglas 9/28/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ActivityMonitor
		implements AWTEventListener
{
	/** Module name */
	private static final String MODULE_NAME											= "ActivityMonitor.";

	/** THe events we're listening for to determine activity */
	private long[] theEvents = {
								 AWTEvent.ACTION_EVENT_MASK,
								 // AWTEvent.ADJUSTMENT_EVENT_MASK,
								 AWTEvent.COMPONENT_EVENT_MASK,
								 // AWTEvent.CONTAINER_EVENT_MASK,
								 AWTEvent.FOCUS_EVENT_MASK,
								 // AWTEvent.HIERARCHY_BOUNDS_EVENT_MASK,
								 // AWTEvent.HIERARCHY_EVENT_MASK,
								 AWTEvent.INPUT_METHOD_EVENT_MASK,
								 // AWTEvent.INVOCATION_EVENT_MASK,
								 AWTEvent.ITEM_EVENT_MASK,
								 AWTEvent.KEY_EVENT_MASK,
								 AWTEvent.MOUSE_EVENT_MASK,
								 AWTEvent.MOUSE_MOTION_EVENT_MASK,
								 AWTEvent.MOUSE_WHEEL_EVENT_MASK,
								 AWTEvent.PAINT_EVENT_MASK,
								 AWTEvent.TEXT_EVENT_MASK,
								 AWTEvent.WINDOW_EVENT_MASK,
								 AWTEvent.WINDOW_FOCUS_EVENT_MASK,
								 AWTEvent.WINDOW_STATE_EVENT_MASK 
							   };


	/** Listeners */
	private ArrayList<IActivityMonitorListener> theListeners = new ArrayList<IActivityMonitorListener>();
	/** time out */
	protected long theTimeout;
	/** the counter */
	protected long theCounter;

	/**
    * Ctor.
	* 
	* @param timeout long
    */
	public ActivityMonitor(long timeout)
	{
		theTimeout = timeout;
		theCounter = 0;

		Toolkit toolkit = Toolkit.getDefaultToolkit();
		for(int i=0; i<theEvents.length; i++)
		{
			toolkit.addAWTEventListener(this, theEvents[i]);
		}

		new Thread(new Runnable()
		{
			public void run()
			{
				while(true)
				{
					//Logger.log( "Ping!!! " + theCounter, Logger.DEBUG );
					if( theCounter++ >= theTimeout )
					{

						fireTimeoutEvent();
						theCounter = 0;
					}
					 
					try
					{
						Thread.sleep(1000);
					}
					catch(InterruptedException ie)
					{
						System.err.println(ie.getMessage());
					}
				}//end while
			}//end run
		 }).start();//start thread 
	}

	/**
	* Add a Monitor listener.
	* 
	* @param l IActivityMonitorListener The listener to add. 
	*/
	public void addActivityMonitorListener(IActivityMonitorListener l) 
	{
		theListeners.add( l );
	}

	/**
	* Remove a Monitor Listener
	*
	* @param l IActivityMonitorListener The listener to remove. 
	*/
	public void removeActivityMonitorListener(IActivityMonitorListener l) 
	{
		theListeners.remove( l );
	}

	/**
	* Fire an update.
	*/
	public void fireTimeoutEvent()
	{
		String methodName = MODULE_NAME + "fireTimeoutEvent()";

		try
		{
			Iterator<IActivityMonitorListener> iter = theListeners.iterator();
			while( iter.hasNext() )
			{
				Logger.log( methodName + " Firing Timeout!!!", Logger.DEBUG );
				IActivityMonitorListener l = iter.next();
				l.timeout();
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	//******************************************************************************************************//
	// AWTEventListener impl
	// 
	/**
	* Invoked when an event is dispatched in the AWT.
	* 
	* @param event AWTEvent 
	*/
	public void eventDispatched(AWTEvent event)
	{
		String methodName = MODULE_NAME + "eventDispatched(AWTEvent)";

		theCounter = 0;
	}
	// AWTEventListener impl ends
}


