package com.jdouglas.framework.util;

import java.io.*;
import java.util.*;

/**
* Logger. The 451st incarnation of my Logger class!!!<br><br>
*
* JGD NOTE: I'm aware that 1.4 introduces a logger class to java.util, and I'll probably eventually fold this into it, 
* JGD NOTE: but I haven't taken the time yet. This works for me at this point. 2/24/04 <br><br>
*
* JGD TODO: Add fileName param and use map to track. Allow callers to log to multiple files.
*
* @author Jason Douglas 5/6/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class Logger
{
	/** Module name */
    private static final String MODULE_NAME = "Logger.";
	/** Default log file name */
    public static final String LOGFILE_NAME = "FCAdmin.log";

    /** Logging levels. */ //Stolen from java.util.logging.Level 
    public static final int DEBUG           = -1; //Override so I can use this for debugging during development.
    public static final int SEVERE          = 10;
    public static final int WARNING         = 9;
    public static final int INFO            = 8;
    public static final int CONFIG          = 7; 
    public static final int FINE            = 6; //Tracking  
    public static final int FINER           = 5;
    public static final int FINEST          = 4; //Everything.

    /** Me pointer */
    private static Logger Me;
    /** Current Logger */
    private static PrintWriter currentLogger;
    /** Enabled flag */
    private static boolean enabled = true;
    /** default logging level */
    private static int logLevel = CONFIG;
	/** Show thread info flag */
	private static boolean showThreadInfo = false;

    /** Map of loggers (for use when I expand this into multiple logfile support */
    private static Map<String,PrintWriter> theLoggers = new HashMap<String,PrintWriter>();
                   
    /**
    * Contructor. Only Logger can create itself.
    */ 
    private Logger()
    {
        try
        {
            if( currentLogger == null )
            {
                currentLogger = new PrintWriter( new FileWriter(LOGFILE_NAME), true );
                theLoggers.put( LOGFILE_NAME, currentLogger );
            }
        }
        catch( Exception e )
        {
            System.out.println( "Unable to create the logfile!" );
            e.printStackTrace();
        }
    }

	/**
	* Set the current logger to the given filename, creating as necessary.
	*
	* @param logFileName String
	*/
	public static void setCurrentLogger(String logFileName)
	{
		currentLogger = getLogWriter(logFileName);
	}

	/** 
	* Get a PrintWriter for the given filename, creating as necessary.
	* 
	* @param logFilename String
	* 
	* @return PrintWriter
	*/
	private static PrintWriter getLogWriter(String logFilename)
	{
		String methodName = MODULE_NAME + "getLogWriter(String)";
		PrintWriter retval = null;

		try
		{
			retval = theLoggers.get(logFilename);
			if( retval == null )
			{
				retval = new PrintWriter( new FileWriter(logFilename), true );
				theLoggers.put( logFilename, retval );
			}
		}
		catch( Exception e )
		{
			e.printStackTrace();
		}


		return retval;
	}

    /**
    * Local impl of log
    *
    * @param str String The string to be logged.
    * @param level Level The logging level for the log.
	* @param logger PrintWriter
    */
    private void _log(String str, int level, PrintWriter logger)
    {
        boolean shouldLog = false;

        if( (enabled == true) &&
            (level >= logLevel) )
        {
            shouldLog = true;
        }

        //Level override so I can just see whatever I'm currently debugging. Log calls with this level should not be shipping.
        if( level == DEBUG )
        {
            shouldLog = true;
        }

        if( shouldLog )
        {
            System.out.println( str );
			if( showThreadInfo )
			{
				logger.println( level + ": [" + Thread.currentThread().toString() + "]\n" + str);
			}
			else
			{
				logger.println( level + ": " +  str);
			}
			logger.flush();
        }
    }

	/**
	* Logs the given string to System.out and the logfile.
	* 
	* @param str String The string to be logged.
	* @param level Level The logging level for the log.
	* @param logFilename String The log file. 
	*/ 
	public static void log(String str, int level, String logFilename)
	{
		getLogger()._log(str, level, getLogWriter(logFilename));
	}

    /**
    * Logs the given string to System.out and the logfile.
    * 
    * @param str String The string to be logged.
    * @param level Level The logging level for the log.
    */ 
    public static void log(String str, int level)
    {
        getLogger()._log(str, level, currentLogger);
    }

    /**
    * Logs the given string to System.out and the logfile.
    * 
    * @param str String The string to be logged.
    */ 
    public static void log(String str)
    {
        getLogger()._log( str, INFO, currentLogger );
    }

    /**
    * Logs the stack trace for the given Throwable impl 
    * and causes it to be printed to System.out. The stack
    * trace will be printed to System.out regardless of the 
    * enabled state of the logger.
    *
    * @param e Throwable The Exception to be logged.
	* @param logFilename String Target log file. 
    */
    public static void logStackTrace(Throwable e, String logFilename)
    {
        getLogger()._logStackTrace(e, getLogWriter(logFilename));
    }

    /**
    * Logs the stack trace for the given Throwable impl 
    * and causes it to be printed to System.out. The stack
    * trace will be printed to System.out regardless of the 
    * enabled state of the logger.
    *
    * @param e Throwable The Exception to be logged.
    */
    public static void logStackTrace(Throwable e)
    {
        getLogger()._logStackTrace(e, currentLogger);
    }

    /**
    * Local impl.
    *
    * @param e Throwable The Exception to be logged.
	* @param logger PrintWriter
    */
    private void _logStackTrace(Throwable e, PrintWriter logger)
    {
        e.printStackTrace( System.out );
        //Log all stack traces.
        e.printStackTrace(logger);
        logger.flush();
    }

    /**
    * Turns on/off the logger.
    * 
    * @param b boolean The toggle flag. 
    */
    public static void setEnabled(boolean b)
    {
        getLogger()._setEnabled(b);
    }

    /**
    * Local impl
    *
    * @param b boolean The toggle flag. 
    */
    private void _setEnabled(boolean b)
    {
        enabled = b;
    }

	/**
	* Dump the System.properties to the logfile.
	*
	* @param forceIt boolean 
	* @param logFilename String
	*/
	public static void logProperties(boolean forceIt, String logFilename)
	{
		getLogger()._logProperties(forceIt, getLogWriter(logFilename));
	}

    /**
    * Dump the System.properties to the logfile.
    *
    * @param forceIt boolean 
    */
    public static void logProperties(boolean forceIt)
    {
        getLogger()._logProperties(forceIt,currentLogger);
    }

    /**
    * Local impl
    *
    * @param forceIt boolean 
	* @param logger PrintWriter
    */
    private void _logProperties(boolean forceIt, PrintWriter logger)
    {
        try
        {
            if( (enabled == true) || (forceIt == true) )
            {    
                logger.println( "Logging System Properties..." );
                logger.println( "" );
                Iterator iter = System.getProperties().entrySet().iterator();
                while( iter.hasNext() )
                {
                    Map.Entry entry = (Map.Entry)iter.next();
                    logger.println( entry.getKey().toString() + " = " + entry.getValue().toString() );
                }
                logger.println( "" );
                logger.println( "" );
                logger.flush();
            }
        }
        catch(Exception e)
        {
            logger.println( "Unabled to access System.properties..." );
            logger.flush();
        }
    }

    /**
    * Local impl.
    * 
    * @param level int New Logging level.
    */
    private void _setLogLevel(int level)
    {
        logLevel = level;
    }

    /**
    * Set the logging level. Any messages with a higher level than the logLevel are logged.
    * 
    * @param level int The new logging level.
    */
    public static void setLogLevel(int level)
    {
        getLogger()._setLogLevel(level);
    }

	/**
    * Set the showThreadInfo Flag. 
	* 
	* @param b boolean
    */
	public static void setShowThreadInfo(boolean b)
	{                  
		showThreadInfo = b;
	}

    /**
    * Private accessor.
    *
    * @return Logger
    */
    private static Logger getLogger()
    {
        if( Me == null )
        {
            Me = new Logger();
        }
        return Me;
    }
}
