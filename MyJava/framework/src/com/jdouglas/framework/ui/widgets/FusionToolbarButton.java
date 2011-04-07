package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;

/**
* Toolbar buttons for FCA. Common look and feel.
*
* @author Jason Douglas 8/1/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/ 

public class FusionToolbarButton    
    extends JButton
{
    //const
    private static final String MODULE_NAME = "FusionToolbarButton.";
    //data

    //methods
    /**
    * Ctor.
    */
    public FusionToolbarButton(Action action)
    {
        super(action);

        setMargin( new Insets(0,0,0,0) );
        setText("");
        setRolloverEnabled( true );
    }
}
