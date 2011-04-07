package com.jdouglas.FusionAE.grids;

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

import com.jdouglas.FusionAE.*;
import com.jdouglas.FusionAE.interfaces.manager.*;
import com.jdouglas.FusionAE.interfaces.props.*;

/**
* GridManager. 
*
* JGD TODO: Need actions for new and open project. 
* JGD: This is completely unused at this point. 3/19/09
*
* @author Jason Douglas 4/26/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridManager 
    extends FusionManager
        implements IGridManager
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "GridManager.";

    /** Add Grid Action */
    private AddGridAction addGridAction;
    /** Response data Handler Action */
    private ResponseDataHandlerAction responseDataHandlerAction;

    /** the resources */
    protected GridResources theResources = (GridResources)FusionAE.getResources(IGridProperties.class);

    /**
    * Constructor.
    */
    public GridManager()
    {
		super(MANAGER_NAME);
    }

    /**
    * Edit | Add Grid
    */
    public void addGrid()
    {
        String methodName = MODULE_NAME + "addGrid()";
        
        try
        {
            //AddGridWizard wiz = new AddGridWizard();

            //if( wiz.showWizard( theExperiment ) )
            //{
            //    //Cheating for the demo. Should use refreshContents
            //    experimentPanel.setDataModel( theExperiment );
            //}
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /** 
    * Launch the Respnose Data Handler tool.
    */
    protected void responseDataHandler()
    {
        String methodName = MODULE_NAME + "responseDataHandler()";

        try
        {

        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }


    //*********************************************************************************************************************//
    // IFusionManager impl
    //

    /**
    * Get the IFusionTab component.
    * 
    * @return IFusionTab object for the manager. 
    */
    public IFusionTab getFusionTab()
    {
        return null;
    }

    /**
    * Get editor component ui for the manager
    *
    * @return JComponent The Editor componenent for manager.
    */
    public JComponent getEditorComponent()
    {
        return null;
    }
    
    /**
    * Commit the manager info to the database.
    */
    public void commit()
    {
    }

    /**
    * Get Validator object for the Manager. 
    *
    * @return IValidator object for the manager. 
    */
    public IValidator getValidator()
    {
        return null;
    }

    /**
    * Import outside data into the manager. Typically occurs post-init.
    * 
    * @param dataSource String The datasource to extract data from. 
    *
    * @return boolean True if import succeeded.
    */
    public boolean importData(String dataSource)
    {
        String methodName = MODULE_NAME + "importData(String)";
        boolean retval = true;

        return retval;
    }

    /**
    * Returns an Action object corresponding to the given string if present.
    *
    * @param actionName String The name of the action.
    *
    * @return Action for the given string. 
    */
    public Action getAction(String actionName)
    {
        String methodName = MODULE_NAME + "getAction(String)";
        Action retval = null;

        return retval;
    }

    /**
    * Returns a list of action names/verbs supported by this object.
    * 
    * @return Iterator with the action strings for the manager. 
    */
    public Iterator getActionStrings()
    {
        String methodName = MODULE_NAME + "getActionString()";
        Iterator retval = new ArrayList().iterator();
        

        return retval;
    }

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
    * Get any toplevel menus associated with the manager. 
    *
    * JGD TODO: Allow the manager to specify the location of the menus and menuitems to be merged. Use the
    * JGD TODO: File-Edit-View-Window-Help system.
    * 
    * @return ArrayList<JMenu> The manager menus. 
    */
    public ArrayList<JMenu> getMenus()
    {
        String methodName = MODULE_NAME + "getMenus()";
        ArrayList<JMenu> retval = new ArrayList<JMenu>();

        return retval;
    }

    /**
    * Get any toolbar components associated with the manager
    *
	* @param menuID int
	* 
    * @return ArrayList<Object> Array with the toolbar components. 
    */
    public ArrayList<Object> getToolbarComponents(int menuID)
    {
        String methodName = MODULE_NAME + "getToolbarComponents(int)";
        ArrayList<Object> retval = new ArrayList<Object>();

        return retval;
    }
    
    /**
    * Get an XML Element containing all the changes made to the manager's containing data.
    *
    * @return Element with the change log for the manager. 
    */ 
    public Element getChangeLog(org.w3c.dom.Document doc)
    {
        return null;
    }

    /**
    * Perform any post creation initialization. Guarenteed to be called after all managers have been created and 
    * registered with the system. This gets called multiple times for the defined init "phases". The first is the 
    * REGISTER_PHASE which allows managers to register as listeners with other managers and then the LOAD_PHASE, during
    * which any data loading (which may be of interest to those listening) will occur. 
    *
    * @param phase int The initialization phase
    */
    public void initManager(int phase)
    {
    }

    /**
    * Perform any pre-destruction tasks. 
    * This is a post-save, pre-teardown chance for cleanup.
    */
    public void closeManager()
    {
    }

    /**
    * Force a refresh of the Manager data.
    */
    public void refreshData()
    {
    }

    //*********************************************************************************************************************//
    // IGridManager impl
    //
    // IGridManager impl ends
    // IFusionManager impl ends
}

/**
* AddGridAction. 
*
* @author Jason Douglas 4/19/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
class AddGridAction
    extends FusionAction
{
    /** Module name */
    private static final String MODULE_NAME = "AddGridAction.";

    /** parent manager */
    private GridManager theManager;
    /** name */
    private String name;
    /** the resources */
    private GridResources theResources = (GridResources)FusionAE.getResources(IGridProperties.class);

    /**
    * Ctor.
    * 
    * @param manager GridManger 
    * @param _name String The name of the action.
    */
    public AddGridAction(GridManager manager, String _name)
    {
        super( _name, KeyStroke.getKeyStroke(KeyEvent.VK_G, KeyEvent.CTRL_MASK) );
        theManager = manager;
        name = _name;

        try
        {
            putValue( Action.SHORT_DESCRIPTION, theResources.addGridTooltip );
            putValue(Action.SMALL_ICON, theResources.addGridIcon );
        }
        catch( Exception e )
        {
            //Oh well,
            Logger.log( MODULE_NAME + "ctor  problem", Logger.SEVERE );
            Logger.logStackTrace( e );
        }
    }

    /**
    * Called when the action is triggered.
    *
    * @param e ActionEvent The Event object. 
    */
    public void actionPerformed(ActionEvent e) 
    {
        Logger.log( "Action performed for " + name, Logger.FINE );
        if( isEnabled() )
        {
            theManager.addGrid();
        }
    }
}

/**
* ResponseDataHandlerAction. 
*
* @author Jason Douglas 4/19/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

class ResponseDataHandlerAction
    extends FusionAction
{
    /** Module name */
    private static final String MODULE_NAME = "ResponseDataHandlerAction.";

    /** parent manager */
    private GridManager theManager;
    /** name */
    private String name;
    /** the resources */
    private GridResources theResources = (GridResources)FusionAE.getResources(IGridProperties.class);

    /**
    * Ctor.
    * 
    * @param manager GridManager The parent object for the action. 
    * @param _name String The name of the action.
    */
    public ResponseDataHandlerAction(GridManager manager, String _name)
    {
        super( _name, KeyStroke.getKeyStroke(KeyEvent.VK_R, KeyEvent.CTRL_MASK) );
        theManager = manager;
        name = _name;

        try
        {
            putValue( Action.SHORT_DESCRIPTION, theResources.responseDataHandlerTooltip );
            putValue(Action.SMALL_ICON, theResources.responseDataHandlerIcon );
        }
        catch( Exception e )
        {
            //Oh well,
            Logger.log( MODULE_NAME + "ctor  problem", Logger.SEVERE );
            Logger.logStackTrace( e );
        }

    }

    /**
    * Called when the action is triggered.
    *
    * @param e ActionEvent The Event object. 
    */
    public void actionPerformed(ActionEvent e) 
    {
        Logger.log( "Action performed for " + name, Logger.FINE );
        if( isEnabled() )
        {
            theManager.responseDataHandler();
        }
    }
}
