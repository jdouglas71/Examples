package com.jdouglas.framework.util;

import java.io.*;
import java.util.*;

/**
* DebugException. Just something I'm thinking about right now. Potentially an exception class that would only be handled
* when running in a debug or verbose mode. Allows developers to throw exceptions around during development and leave the 
* code in so that it can be activated in the field via the command line (e.g. the logger class). It would be ideal to make
* use of the "chained exceptions" support built into throwable via the cause property.
*
* @author Jason Douglas 6/14/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class DebugException
    extends Exception
{
    private static final String MODULE_NAME                                 = "DebugException.";

    /**
    * Ctor.
    *
    * @param message String 
    */
    public DebugException(String message)
    {
        super(message);
    }
}

