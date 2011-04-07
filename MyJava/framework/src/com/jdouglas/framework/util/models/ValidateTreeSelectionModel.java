package com.jdouglas.framework.util.models;

import javax.swing.*;
import javax.swing.tree.*;
import java.awt.*;                      
import java.awt.event.*;                        
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;

/**
* This selection model extends the DefaultTreeSelectionModel and is used to fire 
* validate events whenever the selected path is changed. If the validation fails, 
* the statechange will not be fired and the container GOO won't change (e.g. switch tab's 
* or tree nodes).
*
* @author Jason Douglas 9/10/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ValidateTreeSelectionModel
    extends DefaultTreeSelectionModel
{
    /** module name */
    private static final String MODULE_NAME = "ValidateTreeSelectionModel.";

    /** the validators */
    private ArrayList<IValidator> theValidators = new ArrayList<IValidator>();

    /**
    * Constructor.
    */
    public ValidateTreeSelectionModel()
    {
        super();
    }

    /**
    * Sets the selection to path. If this represents a change, then
    * the TreeSelectionListeners are notified. If <code>path</code> is
    * null, this has the same effect as invoking <code>clearSelection</code>.
    *
    * @param path new path to select
    */
    public void setSelectionPath(TreePath path) 
    {
        String methodName = MODULE_NAME + "setSelectionPath(TreePath)";
        boolean fireEvent = true;

        Map<Object,Object> params = new HashMap<Object,Object>();
        params.put( IFrameworkProperties.SELECTION_PATH, path );

        try
        {
            Iterator<IValidator> iter = theValidators.iterator();
            while( iter.hasNext() )
            {
                IValidator validator = iter.next();
                if( validator.validateContents(params) == false )
                {
					Logger.log( methodName + " ValidateContents returned false, eating event.", Logger.CONFIG );
                    fireEvent = false;
                    break;
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        if( fireEvent == true )
        {
            Logger.log( methodName + " passing along new selected path: " + path, Logger.CONFIG );
            super.setSelectionPath( path );
        }
    }

    /**
    * Add a validator
    */
    public void addValidator(IValidator validator)
    {
        theValidators.add( validator );
    }

    /**
    * Remove a validator
    */
    public boolean removeValidator(IValidator validator)
    {
        return theValidators.remove(validator);
    }
}

