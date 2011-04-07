
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.math.*;
import java.awt.event.*;
import java.text.*;


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
        setTitle( "Do Something Test" );
        setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

        theLabel = new JLabel( "this is a label" );
        theButton = new JButton( "Do Something!" );

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
		setLocation( new Point(200,200) );
    }

    /**
    * Button handler
    */
    public void actionPerformed(ActionEvent e)
    {
        if( e.getSource().equals(theButton) )
        {
			doSomething();
        }
    }

    /**
    * Do Something
    */
    private void doSomething()
    {
		JOptionPane.showMessageDialog( this, "Something!" );
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

