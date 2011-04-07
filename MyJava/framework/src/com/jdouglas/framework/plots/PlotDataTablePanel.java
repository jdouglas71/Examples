package com.jdouglas.framework.plots;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import java.util.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.util.models.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* PlotDataTablePanel. EditorPanel for PlotData that will allow the user to determine which of the points comprising the 
* plot are displayed using a JTable.
*
* @author Jason Douglas 1/31/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class PlotDataTablePanel    
    extends EditorPanel
        implements ActionListener,MouseListener
{
    /** Module Name */
    private static final String MODULE_NAME                                                         = "PlotDataTablePanel.";
    /** Client property name for the IPointData object embedded in the checkbox */
    private static final String POINT_OBJECT                                                        = "PointObject";

    /** Data Model */
    private IPlotData thePlot;
    /** The table */
    private JTable theTable;
    /** the Table model */
    private PlotDataTableModel theModel;
    /** the sort table model */
    private SortTableModel theSortModel;
    /** select all button */
    private JButton selectAllButton = new JButton( "Select All" );
    /** Select None Button */
    private JButton selectNoneButton = new JButton( "Select None" );
    /** Table Panel */
    private JPanel tablePanel;
    /** Table Scroller panel */
    private JPanel scrollerPanel;

    /**
    * ctor
    */
    public PlotDataTablePanel()
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

        setBorder( BorderFactory.createEtchedBorder() );

        setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();

		gbc.anchor = GridBagConstraints.CENTER;
        gbc.fill = GridBagConstraints.BOTH;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        //gbc.gridheight = 1;
        gbc.weightx = 100;
        gbc.weighty = 100;
        gbc.insets = new Insets(5,5,5,5);

        tablePanel = new JPanel();
        tablePanel.setLayout( new BorderLayout() );

        scrollerPanel = new JPanel();
        scrollerPanel.setLayout( new GridBagLayout() );
        add( scrollerPanel, gbc );

        selectAllButton.addActionListener( this );
        selectNoneButton.addActionListener( this );

        gbc.weightx = 1;
        gbc.weighty = 1;
		gbc.fill = GridBagConstraints.NONE;

        gbc.gridwidth = 1;
        add( selectAllButton, gbc );
        //gbc.gridwidth = GridBagConstraints.REMAINDER;
        add( selectNoneButton, gbc );
    }

    /**
    * Create the table.
    */
    private void initTable()
    {
        String methodName = MODULE_NAME + "initTable()";
		ImageIcon upArrowIcon = FusionApplication.theResources.getResourceIcon( IFrameworkProperties.UP_ARROW_HEADER_ICON );
		ImageIcon downArrowIcon = FusionApplication.theResources.getResourceIcon( IFrameworkProperties.DOWN_ARROW_HEADER_ICON );
        
        try
        {
            if( thePlot != null )
            {
                theTable = null;
                theModel = new PlotDataTableModel( thePlot );
                theSortModel = new SortTableModel( theModel );
                theTable = new JTable( theSortModel );                                  
                theTable.getColumnModel().setColumnMargin(1);
                theTable.setColumnSelectionAllowed(false);
                theTable.setRowSelectionAllowed(false);
                theTable.setDragEnabled(false);
                theTable.getTableHeader().setReorderingAllowed(false);
                theTable.getTableHeader().addMouseListener( this );

                //Set the Cell Renderers and widths

                //INCLUDE_COL
                TableColumn col = theTable.getColumn( theModel.getColumnName(PlotDataTableModel.INCLUDED) );
                col.setCellRenderer( new CheckBoxTableCellRenderer() );
                col.setHeaderRenderer( new SortLabelHeaderRenderer(theSortModel, upArrowIcon, downArrowIcon) );
                int minWidth = FusionUtils.getPreferredWidthForColumn(col,theTable);
                if( minWidth > 0 ) 
                {
                    col.setMinWidth( minWidth/2 );
                    col.setMaxWidth( minWidth*3 ); //JGD I admit it. I'm multiplying by 3 arbitrarily
                    col.setWidth( minWidth );
                }

                //X_POINT
                col = theTable.getColumn( theModel.getColumnName(PlotDataTableModel.X_POINT) );
                col.setCellRenderer( new LabelTableCellRenderer() );
                col.setHeaderRenderer( new SortLabelHeaderRenderer(theSortModel, upArrowIcon, downArrowIcon) );
                minWidth = FusionUtils.getPreferredWidthForColumn(col,theTable);
                if( minWidth > 0 ) 
                {
                    col.setMinWidth( minWidth/2 );
                    col.setMaxWidth( minWidth*3 ); //JGD I admit it. I'm multiplying by 3 arbitrarily
                    col.setWidth( minWidth );
                }

                //Y_POINT
                col = theTable.getColumn( theModel.getColumnName(PlotDataTableModel.Y_POINT) );
                col.setCellRenderer( new LabelTableCellRenderer() );
                col.setHeaderRenderer( new SortLabelHeaderRenderer(theSortModel, upArrowIcon, downArrowIcon) );
                minWidth = FusionUtils.getPreferredWidthForColumn(col,theTable);
                if( minWidth > 0 ) 
                {
                    col.setMinWidth( minWidth/2 );
                    col.setMaxWidth( minWidth*3 ); //JGD I admit it. I'm multiplying by 3 arbitrarily
                    col.setWidth( minWidth );
                }

                //Clear panels
                scrollerPanel.removeAll();
                tablePanel.removeAll();

                if( theModel.getRowCount() > 0 )
                {
                    //Setup scrollpanes and add to table panel
                    JScrollPane scrollPane = new JScrollPane( theTable );

                    Dimension tableD = theTable.getPreferredSize();

                    scrollPane.setPreferredSize( new Dimension(tableD.width+100, tableD.height+100) );
                    scrollPane.setViewportBorder( new EmptyBorder(0,0,0,0) );
                    scrollPane.getVerticalScrollBar().setUnitIncrement( 10 );
                    scrollPane.getHorizontalScrollBar().setUnitIncrement( 10 );

                    tablePanel.add( scrollPane, BorderLayout.CENTER );
                    GridBagConstraints gbc = new GridBagConstraints();
                    gbc.anchor = GridBagConstraints.CENTER;

                    gbc.weightx = 2.0;
                    gbc.weighty = 2.0;
                    gbc.fill = GridBagConstraints.BOTH;

                    scrollPane = new JScrollPane( tablePanel );
                    scrollPane.getVerticalScrollBar().setUnitIncrement( 10 );
                    scrollPane.getHorizontalScrollBar().setUnitIncrement( 10 );

                    scrollerPanel.add( scrollPane, gbc );

                    theSortModel.sortTable( PlotDataTableModel.X_POINT );
                }

                tablePanel.invalidate();
                tablePanel.validate();
                tablePanel.repaint();
            }

            scrollerPanel.invalidate();
            scrollerPanel.validate();
            scrollerPanel.repaint();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
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
            theModel.saveChanges();
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
            initTable();
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

		try
		{
			if( e.getSource().equals(selectAllButton) )
			{
				for(int i=0; i<theModel.getRowCount(); i++)
				{
					theModel.setValueAt( new Boolean(true), i, PlotDataTableModel.INCLUDED );
				}
				theTable.invalidate();
				theTable.repaint();
			}
			else if( e.getSource().equals(selectNoneButton) )
			{
				for(int i=0; i<theModel.getRowCount(); i++)
				{
					theModel.setValueAt( new Boolean(false), i, PlotDataTableModel.INCLUDED );
				}
				theTable.invalidate();
				theTable.repaint();
			}
		}
		catch(Exception x)
		{
			FusionUtils.logError( methodName, "Failed", x );
		}
    }
    // ActionListener impl

    //**************************************************************************//
    // MouseListener impl
    //

    /**
    * Invoked when the mouse button has been clicked (pressed
    * and released) on a component.
    *
    * @param e MouseEvent
    */
    public void mouseClicked(MouseEvent e)
    {
        String methodName = MODULE_NAME + "mouseClicked(MouseEvent)";
        Logger.log( methodName, Logger.FINE );
        try
        {
            if( theTable != null )
            {
                TableColumnModel tcm = theTable.getColumnModel();
                int vc = tcm.getColumnIndexAtX(e.getX());
                int mc = theTable.convertColumnIndexToModel(vc);
                theSortModel.sortTable( mc );
                theTable.invalidate();
                theTable.repaint();

                Logger.log( methodName + "source class: " + e.getSource().getClass().getName() );
                if( e.getSource() instanceof JTableHeader )
                {
                    JTableHeader header = (JTableHeader)e.getSource();
                    header.invalidate();
                    header.repaint();
                }
            }
        }
        catch(Exception x)
        {
            FusionUtils.logError( methodName, "Failed", x );
        }
    }

    /**
    * Invoked when a mouse button has been pressed on a component.
    *
    * @param e MouseEvent
    */
    public void mousePressed(MouseEvent e)
    {
    }

    /**
    * Invoked when a mouse button has been released on a component.
    *
    * @param e MouseEvent
    */
    public void mouseReleased(MouseEvent e)
    {
    }

    /**
    * Invoked when the mouse enters a component.
    *
    * @param e MouseEvent
    */
    public void mouseEntered(MouseEvent e)
    {
    }

    /**
    * Invoked when the mouse exits a component.
    *
    * @param e MouseEvent
    */
    public void mouseExited(MouseEvent e)
    {
    }

    // MouseListener impl ends

}

