package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.ui.dialogs.*;

/**
* Generic Splash window can be turned off programatically or times out via a thread. <br><br>
*
* @author Jason Douglas 9/19/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class SplashWindow
    extends JWindow
        implements Runnable
{
	/** Module name */
    private static final String MODULE_NAME = "SplashWindow.";
	/** THread name */
    public static final String THREAD_NAME = "SplashThread";

	/** Image label */
    private JLabel imageLabel;
	/** timeout */
    private int timeout = 30000;
	/** THread to close the Goo */
    private CloserRunner closerRunner;

    /**
    * Ctor. Create a splash window displaying the given imageFileName and for the duration of the timout param.
	* 
	* @param imageFileName String 
	* @param _timeout int
	* @param parent Window
	* 
    */
    public SplashWindow(String imageFileName, int _timeout, Window parent)
    {
        super(parent);
        String methodName = MODULE_NAME + "SplashWindow(String,int)";

        try
        {
            imageLabel = new JLabel( FusionUtils.loadIcon(imageFileName) );
            getContentPane().add( imageLabel, BorderLayout.CENTER );
            pack();
            timeout = _timeout;
            closerRunner = new CloserRunner(this);
            setLocation( FusionUtils.getCenterPosition(getSize()) );
            setCursor( Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR) );
        }
        catch( Exception e )
        {
            FusionUtils.logError( methodName, "loading icon failed", e );
        }
    }
                      
    /**
    * Fire off the splasher thread.
    */
    public void run()
    {
        String methodName = MODULE_NAME + "run()";
        try
        {
			Thread.yield();
            Thread.sleep(timeout);
            closeSplash();
        }
        catch(Exception e)
        {
            FusionUtils.logError(methodName, "Failed", e );
        }

    }

    /**
    * Start displaying the splash window
    */
    public void showSplash()
    {
        String methodName = MODULE_NAME + "showSplash()";

        setVisible( true );
        toFront();

        if( timeout > 0 )
        {
            Thread splashThread = new Thread(this, THREAD_NAME);
            splashThread.start();
			splashThread.yield();
        }
    }

    /**
    * Stop displaying the splash window.
    */
    public void closeSplash()
    {
        String methodName = MODULE_NAME + "closeSplash()";

        setVisible( false );
		//If the parent is a DialogFrame, dispose of it.
		Object obj = getParent();
		if( obj instanceof DialogFrame )
		{
			((DialogFrame)obj).dispose();
		}


        /*
        try
        {
            SwingUtilities.invokeAndWait(closerRunner);
        }
        catch(Exception e)
        {
            FusionUtils.logError(methodName, "Failed", e );
        }
        */
    } 

}

/**
* Thread Runner that closes the splasher.
*/
class CloserRunner
        implements Runnable
{
	/** module name */
    private static final String MODULE_NAME = "CloserRunner.";
	/** the splash window */
    private SplashWindow splasher;

    /**
    * Ctor.
	* 
	* @param _splasher SplashWindow
    */
    protected CloserRunner(SplashWindow _splasher)
    {
        splasher = _splasher;
    }

    /**
    * When an object implementing interface <code>Runnable</code> is used
    * to create a thread, starting the thread causes the object's
    * <code>run</code> method to be called in that separately executing
    * thread.
    * <p>
    * The general contract of the method <code>run</code> is that it may
    * take any action whatsoever.
    *
    * @see     java.lang.Thread#run()
    */
    public void run() 
    {
        splasher.setVisible(false);
    }
}
