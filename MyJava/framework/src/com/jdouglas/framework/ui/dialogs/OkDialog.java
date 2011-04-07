package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.props.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;
import static com.jdouglas.framework.interfaces.props.IUtilConstants.*;

/**
* OkDialog. Yet another incarnation of my base dialog class for OK/Cancel/Help. This class creates the buttons, hooks up
* the listeners and routes everything to the handler methods, okPressed, cancelPressed and helpPressed. Extenders
* of this class just have to fill in the center panel with whatever controls they want and override the necessary
* handlers (usually just okPressed). Be sure and call the base class version to make sure the closeState is set properly.
* 
* @author Jason Douglas 11/12/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class OkDialog
    extends JDialog
        implements ActionListener,KeyListener
{
	/** Module name */
    private static final String MODULE_NAME                                                                 = "OkDialog.";

    /** Predefined Button bitsets */
    public static BitSet OK_DIALOG                                                                          = new BitSet();
    public static BitSet OK_CANCEL_DIALOG                                                                   = new BitSet();                                                     
    public static BitSet OK_CANCEL_HELP_DIALOG                                                              = new BitSet();                                                     
    public static BitSet OK_CANCEL_APPLY_DIALOG                                                             = new BitSet();                                                     
    public static BitSet OK_CANCEL_APPLY_HELP_DIALOG                                                        = new BitSet();                                                     

	/** Dialog Type */
    private BitSet dialogType;
	/** Ok button */
    private JButton okButton;
	/** Cancel button */
    protected JButton cancelButton;
	/** apply button */
    private JButton applyButton;
	/** Help button */
    private JButton helpButton;
	/** Button panel */
    protected JPanel buttonPanel;
    /** Close State */
    protected int closeState = ID_CANCEL;
	/** Initial focus component */
	protected JComponent initFocusComp;
	/** Dispose of DialogFrame parent flag */
	protected boolean disposeDialogParentFlag = true;
	/** Parent HWND, used to parent dialog to a window created outside of java (when set)*/
	protected int parentHWND = -1;

    /**
    * Constructor. This dialog uses the the dialog frame class. See that class for more info. 
    *
    * @param parent Window
    * @param type int 
    */
    public OkDialog(Window parent, BitSet type)
    {
        super( parent, "Fusion AE", Dialog.ModalityType.APPLICATION_MODAL );

        dialogType = type;

        setSize( 300, 120 );

		if( (parent == null) )
		{
			setLocation( FusionUtils.getCenterPosition(getSize()) );
		}
		else
		{
			//Center it on the parent.
			Point location = parent.getLocation();
			Dimension size = parent.getSize();
			Point centerPoint = new Point( (int)(location.getX() + (size.getWidth()/2)),
				                           (int)(location.getY() + (size.getHeight()/2)) );

			setLocation( (int)(centerPoint.getX() - (getSize().getWidth()/2)),
				         (int)(centerPoint.getY() - (getSize().getHeight()/2)) );
		}
        setResizable(false);

        //Just in case this hasn't been set yet
        if( (FusionApplication.getApplicationFrame() != null) &&
		    (FusionApplication.getApplicationFrame().getTitle() != null) )
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
    *
    * @param type int
    */
    public OkDialog(BitSet type)
    {
        this( new DialogFrame(), type );
    }

    /**
    * Default to not show cancel or help
    */
    public OkDialog()
    {
        this(new DialogFrame(), OK_DIALOG);
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

            buttonPanel = new JPanel();
            buttonPanel.setLayout( new GridBagLayout() );
            GridBagConstraints gbc = new GridBagConstraints();

            gbc.anchor = GridBagConstraints.CENTER;
            gbc.gridwidth = 1;
            gbc.insets = new Insets( 5, 5, 8, 5 );

            //Ok button
            okButton = new JButton( FusionApplication.theResources.okButton );
            okButton.addActionListener( this );
            okButton.addKeyListener( this );
            if( dialogType.get(ID_OK) )
            {
                buttonPanel.add( okButton, gbc );
            }

            //Apply Button
            applyButton = new JButton( FusionApplication.theResources.applyButton );
            applyButton.addActionListener( this );
            applyButton.addKeyListener( this );
            if( dialogType.get(ID_APPLY) )
            {
                buttonPanel.add( applyButton, gbc );
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
    *
    * @return int 
    */
    public int showDialog()
    {
        //Show the dialog
        setVisible( true );

		//If the parent is a DialogFrame, dispose of it.
		Object obj = getParent();
		if( (obj instanceof DialogFrame) && disposeDialogParentFlag )
		{
			((DialogFrame)obj).dispose();
		}

		//Request focus for the initial component if set
		if( initFocusComp != null )
		{
			initFocusComp.requestFocus();
		}

        //Return the close state.
        return closeState;
    }

    /**
    * The return value of showDialog is the closeState but here's another way to get it. 
    *
    * @return int 
    */
    public int getCloseState()
    {
        return closeState;
    }

	/**
    * Set the parent HWND. When set, this value will be used to parent the dialog to a non-java window.
	* 
	* @param parent_HWND int
    */
	public void setParentHWND(int parent_HWND)
	{
		parentHWND = parent_HWND;
	}
    
    /**
    * Ok handler. Sets the closeState to ID_OK and closes the dialog. 
    * Derivatives should override (calling super()!) and do whatever processing they need.
    */
    protected void okPressed()
    {
        closeState = ID_OK;
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
    * Apply Button handler. Should act the same as the ok handler but without closing the dialog.
    */
    protected void applyPressed()
    {
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
    *
    * @param e ActionEvent
    */
    public void actionPerformed(ActionEvent e)
    {
        String methodName = MODULE_NAME + "actionPerformed(ActionEvent)";
        try
        {
            if( e.getSource().equals(okButton) )
            {
                okPressed();
            }
            else if( e.getSource().equals(cancelButton) )
            {
                cancelPressed();
            }
            else if( e.getSource().equals(helpButton) )
            {
                helpPressed();
            }
            else if( e.getSource().equals(applyButton) )
            {
                applyPressed();
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
     *
     * @param e KeyEvent 
     */
    public void keyTyped(KeyEvent e)
    {
    }

    /**
    * Invoked when a key has been pressed. 
    * See the class description for {@link KeyEvent} for a definition of 
    * a key pressed event.
    *
    * @param e KeyEvent 
    */
    public void keyPressed(KeyEvent e)
    {
        if( e.getKeyCode() == KeyEvent.VK_ENTER )
        {
            okPressed();
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
    *
    * @param e KeyEvent 
    */
    public void keyReleased(KeyEvent e)
    {
    }
    // KeyListener impl ends 

    /** Setup the BitSet constants */
    static 
    {
        OK_DIALOG.set( ID_OK );

        OK_CANCEL_DIALOG.set( ID_OK );
        OK_CANCEL_DIALOG.set( ID_CANCEL );

        OK_CANCEL_APPLY_DIALOG.set( ID_OK );
        OK_CANCEL_APPLY_DIALOG.set( ID_CANCEL );
        OK_CANCEL_APPLY_DIALOG.set( ID_APPLY );

        OK_CANCEL_HELP_DIALOG.set( ID_OK );    
        OK_CANCEL_HELP_DIALOG.set( ID_CANCEL );    
        OK_CANCEL_HELP_DIALOG.set( ID_HELP );    

        OK_CANCEL_APPLY_HELP_DIALOG.set( ID_OK );    
        OK_CANCEL_APPLY_HELP_DIALOG.set( ID_CANCEL );    
        OK_CANCEL_APPLY_HELP_DIALOG.set( ID_HELP );    
        OK_CANCEL_APPLY_HELP_DIALOG.set( ID_APPLY );    
    }
}



