package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.text.*;
import java.io.*;

import com.jdouglas.framework.util.*;

/**
* HTMLPanel --  A panel that displays a given HTML document.
*
* @author Jason Douglas 1/7/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class HTMLPanel
    extends JPanel
{
	/** module name */
    private static final String MODULE_NAME                                                     = "HTMLPanel.";
    /** Test case string */
    private static final String TEST_CASE                                                       = "TEST CASE";
	/** Test html */
    private static final String TEST_HTML                                                       = "";

	/** Editor component */
    private JEditorPane viewer;
	/** Text to display */
    private String theText;

    /**
    * Create an HTMLPanel displaying the given text.
    */
    public HTMLPanel(String htmlText)
    {
        setLayout( new BorderLayout() );

        try
        {
            StringBuffer buffer = new StringBuffer();
            if( (htmlText == null) || (htmlText.equalsIgnoreCase(TEST_CASE)) )
            {
                /*File f = new File( "test.rtf" );
                FileReader reader = new FileReader(f);
                char[] buf = new char[4096];
                int len = 0;
                while( ((len = reader.read(buf)) != -1) )
                {
                    buffer.append( buf );
                }
                theText = buffer.toString();
                */
                theText = TEST_HTML;
            }
            else
            {
                theText = htmlText;
            }
            
            viewer = new JEditorPane( "text/html", theText );
            viewer.setEditable( false );

            add( new JScrollPane(viewer), BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( MODULE_NAME+"ctor", "Failed", e );
        }
    }

    /**
    * Create a panel with fake data.
    */
    public HTMLPanel()
    {
        this( TEST_CASE );
    }

    /**
    * Completely resets the text in the panel. Use an empty string to reset the panel. 
    * Null is ignored. The given text is assumed to be in RTF format.
    */
    public void setText(String newText)
    {
        String methodName = MODULE_NAME + "setText(String)";

        try
        {
            if( newText != null )
            {
                viewer.setCursor( Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR) );
                theText = newText;
                viewer.setText(theText);
                viewer.setCaretPosition(0);
                viewer.setCursor( null );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Error resetting text: " + e.getMessage(), e );
        }
    }

    /**
    * Returns the JTextComponent.
    *
    * @return JTextComponent
    */
    public JTextComponent getTextComponent()
    {
        return viewer;
    }
}

