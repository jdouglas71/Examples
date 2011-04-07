package com.jdouglas.framework.core;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.border.*;
import org.w3c.dom.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* FusionView. Base implementation of the view class. 
*
* @author Jason Douglas 11/10/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionView
    extends JPanel
        implements IFusionView
{
	/** Module name */
    private static final String MODULE_NAME                                                             = "FusionView.";

	/** Enabled flag for the view */
	private boolean isViewEnabled = true;
	/** Visible flag for the view */
	private boolean isViewVisible = true;

    /** Panel properties */
    private HashMap<Object,Object> theProps = new HashMap<Object,Object>();
	/** PropertyChangeSupport. Manages the PropertyChangeEvents. */
	private PropertyChangeSupport thePropertyChangeSupporter = new PropertyChangeSupport(this);

    /**
    * Constructor
    */
    protected FusionView()
    {
    }

    //*******************************************************************************//
    // IFusionView impl
    //

    /**
    * Getter. Returns null if the key doesn't have any Object associated with it.
    *
    * @param key Object The lookup key for the property.
    *
    * @return Object The value associated with the key or null. 
    */
    public Object getProperty(Object key)
    {
        String methodName = MODULE_NAME + "getProperty(Object)";
        Object retval = null;

        try
        {
            retval = theProps.get( key );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
        
        return retval;
    }

    /**
    * Setter
    *
    * @param key Object The lookup key for the property.
    * @param value Object The value to be stored via the key. 
    */
    public void setProperty(Object key, Object value)
    {
        final String methodName = MODULE_NAME + "setProperty(Object,Object)";

		//Normal Property handling
		try
		{
			final PropertyChangeEvent pcEvent = new PropertyChangeEvent( this, key.toString(), theProps.get(key), value );
			final String keyName = key.toString();

			//If we got here, it's ok to set the property value
			theProps.put( key, value );

			if( thePropertyChangeSupporter.hasListeners((String)key) )
			{
				if( SwingUtilities.isEventDispatchThread() )
				{
					//Notify
					thePropertyChangeSupporter.firePropertyChange( pcEvent );
				}
				else
				{
					//Create worker thread to make sure the change is handled on the AWT thread.
					FusionWorker worker = new FusionWorker() 
					{
						/**
						* Worker thread method.
						*/
						public Object construct()
						{
							try
							{
								//Nothing to do here. 
							}
							catch(Exception xx)
							{
								FusionUtils.logError( methodName, "Failed", xx );
							}

							return null;
						}

						/**
						* Event Queue thread method.
						*/
						public void finished()
						{
							//We have to fire the propertyChangeEvent on the AWT thread!?! Probably safer in the long run, but we could do some very nice things if 
							//we could ensure that this event would be handled off the GUI thread... JGD 5/2/08
							thePropertyChangeSupporter.firePropertyChange( pcEvent );
						}
					};

					worker.start();
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "failed", e );
		}
    }

    /**
    * Refresh the contained goo elements based on the current configuration/data model.
    */
    public void refreshContents() 
    {
        String methodName = MODULE_NAME + "refreshContents()";
    }

    /**
    * Accessor for the data model.
    * 
    * @return iTData The data model.
    */
    public iTData getDataModel() 
    {
        String methodName = MODULE_NAME + "getDataModel()";

        return null;
    }
    
    /**
    * Set the data model.
    *
    * @param data iTData The new Data model 
    */
    public void setDataModel(iTData data) 
    {
        String methodName = MODULE_NAME + "setDataModel(iTData)";
    }

	/**
	* Sets the Enabled flag for the view.
	* NOTE: We don't call this "setEnabled" to make sure we don't accidentally override Component.setEnabled.
	* 
	* @param b boolean
	*/
	public void setViewEnabled(boolean b)
	{
		String methodName = MODULE_NAME + "setViewEnabled(boolean)";
		isViewEnabled = b;
		//JGD TODO: Fire property change event for this.
	}

	/**
	* Get View enabled flag. 
	* 
	* @return boolean 
	*/
	public boolean isViewEnabled()
	{
		return isViewEnabled;
	}

	/**
	* Set visible flag for the view. 
	* NOTE: We don't call this "setVisible" so we don't accidentally override Component.setVisible.
	* 
	* @param b boolean
	*/
	public void setViewVisible(boolean b)
	{
		String methodName = MODULE_NAME + "setViewVisible(boolean)";

		isViewVisible = b;

		//JGD TODO: Fire property change event. 
	}

	/**
	* Get the visible flag for the view. 
	* 
	* @return boolean 
	*/
	public boolean isViewVisible()
	{
		return isViewVisible;
	}

    /**
    * Resets the panel contents to the values stored in the data model.
    */
    public void resetContents()
    {
        String methodName = MODULE_NAME + "resetContents()";
    }

    /**
    * Get the Component/View.
    * 
    * @return JComponent The view Component. 
    */
    public JComponent getComponent() 
    {
        return this;
    }

    /**
    * Add a listener to the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void addListener(Object listener, Class listenerType)
    {
        String methodName = MODULE_NAME + "setListener(Object,Class)";

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Remove a listener from the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void removeListener(Object listener, Class listenerType)
    {
        String methodName = MODULE_NAME + "removeListener(Object,Class)";

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Get a listener from the panel. If the panel supports a listener of the specified type, it will return it, otherwise 
    * it will return null.
    *
    * @param listenerType Class The type of listening the listener would like to do. 
    
    * @return Object The listener or null.
    */
    public Object getListener(Class listenerType)
    {
        String methodName = MODULE_NAME + "getListener(Class)";
        Object retval = null;

        try
        {
            Class[] interfaces = this.getClass().getInterfaces();
            for(int i=0; i<interfaces.length; i++)
            {
                if( interfaces[i].equals( listenerType ) )
                {
                    retval = this;
                    break;
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

	/**
	* Store any view state parameters (e.g. splitter pos). There are no required parameters so 
	* anything stored here is optional for the view.
	*
	* @param doc Document Parent Document to create elements from. 
	* 
	* @return Element The element containing the state of the object.
	*/
	public Element storeViewState(org.w3c.dom.Document doc)
	{
		return null;
	}

	/**
	* Restore any view state parameters that may have been stored by this view.
	*
	* @param elem Element Contains state information.
	*/
	public void restoreViewState(Element elem)
	{
	}

	/**
	* Add PropertyChangeListener
	* 
	* @param l PropertyChangeListener
	*/
	public void addPropertyChangeListener(PropertyChangeListener l)
	{
		thePropertyChangeSupporter.addPropertyChangeListener( l );
	}

	/**
	* Remove PropertyChangeListener
	*
	* @param l PropertyChangeListener
	*/
	public void removePropertyChangeListener(PropertyChangeListener l)
	{
		thePropertyChangeSupporter.removePropertyChangeListener( l );
	}

	/**
	* Add PropertyChangeListener for a specific property
	* 
	* @param prop String 
	* @param l PropertyChangeListener
	*/
	public void addPropertyChangeListener(String prop, PropertyChangeListener l)
	{
		thePropertyChangeSupporter.addPropertyChangeListener( prop, l );
	}
    //**********************************************************************************************************//
    // VetoableChangeListener impl
    //
    /**
    * This method gets called when a constrained property is changed.
    *
    * @param     evt a <code>PropertyChangeEvent</code> object describing the
    *            event source and the property that has changed.
    * @exception PropertyVetoException if the recipient wishes the property
    *              change to be rolled back.
    */
    public void vetoableChange(PropertyChangeEvent evt)
        throws PropertyVetoException
    {

    }
    // VetoableChangeListener impl

    //**********************************************************************************************************//
    // PropertyChangeListener impl
    //
    /**
    * This method gets called when a bound property is changed.
    * @param evt A PropertyChangeEvent object describing the event source 
    *      and the property that has changed.
    */
    public void propertyChange(PropertyChangeEvent evt)
    {

    }
    // PropertyChangeListener impl ends

    // IFusionView impl ends (PARTIAL IMPL, ABSTRACT CLASS)
}
    
