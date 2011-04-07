package com.jdouglas.framework.ui.widgets;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.data.*;

/**
* A JTextField that only accepts numbers as input.<br><br>
* 
* JGD TODO: Handle values entered via cut and paste. <br><br>
* JGD TODO: Override more of the JTextField Ctors. <br><br>
*
* @author Jason Douglas 9/22/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class NumberTextField 
    extends JTextField
        implements KeyListener
{
	/** Module name */
    private static final String MODULE_NAME                 = "NumberTextField.";

	/** Keep the character flag. Flag for keeping non-numeric characters we care about. */
    private boolean keepCharFlag = false;
	/** the overarching data object, if it exists. Used to set dirty flag */
    private iTData theData;

    /**
	* Constructor.
	* 
	* @param numCols int
    */
    public NumberTextField(int numCols)
    {
        super( numCols );
        init();
    }

    /**
    * The number of display col's and a data to notify.
	* 
	* @param numCols int
	* @param data iTData.
    */
    public NumberTextField(int numCols, iTData data)
    {
        this( numCols );
        setDataModel( data );
    }

    /**
    * Initial text value and number of display col's
	* 
	* @param text String
	* @param numCols int
    */ 
    public NumberTextField(String text, int numCols)
    {
        super( text, numCols );
        init();
    }

    /**
    * Initial Text value and number of display col's, plus a manager to notify
    * 
	* @param text String
	* @param numCols int
	* @param data iTData.
    */
    public NumberTextField(String text, int numCols, iTData data)
    {
        this( text, numCols );
        setDataModel( data );
    }

    /**
    * Initializer function.
    */
    private void init()
    {
        String methodName = MODULE_NAME + "init()";
        try
        {
            addKeyListener( this );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Set a data object to be notified (via setDirty) when the textfield has been updated.
	* 
	* @param data iTData.
    */
    public void setDataModel(iTData data)
    {
        theData = data;
    }

    //********************************************************************************//
    // KeyListener impl
    //
    /**
    * Filter the input of the JTextField.
	* 
	* @param e KeyEvent
    */
    public void keyTyped(KeyEvent e)
    {
        String methodName = MODULE_NAME + "keyTyped(KeyEvent)";
        try
        {
            //JGD We're filtering everything but numeric characters if isNumeric is set.
            char keyChar = e.getKeyChar();
            int keyCode = e.getKeyCode();         
			
            if( (Character.isDigit(keyChar) != true) &&
                (keepCharFlag == false) )
            {
                //Eat the event so it isn't processed by the source object (in this case the JTextField)
                //Logger.log( methodName + " Eating keystroke! ", Logger.FINEST  );
                e.consume();
            }
            else
            {
                if( theData != null )
                {
                    theData.setDirtyFlag( true );
                }
            }
        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Failed", x );
        } 
    }

    /**
    * Invoked when a key has been pressed. 
    * See the class description for {@link KeyEvent} for a definition of 
     * a key pressed event.
	* @param e KeyEvent
    */
    public void keyPressed(KeyEvent e)
    {
        String methodName = MODULE_NAME + "keyPressed(KeyEvent)";
		DecimalFormatSymbols decSyms = new DecimalFormatSymbols();
        try
        {
            int keyCode = e.getKeyCode();         
            if( (keyCode == KeyEvent.VK_BACK_SPACE) ||
			    (keyCode == decSyms.getDecimalSeparator()) ||
			    (keyCode == decSyms.getGroupingSeparator()) ||
			    (keyCode == decSyms.getMinusSign()) )
            {
                keepCharFlag = true;
            }
            else 
            {
                keepCharFlag = false;
                //JGD just for the record, I don't really need an if statement for this, but this way is easier to debug
            }
        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Failed", x );
        }
    }

    /**
    * Invoked when a key has been released.
    * See the class description for {@link KeyEvent} for a definition of 
    * a key released event.
	* @param e KeyEvent
    */
    public void keyReleased(KeyEvent e)
    {
        String methodName = MODULE_NAME + "keyReleased(KeyEvent)";
    }
    // KeyListener impl ends

}

