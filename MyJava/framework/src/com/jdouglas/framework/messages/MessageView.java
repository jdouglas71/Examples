package com.jdouglas.framework.messages;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import org.w3c.dom.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.manager.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.ui.widgets.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.enums.data.*;
import com.jdouglas.framework.core.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;

/**
* MessageView. The view used to display messages.
*
* @author Jason Douglas 1/19/10
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class MessageView    
	extends FusionView
        implements IMessageView,TreeSelectionListener,MouseListener
{
    /** module name */
    private static final String MODULE_NAME                                                         = "MessageView.";

	/** the Tree */
	private JTree theTree;
	/** root node */
	private DefaultMutableTreeNode rootNode;
	/** Tree model */
	private DefaultTreeModel theModel;
	/** Settings Are Valid node */
	private DefaultMutableTreeNode validNode;
	/** resources */
	private FrameworkResources theResources;
	/** The manager */
	private IMessageManager theManager;

	/**
	* Default Constructor
	* 
	* @param manager IMessageManager
	*/
	protected MessageView(IMessageManager manager)
	{
		super();

		theResources = (FrameworkResources)FusionApplication.getResources(IFrameworkProperties.class);
		theManager = manager;

		init();
	}

	/**
    * Initialize the goo.
    */
	private void init()
	{
		String methodName = MODULE_NAME + "init()";

		setLayout( new BorderLayout() );

		initTree();

		JScrollPane scroller = new JScrollPane( theTree );
		scroller.setPreferredSize( new Dimension(100,60) );

		add( scroller, BorderLayout.CENTER );
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
			validNode = new DefaultMutableTreeNode( theManager.createMessage( theResources.getResourceString(VALID_SETTINGS_MSG), MessageType.INFO, null ) );

			theTree = new JTree( rootNode );
			theTree.addTreeSelectionListener( this );
			theTree.setRootVisible( false );
			theTree.setShowsRootHandles( false );
			theTree.addMouseListener( this );
			theModel = (DefaultTreeModel)theTree.getModel();

			theModel.insertNodeInto( validNode, rootNode, 0 );
			//YOu have to reset the root in the model to get the new child nodes to show up. Don't ask me why...
			theModel.setRoot( rootNode );
			expandAllRows();

			theTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
			theTree.setCellRenderer( new MessageTreeCellRenderer() );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	//*****************************************************************************************************************//
	// IMessageView impl
	// 
	/**
	* Add a message.
	* 
	* @param message IFusionMessage
	*/
	public void addMessage(IFusionMessage message)
	{
		String methodName = MODULE_NAME + "addMessage(IFusionMessage)";

		try
		{
            DefaultMutableTreeNode newNode = new DefaultMutableTreeNode( message );
			if( validNode.getParent() != null )
			{
				theModel.removeNodeFromParent( validNode );
			}
			theModel.insertNodeInto( newNode, rootNode, rootNode.getChildCount() );
			//YOu have to reset the root in the model to get the new child nodes to show up. Don't ask me why...
			theModel.setRoot( rootNode );
			expandAllRows();
			theTree.scrollPathToVisible( new TreePath(newNode) );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Remove a message.
	* 
	* @param message IFusionMessage
	*/
	public void removeMessage(IFusionMessage message)
	{
		String methodName = MODULE_NAME + "removeMessage(IFusionMessage)";

		try
		{
			DefaultMutableTreeNode node = null;
			Logger.log( methodName + " Removing the message: " + message.getDisplayName(), Logger.CONFIG );

			//JGD TODO: Drill down into all potential children branches.
			for(int i=0; i<rootNode.getChildCount(); i++)
			{
				DefaultMutableTreeNode child = (DefaultMutableTreeNode)rootNode.getChildAt( i );
				IFusionMessage m = (IFusionMessage)(child.getUserObject());
				if( message.equals(m) )
				{
					Logger.log( methodName + " Found the Message Node to remove!", Logger.CONFIG );
					node = child;
					break;
				}
			}

			if( node != null )
			{
				Logger.log( methodName + " Removing node from parent.", Logger.CONFIG );
				//node.removeFromParent(); THis doens't work.
				theModel.removeNodeFromParent( node );
				if( rootNode.getChildCount() == 0 )
				{
					Logger.log( methodName + " Inserting \"Settings are valid\" node..", Logger.CONFIG );
					theModel.insertNodeInto( validNode, rootNode, 0 );
					theModel.setRoot( rootNode );
				}     
				expandAllRows();
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Clear all messages.
	*/
	public void clearMessages()
	{
		String methodName = MODULE_NAME + "clearMessages()";

		try
		{
			if( rootNode.getChildCount() > 0 )
			{
				for(int i=rootNode.getChildCount()-1; i>=0; i--)
				{
					theModel.removeNodeFromParent( (MutableTreeNode)rootNode.getChildAt(i) );
				}
			}

			theModel.insertNodeInto( validNode, rootNode, 0 );
			//YOu have to reset the root in the model to get the new child nodes to show up. Don't ask me why...
			theModel.setRoot( rootNode );
			expandAllRows();
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

	/**
	* Returns true if the message view contains an error.
	* 
	* @return boolean
	*/
	public boolean hasErrors()
	{
		String methodName = MODULE_NAME + "hasErrors()";
		boolean retval = false;

		try
		{
			//JGD TODO: Drill down into all potential children branches.
			for(int i=0; i<rootNode.getChildCount(); i++)
			{
				DefaultMutableTreeNode child = (DefaultMutableTreeNode)rootNode.getChildAt( i );
				IFusionMessage m = (IFusionMessage)(child.getUserObject());
				if( m.getMessageType() == MessageType.ERROR )
				{
					retval = true;
					break;
				}
			}
		} 
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}


	// IMessageView impl ends

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

	//********************************************************************************************************************//
	// MouseListener impl
	// 

	/**
	* Invoked when the mouse button has been clicked (pressed
	* and released) on a component.
	* 
	* @param evt MouseEvent
	*/
	@SuppressWarnings("unchecked")
	public void mouseClicked(MouseEvent evt)
	{
		String methodName = MODULE_NAME + "mouseClicked(MouseEvent)";

		if( evt.getClickCount() >= 2 )
		{
			Logger.log( methodName + " Got double click", Logger.CONFIG );
			//Get the selected message, extract its source data and attempt to set the focus.
			TreePath selPath = theTree.getSelectionPath();
			if( selPath != null )
			{                  
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)(selPath.getLastPathComponent());
				if( node != null )
				{
					IFusionMessage message = (IFusionMessage)node.getUserObject();
					HashMap<String,Object> sourceData = (HashMap<String,Object>)message.getProperty(IFusionMessage.MESSAGE_SOURCE);

					Object source = sourceData.get(IFusionMessage.MESSAGE_SOURCE);
					if( source != null )
					{
						if( source instanceof JTable )
						{
							Logger.log( methodName + " Got JTable.", Logger.CONFIG );
							int row = ((Integer)sourceData.get("Row")).intValue();
							int col = ((Integer)sourceData.get("Col")).intValue();

							JTable table = (JTable)source;
							table.changeSelection(row,col, false, false );
						}
						else if( source instanceof JTextField )
						{
							Logger.log( methodName + " Got JTextField.", Logger.CONFIG );
							JTextField field = (JTextField)source;
							field.requestFocus();
							field.setSelectionStart( 0 );
							field.setSelectionEnd( field.getText().length() );
						}
						else if( source instanceof JComponent )
						{
							Logger.log( methodName + " Got JComponent.", Logger.CONFIG );
							((JComponent)source).requestFocus();
						}
						else
						{
							Logger.log( methodName + " Got " + source.getClass().getName(), Logger.CONFIG );
						}
					}
					else
					{
						Logger.log( methodName + " No message source.", Logger.CONFIG );
					}
				}
				else
				{
					Logger.log( methodName + " Couldn't get tree node.", Logger.CONFIG );
				}
			}
			else
			{
				Logger.log( methodName + " Selection path in tree was null.", Logger.CONFIG );
			}
		}
	}

	/**
	* Invoked when a mouse button has been pressed on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mousePressed(MouseEvent evt)
	{
	}

	/**
	* Invoked when a mouse button has been released on a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseReleased(MouseEvent evt)
	{
	}

	/**
	* Invoked when the mouse enters a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseEntered(MouseEvent evt)
	{
	}

	/**
	* Invoked when the mouse exits a component.
	* 
	* @param evt MouseEvent
	*/
	public void mouseExited(MouseEvent evt)
	{
	}

	// MouseListener impl ends

	/**
    * Expand all rows
    */
	private void expandAllRows()
	{
		String methodName = MODULE_NAME + "expandAllRows()";
		//Expand All the Rows
		for(int i=0; i<theTree.getRowCount(); i++)
		{
			theTree.expandRow( i );
		}
		theTree.revalidate();
	}
}


