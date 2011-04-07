import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GridBagLab extends JFrame implements ActionListener 
{
    final static Color [] colors = { Color.cyan, Color.yellow, Color.green, 
                                     Color.pink, Color.white, Color.magenta };
    int maxButtons = colors.length;
    JButton showButton;
    GBPanel [] gbpanels;

    GridBagLab()
    {
        JPanel p = new JPanel();
        JLabel label = new JLabel("Configure desired parameters, then click SHOW.");
        label.setFont(new Font("SansSerif", Font.BOLD, 14));
        p.add(label);
        getContentPane().add(p, "North");

        Panel gridPanel = new Panel();
        maxButtons = colors.length;
        gridPanel.setLayout(new GridLayout(maxButtons, 1));
        gbpanels = new GBPanel[maxButtons];
        
        for (int i=0; i<maxButtons; i++)
        {   gbpanels[i] = new GBPanel(colors[i]);
            gridPanel.add(gbpanels[i]);
        }
        getContentPane().add(gridPanel, "Center");

        JPanel controlPanel = new JPanel();
        showButton = new JButton("SHOW");
        showButton.setFont(new Font("SansSerif", Font.PLAIN, 18));
        showButton.addActionListener(this);
        controlPanel.add(showButton);
        getContentPane().add(controlPanel, "South");
        
        addWindowListener(new WindowAdapter()
      	{	public void windowClosing(WindowEvent e) { System.exit(0); }  });
        }

    public void actionPerformed(ActionEvent ev)
    {
        if (ev.getSource() == showButton)
	{
            JFrame frame = new DisposableFrame();
            frame.setBounds(200, 100, 300, 300);
            GridBagLayout gbl = new GridBagLayout();
            JPanel pan = new JPanel();
       	    pan.setLayout(gbl);
            for (int k=0; k<maxButtons; k++)
            {	GridBagConstraints gbc = gbpanels[k].getConstraints();
            	if (gbc == null) continue;
               		
               	JButton b = new JButton("(" + gbc.gridx + "," + gbc.gridy + ")" +
                                  	"  " + gbc.gridwidth + "x" + gbc.gridheight);
            	b.setBackground(colors[k]);
            	gbl.setConstraints(b, gbc);
            	pan.add(b);
       	    }
            frame.getContentPane().add(pan, "Center");
            frame.show();
	}
    }
    
    public static void main(String [] args)
    {	JFrame f = new GridBagLab();
    	f.setSize(800,600);
    	f.setVisible(true);
    }
}


class ValChoice extends JComboBox
{
    int [] values;

    ValChoice(String [] labels, int [] values)
    {
    	this.values = values;
        setLightWeightPopupEnabled(false);
    	for (int k=0; k<labels.length; k++) addItem(labels[k]);
    }

    int getSelectedValue()
    {	return values[getSelectedIndex()];  }
}

class XYPanel extends JPanel
{
    XYPanel(Color bgc)
    {	setBackground(bgc);
    	setLayout(new GridLayout(2, 1)); 
    }
}


class GBPanel extends JPanel
{
    JCheckBox useCB;
    JComboBox xChoice, yChoice;
    ValChoice fillChoice, anchorChoice;
    JTextField xtf, ytf, wtf, htf, xwttf, ywttf;
    Color bgcolor;
    
    static String [] fillStrings = { "Both", "Horizontal", "Vertical", "None" };

    static int [] fillValues = 
    		{ GridBagConstraints.BOTH, GridBagConstraints.HORIZONTAL,
    	          GridBagConstraints.VERTICAL, GridBagConstraints.NONE };

    static String [] anchorStrings = 
       		{ "Center", "North", "NorthEast", "East", "SouthEast",  
    	          "South", "SouthWest", "West",  "NorthWest" };
		              
    static int [] anchorValues = 
    	{ GridBagConstraints.CENTER, GridBagConstraints.NORTH, 
    	  GridBagConstraints.NORTHEAST, GridBagConstraints.EAST, 
    	  GridBagConstraints.SOUTHEAST, GridBagConstraints.SOUTH,
          GridBagConstraints.SOUTHWEST, GridBagConstraints.WEST, 
          GridBagConstraints.NORTHWEST, };
          
    GBPanel(Color bgc)
    {
	bgcolor = bgc;
	setBackground(bgcolor);
	JPanel p = new XYPanel(bgcolor);
	p.add(useCB = new JCheckBox("Use"));
	useCB.setBackground(bgcolor);
	add(p);

	p = new XYPanel(bgcolor);
	p.add(new JLabel("X:"));
	p.add(new JLabel("Y:"));
	add(p);

        p = new XYPanel(bgcolor);
	xChoice = new JComboBox();
        xChoice.setLightWeightPopupEnabled(false);
	xChoice.addItem("Type value");
	xChoice.addItem("Relative");
	xChoice.addItem("Remainder");
	p.add(xChoice);
		
	yChoice = new JComboBox();
        yChoice.setLightWeightPopupEnabled(false);
	yChoice.addItem("Type value");
	yChoice.addItem("Relative");
	yChoice.addItem("Remainder");
	p.add(yChoice);
	add(p);

        p = new XYPanel(bgcolor);
	p.add((xtf = new JTextField("0", 2)));
	p.add((ytf = new JTextField("0", 2)));
        add(p);

        p = new XYPanel(bgcolor);
	p.add(new JLabel("Width:"));
	p.add(new JLabel("Height:"));
        add(p);

        p = new XYPanel(bgcolor);
	p.add(wtf = new JTextField("1", 2));
	p.add(htf = new JTextField("1", 2));
        add(p);

        p = new XYPanel(bgcolor);
        p.add(new JLabel("X wt:"));
        p.add(new JLabel("Y wt:"));
        add(p);

        p = new XYPanel(bgcolor);
        p.add(xwttf = new JTextField("100", 3));
        p.add(ywttf = new JTextField("100", 3));
        add(p);

        p = new XYPanel(bgcolor);
        p.add(new JLabel("Fill:"));
        p.add(new JLabel("Anchor:"));
        add(p);  

        p = new XYPanel(bgcolor);
	p.add(fillChoice = new ValChoice(fillStrings, fillValues));
	p.add(anchorChoice = new ValChoice(anchorStrings, anchorValues));
        add(p);
	}

	GridBagConstraints getConstraints()	     // Returns a GridBagConstraints  
	{ 					     // that reflects selections, or 
            if (!useCB.isSelected())  return null;   // null if "Use" checkbox is off	

	    GridBagConstraints gbc = new GridBagConstraints();

	    switch (xChoice.getSelectedIndex())
	    {
	    	case 0:	gbc.gridx = Integer.parseInt(xtf.getText());	// Typed
	    	        break;
	    	case 1:	gbc.gridx = GridBagConstraints.RELATIVE;	// Relative
	    	        break;
	    	case 2: gbc.gridx = GridBagConstraints.REMAINDER;	// Remainder
	    	        break;
	    }
       	    switch (yChoice.getSelectedIndex())
            {
               	    case 0: gbc.gridy = Integer.parseInt(ytf.getText());  // Typed
                       	    break;
            	    case 1: gbc.gridy = GridBagConstraints.RELATIVE;	// Relative
                       	    break;
            	    case 2: gbc.gridy = GridBagConstraints.REMAINDER;	// Remainder
                    	    break;
            }
	    gbc.gridwidth = Integer.parseInt(wtf.getText());
	    gbc.gridheight = Integer.parseInt(htf.getText());

	    gbc.weightx = Double.parseDouble(xwttf.getText());
            gbc.weighty = Double.parseDouble(ywttf.getText());

	    gbc.fill = fillChoice.getSelectedValue();
	    gbc.anchor = anchorChoice.getSelectedValue();

	    return gbc;
	}
}


class DisposableFrame extends JFrame
{
    DisposableFrame()
    {	
         addWindowListener(new WindowAdapter()
         {  public void windowClosing(WindowEvent e) { dispose(); }
         });
    }
}

