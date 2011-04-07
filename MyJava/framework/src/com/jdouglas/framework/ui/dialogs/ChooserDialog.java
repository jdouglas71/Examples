package com.jdouglas.framework.ui.dialogs;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;

/**
* ChooserDialog. A dialog with a listbox containing items to be selected by the user.
*
* @author Jason Douglas 4/1/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ChooserDialog
    extends OkDialog
        implements MouseListener
{
	/** Module name */
    private static final String MODULE_NAME = "ChooserDialog.";

	/** the LIst box control */
    private JList dataList;
	/** Selected Values */
    private ArrayList<Object> selectedValues;
	/** Multi-select flag */
    private boolean isMultiSelect = true;

    /**
    * Constructor
    *
    * @param data ArrayList<Object>
    * @param title String
    * @param multiSelect boolean 
    */
    public ChooserDialog(ArrayList<Object> data, String title, boolean multiSelect)
    {
        super(FusionApplication.getApplicationFrame().getFrame(), OK_CANCEL_DIALOG);
        setSize( 300, 300 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );

        setTitle( title );
        setResizable( true );

        initPanel(data);

		ImageIcon icon = FusionApplication.getApplicationIcon();
		if( icon != null )
		{
			setIconImage( icon.getImage() );
		}
    }

    /**
    * Constructor. Default to single selection.
    *
    * @param data ArrayList<Object>
    * @param title String
    */
    public ChooserDialog(ArrayList<Object> data, String title)
    {
        this( data, title, false );
    }

    /**
    * Set up the controls and panels.
    *
    * @param data ArrayList<Object>
    */
    private void initPanel(ArrayList<Object> data)
    {
        String methodName = MODULE_NAME + "initPanel(Object[])";

        int dataLen = data.size();
        Object[] vals = new Object[dataLen];
        for(int i=0; i<dataLen; i++)
        {
            vals[i] = data.get( i );
        }

        dataList = new JList( vals );
        dataList.setBorder( new EmptyBorder(new Insets(1,5,1,5)) );
        dataList.addKeyListener( this );
        dataList.addMouseListener( this );
        if( isMultiSelect == true )
        {
            dataList.setSelectionMode( ListSelectionModel.MULTIPLE_INTERVAL_SELECTION );
        }
        else
        {
            dataList.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
        }
        dataList.setSelectedIndex( 0 );

        JPanel centralPanel = new JPanel();
        centralPanel.setLayout( new BorderLayout() );
        centralPanel.add( new JScrollPane(dataList), BorderLayout.CENTER );

        getContentPane().add( centralPanel, BorderLayout.CENTER );
    }

    /**
    * OK handler
    */
    public void okPressed()
    {
        String methodName = MODULE_NAME + "okPressed()";
        selectedValues = new ArrayList<Object>();
        Object[] vals = dataList.getSelectedValues();
        for(int i=0; i<vals.length; i++)
        {
            selectedValues.add( vals[i] );
        }
        super.okPressed();
    }

    /**
    * Cancel Handler
    */
    public void cancelPressed()
    {
        String methodName = MODULE_NAME + "cancelPressed()";
        selectedValues = new ArrayList<Object>();
        super.cancelPressed();
    }

    /**
    * Return the selected Values.
    *
    * @return ArrayList<Object>
    */
    public ArrayList<Object> getSelectedValues()
    {
        return selectedValues;
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
        if( e.getSource().equals(dataList) == true )
        {
            if( e.getButton() == MouseEvent.BUTTON1 )
            {
                if( e.getClickCount() == 2 )
                {
                    okPressed();
                }
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
}
