package com.jdouglas.framework.core;

import javax.swing.*;
import java.util.*;

import com.jdouglas.framework.util.*;

/**
* FusionAction. AbstractAction class wrapper with convience methods for common attributes. All Action classes should
* extend this one rather than AbstractAction directly.
*
* @author Jason Douglas 11/13/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class FusionAction  
    extends AbstractAction
{
    //Const
    private static final String MODULE_NAME                                     = "FusionAction.";
    /** Keystroke property */
    public static final String KEYSTROKE                                        = "KeyStroke";
    /** Visible property */
    public static final String VISIBLE                                          = "VisibleFlag";
	/** Button label */
	public static final String BUTTON_LABEL										= "ButtonLabel";

    /**
    * Constructor
    *
    * @param name String
    * @param keyStroke KeyStroke 
    */
    public FusionAction(String name, KeyStroke keyStroke)
    {
        super(name);
        //JGD Should be array. 
        if( keyStroke != null )
        {
            putValue( KEYSTROKE, keyStroke );
            putValue( Action.ACCELERATOR_KEY, keyStroke );
            putValue( VISIBLE, new Boolean(true) );
        }
    }

    /**
    * Constructon. Null keystroke.
    *
    * @param name String 
    */
    public FusionAction(String name)
    {
        this( name, null );
    }

    /**
    * Returns the name associated with the action.
    *
    * @return String 
    */
    public String getName()
    {
        String retval = "";

        retval = (String)getValue(Action.NAME);

        return retval;
    }

	/**
	* Returns the button label associated with the action.
	*
	* @return String 
	*/
	public String getButtonLabel()
	{
		String retval = "";

		retval = (String)getValue(BUTTON_LABEL);

		return retval;
	}

    /**
    * Returns the keystroke associated with the action.
    *
    * @return KeyStroke
    */
    public KeyStroke getKeyStroke()
    {
        KeyStroke retval;

        retval = (KeyStroke)getValue(KEYSTROKE);

        return retval;
    }

    /**
    * Gets all the keystrokes associated with the action.
    *
    * @return KeyStroke[]
    */
    public KeyStroke[] getKeyStrokes()
    {
        KeyStroke[] retval = new KeyStroke[0];

        KeyStroke tmp = getKeyStroke();
        if( tmp != null )
        {
            retval = new KeyStroke[1];
            retval[0] = tmp;
        }

        return retval;
    }

    /**
    * Returns visible state
    * 
    * @return boolean
    */
    public boolean isVisible()
    {
        String methodName = MODULE_NAME + "isVisible()";
        boolean retval = true;

        try
        {
            Boolean b = (Boolean)getValue(VISIBLE);
            retval = b.booleanValue();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Set visible flag.
    *
    * @param b boolean
    */
    public void setVisible(boolean b)
    {
        putValue( VISIBLE, new Boolean(b) );
    }
}
