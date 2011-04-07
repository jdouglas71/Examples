package com.jdouglas.framework.ui.widgets;

/**
* TabNavigator. An implementation of the IFusionNavigator class that provides a tab pane.
*
* @author Jason Douglas 5/15/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;

import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.core.events.*;
import com.jdouglas.framework.util.*;

public class TabNavigator
    extends FusionNavigator
        implements IFusionNavigator,ChangeListener
{
    /** module name */
    private static final String MODULE_NAME                                                             = "TabNavigator.";

    /** THe panel */
    private JPanel thePanel;
    /** The Tabbed Pane */
    private JTabbedPane theTabPane;
    /** Map of tab panels */
    private LinkedHashMap<String,IFusionTab> theTabs = new LinkedHashMap<String,IFusionTab>();
    /** the Panel type to be adding */
    private int theType = IFusionTab.INFO_TYPE;
    /** Parent EditorPanel (if there is one) */
    private IEditorPanel theParent;

    /**
    * Ctor.
    *
    * @param type int
    */
    public TabNavigator(int type)
    {
        theType = type;
        initPanels();
    }

    /**
    * Ctor.
    */
    public TabNavigator()
    {
        this( IFusionTab.INFO_TYPE );
    }

    /**
    * Initialize the gui.
    */
    private void initPanels()
    {
        String methodName = MODULE_NAME + "initPanels()";

        thePanel = new JPanel();
        theTabPane = new JTabbedPane();
        theTabPane.setTabPlacement( JTabbedPane.BOTTOM );
        theTabPane.addChangeListener( this );

        //theTabPane.addTab( "Info", new JLabel("Info tab") );
        //theTabPane.addTab( "Error", new JLabel("Error Tab") );

        thePanel.setLayout( new BorderLayout() );

        thePanel.add( theTabPane, BorderLayout.CENTER );
    }

    /**
    * Add tab.
    *
    * @param tab IFusionTab
    */
    public void addTab(IFusionTab tab)
    {
        String methodName = MODULE_NAME + "addTab(IFusionTab)";

        try
        {
            theTabPane.addTab( tab.getTabName(), tab.getTabIcon(), tab.getTabComponent(theType) );
            theTabs.put( tab.getTabName(), tab );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Remove Tab.
    *
    * @param tab IFusionTab 
    */
    public void removeTab(IFusionTab tab)
    {
        String methodName = MODULE_NAME + "removeTab(IFusionTab)";

        try
        {
            theTabPane.remove( tab.getTabComponent(theType) );
            theTabs.remove( tab.getTabName() );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Remove All tabs.
    */
    public void removeAllTabs()
    {
        theTabPane.removeAll();
    }

    /**
    * Set the selected tabpage
    *
    * @param selTab IFusionTab
    */
    public void setSelectedTab(IFusionTab selTab)
    {
        theTabPane.setSelectedComponent( selTab.getTabComponent(theType) );
    }

    /**
    * Get selected Component.
    *
    * @return Component
    */
    public Component getSelectedTabComponent()
    {
        return theTabPane.getSelectedComponent();
    }

    /**
    * Set the parent editorPanel.
    *
    * @param parent IEditorPanel
    */
    public void setParent(IEditorPanel parent)
    {
        theParent = parent;
    }

    /**
    * Get the parent editor Panel. May be null.
    *
    * @return IEditorPanel
    */
    public IEditorPanel getParent()
    {
        return theParent;
    }

	/**
	* Get all the tabs.
	*
	* @return ArrayList<IFusionTab>
	*/
	public ArrayList<IFusionTab> getTabs()
	{
		String methodName = MODULE_NAME + "getTabs()";
		ArrayList<IFusionTab> retval = new ArrayList<IFusionTab>();

		try
		{
			Iterator<IFusionTab> iter = theTabs.values().iterator();
			while( iter.hasNext() )
			{
				retval.add( iter.next() );
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;

	}

    //******************************************************************************************************************//
    // IFusionNavigator impl
    //
    /**
    * Get the navigator component.
    *
    * @return JComponent The navigator component. 
    */
    public JComponent getNavigatorComponent()
    {
        return thePanel;
    }
    // IFusionNavigator impl ends

    //****************************************************************************************************************//
    // ChangeListener impl
    //
    /**
    * Invoked when the target of the listener has changed its state.
    *
    * @param e  a ChangeEvent object
    */
    public void stateChanged(ChangeEvent e)
    {
        String methodName = MODULE_NAME + "stateChanged(ChangeEvent)";

        try
        {
            NavigatorChangeEvent nce = new NavigatorChangeEvent(this,e);

            nce.setProperty( NavigatorChangeEvent.PARENT, theParent );

            fireNavigatorSelectionChange( nce );
        }
        catch(Exception ex)
        {
            FusionUtils.logError( methodName, "Failed", ex );
        }
    }

    // ChangeListener impl ends 
}
