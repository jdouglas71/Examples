package com.jdouglas.framework.core;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.border.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.ui.dialogs.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;

/**
* EditorPanel. Base implementation of the editor panel. The goal is to provide as much common functionaliy in this class as possible 
* for all derived editor panels. There is support in this class for minimize and maximize buttons as well as support for using this 
* panel in a wizard. 
*
* @author Jason Douglas 6/6/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public abstract class EditorPanel
    extends FusionView
        implements IEditorPanel,ActionListener
{
	/** Module name */
    private static final String MODULE_NAME                                                             = "EditorPanel.";

	/** Is the panel editable flag */
    protected boolean isEditable = true;
	/** the Wizard dialog Next button. Get passed in by the wizard dialog via setProperties.  */
	protected JButton nextButton;
	/** the Wizard dialog Back button. Get passed in by the wizard dialog via setProperties.  */
	protected JButton backButton;
	/** Parent IWizardContainer (if there is one) */
	protected IWizardContainer wizardContainer;
    /** the Center Panel  */
    protected JPanel theCenterPanel;
	/** The Top Panel*/
    protected JPanel theTopPanel;
    /** Display Label */
    protected JLabel theTopDisplayLabel = new JLabel();
	/** Min button */
    protected JButton minButton;
	/** Max Button */
    protected JButton maxButton;
    /** Window State */
    protected boolean isMinimized = false;
	/** GBC for the entire panel */
    private GridBagConstraints mainGBC = new GridBagConstraints();
	/** GBC for the center panel */
    private GridBagConstraints centerGBC = new GridBagConstraints();
	/** Control List */
	protected ArrayList<JComponent> theControls = new ArrayList<JComponent>();

    /**
    * Constructor
    * 
    * @param minMaxButton True if the min and max buttons should be displayed.
    */
    protected EditorPanel(boolean minMaxButton)
    {
		super();
        setLayout( new GridBagLayout() );

        mainGBC.anchor = GridBagConstraints.WEST;
        mainGBC.gridwidth = GridBagConstraints.REMAINDER;
        mainGBC.fill = GridBagConstraints.BOTH;
        mainGBC.weightx = 100;

        theCenterPanel = new JPanel();

        theTopPanel = new JPanel();
        theTopPanel.setLayout( new GridBagLayout() );

        centerGBC.anchor = GridBagConstraints.WEST;
        centerGBC.gridwidth = 1;
        centerGBC.insets = new Insets(1,5,1,5);

        minButton = new JButton( FusionApplication.theResources.getResourceIcon(IFrameworkProperties.MINUS_ICON) );
        minButton.setMargin( new Insets(0,0,0,0) );
        minButton.addActionListener( this );

        maxButton = new JButton( FusionApplication.theResources.getResourceIcon(IFrameworkProperties.PLUS_ICON) );
        maxButton.setMargin( new Insets(0,0,0,0) );
        maxButton.addActionListener( this );

        theTopDisplayLabel.setHorizontalTextPosition( SwingConstants.LEFT );
        
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.anchor = GridBagConstraints.NORTHEAST;
        gbc.gridwidth = 1;

        buttonPanel.add( minButton, gbc );
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        buttonPanel.add( maxButton, gbc );

        if( isMinimized )
        {
            minButton.setVisible( false );
            maxButton.setVisible( true );

            String tmpStr = (String)getProperty( DISPLAY_NAME );
            if( tmpStr == null )
            {
                tmpStr = "NO DISPLAY NAME";
            }
            theTopDisplayLabel.setText( tmpStr );
            theTopDisplayLabel.setToolTipText( tmpStr );
        }
        else
        {
            theTopDisplayLabel.setText( "" );
            theTopDisplayLabel.setToolTipText( "" );
            minButton.setVisible( true );
            maxButton.setVisible( false );
        }


        centerGBC.gridwidth = 1;
        centerGBC.weightx = 100.0;
        theTopPanel.add( theTopDisplayLabel, centerGBC );
        centerGBC.gridwidth = GridBagConstraints.REMAINDER;
        centerGBC.anchor = GridBagConstraints.NORTHEAST;
        centerGBC.weightx = 1.1;
        centerGBC.gridx = 10;
        theTopPanel.add( buttonPanel, centerGBC );
        centerGBC.gridx = GridBagConstraints.RELATIVE;

        //theTopPanel.setBorder( BorderFactory.createRaisedBevelBorder() );
        //theCenterPanel.setBorder( BorderFactory.createLineBorder(Color.GREEN) );

        if( minMaxButton )
        {
            mainGBC.anchor = GridBagConstraints.NORTHEAST;
            mainGBC.fill = GridBagConstraints.BOTH;
            add( theTopPanel, mainGBC );
            mainGBC.anchor = GridBagConstraints.WEST;
        }
        add( theCenterPanel, mainGBC );
    }

    /**
    * Constructor
    */
    protected EditorPanel()
    {
        this( false );
    }

	/**
	* Enable the controls based only on the value of the param
	* 
	* @param b boolean 
	*/
	protected void enableControls(boolean b)
	{
		String methodName = MODULE_NAME + "enableControls(boolean)";
		try
		{
			Iterator<JComponent> iter = theControls.iterator();
			while( iter.hasNext() )
			{
				iter.next().setEnabled( b );
			}

		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Enable the controls based on content 
	*/
	protected void enableControls()
	{
		String methodName = MODULE_NAME + "enableControls(boolean)";
		try
		{
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    //*******************************************************************************//
    // IEditorPanel impl
    //

	/**
	* Setter
	*
	* @param key Object The lookup key for the property.
	* @param val Object The value to be stored via the key. 
	*/
	public void setProperty(Object key, Object val)
	{
		String methodName = MODULE_NAME + "setProperty(Object,Object)";

		//Do this first. Let the base impl rule unless we have a specific reason not to.
		super.setProperty(key,val);

		if( key.equals(IFrameworkProperties.FINISH_BUTTON) )
		{
			if( val instanceof JButton )
			{
				nextButton = (JButton)val;
			}
		}
		else if( key.equals(IFrameworkProperties.BACK_BUTTON) )
		{
			if( val instanceof JButton )
			{
				backButton = (JButton)val;
			}
		}
		else if( key.equals(IFrameworkProperties.WIZARD_CONTAINER) )
		{
			if( val instanceof IWizardContainer )
			{
				wizardContainer = (IWizardContainer)val;
				Iterator<JComponent> iter = theControls.iterator();
				while( iter.hasNext() )
				{
					iter.next().addKeyListener( wizardContainer );
				}
			}
		}
	}

    /**
    * Save the values in the contained GOO elements to the data model.
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents(boolean forceMsg) 
    {
        String methodName = MODULE_NAME + "saveContents(boolean)";
        boolean retval = true;

        return retval;
    }

    /**
    * Save the values in the contained GOO elements to the data model.
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents() 
    {
        return saveContents( false );
    }

    /**
    * Validate contained portion of the GOO vs data model.
    * The forceMsg param forces the method to display any errors it finds.
    *
    * @return boolean True if valid. 
    */
    public boolean validateContents(boolean forceMsg) 
    {
        String methodName = MODULE_NAME + "validateContents(boolean)";
        boolean retval = true;

        return retval;
    }

    /**
    * Validate contained portion of the GOO vs data model
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents() 
    {
        return validateContents(false);
    }

    /**
    * Determine if the data presented to the user by this component has been modified.
    *
    * @return boolean True if contents have been modified by the user. 
    */
    public boolean hasBeenModified() 
    {
        String methodName = MODULE_NAME + "hasBeenModified()";
        boolean retval = false;

        return retval;
    }

    /**
    * Set the editable flag on the panel. If false, the input components will be disabled. This is not the same as disabling 
    * the entire panel, which disables ALL components in the panel.
    *
    * @param b boolean
    */
    public void setEditable(boolean b)
    {
        isEditable = b;
    }

    // IEditorPanel impl ends (PARTIAL IMPL, ABSTRACT CLASS)

    //********************************************************************************************************//
    // ActionListener impl
    // 
    /**
    * Invoked when an action occurs.
    */
    public void actionPerformed(ActionEvent e)
    {
        String methodName = MODULE_NAME + "actionPerformed(ActionEvent)";

        try
        {
            if( e.getSource().equals(minButton) )
            {
                minButton.setVisible( false );
                maxButton.setVisible( true );
                isMinimized = true;
                theTopPanel.invalidate();
                theTopPanel.validate();
                theTopPanel.repaint();
                
                String tmpStr = (String)getProperty( DISPLAY_NAME );
                if( tmpStr == null )
                {
                    tmpStr = "NO DISPLAY NAME";
                }
                theTopDisplayLabel.setText( tmpStr );
                theTopDisplayLabel.setToolTipText( tmpStr );
                theCenterPanel.setVisible( false );

                invalidate();
                validate();
                repaint();
            }
            else if( e.getSource().equals(maxButton) )
            {
                maxButton.setVisible( false );
                minButton.setVisible( true );
                isMinimized = false;
                theTopPanel.invalidate();
                theTopPanel.validate();
                theTopPanel.repaint();

                theTopDisplayLabel.setText( "" );
                theTopDisplayLabel.setToolTipText( "" );
                
                theCenterPanel.setVisible( true );

                invalidate();
                validate();
                repaint();
            }
        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Failed", x );
        }
    }

    // ActionListener impl ends
}
    
