package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* MessageBox. The messageboxes provided by JOptionPane don't work as well as mine.
* 
* @author Jason Douglas 6/17/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class MessageBox
    extends OkDialog
{
	/** Module name */
    public static final String MODULE_NAME = "MessageBox.";

	/** Controls */
    private JLabel messageLabel;
    private String messageStr;
    private int messageType;

    /**
    * Ctor. Uses the JOptionPane constants (why reinvent?)  
    */
    public MessageBox(String message, int message_type)
    {
        super();

        messageStr = message;
        messageType = message_type;
        
        //JGD TODO Base size on the message string...
        setSize( 300, 120 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );
        setResizable(false);

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}

        initPanels();
        addKeyListener( this );
    }

    /**
    * Default to a plain message
    */
    public MessageBox(String message)
    {
        this(message, JOptionPane.PLAIN_MESSAGE );
    }

    /**
    * Don't use this.
    */
    private MessageBox()
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

            switch(messageType)
            {
                case JOptionPane.PLAIN_MESSAGE:
                    messageLabel = new JLabel( messageStr );
                    break;

                case JOptionPane.ERROR_MESSAGE:
                    messageLabel = new JLabel( messageStr, 
                                               UIManager.getIcon("OptionPane.errorIcon"),
                                               SwingConstants.LEADING );
                    break;

                case JOptionPane.INFORMATION_MESSAGE:
                    messageLabel = new JLabel( messageStr, 
                                               UIManager.getIcon("OptionPane.informationIcon"),
                                               SwingConstants.LEADING );
                    break;

                case JOptionPane.WARNING_MESSAGE:
                    messageLabel = new JLabel( messageStr, 
                                               UIManager.getIcon("OptionPane.warningIcon"),
                                               SwingConstants.LEADING );
                    break;

                case JOptionPane.QUESTION_MESSAGE:
                    messageLabel = new JLabel( messageStr, 
                                               UIManager.getIcon("OptionPane.questionIcon"),
                                               SwingConstants.LEADING );
                    break;

                default:
                    messageLabel = new JLabel( messageStr );
            }

            messageLabel.setIconTextGap( 15 );

            centralPanel.add( messageLabel, gbc );

            getContentPane().add( centralPanel, BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * An example of overriding okPressed.
    */
    protected void okPressed()
    {
        //JOptionPane.showMessageDialog( null, "You pressed OK!" );
        super.okPressed();
    }
}



