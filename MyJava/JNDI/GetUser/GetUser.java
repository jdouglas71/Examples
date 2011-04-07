/*
* LDAP example of getting a user info from Active Directory. Based on an example found on
* the JNDI forum of Java Developer connection (Via google). 
*
* Jason Douglas 1/5/02
*/
import javax.naming.*;
import java.util.Hashtable;
import javax.naming.directory.*;

class GetUser
{
    //Const 
    //JGD NOTE: Everything here but the pwd should come from a properties file. The pwd could be in the database?
    private static final String LDAP_SERVER_IP = "10.0.0.1"; //JGD Where do I get the real one?
    private static final String LDAP_SERVER_PORT = "389";   //JGD Standard LDAP port
    private static final String LDAP_URL = "ldap://" + LDAP_SERVER_IP + ":" + LDAP_SERVER_PORT;
    private static final String DOMAIN_NAME = "home.s-matrix-corp";
    private static final String DOMAIN_EXT = "com";
    private static final String ADMIN_NAME = "jdouglas";
    private static final String ADMIN_PWD = "jasoniscool";
    private static final String USER_NAME = "jdouglas";
    private static final String AUTH_MECH = "simple";
    
    //Data

    //Methods
    public static void main(String args[])
    {

        // Set up environment for creating initial context
        Hashtable theEnv = new Hashtable();

        theEnv.put( Context.INITIAL_CONTEXT_FACTORY, 
                    "com.sun.jndi.ldap.LdapCtxFactory" );

        //JGD I know this is incorrect for now
		
        theEnv.put( Context.PROVIDER_URL, 
                    LDAP_URL );
		
        theEnv.put( Context.SECURITY_AUTHENTICATION, 
                    AUTH_MECH );
        theEnv.put( Context.SECURITY_PRINCIPAL, 
                    ADMIN_NAME + "@" + DOMAIN_NAME + "." + DOMAIN_EXT );
        theEnv.put( Context.SECURITY_CREDENTIALS, 
                    ADMIN_PWD );
		 
        try
        {
            // Create initial context
            DirContext theContext = new InitialDirContext( theEnv );

            System.out.println( "Login Done" );

            Attributes theAttrs = theContext.getAttributes( "cn="+USER_NAME+",cn=users,dc="+DOMAIN_NAME+",dc="+DOMAIN_EXT );

            for( NamingEnumeration enumer = theAttrs.getAll(); enumer.hasMore(); )
            {
                Attribute attr = (Attribute)enumer.next();
                System.out.print(" Attribute: " + attr.getID());
                //Print each value
                for( NamingEnumeration en = attr.getAll(); en.hasMore(); )
                {
                    System.out.println(" Value: " + en.next());
                }
            }
        }
        catch( NamingException e )
        {
            System.out.println( "Exception thrown! " + e.getMessage() );
            e.printStackTrace(System.out);
        }
    }
}

