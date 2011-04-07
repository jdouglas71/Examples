package com.jdouglas.framework.util;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.datatransfer.*;
import java.util.*;

/**
* TablePasteAdapter. Enables paste of excel style strings into a JTable. Not sure why this isn't already built into JTable.
* Adapted from JavaWorld Tip 77. 
*
* @author Jason Douglas
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class TablePasteAdapter
        implements ActionListener
{
    /** Module name */ 
    private static final String MODULE_NAME                                                         = "TablePasteAdapter.";
    /** Paste action string */
    private static final String PASTE_ACTION                                                        = "Paste";

    /** the Table */
    private JTable theTable;
    /** the Clipboard */
    private Clipboard theClipboard;
	/** the keystroke we're using for paste */
	private KeyStroke pasteKey = KeyStroke.getKeyStroke( KeyEvent.VK_V, ActionEvent.CTRL_MASK, false );


    /**
    * Constructor. Registers itself as a paste action for the given JTable.
    *
    * @param table JTable
    */
    public TablePasteAdapter(JTable table)
    {
		setTable( table );
        theClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    }

    /**
    * Get the table.
    *
    * @return JTable
    */
    public JTable getTable()
    {
        return theTable;
    }

    /**
    * Set the table
    *
    * @param table JTable
    */
    public void setTable(JTable table)
    {
		String methodName = MODULE_NAME + "setTable(JTable)";

		try
		{
			theTable = table;
			theTable.registerKeyboardAction( this, PASTE_ACTION, pasteKey, JComponent.WHEN_FOCUSED );
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
    }

    /**
    * Called when the paste keystroke is struck. 
    * 
    * @param e ActionEvent
    */
    public void actionPerformed(ActionEvent e)
    {
        String methodName = MODULE_NAME + "actionPerformed(ActionEvent)";

        if( e.getActionCommand().equals(PASTE_ACTION) )
        {
            Logger.log( methodName + " Pasting!!!", Logger.FINE );
            int startRow = (theTable.getSelectedRows())[0];
            int startCol = (theTable.getSelectedColumns())[0];

            try
            {
                String tmpStr = (String)(theClipboard.getContents(this).getTransferData(DataFlavor.stringFlavor));
				StringBuilder tmpBuf = new StringBuilder(tmpStr);
				ArrayList<StringBuilder> rowStrings = new ArrayList<StringBuilder>();
                //Logger.log( methodName + " Input String:\n" + tmpStr, Logger.DEBUG );
                //Logger.log( methodName + " Input String:\n" + FusionUtils.strToHex(tmpStr), Logger.DEBUG );

				StringBuilder buf = new StringBuilder( " " );
				//Parse into rows (delimited by the new line)
				for(int i=0; i<tmpBuf.length(); i++)
				{
					if( tmpBuf.charAt(i) != '\n' )
					{
						buf.append( tmpBuf.charAt(i) );
					}
					else
					{
						rowStrings.add( buf );
						buf = new StringBuilder( " " );
					}
				}

                for(int i=0; i<rowStrings.size(); i++ )
                {
					StringBuilder rowBuf = rowStrings.get(i);
					ArrayList<String> colStrings = new ArrayList<String>();
					//Logger.log( methodName + " RowStr: " + rowBuf.toString(), Logger.DEBUG );
					//Logger.log( methodName + " RowStr: " + FusionUtils.strToHex(rowBuf.toString()), Logger.DEBUG );

					//Parse row into cols 
					buf = new StringBuilder(" ");
					for(int j=0; j<rowBuf.length(); j++)
					{
						if( rowBuf.charAt(j) != '\t' )
						{
							buf.append( rowBuf.charAt(j) );
						}
						else
						{
							colStrings.add( buf.toString() );
							buf = new StringBuilder( " " );
						}
					}

					//Grab the last column value (it will follow a tab or be the only column).
					colStrings.add( buf.toString() );

					//Parse col Strings into values. 
                    for(int j=0; j<colStrings.size(); j++)
                    {
                        String val = colStrings.get(j);
						//Logger.log( methodName + " val: " + val, Logger.DEBUG );
						//Logger.log( methodName + " val: " + FusionUtils.strToHex(val), Logger.DEBUG );

                        if( startRow+i< theTable.getRowCount()  &&
                            startCol+j< theTable.getColumnCount() )
                        {
							//Determine the class of the column we're pasting into.
							Class c = theTable.getColumnClass(startCol+j);
							Object obj = val;

							if( val.trim().equals("") )
							{
								obj = null;
							}

							//It's easy to create a new object of the given class object using Class.newInstance(). The 
							//difficulty comes in setting the value using the passed in string. I'm not sure the best way to
							//do this, but for now, I'm going to handle specific cases (e.g. Double) and go from there.
							//JGD 5/11/07
							//JGD 4/18/09 I believe the answer is to call valueOf for the class. 
							if( (obj != null) && (c.equals(Double.class)) )
							{
								obj = new Double(val);
							}

                            theTable.setValueAt(obj,startRow+i,startCol+j);
                        }
                        //Logger.log( methodName + " Putting "+ val + " at row= " + (startRow + i) + " column= " + (startCol + j), Logger.DEBUG );
                    }
                }
            }
            catch( Exception ex )
            {
                FusionUtils.logError( methodName, "Failed", ex );
            }
        }
    }
}


