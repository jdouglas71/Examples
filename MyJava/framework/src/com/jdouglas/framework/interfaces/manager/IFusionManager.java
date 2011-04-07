package com.jdouglas.framework.interfaces.manager;

import javax.swing.*;
import java.util.*;
import java.io.*;
import org.w3c.dom.*;

import com.jdouglas.framework.enums.view.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* IFusionManager. Base interface for the various managers in FCA.<br><BR>
* 
* JGD TODO: Should be using Map for actions and a listener\broadcast scheme for the commit.<br><br>
*
* JGD TODO: Generic component getter that provides mechanism for requesting different views on the manager data. (Editor, Readonly, etc.)<br><br>
* 
* @author Jason Douglas 2/7/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionManager
{
    /**
    * Register phase of the init procedure. All managers have been created, but their data has not been loaded.
    * This phase allows other interested managers to register as listeners prior to the data load phase. 
    */
    public static final int REGISTER_PHASE                  = 0;
    /**  Managers can now load data. */
    public static final int LOAD_PHASE                      = 1;

	/**
	* Get the IFusionTab component.
	* 
	* @return IFusionTab object for the manager. 
	*/
	public IFusionTab getFusionTab();

    /**
    * Get editor component ui for the manager
    *
    * @return JComponent The Editor componenent for manager.
    */
    public JComponent getEditorComponent();
    
    /**
    * Commit the manager info to the database.
    */
    public void commit();

    /**
    * Get Validator object for the Manager. 
    *
    * @return IValidator object for the manager. 
    */
    public IValidator getValidator();

    /**
    * Import outside data into the manager. Typically occurs post-init.
    * 
    * @param dataSource String The datasource to extract data from. 
    *
    * @return boolean True if import succeeded.
    */
    public boolean importData(String dataSource);

	/**
	* Import outside data into the manager. Typically occurs post-init.
	* 
	* @param dataSource File The datasource to extract data from. 
	*
	* @return boolean True if import succeeded.
	*/
	public boolean importData(File dataSource);

    /**
    * Returns an Action object corresponding to the given string if present.
    *
    * @param actionName String The name of the action.
    *
    * @return Action for the given string. 
    */
    public Action getAction(String actionName);

    /**
    * Returns a list of action names/verbs supported by this object.
    * 
    * @return Iterator with the action strings for the manager. 
    */
    public Iterator getActionStrings();

    /**
    * A name string associated with the manager. Used to hash the manager. 
    *
    * @return String The manager name. 
    */
    public String getManagerName();

    /**
    * Get any toplevel menus associated with the manager. 
	* 
    * @return ArrayList<JMenu> The manager menus. 
    */
    public ArrayList<JMenu> getMenus();

	/**
    * Get any menuitems associated with the standard frame menus.
	* 
	* @param menuID MenuID 
	* 
	* @return ArrayList<JMenuItem>
    */
	public ArrayList<JMenuItem> getMenuItems(MenuID menuID);

    /**
    * Get menuitems to be displayed in a popup menu.
    * JGD TODO: Provide some sort of context object that managers can use to determine what, if any, menuitems
    * JGD TODO: should be displayed. This will allow other managers to potentially add menuitems to a local menu,
    * JGD TODO: even if they are not the current manager\tab. For now, I'll only be using the local manager to populate
    * JGD TODO: any local menus.
    *
    * @return ArrayList of Popupmenus. 
    */
    public ArrayList<JMenuItem> getPopupMenus();

    /**
    * Get any toolbar components associated with the manager
    *
	* @param menuID MenuID The ID of the menu being updated. @see IApplicationFram
	* 
    * @return ArrayList<Object> Array with the toolbar components. 
    */
    public ArrayList<Object> getToolbarComponents(MenuID menuID);
    
    /**
    * Get an XML Element containing all the changes made to the manager's containing data.
    *
    * @return Element with the change log for the manager. 
    */ 
    public Element getChangeLog(org.w3c.dom.Document doc);

    /**
    * Perform any post creation initialization. Guarenteed to be called after all managers have been created and 
    * registered with the system. This gets called multiple times for the defined init "phases". The first is the 
    * REGISTER_PHASE which allows managers to register as listeners with other managers and then the LOAD_PHASE, during
    * which any data loading (which may be of interest to those listening) will occur. 
    *
    * @param phase int The initialization phase
    */
    public void initManager(int phase);

    /**
    * Perform any pre-destruction tasks. 
    * This is a post-save, pre-teardown chance for cleanup.
    */
    public void closeManager();

    /**
    * Add a Manager listener.
    * 
    * @param l IFusionManagerListener The listener to add. 
    */
    public void addFusionManagerListener(IFusionManagerListener l);

    /**
    * Remove a Manager Listener
    *
    * @param l IFusionManagerListener The listener to remove. 
    */
    public void removeFusionManagerListener(IFusionManagerListener l);

    /**
    * Fire an update.
    *
    * @param man IFusionManager The manager being updated. 
    */
    public void fireManagerUpdate(IFusionManager man);

    /**
    * Get the state of the manager's dirty flag.
    *
    * @return boolean The state of the manager's local dirty flag. 
    */
    public boolean isDirty();

    /**
    * Set the dirty flag. 
    *
    * @param b boolean The new state of the dirty flag for the manager.
    */
    public void setDirtyFlag(boolean b);

	/**
    * Get Dirty Map. Use document to create DOM elements listing any "dirty" objects controlled 
	* by this manager.
	* 
	* @param doc Document
	* 
	* @return Element Null return values mean nothing is dirty.
    */
	public Element getDirtyMap(Document doc);

    /**
    * Force a refresh of the Manager data.
    */
    public void refreshData();

	/**
    * Get a FusionViewFactory from the manager. It is assumed that the types of data used to request views will be in the perview
	* of the specific manager object (e.g. Views for FusionUser's requested from the factory produced by FusionUserManager).
	* 
	* @return IFusionViewFactory
    */
	public IFusionViewFactory getViewFactory();
}
