package com.jdouglas.framework.core;

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

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.enums.view.*;

/**
* FusionManager. Abstract Base class for IFusionManager derivatives.
*
* @author Jason Douglas 5/27/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionManager
        implements IFusionManager
{
	/** Module name */
    private static final String MODULE_NAME               = "FusionManager.";

    /** Manager listeners */
    protected ArrayList<IFusionManagerListener> theListeners = new ArrayList<IFusionManagerListener>();
    /** dirty flag */
    protected boolean theDirtyFlag = false;
	/** Manager name */
	protected String theManagerName = MODULE_NAME;
	/** The menuItems for the manager (indices based on IApplicationFrame menuID constants */
	protected EnumMap<MenuID,ArrayList<JMenuItem>> theMenuItems;   
	/** The toolbar components */
	protected EnumMap<MenuID,ArrayList<Object>> theToolbarComponents;
	/** The toplevel menus for the manager */
	protected ArrayList<JMenu> theMenus = new ArrayList<JMenu>();
	/** The popup menus */
	protected ArrayList<JMenuItem> thePopupMenus = new ArrayList<JMenuItem>();

	/**
    * Constructor. 
	* 
	* @param managerName String 
    */
	protected FusionManager(String managerName)
	{
		theManagerName = managerName;

		//Initialize the menu items arraylists. 
		theMenuItems = new EnumMap<MenuID,ArrayList<JMenuItem>>(MenuID.class);
		theMenuItems.put(MenuID.FILE_MENU, new ArrayList<JMenuItem>());
		theMenuItems.put(MenuID.EDIT_MENU, new ArrayList<JMenuItem>());
		theMenuItems.put(MenuID.VIEW_MENU, new ArrayList<JMenuItem>());
		theMenuItems.put(MenuID.TOOLS_MENU, new ArrayList<JMenuItem>());
		theMenuItems.put(MenuID.HELP_MENU, new ArrayList<JMenuItem>());
		theMenuItems.put(MenuID.MANAGER_MENU, new ArrayList<JMenuItem>());

		//Initialize the toolbar component arrayLists
		theToolbarComponents = new EnumMap<MenuID,ArrayList<Object>>(MenuID.class);
		theToolbarComponents.put(MenuID.FILE_MENU, new ArrayList<Object>());
		theToolbarComponents.put(MenuID.EDIT_MENU, new ArrayList<Object>());
		theToolbarComponents.put(MenuID.VIEW_MENU, new ArrayList<Object>());
		theToolbarComponents.put(MenuID.TOOLS_MENU, new ArrayList<Object>());
		theToolbarComponents.put(MenuID.HELP_MENU, new ArrayList<Object>());
		theToolbarComponents.put(MenuID.MANAGER_MENU, new ArrayList<Object>());
	}

    //********************************************************************************************//
    // IFusionManager impl (partial)
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
	* Import outside data into the manager. Typically occurs post-init.
	* 
	* @param dataSource File The datasource to extract data from. 
	*
	* @return boolean True if import succeeded.
	*/
	public boolean importData(File dataSource)
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
	* Get any toplevel menus associated with the manager. 
	* 
	* @return ArrayList<JMenu> The manager menus. 
	*/
	public ArrayList<JMenu> getMenus()
	{
		String methodName = MODULE_NAME + "getMenus()";

		return theMenus;
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
		String methodName = MODULE_NAME + "getMenuItems(int)";

		return theMenuItems.get(menuID);
	}

	/**
	* Get any toolbar components associated with the manager
	*
	* @param menuID MenuID The ID of the menu being updated. 
	* @return ArrayList<Object> Array with the toolbar components. 
	*/
	public ArrayList<Object> getToolbarComponents(MenuID menuID)
	{
		String methodName = MODULE_NAME + "getToolbarComponents(int)";
		return theToolbarComponents.get(menuID);
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
    * Add a Manager listener.
    * 
    * @param l IFusionManagerListener The listener to add. 
    */
    public void addFusionManagerListener(IFusionManagerListener l) 
    {
		synchronized( theListeners )
		{
			theListeners.add( l );
		}
    }

    /**
    * Remove a Manager Listener
    *
    * @param l IFusionManagerListener The listener to remove. 
    */
    public void removeFusionManagerListener(IFusionManagerListener l) 
    {
		synchronized( theListeners )
		{
			theListeners.remove( l );
		}
    }

    /**
    * Fire an update.
    *
    * @param man IFusionManager The manager being updated. 
    */
    public synchronized void fireManagerUpdate(IFusionManager man)
    {
        String methodName = MODULE_NAME + "fireManagerUpdate(IFusionManager)";

        try
        {
			//JGD TODO: This is worrysome. Should investigate further.
			synchronized( theListeners )
			{
				Iterator<IFusionManagerListener> iter = theListeners.iterator();
				while( iter.hasNext() )
				{
					IFusionManagerListener l = iter.next();
					l.managerUpdated( man );
				}
			}
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
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
    * Perform any pre-destruction tasks. This does NOT include saving the state of the managed data object, but 
    * any cleanup tasks that must happen before the GOO is torn down.
    */
    public void closeManager()
    { 
    }

    /**
    * Get the state of the manager's dirty flag.
    *
    * @return boolean The state of the manager's local dirty flag. 
    */
    public boolean isDirty()
    {
        return theDirtyFlag;
    }

    /**
    * Set the dirty flag. 
    *
    * @param b boolean The new state of the dirty flag for the manager.
    */
	public void setDirtyFlag(boolean b)
    {
        String methodName = MODULE_NAME + "setDirtyFlag(b)";
        Logger.log( methodName + " Manager: " + getManagerName() + " setting dirty flag to " + b, Logger.CONFIG );
        theDirtyFlag = b;
        
        if( FusionApplication.getApplicationFrame() != null )
        {
            Logger.log( methodName + " Manager: " + getManagerName() + " setting global dirty flag to " + b + ".", Logger.CONFIG );
            FusionApplication.getApplicationFrame().setDirtyFlag( b );
        }
    }

	/**
	* Get Dirty Map. Use document to create DOM elements listing any "dirty" objects controlled 
	* by this manager.
	* 
	* @param doc Document
	* 
	* @return Element Null return values mean nothing is dirty.
	*/
	public Element getDirtyMap(Document doc)
	{
		return null;
	}

    /**
    * Force a refresh of the contained manager data.
    */
    public void refreshData()
    {

    }

    /**
    * Get menuitems to be displayed in a popup menu.
    * JGD TODO: Provide some sort of context object that managers can use to determine what, if any, menuitems
    * JGD TODO: should be displayed. This will allow other managers to potentially add menuitems to a local menu,
    * JGD TODO: even if they are not the current manager\tab. For now, I'll only be using the local manager to populate
    * JGD TODO: any local menus.
    *
    * @return ArrayList<JMenuItem> of Popupmenus. 
    */
    public ArrayList<JMenuItem> getPopupMenus()
    {
        return thePopupMenus;
    }

	/**
	* Get a FusionViewFactory from the manager. It is assumed that the types of data used to request views will be in the perview
	* of the specific manager object (e.g. Views for FusionUser's requested from the factory produced by FusionUserManager).
	* 
	* @return IFusionViewFactory
	*/
	public IFusionViewFactory getViewFactory()
	{
		String methodName = MODULE_NAME + "getViewFactory()";
		IFusionViewFactory retval = null;

		//JGD TODO Generic View factory

		return retval;
	}

    // IFusionManager impl ends

	/**
    * Return the manager name as the string rep of this object.
	* 
	* @return String 
    */
	@Override
	public String toString()
	{
		return theManagerName;
	}
 }
