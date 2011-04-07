package com.jdouglas.framework.ui.widgets;

import java.awt.*;
import javax.swing.border.*;

/**
* Border class that only paints the bottom line of the border to give an underline effect.
* 
* @author Jason Douglas 4/10/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class UnderlineBorder 
    extends AbstractBorder
{
    //Const
    private static final String MODULE_NAME = "UnderlineBorder.";

    //Data 
    private int thickness = 3;
    private Color color = Color.black;

    /**
    * Create a border of the given thickness and color.
    */
    public UnderlineBorder(int _thickness, Color _color)
    {
        if( _thickness > 0 )
        {
            thickness = _thickness;
        }

        if( _color != null )
        {
            color = _color;
        }
    }

    /**
    * Create a black border of the given thickness.
    */
    public UnderlineBorder(int _thickness)
    {
        this( _thickness, Color.black );
    }

    /**
    * Create a 3 pixel wide black border.
    */
    public UnderlineBorder()
    {
        this( 3, Color.black );
    }

    /**
    * Paint the border
    */
    public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) 
    {
        String methodName = MODULE_NAME + "paintBorder(Component,Graphics,int,int,int,int)";

        Color oldColor = g.getColor();

        g.setColor( color );

        for(int i=0; i<thickness; i++)
        {
            g.drawLine( x-2, y+height-i, x+width+2, y+height-i );
        }

        g.setColor( oldColor );
    }
}
