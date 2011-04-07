package com.jdouglas.framework.util.models;

import javax.swing.*;
import java.awt.*;                      
import java.awt.event.*;                        
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;

/**
* This selection model extends the DefaultSingleSelectionModel and is used to fire 
* validate events whenever the selected index is changed. If the validation fails, 
* the statechange will not be fired and the container GOO won't change (e.g. switch tab's 
* or tree nodes).
*
* @author Jason Douglas 9/10/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ValidateSingleSelectionModel
    extends DefaultSingleSelectionModel
{
    //Const 
    private static final String MODULE_NAME = "ValidateSingleSelectionModel.";

    //Data
    private ArrayList<IValidator> theValidators;

    /**
    * Ctor
    */ 
    public ValidateSingleSelectionModel()
    {
        super();

        theValidators = new ArrayList<IValidator>();
    }


    /**
    * This is where we override the parent class. We want to validate the contents of the current selection, preventing 
    * the index from changing if the validation fails.
    *
    * The selection model doesn't actually know what the selected object is, it just fires events. So that's what we'll 
    * do for the validators. We cycle thru and tell them the current index, and they determine if they care and validate 
    * accordingly. Validators are responsible for informing the user of the validation failure.
    * 
    * Jason Douglas 9/10/03
    *
    * @param index int 
    */
    public void setSelectedIndex(int index)
    {   
        String methodName = MODULE_NAME + "setSelectedIndex(int)";
        boolean fireEvent = true;

        Map<Object,Object> params = new HashMap<Object,Object>();
        params.put( IFrameworkProperties.SELECTION_INDEX, new Integer(index) );

        try
        {
            Iterator<IValidator> iter = theValidators.iterator();
            while( iter.hasNext() )
            {
                IValidator validator = iter.next();
                if( validator.validateContents(params) == false )
                {
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
            Logger.log( methodName + " passing along new selected Index: " + index, Logger.FINEST );
            super.setSelectedIndex( index );
        }
    }

    /**
    * Add a validator
    *
    * @param validator IValidator
    */
    public void addValidator(IValidator validator)
    {
        theValidators.add( validator );
    }

    /**
    * Remove a validator
    *
    * @param validator IValidator
    *
    * @return boolean <code>true</code> if the validator was successfully removed. 
    */
    public boolean removeValidator(IValidator validator)
    {
        return theValidators.remove(validator);
    }
}
                                       
