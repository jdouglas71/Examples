package com.jdouglas.framework.ui.charts;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;
import java.beans.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;

import org.jfree.chart.*;
import org.jfree.chart.axis.*;
import org.jfree.chart.plot.*;
import org.jfree.chart.renderer.xy.*;
import org.jfree.chart.title.*;
import org.jfree.data.xy.*;
import org.jfree.ui.*;
import org.jfree.chart.annotations.*;

/**
* XYChartPanel. Creates a graph using JFreeChart.
*
* @author Jason Douglas 1/17/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class XYChartPanel
    extends EditorPanel
{
	/** Module name */
    private static final String MODULE_NAME                                                             = "XYChartPanel.";
    /** Panel name */
    public static final String XY_CHART_PANEL                                                           = "XYChartPanel";
    /** Data Model */
    private IPlotCollection thePlots = null;
    /** sentry */
    private boolean refreshContentsSentry = false;
    private boolean validateContentsSentry = false;
    /** The Chart */
    private JFreeChart theChart = null; 
	/** chart container */
    private JPanel theChartPanel = null;

    /**
    * Ctor 
    */
    public XYChartPanel()
    {
        setProperty( PANEL_NAME, XY_CHART_PANEL );
        initPanels();
    }

    /**
    * Create the controls and put together the layout.
    */
    private void initPanels()
    {
        String methodName = MODULE_NAME + "initPanels()";

        //Clear the default EditorPanel controls
        removeAll();

        setBorder( BorderFactory.createEtchedBorder() );

        setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();

        gbc.anchor = GridBagConstraints.NORTHWEST;
        gbc.fill = GridBagConstraints.BOTH;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.gridheight = GridBagConstraints.REMAINDER;
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 100;
        gbc.weighty = 100;
        gbc.insets = new Insets(5,5,5,5);

        theChartPanel = createChartPanel();

        add( theChartPanel, gbc );
    }

    /**
    * Creates a sample dataset.
    * 
    * @return The dataset.
    */
    private XYDataset createDataset() 
    {
        XYSeriesCollection retval = new XYSeriesCollection();

        if( thePlots != null )
        {
            Iterator<IPlotData> iter = thePlots.getPlots().iterator();
            while( iter.hasNext() )
            {
                IPlotData plotData = iter.next();
                XYSeries series = new XYSeries( plotData.getStringProperty(IPlotData.PLOT_NAME) );
                Iterator<IPointData> ptIter = plotData.getPoints().iterator();
                while( ptIter.hasNext() )
                {
                    IPointData pt = ptIter.next();

                    if( pt.isVisible() )
                    {
                        series.add( pt.getX(), pt.getY() );
                    }
                }
                retval.addSeries( series );
            }
        }

        return retval;
    }

    /**
    * Creates a sample chart.
    * 
    * @param dataset  a dataset.
    * 
    * @return The chart.
    */
    private JFreeChart createChart(XYDataset dataset) 
    {
        String methodName = MODULE_NAME + "createChart(XYDataSet)";
        JFreeChart retval = null;

        try
        {
            if( thePlots != null )
            {
                retval = ChartFactory.createXYLineChart( thePlots.getStringProperty(IPlotCollection.CHART_TITLE),
                                                         thePlots.getStringProperty(IPlotCollection.X_AXIS_TITLE),
                                                         thePlots.getStringProperty(IPlotCollection.Y_AXIS_TITLE),
                                                         dataset, 
                                                         PlotOrientation.VERTICAL,
                                                         true,
                                                         true,
                                                         false 
                                                       );

                //Add the subtitle if it exists
                String tmpStr = thePlots.getStringProperty(IPlotCollection.CHART_SUB_TITLE);
                if( tmpStr != null )
                {
                    retval.addSubtitle( new TextTitle(tmpStr) );
                }

                //Add the source title if it exists.
                tmpStr = thePlots.getStringProperty(IPlotCollection.CHART_SOURCE_TITLE);
                if( tmpStr != null )
                {
                    TextTitle source = new TextTitle( tmpStr );

                    source.setFont(new Font("SansSerif", Font.PLAIN, 10));
                    source.setPosition(RectangleEdge.BOTTOM);
                    source.setHorizontalAlignment(HorizontalAlignment.RIGHT);
                    retval.addSubtitle(source);
                }

                retval.setBackgroundPaint( Color.white );

                XYPlot plot = (XYPlot)retval.getPlot();
                plot.setBackgroundPaint( (Paint)thePlots.getProperty(IPlotCollection.BACKGROUND_PAINT) );
                plot.setRangeGridlinePaint( (Paint)thePlots.getProperty(IPlotCollection.GRIDLINE_PAINT) );
                plot.setRangeGridlinesVisible( ((Boolean)thePlots.getProperty(IPlotCollection.GRIDLINES_VISIBLE)).booleanValue() );

                //Range (y-axis) markers
                Iterator<IPlotMarker> markerIter = thePlots.getRangeMarkers().iterator();
                while( markerIter.hasNext() )
                {
                    plot.addRangeMarker( markerIter.next().getMarker(), Layer.BACKGROUND );
                }

                //Domain (x-axis) markers
                markerIter = thePlots.getDomainMarkers().iterator();
                while( markerIter.hasNext() )
                {
                    plot.addDomainMarker( markerIter.next().getMarker(), Layer.BACKGROUND );
                }

                //customise the range axis...
                NumberAxis rangeAxis = (NumberAxis)plot.getRangeAxis();

                // customise the renderer...
                XYLineAndShapeRenderer renderer = (XYLineAndShapeRenderer)plot.getRenderer();

                Iterator<IPlotData> plotIter = thePlots.getPlots().iterator();
                int i = 0;
                while( plotIter.hasNext() )
                {
                    IPlotData plotData = plotIter.next();

                    //Logger.log( methodName + " plot name: " + plotData.getStringProperty(IPlotData.PLOT_NAME), Logger.DEBUG );
                    renderer.setSeriesVisible( i, plotData.isVisible() );
            
                    if( plotData.getProperty(IPlotData.STROKE) != null )
                    {
                        renderer.setSeriesStroke( i, (Stroke)plotData.getProperty(IPlotData.STROKE) );
                    }
                    else
                    {
                        plotData.setProperty( IPlotData.STROKE, renderer.getSeriesStroke(i) );
                    }

                    if( plotData.getProperty(IPlotData.OUTLINE_STROKE) != null )
                    {
                        renderer.setSeriesOutlineStroke( i, (Stroke)plotData.getProperty(IPlotData.OUTLINE_STROKE) );
                    }
                    else
                    {
                        plotData.setProperty( IPlotData.OUTLINE_STROKE, renderer.getSeriesOutlineStroke(i) );
                    }

                    if( plotData.getProperty(IPlotData.SHAPE) != null )
                    {
                        renderer.setSeriesShape( i, (Shape)plotData.getProperty(IPlotData.SHAPE) );
                    }
                    else
                    {
                        plotData.setProperty(IPlotData.SHAPE, renderer.getSeriesShape(i) );
                    }

                    if( plotData.getProperty(IPlotData.PAINT) != null )
                    {
                        //Logger.log( methodName + " Using the stored Paint object: " + ((Paint)plotData.getProperty(IPlotData.PAINT)).toString(), Logger.DEBUG );
                        renderer.setSeriesPaint( i, (Paint)plotData.getProperty(IPlotData.PAINT) );
                    }
                    else
                    {
                        //Logger.log( methodName + " Using default Paint object and storing it: " + renderer.getSeriesPaint(i).toString(), Logger.DEBUG );
                        plotData.setProperty(IPlotData.PAINT, renderer.getSeriesPaint(i) );
                    }

                    if( plotData.getProperty(IPlotData.SHAPES_VISIBLE) != null )
                    {
                        renderer.setSeriesShapesVisible( i, ((Boolean)plotData.getProperty(IPlotData.SHAPES_VISIBLE)).booleanValue() );
                    }
					else
					{
						plotData.setProperty( IPlotData.SHAPES_VISIBLE, renderer.getSeriesShapesVisible( i ) );
					}

                    if( plotData.getProperty(IPlotData.VISIBLE_IN_LEGEND) != null )
                    {
                        renderer.setSeriesVisibleInLegend(i, ((Boolean)plotData.getProperty(IPlotData.VISIBLE_IN_LEGEND)).booleanValue() );
                    }

                    if( plotData.getProperty(IPlotData.ANNOTATION) != null )
                    {
                        if( plotData.isVisible() )
                        {
							Object obj = plotData.getProperty(IPlotData.ANNOTATION);

							if( obj instanceof XYAnnotation )
							{
								plot.addAnnotation( (XYAnnotation)obj );
							}
							else if( obj instanceof String )
							{
								IPointData pt = plotData.getPoints().get( plotData.getPoints().size()/2 );
								XYPointerAnnotation annot = new XYPointerAnnotation( (String)obj, pt.getX(), pt.getY(), -(Math.PI)/2.0 );
								annot.setLabelOffset( TOP_ALIGNMENT );
								plot.addAnnotation( annot );
							}
                        }
                    }

                    if( plotData.getProperty(IPlotData.LINES_VISIBLE) != null )
                    {
                        renderer.setSeriesLinesVisible( i, ((Boolean)plotData.getProperty(IPlotData.LINES_VISIBLE)).booleanValue() );
                    }

                    i++;
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
    * Creates a panel for the chart. 
    * 
    * @return A panel.
    */
    public JPanel createChartPanel() 
    {
        JFreeChart chart = createChart(createDataset());
        return new ChartPanel(chart);
    }

    /**
    * Enable controls based on contents.
    */
    protected void enableControls()
    {
        if( (thePlots == null) || (isViewEnabled() == false) )
        {
            enableControls( false );
        }
        else
        {
            enableControls( true );
        }   
    }

    /**
    * Enable Controls based on param.
    *
    * @param b boolean 
    */
    protected void enableControls(boolean b)
    {
        String methodName = MODULE_NAME + "enableControls(boolean)";

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    //***********************************************************************//
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
        super.setProperty( key, val );
    }

    /**
    * Refresh the contained goo elements based on the current configuration/data model.
    */
    public void refreshContents()
    {
        String methodName = MODULE_NAME + "refreshContents()";

        try
        {
            refreshContentsSentry = true;
            //Do stuff here

            initPanels();

            refreshContentsSentry = false;
        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Extracting APPLICATION_MODULES failed.", x );
            refreshContentsSentry = false;
        }

        enableControls();
        revalidate();
        repaint();
    }

    /**
    * Validate contained portion of the GOO vs data model
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if contents are valid. 
    */
    public boolean validateContents(boolean forceMsg)
    {
        String methodName = MODULE_NAME + "validateContents(boolean)";
        boolean retval = true;

        validateContentsSentry = false;

        return retval;
    }

    /**
    * Save the values in the contained GOO elements to the data model.
    *
    * @param forceMsg boolean Display all validation messages to the user. 
    *
    * @return boolean True if the save operation was successful. 
    */
    public boolean saveContents(boolean forceMsg)
    {
        String methodName = MODULE_NAME + "saveContents(boolean)";
        boolean retval = true;

        //Validate the contents and move on as necessary.
        retval = validateContents(forceMsg);

        if( retval == true )
        {
        }
        else
        {
            Logger.log( methodName + " validation failed not saving.", Logger.DEBUG );
        }

        return retval;
    }

    /**
    * Resets the panel contents to the values stored in the data model.
    */
    public void resetContents()
    {
        String methodName = MODULE_NAME + "resetContents()";

        try
        { 
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
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

        try
        {
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Retrieve the data model.
    * 
    * @return iTData The data model.
    */
    public iTData getDataModel()
    {
        return thePlots;
    }

    /**
    * Set the Data Model.
    * 
    * @param newData iTData The Data model.
    */
    public void setDataModel(iTData newData)
    {
        String methodName = MODULE_NAME + "setDataModel(iTData)";

        try
        {
            if( hasBeenModified() == true )
            {
                saveContents();
            }

            if( newData instanceof IPlotCollection )
            {
                thePlots = (IPlotCollection)newData;

                enableControls();
                refreshContents();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Enable\Disable the Panel. This means no validation, editing, saving, etc.
    *
    * @param b boolean 
    */
    public void setViewEnabled(boolean b)
    {
        String methodName = MODULE_NAME + "setViewEnabled(boolean)";

        super.setViewEnabled( b );
        if( isViewEnabled() )
        {
            //Enable based on contents
            enableControls();
        }
        else
        {
            //Disable everybody
            enableControls(false);
        }
    }

    /**
    * Set the editable flag on the panel. If false, the input components will be disabled. This is not the same as disabling 
    * the entire panel, which disables ALL components in the panel.
    *
    * @param b boolean
    */
    public void setEditable(boolean b)
    {
        super.setEditable( b );
        enableControls();
    }

    //**********************************************************************************************************//
    // VetoableChangeListener impl
    //
    /**
    * This method gets called when a constrained property is changed.
    *
    * @param     evt a <code>PropertyChangeEvent</code> object describing the
    *            event source and the property that has changed.
    * @exception PropertyVetoException if the recipient wishes the property
    *              change to be rolled back.
    */
    public void vetoableChange(PropertyChangeEvent evt)
        throws PropertyVetoException
    {

    }
    // VetoableChangeListener impl

    //**********************************************************************************************************//
    // PropertyChangeListener impl
    //
    /**
    * This method gets called when a bound property is changed.
    * @param evt A PropertyChangeEvent object describing the event source 
    *      and the property that has changed.
    */
    public void propertyChange(PropertyChangeEvent evt)
    {

    }
    // PropertyChangeListener impl ends

    // IEditorPanel impl ends
}
