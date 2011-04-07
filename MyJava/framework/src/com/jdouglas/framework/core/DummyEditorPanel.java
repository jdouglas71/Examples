package com.jdouglas.framework.core;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.border.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.core.*;

/**
* DummyEditorPanel. A placeholder editor panel that just displays the string given in the constructor. 
*
* @author Jason Douglas 4/20/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class DummyEditorPanel
    extends EditorPanel
{
	/** Module name */
    private static final String MODULE_NAME = "DummyEditorPanel.";
	/** Label */
	private JLabel theLabel;

    /**
    * Ctor
	* 
	* @param text String 
    */
    public DummyEditorPanel(String text)
    {
		setLayout(new BorderLayout() );
		theLabel = new JLabel( text, SwingConstants.CENTER );
		theControls.add( theLabel );
		add( theLabel, BorderLayout.CENTER );
    }
}
    
