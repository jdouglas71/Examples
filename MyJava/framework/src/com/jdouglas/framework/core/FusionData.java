package com.jdouglas.framework.core;

import java.util.*;
import java.beans.*;
import javax.swing.*;
import org.w3c.dom.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.util.*;

/**
* FusionData. Base implementation of iTData. Anyone wanting to implement iTData should extend this class.<BR><BR>
* 
* Notes: I want to get the property and hashkey code that is redundant to all iTData impl's in one place. 
*        Not entirely sure what impact this will have on my objects implementing extened iTData interfaces 
*        (e.g. IFusionUser) to have them now extending this class. Shouldn't be a problem? <BR><BR>
*  
*        I don't intend for this to live in the util package in the framework structure. Just a place for it now while 
*        I explore the concept.<br><br>
*
*        -- This is working out very well. I'm sticking with the default impl concept moving forward with framework. JGD 8/3/05 <br><br>
*
* TODO: <br><br>
*       -- It would be cool if we put the properties under change control via listeners so that changes could be broadcast
*          and potentially vetoed. This could be very powerful moving forward. Components could listen for prop changes and update 
*          as appropriate, greatly lessening the need for protective logic in the set calls thru out the codebase. Sometimes I think
*          it's overkill, but I think over time and as complexity grows it will be valuable. JGD 8/3/05
*          JGD 4/12/06 (Happy Birthday Patrick!) The iTData interface now support VetoableChangeListeners and IEditorPanel has been 
*          changed to now extend VetoableChangeListener and PropertyChangeListener so that we can broadcast and allow to be rejected, 
*          property changes. <br><br>
*          
* Cloning: Cloning Objects can be problematic. The default impl for collections only does a shallow copy, meaning that the cloned collection
*          is still pointing to the same objects as the original collection. In order to do a deep copy (where your cloned collection is pointing 
*          to completely new objects with the same values as the original), you must implement a serious amount of code in multiple objects and still
*          hope that every object you are storing in your collection does the right thing. Instead, what we're going to do for FusionData is assume that
*          our underlying storage mechanism is XML, and use the Element that was used to create the data object to clone the data object. The hole in this 
*          approach is new data objects, but in that case, we're just going to have to generate the xml on the fly. We're going to need it at some point anyway....
* 	        Jason Douglas 4/27/08
* 
*          
* @author Jason Douglas 2/4/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionData
        implements iTData
{
    /** Module Name */
    private static final String MODULE_NAME = "FusionData.";

	/** Core XML Element */
	private Element theCoreElement; 
    /** The property map, protected to allow decendent access */
    protected HashMap<Object,Object> theProps;
	/** The type map for the prop keys. If we know what class the value associated with a key should be, we store it here. */
	protected HashMap<Object,Class> thePropTypes;
    /** The property save point Map. Protected to allow decendent access */
    private HashMap<Object,Object> theSavedProps;

    /** Internal property to give a way to differentiate btwn data objects. Useful when storing data objects in a map so you don't have to rely a property that may be changed by the user */
    private String hashKey;
    /** Top level name of the change log XML */
    private String changeLogName;
    /** Visible flag. When false, the data will not be displayed in the GOO */
    private boolean isVisible = true;
    /** Dirty flag */
    private boolean isDirty = false;
    /** Parent object, Can be null */
    private iTData theParent;

    /** VetoableChangeSupport. Manages the VetoableChangeEvents */
    private VetoableChangeSupport theVetoableChangeSupporter;
    /** PropertyChangeSupport. Manages the PropertyChangeEvents. */
    private PropertyChangeSupport thePropertyChangeSupporter;

    /**
    * Constructor
    */
    public FusionData()
    {
		theVetoableChangeSupporter = new VetoableChangeSupport(this); 
		thePropertyChangeSupporter = new PropertyChangeSupport(this); 
		theProps = new HashMap<Object,Object>();
		thePropTypes = new HashMap<Object,Class>();

        hashKey = FusionUtils.generateHashKey();

        changeLogName = "UNINITIALIZED";
    }

	/**
    * Data toString representation is the display name if set.
	* 
	* @return String 
    */
	@Override
	public String toString()
	{
		String retval = null;
		retval = getDisplayName();
		if( retval == null )
		{
			retval = super.toString();
		}

		return retval;
	}

    //*****************************************************************************************//
    // iTData impl
	// 

	/**
    * Get display name. 
	* 
	* @return String 
    */
	public String getDisplayName()
	{
		return getStringProperty(DISPLAY_NAME);
	}

    /**
    * In this section, we'll be checking for properties that have been added since we shipped and                      
    * adding them to the restored data with default values in an attempt to do the right thing. Note that we do this 
    * AFTER we save off the delta so that the changes will appear in the change log. We are not cheaters.              
    */
    private void updateProperties()
    {
        String methodName = MODULE_NAME + "updateProperties()";
        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Return an Element created from the given Document object containing state.
    * 
    * @param doc Document Parent Document to create elements from. 
    * 
    * @return Element The element containing the state of the object.
    */
    public Element storeState(org.w3c.dom.Document doc)
    {
        return null;
    }

    /**
    * Restore the state of the object using the given element
    *
    * @param elem Element Contains state information.
    */
    public void restoreState(Element elem)
    {
		String methodName = MODULE_NAME + "restoreState(Element)";

		//Here's where we snag the element so we can use it later for cloning
		theCoreElement = elem;
    }

    /**
    * Return an Element containing the change log (the delta) for the implementing object.
    *
    * @param doc Document Parent Document to create elements from. 
    * 
    * @return Element The element containing the change log of the object or null if no changes have been made. 
    */
    public Element getChangeLog(org.w3c.dom.Document doc)
    {
        return null;
    }

    /**
    * Set the Change Log Name. This is used in the change log for display purposes so it needs
    * to be dynamic for locale support.
    *
    * @param name String The change log name. 
    */
    public void setChangeLogName(String name)
    {
        changeLogName = name;
    }

    /**
    * Get the Change Log Name. This is used in the change log for display purposes so it needs
    * to be dynamic for locale support.
    *
    * @return String The change Log name. 
    */
    public String getChangeLogName()
    {
        return changeLogName;
    }

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
			if( key.equals(XML_CORE_ELEMENT) )
			{
				retval = theCoreElement;
			}
			else
			{
				retval = theProps.get( key );
			}
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
            retval = null;
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
        try
        {
			//Here's where we catch properties that we don't intend to store in the map. 
			if( key.equals(XML_CORE_ELEMENT) )
			{
				if( value instanceof Element )
				{
					theCoreElement = (Element)value;
				}
				//Bail out. We don't want to process this as normal.
				return;
			}

			//Normal Property handling
            try
            {
                final PropertyChangeEvent pcEvent = new PropertyChangeEvent( this, key.toString(), theProps.get(key), value );
                final String keyName = key.toString();

				//Will throw exception if something objects
                theVetoableChangeSupporter.fireVetoableChange( pcEvent );
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
            catch(PropertyVetoException pve)
            {
                Logger.log( methodName + " PropertyVetoException caught. " + pve.getMessage(), Logger.DEBUG );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
        }
    }

    /**
    * Getter as String. You get an empty string upon failure.
    *
    * @param key Object The lookup key for the property.
    *
    * @return String The value associated with the key or an empty string. 
    */
    public String getStringProperty(Object key)
    {
        String methodName = MODULE_NAME + "getStringProperty(Object)";
        String retval = "";

        try
        {
            Object obj = getProperty( key );
            if( obj != null )
            {
                retval = obj.toString();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
            retval = "";
        }

        //I'm tempted to call trim here, but I think it's possible that a property may consist entirely of whitespace. At least 
        //I'm I'm sure I could contrive a way that's possible... JGD 8/4/05
        return retval;
    }

	/**
	* Getter as boolean. Will return false if the property doesn't exist or cannot be cast to a Boolean. 
	*
	* @param key Object The lookup key for the property.
	*
	* @return boolean The value associated with the key.. 
	*/
	public boolean getBooleanProperty(Object key)
	{
		String methodName = MODULE_NAME + "getBooleanProperty(Object)";
		boolean retval = false;

		try
		{
			Object obj = getProperty( key );
			if( obj != null && obj instanceof Boolean )
			{
				retval = ((Boolean)obj).booleanValue();
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "failed", e );
		}

		//if( key.equals("ResetStages") )
		//{
		//	Logger.log( methodName + " key: " + key + " value: " + retval, Logger.DEBUG );
		//} 

		return retval;
	}

    /**
    * A unique, immutable string used to store and retrieve data objects in hashmaps. This is not a saved\restored
    * property of the data object being modeled, but a system tool for mapping these objects without relying on a 
    * property that may be changed by the user.  
    *
    * @return String System-unique string. 
    */
    public String getHashKey()
    {
        return hashKey;
    }

    /**
    * Determines whether the data object should be displayed in the GOO. This is not stored in the database and is
    * determined at runtime. 
    *
    * @return boolean True if the data object is elligible for display. 
    */
    public boolean isVisible()
    {
        return isVisible;
    }

    /**
    * Set the visibility property for the individual data object. Determines whether the object will be displayed 
    * in the GOO. Not stored in any database and determined at runtime.
    *
    * @param b boolean True if the data is ellible for display. 
    */
    public void setVisible(boolean b)
    {
        isVisible = b;
    }

    /**
    * Get the state of the user defined flag.
    *
    * @return boolean True if the data is user defined. False if imported from 3rd party source.
    */
    public boolean isUserDefined()
    {
        String methodName = MODULE_NAME + "isUserDefined()";
        boolean retval = true; //default to true. The false case is special. 

        try
        {
            retval = getBooleanProperty(USER_DEFINED);
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Return an XML string of the given type.
    * JGD TODO: Is this really the way I want to do this?
    *
    * @param type int 
    *
    * @return String
    */
    public String getXMLString(int type)
    {
		String methodName = MODULE_NAME + "getXMLString(int)";
		String retval = methodName + " No element defined for this data.";

		try
		{
			if( theCoreElement != null )
			{                         
				retval = FusionUtils.getXMLString( theCoreElement, true );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

        return retval;
    }

    /**
    * String representation of the data. I don't use toString because I need to overload that for display purposes at times.
    * This string will be a listing of all the properties and values so that we can log it for debug purposes.
    *
    * @return String 
    */
    public String dumpString()
    {
        String methodName = MODULE_NAME + "dumpString()";
        String retval = "";

        try
        {
            StringBuffer strBuf = new StringBuffer();

            Iterator iter = theProps.entrySet().iterator();
            while( iter.hasNext() )
            {
                Map.Entry entry = (Map.Entry)iter.next();
                strBuf.append( entry.getKey() + " = " + entry.getValue() + "\n" );
            }

            retval = strBuf.toString();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Get the state of the data's dirty flag.
    *
    * @return boolean 
    */
    public boolean isDirty()
    {
        return isDirty;
    }

    /**
    * Set the data dirty flag. 
    *
    * @param b boolean
    */
    public void setDirtyFlag(boolean b)
    {
        String methodName = MODULE_NAME + "setDirtyFlag(boolean)";
        isDirty = b;

		//Setting the flag as a property so it can be broadcast
		setProperty( DIRTY_FLAG, new Boolean(b) );

		//The parent should be set to dirty as well.
		if( b && (getParent() != null) )
		{
			getParent().setDirtyFlag( b );
		}

        //It's useful to log dirty flag sets for debug purposes.
        Logger.log( methodName + " b: " + b + " for " + getStringProperty(DISPLAY_NAME), Logger.CONFIG );
    }

    /**
    * Set the parent iTData object. A null value denotes this is a toplevel data object. 
    *
    * @param parent iTData 
    */
    public void setParent(iTData parent)
    {
        theParent = parent;
    }

    /**
    * Get the parent iTData object. A null return value denotes this is the top level data object. 
    *
    * @return iTData
    */
    public iTData getParent()
    {
        return theParent;
    }

    /**
    * Restore the props to the last save point. Discards changes.
    */
    public void restoreFromSavePoint()
    {
        String methodName = MODULE_NAME + "restoreFromSavePoint()";

        //JGD TODO commented out for now since I don't expose the resetContents actions yet and I wanted to make
        //JGD TODO sure this wasn't killing me. 8/31/06

        //Logger.log( methodName + " called for namme: " + getStringProperty(DISPLAY_NAME), Logger.CONFIG );

        //theProps = theSavedProps;
    }

    /**
    * Reset the save point. 
    */
    public void resetSavePoint()
    {
        String methodName = MODULE_NAME + "resetSavePoint()";

		//JGD NOTE: This is faulty. It is not a deep copy, so actual objects that are in Props will also be in SavedProps, meaning that
		//JGD NOTE: if something changes the object without replacing it (a logical move), the change will be in both Maps and thus not
		//JGD NOTE: picked up in the audit log. NEed a deep copy or an xml log. 

        theSavedProps = new HashMap<Object,Object>( theProps );
    }

    /**
    * Get the Save point 
    * 
    * @return HashMap<Object,Object>
    */
    public HashMap<Object,Object> getSavePoint()
    {
        String methodName = MODULE_NAME + "getSavePoint()";

        return theSavedProps;
    }

    /**
    * Set the locked flag.
    *
    * @param b boolean 
    */
    public void setLocked(boolean b)
    {
        String methodName = MODULE_NAME + "setLocked(boolean)";

        setProperty( LOCKED_FLAG, new Boolean(b) );
    }

    /**
    * Return the state of the locked flag. "Locked" data typically cannot be edited but the implementor is free to adjust
    * the defintion as necessary.
    *
    * @return boolean 
    */
    public boolean isLocked()
    {
        String methodName = MODULE_NAME + "isLocked()";
        boolean retval = false;
        
        try
        {
            retval = getBooleanProperty(LOCKED_FLAG);
        }
        catch(Exception e)
        {
            //I don't care.
        }

        return retval;
    }

	/**
	* Get IngoredKeys. Some properties are for internal use only and don't need to show up in the audit log (or saved potentially).
	* This method will return an ArrayList with the ignored keys.
	* 
	* @return ArrayList<String>
	*/
	public ArrayList<String> getIgnoredKeys()
	{
		return new ArrayList<String>();
	}

	/**
	* Get the precision.
	* 
	* @return int
	*/
	public int getPrecision()
	{
		String methodName = MODULE_NAME + "getPrecsion()";
		int retval = -1;

		try
		{
			Integer prec = (Integer)getProperty(PRECISION);
			if( prec != null )
			{
				retval = prec.intValue();
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
	* Get the ID property. Will return null if the property is not set or the property is not an Integer or parsable into an Integer.
	* 
	* @return Integer
	*/
	public Integer getID()
	{
		String methodName = MODULE_NAME + "getID()";
		Integer retval = null;

		try
		{
			Object obj = getProperty(ID);
			if( obj instanceof String )
			{
				retval = new Integer( (String)obj );
			}
			else if( obj instanceof Integer )
			{
				retval = (Integer)obj;
			}
		}
		catch(Exception e)
		{
			//Don't care 
			retval = null;
		}

		return retval;
	}

    /**
    * Add VetoableChangeListener for all properties.
    * 
    * @param l VetoableChangeListener
    */
    public void addVetoableChangeListener(VetoableChangeListener l)
    {
        theVetoableChangeSupporter.addVetoableChangeListener( l );
    }

    /**
    * Remove VetoableChangeListener for all properties.
    *
    * @param l VetoableChangeListener
    */
    public void removeVetoableChangeListener(VetoableChangeListener l)
    {
        theVetoableChangeSupporter.removeVetoableChangeListener( l );
    }

    /**
    * Add VetoableChangeListener for a specific property.
    * 
    * @param prop String 
    * @param l VetoableChangeListener
    */
    public void addVetoableChangeListener(String prop, VetoableChangeListener l)
    {
        theVetoableChangeSupporter.addVetoableChangeListener( prop, l );
    }

    /**
    * Remove VetoableChangeListener for a specific property.
    *
    * @param prop String 
    * @param l VetoableChangeListener
    */
    public void removeVetoableChangeListener(String prop, VetoableChangeListener l)
    {
        theVetoableChangeSupporter.removeVetoableChangeListener( prop, l );
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

    /**
    * Remove PropertyChangeListener
    *
    * @param prop String 
    * @param l PropertyChangeListener
    */
    public void removePropertyChangeListener(String prop, PropertyChangeListener l)
    {
        thePropertyChangeSupporter.removePropertyChangeListener( prop, l );
    }
    // iTData impl ends


	/**
    * Fire a property change event. 
	* 
	* @param evt PropertyChangeEvent 
    */
	protected void firePropertyChange(final PropertyChangeEvent evt)
	{
		final String methodName = MODULE_NAME + "firePropertyChange(PropertyChangeEvent)";
	
		try
		{

			if( thePropertyChangeSupporter.hasListeners(evt.getPropertyName()) )
			{
				if( SwingUtilities.isEventDispatchThread() )
				{
					//Notify
					thePropertyChangeSupporter.firePropertyChange( evt );
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
							thePropertyChangeSupporter.firePropertyChange( evt );
						}
					};

					worker.start();
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}
}
