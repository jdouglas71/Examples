/**
* Xpath example
*
*/

import java.io.*;
import java.util.*;
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

public class Test
{
	private static final String MODULE_NAME = "Test.";
	public static final String TEST_XML = "<SystemControl changeState='UNCHANGED' displayLabel='2 Position Switching Valve' globalLabelIDREF='101003000' systemControlCategory='SWITCHING_VALVE' systemControlID='1003000' systemControlToken='HP_1100_G1316_SWITCHING_VALVE' systemControlVersion='1.8.1.1'><Factors><Factor changeState='UNCHANGED' factorID='1003015' factorState='EXTENDED' factorStateLock='RESTRICTED' maximumAllowed='1' minimumRequired='1' sequencePosition='1'><ValueDefinition FAIDEToken='COLUMN' changeState='UNCHANGED' displayLabel='Valve Gradient Initial-step position' globalLabelIDREF='101003015' nameOfModule='Agilent Technologies 1100 Column Compartment (G1316)' systemControlToken='HP_1100_G1316_SWITCHING_VALVE' valueDefinitionID='1003015' valueDefinitionLabel='Valve Gradient Initial-step position' valueDefinitionToken='VALVE_POS16' valueDefinitionType='CATEGORICAL' valuePrecision='' valueUnit='*' valueUnitLabel='Undefined' valueUnitToken='UNDEFINED'><Constraint calculationIDREF='' changeState='UNCHANGED' constraintID='192' constraintType='ABSOLUTE' rank='0'>HP_1100_1316_POS_1_2</Constraint><Constraint calculationIDREF='' changeState='UNCHANGED' constraintType='RESTRICTED' rank='0'>HP_1100_1316_POS_1_2</Constraint><Constraint calculationIDREF='' changeState='UNCHANGED' constraintID='193' constraintType='ABSOLUTE' rank='1'>HP_1100_1316_POS_1_6</Constraint><Constraint calculationIDREF='' changeState='UNCHANGED' constraintType='RESTRICTED' rank='1'>HP_1100_1316_POS_1_6</Constraint></ValueDefinition></Factor></Factors></SystemControl>";


    /**
    * Execute given xPathCommand on given source node and return the result as an XObject.
    *
    * @param xPathCommand String
    * @param sourceNode Node
	* @param commandType int (e.g. XPath.SELECT or XPath.MATCH)
    *
    * @return XObject
    */ 
    public static XObject executeXPathCommand(String xPathCommand, Node sourceNode, int commandType)
    {
        String methodName = MODULE_NAME + "executeXPathCommand(String,Node)";
        XObject retval = null;

        try
        {
            PrefixResolver prefixResolver = new PrefixResolverDefault( sourceNode );
            XPathContext xpContext = new XPathContext();
            XPath xpath = new XPath( xPathCommand, null, prefixResolver, commandType );

            retval = xpath.execute( xpContext, sourceNode, prefixResolver );
        }
        catch(Exception e)
        {
			e.printStackTrace( System.out );
        }

        return retval; 
    }


	/**
	* Main
	*/
	public static void main(String[] args)
	{
		//String selString = "count(SystemControl)";
		String selString = "count(SystemControl/Factors/Factor/ValueDefinition[@FAIDEToken='COLUMN' and @valueDefinitionType='CATEGORICAL']/Constraint[@constraintType='ABSOLUTE'])";

		try
		{
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            factory.setIgnoringComments(true);
            factory.setCoalescing(false);
            factory.setNamespaceAware(true);
            factory.setValidating(false);

            DocumentBuilder parser = factory.newDocumentBuilder();
            StringReader xmlReader = new StringReader(TEST_XML);
            InputSource xmlSource = new InputSource( xmlReader );
            Document doc = parser.parse( xmlSource );

			XObject xObj = Test.executeXPathCommand( selString, doc, XPath.SELECT );

			System.out.println( xObj.toString() );
		}
		catch(Exception e)
		{
			e.printStackTrace( System.out );
		}
	}


}

