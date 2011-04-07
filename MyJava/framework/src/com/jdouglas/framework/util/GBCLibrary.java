package com.jdouglas.framework.util;

import java.awt.*;
import javax.swing.JComponent;
import javax.swing.JPanel;

/**
* GBCLibrary. A GridBagConstraint generator. Creates commonly used grid bag layouts.
* 
* @author Jason Douglas 12/5/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class GBCLibrary
{
	/** Module name */
	private static final String MODULE_NAME 																= "GBCLibrary.";

	/** Default insets */
	private static final Insets DEFAULT_INSETS = new Insets(5,5,5,5);

	/**
    * Create a set of constraints where the controls all line up in one column.
	* 
	* @return GridBagConstraints
    */
	public static GridBagConstraints oneColGBC()
	{
		String methodName = MODULE_NAME + "oneColGBC()";
		GridBagConstraints retval = new GridBagConstraints();

		retval.anchor = GridBagConstraints.WEST;
		retval.insets = DEFAULT_INSETS;
		retval.gridwidth = GridBagConstraints.REMAINDER;

		return retval;
	}
	
	/**
    * Convenience routine for creating a GBC and using it to add a component to a panel that is configured with a GridBagLayout
    *
	* @param p_objContainerPanel the object to which the JComponent will be added
    * @param p_intGridX int X Position in the layout manager
    */
	public static void addUIComponentToPanel(JPanel p_objContainerPanel, int p_intGridX, int p_intGridY, int p_intGridWidth, int p_intGridHeight, double p_dblWeightX, double p_dblWeightY, int p_intFill, int p_intAnchor, JComponent p_objComponent, Insets p_objInsets)
	{
		GridBagConstraints objConstraints = new GridBagConstraints(p_intGridX, p_intGridY, p_intGridWidth, p_intGridHeight, p_dblWeightX, p_dblWeightY, p_intAnchor, p_intFill, p_objInsets, 0, 0);
		p_objContainerPanel.add(p_objComponent, objConstraints);
	}
}
