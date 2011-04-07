package com.jdouglas.framework.util;

import javax.swing.SwingUtilities;

/**
* This is the 3rd version of SwingWorker (also known as
* SwingWorker 3), an abstract class that you subclass to
* perform GUI-related work in a dedicated thread.  For
* instructions on and examples of using this class, see:
* 
* http://java.sun.com/docs/books/tutorial/uiswing/misc/threads.html
*
* Note that the API changed slightly in the 3rd version:
* You must now invoke start() on the SwingWorker after
* creating it. <br><br>
* 
* JGD: Copied from http://java.sun.com/docs/books/tutorial/uiswing/misc/example-1dot4/SwingWorker.java.
* See http://java.sun.com/docs/books/tutorial/uiswing/misc/threads.html#SwingWorker for examples on use.
*
* JGD: Added daemon flag. 9/30/04 
*  
* JGD: Renamed to FusionWorker to get around name conflict with 
* Java 6. 
*
* @author Jason Douglas 
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionWorker 
{
    /** Module name */
    private static final String MODULE_NAME  = "FusionWorker.";
	/** Thread number */
	public static int threadNum = 0; //JGD NOTE: Public for testing only

	/** The value. See getValue(), setValue() */
    private Object value; 

    /** 
    * Class to maintain reference to current worker thread
    * under separate synchronization control.
    */
    private static class ThreadVar 
    {
        private Thread thread;
        ThreadVar(Thread t)
        {
            thread = t;
        }
        synchronized Thread get()
        {
            return thread;
        }
        synchronized void clear()
        {
            thread = null;
        }
    }

    private ThreadVar threadVar;
    private boolean useDaemonThreads = false;

    /**
    * Creates a worker that when started will call the construct method, invoke the finished method on the AWT thread 
    * (via SwingUtilities.invokeLater()) and then exit. The daemon parameter determines whether the worker threads are 
    * set to be daemon threads.
    *
    * @param useDaemon boolean If true, use daemon threads as the worker threads.
    */
    public FusionWorker(boolean useDaemon)
    {
        useDaemonThreads = useDaemon;

        //Anonymous Runnable class for running the finished method.
        final Runnable doFinished = new Runnable()
        {
            public void run()
            {
                finished();
            }
        };

        //Anonymous runnable class for running the construct method.
        Runnable doConstruct = new Runnable()
        {
            public void run()
            {
                try
                {
                    setValue(construct());
                }
                finally
                {
                    threadVar.clear();
                }

                SwingUtilities.invokeLater(doFinished);
            }
        };

		String threadName = "FusionWorker-" + (threadNum++);
        Thread t = new Thread(doConstruct, threadName );
        t.setDaemon( useDaemonThreads );
        threadVar = new ThreadVar(t);
    }

    /**
    * Ctor creates a worker that does not use daemon theads (meaning it won't prevent termination of the 
    * main thread if still running).
    */
    public FusionWorker()
    {
        this( false );
    }

    /** 
    * Get the value produced by the worker thread, or null if it 
    * hasn't been constructed yet.
    */
    protected synchronized Object getValue() 
    {
        return value; 
    }

    /** 
    * Set the value produced by worker thread 
    */
    private synchronized void setValue(Object x) 
    {
        value = x; 
    }

    /** 
    * Compute the value to be returned by the <code>get</code> method. 
    */
    public abstract Object construct();

    /**
    * Called on the event dispatching thread (not on the worker thread)
    * after the <code>construct</code> method has returned.
    */
    public void finished() 
    {
    }

    /**
    * A new method that interrupts the worker thread.  Call this method
    * to force the worker to stop what it's doing.
    */
    public void interrupt() 
    {
        Thread t = threadVar.get();
        if( t != null )
        {
            t.interrupt();
        }
        threadVar.clear();
    }

    /**
    * Return the value created by the <code>construct</code> method.  
    * Returns null if either the constructing thread or the current
    * thread was interrupted before a value was produced.
    * 
    * @return the value created by the <code>construct</code> method
    */
    public Object get()
    {
        while( true )
        {
            Thread t = threadVar.get();
            if( t == null )
            {
                return getValue();
            }
            try
            {
                t.join();
            }
            catch( InterruptedException e )
            {
                Thread.currentThread().interrupt(); // propagate
                return null;
            }
        }
    }

    /**
    * Start the worker thread.
    */
    public void start()
    {
        Thread t = threadVar.get();
        if( t != null )
        {
            t.start();
            t.yield();
        }
    }
}
