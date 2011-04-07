package com.jdouglas.framework.interfaces.data;

import org.w3c.dom.*;
import java.beans.*;
import java.util.*;

/**
* iTData. Interface for base data object in framework.
*  
* @author Jason Douglas 3/28/10 (this version).
*/

public interface iTData
{
    /** XML Property element */
    public static final String XML_PROPERTY_ELEMENT         = "Property";
    /** Element type */
    public static final String XML_ELEMENT_TYPE             = "ElementType";
    /** Key attribute */
    public static final String XML_KEY_ATTRIBUTE            = "KeyAttribute";
    /** Value Attribute */
    public static final String XML_VALUE_ATTRIBUTE          = "ValueAttribute";   
	/** The XML element used to propagate/restore this data object.*/
	public static final String XML_CORE_ELEMENT				= "XMLCoreElement";
	/** XML Parent Document */
	public static final String XML_PARENT_DOCUMENT			= "XMLParentDocument";

    /** Data name */
    public static final String XML_DATA_NAME                = "NAME";
    /** Data Text */
    public static final String XML_DATA_TEXT                = "TEXT";
    /** Data changed flag */
    public static final String XML_DATA_CHANGED             = "CHANGED";
    /** Data added flag */
    public static final String XML_DATA_ADDED               = "ADDED";
    /** Data removed flag */
    public static final String XML_DATA_REMOVED             = "REMOVED";

    /** Uninitialized property */
    public static final String UNINITIALIZED                = "Uninitialized Property";
    /** None selected */
    public static final String NONE_SELECTED                = "NoneSelected";

    /** Common properties. These don't necessarily have to exist for every impl of the interface. */
	/** Display Label (String) */
	public static final String DISPLAY_LABEL				= "displayLabel"; 
    /** ID (Integer) */
    public static final String ID                           = "ID";
    /** Icon for the data (ImageIcon) */
    public static final String ICON                         = "Icon";
    /** User defined data (Boolean) */
    public static final String USER_DEFINED                 = "UserDefined";
    /** Locked prop. Locked data cannot be edited by the user (Boolean) */
    public static final String LOCKED_FLAG                  = "LockedFlag";
	/** Value (String) */
	public static final String VALUE						= "value";
	/** Dirty flag. Prop name used to broadcast event (Boolean) */
	public static final String DIRTY_FLAG					= "isDirtyFlag";
	/** Read Only (Boolean) */
	public static final String READ_ONLY					= "readOnly";
	/** Type (String) */
	public static final String TYPE							= "type";
	/** Temporary Flag (Boolean) */
	public static final String TEMPORARY_FLAG				= "temporaryFlag";
	/** Creation/Modification date time stamp */
	public static final String DATE_TIME_STAMP				= "dateTimeStamp"; 
	/** ENabled Flag (Boolean) */
	public static final String ENABLED_FLAG	   				= "isEnabled";

	/**
	* Get display name. 
	* 
	* @return String 
	*/
	public String getDisplayName();

    /**
    * Return an Element created from the given Document object containing state.
    * 
    * @param doc Document Parent Document to create elements from. 
    * 
    * @return Element The element containing the state of the object.
    */
    public Element storeState(org.w3c.dom.Document doc);

    /**
    * Restore the state of the object using the given element. 
    *
    * @param elem Element Contains state information.
    */
    public void restoreState(Element elem);

    /**
    * Return an Element containing the change log (the delta) for the implementing object.
    *
    * @param doc Document Parent Document to create elements from. 
    * 
    * @return Element The element containing the change log of the object or null if no changes have been made. 
    */
    public Element getChangeLog(org.w3c.dom.Document doc);

    /**
    * Set the Change Log Name. This is used in the change log for display purposes so it needs
    * to be dynamic for locale support.
    *
    * @param name String The change log name. 
    */
    public void setChangeLogName(String name);

    /**
    * Get the Change Log Name. This is used in the change log for display purposes so it needs
    * to be dynamic for locale support.
    *
    * @return String The change Log name. 
    */
    public String getChangeLogName();

    /**
    * Getter. Returns null if the key doesn't have any Object associated with it. 
    *
    * @param key Object The lookup key for the property.
    *
    * @return Object The value associated with the key or null. 
    */
    public Object getProperty(Object key);

    /**
    * Getter as String. You get an empty string upon failure.
    *
    * @param key Object The lookup key for the property.
    *
    * @return String The value associated with the key or an empty string. 
    */
    public String getStringProperty(Object key);

	/**
	* Getter as Boolean. Returns 'false' if the property doesn't exist or cannot be cast to a boolean value.
	*
	* @param key Object The lookup key for the property.
	*
	* @return String The value associated with the key or an empty string. 
	*/
	public boolean getBooleanProperty(Object key);

    /**
    * Setter. These properties will be persistent (via store\restoreState).
    *
    * @param key Object The lookup key for the property.
    * @param value Object The value to be stored via the key. 
    */
    public void setProperty(Object key, Object value);

    /**
    * A unique, immutable string used to store and retrieve data objects in hashmaps. This is not a saved\restored
    * property of the data object being modeled, but a system tool for mapping these objects without relying on a 
    * property that may be changed by the user.  
    *
    * @return String System-unique string. 
    */
    public String getHashKey();

    /**
    * Determines whether the data object should be displayed in the GOO. This is not stored in the database and is
    * determined at runtime. 
    *
    * @return boolean True if the data object is elligible for display. 
    */
    public boolean isVisible();

    /**
    * Set the visibility property for the individual data object. Determines whether the object will be displayed 
    * in the GOO. Not stored in any database and determined at runtime.
    *
    * @param b boolean True if the data is ellible for display. 
    */
    public void setVisible(boolean b);

    /**
    * Get the state of the user defined flag.
    *
    * @return boolean True if the data is user defined. False if imported from 3rd party source.
    */
    public boolean isUserDefined();

    /**
    * Return an XML string of the given type.
    * 
    * @param type int 
    *
    * @return String
    */
    public String getXMLString(int type);

    /**
    * String representation of the data. I don't use toString because I need to overload that for display purposes at times.
    * This string will be a listing of all the properties and values so that we can log it for debug purposes.
    *
    * @return String 
    */
    public String dumpString();

    /**
    * Get the state of the data's dirty flag.
    *
    * @return boolean 
    */
    public boolean isDirty();

    /**
    * Set the data dirty flag for the data object. 
    *
    * @param b boolean
    */
    public void setDirtyFlag(boolean b);

    /**
    * Set the parent iTData object. A null value denotes this is a toplevel data object. 
    *
    * @param parent iTData 
    */
    public void setParent(iTData parent);

    /**
    * Get the parent iTData object. A null return value denotes this is the top level data object. 
    *
    * @return iTData
    */
    public iTData getParent();

    /**
    * Restore the props to the last save point. Discards changes.
    */
    public void restoreFromSavePoint();

    /**
    * Reset the save point. 
    */
    public void resetSavePoint();

    /**
    * Get the Save point 
    * 
    * @return HashMap<Object,Object>
    */
    public HashMap<Object,Object> getSavePoint();

    /**
    * Set the locked flag.
    *
    * @param b boolean 
    */
    public void setLocked(boolean b);

    /**
    * Return the state of the locked flag. "Locked" data typically cannot be edited but the implementor is free to adjust
    * the defintion as necessary.
    *
    * @return boolean 
    */
    public boolean isLocked();

    /**
    * Get IngoredKeys. Some properties are for internal use only and don't need to show up in the audit log (or saved potentially).
    * This method will return an ArrayList with the ignored keys.
    * 
    * @return ArrayList<String>
    */
    public ArrayList<String> getIgnoredKeys();

	/**
    * Get the ID property. Will return null if the property is not set.
	* 
	* @return Integer
    */
	public Integer getID();

    /**
    * Add VetoableChangeListener for all properties.
    * 
    * @param l VetoableChangeListener
    */
    public void addVetoableChangeListener(VetoableChangeListener l);

    /**
    * Remove VetoableChangeListener for all properties.
    *
    * @param l VetoableChangeListener
    */
    public void removeVetoableChangeListener(VetoableChangeListener l);

    /**
    * Add VetoableChangeListener for a specific property.
    * 
    * @param prop String 
    * @param l VetoableChangeListener
    */
    public void addVetoableChangeListener(String prop, VetoableChangeListener l);

    /**
    * Remove VetoableChangeListener for a specific property.
    *
    * @param prop String 
    * @param l VetoableChangeListener
    */
    public void removeVetoableChangeListener(String prop, VetoableChangeListener l);

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
    * Remove PropertyChangeListener
    *
    * @param prop String 
    * @param l PropertyChangeListener
    */
    public void removePropertyChangeListener(String prop, PropertyChangeListener l);
}
