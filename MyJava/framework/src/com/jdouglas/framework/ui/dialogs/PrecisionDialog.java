package com.jdouglas.framework.ui.dialogs;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.util.*;
import java.text.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;

/**
* PrecisionDialog. A dialog with a listbox containing items to be selected by the user.
*
* @author Jason Douglas 4/1/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PrecisionDialog
    extends OkDialog
        implements MouseListener,ChangeListener
{
	/** Module name */
    private static final String MODULE_NAME = "PrecisionDialog.";

	//Controls 
	/** Num Decimal places Label */
	private JLabel numDecPlacesLabel;
	/** Num decimal places spinner */
	private JSpinner numDecPlacesSpinner;
	/** Display Text field */
	private JTextField displayField;

	/** Resources */
	private FrameworkResources theResources = (FrameworkResources)FusionApplication.getResources(IFrameworkProperties.class);

    /**
    * Constructor
	* 
	* @param parent Window
	* @param precision Integer
    */
    public PrecisionDialog(Window parent, Integer precision)
    {
        super(parent, OK_CANCEL_DIALOG);
        setSize( 300, 300 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );

        setTitle( theResources.getResourceString(PRECISION_DIALOG_TITLE) );
        setResizable( true );

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}

        initPanel(precision);
    }

	/**
	* Constructor
	*/
	public PrecisionDialog()
	{
		this( FusionApplication.getApplicationFrame().getFrame(), 2 );
	}

    /**
    * Set up the controls and panels.
	* 
	* @param precision Integer
    */
    private void initPanel(Integer precision)
    {
        String methodName = MODULE_NAME + "initPanel()";

		//Controls 
		numDecPlacesLabel = new JLabel( theResources.getResourceString(NUM_DECIMAL_PLACES_LABEL) );
		SpinnerModel numModel = new SpinnerNumberModel( precision.intValue(), 0, 9, 1 );
		numDecPlacesSpinner = new JSpinner( numModel );
		numDecPlacesLabel.setLabelFor( numDecPlacesSpinner );
		numDecPlacesSpinner.addChangeListener(this);

		displayField = new JTextField( 18 );
		displayField.setEditable( false );
		displayField.setHorizontalAlignment(JTextField.RIGHT);
		updateDisplayField();

		//Layout 
		JPanel centerPanel = new JPanel();
		centerPanel.setLayout( new GridBagLayout() );
		JPanel p = new JPanel();
		p.setLayout( new GridBagLayout() );
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.anchor = GridBagConstraints.SOUTHWEST;
		gbc.insets = new Insets(5,5,5,5);

		p.add( numDecPlacesLabel, gbc );
		p.add( numDecPlacesSpinner, gbc );

		gbc.gridwidth = GridBagConstraints.REMAINDER;
		//gbc.fill = GridBagConstraints.HORIZONTAL;
		//gbc.weightx = 1.0;
		centerPanel.add( p, gbc );
		//gbc.weightx = 0.0;
		centerPanel.add( displayField, gbc );

		getContentPane().add( centerPanel, BorderLayout.CENTER );
    }

    /**
    * OK handler
    */
    public void okPressed()
    {
        String methodName = MODULE_NAME + "okPressed()";
        super.okPressed();
    }

    /**
    * Cancel Handler
    */
    public void cancelPressed()
    {
        String methodName = MODULE_NAME + "cancelPressed()";
        super.cancelPressed();
    }

    /**
    * Return the selected Precision.
    *
    * @return Integer
    */
    public Integer getSelectedPrecision()
    {
        return (Integer)numDecPlacesSpinner.getValue();
    }

	/**
    * Update Display Field.
    */
	private void updateDisplayField()
	{
		String methodName = MODULE_NAME + "updateDisplayField()";

		try
		{
			int numPlaces = ((Integer)numDecPlacesSpinner.getValue()).intValue();
			DecimalFormat df = FusionUtils.getDecimalFormat( numPlaces );
			displayField.setText( df.format(1.0) );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

	}

    //**************************************************************************************************//
    // MouseListener impl
    //
    /**
    * Invoked when the mouse button has been clicked (pressed
    * and released) on a component.
    */
    public void mouseClicked(MouseEvent e)
    {
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

	//***************************************************************************************************//
	// ChangeListener impl
	// 
	/**
	* Invoked when the target of the listener has changed its state.
	*
	* @param evt  a ChangeEvent object
	*/
	public void stateChanged(ChangeEvent evt)
	{
		String methodName = MODULE_NAME + "stateChanged(ChangeEvent)";

		try
		{
			updateDisplayField();
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	// ChangeListener impl ends 
}
