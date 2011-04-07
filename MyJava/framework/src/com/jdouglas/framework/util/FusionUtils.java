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
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;
import org.xml.sax.*;
import org.w3c.dom.*;
import org.apache.xpath.*;
import org.apache.xpath.objects.*;
import org.apache.xml.utils.*;

import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.math.*;
import com.jdouglas.framework.util.models.*;
import com.jdouglas.framework.ui.widgets.*;

/**
* FusionUtils. A class to put assorted utility functions.
* 
* @author Jason Douglas 5/14/02
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class FusionUtils
{
	/** Module name */
    private static final String MODULE_NAME	 																= "FusionUtils.";
	/** Default resource bundle */
    private static final String DEFAULT_BUNDLE 																= "com.jdouglas.framework.core.FrameworkResources";

    /** Me pointer */
    private static FusionUtils Me = null;
    /** Bundle map */
    private Map<String,ResourceBundle> theBundles;
    /** Hash Key Seed */
    private static int hashKeySeed = 1000;
    /** The base resource class. Used for loading resources */
    private static Class imageBaseClass = com.jdouglas.framework.core.FusionApplication.class;
    /** the base resource component. Used for tracking image loading */
    private static Component imageBaseComponent = new JFrame();

    /**
    * Only FusionUtils can create FusionUtils. 
    */
    private FusionUtils()
    {
    }
                                              
    /**
    * Get me one.
    *
    * @return FusionUtils
    */
    public static FusionUtils getFusionUtils()
    {
        if( FusionUtils.Me == null )
        {
            FusionUtils.Me = new FusionUtils();
            FusionUtils.Me.initFusionUtils();
        }
        return Me;
    }

    /**
    * Start me up.
    */
    private void initFusionUtils()
    {
        theBundles = new HashMap<String,ResourceBundle>();
    }

    /**
    * Calculates x,y to center window of given dimension on the desktop
    * 
    * @param d Dimension object used (along with the size of the screen) to determine the center point location.
    *
    * @return Point 
    */
    public static Point getCenterPosition(Dimension d)
    {
        Point retval = new Point(0,0);

        try
        {
            Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
            int x = (screen.width/2) - (d.width/2);
            int y = (screen.height/2) - (d.height/2);
            retval = new Point(x,y);
        }
        catch( Exception e )
        {
            retval = new Point(0,0);
        }

        return retval;
    }

    /**
    * Look for the bundle in the hashMap first, load if necessary.
    *
    * @param name String containing the name of the ResourceBundle.
    * @param locale String containing the locale of the ResourceBundle we're attempting to load.
    *
    * @return ResourceBundle
    */
    private ResourceBundle findBundle(String name, Locale locale)
    {
        String methodName = MODULE_NAME + "findBundle(String,Locale)";
        ResourceBundle retval = null;
        try
        {
            if( name != null )
            {
                retval = theBundles.get( name );
                if( retval == null )
                {
                    //System.out.println( methodName + " locale: " + locale.toString() );
                    //System.out.println( methodName + " locale displayname: " + locale.getDisplayName() );
                    //System.out.println( methodName + " locale variant: " + locale.getDisplayVariant() );
					//Logger.log( methodName + " Loading bundle: " + name, Logger.DEBUG );
                    retval = ResourceBundle.getBundle( name, locale );
					//if( retval != null )
					//{
					//	Logger.log( methodName + " Successfully loaded bundle " + name, Logger.DEBUG );
					//	Logger.log( methodName + " " + retval.toString(), Logger.DEBUG );
					//}
                    theBundles.put( name, retval );
                }
            }
        }
        catch( Exception e )
        {
            logError( methodName, "Failed", e );
            retval = null;
        }
        return retval;
    }

    /**
    * Get the string associated with the given id from the given bundle name. If the string
    * is not found, the defaultValue param is returned (defaulted to null).
    *
    * @param id String contianing the id of the resource we're looking up.
    * @param defaultValue String contianing the value returned in the event the lookup fails.
    * @param bundle_name String containing the name of the ResourceBundle we are using for the lookup.
    * @param locale String specifying the locale of the bundle we're loading.
    *
    * @return String 
    */
    private String _getResourceString(String id, String defaultValue, String bundle_name, Locale locale)
    {
        String methodName = MODULE_NAME + "_getResourceString(String,String,String,Locale)";
        String retval = defaultValue;
        try
        {
            ResourceBundle bundle = findBundle( bundle_name, locale );
            retval = (String)bundle.getObject( id );
        }
        catch( Exception e )
        {
            //I don't log the stack trace because it's just clutter in the log and not important. 
            Logger.log( methodName + " Resource String lookup failed. Returning default value.", Logger.CONFIG );
            Logger.log( methodName + " id: " + id + " defaultValue: " + defaultValue + " bundle_name: " + bundle_name + " Locale: " + locale.toString(), Logger.CONFIG );
			//FusionUtils.logError( methodName, "failed", e );
            retval = defaultValue;
        }
        
        if( retval != null ) 
            return retval.trim();
        else
            return retval;
    }

    /**
    * Get the string associated with the given id from the given bundle name. If the string
    * is not found, the defaultValue param is returned (defaulted to null).
    *
    * @param id String contianing the id of the resource we're looking up.
    * @param defaultValue String contianing the value returned in the event the lookup fails.
    * @param bundle_name String containing the name of the ResourceBundle we are using for the lookup.
    * @param locale String specifying the locale of the bundle we're loading.
    *
    * @return String 
    */
    public static String getResourceString(String id, String defaultValue, String bundle_name, Locale locale)
    {
        return getFusionUtils()._getResourceString( id, 
                                                    defaultValue,
                                                    bundle_name,
                                                    locale 
                                                  );
    }

    /**
    * Get the string associated with the given id from the given bundle name. If the string
    * is not found, the defaultValue param is returned (defaulted to null). Locale is defaulted to the default.
    *
    * @param id String contianing the id of the resource we're looking up.
    * @param defaultValue String contianing the value returned in the event the lookup fails.
    * @param bundle_name String containing the name of the ResourceBundle we are using for the lookup.
    *
    * @return String 
    */
    public static String getResourceString(String id, String defaultValue, String bundle_name)
    {
        return getFusionUtils()._getResourceString( id, 
                                                    defaultValue,
                                                    bundle_name,
                                                    Locale.getDefault() 
                                                  );
    }

    /**
    * Get the string associated with the given id from the default resource bundle. If the string
    * is not found, the defaultValue param is returned (defaulted to null).
    *
    * @param id String contianing the id of the resource we're looking up.
    * @param defaultValue String contianing the value returned in the event the lookup fails.
    *
    * @return String 
    */
    public static String getResourceString(String id, String defaultValue)
    {
        return getFusionUtils()._getResourceString( id, 
                                                    defaultValue,
                                                    DEFAULT_BUNDLE,
                                                    Locale.getDefault() 
                                                  );
    }

    /**
    * Get the string associated with the given id from the given bundle name. If the string
    * is not found, null is returned.
    *
    * @param id String contianing the id of the resource we're looking up.
    *
    * @return String 
    */
    public static String getResourceString(String id)
    {
        return getFusionUtils()._getResourceString( id, 
                                                    null,
                                                    DEFAULT_BUNDLE,
                                                    Locale.getDefault() 
                                                  );
    }

    /**
    * Convienence method for calling help for the application.
    * 
    * @param cmdLine String
    */
    public static void callHelp(String cmdLine)
    {
        String methodName = MODULE_NAME + "callHelp(String)";
        try
        {
            Runtime.getRuntime().exec( cmdLine );
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }
    }


    /**
    * Takes a TableColumn and determines the preferred width for the entire column based on the contents
    * of the row cells. Lifted from Graphic Java's chapter on Tables.
    *
    * @param col The TableColumn object contianing the cells we're basing the size on.
    * @param table the JTable object that will contiain the given TableColumn. Used to get the renderer object.
    *
    * @return int 
    */
    public static int getPreferredWidthForColumn(TableColumn col, JTable table)
    {
        String methodName = MODULE_NAME + "getPreferredWidthForColumn(TableColumn,JTable)";
        int retval = 0;

        int headerWidth = getColumnHeaderWidth(col, table);
        int cellWidth = getWidestCellInColumn(col, table);

        retval = headerWidth > cellWidth ? headerWidth : cellWidth;

        //retval += 20; //JGD Fudge Factor

        //Logger.log( methodName + " retval: " + retval, Logger.INFO );

        return retval;
    }

    /**
    * Figures out the width of the column header for the given TableColumn.
    * Lifted from Graphic Java's chapter on Tables.
    *
    * @param col The TableColumn object contianing the header we're basing the size on.
    * @param table the JTable object that will contiain the given TableColumn. Used to get the renderer object.
    *
    * @return int
    */
    private static int getColumnHeaderWidth(TableColumn col, JTable table)
    {
        String methodName = MODULE_NAME + "getColumnHeaderWidth(TableColumn.JTable)";
        int retval = -1;

        //JGD THis seems to be returning null a lot. Could my friends at Graphic Java be lying to me???
        //JGD Yes, they were. The default value of TableColumn.headerRenderer is null. If it's null, it 
        //JGD uses the defaultHeaderRenderer which is just a JLabel (See TableColumn.java) 3/19/03
        TableCellRenderer renderer = col.getHeaderRenderer();

        if( renderer != null )
        {
            Component comp = renderer.getTableCellRendererComponent( table,
                                                                     col.getHeaderValue(),
                                                                     false, false, 0, 0 );
            retval = comp.getPreferredSize().width;
        }
        else //renderer is null, the default is a label, create our own label to figure it out
        {
            JLabel label = new JLabel((String)col.getHeaderValue(),SwingConstants.CENTER);
            retval = label.getPreferredSize().width;
        }

        //Logger.log( methodName + " retval: " + retval, Logger.INFO );
        return retval;
    }


    /**
    * Figures out the width of the widest cell in a TableColumn
    * Lifted from Graphic Java's chapter on Tables.
    *
    * @param col The TableColumn object contianing the cells we're basing the size on.
    * @param table the JTable object that will contiain the given TableColumn. Used to get the renderer object.
    *
    * @return int
    */
    private static int getWidestCellInColumn(TableColumn col, JTable table)
    {
        String methodName = MODULE_NAME + "getWidestCellInColumn(TableColumn, JTable)";
        int retval = -1;
        int modelIndex = col.getModelIndex();
        int width = 0;
        int maxWidth = 0;

        for(int i=0; i<table.getRowCount(); i++)
        {
            TableCellRenderer renderer = table.getCellRenderer(i,modelIndex);
            Component comp = renderer.getTableCellRendererComponent( table, 
                                                                     table.getValueAt(i,modelIndex),
                                                                     false,false,i,modelIndex );
            width = comp.getPreferredSize().width;
            maxWidth = width > maxWidth ? width : maxWidth;
        }
        //JGD Fudge it just a little...
        retval = maxWidth+5;

        //Logger.log( methodName + " retval: " + retval, Logger.INFO );

        return retval;
    }

    /**
    * Return a string containing the current date and time.
    * 
    * @param format int 
    * @return String 
    */
    public static String getCurrentDateTime(int format)
    {
        String methodName = MODULE_NAME + "getCurrentDateTime()";
        String retval = "";
        try
        {
            DateFormat defaultDate = DateFormat.getDateTimeInstance( format, format );
            retval = defaultDate.format( new Date() );
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Return a string containing the current date and time.
    * 
    * @return String 
    */
    public static String getCurrentDateTime()
    {
        return getCurrentDateTime( DateFormat.DEFAULT );
    }


    /**
    * Get the current Date.
    *
    * @return String 
    */
    public static String getCurrentDate()
    {
        String methodName = MODULE_NAME + "getCurrentDate()";
        String retval = "";
        try
        {
            DateFormat defaultDate = DateFormat.getDateInstance();
            retval = defaultDate.format( new Date() );
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Return a string containing the current time.
    *
    * @return String
    */
    public static String getCurrentTime()
    {
        String methodName = MODULE_NAME + "getCurrentTime()";
        String retval = "";
        try
        {
            DateFormat defaultTime = DateFormat.getTimeInstance( DateFormat.LONG );
            retval = defaultTime.format( new Date() );
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Generate a random password, used when a password validation fails to ensure that the user doesn't get saved with
    * some sort of invalid (and thus insecure) password. Also used to initialize passwords.
    *
    * @return String 
    */
    public static String randomPassword()
    {
        String methodName = MODULE_NAME + "randomPassword()";
        String retval = "";
        char[] pwd = new char[12];

        Random randomGuy = new Random();

        //We only want ASCII values 40-126
        for(int i=0; i<pwd.length; i++)
        {
            pwd[i] = (char)(randomGuy.nextInt(86)+40);
        }

        retval = new String( pwd );

        //Logger.log( methodName + " generated: " + retval, Logger.INFO );

        return retval;
    }

    /**
    * Convert a BitSet to a String of 1's and 0's representing the bits.
    * JGD NOTE: Just using the BitSet.toString() for now.
    * 
    * @param bitSet a BitSet to be converted to String.
    *
    * @return String 
    */
    public static String convertBitSetToString(BitSet bitSet)
    {
        String methodName = MODULE_NAME + "convertBitSetToString(BitSet)";
        String retval = "";

        try
        {
            retval = bitSet.toString();
            /*
            StringBuffer strBuf = new StringBuffer();
            for(int i=0; i<bitSet.size(); i++)
            {
                if( bitSet.get(i) == true )
                {
                    strBuf.append( "1" );
                }
                else
                {
                    strBuf.append( "0" );
                }
            }
            retval = strBuf.toString();
            */
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Convert a String to a BitSet. The Format is {x,y,z} where x,y,and z are the indicies of the set bits.
    * This relies on the BitSet.toString format, so if it changes, we could have trouble (but I don't think 
    * it will).
    * 
    * @param bitString a String representation of a bitset
    *
    * @return BitSet 
    */
    public static BitSet convertStringToBitSet(String bitString)
    {
        String methodName = MODULE_NAME + "convertStringToBitSet(String)";
        BitSet retval = new BitSet();

        Logger.log( methodName + " Before: " + bitString, Logger.FINE );

        try
        {
            StringTokenizer toker = new StringTokenizer( bitString, "{}" );
            while( toker.hasMoreElements() )
            {
                String bits = ((String)toker.nextElement()).trim();
                StringTokenizer toker2 = new StringTokenizer( bits, "," );
                while( toker2.hasMoreElements() )
                {
                    Integer index = new Integer( ((String)toker2.nextElement()).trim() );
                    retval.set( index.intValue() );
                }
            }
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        Logger.log( methodName + " After: " + retval.toString(), Logger.FINE );

        return retval;
    }

    /**
    * BitSet conversion test
    */
    public static void testBitSetConversion()
    {
        String methodName = MODULE_NAME + "testBitSetConversion()";
        BitSet tester = new BitSet(8);

        for(int i=0; i<16; i++)
        {
            if( ((i%2) == 0) )
            {
                tester.set(i);
            }
        }

        Logger.log( methodName + " Starting: " + tester.toString(), Logger.FINE );
        String testStr = convertBitSetToString( tester );
        Logger.log( methodName + " Converted to String: " + testStr, Logger.FINE );
        Logger.log( methodName + " Converted from String: "+  convertStringToBitSet(testStr).toString(), Logger.FINE );
    }


    /**
    * Extract a HashMap of key\Value pairs from an XML NodeList. Used by iTData impl's everywhere.
    *
    * @param propList a NodeList of property elements.
    * @param xmlElementType String containing the element type contained in the nodeList.
    * @param xmlKeyAttribute String containing the name of the attribute for the key.
    * @param xmlValueAttribute String containing the name of the attribute for the value.
    *
    * @return HashMap<Object,Object> 
    */
    public static HashMap<Object,Object> extractMapFromNodeList(NodeList propList, String xmlElementType, String xmlKeyAttribute, String xmlValueAttribute)
    {
        String methodName = MODULE_NAME + "extractMapFromNodeList(NodeList,String,String,String)";
        HashMap<Object,Object> retval = new HashMap<Object,Object>();

        //Logger.log( methodName + " " + xmlElementType + "," + xmlKeyAttribute + "," + xmlValueAttribute, Logger.CONFIG );

        try
        {
            String typeStr = "";
            String keyStr = "";
            String valStr = "";
            String dummyStr = new String("");
            Integer dummyInt = new Integer(71);
            Boolean dummyBool = new Boolean("true");
            BitSet dummyBitSet = new BitSet();
            Date dummyDate = new Date();
            Element propElem = null;

            for(int i=0; i<propList.getLength(); i++)
            {
                propElem = (Element)propList.item(i);
                typeStr = propElem.getAttribute( xmlElementType );
                keyStr = propElem.getAttribute( xmlKeyAttribute );
                valStr = propElem.getAttribute( xmlValueAttribute );
                //Logger.log( methodName + " type: " + typeStr + " key: " + keyStr + " val: " + valStr, Logger.DEBUG );
                
                //If you ain't one of these, you're out!!!
                if( typeStr.intern() == dummyStr.getClass().getName().intern() )
                {
                    String strVal = valStr;
                    retval.put( keyStr, strVal );
                }
                else if( typeStr.intern() == dummyInt.getClass().getName().intern() )
                {
                    Integer intVal = new Integer(valStr);
                    retval.put( keyStr, intVal );
                }
                else if( typeStr.intern() ==  dummyBool.getClass().getName().intern() )
                {
                    Boolean boolVal = new Boolean( valStr );
                    retval.put( keyStr, boolVal );
                }
                else if( typeStr.intern() == dummyBitSet.getClass().getName().intern() )
                {
                    BitSet bitSetVal = FusionUtils.convertStringToBitSet( valStr );
                    retval.put( keyStr, bitSetVal );
                }
                else if( typeStr.intern() == dummyDate.getClass().getName().intern() )
                {
                    if( valStr.trim().equals("") == false )
                    {
                        Long tmpVal = new Long( valStr );
                        Date dateVal = new Date( tmpVal.longValue() );
                        retval.put( keyStr, dateVal );
                    }
                    else
                    {
                        retval.put( keyStr, valStr );
                    }
                }
                else
                {
                    //Default to String 
                    retval.put( keyStr, valStr );
                    Logger.log( methodName + " Problem adding the value, \"" + valStr + "\" for key \"" + keyStr + "\". It's type: " + typeStr + " was unknown. Defaulting to String.", Logger.SEVERE );
                }
            }
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

	/**
	* Error Logger to specified log file. 
	*
	* @param location String containing the class and methodName where the error occurred.
	* @param message String containing a message related to the error.
	* @param e the Exception object.
	* @param logFilename String Target log file. 
	*/
	public static void logError(String location, String message, Throwable e, String logFilename)
	{
		Logger.log( location + " " + message + " " + e, Logger.SEVERE, logFilename );
		if( e != null )
		{
			Logger.logStackTrace( e, logFilename );
		}
	}

    /**
    * Error Logger.
    *
    * @param location String containing the class and methodName where the error occurred.
    * @param message String containing a message related to the error.
    * @param e the Exception object.
    */
    public static void logError(String location, String message, Throwable e)
    {
        Logger.log( location + " " + message + " " + e, Logger.SEVERE );
        if( e != null )
        {
            Logger.logStackTrace( e );
        }
    }

    /**
    * Generates unique hash keys. Guarenteed to be unique during the application run. 
    * DO NOT STORE THESE VALUES! They will not be valid across sessions. 
    *
    * @return String 
    */
    public static String generateHashKey()
    {
        String methodName = MODULE_NAME + "_generateHashKey()";

        String retval = "" + hashKeySeed++;

        //Logger.log( methodName + " hashKey = " + retval, Logger.DEBUG );

        return retval;
    }

    /**
    * String massager method. Takes a string and a map of masks and values and replaces them in the 
    * original String. 
    * 
    * @param originalStr String Original String
    * @param replacements Map<String,String> Map containing the masks (keys) and replacement values (values).
    *  
    * @return String 
    */
    public static String massageString(String originalStr, Map<String,String> replacements)
    {
        String methodName = MODULE_NAME + "massageString(String, Map<String,String>)";
        String retval = originalStr;
        try
        {   
            Iterator iter = replacements.entrySet().iterator();
            while( iter.hasNext() )
            {
                Map.Entry entry = (Map.Entry)iter.next();
                //retval = retval.replaceAll( entry.getKey().toString(), entry.getValue().toString() );
                retval = replaceAll( retval, entry.getKey().toString(), entry.getValue().toString() );
            }
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Extract the extension from a file name.
    * 
    * @param file File The file object of interest.
    *
    * @return String The extension of the file.
    */
    public static String getExtension(File file)
    {
        String retval = getExtension( file.getPath() );
        return retval;
    }

    /**
    * Extract the extension from a file name.
    * 
    * @param fileName String The filename of interest.
    *
    * @return String The extension of the file.
    */
    public static String getExtension(String fileName)
    {
        String retval = null;

        int i = fileName.lastIndexOf('.');
        if( (i > 0) && (i < (fileName.length() - 1)) )
        {
            retval = fileName.substring(i+1).toLowerCase();
        }
        return retval;
    }

    /**
    * Replace all instances of the given mask with the replacement string. 
    * 
    * @param rawData String The raw, unchanged string. 
    * @param mask String The string to be replaced in the given String.
    * @param replacement String The string used to replace all instances of the mask in the rawData String.
    * 
    * @return String The updated string. 
    */
    public static String replaceAll(String rawData, String mask, String replacement)
    {
        String methodName = MODULE_NAME + "replaceAll(String,String,String)";
        String retval = "";

        //Logger.log( methodName + "rawData: " + rawData + " mask: " + mask + " replacement: " + replacement, Logger.DEBUG );

        try
        {
            int startingIndex = 0;
            int index = 0;
            StringBuffer buf = new StringBuffer();

            //Iterate thru and find all the mask instances and replace them. 
            while( (index = rawData.indexOf(mask,startingIndex)) >= 0 )
            {
                if( (index - startingIndex) > 0 )
                {
                    buf.append( rawData.substring(startingIndex,index) );
                }
                buf.append( replacement );

                startingIndex = index + mask.length();
            }

            //Tack on whatever's left. 
            if( startingIndex < rawData.length() )
            {
                buf.append( rawData.substring(startingIndex) );
            }

            retval = buf.toString();

            //Logger.log( methodName + " retval: " + retval, Logger.DEBUG );
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }
        
        return retval;
    }

    /**
    * Execute the given command via the Runtime class. 
    *
    * @param cmdStr String The command to execute
    * @param tellUser boolean If true, if the command fails, we will display the error message to the user.
    * 
    * @return boolean <code>True</code> if the command succeeded.
    */
    public static boolean executeCommand(String cmdStr, boolean tellUser)
    {
        String methodName = MODULE_NAME + "executeCommand(String,boolean)";
        Process retProcess = null;
        String inLine = "";
        BufferedReader errReader = null;
        StringBuffer buf = new StringBuffer();
        boolean retval = false;

        try
        {
            retProcess = Runtime.getRuntime().exec( cmdStr );
            errReader = new BufferedReader( new InputStreamReader(retProcess.getErrorStream()) );
            while( (inLine = errReader.readLine()) != null )
            {
                buf.append( inLine );
                buf.append( " " );
            }

            int exitVal = retProcess.waitFor();
            Logger.log( methodName + " exitVal: " + exitVal );
            if( exitVal != 0 )
            {
                Logger.log( methodName + " errMsg: " + buf.toString() );
                if( tellUser == true )
                {
                    JOptionPane.showMessageDialog( null,
                                                   buf.toString(),
                                                   "Error executing command",
                                                   JOptionPane.ERROR_MESSAGE );
                }
            }
            else
            {
                retval = true;
            }
        }
        catch(Exception e)
        {
            logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Execute the given command via the Runtime class, informing the user upon failure.
    * 
    * @param cmdStr String The command to execute.
    * 
    * @return boolean True if command succeeds.
    */
    public static boolean executeCommand(String cmdStr)
    {
        return executeCommand( cmdStr, true );
    }

    /**
    * Set the class from which images are loaded. Default is com.jdouglas.FCAdmin.FCAdmin.class.
    *
    * @param baseClass Class
    */
    public static void setResourceBaseClass(Class baseClass)
    {
        imageBaseClass = baseClass;
    }

    /**
    * Set the Component used to track resource loading. Default is FusionApplication.getApplicationFrame().getFrame().
    *
    * @param comp Component
    */
    public static void setResourceBaseComponent(Component comp)
    {
        imageBaseComponent = comp;
    }

    /**
    * Load an Image by name. Assumes the image is a resource of the application class.
    *
    * @param imageName String
	* @param baseClass Class
    *
    * @return Image
    */
    public static Image loadImage(String imageName, Class baseClass)
    {
        String methodName = MODULE_NAME + "loadImage(String,Class)";
        Image retval = null;

        try
        {
            URL url = baseClass.getResource( imageName );
            
            if( url != null )
            {
                retval = Toolkit.getDefaultToolkit().getImage( url );
                MediaTracker tracker = new MediaTracker( imageBaseComponent );
                tracker.addImage( retval, 0 );
                tracker.waitForAll();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

	/**
	* Load an Image by name. Assumes the image is a resource of the application class.
	*
	* @param imageName String
	*
	* @return Image
	*/
	public static Image loadImage(String imageName)
	{
		return FusionUtils.loadImage( imageName, imageBaseClass );
	}

    /**
    * Load an image from a file. Uses a MediaTracker to ensure it doesn't return until the image is completely
    * loaded. 
    *
    * @param imageFileName String
    *
    * @return Image
    */
    public static Image loadImageFromFile(String imageFileName)
    {
        String methodName = MODULE_NAME + "loadImageFromFile(String)";
        Image retval = null;

        try
        {
            //First test to see if the image actually exists
            File imageFile = new File( imageFileName );
            if( imageFile.exists() ) 
            {
                retval = Toolkit.getDefaultToolkit().getImage( imageFileName );
                MediaTracker tracker = new MediaTracker( imageBaseComponent );
                tracker.addImage( retval, 0 );
                tracker.waitForAll();
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Loading image from file failed.", e );
            retval = null;
        }

        return retval;
    }

    /**
    * Load an Icon by name. 
    *
    * @param iconName String 
	* @param baseClass Class 
    *
    * @return ImageIcon 
    */
    public static ImageIcon loadIcon(String iconName, Class baseClass)
    {
        String methodName = MODULE_NAME + "loadIcon(String,Class)";
        ImageIcon retval = null;

        Logger.log( methodName + " loading icon: " + iconName );

        try
        {
            Image img = loadImage( iconName, baseClass );
            if( img != null )
            {
                retval = new ImageIcon( img );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
        return retval;
    }

	/**
	* Load an Icon by name. 
	*
	* @param iconName String 
	*
	* @return ImageIcon 
	*/
	public static ImageIcon loadIcon(String iconName)
	{
		return loadIcon(iconName,imageBaseClass);
	}

    /**
    * Extract the XML String from the given Node object.
    *
    * @param node Node
    * @param trimHeader boolean If true, trim the XML header from the generated XML String 
    *
    * @return String 
    */ 
    public static String getXMLString(Node node, boolean trimHeader)
    {
        String methodName = MODULE_NAME + "getXMLString(Node,boolean)";
        String retval = "";

        try
        {
            TransformerFactory tf = TransformerFactory.newInstance();
            Transformer transformer = tf.newTransformer();
			transformer.setOutputProperty( OutputKeys.INDENT, "yes" );
            DOMSource source = new DOMSource( node );
            StringWriter strWriter = new StringWriter();
            StreamResult strResult = new StreamResult( strWriter );
            transformer.transform( source, strResult );

            retval = strWriter.toString();
            if( trimHeader )
            {
                int index = retval.indexOf( "?>" );
                if( index > 0 ) 
                {
                    retval = retval.substring(index+2).trim();
                }
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Extract the XML string form the given Node object, automatically trimming the xml header.
    * 
    * @param node Node
    *
    * @return String 
    */ 
    public static String getXMLString(Node node)
    {
        return getXMLString( node, true );
    }

	/**
    * Load an XML file
	* 
	* @param file File
	* 
	* @return Document
    */
	public static final Document loadXMLFile(File file)
	{
		String methodName = MODULE_NAME + "loadXMLFile(File)";
		Document retval = null;

		try
		{
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			factory.setIgnoringComments(true);
			factory.setCoalescing(false);
			factory.setNamespaceAware(true);
			factory.setValidating(false);

			DocumentBuilder parser = factory.newDocumentBuilder();
			retval = parser.parse( file );
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    /**
    * Copy the source file to the destination file. This is just the brute force method. It's up to the callers to 
    * do whatever checks they want to do beforehand (e.g. dest file already exists).
    *
    * @param srcFile File
    * @param destFile File
    * 
    * @return boolean True if copy succeeded. 
    */
    public static boolean copyFile(File srcFile, File destFile)
    {
        String methodName = MODULE_NAME + "copyFile(File,File)";
        boolean retval = true;
        FileInputStream srcStream = null;
        FileOutputStream destStream = null;

        try
        {
            Logger.log( methodName + " Copying " + srcFile.getPath() + " to " + destFile.getPath(), Logger.DEBUG );

            if( destFile.exists() == false )
            {
                Logger.log( methodName + " Creating new file.", Logger.CONFIG );
                destFile.createNewFile();
            }

            srcStream = new FileInputStream( srcFile );
            destStream = new FileOutputStream( destFile );
            byte[] buf = new byte[4096];
            int bytesRead;

            while( (bytesRead = srcStream.read(buf)) != -1)
            {
                destStream.write( buf, 0, bytesRead );
            }

            destStream.close();
            srcStream.close();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Copy Failed", e );
            retval = false;
        }
        finally
        {
            //Just in case 
            if( srcStream != null ) try { srcStream.close(); } catch(Exception e) { ; }
            if( destStream != null ) try { destStream.close(); } catch(Exception e) { ; }
        }

        return retval;
    }

    /**
    * Execute given xPathCommand on given source node and return the result as an XObject.
    *
    * @param xPathCommand String
    * @param sourceNode Node
	* @param logIt boolean
    *
    * @return XObject
    */ 
    public static XObject executeXPathCommand(String xPathCommand, Node sourceNode, boolean logIt)
    {
        String methodName = MODULE_NAME + "executeXPathCommand(String,Node)";
        XObject retval = null;

        try
        {
			//JGD TODO: Revisit XPath impl. This has the limitation that it always selects from the parent document of 
			//JGD TODO: the given node. It would be nice to be able to search only on the given node.
			if( logIt )
			{
				Logger.log( methodName + " xPathCommand: " + xPathCommand, Logger.DEBUG );
				Logger.log( methodName + " sourceNode XML: " + FusionUtils.getXMLString(sourceNode,true), Logger.DEBUG );
			}

            PrefixResolver prefixResolver = new PrefixResolverDefault( sourceNode );
            XPathContext xpContext = new XPathContext();
            XPath xpath = new XPath( xPathCommand, null, prefixResolver, XPath.SELECT );

            retval = xpath.execute( xpContext, sourceNode, prefixResolver );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "XPath Command failed.", e );
        }

        return retval; 
    }

	/**
	* Execute given xPathCommand on given source node and return the result as an XObject.
	*
	* @param xPathCommand String
	* @param sourceNode Node
	*
	* @return XObject
	*/ 
	public static XObject executeXPathCommand(String xPathCommand, Node sourceNode)
	{
		return executeXPathCommand( xPathCommand, sourceNode, false );
	}


    /**
    * Find node(s) in given node using given xpath string.
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
            XObject result = executeXPathCommand( xPathCommand, sourceNode, logIt );
            if( result != null )
            {
                retval = result.nodelist();
				if( retval.getLength() > 0 )
				{
					//Logger.log( methodName + " Found Node: " + FusionUtils.getXMLString(retval.item(0)), Logger.CONFIG );
				}
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "XPath Find failed", e );
            retval = null; 
        }

        return retval; 
    }

	/**
	* Find node(s) in given node using given xpath string.
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
	* Find node(s) in given node using given xpath string.
	* 
	* @param xPathCommand String
	* @param sourceXML String 
	* @param logIt boolean
	* 
	* @return NodeList Returns null if the find commmand failed. 
	*/
	public static NodeList findNodes(String xPathCommand, String sourceXML, boolean logIt)
	{
		String methodName = MODULE_NAME + "findNodes(String,String)";
		NodeList retval = null;

		try
		{
			Logger.log( methodName + " xPathCommand: " + xPathCommand + " sourceNode: " + sourceXML, Logger.CONFIG );

			XObject result = executeXPathCommand( xPathCommand, FusionUtils.getXMLDocument(sourceXML), logIt );
			if( result != null )
			{
				retval = result.nodelist();
				Logger.log( methodName + " Found " + retval.getLength() + " nodes.", Logger.CONFIG );
				if( retval.getLength() > 0 )
				{
					Logger.log( methodName + " Found Node: " + FusionUtils.getXMLString(retval.item(0)), Logger.CONFIG );
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "XPath Find failed", e );
			retval = null; 
		}

		return retval; 
	}

	/**
	* Find node(s) in given node using given xpath string.
	* 
	* @param xPathCommand String
	* @param sourceXML String 
	* 
	* @return NodeList Returns null if the find commmand failed. 
	*/
	public static NodeList findNodes(String xPathCommand, String sourceXML)
	{
		return findNodes( xPathCommand, sourceXML, false );
	}


	/**
	* Find single node in given node using given xpath string.
	* 
	* @param xPathCommand String
	* @param sourceNode Node
	* 
	* @return Node Returns null if the find commmand failed. 
	*/
	public static Node findSingleNode(String xPathCommand, Node sourceNode)
	{
		String methodName = MODULE_NAME + "findSingleNode(String,Node)";
		Node retval = null;

		try
		{
			XObject result = executeXPathCommand( xPathCommand, sourceNode );
			if( result != null )
			{
				NodeList nodeList = result.nodelist();
				if( nodeList.getLength() == 1 )
				{
					retval = nodeList.item(0);
				}
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "XPath Find failed", e );
			retval = null; 
		}

		return retval; 
	}

    /** 
    * Get the Text value of the given Node
    *
    * @param node Node
    * 
    * @return String
    */
    public static String getNodeValue(Node node)
    {
        String methodName = MODULE_NAME + "getNodeValue(Node)";
        String retval = "";

        try
        {
            if( node.hasChildNodes() )
            {
                NodeList nodes = node.getChildNodes();
                for(int i=0; i<nodes.getLength(); i++)
                {
                    if( nodes.item(i).getNodeType() == Node.TEXT_NODE )
                    {
                        retval = nodes.item(i).getNodeValue();
                        break;
                    }
                }
            }
        }
        catch(Exception e)
        {
			Logger.log( methodName + " EXCEPTION!!! node: " + FusionUtils.getXMLString(node), Logger.DEBUG );
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

	/** 
	* Set the Text value of the given Node
	*
	* @param val String
	* @param node Node
	*/
	public static void setNodeValue(String val, Node node)
	{
		String methodName = MODULE_NAME + "setNodeValue(String,Node)";

		try
		{
			//Logger.log( methodName + " val: " + val + " node: " + FusionUtils.getXMLString(node), Logger.DEBUG );
			if( node.hasChildNodes() )
			{
				NodeList nodes = node.getChildNodes();
				for(int i=0; i<nodes.getLength(); i++)
				{
					if( nodes.item(i).getNodeType() == Node.TEXT_NODE )
					{
						nodes.item(i).setNodeValue(val);
						//Logger.log( methodName + " Found text node, setting value", Logger.DEBUG );
						return;
					}
				}
			}
			//Logger.log( methodName + " Didn't find text node, creating text node.", Logger.DEBUG );
			//If we got here, there is no text node. Create it.
			node.appendChild( node.getOwnerDocument().createTextNode(val) );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}
	}

    /**
    * Execute the count function for XPath. For whatever reason, I've found that this call fails on subnodes of an XML 
    * document and I need to create a new document from the XML of the given node in order to get results.
    *
    * @param selString String
    * @param node Node
    *
    * @return int The result of the call to count()
    */
    public static int executeXPathCount(String selString, Node node)
    {
        String methodName = MODULE_NAME + "executeXPathCount(String,Node)";
        int retval = -1;

        try
        {
			Document doc = FusionUtils.getXMLDocument( getXMLString(node) );
            XObject xObj = executeXPathCommand( "count("+selString+")", doc );

            retval = Integer.parseInt( xObj.toString() );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

	/**
	* Execute the count function for XPath. For whatever reason, I've found that this call fails on subnodes of an XML 
	* document and I need to create a new document from the XML of the given node in order to get results.
	*
	* @param selString String
	* @param xmlString String
	*
	* @return int The result of the call to count()
	*/
	public static int executeXPathCount(String selString, String xmlString)
	{
		String methodName = MODULE_NAME + "executeXPathCount(String,String)";
		int retval = -1;

		try
		{
			Logger.log( methodName + " xmlStr: " + xmlString, Logger.CONFIG );
			Document doc = FusionUtils.getXMLDocument( xmlString );
			XObject xObj = executeXPathCommand( "count("+selString+")", doc );

			retval = Integer.parseInt( xObj.toString() );

			Logger.log( methodName + " FOund : " + retval, Logger.CONFIG );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
    * Create XML Document from given xml string.
	* 
	* @param xmlString String
	* 
	* @return Document 
    */
	public static Document getXMLDocument(String xmlString)
	{
		String methodName = MODULE_NAME + "getXMLDocument(String)";
		Document retval = null;

		try
		{
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			factory.setIgnoringComments(true);
			factory.setCoalescing(false);
			factory.setNamespaceAware(true);
			factory.setValidating(false);

			DocumentBuilder parser = factory.newDocumentBuilder();
			StringReader xmlReader = new StringReader( xmlString );
			InputSource xmlSource = new InputSource( xmlReader );
			retval = parser.parse( xmlSource );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    /** 
    * Stomp trailing copy of given string. Used when building delimeted lists and you need to stomp the last delimiter.
    *
    * @param buf StringBuffer
    * @param delim String
    */
    public static void stompTrailingDelim(StringBuffer buf, String delim)
    {
        String methodName = MODULE_NAME + "stompTrailingDelim(StringBuffer, String)";

        try
        {
            //Logger.log( methodName + " Before: " + buf.toString(), Logger.DEBUG );
            int loc = buf.lastIndexOf( delim );
            if( (loc < buf.length()) && (loc >= 0) )
            {
                buf.deleteCharAt( loc );
            }
           // Logger.log( methodName + " After: " + buf.toString(), Logger.DEBUG );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }
    }

	/**
    * Create and return a DecimalFormat object with the given precision.
	* 
	* @param precision int
	* 
	* @return DecimalFormat
    */
	public static DecimalFormat getDecimalFormat(int precision)
	{
		String methodName = MODULE_NAME + "getDecimalFormat(int)";
		DecimalFormat retval = new DecimalFormat("");

		try
		{
			StringBuffer buf = new StringBuffer( "0" );
			if( precision > 0 )
			{
				buf.append(".");
			}

			for(int i=0; i<precision; i++)
			{
				buf.append("0");
			}

			retval = new DecimalFormat( buf.toString() );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
    * Returns true if the given string can be parsed into a Double. Useful for situations where catching a NumberFormatException is awkward.
	* JGD NOTE: Lifted from the documentation for the JDK 1.6.02 version of Double.valueOf(). Modified to be generic. Doubt that it's internationalized,
	* JGD NOTE: but if we stick to our policy of only storing string representations of Doubles in the English locale format, we should be good.
	* 
	* @param val String
	* 
	* @return boolean
    */
	public static boolean isDouble(String val)
	{
		String methodName = MODULE_NAME + "isDouble(String)";
		boolean retval = false;

		try
		{
			//JGD NOTE: Lifted from the java source 1.6.02 for Double.valueOf()
			final String Digits	= "(\\p{Digit}+)";
			final String HexDigits  = "(\\p{XDigit}+)";
			// an exponent is 'e' or 'E' followed by an optionally 
			// signed decimal integer.
			final String Exp	= "[eE][+-]?"+Digits;
			final String fpRegex	=
				    ("[\\x00-\\x20]*"+	// Optional leading &quot;whitespace&quot;
				     "[+-]?(" +	// Optional sign character
				     "NaN|" +		// "NaN" string
				     "Infinity|" +	// "Infinity" string
			
				     // A decimal floating-point string representing a finite positive
				     // number without a leading sign has at most five basic pieces:
				     // Digits . Digits ExponentPart FloatTypeSuffix
				     // 
				     // Since this method allows integer-only strings as input
				     // in addition to strings of floating-point literals, the
				     // two sub-patterns below are simplifications of the grammar
				     // productions from the Java Language Specification, 2nd 
				     // edition, section 3.10.2.
			
				     // Digits ._opt Digits_opt ExponentPart_opt FloatTypeSuffix_opt
				     "((("+Digits+"(\\.)?("+Digits+"?)("+Exp+")?)|"+
			
				     // . Digits ExponentPart_opt FloatTypeSuffix_opt
				     "(\\.("+Digits+")("+Exp+")?)|"+
			
			         // Hexadecimal strings
			         "((" +
			         // 0[xX] HexDigits ._opt BinaryExponent FloatTypeSuffix_opt
			         "(0[xX]" + HexDigits + "(\\.)?)|" +
			
			         // 0[xX] HexDigits_opt . HexDigits BinaryExponent FloatTypeSuffix_opt
			         "(0[xX]" + HexDigits + "?(\\.)" + HexDigits + ")" +
			
			         ")[pP][+-]?" + Digits + "))" +
				     "[fFdD]?))" +
				     "[\\x00-\\x20]*");// Optional trailing &quot;whitespace&quot;
				    
			if( Pattern.matches(fpRegex, val) )
			{
				retval = true;
			}
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/** 
	* Get a Hexadecimal version of your string! 
	* 
	* @param str String 
	* 
	* @return String
	*/
	public static String strToHex(String str)
    {
		String methodName = MODULE_NAME + "strToHex(String)";
		StringBuffer buf = new StringBuffer();

		for(int i=0; i<str.length(); i++)
        {
			int cursor = 0;
			int intVal = str.charAt(i);
			String binChar = new String(Integer.toBinaryString(str.charAt(i)));
			for(int j=0; j<binChar.length(); j++)
            {
				if(binChar.charAt(j) == '1')
                {
					cursor += 1;
				}
			}
			if( (cursor%2) > 0 )
            {
				intVal += 128;
			}
			buf.append(Integer.toHexString(intVal) + " ");
		}
		return buf.toString();
	}

	/**
    * Get a list of files from the given directory that conform to the given regular expression.
	* For example, the regular expression, ".*\\.xml$", is the equivilent of using "*.xml" on the command line.
	* 
	* @param srcDir File
	* @param filter String
	* 
	* @return ArrayList<File>
    */
	public static ArrayList<File> getFilesByExtension(File srcDir, final String filter)
	{
		String methodName = MODULE_NAME + "getFilesByExtension(File,String)";
		ArrayList<File> retval = new ArrayList<File>();

		try
		{
			File[] arrFile = srcDir.listFiles(new FilenameFilter()
			{
				public boolean accept(File dir, String name)
				{
					return (name.matches(filter));
				}
			});

			for(int i=0; i<arrFile.length; i++)
			{
				retval.add( arrFile[i] );
			}
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/**
    * Tests to see if a mutex of the given name exists. 
	* 
	* @param name String 
	* 
	* @return boolean
    */
	public static native boolean doesMutexExist(String name);

	/**
	* Creates the given mutex. Doesn't close it but leaves it open until the process exits.
	* 
	* @param name String 
	*/
	public static native void createMutex(String name);

    /**
    * Returns True if the application is already running.
    *
    * @param appName String
    *
    * @return boolean. True if the application is running. 
    */
    public static native boolean isRunning(String appName);

    /**
    * Returns the name of the computer we're running on.
    *
    * @return String name of the computer
    */
    public static native String identifyComputer();

	/**
    * Get the value of the given Registration key under HKLM.
	* 
	* @param key String The Registration Key
	* @param val String The Registration value to query.
	* 
	* @return String Will begin with ERROR if the lookup failed.
    */
	public static native String getRegKey(String key, String val);

	/**
    * Get the Windows HWND for the foreground window. Uses Win32 API 
    * GetForegroundWindow.
	* 
	* @return int 
    */
	public static native int getForegroundHWND();

	/**
    * Get the HWND of the parent of the given child. Uses the Win32 API
	* GetParent().
	* 
	* @param childHWND int
	* 
	* @return int Parent HWND.
    */
	public static native int getParentWindowHWND(int childHWND);

	/**
    * Get the HWND of the window with the given title.
	* 
	* @param title String
	* @param windowClassName String
	* 
	* @return int
    */
	public static native int getHWNDFromTitle(String title, String windowClassName);

	/**
	* Native method for getting the version of Fusion AE present on the system.
	*
	* @return String
	*/
	public static native String getFusionVersionString();

	/**
	* Hooks the parent windows wndProc and intercepts WM_ACTIVATE in order to bring the child window to the top of the z-order.
	* 
	* @param parentHWND int
	* @param childHWND int
	*/
	public static native boolean hookParentWindow(int parentHWND, int childHWND);

	/**
	* Unhooks the parent windows wndProc. VERY IMPORTANT. If you don't unhook the wndProc, then the real wndProc for the parent window will never be reset.
	* 
	* @param parentHWND int
	*/
	public static native boolean unhookParentWindow(int parentHWND);

    /**
    * The native method impl. 
    */
    static 
    {
        try
        {
            System.loadLibrary( "FusionUtils" );
            Logger.log( "FusionUtils.dll Loaded", Logger.DEBUG );
        }
        catch(Throwable e)
        {
            FusionUtils.logError( MODULE_NAME, "FusionUtils LoadLibrary call failed.", e );
        }
    }
}
