package com.jdouglas.framework.project;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* ProjectData. Wrapper objects for the project data.
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ProjectData
    extends FusionData
        implements IProjectData
{
    /** MOdule name */
    private static final String MODULE_NAME                                                             = "ProjectData.";

	/** Child nodes */
	private HashMap<String,IProjectData> theChildNodes = new HashMap<String,IProjectData>();


    /**
    * Ctor
    * 
    * @param name String
    */
    protected ProjectData(String name)
    {
        setProperty( DISPLAY_NAME, name );
    }         

	/** 
	* Use the name as the string representation
	*
	* @return String
	*/
	public String toString()
	{
		return getName();
	}

    //*************************************************************************************************//
    // IProjectData impl
    //

    /**
    * Get the name.
    *
    * @return String name
    */
    public String getName()
    {
        return getStringProperty( DISPLAY_NAME );
    }


    /** 
    * Get Child ProjectData nodes.
    *
    * @return ArrayList<IProjectData> the child nodes.
    */
    public ArrayList<IProjectData> getChildData()
	{
		String methodName = MODULE_NAME + "getChildNodes()";
		ArrayList<IProjectData> retval = new ArrayList<IProjectData>();

		try
		{
			Iterator<IProjectData> iter = theChildNodes.values().iterator();
			while( iter.hasNext() )
			{
				retval.add( iter.next() );
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Add a child node 
	* 
	* @param child IProjectData
	*/
	public void addChild(IProjectData child)
	{
		theChildNodes.put( child.getName(), child );
	}

    // IProjectData impl
}
