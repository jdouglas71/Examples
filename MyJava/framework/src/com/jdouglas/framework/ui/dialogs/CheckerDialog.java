package com.jdouglas.framework.ui.dialogs;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* CheckerDialog. A dialog with a list of checkboxes containing iTData objects to be selected by the user based on 
* the state of the isVisible flag. 
*
* @author Jason Douglas 2/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class CheckerDialog
    extends OkDialog
		implements ActionListener
{                                         
    /** Module Name */
    private static final String MODULE_NAME                                                             = "CheckerDialog.";
    /** object property for the checkbox */
    private static final String MYOBJECT                                                                = "MyObject";

    /** Checkboxes */
    private ArrayList<JCheckBox> theCheckers = new ArrayList<JCheckBox>();
	/** Select None button */
	private JButton selectNoneButton;
	/** Select All Button */
	private JButton selectAllButton;

    /**
    * Constructor
    *
	* @param parent Window
    * @param data ArrayList<iTData>
    * @param title String
    */
    public CheckerDialog(Window parent, ArrayList<iTData> data, String title)
    {
        super(parent, OK_CANCEL_DIALOG);
        setSize( 225, 300 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );

        setTitle( title );
        setResizable( true );

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}

        initPanel(data);
    }

    /**
    * Set up the controls and panels.
    *
    * @param data ArrayList<iTData>
    */
    private void initPanel(ArrayList<iTData> data)
    {
        String methodName = MODULE_NAME + "initPanel(Object[])";

        JPanel checkerPanel = new JPanel();
        checkerPanel.setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();

        gbc.anchor = GridBagConstraints.WEST;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.gridheight = 1;

        Iterator<iTData> iter = data.iterator();

        while( iter.hasNext() )
        {
            iTData d = iter.next();
            JCheckBox checker = new JCheckBox( d.getStringProperty(iTData.DISPLAY_NAME), d.isVisible() );

            checker.putClientProperty( MYOBJECT, d );
			checker.addKeyListener( this );

            checkerPanel.add( checker, gbc );

            theCheckers.add( checker );
        }

		selectNoneButton = new JButton( FusionApplication.theResources.selectNoneButton );
		selectNoneButton.addActionListener( this );

		selectAllButton = new JButton( FusionApplication.theResources.selectAllButton );
		selectAllButton.addActionListener( this );

		JPanel selectPanel = new JPanel();
		selectPanel.setLayout( new GridBagLayout() );

		gbc.anchor = GridBagConstraints.WEST;
		gbc.insets = new Insets(5,5,5,5);
		gbc.gridwidth = 1;
		selectPanel.add( selectAllButton, gbc );
		gbc.gridwidth = GridBagConstraints.REMAINDER;
		selectPanel.add( selectNoneButton, gbc );

        JPanel centralPanel = new JPanel();
        centralPanel.setLayout( new BorderLayout() );
        centralPanel.add( new JScrollPane(checkerPanel), BorderLayout.CENTER );
		centralPanel.add( selectPanel, BorderLayout.SOUTH );
		centralPanel.setBorder( new EtchedBorder() );

        getContentPane().add( centralPanel, BorderLayout.CENTER );
    }

    /**
    * OK handler
    */
    public void okPressed()
    {
        String methodName = MODULE_NAME + "okPressed()";

        //Iterate thru the checkers and commit the changes to their respective objects. 
        Iterator<JCheckBox> iter = theCheckers.iterator();
        while( iter.hasNext() )
        {
            JCheckBox checker = iter.next();
            iTData data = (iTData)checker.getClientProperty(MYOBJECT);
            if( data != null )
            {
                data.setVisible( checker.isSelected() );
            }
        }

        super.okPressed();
    }

	//********************************************************************************************************//
	// ActionListener impl
	// 
	/**
	* Invoked when an action occurs.
	* 
	* @param e ActionEvent
	*/
	public void actionPerformed(ActionEvent e)
	{
		String methodName = MODULE_NAME + "actionPerfored(ActionEvent)";

		try
		{
			if( e.getSource().equals(selectNoneButton) )
			{
				Iterator<JCheckBox> iter = theCheckers.iterator();
				while( iter.hasNext() )
				{
					iter.next().setSelected(false);
				}
			}
			else if( e.getSource().equals(selectAllButton) )
			{
				Iterator<JCheckBox> iter = theCheckers.iterator();
				while( iter.hasNext() )
				{
					iter.next().setSelected(true);
				}
			}
			else
			{
				super.actionPerformed( e );
			}
		}
		catch( Exception ex )
		{
			FusionUtils.logError( methodName, "Failed", ex );
		}
	}

	// ActionListener impl ends
}
