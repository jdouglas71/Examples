package com.jdouglas.framework.core;

import java.util.*;
import javax.swing.ImageIcon;

import com.jdouglas.system_interaction.infobus.wizard_manager.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.util.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;


/**
* FusionApplication. Base application class. This is not an interface. Everyone in the framework needs access to this 
* all applications should have a class derived from this.
*
* @author Jason Douglas 11/15/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionApplication
        implements IApplication
{
	/** Module name */
    private static final String MODULE_NAME                                                         = "FusionApplication.";
	/** Monitor thread name (Not sure this needs to be hidden or not) */
	private static final String FUSION_APPLICATION_MONITOR											= "FusionApplicationMonitor";

    /** the application frame */
    private static IApplicationFrame theFrame;
    /** Resources */
    public static FrameworkResources theResources;
	/** Resource map */
    private static Map<Object,Object> theResourceMap = new HashMap<Object,Object>();
	/** Monitor Timer */
	private static Timer theMonitor;
	/** Map the managers by name */
	private static Map<String,IFusionManager> theManagers;       
	/** Application Icon */
	private static ImageIcon theAppIcon;
	/** Application Token */
	private static String theAppToken;
	/** Application pointer */
	private static IApplication theApplication;
	/** Application title */
	private static String theAppTitle = "Fusion Application";

    /**
    * Constructor. 
    *
    * @param logFileName String
    * @param loggingEnabled boolean
    */ 
    protected FusionApplication(String logFileName, boolean loggingEnabled)
    {
        Logger.setCurrentLogger( logFileName );
        Logger.setEnabled( loggingEnabled );
        FusionApplication.theResources = new FrameworkResources();
        theResourceMap.put( IFrameworkProperties.class, theResources );
		theMonitor = new Timer( FUSION_APPLICATION_MONITOR, false );
		theManagers = new LinkedHashMap<String,IFusionManager>();
    }

    /**
    * Constructor. Sets the logfile name and loads the resources for the framework.
    */ 
    protected FusionApplication()
    {
        this( "FusionApplication.log", true );
    }

    /**
    * Get the resources associated with the given interface class.
    * 
    * @param key Object
    * @return Object FusionResources extender
    */
    public static Object getResources(Object key)
    {
        return theResourceMap.get( key );
    }

    /**
    * Add resources to the application.
    *
    * @param key Object 
    * @param resources Object
    */
    public static void addResources(Object key, Object resources)
    {
        theResourceMap.put( key, resources );
    }

    /**
    * Get the frame instance for the application.
    *
    * @return IApplicationFrame
    */
    public static IApplicationFrame getApplicationFrame()
    {
        return theFrame;
    }

    /**
    * Set the frame instance.
    *
    * @param frame IApplcationFrame.
    */
    public static void setApplicationFrame(IApplicationFrame frame)
    {
        theFrame = frame;
        FusionUtils.setResourceBaseComponent( frame.getFrame() );
    }

	/**
    * Get the monitor timer. Use to add TimerTasks.
	* 
	* @return Timer
    */
	public static Timer getApplicationTimer()
	{
		return theMonitor;
	}

	/**
	* Store the given manager in the various lists.
	*
	* @param newManager IFusionManager The new Manager object.
	*/
	public static void storeManager(IFusionManager newManager)
	{
		String methodName = MODULE_NAME + "storeManager(IFusionManager)";

		try
		{
			theManagers.put( newManager.getManagerName(), newManager );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Get the managers.
	*
	* @return Map<String,IFusionManager> containing the IFusionManager objects for the system.
	*/
	public static Map<String,IFusionManager> getManagers()
	{
		String methodName = MODULE_NAME + "getManagers()";
		Logger.log( methodName, Logger.FINE );
		return theManagers;
	}

	/**
	* Close the managers by iterating thru the manager list and calling IFusionManager.closeManager(). 
	* This is a post-save, pre-teardown chance for cleanup.
	*/ 
	public static void closeManagers()
	{
		String methodName = MODULE_NAME + "closeManagers()";
		try
		{
			Iterator iter = getManagers().values().iterator();
			while( iter.hasNext() )
			{
				IFusionManager man = (IFusionManager)iter.next();
				man.closeManager();
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
    * Set the application Icon 
	* 
	* @param icon ImageIcon
    */
	public static void setApplicationIcon(ImageIcon icon)
	{
		theAppIcon = icon;
	}

	/**
    * Get the application Icon.
	* 
	* @return ImageIcon
    */
	public static ImageIcon getApplicationIcon()
	{
		return theAppIcon;
	}

	/**
	* Set the application token
	* 
	* @param token String
	*/
	public static void setApplicationToken(String token)
	{
		theAppToken = token;
	}

	/**
	* Get the application Token.
	* 
	* @return String
	*/
	public static String getApplicationToken()
	{
		return theAppToken;
	}

	/**
	* Set the application title
	* 
	* @param title String
	*/
	public static void setApplicationTitle(String title)
	{
		theAppTitle = title;
	}

	/**
	* Get the application Title.
	* 
	* @return String
	*/
	public static String getApplicationTitle()
	{
		return theAppTitle;
	}

	/**
    * Set the application pointer. The application pointer gives universal access to the current application object so 
	* that callers can ensure that the application specific implementation of certain methods are called (e.g. initApplication 
	* and closeApplication).
	* 
	* @param app IApplication 
    */
	public static void setApplication(IApplication app)
	{
		theApplication = app;
	}

	/**
	* Get the application pointer. The application pointer gives universal access to the current application object so 
	* that callers can ensure that the application specific implementation of certain methods are called (e.g. initApplication 
	* and closeApplication).
	* 
	* @return IApplication 
	*/
	public static IApplication getApplication()
	{
		return theApplication;
	}

	/**
    * Run a wizard from the VB side via the infobus. 
	* 
	* @param wizardName String
	* @param data iTData
	* @param worker IWizardWorker
	* 
	* @return iTData
    */
	public static iTData runWizard(String wizardName, iTData data, IWizardWorker worker)
	{
		return null;
	}

	//****************************************************************************************************//
	// IApplication impl
	// 
	 
	/**
	* Initialize the application. NOT called from the ctor and should NOT depend on being called from main function.
	* Allows application class to be initialized independent of the main function of an application. Call via application pointer. 
	*/
	//public void initApplication()
	//{
	//}

	/** 
	* Close the application. Call via the application pointer. 
	* 
	* @param code int Exit code. Defined in IUtilCOnstants.
	* @param msg String Message to be displayed to user. 
	*/
	//public void closeApplication(int code, String msg)
	//{
	//	String methodName = MODULE_NAME + "closeApplication(int,String)";
	//	Logger.log( methodName, Logger.DEBUG );
	//}

	// IApplication impl ends 

    /**
    * There can be only one.
    */
    static 
    {
        theResourceMap.put( IFrameworkProperties.class, theResources );
    }
}
