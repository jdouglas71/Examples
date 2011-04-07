package com.jdouglas.framework.core;

/**
* FusionException. An exception wrapper. Gothing for now, but will be enhanced to interact with the MEssage\ErrorManager.
* 
* @author Jason Douglas 5/25/07
* Copyright © 2004-2010 S-Matrix
*/

public class FusionException	
	extends Exception
{
	/** Module name  */
	private static final String MODULE_NAME																	= "FusionException.";

	/**
	* Ctor.
	* 
	* @param message String
    */
	public FusionException(String message)
	{
		super( message );
	}
}
