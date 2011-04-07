package com.jdouglas.framework.util;

/**
* ThreadSentry. A sentry class that can be used btwn threads to prevent race conditions. 
* 
* Adapted from "Java Threads"  ISBN 1-56592-418-5
*
* @author Jason Douglas
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ThreadSentry
{
	/** Module name */
	private static final String MODULE_NAME																 = "ThreadSentry.";

	/** the sentry */
	private Thread theSentry = null;
	/** THe counter */
	private int sentryCount = 0;

	/**
	* Get the sentry. 
	*/
	public synchronized void getSentry()
	{
		String methodName = MODULE_NAME + "getSentry()";

		//Keep trying to get the sentry until you get one.
		while( tryGetSentry() == false )
		{
			try
			{
				wait();
			}
			catch(Exception e)
			{
				//Don't care.
			}
		}
	}

	/**
	* Free the sentry.
	*/
	public synchronized void freeSentry()
	{
		String methodName = MODULE_NAME + "freeSentry()";

		//Frees the sentry and kills it if the counter is 0.
		if( getSentryOwner() == Thread.currentThread() )
		{
			sentryCount--;
			if( sentryCount == 0 )
			{
				theSentry = null;
				notify();
			}
		}
	}

	/** 
	* Internal method used to attempt to secure the sentry.
	*/
	private synchronized boolean tryGetSentry()
	{
		String methodName = MODULE_NAME + "tryGetSentry()";
		boolean retval = false;

		if( theSentry == null )
		{
			//No sentry, set it and go.
			theSentry = Thread.currentThread();
			sentryCount = 1;
			retval = true;
		}
		else if( theSentry == Thread.currentThread() )
		{
			//We are the thread that currently has the lock, so just increment the counter.
			sentryCount++;
			retval = true;
		}
		else
		{
			//We are NOT the thread that currently has the sentry, therefore we cannot get it and we must wait.
			retval = false;
		}
		

		return retval;
	}

	/**
	* Get the owner of sentry
	*
	* @return Thread Owner of the sentry.						
	*/
	private synchronized Thread getSentryOwner()
	{
		return theSentry;
	}
}
