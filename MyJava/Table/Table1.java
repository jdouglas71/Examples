/**
* Table example from the book Graphic Java, Mastering the JFC, ch 19 page 1145.
* Jason Douglas
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.*;

public class Table1 
	extends JFrame
{
	//Const
	//Data
	private JTable theTable;
	//Method
	public Table1()
	{
		theTable = new JTable( new MyTableModel() );
		getContentPane().add( new JScrollPane(theTable), BorderLayout.CENTER );
		this.setDefaultCloseOperation( WindowConstants.DISPOSE_ON_CLOSE );
		setSize( 500, 500 );
		setLocation( 100, 100 );
	}

	public static void main(String[] args)
	{
		JFrame f = new Table1();

		f.show();
	}
}	


class MyTableModel
	extends AbstractTableModel
{
	protected int rows = 100;
	protected int cols = 10;

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
		return "(" + row + "," + col + ")";
	}

	public String getColumnName(int col)
	{
		return "Column " + col; 
	}
}




