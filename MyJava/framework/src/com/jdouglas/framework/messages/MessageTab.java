package com.jdouglas.framework.messages;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.ui.widgets.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.enums.data.*;

/**
* MessageTab. Skeleton impl for now using an infopanel. Soon to be a tree. 
*
* @author Jason Douglas 4/10/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class MessageTab    
	extends TabPage
        implements IFusionTab,TreeSelectionListener
{
    /** module name */
    private static final String MODULE_NAME                                                         = "MessageTab.";

    /** the info panel */
    private InfoPanel infoPanel = new InfoPanel();

	/** container panel */
	private JPanel thePanel = new JPanel();
	/** the Tree */
	private JTree theTree;
	/** root node */
	private DefaultMutableTreeNode rootNode;
	/** Tree model */
	private DefaultTreeModel theModel;


	/**
	* Default Ctor
	*/
	public MessageTab()
	{
		super( "Message", 'M', null, null );
		tabElementName = MODULE_NAME;

		init();
	}


	/**
    * Initialize the goo.
    */
	private void init()
	{
		String methodName = MODULE_NAME + "init()";

		thePanel.setLayout( new BorderLayout() );

		initTree();

		thePanel.add( new JScrollPane(theTree), BorderLayout.CENTER );

		tabComponent = thePanel;
	}

	/**
	* Initialize the JTree with the given project.
	*/
	private void initTree()
	{
		String methodName = MODULE_NAME + "initTree()";

		try
		{
			rootNode = new DefaultMutableTreeNode( "Messages" );

			theTree = new JTree( rootNode );
			theTree.setCellRenderer( new MessageTreeCellRenderer() );
			theTree.addTreeSelectionListener( this );
			theTree.setRootVisible( false );
			theModel = (DefaultTreeModel)theTree.getModel();

			theTree.getSelectionModel().setSelectionMode(TreeSelectionModel.CONTIGUOUS_TREE_SELECTION);
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    /**
    * Set the text of the infopanel
    *
    * @param text String
    */
    public void setInfoText(String text)
    {
		String methodName = MODULE_NAME + "setInfoText(String)";

		try
		{
			Logger.log( methodName + " adding message: " + text, Logger.DEBUG );

			//DefaultMutableTreeNode node = new DefaultMutableTreeNode( new MessageData(text,MessageType.INFO), false );

			//theModel.insertNodeInto( node, rootNode, rootNode.getChildCount() );

			//theTree.getSelectionModel().setSelectionPath( new TreePath(node.getPath()) );
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
    }

	/**
	* Set the selected node by string. 
	* 
	* @param name String
	*/
	public void setSelectedNode(String name)
	{
		String methodName = MODULE_NAME + "setSelectedNode(String)";
		DefaultMutableTreeNode selectionNode = null;
		DefaultMutableTreeNode node = null;

		try
		{
			for(int i=0; i<rootNode.getChildCount(); i++)
			{
				node = (DefaultMutableTreeNode)rootNode.getChildAt( i );
				if( node.getUserObject().toString().intern() == name.intern() )
				{
					selectionNode = node;
				}
				else
				{
					for(int j=0; j<node.getChildCount(); j++)
					{
						DefaultMutableTreeNode n = (DefaultMutableTreeNode)node.getChildAt( j );
						if( n.getUserObject().toString().intern() == name.intern() )
						{
							selectionNode = n;
							break;
						}
					}
				}

				if( selectionNode != null )
				{
					break;
				}
			}

			if( selectionNode != null )
			{
				theTree.getSelectionModel().setSelectionPath( new TreePath(selectionNode.getPath()) );
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	//************************************************************************************************//
	// IFusionTab impl 
	// 

    //************************************************************************************************//
    // IApplicationFrameListener impl
    //
    /**
    * Let the listeners know that the wait state has been changed to the given value.
    * 
    * @param waitState boolean The current value of the frame's waitState.
    */
    public void waitStateChanged(boolean waitState)
    {

    }
    // IApplicationFrameListener impl ends

    //*************************************************************************************************//
    // IValidator impl
    //
    /**
    * This call comes from a selection model. The params Map allows various information to be passed to the valiators. 
    * Returning false will cause the selection model from blocking the change of selection indices, so use the power wisely.
    * 
    * @param params Map<Object,Object> Constraints and other types of information necessary to validate.
    *
    * @return boolean True if the validation passed. 
    */
    public boolean validateContents(java.util.Map<Object,Object> params)
    {
        return true;
    }
    // IValidator impl ends

    //************************************************************************************************//
    // ChangeListener impl
    //
    /**
    * Invoked when the target of the listener has changed its state.
    *
    * @param e  a ChangeEvent object
    */
    public void stateChanged(ChangeEvent e)
    {
    }
    // ChangeListener impl 
    // IFusionTab impl ends

	//******************************************************************************************************************//
	// TreeSelectionListener impl
	//
	/** 
	* Called whenever the value of the selection changes.
	*
	* @param e the event that characterizes the change.
	*/
	public void valueChanged(TreeSelectionEvent e)
	{
		String methodName = MODULE_NAME + "valueChanged(TreeSelectionEvent)";

		try
		{
		}
		catch(Exception ex)
		{
			FusionUtils.logError( methodName, "Failed", ex );
		}
	}
	// TreeSelectionListener impl ends
}

