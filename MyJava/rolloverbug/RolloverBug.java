/**
* Example to display the rollover bug in JToolbar in JDK 1.4.2.
* 
* Jason Douglas 8/1/03
*/

import java.awt.*;
import javax.swing.*;


public class RolloverBug
	extends JFrame
{
	private JToolBar theToolbar;
	

	public RolloverBug()
	{
		this.setDefaultCloseOperation( WindowConstants.EXIT_ON_CLOSE );

		this.setSize( 200, 200 );

		theToolbar = new JToolBar();
		theToolbar.setRollover( true );

		JButton button = new JButton( "Should be Rollover" );
		button.setRolloverEnabled( true );

		theToolbar.add( button );

		getContentPane().add( theToolbar, BorderLayout.NORTH );
	}


	public static void main(String[] args)
	{
		try
		{
			//Set the look and feel to winders
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");

			JFrame f = new RolloverBug();

            
            //Update the Component UI
            //SwingUtilities.updateComponentTreeUI(f);

			f.show();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}
