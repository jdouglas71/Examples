package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* ConfirmDialog. The messageboxes provided by JOptionPane don't work as well as mine.
* 
* @author Jason Douglas 6/17/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ConfirmDialog
    extends YesNoDialog
{
	/** Module name */
    public static final String MODULE_NAME = "ConfirmDialog.";

	/** Message label control */
    private JLabel messageLabel;
	/** The message string */
    private String messageStr;

    /**
    * Ctor. Uses the JOptionPane constants (why reinvent?)  
    */
    public ConfirmDialog(Frame parent, String message)
    {
        super(parent, YES_NO_DIALOG);

        messageStr = message;
        
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
    * Ctor with a dialog frame.
    */
    public ConfirmDialog(String message)
    {
        this( new DialogFrame(), message );
    }

    /**
    * Don't use this.
    */
    private ConfirmDialog()
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
            
            gbc.anchor = GridBagConstraints.CENTER;

            messageLabel = new JLabel( messageStr, 
                                       UIManager.getIcon("OptionPane.questionIcon"),
                                       SwingConstants.LEADING );

            messageLabel.setIconTextGap( 15 );

            centralPanel.add( messageLabel, gbc );

            getContentPane().add( centralPanel, BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }
}



