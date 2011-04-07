/**
* JNDI example from the tutorial.
*
* @author Jason Douglas 12/12/02
*/

import javax.naming.*;
import javax.naming.directory.*;
import java.util.*;

public class GetAttr
{

    public static void main(String[] args)
    {
        Hashtable theEnv = new Hashtable();
        theEnv.put( Context.INITIAL_CONTEXT_FACTORY,
                    "com.sun.jndi.ldap.LdapCtxFactory" );
        theEnv.put( Context.PROVIDER_URL, 
                    "file:d:/jndi/test" );

        try
        {
            DirContext theContext = new InitialDirContext(theEnv);

            Attributes theAttrs = theContext.getAttributes( "cn=Ted Geisel, ou=People" );
            System.out.println( "Sn: = " + theAttrs.get("sn").get() );
        }
        catch(Exception e)
        {
            System.out.println( "Error caught" );
            e.printStackTrace( System.out );
        }
        
    }
}


