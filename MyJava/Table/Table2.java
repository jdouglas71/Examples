/**
* Table example from the book Graphic Java, Mastering the JFC, ch 19 page 1145.
* Jason Douglas
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.*;

public class Table2 
    extends JFrame
{
    //Const
    //Data
    private JTable theTable;
    //Method
    public Table2()
    {
        theTable = new JTable( new MyTableModel() );
        getContentPane().add( new JScrollPane(theTable), BorderLayout.CENTER );
        this.setDefaultCloseOperation( WindowConstants.DISPOSE_ON_CLOSE );
        setSize( 500, 500 );
        setLocation( 100, 100 );
    }

    public static void main(String[] args)
    {
        JFrame f = new Table2();

        f.show();

    }


}   


class MyTableModel
    extends AbstractTableModel
{
    protected int rows = 100;
    protected int cols = 10;

	protected Object[][] data;
	
	public MyTableModel()
	{
		data = new Object[rows][cols];

		for(int i=0; i<rows; i++)
		{
			for(int j=0; j<cols; j++)
			{
				data[i][j] = Boolean.TRUE;
			}
		}
	}


    public int getRowCount()
    {
        return rows;
    }

    public int getColumnCount()
    {
        return cols;
    }

    public Object getValueAt(int row, int col)
    {
        return data[row][col];
    }

	public void setValueAt(Object val, int row, int col)
	{
		System.out.println( "(" + row + "," + col + ") ----->>> " + val );
		data[row][col] = val;
	}

    public String getColumnName(int col)
    {
        return "Column " + col; 
    }

	public Class getColumnClass(int col)
	{
		return getValueAt(0,col).getClass();
	}

	public boolean isCellEditable(int row, int col)
	{
		return true;
	}
}




