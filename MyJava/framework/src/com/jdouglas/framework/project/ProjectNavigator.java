package com.jdouglas.framework.project;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;     
import javax.swing.event.*;     
import javax.swing.tree.*;    
import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.listeners.*;
import com.jdouglas.framework.interfaces.view.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.core.events.*;


/**
* ProjectNavigator. This is decorated tree panel that displays the contents of a project and a allows the user to navigate
* said project.
*
* JGD TODO: 
*
* @author Jason Douglas 4/11/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class ProjectNavigator
    extends FusionNavigator
        implements IFusionNavigator,TreeSelectionListener
{
    /** module name */
    private static final String MODULE_NAME =                                                                   "ProjectNavigator.";

    /** the main panel */
    private JPanel thePanel = new JPanel();
    /** the project */
    private IProject theProject;
    /** the Tree */
    private JTree theTree;
    /** root node */
    private DefaultMutableTreeNode rootNode;
    /** Parent node */
    private DefaultMutableTreeNode parentNode;
    /** node placeholder. convienence */
    private DefaultMutableTreeNode node;

    /**
    * Ctor
    *
    * @param project IProject
    */
    protected ProjectNavigator(IProject project)
    {
        theProject = project;

        init();
    }

    /**
    * Initialize the goo.
    */
    private void init()
    {
        String methodName = MODULE_NAME + "init()";

        try
        {
            thePanel.setLayout( new BorderLayout() );

            initTree();

            thePanel.add( new JScrollPane(theTree), BorderLayout.CENTER );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

    /**
    * Initialize the JTree with the given project.
    */
    private void initTree()
    {
        String methodName = MODULE_NAME + "initTree()";

        try
        {
            rootNode = new DefaultMutableTreeNode( theProject.getProjectName() );
            Iterator<IProjectData> iter = theProject.getProjectData().iterator();
            while( iter.hasNext() ) 
            {
                IProjectData pData = iter.next();
                parentNode = new DefaultMutableTreeNode( pData );
                //JGD TODO: ONly going one level deep right now. Need to make recursive
                Iterator<IProjectData> childIter = pData.getChildData().iterator();
                while( childIter.hasNext() )
                {
                    IProjectData childData = iter.next();
                    node = new DefaultMutableTreeNode( childData, false );
                    parentNode.add( node );
                }
                rootNode.add( parentNode );
            }

            theTree = new JTree( rootNode );
            theTree.setCellRenderer( new ProjectDataTreeCellRenderer() );
            theTree.addTreeSelectionListener( this );

            theTree.getSelectionModel().setSelectionMode(TreeSelectionModel.CONTIGUOUS_TREE_SELECTION);
        }
        catch(Exception e)
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

    //******************************************************************************************************************//
    // IFusionNavigator impl
    //
    /**
    * Get the navigator component.
    *
    * @return JComponent The navigator component. 
    */
    public JComponent getNavigatorComponent()
    {
        return thePanel;
    }

    // IFusionNavigator impl ends

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

            NavigatorChangeEvent nce = new NavigatorChangeEvent(this,e);

            fireNavigatorSelectionChange( nce );
        }
        catch(Exception ex)
        {
            FusionUtils.logError( methodName, "Failed", ex );
        }
    }

    // TreeSelectionListener impl ends
}

/**
* Custom TreeCellRenderer for the ProjectNavigator
* 
* @author Jason Douglas 4/11/07
*/
class ProjectDataTreeCellRenderer
    extends DefaultTreeCellRenderer
{
    /** Module Name */
    private static final String MODULE_NAME = "ProjectDataTreeCellRenderer.";

    /**
    * Ctor
    */
    protected ProjectDataTreeCellRenderer()
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
            //Do stuff here.
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }
}
