package com.jdouglas.framework.project;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;
import org.w3c.dom.*;
import org.xml.sax.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.enums.view.*;

/**
* ProjectManager. The project manager!!!!
*
* JGD TODO: Need actions for new and open project. 
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ProjectManager 
    extends FusionManager
        implements IProjectManager
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "ProjectManager.";

    /** current project */
    private IProject theProject;
	/** project navigators */
	private HashMap<String,IFusionNavigator> theNavigators = new HashMap<String,IFusionNavigator>();

    /**
    * Constructor
    */
    public ProjectManager()
    {
		super(MANAGER_NAME);
        initFakeData();
    }

    /**
    * Create a fake project.
    */
    private void initFakeData()
    {
        theProject = new Project( "Example Project" );
        theProject.addToProject( new ProjectData("Experiment 1") );
        theProject.addToProject( new ProjectData("Experiment 2") );
        theProject.addToProject( new ProjectData("Experiment 3") );
        theProject.addToProject( new ProjectData("Experiment 4") );
        theProject.addToProject( new ProjectData("Experiment 5") );
    }

	//*********************************************************************************************************************//
	// IFusionManager impl
	// 

	/**
	* A name string associated with the manager. Used to hash the manager. 
	*
	* @return String The manager name. 
	*/
	public String getManagerName()
	{
		return MANAGER_NAME;
	}

	/**
	* Get any menuitems associated with the standard frame menus.
	* 
	* @param menuID MenuID
	* 
	* @return ArrayList<JMenuItem>
	*/
	public ArrayList<JMenuItem> getMenuItems(MenuID menuID)
	{
		//JGD NOTE: TEMPORARY! Just here while I update all the manager classes.
		String methodName = MODULE_NAME + "getMenuItems(int)";
		ArrayList<JMenuItem> retval = new ArrayList<JMenuItem>();
	
		return retval;
	}

    //*********************************************************************************************************************//
    // IProjectManager impl
    //
    /**
    * Get the current project.
    *
    * @return IProject
    */
    public IProject getCurrentProject()
    {
        return theProject;
    }

    /**
    * Get a project navigator for the given project.
    * 
	* @param project IProject 
	* 
    * @return IFusionNavigator
    */
    public IFusionNavigator getNavigator(IProject project)
    {
        String methodName = MODULE_NAME + "getNavigator(IProject)";
		IFusionNavigator retval = null;

		try
		{
			retval = theNavigators.get( project.getProjectName() );
			if( retval == null )
			{
				retval = new ProjectNavigator( project );
				theNavigators.put( project.getProjectName(), retval );
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
    }
    // IProjectManager impl ends
	// IFusionManager impl ends
}
