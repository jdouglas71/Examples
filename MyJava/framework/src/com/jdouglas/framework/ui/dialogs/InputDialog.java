package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* InputDialog. The messageboxes provided by JOptionPane don't work as well as mine.
* 
* @author Jason Douglas 6/17/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class InputDialog
    extends OkDialog
        implements FocusListener
{
	/** Module Name */
    public static final String MODULE_NAME = "InputDialog.";

	/** Controls */
    private JLabel messageLabel;
    private JTextField inputField;
	/** the message string */
    private String messageStr;
	/** is Numeric Flag */
    private boolean isNumeric = false;

    /**
    * Constructor. Uses the JOptionPane constants (why reinvent?)  
	* 
	* @param parent Frame
	* @param message String
	* @param isNumericOnly boolean
    */
    public InputDialog(Frame parent, String message, boolean isNumericOnly)
    {
        super(OK_CANCEL_DIALOG);

        messageStr = message;
        isNumeric = isNumericOnly;
        
        //JGD TODO Base size on the message string...
        setSize( 300, 120 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );
        setResizable(false);

        //Just in case this hasn't been set yet
        if( (FusionApplication.getApplicationFrame().getTitle() == null) || 
            (FusionApplication.getApplicationFrame().getTitle().equals("") == true) )
        {
            setTitle("Fusion Administrator" );
        }
        else
        {
            setTitle( FusionApplication.getApplicationFrame().getTitle() );
        }

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}
        
        initPanels();
        addKeyListener( this );
    }

    /**
    * Dialog frame parent. 
	* 
	* @param message String
	* @param isNumericOnly boolean
    */
    public InputDialog(String message, boolean isNumericOnly) 
    {
        this( new DialogFrame(), message, isNumericOnly );
    }

    /**
    * Constructor, allows numerics.
	* 
	* @param message String
    */
    public InputDialog(String message)
    {
        this( new DialogFrame(), message, false );
    }
    
    /**
    * Don't use this.
    */
    private InputDialog()
    {
        this( "Jason is cool" );
    }

    /**
    * Create an initialize the controls
    */
    private void initPanels()
    {
        String methodName = MODULE_NAME + "initPanels()";
        String labelStr = "";

        try
        {
            JPanel centralPanel = new JPanel();
            centralPanel.setLayout( new GridBagLayout() );
            GridBagConstraints gbc = new GridBagConstraints();
            
            gbc.insets = new Insets( 5,5,5,5 );
            gbc.anchor = GridBagConstraints.WEST;
            gbc.fill = GridBagConstraints.HORIZONTAL;
            gbc.gridwidth = GridBagConstraints.REMAINDER;
            gbc.gridheight = GridBagConstraints.RELATIVE;

            messageLabel = new JLabel( messageStr );
            
            centralPanel.add( messageLabel, gbc );

            gbc.gridheight = GridBagConstraints.REMAINDER;

            inputField = new JTextField("", 25);
            inputField.addKeyListener( this );
            inputField.addFocusListener( this );

            centralPanel.add( inputField, gbc );

            getContentPane().add( centralPanel, BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Get the input.
    */
    public String getInputString()
    {
        return inputField.getText();
    }

    //************************************************************************//
    // KeyListener impl (overriding base class versions)
    //
    private boolean isBackspace = false;
    /**
    * Invoked when a key has been typed.
    * See the class description for {@link KeyEvent} for a definition of 
    * a key typed event.
	* 
	* @param evt KeyEvent
    */
    public void keyTyped(KeyEvent evt)
    {
        String methodName = MODULE_NAME + "keyTyped(KeyEvent)";
        try
        {
            //JGD We're filtering everything but numeric characters for the numVials field
            char keyChar = evt.getKeyChar();
            int keyCode = evt.getKeyCode();         
            if( (isNumeric == true) && 
                (evt.getSource().equals(inputField)) &&
                (Character.isDigit(keyChar) != true) &&
                (isBackspace == false) )
            {
                //Eat the event so it isn't processed by the source object (in this case the JTextField)
                //Logger.log( methodName + " Eating keystroke!", Logger.FINEST  );
                evt.consume();
            }

            super.keyTyped( evt );
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
	* 
	* @param evt KeyEvent
    */
    public void keyPressed(KeyEvent evt)
    {
        String methodName = MODULE_NAME + "keyPressed(KeyEvent)";

        //Checking for backspace for the numeric filter (Backspace doesn't come in a typed key)
        int keyCode = evt.getKeyCode();         
        if( keyCode == KeyEvent.VK_BACK_SPACE )
        {
            isBackspace = true;
        }
        else 
        {
            isBackspace = false;
        }

        super.keyPressed( evt );
    }

    // KeyListener impl (Override) ends 

    //*****************************************************************************************//
    // FocusListener impl
    //
    /**
    * Invoked when a component gains the keyboard focus.
	* 
	* @param evt FocusEvent
    */
    public void focusGained(FocusEvent evt)
    {
        if( evt.getSource().equals(inputField) )
        {
            inputField.setSelectionStart( 0 );
            inputField.setSelectionEnd( inputField.getText().length() );
        }
    }

    /**
    * Invoked when a component loses the keyboard focus.
	* 
	* @param evt FocusEvent
    */
    public void focusLost(FocusEvent evt)
    {
    }
    // FocusListener impl

}



