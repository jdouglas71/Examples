package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;

/**
* TabPage. A basic IFusionTab impl.
*
* @author Jason Douglas 5/15/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class TabPage    
	extends FusionView
        implements IFusionTab
{
    /** module name */
    private static final String MODULE_NAME                                                         = "TabPage.";
    /** Tab mnemonic */
    private int tabMnemonic;
    /** Tab Name */
    private String tabName;
    /** Tab XML Element name */
    protected String tabElementName;
    /** tab mnemonic index */
    private int tabMnemonicIndex = -1;
    /** Tab Types */
    private BitSet tabTypes;
    /** Tab component */
    protected JComponent tabComponent;
    /** Enabled Icon */
    private ImageIcon enabledIcon;
    /** Disabled icon */
    private ImageIcon disabledIcon;
	/** Parent tabbed pane */
	protected JTabbedPane theTabPane;

    /** 
    * Default Ctor.
    */
    public TabPage()
    {
    }

    /**
    * Set 'em all ctor.
    *
    * @param name String
    * @param mnemonic int
    * @param comp JComponent
    * @param icon ImageIcon
    */
    public TabPage(String name, int mnemonic, JComponent comp, ImageIcon icon)
    {
        tabName = name;
        tabMnemonic = mnemonic;
		tabComponent = comp;
		enabledIcon = icon;
    }


    //************************************************************************************************//
    // IFusionTab impl
    //

    /**
    * Get the tab mnenonic.
	* 
	* @return int 
    */
    public int getTabMnemonic() 
    {
        return tabMnemonic;
    }

    /**
    * Get the Display name for the tab
    *
    * @return String The display name for the tab.
    */
    public String getTabName() 
    {
        return tabName;
    }

    /**
    * Get a string that can be used as an XML element name for the tab.
    *
    * @return String
    */
    public String getTabElementName() 
    {
        return tabElementName;
    }

    /**
    * Mnemonic index. Let's the tab set the index of the mnemonic indicator in the tab text (usually an underbar).
    * returning -1 means to use the default as defined by the tabbedpane.
    *
    * @param index int The index in the tab name of the mnemonic charcter indicator.
    */
    public void setTabMnemonicIndex(int index) 
    {
        tabMnemonicIndex = index;
    }

    /**
    * Get the type(s) supported by the tab. Use the type constants to determine if
    * tab supports the required type.
    *
    * @return BitSet The types supported by the tab.
    */
    public BitSet getTabTypes() 
    {
        return tabTypes;
    }

    /**
    * Get the component to be displayed in the tab.
    * This will NOT be placed in a JScrollPane before insertion.
    * If the component needs a scrollPane, it should already be in one.
    * If the type requested for the tab is not supported, this will return null.
    *
    * @param type int The Type of tab component requested. Current values are IFusionTab.ADMIN_TYPE, IFusionTab.PROJECT_TYPE, IFusionTab.USER_TYPE.
    *
    * @return JComponent The component for the tab or null if the type is not supported.
    */
    public JComponent getTabComponent(int type) 
    {
        return tabComponent;
    }

    /**
    * Set the Mnemonic for the tab Page
    *
    * @param mnemonic int The new mnemonic for the tab.
    */
    public void setTabMnemonic(int mnemonic) 
    {
        tabMnemonic = mnemonic;
    }


    /**
    * Set the enabled tab icon.
    *
    * @param icon ImageIcon The new enabled Icon for the tab.
    */
    public void setTabIcon(ImageIcon icon) 
    {
        setTabIcon( icon, true );
    }

    /**
    * Get the icon for the tab based on the enabled param.
    *
    * @param enabled boolean The tab state associated with the desired icon.
    *
    * @return ImageIcon The icon for the requested tab state.
    */
    public ImageIcon getTabIcon(boolean enabled) 
    {
        if( enabled )
            return enabledIcon;
        else
            return disabledIcon;
    }

    /**
    * Get the mnemonic character index in the tab display name. Used to determine where to place the indicator (e.g. underbar)
    *
    * @return int Mnemonic character index in the display string.
    */
    public int getTabMnemonicIndex() 
    {
        return tabMnemonicIndex;
    }

    /**
    * Accessors for the icon. Use the enabled param to dictate if it's the Enabled Icon or
    * the Disabled Icon. Default is Enabled.
    *
    * @param icon ImageIcon the new icon for the tab.
    * @param enabled boolean The state of tab associated with the icon.
    */
    public void setTabIcon(ImageIcon icon, boolean enabled) 
    {
        if( enabled )
        {
            enabledIcon = icon;
        }
        else
        {
            disabledIcon = icon;
        }
    }

    /**
    * Store any view state parameters (e.g. splitter pos). There are no required parameters so
    * anything stored here is optional for the tab.
    *
    * @param doc Document Parent Document to create elements from.
    *
    * @return Element The element containing the state of the object.
    */
    public Element storeViewState(org.w3c.dom.Document doc) 
    {
        return null;
    }

    /**
    * Restore any view state parameters that may have been stored by this tab.
    *
    * @param elem Element Contains state information.
    */
    public void restoreViewState(Element elem) 
    {
    }

    /**
    * Get the enabled icon for the tab.
    *
    * @return ImageIcon The icon for the enabled tab state.
    */
    public ImageIcon getTabIcon()
    {
        return getTabIcon( true );
    }

    /**
    * Tell the tab whether or not it should show the info panel (if present) associated with the tab.
    * JGD NOTE: Soon to be deprecated. 4/9/07
    *
    * @param b boolean True if the info panel should be displayed.
    */
    public void showInfoPanel(boolean b) 
    {
        //Going away.
    }

	/**
    * Set the tab's container.
	* 
	* @param tabPane JTabbedPane
    */
	public void setTabbedPane(JTabbedPane tabPane)
	{
		theTabPane = tabPane;
	}

    //************************************************************************************************//
    // IApplicationFrameListener impl
    //
    /**
    * Let the listeners know that the wait state has been changed to the given value.
    * 
    * @param waitState boolean The current value of the frame's waitState.
    */
    public void waitStateChanged(boolean waitState)
    {

    }
    // IApplicationFrameListener impl ends

    //*************************************************************************************************//
    // IValidator impl
    //
    /**
    * This call comes from a selection model. The params Map allows various information to be passed to the valiators. 
    * Returning false will cause the selection model from blocking the change of selection indices, so use the power wisely.
    * 
    * @param params Map<Object,Object> Constraints and other types of information necessary to validate.
    *
    * @return boolean True if the validation passed. 
    */
    public boolean validateContents(java.util.Map<Object,Object> params)
    {
        return true;
    }
    // IValidator impl ends

    //************************************************************************************************//
    // ChangeListener impl
    //
    /**
    * Invoked when the target of the listener has changed its state.
    *
    * @param e  a ChangeEvent object
    */
    public void stateChanged(ChangeEvent e)
    {
    }
    // ChangeListener impl 
    // IFusionTab impl ends
}
