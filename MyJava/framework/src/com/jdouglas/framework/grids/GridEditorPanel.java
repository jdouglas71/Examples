package com.jdouglas.FusionAE.grids;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.ui.dialogs.*;
import com.jdouglas.framework.ui.widgets.*;
import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.core.*;

import com.jdouglas.FusionAE.interfaces.data.*;

/**
* GridEditorPanel. First pass at the M2A1 data grid for FusionAE. 
*
* @author Jason Douglas 4/16/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridEditorPanel
    extends EditorPanel
{
    /** Module name */
    private static final String MODULE_NAME                                                             = "GridEditorPanel.";
    /** The panel name. */
    protected static final String DESIGN_PANEL                                                          = "GridEditorPanel";
    /** data Model */
    private IColumnGrid theGrid;
    /** Prevent recursive reentry */
    private boolean validateContentsSentry = false;
    /** The main Table */
    private JTable theTable;
    /** the Header Table */
    private JTable theHeaderTable;
    /** The tabel model */
    private GridTableModel theModel;
    /** The Scroll Pane */
    private JScrollPane theScrollPane;
    /** The paste adapter */
    private TablePasteAdapter thePasteAdapter;

    /**
    * Constructor 
    */ 
    public GridEditorPanel()
    {
        setProperty( PANEL_NAME, DESIGN_PANEL );
    }

    /**
    * Create the controls and panel and lay them out.
    */
    private void initPanel()
    {
        String methodName = MODULE_NAME + "initPanel()";

        try
        {
            //remove the contents of the panel and start from scratch.
            removeAll();

            initTable();

            setLayout( new BorderLayout() );
            add( theScrollPane, BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Enable the controls based on their contents. Any rules the values of one control
    * disabling another based on some value should be enforced here.
    */
    protected void enableControls()
    {
        String methodName = MODULE_NAME + "enableControls()";
        if( (theGrid == null) || (isViewEnabled() == false) ) //no config, no controls
        {
            enableControls(false);
        }
        else
        {
            //Enable the controls based on whatever the current state of the panel is. 
        }
    }
    
    /**
    * Enable the controls based only on the value of the param
    * 
    * @param b boolean 
    */
    protected void enableControls(boolean b)
    {
        //Call setEnabled for all controls here with param
    }

    /**
    * Request Focus for the configname field.
    */
    private void setInitFocus()
    {
        String methodName = MODULE_NAME + "setInitFocus()";

        if( (theGrid != null) && (isViewEnabled() == true) )
        {
            //Set the focus to the whatever the first control in the sequence should be 
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
        String methodName = MODULE_NAME + "setProperty(Object,Object)";

        super.setProperty( key, val );

        if( key.equals(INIT_FOCUS) )
        {
            if( val instanceof Boolean )
            {
                boolean b = ((Boolean)val).booleanValue();
                if( b == true )
                {
                    setInitFocus();
                }
            }
        }
    }

    /**
    * Refresh the contained goo elements based on the current configuration/data model.
    */
    public void refreshContents()
    {
        String methodName = MODULE_NAME + "refreshContents()";

        if( theGrid != null )
        {
            //UPdate the gui based on the values in the data model here 
			initPanel();
			invalidate();
			validate();
			repaint();
			
        }
    }

    /**
    * Validate contained portion of the GOO vs data model
    *
    * @return boolean True if valid. 
    */
    public boolean validateContents(boolean forceMsg)
    {
        String methodName = MODULE_NAME + "validateContents(boolean)";
        boolean retval = true;
        int focusTarget = -1;

        String reasonFailed = "";

        if( (validateContentsSentry == false) && (isViewEnabled() == true) )
        {
            validateContentsSentry = true;
        }
        else
        {
            return retval;
        }

		try
		{
			Logger.log( methodName, Logger.FINEST );
			//Logger.logStackTrace( new Exception( "Whose calling me?" ) );
	
			// VALIDATE GUI contents vs whatever rules here HERE
		} 
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
		finally
		{
			validateContentsSentry = false;
		}

        return retval;
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

        Logger.log( methodName, Logger.FINE );
        //Logger.logStackTrace( new Exception("Who's calling me?") );

        //No config, no save
        if( (theGrid == null) || (isViewEnabled() == false) ) 
        {
            Logger.log( methodName + " theGrid is null.", Logger.FINEST );
            retval = false;
            return retval;
        }

        //Validate the contents and move on as necessary.
        retval = validateContents(forceMsg);

        if( retval == true )
        {
            try
            {
                //Save GUI values to data model here
                if( theModel.isDirty() )
                {
					theModel.saveContents();
                }
            }
            catch(Exception e)
            {
                FusionUtils.logError( methodName, "Failed", e );
                retval = false;
            }
        }
        return retval;
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
            if( (theGrid != null) && (isViewEnabled() == true) ) 
            {
                //TEST GUI contents vs theGrid values here 
                retval = theModel.isDirty();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Accessor for the data model.
    * 
    * @return iTData The data model.
    */
    public iTData getDataModel()
    {
        return theGrid;
    }

    /**
    * Set the data model.
    *
    * @param newData iTData The new Data model 
    */
    public void setDataModel(iTData newData)
    {
        String methodName = MODULE_NAME + "setDataModel(iTData)";

        if( newData instanceof IColumnGrid )
        {
            theGrid = (IColumnGrid)newData;
        }

        initPanel();
        enableControls();
        refreshContents();
    }

    /**
    * Set the enabled state for the panel. Disabled means no editing, saving, validating, etc.
    *
    * @param b boolean The new enabled state of the panel. 
    */
    public void setViewEnabled(boolean b)
    {
        String methodName = MODULE_NAME + "setViewEnabled(boolean)";

        super.setViewEnabled(b);
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

    /**
    * Add a listener to the panel. The class param will help the implementor determine what 
    * contained components are appropriate for the listener to be attached to.
    *
    * @param listener Object The listener to add
    * @param listenerType Class The type of listening the listener would like to do. 
    */
    public void addListener(Object listener, Class listenerType)
    {
        String methodName = MODULE_NAME + "setListener(Object,Class)";

        try
        {
            //Just an example of what you would look for.
            if( listenerType.equals(ComponentListener.class) )
            {
                //Add the listener to something. Probably should remove it first so you don't have duplicates.
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    // IEditorPanel impl ends

    /**
    * Create the tables using the Grid
    */
    protected void initTable()
    {
        String methodName = MODULE_NAME + "initTable()";
        int minWidth = 0;

        //Create the model 
        theModel = new GridTableModel( theGrid );
        theModel.setEditable( true );

        //Create the tables 
        theTable = new JTable( theModel );                                  
        theTable.getColumnModel().setColumnMargin(1);
        theTable.getTableHeader().setReorderingAllowed(false);
        theTable.setAutoResizeMode( JTable.AUTO_RESIZE_OFF );
        theTable.setSelectionMode( ListSelectionModel.MULTIPLE_INTERVAL_SELECTION );
        theTable.setRowSelectionAllowed( true );
        theTable.setColumnSelectionAllowed( true );
        theTable.setCellSelectionEnabled( true );
        thePasteAdapter = new TablePasteAdapter( theTable );

        theScrollPane = new JScrollPane( theTable );

        //Create the header table
        RunLabelTableModel headerModel = new RunLabelTableModel(theGrid);
        theHeaderTable = new JTable( headerModel );
        theHeaderTable.setAutoResizeMode( JTable.AUTO_RESIZE_OFF );
        theHeaderTable.getTableHeader().setReorderingAllowed( false );
        theHeaderTable.setRowSelectionAllowed( false );
        theHeaderTable.setColumnSelectionAllowed( false );
		TableColumnModel tcm = theHeaderTable.getColumnModel();
		TableColumn firstColumn = tcm.getColumn(0);
        theHeaderTable.setPreferredScrollableViewportSize( new Dimension( firstColumn.getPreferredWidth() + 
                                                                          theHeaderTable.getColumnModel().getColumnMargin(), 0 ) );

        //Set the renderer for the header table
        TableColumn col = theHeaderTable.getColumn( IGrid.RUN_NUMBER );
        LabelTableCellRenderer r = new LabelTableCellRenderer();
        r.setBackground( Color.lightGray );
        r.setBorder( new EtchedBorder() );              
        col.setCellRenderer( r );
        col.setHeaderRenderer( new LabelHeaderRenderer() );
        //Don't want to be able to resize the header table
        col.setMaxWidth( col.getPreferredWidth() );
        col.setMinWidth( col.getPreferredWidth() );

        //Set the CellRenderer and determine minimum widths for the main table 
        for(int i=0; i<theModel.getColumnCount(); i++)
        {
            col = theTable.getColumn( theModel.getColumnName(i) );
            LabelTableCellRenderer rr = new LabelTableCellRenderer();
            col.setCellRenderer( rr );
            col.setHeaderRenderer( new LabelHeaderRenderer() );
            int tmp = FusionUtils.getPreferredWidthForColumn(col,theTable);
            if( tmp > minWidth )
            {
                minWidth = tmp;
            }
        }

        //Set the minimum widths
        for(int i=0; i<theModel.getColumnCount(); i++)
        {
            col = theTable.getColumn( theModel.getColumnName(i) );
            col.setMinWidth( minWidth );
        }

        theScrollPane.setRowHeaderView( theHeaderTable );
        theScrollPane.setCorner( JScrollPane.UPPER_LEFT_CORNER, theHeaderTable.getTableHeader() );
    }
}



