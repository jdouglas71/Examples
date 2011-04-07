/*
* LDAP Example for accessing the Active Directory
* NOTE: Downloaded from the Java forum. 
*/
import javax.naming.*;
import java.util.Hashtable;
import javax.naming.directory.*;

class MyConnection
{
	public static void main(String args[])
	{

		// Set up environment for creating initial context
		Hashtable env = new Hashtable(11);
		env.put(Context.INITIAL_CONTEXT_FACTORY, "com.sun.jndi.ldap.LdapCtxFactory");
		//LDAP Server IP - 192.168.0.5
		//Port - 389
		env.put(Context.PROVIDER_URL, "ldap://192.168.0.5:389/");

		//Authentication Mechanism - Simple
		//Domain Name - mktsoftdomain.com
		//User Name - Administrator
		//Password - donottouch
		env.put(Context.SECURITY_AUTHENTICATION, "simple");
		env.put(Context.SECURITY_PRINCIPAL, "Administrator@mktsoftdomain.com");
		env.put(Context.SECURITY_CREDENTIALS, "donottouch");

		try
		{
	        // Create initial context
			DirContext ctx = new InitialDirContext(env);
			System.out.println("Login Done");

			//User Name - vishu
			//Domain - mktsoftdomain.com
			Attributes answer = ctx.getAttributes("cn=vishu,cn=users,dc=mktsoftdomain,dc=com");

			for( NamingEnumeration ae = answer.getAll(); ae.hasMore(); )
			{
				Attribute attr = (Attribute)ae.next();
				System.out.print(" Attribute: " + attr.getID());
                //Print each value
				for( NamingEnumeration e = attr.getAll(); e.hasMore(); )
				{
					System.out.println(" Value: " + e.next());
				}
			}
		}
		catch( NamingException NEx )
		{
			NEx.printStackTrace();
		}
	}
}

