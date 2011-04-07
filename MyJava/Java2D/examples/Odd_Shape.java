import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.geom.*;
import java.awt.image.BufferedImage;

public class Odd_Shape extends JApplet{
    
    public void init(){
	buildUI(getContentPane());
    }
    public void buildUI(Container container) {
	setBackground(Color.white);
        OddPanel oddPanel = new OddPanel();
        container.add(oddPanel, BorderLayout.CENTER);
    }

    public static void main(String s[]) {

        JFrame f = new JFrame("Odd_Shape");
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {System.exit(0);}
        });
        Odd_Shape applet = new Odd_Shape();      
        applet.buildUI(f.getContentPane());
        f.setSize(new Dimension(350,200));
        f.setVisible(true);
    }
}

class OddPanel extends JPanel{

	int x, y, x1, y1, x2, y2;
	GeneralPath oddShape;
	BufferedImage bi;
	Graphics2D big;
	boolean firstTime;
	Rectangle area;

	public OddPanel(){
            oddShape = new GeneralPath();
	    firstTime = true;
	    area = new Rectangle();
	}

        public GeneralPath createPath(int x, int y) {
	    x2 = x;
	    y2 = y;
            oddShape.moveTo(x, y);
	    x -= 100;
	    oddShape.lineTo(x, y);
	    y += 50;
	    oddShape.lineTo(x, y);
	    x += 100;
	    oddShape.lineTo(x, y);
            x += 10;
	    y -= 10;
	    x1 = x - 20;
	    y1 = y - 20;
	    oddShape.curveTo(x, y, x1, y1, x2, y2);
	    return oddShape;
	}

	public void paintComponent(Graphics g){
	   // super.paintComponent(g);
	    Graphics2D g2 = (Graphics2D)g;
	    if(firstTime){
  	      Dimension dim = getSize();
	      int w = dim.width;
              int h = dim.height;
	      x = w/2 + 50;
	      y = h/2 - 25;
	      oddShape = createPath(x, y);
	      area = new Rectangle(w, h); 
              bi = (BufferedImage)createImage(w, h);
              big = bi.createGraphics();
 	      big.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
	      firstTime = false;
            }

            // Clears the shape that was previously drawn.
            big.setColor(Color.white);
  	    big.fillRect(0, 0, area.width, area.height);

	    big.setColor(Color.magenta);
	    big.setStroke(new BasicStroke(3.0f));
            big.draw(oddShape);
            // Draws the buffered image to the screen.
            g2.drawImage(bi, 0, 0, this);
                 
	}
}
