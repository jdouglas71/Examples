package com.jdouglas.framework.interfaces.manager;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* IProjectManager interface.
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IProjectManager    
    extends IFusionManager
{
    /** Manager name */
    public static final String MANAGER_NAME                                                             = "ProjectManager";


    /**
    * Get the current project.
    *
    * @return IProject
    */
    public IProject getCurrentProject();

    /**
    * Get a project navigator for the given project.
    *
    * @param project IProject
    * 
    * @return IFusionNavigator
    */
    public IFusionNavigator getNavigator(IProject project);

}
