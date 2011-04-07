
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;


public class Test	
	extends JFrame
		implements ActionListener
{
	private JLabel theLabel;
	private JButton theButton;


	/**
	* Ctor
	*/ 
	public Test()
	{
		setTitle( "Make Bigger Test" );
		setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

		theLabel = new JLabel( "this is a label" );
		theLabel.setBorder( BorderFactory.createLineBorder(Color.YELLOW) );
		theButton = new JButton( "MakeBigger" );

		theButton.addActionListener( this );

		JPanel p = new JPanel();
		p.setLayout( new GridBagLayout() );
		GridBagConstraints gbc = new GridBagConstraints();

		gbc.anchor = GridBagConstraints.WEST;
		gbc.gridwidth = GridBagConstraints.REMAINDER;
		gbc.insets = new Insets( 10, 10, 10, 10 );

		p.add( theLabel, gbc );
		p.add( theButton, gbc );

		getContentPane().add( p );

		setSize( 400, 400 );
	}

	/**
	* Button handler
	*/
    public void actionPerformed(ActionEvent e)
	{
		if( e.getSource().equals(theButton) )
		{
			makeBigger();
		}
	}

	/**
	* Attempt to resize the label.
	*/
	private void makeBigger()
	{
		Dimension d = theLabel.getSize();
		d.width += 100;
		theLabel.setSize( d );
		theLabel.setPreferredSize( d );
		theLabel.getGraphics();
	}

	/**
	* Main
	*/
	public static void main(String[] args)
	{
		Test t = new Test();
		t.show();
	}

}

