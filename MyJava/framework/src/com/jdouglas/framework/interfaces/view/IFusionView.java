package com.jdouglas.framework.interfaces.view;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import javax.swing.*;
import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* IFusionView. Base view interface for framework. NOT USING YET.
*
* @author Jason Douglas 5/16/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public interface IFusionView
    extends VetoableChangeListener,PropertyChangeListener      
{
	/** Label property (String) */
	public static final String LABEL												= "Label";
	/** Component (JComponent). For single component views, I occasionally need access to the component so that I can lay it out with components from other sources. */
	public static final String SINGLE_COMPONENT										= "SingleComponent";

    /**
    * Get the view component.
    *
    * @return JComponent The view component. 
    */
    public JComponent getComponent();

	/**
	* Retrieve the data model.
	* 
	* @return iTData The data model.
	*/
	public iTData getDataModel();

	/**
	* Set the Data Model.
	* 
	* @param data iTData The Data model.
	*/
	public void setDataModel(iTData data);

    /**
    * Getter. Returns null if the key doesn't have any Object associated with it.
    *
    * @param key Object The lookup key for the property.
    *
    * @return Object The value associated with the key or null. 
    */
    public Object getProperty(Object key);

    /**
    * Setter
    *
    * @param key Object The lookup key for the property.
    * @param val Object The value to be stored via the key. 
    */
    public void setProperty(Object key, Object val);

	/**
    * Sets the Enabled flag for the view.
	* NOTE: We don't call this "setEnabled" to make sure we don't accidentally override Component.setEnabled.
	* 
	* @param b boolean
    */
	public void setViewEnabled(boolean b);

	/**
    * Get View enabled flag. 
	* 
	* @return boolean 
    */
	public boolean isViewEnabled();

	/**
    * Set visible flag for the view. 
	* NOTE: We don't call this "setVisible" so we don't accidentally override Component.setVisible.
	* 
	* @param b boolean
    */
	public void setViewVisible(boolean b);

	/**
    * Get the visible flag for the view. 
	* 
	* @return boolean 
    */
	public boolean isViewVisible();

	/**
	* Rebuild the contained goo elements based on the current configuration/data model.
	* Basically reinitializes the panel ui. 
	*/
	public void refreshContents();

	/**
	* Resets the panel contents to the values stored in the data model.
	* Differs from refreshContents in the sense that it doesn't rebuild the gui. 
	*/
	public void resetContents();

	/**
    * Add a listener to the view. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void addListener(Object listener, Class listenerType);

    /**
    * Remove a listener to the view. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void removeListener(Object listener, Class listenerType);

	/**
	* Get a listener from the view. If the view supports a listener of the specified type, it will return it, otherwise 
	* it will return null.
	*
	* @param listenerType Class The type of listening the listener would like to do. 

	* @return Object The listener or null.
	*/
	public Object getListener(Class listenerType);

	/**
	* Add PropertyChangeListener
	* 
	* @param l PropertyChangeListener
	*/
	public void addPropertyChangeListener(PropertyChangeListener l);

	/**
	* Remove PropertyChangeListener
	*
	* @param l PropertyChangeListener
	*/
	public void removePropertyChangeListener(PropertyChangeListener l);

	/**
	* Add PropertyChangeListener for a specific property
	* 
	* @param prop String 
	* @param l PropertyChangeListener
	*/
	public void addPropertyChangeListener(String prop, PropertyChangeListener l);

	/**
	* Store any view state parameters (e.g. splitter pos). There are no required parameters so 
	* anything stored here is optional for the view.
	*
	* @param doc Document Parent Document to create elements from. 
	* 
	* @return Element The element containing the state of the object.
	*/
	public Element storeViewState(org.w3c.dom.Document doc); 

	/**
	* Restore any view state parameters that may have been stored by this view.
	*
	* @param elem Element Contains state information.
	*/
	public void restoreViewState(Element elem);

}
