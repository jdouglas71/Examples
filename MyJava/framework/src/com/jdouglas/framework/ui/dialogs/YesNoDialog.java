package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;
import static com.jdouglas.framework.interfaces.props.IUtilConstants.*;

/**
* Yet another incarnation of my base dialog class for Yes/No/Cancel. This class creates the buttons, hooks up
* the listeners and routes everything to the handler methods, okPressed, cancelPressed and helpPressed. Extenders
* of this class just have to fill in the center panel with whatever controls they want and override the necessary
* handlers (usually just okPressed). Be sure and call the base class version to make sure the closeState is set properly.
* 
* @author Jason Douglas 11/12/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class YesNoDialog
    extends JDialog
        implements ActionListener,KeyListener
{
	/** Module name */
    private static final String MODULE_NAME                                                             = "YesNoDialog.";

    /** Predefined button bitsets */
    public static BitSet YES_NO_DIALOG                                                                  = new BitSet();                                                     
    public static BitSet YES_NO_CANCEL_DIALOG                                                           = new BitSet();                                                     
    public static BitSet YES_NO_CANCEL_HELP_DIALOG                                                      = new BitSet();                                                     

	/** Dialog type */
    private BitSet dialogType;
	/** Controls */
    private JButton yesButton;
    private JButton noButton;
    private JButton cancelButton;
    private JButton helpButton;
	/** The close state */
    private int closeState = ID_CANCEL;

    /**
    * Ctor. This dialog uses the the dialog frame class. See that class for more info. 
    *
    * @param parent Frame
    * @param type BitSet
    */
    public YesNoDialog(Frame parent, BitSet type)
    {
        super( parent, FusionApplication.getApplicationFrame().getTitle(), true );

        dialogType = type;

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
    * Type only with a dialogFrame as the parent
    */
    public YesNoDialog(BitSet type)
    {
        this( new DialogFrame(), type );
    }

    /**
    * Default to not show cancel or help
    */
    public YesNoDialog()
    {
        this(new DialogFrame(), YES_NO_DIALOG);
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
            getContentPane().setLayout( new BorderLayout() );

            JPanel buttonPanel = new JPanel();
            buttonPanel.setLayout( new GridBagLayout() );
            GridBagConstraints gbc = new GridBagConstraints();

            gbc.anchor = GridBagConstraints.CENTER;
            gbc.gridwidth = 1;
            gbc.insets = new Insets( 5, 5, 8, 5 );

            //Yes Button
            yesButton = new JButton( FusionApplication.theResources.yesButton );
            yesButton.addActionListener( this );
            yesButton.addKeyListener( this );
            if( dialogType.get(ID_YES) )
            {
                buttonPanel.add( yesButton, gbc );
            }

            //No Button
            noButton = new JButton( FusionApplication.theResources.noButton );
            noButton.addActionListener( this );
            noButton.addKeyListener( this );
            if( dialogType.get(ID_NO) )
            {
                buttonPanel.add( noButton, gbc );
            }
            
            //Cancel button
            cancelButton = new JButton( FusionApplication.theResources.cancelButton );
            cancelButton.addActionListener( this );
            cancelButton.addKeyListener( this );
            if( dialogType.get(ID_CANCEL) ) 
            {
                buttonPanel.add( cancelButton, gbc );
            }

            //Help button 
            helpButton = new JButton( FusionApplication.theResources.helpButton );
            helpButton.addActionListener( this );
            helpButton.addKeyListener( this );
            if( dialogType.get(ID_HELP) )
            {
                buttonPanel.add( helpButton, gbc );
            }

            getContentPane().add( buttonPanel, BorderLayout.SOUTH );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Show and return the close state
    */
    public int showDialog()
    {
        //Show the dialog
        setVisible( true );

        //If the parent is a DialogFrame, dispose of it.
        Object obj = getParent();
        if( obj instanceof DialogFrame )
        {
            ((DialogFrame)obj).dispose();
        }

        //Return the close state.
        return closeState;
    }

    /**
    * The return value of showDialog is the closeState but here's another way to get it. 
    */
    public int getCloseState()
    {
        return closeState;
    }
    
    /**
    * Yes handler. Sets the closeState to ID_OK and closes the dialog. 
    * Derivatives should override (calling super()!) and do whatever processing they need.
    */
    protected void yesPressed()
    {
        closeState = ID_YES;
        setVisible( false );
    }

    /**
    * No Handerl. Sets the closeState to ID_NO and closes the dialog.
    */
    protected void noPressed()
    {
        closeState = ID_NO;
        setVisible( false );
    }
    
    /**
    * Cancel handler. Sets the close state to ID_CANCEL and closes the dialog.
    * Derivatives shouldn't need to override.
    */
    protected void cancelPressed()
    {
        closeState = ID_CANCEL;
        setVisible( false );
    }

    /**
    * Help handler. Doesn't do anything. Derivatives should override to show help.
    * Help does not close the dialog.
    */
    protected void helpPressed()
    {
    }

    //*************************************************************************//
    // ActionListener impl
    //
    /**
    * Button handler 
    */
    public void actionPerformed(ActionEvent e)
    {
        String methodName = MODULE_NAME + "actionPerformed(ActionEvent)";
        try
        {
            if( e.getSource().equals(yesButton) )
            {
                yesPressed();
            }
            else if( e.getSource().equals(noButton) )
            {
                noPressed();
            }
            else if( e.getSource().equals(cancelButton) )
            {
                cancelPressed();
            }
            else if( e.getSource().equals(helpButton) )
            {
                helpPressed();
            }

        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Failed", x );
        }
    }
    // ActionListener impl

    //************************************************************************//
    // KeyListener impl
    //
    /**
     * Invoked when a key has been typed.
     * See the class description for {@link KeyEvent} for a definition of 
     * a key typed event.
     */
    public void keyTyped(KeyEvent e)
    {
    }

    /**
     * Invoked when a key has been pressed. 
     * See the class description for {@link KeyEvent} for a definition of 
     * a key pressed event.
     */
    public void keyPressed(KeyEvent e)
    {
        if( e.getKeyCode() == KeyEvent.VK_ENTER )
        {
            yesPressed();
        }
        else if( e.getKeyCode() == KeyEvent.VK_ESCAPE )
        {
            cancelPressed();
        }
        else if( e.getKeyCode() == KeyEvent.VK_F1 )
        {
            helpPressed();
        }
    }

    /**
     * Invoked when a key has been released.
     * See the class description for {@link KeyEvent} for a definition of 
     * a key released event.
     */
    public void keyReleased(KeyEvent e)
    {
    }
    // KeyListener impl ends 

    static 
    {
        YES_NO_DIALOG.set( ID_YES );
        YES_NO_DIALOG.set( ID_NO );

        YES_NO_CANCEL_DIALOG.set( ID_YES );
        YES_NO_CANCEL_DIALOG.set( ID_NO );
        YES_NO_CANCEL_DIALOG.set( ID_CANCEL );

        YES_NO_CANCEL_HELP_DIALOG.set( ID_YES );
        YES_NO_CANCEL_HELP_DIALOG.set( ID_NO );
        YES_NO_CANCEL_HELP_DIALOG.set( ID_CANCEL );
        YES_NO_CANCEL_HELP_DIALOG.set( ID_HELP );
    }
}



