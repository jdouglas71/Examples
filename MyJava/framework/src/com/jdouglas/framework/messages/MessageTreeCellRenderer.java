package com.jdouglas.framework.messages;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.util.*;


/**
* Custom TreeCellRenderer for the Message Pane
* 
* @author Jason Douglas 1/19/10
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
class MessageTreeCellRenderer
    extends DefaultTreeCellRenderer
{
    /** Module Name */
    private static final String MODULE_NAME = "MessageTreeCellRenderer.";
	/** Label width */
	private static final int LABEL_WIDTH = 1400;

    /**
    * Constructor
	*/
    protected MessageTreeCellRenderer()
    {
        super();
    }

    /**
    * Get the component.
    *
    * @param tree JTree
    * @param value Object
    * @param selected boolean
    * @param expanded boolean
    * @param leaf boolean
    * @param row int
    * @param hasFocus boolean
    * 
    * @return Component The renderer
    */
    public Component getTreeCellRendererComponent( JTree tree, Object value,
                                                   boolean selected, boolean expanded, 
                                                   boolean leaf, int row, boolean hasFocus)
    {
        String methodName = MODULE_NAME + "getTreeCellRendererComponent(...)";

        Component retval = super.getTreeCellRendererComponent(tree,value,selected,expanded,leaf,row,hasFocus);
        
        try
        {
			if( retval instanceof JLabel )
			{
				JLabel label = (JLabel)retval;
                DefaultMutableTreeNode node = (DefaultMutableTreeNode)value;
                Object obj = node.getUserObject();

				if( obj instanceof iTData )
				{
					iTData data = (iTData)obj;

					ImageIcon icon = (ImageIcon)data.getProperty( iTData.ICON );
					if( icon != null )
					{
						label.setIcon( icon );
						setLeafIcon( icon );
					}
				}

				//Setting the size of the component to be uniform and large so the tree doesn't get centered when the splitter is expanded.
				Dimension d = label.getPreferredSize();
				Dimension treeD = tree.getSize();
				Icon icon = label.getIcon();

				if( d.width < treeD.width )
				{
					d.width = treeD.width;
					if( icon != null )
					{
						d.width -= icon.getIconWidth();
					}
					label.setSize( d );
					label.setPreferredSize( d );
				}
			}
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }
}
