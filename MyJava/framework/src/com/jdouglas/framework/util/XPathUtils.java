package com.jdouglas.framework.util;

import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.font.*;
import javax.swing.*;
import java.text.*;
import javax.swing.table.*;
import javax.xml.parsers.*;
import javax.xml.xpath.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;
import org.xml.sax.*;
import org.w3c.dom.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.math.*;
import com.jdouglas.framework.util.models.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* XPathUtils. Utilities class for my xpath utilities. Probably end up moving them back into FusionUtils once I've determined that they work.
* 
* @author Jason Douglas 10/23/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class XPathUtils
{
	/** Module name */
    private static final String MODULE_NAME	 																= "XPathUtils.";

    /** Me pointer */
    private static XPathUtils Me = null;

    /**
    * Only XPathUtils can create XPathUtils. 
    */
    private XPathUtils()
    {
    }
                                              
    /**
    * Get me one.
    *
    * @return XPathUtils
    */
    public static XPathUtils getXPathUtils()
    {
        if( XPathUtils.Me == null )
        {
            XPathUtils.Me = new XPathUtils();
            XPathUtils.Me.initXPathUtils();
        }
        return Me;
    }

    /**
    * Start me up.
    */
    private void initXPathUtils()
    {
    }

	//********************************************************************************************************************//
	// New XPath utils using JAXP
	// 
	/**
	* Find node(s) in given node using given xpath string using JAXP.
	* 
	* @param xPathCommand String
	* @param sourceNode Node
	* @param logIt boolean
	* 
	* @return NodeList Returns null if the find commmand failed. 
	*/
	public static NodeList findNodes(String xPathCommand, Node sourceNode, boolean logIt)
	{
		String methodName = MODULE_NAME + "findNodes(String,Node)";
		NodeList retval = null;

		try
		{
			if( logIt )
			{
				Logger.log( methodName + " xPathCommand: " + xPathCommand + " sourceNode: " + FusionUtils.getXMLString(sourceNode), Logger.DEBUG );
			}

			XPathFactory xpFactory = XPathFactory.newInstance();
			XPath xPath = xpFactory.newXPath();
			XPathExpression xpExpr = xPath.compile( xPathCommand );
			retval = (NodeList)xpExpr.evaluate( sourceNode, XPathConstants.NODESET );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "XPath Find failed", e );
			retval = null; 
		}

		return retval; 
	}

	/**
	* Find node(s) in given node using given xpath string using JAXP.
	* 
	* @param xPathCommand String
	* @param sourceNode Node
	* 
	* @return NodeList Returns null if the find commmand failed. 
	*/
	public static NodeList findNodes(String xPathCommand, Node sourceNode)
	{
		return findNodes( xPathCommand, sourceNode, false );
	}

	/**
	* Find single node in given node using given xpath string using JAXP.
	* 
	* @param xPathCommand String
	* @param sourceNode Node
	* @param logIt boolean
	* 
	* @return Node Returns null if the find commmand failed. 
	*/
	public static Node findSingleNode(String xPathCommand, Node sourceNode, boolean logIt)
	{
		String methodName = MODULE_NAME + "findSingleNode(String,Node)";
		Node retval = null;

		try
		{
			if( logIt )
			{
				Logger.log( methodName + " xPathCommand: " + xPathCommand + " sourceNode: " + FusionUtils.getXMLString(sourceNode), Logger.DEBUG );
			}

			XPathFactory xpFactory = XPathFactory.newInstance();
			XPath xPath = xpFactory.newXPath();
			XPathExpression xpExpr = xPath.compile( xPathCommand );
			retval = (Node)xpExpr.evaluate( sourceNode, XPathConstants.NODE );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "XPath Find failed", e );
			retval = null; 
		}

		return retval; 
	}

	/**
	* Find single node in given node using given xpath string using JAXP.
	* 
	* @param xPathCommand String
	* @param sourceNode Node
	* 
	* @return Node Returns null if the find commmand failed. 
	*/
	public static Node findSingleNode(String xPathCommand, Node sourceNode)
	{
		return findSingleNode( xPathCommand, sourceNode, false );
	}

	// New XPath utils using JAXP ends
}
