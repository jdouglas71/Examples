import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.applet.Applet;
import java.awt.geom.*;
import java.awt.image.BufferedImage;

public class Quad extends JApplet{

    static protected JLabel label;
    QuadPanel quadPanel;

    public void init(){
	//Initialize the layout.
        getContentPane().setLayout(new BorderLayout());
        quadPanel = new QuadPanel();
        quadPanel.setBackground(Color.white);
        getContentPane().add(quadPanel);
        label = new JLabel("Drag the points to adjust the curve.");
        getContentPane().add("South", label);
    }

    public static void main(String s[]) {
        JFrame f = new JFrame("Quad");
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {System.exit(0);}
        });
        JApplet applet = new Quad();
        f.getContentPane().add(applet, BorderLayout.CENTER);
        applet.init();
        f.pack();
        f.setSize(new Dimension(350,250));
        f.setVisible(true);
    }
}

class QuadPanel extends JPanel implements MouseListener, MouseMotionListener{

	BufferedImage bi;
	Graphics2D big;
	int x, y;
	Rectangle area, startpt, endpt, ctrl, rect;	
	QuadCurve2D.Double quad = new QuadCurve2D.Double();
	Point2D.Double start, end, control, point;
	boolean firstTime = true;
	boolean pressOut = false;

	public QuadPanel(){

                setBackground(Color.white);
                addMouseMotionListener(this);
                addMouseListener(this);

		start = new Point2D.Double();
		control = new Point2D.Double();
		end = new Point2D.Double();

                quad.setCurve(start, control, end);
		startpt = new Rectangle(0, 0, 8, 8);
		endpt = new Rectangle(0, 0, 8, 8);
		ctrl = new Rectangle(0, 0, 8, 8);
	}

	public void mousePressed(MouseEvent e){

		x = e.getX();
		y = e.getY();

		if(startpt.contains(x, y)){
			rect = startpt;
			point = start;
			x = startpt.x - e.getX();
			y = startpt.y - e.getY();
			updateLocation(e);
		}
 		else if(endpt.contains(x, y)){
			rect = endpt;
			point = end;
			x = endpt.x - e.getX();
			y = endpt.y - e.getY();
			updateLocation(e);
		}
		else if(ctrl.contains(x, y)){
			rect = ctrl;
			point = control;
			x = ctrl.x - e.getX();
			y = ctrl.y - e.getY();
			updateLocation(e);
		}
		else {
			pressOut = true;
		}
	}

	public void mouseDragged(MouseEvent e){
                if(!pressOut) {
                        updateLocation(e);
                } 
	}

	public void mouseReleased(MouseEvent e){

               if(startpt.contains(e.getX(), e.getY())){
                        rect = startpt;
                        point = start;
                        updateLocation(e);
                }
                else if(endpt.contains(e.getX(), e.getY())){
                        rect = endpt;
                        point = end;
                        updateLocation(e);
                }
                else if(ctrl.contains(e.getX(), e.getY())){
                        rect = ctrl;   
                        point = control;
                        updateLocation(e); 
                }
                else {
                        pressOut = false;
                }
	}

	public void mouseMoved(MouseEvent e){}

	public void mouseClicked(MouseEvent e){}
	public void mouseExited(MouseEvent e){}
	public void mouseEntered(MouseEvent e){}

	public void updateLocation(MouseEvent e){

		rect.setLocation((x + e.getX())-4, (y + e.getY())-4);
		point.setLocation(x + e.getX(), y + e.getY());

                checkPoint();

		quad.setCurve(start, control, end);
		repaint();
	}

	public void paintComponent(Graphics g){
                super.paintComponent(g);
		update(g);
	}

	public void update(Graphics g){

		Graphics2D g2 = (Graphics2D)g;
		Dimension dim = getSize();
		int w = dim.width;
                int h = dim.height; 
                 
          	if(firstTime){
		  bi = (BufferedImage)createImage(w, h);
		  big = bi.createGraphics();
		  start.setLocation(w/2-50, h/2);
		  end.setLocation(w/2+50, h/2);
		  control.setLocation((int)(start.x)+50, (int)(start.y)-50);
		  startpt.setLocation((int)((start.x)-4), (int)((start.y)-4));
                  endpt.setLocation((int)((end.x)-4), (int)((end.y)-4));
                  ctrl.setLocation((int)((control.x)-4), (int)((control.y)-4));
		  quad.setCurve(start, control, end);
        	  big.setColor(Color.black);
		  big.setStroke(new BasicStroke(5.0f));
                  big.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		  area = new Rectangle(dim);
		  firstTime = false;
		}

		// Clears the rectangle that was previously drawn.
		big.setColor(Color.white);
		big.clearRect(0, 0, area.width, area.height);

		// Draws and fills the newly positioned rectangle to the buffer.
		big.setPaint(Color.black);
		big.draw(quad);
		big.setPaint(Color.red);
		big.fill(startpt);
		big.setPaint(Color.magenta);
		big.fill(endpt);
		big.setPaint(Color.blue);
		big.fill(ctrl);

		// Draws the buffered image to the screen.
		g2.drawImage(bi, 0, 0, this);

	}
	/*
         * Checks if the rectangle is contained within the applet window.  If the rectangle
         * is not contained withing the applet window, it is redrawn so that it is adjacent
         * to the edge of the window and just inside the window.
	 */

	void checkPoint(){
		
		if (area == null) {
			return;
		}

		if((area.contains(rect)) && (area.contains(point))){
			return;
		}
		int new_x = rect.x;
		int new_y = rect.y;

		double new_px = point.x;
		double new_py = point.y;

		if((rect.x+rect.width)>area.getWidth()){
			new_x = (int)area.getWidth()-(rect.width-1);
		}
		if(point.x > area.getWidth()){
			new_px = (int)area.getWidth()-1;
		}
		if(rect.x < 0){  
			new_x = -1;
		}
		if(point.x < 0){
			new_px = -1;
		}
		if((rect.y+rect.width)>area.getHeight()){
			new_y = (int)area.getHeight()-(rect.height-1);
		}
		if(point.y > area.getHeight()){
			new_py = (int)area.getHeight()-1;
		}
		if(rect.y < 0){  
			new_y = -1;
		}
		if(point.y < 0){
                        new_py = -1;
                }
		rect.setLocation(new_x, new_y);
		point.setLocation(new_px, new_py);

	}
}
