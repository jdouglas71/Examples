package com.jdouglas.framework.messages;

import java.util.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.enums.data.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;

/** 
* FusionMessage. Implementation class for IFusionMessage
*
* @author Jason Douglas 6/22/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/
public class FusionMessage
    extends FusionData
        implements IFusionMessage
{
    /** Mod name */
    private static final String MODULE_NAME                                                                     = "FusionMessage.";

    /** Child messages */
    private ArrayList<IFusionMessage> childMessages = new ArrayList<IFusionMessage>();

    /**
    * Constructor
    *
    * @param text String 
    * @param type MessageType 
	* @param sourceData HashMap<String,Object>
    */
    protected FusionMessage(String text, MessageType type, HashMap<String,Object> sourceData)
    {
        setProperty( DISPLAY_NAME, text );
        setProperty( TYPE, type );
        setProperty( MESSAGE_SOURCE, sourceData );

        FrameworkResources frameworkResources = (FrameworkResources)FusionApplication.getResources(IFrameworkProperties.class);

        switch( type )
        {
            case WARNING:
                setProperty( ICON, frameworkResources.getResourceIcon(YELLOW_FLAG_ICON) );
                break;
            case ERROR:
                setProperty( ICON, frameworkResources.getResourceIcon(RED_FLAG_ICON) );
                break;
            case INFO:
            default:
                setProperty( ICON, frameworkResources.getResourceIcon(GREEN_FLAG_ICON) );
        }        
    }


    //**********************************************************************************************************************************//
    // IFusionMessage impl
    // 
    
    /**
    * Get the type. 
    *  
    * @return MessageType
    */
    public MessageType getMessageType()
    {
        return (MessageType)getProperty( TYPE );
    }

    /**
    * Does the message have child messages?
    * 
    * @return boolean
    */
    public boolean hasChildren()
    {
        return (childMessages.size() > 0);
    }

    /**
    * Get child messages.
    * 
    * @return ArrayList<IFusionMessage>
    */
    public ArrayList<IFusionMessage> getChildMessages()
    {
        return (ArrayList<IFusionMessage>)Collections.unmodifiableList(childMessages);
    }

    /**
    * Add a child message.
    * 
    * @param child IFusionMessage
    */
    public void addChildMessage(IFusionMessage child)
    {
        childMessages.add( child );
    }

    /**
    * Remove child message.
    * 
    * @param child IFusionMessage
    */
    public void removeChildMessage(IFusionMessage child)
    {
        childMessages.remove( child );
    }

    // IFusionMessage impl ends
}
