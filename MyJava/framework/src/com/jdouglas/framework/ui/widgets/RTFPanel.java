package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

import com.jdouglas.framework.util.*;

/**
* A panel that displays a given RTF document.
* NOTE: There appears to be a limitation in RTF support. This code will not work for 
* RTF generated in WORD XP, but will for RTF generated by WordPad. So if a document doesn't 
* show up here, save it in wordpad.  <br><br>
* JGD TODO: Figure out the difference btwn rtf in word and wordpad. <br><br>
* 
* @author Jason Douglas 1/7/03
* Copyright � 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class RTFPanel
    extends JPanel
{
    //Const 
    private static final String MODULE_NAME = "RTFPanel.";
    public static final String TEST_CASE = "TEST CASE";
    private static final String TEST_RTF = "Test Values for Fusion Admninistrator";

    //Data
    private JEditorPane viewer;
    private String theText;

    //Methods
    /**
    * Create an RTFPanel displaying the given text.
    */
    public RTFPanel(String rtfText)
    {
        setLayout( new BorderLayout() );

        try
        {
            StringBuffer buffer = new StringBuffer();
            if( (rtfText == null) || (rtfText.equalsIgnoreCase(TEST_CASE)) )
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
                theText = TEST_RTF;
            }
            else
            {
                theText = rtfText;
            }
            
            viewer = new JEditorPane( "text/rtf", theText );
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
    public RTFPanel()
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
}

