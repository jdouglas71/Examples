package com.jdouglas.framework.interfaces.view;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;

/**
* IFusionViewFactory. The interface for IFusionView creatation and (potentially) tracking. This is not fully fleshed out yet.
*
* @author Jason Douglas 3/15/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFusionViewFactory
{
	/** Editor panel (Boolean) */
	public static final String EDITOR_PANEL													= "EditorPanel";

    /**
    * Returns an IFusionView object associated with the given iTData object. The method is allowed to 
    * return null, but implementors would be better served by defined a base or generic editor panel for 
    * the data that could be used in case a more specialized version is not available.
    *
    * @param data iTData
    *
    * @return IFusionView
    */
    public IFusionView createFusionView(iTData data, HashMap<String,Object> params);

}



