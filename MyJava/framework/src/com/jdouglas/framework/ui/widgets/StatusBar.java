package com.jdouglas.framework.ui.widgets;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.interfaces.props.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;

/**
* Statusbar impl for FCA.
* 
* @author Jason Douglas 10/2/03 
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/ 

public class StatusBar
    extends JPanel
{
    /** Module name */
    private static final String MODULE_NAME                 = "StatusBar.";
    
    /** the interval before the statusbar clears the status region */
    private static final int AUTOCLEAR_INTERVAL             = 7000;
    /** The period btwn spinner updates, dictates the spin "speed" */
    private static final int SPINNER_PERIOD                 = 10;

    /** Size of the separator btwn regions */
    private static final int SEPARATOR_SIZE                 = 3;
    /** Thread priority for the spinner */
    private static final int SPINNER_PRIORITY               = Thread.NORM_PRIORITY + 2;

    /** Region constants */
    public static final int STATUS_REGION                   = 0;
    public static final int PROGRESS_REGION                 = 1;
    public static final int MODIFIED_REGION                 = 2;
	public static final int LOCKED_REGION					= 3;

    /** Stop the progress indicator */
    public static final String PROGRESS_STOP                = "ProgressStop";
    /** Start the progress indicator */
    public static final String PROGRESS_START               = "ProgressStart";

    /** The modified region */
    private JPanel modifiedPanel;
	private JLabel modifiedLabel;
	/** the locked region */
	private JPanel lockedPanel;
    private JLabel lockedLabel;
	/** the status region */
    private JTextField statusRegion;
	/** the progress region */
    private JProgressBar progressRegion;

    /** the toolbar that is the actual statusbar component */
    private JToolBar theStatusBar;

    /** Task for the spinner */
    private TimerTask spinnerTask;
    /** timer for hte spinner */
    private java.util.Timer theSpinnerTimer;
    /** the update timer */
    private java.util.Timer theUpdateTimer;

    /** Update sentry */
    protected static boolean shouldUpdateProgress = false;

    /** Resources */
    private FrameworkResources theResources;

    /**
    * Constructor
    */    
    public StatusBar()
    {
		theResources = (FrameworkResources)FusionApplication.getResources(IFrameworkProperties.class);
        initRegions();
        theSpinnerTimer = new java.util.Timer(true);
        theUpdateTimer = new java.util.Timer(true);
    }

    /**
    * Create the region components and place them in the parent container.
    */
    private void initRegions()
    {
        String methodName = MODULE_NAME + "initRegions()";

        try
        {
			//Status region
            statusRegion = new JTextField();
            statusRegion.setEditable( false );
            statusRegion.setBorder( BorderFactory.createLoweredBevelBorder() );
            //Set margin here doesn't seem to do what I think it should!?!
            statusRegion.setMargin( new Insets(1,2,1,1) );

            //Progress Region
            progressRegion = new JProgressBar();
            progressRegion.setString( "" );
            progressRegion.setStringPainted( true );
            progressRegion.setBorder( BorderFactory.createLoweredBevelBorder() );

			//Locked region
			lockedPanel = new JPanel();
			lockedPanel.setLayout( new BorderLayout() );
            lockedPanel.setBorder( BorderFactory.createLoweredBevelBorder() );

            lockedLabel = new JLabel( theResources.lockedText );
            lockedLabel.setIcon( theResources.getResourceIcon(IFrameworkProperties.LOCKED_ICON) );
			lockedLabel.setToolTipText( theResources.lockedTooltip );

			lockedLabel.setVisible( false );

			lockedPanel.add( lockedLabel, BorderLayout.CENTER );

            //Modified Region
            modifiedPanel = new JPanel();
			modifiedPanel.setLayout( new BorderLayout() );
            modifiedPanel.setBorder( BorderFactory.createLoweredBevelBorder() );
			//modifiedPanel.setBackground( Color.BLUE );

			modifiedLabel = new JLabel( "" );
			modifiedLabel.setBorder( BorderFactory.createEmptyBorder() );

			modifiedLabel.setOpaque( true );

			modifiedPanel.add( modifiedLabel, BorderLayout.CENTER );

            //Gridbag Layout
            setLayout( new GridBagLayout() );
            GridBagConstraints gbc = new GridBagConstraints();

            gbc.anchor = GridBagConstraints.WEST;
            gbc.gridwidth = 6;
			gbc.gridx = 0;
            gbc.fill = GridBagConstraints.BOTH;
            gbc.weightx = 4.0;
            gbc.insets = new Insets( 0,1,0,SEPARATOR_SIZE );

            add( statusRegion, gbc );

            gbc.weightx = 0.5;
            gbc.gridwidth = 2;
			gbc.gridx = 6;

            add( progressRegion, gbc );

            gbc.weightx = 0.25;
            gbc.insets = new Insets( 0,1,0,1 );
			gbc.gridwidth = 1;
			gbc.gridx = 8;

			add( lockedPanel, gbc );

            gbc.gridwidth = 1; 
			gbc.gridx = 9;
            gbc.weightx = 0.25;
            gbc.insets = new Insets( 0,1,0,1 );

            add( modifiedPanel, gbc );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Update the region with the given string. If the lock param is true, the status text will not 
    * be automatically cleared.
    */ 
    public void updateRegion(final int region, final String value, final boolean lock)
    {
        String methodName = MODULE_NAME + "updateRegion(int,String)";

        try
        {
            switch(region)
            {
                case STATUS_REGION:
                {
                    if( value != null )
                    {
                        Logger.log( methodName + " updating the status region with " + value, Logger.CONFIG );
                        synchronized( statusRegion )
                        {
                            statusRegion.setText( " " + value );
                        }
                        if( (value != null) && 
                            (value.equals("") == false) &&
                            (lock == false) )
                        {
                            AutoClearStatus clearer = new AutoClearStatus(this, value);
                            theUpdateTimer.schedule( clearer, AUTOCLEAR_INTERVAL );
                        }
                    }
                    break;
                }

                case PROGRESS_REGION:
                {
                    if( value != null )
                    {
                        if( value.intern() == PROGRESS_START.intern() )
                        {
                            startProgress();
                        }
                        else if( value.intern() == PROGRESS_STOP.intern() )
                        {
                            stopProgress();
                        }
                    }
                    break;
                }

                case MODIFIED_REGION:
                {
                    if( value != null )
                    {
						modifiedLabel.setText( " " + value );
                    }
					if( value.equals("") )
					{
						modifiedLabel.setIcon( null );
					}
					else
					{
						modifiedLabel.setIcon( theResources.getResourceIcon(DIRTY_ICON) );
					}
					break;
                }

				case LOCKED_REGION:
				{
					if( value != null )
					{
						lockedLabel.setToolTipText( value );
						if( value.equals("") )
						{
							lockedLabel.setVisible( false );
						}
						else
						{
							lockedLabel.setVisible( true );
						}
					}
					break;
				}

                default:
                    //Do nothing
            }

            //Force a repaint
            if( isShowing() )
            {
                invalidate();
                validate();
                repaint();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Update the given region. Status region will automatically be cleared.
    */
    public void updateRegion(int region, String value)
    {
        updateRegion( region, value, false );
    }

    /**
    * Clear the given text from the statusbar if it's still there.
    */
    protected synchronized void clearStatus(String text)
    {   
        String methodName = MODULE_NAME + "clearStatus(String)";

        Logger.log( methodName + " text: " + text, Logger.INFO );
        try
        {
            synchronized( statusRegion )
            {
                if( statusRegion.getText().trim().equals(text) )
                {
                    Logger.log( methodName + " Clearing the text.", Logger.INFO );
                    statusRegion.setText("");
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
        }
    }

    /**
    * Start Progress spinner thread
    */
    private synchronized void startProgress()
    {
        String methodName = MODULE_NAME + "startProgress()";

        try
        {
            //Make sure we aren't already spinner
            if( shouldUpdateProgress == true )
            {
                stopProgress();
            }
            shouldUpdateProgress = true;

            synchronized( progressRegion )
            {
                progressRegion.setString( "working..." );
            }

            spinnerTask = new ProgressSpinner(this);
            theSpinnerTimer.scheduleAtFixedRate( spinnerTask, new Date(), SPINNER_PERIOD );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Stop progress spinner thread.
    */
    private synchronized void stopProgress()
    {
        String methodName = MODULE_NAME + "stopProgress()";

        try
        {
            shouldUpdateProgress = false;
            if( spinnerTask != null )
            {
                spinnerTask.cancel();
            }
            synchronized( progressRegion )
            {
                progressRegion.setString( "" );
                progressRegion.setValue( -1 );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Update the progressbar
    */
    protected void updateProgressBar()
    {
        String methodName = MODULE_NAME + "updateProgressBar()";

        try
        {
            //Increment the progress value and move on.
            synchronized( progressRegion )
            {
                int progressValue = progressRegion.getValue() + 1;
                if( progressValue >= 100 )
                {
                    progressValue = 0;
                }

                progressRegion.setValue( progressValue );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "failed", e );
        }
    }
}

/**
* Progress Spinner thread
*/
class ProgressSpinner
    extends TimerTask
{
    private StatusBar statusBar;

    /**
    * Ctor
    */
    protected ProgressSpinner(StatusBar sb)
    {
        statusBar = sb;
    }

    /**
    * Call back into the statusbar to update the progress bar
    */
    public void run() 
    {
        statusBar.updateProgressBar();
    }
}

/**
* Clear the status region after some time.
*/
class AutoClearStatus
    extends TimerTask
{
    private StatusBar statusBar;
    private String theText;

    /**
    * Ctor
    */
    protected AutoClearStatus(StatusBar sb, String text)
    {
        statusBar = sb;
        theText = text;
    }

    /**
    * Call clear
    */
    public void run() 
    {
        statusBar.clearStatus( theText );
        cancel();
    }
}
