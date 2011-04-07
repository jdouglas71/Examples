/**
* My version of the shapes2d demo in an application frame.
* @author Jason Douglas 10/21/04
*/

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class ShapesComponent	
	extends JComponent
{
	final static int maxCharHeight = 15;
	final static int minFontSize = 6;

	final static Color bg = Color.blue;
	final static Color fg = Color.yellow;
	final static Color red = Color.red;
	final static Color white = Color.white;

	final static BasicStroke stroke = new BasicStroke( 2.0f );
	final static BasicStroke wideStroke new BasicStroke( 8.0f );

	final static float dash1[] = {10.0f};
	final static BasicStroke dashed = new BasicStroke( 1.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10.0f, dash1, 0.0f);

	private Dimension totalSize;
	private FontMetrics fontMetrics;

	/**
	* Init method.
	*/
	public void init()
	{
		//Set the drawing colors
		setBackground(bg);
		setForeground(fg);
	}

	/**
	* A font picker based on the given string and the boundries set in the globals.
	*/
	public FontMetrics pickFont(Graphics2D g2, String longString, int xSpace)
	{
		boolean fontFits = false;
		Font font = g2.getFont();
		FontMetrics retval = g2.getFontMetrics();
		int size = font.getSize();
		String name = font.getName();
		int style = font.getStyle();

		while( !fontFits )
		{
			if( (retval.getHeight() <= maxCharHeight) &&
				(retval.stringWidth((longString) <= xSpace) )
			{
				fontFits = true;
			}
			else
			{
				if( size <= minFontSize )
				{
					fontFits = true;
				}
				else
				{
					g2.setFont( font.deriveFont(style,--size) );
					retval = g2.getFontMetrics();
				}
			}
		}
	}

	/**
	* Override paint and do some stuff.
	*/
	public void paint(Graphics g)
	{
		Graphics2D g2 = (Graphics2D)g;

		//Tell the renderer to antialias if possible.
		g2.setRenderingHint( RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON );

		//Figure out how much space we need for our "grid".
		Dimension d = getSize();
		int gridWidth = d.width / 6;
		int gridHeight = d.height/ 2;

		fontMetrics = pickFont( g2, "Filled and Stroked GeneralPath", gridWidth );

		color fg3D = Color.lightGray;
		
		g2.setPaint( fg3D );
		g2.draw3DRect( 0, 0, d.width - 1, d.height= 1, true );
		g2.draw3DRect( 3, 3, d.width - 7, d.height - 7, false );
		g2.setPaint( fg );

		int x = 5;
		int y = 7; 
		int rectWidth = gridWidth - (2*x);
		int stringY = gridHeight - 3 - fontMetrics.getDescent();
		int rectHeight = stringY - fontMetrics.getMaxAscent() - y - 2;


	}

}
