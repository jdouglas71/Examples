
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
    public enum TestEnum
    {
		UNKNOWN("unknown value"),
        ONE("uno"),
        TWO("dos"),
        THREE("trece"),
        FOUR("cuatro");

        private String theVal;

        private TestEnum(String v) 
        {
            theVal = v;
        }

        public String getVal() 
        {
            return theVal;
        }

        public static TestEnum getTestEnum(Integer id)
		{
			switch( id.intValue() )
			{
				case 1:	
					return ONE;
				case 2:
					return TWO;
				case 3:
					return THREE;
				case 4:
					return FOUR;
				default:
					return UNKNOWN;
			}
		}
    };

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
        //Test t = new Test();
        //t.show();

		Scanner in = new Scanner(System.in);
		System.out.println( "Enter a number: (ONE, TWO, THREE, FOUR) " );
		String input = in.next();

		TestEnum te = TestEnum.valueOf( TestEnum.class, input );

		System.out.println( " te: " + te );
		System.out.println( " te.val = " + te.getVal() );

		System.out.println( " 1 = " + TestEnum.getTestEnum(1) );
		System.out.println( " 5 = " + TestEnum.getTestEnum(5) );
    }
}

