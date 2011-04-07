package com.jdouglas.framework.plots;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* PlotDataEditorPanel. EditorPanel for PlotData that will allow the user to determine which of the points comprising the 
* plot are displayed.
*
* @author Jason Douglas 1/21/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotDataEditorPanel    
    extends EditorPanel
        implements ActionListener
{
    /** Module Name */
    private static final String MODULE_NAME                                                         = "PlotDataEditorPanel.";
    /** Client property name for the IPointData object embedded in the checkbox */
    private static final String POINT_OBJECT                                                        = "PointObject";

    /** Data Model */
    private IPlotData thePlot;
    /** The checkboxes */
    private ArrayList<JCheckBox> theCheckers = new ArrayList<JCheckBox>();
    /** Checker Panel */
    private JPanel checkerPanel = new JPanel();
    /** select all button */
    private JButton selectAllButton = new JButton( "Select All" );
    /** Select None Button */
    private JButton selectNoneButton = new JButton( "Select None" );

    /**
    * ctor
    */
    public PlotDataEditorPanel()
    {
        initPanel();
    }

    /**
    * Create the controls and place them
    */
    private void initPanel()
    {
        String methodName = MODULE_NAME + "initPanel()";

        //Clear the default EditorPanel controls
        removeAll();

        //setBorder( BorderFactory.createEtchedBorder() );

        setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();

        gbc.anchor = GridBagConstraints.NORTHWEST;
        gbc.fill = GridBagConstraints.BOTH;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.gridheight = 1;
        gbc.weightx = 100;
        gbc.weighty = 100;
        gbc.insets = new Insets(5,5,5,5);

        JScrollPane scroller = new JScrollPane(checkerPanel);
        add( scroller, gbc );

        selectAllButton.addActionListener( this );
        selectNoneButton.addActionListener( this );

        gbc.weightx = 1;
        gbc.weighty = 1;

        gbc.gridwidth = 1;
        add( selectAllButton, gbc );
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        add( selectNoneButton, gbc );
    }


    //*******************************************************************************//
    // IEditorPanel impl
    //

    /**
    * Save the contents without forcing a validation message for the user.
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents()
    {
        String methodName = MODULE_NAME + "saveContents()";
        boolean retval = true;

        try
        {
            Iterator<JCheckBox> iter = theCheckers.iterator();
            while( iter.hasNext() )
            {
                JCheckBox checker = iter.next();
                Object obj = checker.getClientProperty( POINT_OBJECT );
                if( (obj != null) && (obj instanceof IPointData) )
                {
                    IPointData point = (IPointData)obj;
                    point.setVisible( checker.isSelected() );
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
        
        return retval;
    }


    /**
    * Refresh the contained goo elements based on the current configuration/data model.
    */
    public void refreshContents() 
    {
        String methodName = MODULE_NAME + "refreshContents()";

        try
        {
            checkerPanel.removeAll();
            checkerPanel.setLayout( new GridBagLayout() );
            GridBagConstraints gbc = new GridBagConstraints( GridBagConstraints.RELATIVE,
                                                             GridBagConstraints.RELATIVE,
                                                             GridBagConstraints.REMAINDER,
                                                             1,
                                                             1.0, 1.0, GridBagConstraints.NORTHWEST,
                                                             GridBagConstraints.BOTH, 
                                                             new Insets(0,1,0,1),
                                                             0, 0 );

            Iterator<IPointData> iter = thePlot.getPoints().iterator();
            while( iter.hasNext() )
            {
                IPointData p = iter.next();
                JCheckBox checker = new JCheckBox( "" + p.getX() + "," + p.getY(), p.isVisible() );
                checker.putClientProperty( POINT_OBJECT, p );
                //checker.addItemListener( this );
                theCheckers.add( checker );

                checkerPanel.add( checker, gbc );
            }                                

            checkerPanel.repaint();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Accessor for the data model.
    * 
    * @return iTData The data model.
    */
    public iTData getDataModel() 
    {
        String methodName = MODULE_NAME + "getDataModel()";

        return thePlot;
    }
    
    /**
    * Set the data model.
    *
    * @param data iTData The new Data model 
    */
    public void setDataModel(iTData data) 
    {
        String methodName = MODULE_NAME + "setDataModel(iTData)";

        if( data instanceof IPlotData )
        {
            thePlot = (IPlotData)data;
            refreshContents();
        }
    }

    // IEditorPanel impl ends 

    //**********************************************************************************************//
    // ActionListener impl
    //
    /**
    * Invoked when an action occurs.
    */
    public void actionPerformed(ActionEvent e)
    {
        String methodName = MODULE_NAME + "actionPerformed(ActionEvent)";

        if( e.getSource().equals(selectAllButton) )
        {
            Iterator<JCheckBox> iter = theCheckers.iterator();
            while( iter.hasNext() )
            {
                iter.next().setSelected( true );
            }
        }
        else if( e.getSource().equals(selectNoneButton) )
        {
            Iterator<JCheckBox> iter = theCheckers.iterator();
            while( iter.hasNext() )
            {
                iter.next().setSelected( false );
            }
        }
    }

    // ActionListener impl

}

