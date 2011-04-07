package com.jdouglas.framework.util;

import java.awt.Color;
import java.text.*;
import javax.swing.*;
import javax.swing.text.*;


/**
* DecimalInputVerifier. 
*
* @author Bill Merkle 3/12/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class DecimalInputVerifier extends InputVerifier
{
    /** Module name */
    private static final String MODULE_NAME  = "DecimalInputVerifier.";
	
	
	//Constants
	
	//Attributes
	private double m_dblMinValue = Double.MIN_VALUE;
	private double m_dblMaxValue = Double.MAX_VALUE;
	private int m_intPrecision = -1;
	private NumberFormatter m_objNumberFormatter = null;
	private Color m_objDefaultColor = null;
	
	//GUI
	
    /**
    * Constructor.
    */ 
	public DecimalInputVerifier()
    {
		this(Double.MIN_VALUE, Double.MAX_VALUE);
	}
	
	public DecimalInputVerifier(double p_dblMinValue, double p_dblMaxValue)
    {
		this(p_dblMinValue, p_dblMaxValue, -1);
	}
	
	public DecimalInputVerifier(double p_dblMinValue, double p_dblMaxValue, int p_intPrecision)
    {
		m_dblMinValue = p_dblMinValue;
		m_dblMaxValue = p_dblMaxValue;
		m_intPrecision = p_intPrecision;
		m_objNumberFormatter = new NumberFormatter(this.getDecimalFormat());
	}
	
	//Public - InputVerifier
	public boolean verify(JComponent input)
	{
		String methodName = MODULE_NAME + "verify()";
		
		if(input instanceof JTextField)
		{
			JTextField txtTextField = (JTextField)input;
			
			if(m_objDefaultColor == null)
			{
				m_objDefaultColor = txtTextField.getBackground();
			}
			
			//System.out.println(methodName + ": getText() is = " + txtTextField.getText());
			
			Double objDouble = null;
			String strValue = null;
			
			try
			{
				objDouble = new Double(txtTextField.getText());
				
				try
				{
					strValue = m_objNumberFormatter.valueToString(objDouble);
					//System.out.println(methodName + ": formattedValue = " + strValue);
					txtTextField.setText(strValue);
					txtTextField.setBackground(m_objDefaultColor);
				}
				catch(ParseException pe)
				{
					//System.out.println(methodName + ": ParseException Thrown");
					txtTextField.setBackground(Color.RED);
				}
				
			}
			catch(NumberFormatException nfe)
			{
				//System.out.println(methodName + ": value may NOT be a number. See if the user entered an already formatted number");
				
				try
				{
					Object objObject = (Double)m_objNumberFormatter.stringToValue(txtTextField.getText());
					//System.out.println(methodName + ": strintToValue() worked. Value object class is: " + objObject.getClass());
					
					if(objObject instanceof Double)
					{
						strValue = m_objNumberFormatter.valueToString((Double)objObject);
						txtTextField.setText(strValue);
					}
					
					txtTextField.setBackground(m_objDefaultColor);
				}
				catch(ParseException pe)
				{
					//System.out.println(methodName + ": Nope. that didn't work. It's NOT a number");
					txtTextField.setBackground(Color.RED);
				}
			}
		}
		
		return true;
	}
	
	public boolean shouldYieldFocus(JComponent input)
	{
		return this.verify(input);
	}
	
	//Private
	/**
	* This Method...
	*/
	private DecimalFormat getDecimalFormat()
	{
		if(m_intPrecision == -1)
		{
			return new DecimalFormat();
		}
		else
		{
			StringBuffer strPattern = new StringBuffer("#,##0.");
			
			for(int a=0; a<m_intPrecision; a++)
			{
				strPattern.append('0');
			}
			
			return new DecimalFormat(strPattern.toString());
		}
	}
}
