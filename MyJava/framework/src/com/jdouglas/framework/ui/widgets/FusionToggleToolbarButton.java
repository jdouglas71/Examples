package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;

/**
* Toggle Toolbar buttons for FCA. Common look and feel.
*
* @author Jason Douglas 12/16/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/ 

public class FusionToggleToolbarButton    
    extends JToggleButton
{
    //const
    private static final String MODULE_NAME = "FusionToggleToolbarButton.";
    //data

    //methods
    /**
    * Ctor.
    */
    public FusionToggleToolbarButton(Action action)
    {
        super(action);

        setMargin( new Insets(0,0,0,0) );
        setText("");
    }
}
