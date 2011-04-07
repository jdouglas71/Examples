package com.jdouglas.framework.plots;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.ui.dialogs.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;

/**
* PlotCollectionDialog. An Ok dialog container for the PlotDataEditorPanel that allows the user to select which points in a 
* plot to graph.
*
* @author Jason Douglas 2/20/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class PlotCollectionDialog
    extends OkDialog
		implements ItemListener 
{
    /** Module name */
    private static final String MODULE_NAME = "PlotCollectionDialog.";
    /** title string */
    private String titleString = "Plot Data Editor";
    /** Editor Panel */
    private IEditorPanel plotPanel;
	/** Data */
	private IPlotCollection thePlots;
	/** plots combo */
	private JComboBox plotsCombo;

    /**
    * ctor
    *
    * @param plots IPlotCollection
    */
    public PlotCollectionDialog(IPlotCollection plots)
    {
        super( OK_CANCEL_DIALOG );

		thePlots = plots;

        initPanels();

        setTitle( titleString ); 

        setSize( 400, 550 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );
        setResizable( true );
    }

    /**
    * Initialize the goo components
    */ 
    private void initPanels()
    {
        String methodName = MODULE_NAME + "initPanels()";
        String labelStr = "";

        try
        {              
			JLabel label = new JLabel( "Select a plot to edit: " );

			plotsCombo = new JComboBox();
			Iterator<IPlotData> iter = thePlots.getPlots().iterator();
			while( iter.hasNext() )
			{
				plotsCombo.addItem( iter.next() );
			}

			plotsCombo.setSelectedIndex( 0 );
			plotsCombo.addItemListener( this );
			plotsCombo.addKeyListener( this );

			JPanel panel = new JPanel();
			panel.add( label );
			panel.add( plotsCombo );

			getContentPane().add( panel, BorderLayout.NORTH );

            plotPanel = new PlotDataTablePanel();
            plotPanel.setDataModel( (IPlotData)plotsCombo.getSelectedItem() );

            getContentPane().add( plotPanel.getComponent(), BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * React to ok button click.
    */
    public void okPressed()
    {
        plotPanel.saveContents();
        super.okPressed();
    }

	//****************************************************************************************//
	// ItemListener impl
	//
    /**
    * Invoked when an item has been selected or deselected by the user.
    * The code written for this method performs the operations
    * that need to occur when an item is selected (or deselected).
    */    
    public void itemStateChanged(ItemEvent e)
	{
		if( e.getSource().equals( plotsCombo ) )
		{
			if( e.getStateChange() == ItemEvent.SELECTED )
			{
				plotPanel.saveContents();
				plotPanel.setDataModel( (IPlotData)e.getItem() );
			}
		}
	}

	// ItemListener impl ends

}
