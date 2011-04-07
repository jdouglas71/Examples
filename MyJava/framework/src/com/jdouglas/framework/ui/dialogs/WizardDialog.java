package com.jdouglas.framework.ui.dialogs;

import java.awt.*;
import java.beans.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.messages.*;
import com.jdouglas.framework.core.events.*;
import com.jdouglas.framework.ui.widgets.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.listeners.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;
import static com.jdouglas.framework.interfaces.props.IUtilConstants.*;

/**
* WizardDialog. Ideally, we would have the caller pass in a series of components to be used in sequence as the user presses
* the next button. When the last one is displayed, the next button would be switched to the OK button. This would require an
* interface for components (really?) and a data model (definitely). Probably can just use a HashMap for now. JGD 9/27/05
* 
* @author Jason Douglas 11/12/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class WizardDialog
    extends JDialog
        implements IWizardContainer,ActionListener,MouseListener,ComponentListener,WindowListener,PropertyChangeListener
{
	/** module name */
    private static final String MODULE_NAME                                 = "WizardDialog.";
    /** Button prop. */
    private static final String BUTTON_ID                                   = "ButtonType";

    /** the Wizard */
    private IWizard theWizard;
    /** the current Panel */
    private IEditorPanel currentPanel;
	/** cancel button */
    private JButton cancelButton;
	/** next button */
    private JButton nextButton; 
	/** back/finish button */
    private JButton backButton;
	/** Message View */
	private IMessageView theMessageView;
    /** Close State */
    protected int closeState = ID_CANCEL;
	/** Parent HWND */
	private int parentHWND = -1;
	/** Show Message Area */
	private boolean showMessageArea = false;
	/** Listeners */
	private ArrayList<IWizardContainerListener> theListeners = new ArrayList<IWizardContainerListener>();
	/** First time shown flag */
	private boolean firstTimeShown = true;
	/** The Message Manager */
	private IMessageManager theMessageManager;

    /**
    * Constructor. Modal dialog to be used on Java side with Java parent.
    *
    * @param wizard IWizard
    * @param parent Frame
    * @param size Dimension
	* @param showMsgArea boolean
    */
    public WizardDialog(IWizard wizard, Frame parent, Dimension size, boolean showMsgArea)
    {
        super( parent, "Wizard Dialog", true );

		theMessageManager = (IMessageManager)FusionApplication.getManagers().get(IMessageManager.MANAGER_NAME);

        theWizard = wizard;

        setSize( size );
        setLocation( FusionUtils.getCenterPosition(getSize()) );
        setResizable(false);
		showMessageArea = showMsgArea;

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
		addWindowListener( this );
		addComponentListener( this );
    }

	/**
	* Constructor. Modal dialog to be used on Java side with Java parent.
	*
	* @param wizard IWizard
	* @param parent Frame
	* @param size Dimension
	*/
	public WizardDialog(IWizard wizard, Frame parent, Dimension size)
	{
		this( wizard, parent, size, false );
	}

	/**
	* Constructor. Modeless dialog meant to be used with native windows parent. 
	*
	* @param wizard IWizard
	* @param _parentHWND int
	* @param size Dimension
	* @param showMsgArea boolean
	*/
	public WizardDialog(IWizard wizard, int _parentHWND, Dimension size, boolean showMsgArea)
	{
		super( (JDialog)null, "Wizard Dialog", true );

		theWizard = wizard;

		parentHWND = _parentHWND;
		showMessageArea = showMsgArea;

		//setDefaultCloseOperation( JDialog.DO_NOTHING_ON_CLOSE );

		setSize( size );
		setLocation( FusionUtils.getCenterPosition(getSize()) );
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
		addComponentListener( this );
		addWindowListener( this );
	}


	/**
	* Constructor. Modeless dialog meant to be used with native windows parent. 
	*
	* @param wizard IWizard
	* @param _parentHWND int
	* @param size Dimension
	*/
	public WizardDialog(IWizard wizard, int _parentHWND, Dimension size)
	{
		this( wizard, _parentHWND, size, true );
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
			//Create controls 
            //Cancel button
            cancelButton = new JButton( FusionApplication.theResources.cancelButton );
            cancelButton.addActionListener( this );
            //cancelButton.addKeyListener( this );

            //Next Button 
            nextButton = new JButton( FusionApplication.theResources.nextButton );
            nextButton.addActionListener( this );
            //nextButton.addKeyListener( this );
            nextButton.putClientProperty( BUTTON_ID, new Integer(ID_NEXT) );

            //Back Button 
            backButton = new JButton( FusionApplication.theResources.backButton );
            backButton.addActionListener( this );
            //backButton.addKeyListener( this );
            backButton.setEnabled( false );

			//Message View 
			IMessageManager messMan = (IMessageManager)FusionApplication.getManagers().get(IMessageManager.MANAGER_NAME);
			if( messMan != null )
			{
				theMessageView = messMan.getMessageView("WizardDialog"+FusionUtils.getCurrentTime()); //Make sure we get a new one each time (for now).
			}

			//Layout 
            getContentPane().setLayout( new BorderLayout() );

            JPanel buttonPanel = new JPanel( new GridBagLayout() );
			//buttonPanel.setBackground( Color.RED );
			
            GridBagConstraints gbc = new GridBagConstraints();
            gbc.anchor = GridBagConstraints.WEST;
            gbc.insets = new Insets( 5, 5, 5, 5 );
			gbc.gridx = 0;
			gbc.gridy = 0;

			if( showMessageArea )
			{
				gbc.gridwidth = 3;
				gbc.fill = GridBagConstraints.HORIZONTAL;
				gbc.weightx = 1.0;
				buttonPanel.add( theMessageView.getComponent(), gbc );
				gbc.gridy = 1;
				gbc.weightx = 0.0;
				gbc.weighty = 0.0;
				gbc.fill = GridBagConstraints.NONE;
			}
					  /*
			gbc.weightx = 1.0;
            gbc.gridwidth = 1;
			gbc.gridx = 0;
            gbc.anchor = GridBagConstraints.EAST;
            gbc.insets = new Insets( 5, 15, 5, 5 );
            buttonPanel.add( backButton, gbc );
			gbc.gridx = 1;
            gbc.anchor = GridBagConstraints.WEST;
            gbc.insets = new Insets( 5, 5, 5, 15 );
            buttonPanel.add( nextButton, gbc );

            gbc.gridwidth = 1;

            gbc.fill = GridBagConstraints.NONE;
            gbc.anchor = GridBagConstraints.EAST;
			gbc.gridx = 2;
            buttonPanel.add( cancelButton, gbc );
			*/

			//Button SubPanel with boxLayout
			JPanel subPanel = new JPanel();
			subPanel.setLayout( new BoxLayout(subPanel,BoxLayout.LINE_AXIS) );
			subPanel.setBorder( BorderFactory.createEmptyBorder(0,5,0,5) );
			subPanel.add( Box.createHorizontalGlue() );
			subPanel.add( backButton );
			subPanel.add( Box.createRigidArea(new Dimension(10,0)) );
			subPanel.add( nextButton );
			//subPanel.add( Box.createRigidArea(new Dimension(30,0)) );
			subPanel.add( Box.createHorizontalGlue() );
			subPanel.add( cancelButton );

            gbc.gridwidth = 3;
			gbc.fill = GridBagConstraints.HORIZONTAL;
			gbc.weightx = 1.0;
			buttonPanel.add( subPanel, gbc );

            getContentPane().add( buttonPanel, BorderLayout.SOUTH );

            theWizard.setWizardContainer( this );
            theWizard.setButtons( backButton, nextButton );

            currentPanel = theWizard.nextPanel();
            //The panel will make sure this doesn't get added multiple times.
            currentPanel.addListener( this, MouseListener.class );
			currentPanel.addPropertyChangeListener( IEditorPanel.LAST_PANEL, this );
			currentPanel.addPropertyChangeListener( IEditorPanel.FIRST_PANEL, this );

            if( (currentPanel != null) && (currentPanel.getProperty(IEditorPanel.LAST_PANEL) != null) )
            {
                nextButton.setText( FusionApplication.theResources.finishButton );
                nextButton.putClientProperty( BUTTON_ID, new Integer(ID_FINISH) );
            }

            //Set the center panel
            if( currentPanel != null )
            {
                getContentPane().add( currentPanel.getComponent(), BorderLayout.CENTER );
                //Update title bar
				setTitle( theWizard.getWizardTitle() );
            }
            else
            {
                getContentPane().add( new JPanel(), BorderLayout.CENTER );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Cancel handler. Sets the close state to ID_CANCEL and closes the dialog.
    * Derivatives shouldn't need to override.
    */
    protected void cancelPressed()
    {
		String methodName = MODULE_NAME + "cancelPressed()";

		Logger.log( methodName, Logger.DEBUG );
        closeState = ID_CANCEL;
        setVisible( false );
		fireWizardContainerClosed();
    }

    /**
    * Next button handler. Extenders can call setCenterPanel to update the gui.
    */
    protected void nextPressed()
    {
        String methodName = MODULE_NAME + "nextPressed()";

        try
        {
			setCursor( Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR) );
			theMessageView.clearMessages();

            int buttonType = ((Integer)nextButton.getClientProperty( BUTTON_ID )).intValue();
            if( buttonType == ID_FINISH )
            {
				Logger.log( methodName + " Shuttin' er down.", Logger.DEBUG );
				 
                //We're finished. Bail time. 
                if( currentPanel.validateContents() )
                {
                    if( currentPanel.saveContents() )
					{
						Logger.log( methodName + " Closin' er down.", Logger.DEBUG );
						closeState = ID_FINISH;
						setVisible( false );
						fireWizardContainerClosed();
						return;
					}
					else
					{
						Logger.log( methodName + " Save Failed. Do nothing.", Logger.DEBUG );
					}
                }
				else
				{
					Logger.log( methodName + " validateContents failed!", Logger.DEBUG );
				}
            }
            else
            {
                //Get the new panel
                IEditorPanel newPanel = theWizard.nextPanel();
                if( newPanel != null )
                {
                    //Remove last panel
                    if( currentPanel != null )
                    {
                        getContentPane().remove( currentPanel.getComponent() );
						currentPanel.removePropertyChangeListener( this );
                    }
                    //iF it's the last one, switch the button
                    if( newPanel.getProperty(IEditorPanel.LAST_PANEL) != null )
                    {
                        nextButton.setText( FusionApplication.theResources.finishButton );
                        nextButton.putClientProperty( BUTTON_ID, new Integer(ID_FINISH) );
                    }
                    getContentPane().add( newPanel.getComponent(), BorderLayout.CENTER );
                    currentPanel = newPanel;

                    //Add Mouse Listener
                    currentPanel.addListener( this, MouseListener.class );
                    //currentPanel.addListener( this, KeyListener.class );
					currentPanel.addPropertyChangeListener( IEditorPanel.LAST_PANEL, this );
					currentPanel.addPropertyChangeListener( IEditorPanel.FIRST_PANEL, this );

                    //Update title bar
                    String panelTitle = (String)(currentPanel.getProperty(IEditorPanel.TITLE));
                    if( panelTitle != null )
                    {
                        setTitle( theWizard.getWizardTitle() );
                    }

					//If we have a message pane, call validateContents so the message pane will accurately reflect the state of the panel
					if( showMessageArea )
					{
						currentPanel.validateContents();
					}

                    invalidate();
                    validate();
                    repaint();

                    //Set initial focus
                    currentPanel.setProperty( IEditorPanel.INIT_FOCUS, new Boolean(true) );
                }
				else
				{
					//If the newPanel is null, we assume that the wizard is done and bail.
					//We're finished. Bail time. 
					if( currentPanel.validateContents() )
					{
						if( currentPanel.saveContents() )
						{
							Logger.log( methodName + " Closin' er down.", Logger.DEBUG );
							closeState = ID_FINISH;
							setVisible( false );
							fireWizardContainerClosed();
							return;
						}
						else
						{
							Logger.log( methodName + " Save Failed. Do nothing.", Logger.DEBUG );
						}
					}
				}
            }

            backButton.setEnabled( (currentPanel.getProperty(IEditorPanel.FIRST_PANEL) == null) );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
		finally
		{
			setCursor( null );
		}
    }

    /**
    * Back Button handler. 
    */
    protected void backPressed() 
    {
        String methodName = MODULE_NAME + "backPressed()";

        try
        {
            //Reset the message pane
			theMessageView.clearMessages();

			setCursor( Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR) );
            IEditorPanel newPanel = theWizard.previousPanel();

            if( newPanel != null )
            {
                //Swap next button if necessary
                if( (newPanel.getProperty(IEditorPanel.LAST_PANEL) == null) )
                {
                    nextButton.setText( FusionApplication.theResources.nextButton );
                    nextButton.putClientProperty( BUTTON_ID, new Integer(ID_NEXT) );
                }

                //Remove last panel
                if( currentPanel != null )
                {
                    getContentPane().remove( currentPanel.getComponent() );
					currentPanel.removePropertyChangeListener( this );
                }

                //Swap panels
                currentPanel = newPanel;
                getContentPane().add( currentPanel.getComponent(), BorderLayout.CENTER );

                //Enable the back button if appropriate
                backButton.setEnabled( (currentPanel.getProperty(IEditorPanel.FIRST_PANEL) == null) );

                //Add Listeners 
                currentPanel.addListener( this, MouseListener.class );
                //currentPanel.addListener( this, KeyListener.class );
				currentPanel.addPropertyChangeListener( IEditorPanel.LAST_PANEL, this );
				currentPanel.addPropertyChangeListener( IEditorPanel.FIRST_PANEL, this );

                //Update title bar
                String panelTitle = (String)(currentPanel.getProperty(IEditorPanel.TITLE));
                if( panelTitle != null )
                {
                    setTitle( theWizard.getWizardTitle() );
                }

				//If we have a message pane, call validateContents so the message pane will accurately reflect the state of the panel
				if( showMessageArea )
				{
					currentPanel.validateContents();
				}

                invalidate();
                validate();
                repaint();

                //Set initial focus
                currentPanel.setProperty( IEditorPanel.INIT_FOCUS, new Boolean(true) );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
		finally
		{
			setCursor( null );
		}
    }

	//**************************************************************************************************************************//
	// IWizardContainer impl
	// 
	/**
	* Show and return the close state
	*
	* @return int 
	*/
	public int showDialog()
	{
		String methodName = MODULE_NAME + "showDialog()";

		//Show the dialog
		setVisible( true );

		//If the parent is a DialogFrame, dispose of it.
		Object obj = getParent();
		if( obj instanceof DialogFrame )
		{
			((DialogFrame)obj).dispose();
		}

		if( parentHWND > 0 )
		{                             
			Logger.log( methodName + " Unhooking from the parent window.", Logger.DEBUG );
			boolean result = FusionUtils.unhookParentWindow(parentHWND);
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
    * Send a message to the message pane..
	* 
	* @param message IFusionMessage
    */
    public void setMessage(IFusionMessage message)
    {
        String methodName = MODULE_NAME + "setMessage(IFusionMessage)";

        try
        {
			if( showMessageArea )
			{
				theMessageView.addMessage( message );
			}
			else
			{
				if( message.getMessageType() == MessageType.ERROR )
				{
					JOptionPane.showMessageDialog( this, 
												   message.toString(),
												   theWizard.getWizardTitle(),
												   JOptionPane.ERROR_MESSAGE );
				}
			}
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

	/** 
	* Remove a message from the message view.
	* 
	* @param message IFusionMessage
	*/
	public void removeMessage(IFusionMessage message)
	{
		if( theMessageView != null )
		{
			theMessageView.removeMessage( message );
		}
	}


    /**
    * Set the message pane text.
    *
    * @param text String
	* @param type MessageType
    */
    public void setMessageText(String text, MessageType type)
    {
		setMessage( theMessageManager.createMessage(text,type,null) );
    }

	/**
	* Clear the message area. 
	*/
	public void clearMessages()
	{
		if( theMessageView != null )
		{
			theMessageView.clearMessages();
		}
	}

	/**
	* Get the window associated with the container. (For parenting)
	* 
	* @return Window
	*/
	public Window getWindow()
	{
		return this;
	}

	/**
    * Set parent HWND
	* 
	* @param parent_HWND int
    */
	public void setParentHWND(int parent_HWND)
	{
		parentHWND = parent_HWND;
	}

	/**
	* Add wizard container listener.
	* 
	* @param l IWizardContainerListener 
	*/
	public void addWizardContainerListener(IWizardContainerListener l)
	{
		theListeners.add( l );
	}

	/**
	* Remove wizard container listener.
	* 
	* @param l IWizardContainerListener 
	*/
	public void removeWizardContainerListener(IWizardContainerListener l)
	{
		theListeners.remove( l );
	}

	// IWizardContainer impl ends
    
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
            if( e.getSource().equals(backButton) )
            {
                if( backButton.isEnabled() )
                {
                    backPressed();
                }
            }
            else if( e.getSource().equals(cancelButton) )
            {
                if( cancelButton.isEnabled() )
                {
                    cancelPressed();
                }
            }
            else if( e.getSource().equals(nextButton) )
            {
                if( nextButton.isEnabled() )
                {
                    nextPressed();
                }
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
        String methodName = MODULE_NAME + "KeyPressed(KeyEvent)";

        if( e.getKeyCode() == KeyEvent.VK_ENTER )
        {
            Logger.log( methodName + " Enter pressed.", Logger.CONFIG );
            if( nextButton.isEnabled() ) 
            {
                nextPressed();
            }
        }
        else if( e.getKeyCode() == KeyEvent.VK_ESCAPE )
        {
            if( cancelButton.isEnabled() )
            {
                cancelPressed();
            }
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

    //********************************************************************************//
    // MouseListener impl
    //
    /**
    * Invoked when the mouse button has been clicked (pressed
    * and released) on a component.
    */
    public void mouseClicked(MouseEvent e)
    {
        String methodName = MODULE_NAME + "mouseClicked(MouseEvent)";

        if( e.getClickCount() >= 2 )
        {
            if( nextButton.isEnabled() )
            {
                nextPressed();
            }
        }
    }

    /**
    * Invoked when a mouse button has been pressed on a component.
    */
    public void mousePressed(MouseEvent e)
    {
    }

    /**
    * Invoked when a mouse button has been released on a component.
    */
    public void mouseReleased(MouseEvent e)
    {
    }

    /**
    * Invoked when the mouse enters a component.
    */
    public void mouseEntered(MouseEvent e)
    {
    }

    /**
    * Invoked when the mouse exits a component.
    */
    public void mouseExited(MouseEvent e)
    {
    }

    // MouseListener impl ends

	//*******************************************************************************************//
	// ComponentListener impl
	//
    /**
    * Invoked when the component's size changes.
    */
    public void componentResized(ComponentEvent e)
	{
	}

    /**
    * Invoked when the component's position changes.
    */    
    public void componentMoved(ComponentEvent e)
	{
	}

    /**
    * Invoked when the component has been made visible.
    */
    public void componentShown(ComponentEvent e)
	{
		if( e.getSource().equals(this) )
		{
			//Set the initial focus of the editor panel when the dialog is first shown. 
			if( currentPanel != null )
			{
				currentPanel.setProperty( IEditorPanel.INIT_FOCUS, new Boolean(true) );
			}
		}
	}

    /**
    * Invoked when the component has been made invisible.
    */
    public void componentHidden(ComponentEvent e)
	{
		String methodName = MODULE_NAME + "componentHidden(ComponentEvent)";
		//Logger.log( methodName, Logger.DEBUG );
	}

	// ComponentListener impl ends

	//********************************************************************************************//
	// WindowListener impl 
	// 
	/**
	* Invoked the first time a window is made visible.
	* 
	* @param e WindowEvent
	*/
	public void windowOpened(WindowEvent e)
	{
		String methodName = MODULE_NAME + "windowOpened(WindowEvent)";

		//Logger.log( methodName, Logger.DEBUG );
	}

	/**
	* Invoked when the user attempts to close the window
	* from the window's system menu.
	* 
	* @param e WindowEvent
	*/
	public void windowClosing(WindowEvent e)
	{
		String methodName = MODULE_NAME + "windowClosing(WindowEvent)";

		//Logger.log( methodName, Logger.DEBUG );
	}

	/**
	* Invoked when a window has been closed as the result
	* of calling dispose on the window.
	* 
	* @param e WindowEvent
	*/
	public void windowClosed(WindowEvent e)
	{
		String methodName = MODULE_NAME + "windowClosed(WindowEvent)";

		//Logger.log( methodName, Logger.DEBUG );
	}

	/**
	* Invoked when a window is changed from a normal to a
	* minimized state. For many platforms, a minimized window 
	* is displayed as the icon specified in the window's 
	* iconImage property.
	* @see java.awt.Frame#setIconImage
	* 
	* @param e WindowEvent
	*/
	public void windowIconified(WindowEvent e)
	{
	}

	/**
	* Invoked when a window is changed from a minimized
	* to a normal state.
	* 
	* @param e WindowEvent
	*/
	public void windowDeiconified(WindowEvent e)
	{
	}

	/**
	* Invoked when the Window is set to be the active Window. Only a Frame or
	* a Dialog can be the active Window. The native windowing system may
	* denote the active Window or its children with special decorations, such
	* as a highlighted title bar. The active Window is always either the
	* focused Window, or the first Frame or Dialog that is an owner of the
	* focused Window.
	* 
	* @param evt WindowEvent
	*/
	public void windowActivated(WindowEvent evt)
	{
		String methodName = MODULE_NAME + "windowActivated(WindowEvent)";

		try
		{
			//Logger.log( methodName, Logger.DEBUG );
			if( firstTimeShown )
			{
				if( parentHWND > 0 )
				{
					//int myHWND = FusionUtils.getHWNDFromTitle( getTitle(), "SunAwtDialog" );
					int myHWND = FusionUtils.getForegroundHWND();
					Logger.log( methodName + " Hooking parent of HWND: " + Integer.toHexString(myHWND) + " to: " + Integer.toHexString(parentHWND), Logger.DEBUG );
					FusionUtils.hookParentWindow(parentHWND, myHWND); 
					firstTimeShown = false;
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Invoked when a Window is no longer the active Window. Only a Frame or a
	* Dialog can be the active Window. The native windowing system may denote
	* the active Window or its children with special decorations, such as a
	* highlighted title bar. The active Window is always either the focused
	* Window, or the first Frame or Dialog that is an owner of the focused
	* Window.
	* 
	* @param e WindowEvent
	*/
	public void windowDeactivated(WindowEvent e)
	{
		String methodName = MODULE_NAME + "windowDeactivated(WindowEvent)";

		//Logger.log( methodName, Logger.DEBUG );
	}

	// WindowListener impl ends

	//********************************************************************************************************//
	// PropertyChnageListener impl
	// 

	/**
	* This method gets called when a bound property is changed.
	* 
	* @param evt A PropertyChangeEvent object describing the event source 
	*   	and the property that has changed.
	*/
	public void propertyChange(PropertyChangeEvent evt)
	{
		String methodName = MODULE_NAME + "propertyChange(PropertyChangeEvent)";

		try
		{
			//Only care about these properties
			if( evt.getPropertyName().intern() == IEditorPanel.LAST_PANEL.intern() )
			{
				//Only care if the source is the current panel
				if( evt.getSource().equals(currentPanel) )
				{
					if( evt.getNewValue() == null )
					{
						nextButton.setText( FusionApplication.theResources.nextButton );
						nextButton.putClientProperty( BUTTON_ID, new Integer(ID_NEXT) );
					}
					else
					{
						nextButton.setText( FusionApplication.theResources.finishButton );
						nextButton.putClientProperty( BUTTON_ID, new Integer(ID_FINISH) );
					}
				}
			}
			else if( evt.getPropertyName().intern() == IEditorPanel.FIRST_PANEL.intern() )
			{
				//Only care if the source is the current panel
				if( evt.getSource().equals(currentPanel) )
				{
					if( evt.getNewValue() == null )
					{
						backButton.setEnabled( true );
					}
					else
					{
						backButton.setEnabled( false );
					}
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	// PropertyChangeListener impl ends

	/**
	* Fire a Wizard Container Event.
	*/
	protected void fireWizardContainerClosed()
	{
		final String methodName = MODULE_NAME + "fireWizardContainerClosed()";

		try
		{
			Iterator<IWizardContainerListener> iter = theListeners.iterator();
			while( iter.hasNext() )
			{
				final IWizardContainerListener l = iter.next();
				final WizardContainerEvent evt = new WizardContainerEvent( this );
				if( SwingUtilities.isEventDispatchThread() )
				{
					//Notify
					l.wizardContainerClosed( evt );
				}
				else
				{
					//Create worker thread to make sure the change is handled on the AWT thread.
					FusionWorker worker = new FusionWorker() 
					{
						/**
						* Worker thread method.
						*/
						public Object construct()
						{
							try
							{
								//Nothing to do here. 
							}
							catch(Exception xx)
							{
								FusionUtils.logError( methodName, "Failed", xx );
							}
			
							return null;
						}
			
						/**
						* Event Queue thread method.
						*/
						public void finished()
						{
							l.wizardContainerClosed( evt );
						}
					};
			
					worker.start();
				}
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}
}



