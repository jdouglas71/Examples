
/**
 * The tester class for the DNDList. This class creates the lists, 
 * positions them in a frame, populates the list with the default 
 * data.
 *
 * @version 1.0
 *
 */

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;


public class TestDND
{
	public static void main (String args[])
	{
		TestDND testDND = new TestDND();
	}

	/**
	 * constructor
	 * creates the frame, the lists in it and sets the data in the lists
	 */

	public TestDND()
	{
		JFrame f = new JFrame("Drag and Drop Lists");

		DNDList sourceList = new DNDList();

		// add data to the source List
		DefaultListModel sourceModel = new DefaultListModel();

		sourceModel.addElement( "Source Item1");
		sourceModel.addElement( "Source Item2");
		sourceModel.addElement( "Source Item3");
		sourceModel.addElement( "Source Item4");

		// gets the panel with the List and a heading for the List
		JPanel sourcePanel = getListPanel(sourceList, "SourceList", sourceModel); 

		DNDList targetList = new DNDList();

		// add data to the target List 
		DefaultListModel targetModel = new DefaultListModel();

		targetModel.addElement( "Target Item1");
		targetModel.addElement( "Target Item2");
		targetModel.addElement( "Target Item3");
		targetModel.addElement( "Target Item4");

		JPanel targetPanel = getListPanel(targetList, "TargetList", targetModel); 
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.X_AXIS));
		mainPanel.add( sourcePanel );
		mainPanel.add( targetPanel );

		f.getContentPane().add( mainPanel );
		f.setSize (300, 300);
		f.addWindowListener (new WindowAdapter()
							 {
								 public void windowClosing(WindowEvent e)
								 {
									 System.exit(0);
								 }
							 });
		f.setVisible (true);
	}

	/**
	 * a convenience method
	 * used for positioning of the ListBox and the Label.
	 * 
	 * @param list  - the special DND List
	 * @param labelName - the heading for the list
	 * @param listModel - model for the list
	 */

	private JPanel getListPanel(DNDList list, String labelName, DefaultListModel listModel )
	{
		JPanel listPanel = new JPanel();
		JScrollPane scrollPane = new JScrollPane(list);

		list.setModel(listModel);   
		JLabel nameListName = new JLabel(labelName );

		listPanel.setLayout( new BorderLayout());
		listPanel.add(nameListName, BorderLayout.NORTH);
		listPanel.add( scrollPane, BorderLayout.CENTER);

		return listPanel;     
	}

}
