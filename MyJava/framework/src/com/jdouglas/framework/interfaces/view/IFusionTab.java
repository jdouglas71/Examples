package com.jdouglas.framework.interfaces.view;

import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.listeners.*;

/**
* IFusionTab. Interface that allows the IApplicationFrame to interact with each of the tabbed panes.
* Extends ChangeListener so these objects can be registered with the tab pane and 
* track the tabswitching. This is really the PAGE interface, but I called it tab at
* first and I'm sticking to it for now.
* 
* Added type property. Tabs can be more than one type. JGD 11/4/03
* 
* @author Jason Douglas
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionTab
    extends ChangeListener, IValidator, IApplicationFrameListener,IFusionView
{
	//JGD TODO: Not really using this yet. Should revisit for FAE project. it would be nice to expand this to be more generic than just tabs (e.g. Navigator, editor, etc.).
    /** Tab type enum. */
    public static final int NUM_TYPES                                                       = 4;    //JGD TODO Make a first last set of consts and get rid of this.
    public static final int UNKNOWN_TYPE                                                    = 0;
    public static final int ADMIN_TYPE                                                      = 1;
    public static final int PROJECT_TYPE                                                    = 2;
    public static final int USER_TYPE                                                       = 3;
    public static final int INFO_TYPE                                                       = 4;

    /** View Properties */
    public static final String SPLITTER_POS                                                 = "SplitterPosition";
    public static final String SHOW_CONSTRAINTS                                             = "ShowConstraints";
	public static final String NAV_SPLITTER_POS												= "navSplitterPos";

    /**
    * Get the Display name for the tab
    *
    * @return String The display name for the tab. 
    */
    public String getTabName();

    /**
    * Get a string that can be used as an XML element name for the tab.
    *
    * @return String
    */
    public String getTabElementName();

    /**
    * Get the type(s) supported by the tab. Use the type constants to determine if 
    * tab supports the required type.
    *
    * @return BitSet The types supported by the tab. 
    */
    public BitSet getTabTypes();

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
    public JComponent getTabComponent(int type);

    /**
    * Set the Mnemonic for the tab Page
    *
    * @param mnemonic int The new mnemonic for the tab.
    */
    public void setTabMnemonic(int mnemonic);

    /**
    * Get the tab mnenonic.
    */
    public int getTabMnemonic();

    /**
    * Mnemonic index. Let's the tab set the index of the mnemonic indicator in the tab text (usually an underbar).
    * returning -1 means to use the default as defined by the tabbedpane.
    *
    * @param index int The index in the tab name of the mnemonic charcter indicator.
    */ 
    public void setTabMnemonicIndex(int index);

    /**
    * Get the mnemonic character index in the tab display name. Used to determine where to place the indicator (e.g. underbar)
    */
    public int getTabMnemonicIndex();

    /**
    * Accessors for the icon. Use the enabled param to dictate if it's the Enabled Icon or 
    * the Disabled Icon. Default is Enabled.
    *
    * @param icon ImageIcon the new icon for the tab.
    * @param enabled boolean The state of tab associated with the icon.
    */
    public void setTabIcon(ImageIcon icon, boolean enabled);

    /**
    * Set the enabled tab icon.
    * 
    * @param icon ImageIcon The new enabled Icon for the tab.
    */  
    public void setTabIcon(ImageIcon icon);

    /**
    * Get the icon for the tab based on the enabled param.
    *
    * @param enabled boolean The tab state associated with the desired icon.
    *
    * @return ImageIcon The icon for the requested tab state. 
    */
    public ImageIcon getTabIcon(boolean enabled);

    /**
    * Get the enabled icon for the tab.
    *
    * @return ImageIcon The icon for the enabled tab state. 
    */
    public ImageIcon getTabIcon();

    /**
    * Tell the tab whether or not it should show the info panel (if present) associated with the tab.
    * JGD NOTE: Soon to be deprecated. 4/9/07
    * 
    * @param b boolean True if the info panel should be displayed.
    */
    public void showInfoPanel(boolean b);

	/**
    * Set the tab's container.
	* 
	* @param tabPane JTabbedPane
    */
	public void setTabbedPane(JTabbedPane tabPane);

}
