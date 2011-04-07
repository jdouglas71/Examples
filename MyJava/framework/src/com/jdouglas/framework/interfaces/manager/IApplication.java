package com.jdouglas.framework.interfaces.manager;

/**
* IApplication. Application interface that supplies hooks for methods that need to be called dynamically in a framework application.
* In most cases, it's sufficient to hang everything off of FusionApplication, but there are a couple things that need to be able to 
* be called appropriately without knowing what application is actually running (e.g. FCAdmin or FusionAE). Perhaps this is just the first 
* move in moving all the FusionApplication functionality into this interface, but I still think that having the static top level application
* class allows for more flexibility. Working with the managers across FAE and FA has certainly shown me how dependent I've been on a 
* specific application class. 
* 
* JGD NOTE: Manager package isn't the right place for this. Might need it's own interface package. Doesn't fit any of the current categories.
* 
* @author Jason Douglas 3/6/08
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IApplication
{
	/**
	* Initialize the application. NOT called from the ctor and should NOT depend on being called from main function.
	* Allows application class to be initialized independent of the main function of an application. Call via application pointer. 
	*/
	public void initApplication();

	/** 
	* Close the application. Call via the application pointer. 
	* 
	* @param code int Exit code. Defined in IUtilCOnstants.
	* @param msg String Message to be displayed to user. 
	*/
	public void closeApplication(int code, String msg);
}
