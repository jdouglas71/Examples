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
* PlotDataDialog. An Ok dialog container for the PlotDataEditorPanel that allows the user to select which points in a 
* plot to graph.
*
* @author Jason Douglas 1/30/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class PlotDataDialog
    extends OkDialog
{
    /** Module name */
    private static final String MODULE_NAME = "PlotDataDialog.";
	/** title string */
	private String titleString = "Plot Data Editor";
    /** Editor Panel */
    private IEditorPanel plotPanel;

    /**
    * ctor
    *
    * @param plotData IPlotData
    */
    public PlotDataDialog(IPlotData plotData)
    {
        super( OK_CANCEL_DIALOG );

        initPanels(plotData);

		setTitle( titleString + " - " + plotData.getStringProperty(IPlotData.PLOT_NAME) );

        setSize( 400, 550 );
        setLocation( FusionUtils.getCenterPosition(getSize()) );
        setResizable( true );
    }

    /**
    * Initialize the goo components
    *
    * @param plotData IPlotData
    */ 
    private void initPanels(IPlotData plotData)
    {
        String methodName = MODULE_NAME + "initPanels()";
        String labelStr = "";

        try
        {              
            plotPanel = new PlotDataTablePanel();
            plotPanel.setDataModel( plotData );

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
}
