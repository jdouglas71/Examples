package com.jdouglas.framework.interfaces.props;

import java.util.*;

/**
* Property strings for the math utilities.
* 
* 
* @author Jason Douglas 2/6/09
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IMathProperties
{
	/** Bundle name */
	public static final String BUNDLE_NAME 								= "com.jdouglas.framework.util.math.MathStrings";

	/** Masks */
	public static final String VAL_MASK									= "%VAL%";

	/**Errors*/
	public static final String SUM_OF_SQUARES_ERROR 					= "SumOfSquaresError";
	public static final String SUM_OF_SQUARES_MEAN_ERROR				= "SumOfSquaresMeanError";
	public static final String MISSING_VAL_ERROR						= "MissingValueInTargetProfileError";
	public static final String LESS_THAN_ZERO_IN_WEIBULL_ERROR			= "LessThanZeroInWeibullError";
}
