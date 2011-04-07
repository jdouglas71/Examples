package com.jdouglas.framework.util;

import java.util.*;

/**
* CommandLineOption. Class to represent a command line option. <br><br>
* JGD NOTE: Interface???
*
* @author Jason Douglas 12/26/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class CommandLineOption
{
    private static final String MODULE_NAME                     = "CommandLineOption.";

    private ArrayList<String> theCmds = new ArrayList<String>();
    private String theDescription;

    private boolean isVisible = true;

    /**
    * Ctor.
    * 
    * @param opts String[]
    * @param desc String
    */
    public CommandLineOption(String[] opts, String desc)
    {
        theDescription = desc;
        
        for(int i=0; i<opts.length; i++)
        {
            theCmds.add( opts[i] );
        }
    }

    /**
    * Get the commands.
    * 
    * @return ArrayList<String>
    */
    public ArrayList<String> getCommands()
    {
        return theCmds;
    }

    /**
    * Get the description.
    *
    * @return String
    */
    public String getDescription()
    {
        return theDescription;
    }

    /**
    * Get the Command Syntax.
    *
    * @return String
    */
    public String getSyntax()
    {
        String methodName = MODULE_NAME + "getSyntax()";
        StringBuffer buf = new StringBuffer();

        buf.append( "[" );
        Iterator iter = theCmds.iterator();
        while( iter.hasNext() )
        {
            buf.append( ((String)iter.next()) + "," );

        }

        //Stomp last comma
        int lastComma = buf.lastIndexOf(",");
        if( lastComma > 0 )
        {
            buf.deleteCharAt( lastComma );
        }
        buf.append( "] " + theDescription );

        return buf.toString();
    }

    /**
    * Invisible commands don't show up in the PrintSyntax list.
    * 
    * @param b boolean
    */
    public void setVisible(boolean b)
    {
        isVisible = b;
    }

    /**
    * Get the visibility flag
    */ 
    public boolean isVisible()
    {
        return isVisible;
    }
}


