package com.jdouglas.framework.util;

import java.util.*;
import javax.swing.filechooser.*;
import java.io.*;

/**
* FusionFileFilter. Generic File filter class. Extends the FileChooser version and makes it better.
*
* @author Jason Douglas 6/24/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class FusionFileFilter
    extends javax.swing.filechooser.FileFilter
{
    private static final String MODULE_NAME = "FusionFileFilter.";

    private ArrayList<String> theSuffixes = new ArrayList<String>();
    private String theDescription;

    /**
    * Ctor. 
    *
    * @param suffixes String Semi-colon delimited string containing the supported suffixes for this filter.
    * @param description String Description for the file type to be displayed to the user.
    */
    public FusionFileFilter(String suffixes, String description)
    {
        theDescription = description;
        StringTokenizer toker = new StringTokenizer( suffixes,";", false);
        while( toker.hasMoreElements() )
        {
            //Standardize on storing everything in upper case.
            theSuffixes.add( ((String)toker.nextElement()).toUpperCase() );
        }
    }

    /**
    * Tests whether or not the specified abstract pathname should be
    * included in a pathname list.
    *
    * @param  file File
    * @return  <code>true</code> if and only if <code>pathname</code>
    *          should be included
    */
    public boolean accept(File file) 
    {
        String methodName = MODULE_NAME + "accept(File)";
        boolean retval = false;

        //Logger.log( MODULE_NAME + methodName + " filename: " + file.getName() );

        //We want to display directories in the fileChooser
        if( file.isDirectory() )
        {
            retval = true;
        }

        //Isn't a directory so we need to check the extension
        if( retval != true ) 
        {
            String suffix = FusionUtils.getExtension(file);
            if( suffix != null )
            {
                Iterator iter = theSuffixes.iterator();
                while( (iter.hasNext()) && (retval == false) )
                {
                    retval = suffix.equalsIgnoreCase( (String)iter.next() );
                }
            }
        }
                                 
        //Logger.log( MODULE_NAME + methodName + " retval: " + retval );
        return retval;
    }

    /**
    * Get the description string displayed in the combo.
    *
    * @return String 
    */
    public String getDescription()
    {
        return theDescription;
    }

    /**
    * Returns the supported extensions. Note that all extension strings are bumped to upper case when added to the list.
    * 
    * @return ArrayList<String>
    */
    public ArrayList<String> getExtensions()
    {
        return theSuffixes;
    }
}
