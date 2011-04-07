package com.jdouglas.framework.core;

import javax.swing.*;
import java.awt.*;
import java.net.*;
import java.io.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.props.*;

/**
* Extend this class to create your very own Resource manager!  This class provides the mechanisms required to:
* -- Extract String values from a given ResourceBundle via getResourceString.
* -- Load files of any type.
* -- Load Images 
* -- Load Icons 
* 
* @author Jason Douglas 8/25/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class FusionResources
{
	/** Module Name */
    private static final String MODULE_NAME = "FusionResources.";
	/** Resource bundle */
    private String theBundle = IFrameworkProperties.FRAMEWORK_BUNDLE;
	/** The base resource class. Used for loading resources */
	private Class theResourceBaseClass = com.jdouglas.framework.core.FusionApplication.class;

	/** Load on Demand Support */
	/** Map of resource ID's to default values */
	private HashMap<String,String> theDefaultValues = new HashMap<String,String>();
	/** Map of resource ID's to loaded String values */
	private HashMap<String,String> theResourceStrings = new HashMap<String,String>();
	/** Map of resource ID's to loaded Icons */
	private HashMap<String,ImageIcon> theResourceIcons = new HashMap<String,ImageIcon>();
	/** Map of resource ID's to loaded Images */
	private HashMap<String,Image> theResourceImages = new HashMap<String,Image>();

	/** Logging flag */
	private boolean loggingFlag = true;

    /** 
    * Retieves the resource name from the given bundleName using the given resource identifier.
    * If the resource cannot be located, the defaultVal param is returned. 
    *
    * @param resName String
    * @param defaultVal String
    * @param bundleName String
    *
    * @throws Exception 
    * @return String
    */
    public String getResourceString(String resName, String defaultVal, String bundleName)
        throws Exception 
    {
        String retval = "";

        String tmpStr =  FusionUtils.getResourceString( resName,
                                                        defaultVal,
                                                        bundleName );
        if( tmpStr == null ) 
            throw new Exception("Couldn't load " + resName + " from " + theBundle );
        else
            retval = tmpStr;

        return retval;
    }

    /**
    * Get the resource using the default bundle, returning the defaultVal param if the resource cannot be located.
    *
    * @param resName String
    * @param defaultVal String
    *
    * @throws Exception 
    * @return String
    */
    public String getResourceString(String resName, String defaultVal)
        throws Exception
    {
        return getResourceString( resName, defaultVal, theBundle );
    }
    
    /**
    * Get the resource using the default bundle, returning <code>null</code> if the resource cannot be located.
    *
    * @param resName String
    *
    * @throws Exception 
    * @return String
    */
    //public String getResourceString(String resName)
    //    throws Exception 
    //{
    //    return getResourceString( resName, null );
    //}

    /**
    * Set the bundle name
    *
    * @param newBundle String 
    */
    public void setBundleName(String newBundle)
    {
        theBundle = newBundle;
    }

	/**
    * Set the resource base class. Used to load resources. 
	* 
	* @param baseClass Class 
    */
	public void setResourceBaseClass(Class baseClass)
	{
		theResourceBaseClass = baseClass;
	}

    /**
    * Load an Image by name
    *
    * @param imageName String
    *
    * @return Image
    */
    public Image loadImage(String imageName)
    {
        String methodName = MODULE_NAME + "loadImage(String)";
        return FusionUtils.loadImage( imageName, theResourceBaseClass );
    }

    /**
    * Load an Icon by name. 
    *
    * @param iconName String 
    *
    * @return ImageIcon 
    */
    public ImageIcon loadIcon(String iconName)
    {
        String methodName = MODULE_NAME + "loadIcon(String)";
        return FusionUtils.loadIcon( iconName, theResourceBaseClass );
    }

    /**
    * Load a File by name and return a string with it's contents. (The file should be small).
    *
    * @param filename String
    * @param defaultValue String
	* @param baseResourceClass
    *
    * @return String 
    */
    public String loadFile(String filename, String defaultValue, Class baseResourceClass)
    {
        String methodName = MODULE_NAME + "loadFile(String)";
        String retval = "";

        try
        {   
			URL url = baseResourceClass.getResource( filename );
            Object contents = url.getContent();

            if( contents instanceof String )
            {
                retval = (String)contents;
            }
            else if( contents instanceof InputStream )
            {
                InputStreamReader reader = new InputStreamReader( (InputStream)contents );
                StringBuffer buf = new StringBuffer();
                try
                {
                    //Read in 4096 bytes at a time until we can't read no more! 
                    char[] inBuf = new char[4096];
                    while( reader.read(inBuf,0,inBuf.length) >= 0) 
                    {
                        buf.append( inBuf );
                    }
                }
                catch(IndexOutOfBoundsException io)
                {
                    //Don't care we're done.
                    Logger.log( methodName + " index out of bounds. Done reading." );
                }
                retval = buf.toString().trim();
            }
            else 
            {
                retval = defaultValue;
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
            retval = defaultValue;
        }

        return retval;
    }

    /**
    * Load a file by name from the jar file (vai URL) with a default value set to a blank string.
    *
    * @param fileName String
    *
    * @return String 
    */
    public String loadFile(String fileName)
    {
        return loadFile(fileName, "", theResourceBaseClass );
    }

	//Load on Demand support

	/**
    * Get the default value for the given resource ID. Can be null.
	* 
	* @param id String
	* 
	* @return String
    */
	public String getDefaultValue(String id)
	{
		return theDefaultValues.get(id);
	}

	/**
    * Set the default value for the given resource id. 
	* 
	* @param id String
	* @param val String
    */
	public void setDefaultValue(String id, String val)
	{
		theDefaultValues.put( id, val );
	}

	/**
    * Get the resource string for the given id. Returns the default value if the id 
	* cannot be found. Loads on demand.
	* 
	* @param id String
	* 
	* @return String
    */
	public String getResourceString(String id)
	{
		String methodName = MODULE_NAME + "getResourceString(String)";
		String retval = theResourceStrings.get( id );

		try
		{
			if( retval == null )
			{
				//Logger.log( methodName + " Loading value for id: "+ id, Logger.DEBUG );
				retval = getResourceString( id, getDefaultValue(id) );
				theResourceStrings.put( id, retval );
				//Logger.log( methodName + " Got value for id: "+ id + " = " + retval, Logger.DEBUG );
			}
			else
			{
				//Logger.log( methodName + " Returned preloaded value for id: " + id + " = " + retval, Logger.DEBUG );
			}
		}
		catch( Exception e )
		{
			if( loggingFlag )
			{
				Logger.log( methodName + " No value found for id: " + id, Logger.DEBUG );
			}
		}

		return retval;
	}

	/**
    * Get Resource Image, loading if necessary. 
	* 
	* @param id String
	* 
	* @return Image 
    */
	public Image getResourceImage(String id)
	{
		String methodName = MODULE_NAME + "getResourceImage(String)";
		Image retval = theResourceImages.get( id );

		try
		{
			if( retval == null )
			{
				//Logger.log( methodName + " LOading image for ID: " + id, Logger.DEBUG );
				retval = loadImage( getResourceString(id) );
				theResourceImages.put( id, retval );
			}
			else
			{
				//Logger.log( methodName + " Returning loaded Image for ID: " + id, Logger.DEBUG );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Get Resource Icon, loading if necessary. 
	* 
	* @param id String
	* 
	* @return ImageIcon 
	*/
	public ImageIcon getResourceIcon(String id)
	{
		String methodName = MODULE_NAME + "getResourceIcon(String)";
		ImageIcon retval = theResourceIcons.get( id );

		try
		{
			if( retval == null )
			{
				//Logger.log( methodName + " LOading icon for ID: " + id, Logger.DEBUG );
				retval = loadIcon( getResourceString(id) );
				theResourceIcons.put( id, retval );
			}
			else
			{
				//Logger.log( methodName + " Returning preloaded icon for id: " + id, Logger.DEBUG );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
    * Set Logging flag.
	* 
	* @param b boolean
    */
	public void setLoggingFlag(boolean b)
	{
		loggingFlag = b;
	}
}
