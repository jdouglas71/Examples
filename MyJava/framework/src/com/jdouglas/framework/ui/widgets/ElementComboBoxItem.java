package com.jdouglas.FCAdmin.instruments;

import java.util.*;
import java.text.*;
import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.util.*;

/**
* ElementComboBoxItem. Combobox item wrapper for Elements.
*
* @author Jason Douglas 10/20/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class ElementComboBoxItem
{
	/** The Module name */
    private static final String MODULE_NAME = "ElementComboBoxItem.";

	/** The Element object */
    private Element theElement;
	/** Display attribute (if null, use node value) */
	private String displayAttribute = iTData.DISPLAY_LABEL;
	/** Formatter to use for display */
	private Format theFormatter;
    
    /**
    * Constructor. 
    *
    * @param element Element
	* @param displayAttr String The attribute to use in toString.
	* @param formatter Format 
    */
    public ElementComboBoxItem(Element element, String displayAttr, Format formatter)
    {
        theElement = element;
		displayAttribute = displayAttr;
		theFormatter = formatter;
    }

	/**
	* Constructor. 
	*
	* @param element Element
	*/
	public ElementComboBoxItem(Element element)
	{
		this( element, iTData.DISPLAY_LABEL, null );
	}

    /**
    * Get the Element associated with the item
    *
    * @return Element
    */
    public Element getElement()
    {
        return theElement;
    }

    /**
    * The String representation of the item.
    *
    * @return String
    */
    public String toString()
    {
		String methodName = MODULE_NAME + "toString()";
        String retval = "Null Element";

		try
		{
			if( theElement != null )
			{
				if( displayAttribute != null )
				{
					retval = theElement.getAttribute( displayAttribute );
				}
				else
				{
					retval = FusionUtils.getNodeValue( theElement );
				}
			}
	
			if( theFormatter != null )
			{
				if( theFormatter instanceof DecimalFormat )
				{
					retval = theFormatter.format( new Double(retval) );
				}
				else
				{
					retval = theFormatter.format( retval );
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

        return retval;
    }

    /**
    * Determine equality using the label.
    *
    * @param obj Object
    *
    * @return boolean
    */
    public boolean equals(Object obj)
    {
        String methodName = MODULE_NAME + "equals(Object)";
        boolean retval = false;

        try
        {
            if( obj instanceof ElementComboBoxItem )
            {
                if( obj.toString().intern() == toString().intern() )
                {
                    retval = true;
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }
}
