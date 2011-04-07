package com.jdouglas.framework.core.events;

import java.util.*;
import javax.swing.event.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.listeners.*;

/**
* FusionEvent. Base class for events. 
*
* @author Jason Douglas 4/2/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class FusionEvent
{
    /** Module Name */
    private static final String MODULE_NAME                                                                 = "FusionEvent.";

    /** Map of properties */
    private HashMap<String,Object> theProps = new HashMap<String,Object>();

    /** 
    * Get Property 
    * 
    * @param key String
    * 
    * @return Object 
    */
    public Object getProperty(String key)
    {
        return theProps.get(key);
    }

    /** 
    * Set property. 
    *
    * @param key String
    * @param val Object
    */
    public void setProperty(String key, Object val)
    {
        theProps.put( key, val );
    }
}

