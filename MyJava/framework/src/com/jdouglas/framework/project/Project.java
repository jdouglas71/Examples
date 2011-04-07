package com.jdouglas.framework.project;

import java.util.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.util.*;

/**
* Project. The base project class.
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class Project 
    extends FusionData
        implements IProject
{
    /** Module name */
    private static final String MODULE_NAME =                                                               "Project.";

    /** Map of Project Data */
    private HashMap<String,IProjectData> projectData = new LinkedHashMap<String,IProjectData>();

    /**
    * Ctor.
    *
    * @param name String
    */
    protected Project(String name)
    {
        setProperty( DISPLAY_NAME, name );
    }

    //***************************************************************************************************************//
    // IProject impl 
    //

    /**
    * Get the project name.
    *
    * @return String Project Name.
    */
    public String getProjectName()
    {
        return getStringProperty( iTData.DISPLAY_NAME );
    }

    /**
    * Get the ProjectData objects.
    *
    * @return ArrayList The Project data objects.
    */
    public ArrayList<IProjectData> getProjectData()
    {
        String methodName = MODULE_NAME + "getProjectData()";
        ArrayList<IProjectData> retval = new ArrayList<IProjectData>();

        try
        {
            Iterator<IProjectData> iter = projectData.values().iterator();
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
    * Get specific project data by name.
    *
    * @param name String
    *
    * @return IProjectData. Null if an object by that name does not exist in the project.
    */
    public IProjectData getProjectData(String name)
    {
        String methodName = MODULE_NAME + "getProjectData(String)";
        IProjectData retval = null;

        try
        {
            retval = projectData.get( name );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Fialed", e );
        }


        return retval;
    }

    /**
    * Add to project. 
    *
    * @param data IProjectData
    */
    public void addToProject(IProjectData data)
    {
        String methodName = MODULE_NAME + "addToProject(IProjectData)";

        try
        {
            projectData.put( data.getName(), data );

        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * REmove from project. 
    *
    * @param data IProjectData
    *
    * @return boolean True if the data was successfully removed. 
    */
    public boolean removeFromProject(IProjectData data)
    {
        String methodName = MODULE_NAME + "removeFromProject(IProjectData)";
        boolean retval = true;

        try
        {
            projectData.remove( data.getName() );
        }
        catch(Exception e)
        {
            retval = false;
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    // IProject impl ends

}
