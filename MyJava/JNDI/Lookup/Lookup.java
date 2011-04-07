/**
* JNDI Naming example swiped from the tutorial. I like to type them in myself. The hands
* remember everything.
* 
* Jason Douglas 12/5/02
*/
import javax.naming.*;
import java.util.*;

public class Lookup
{
	public static void main(String[] args)
	{
		//Parse command line
		String theName = "";
		if( args.length < 1 )
		{
			System.out.println( "Syntax: Lookup name" );
			System.exit( 0 );
		}
		else
		{
			theName = args[0];
		}

		//Create the environment
		Hashtable theEnv = new Hashtable();
		theEnv.put( Context.INITIAL_CONTEXT_FACTORY,
					"com.sun.jndi.fscontext.RefFSContextFactory" );

		try
		{
			//Create the context
			Context theContext = new InitialContext(theEnv);

			//Lookup the object
			Object obj = theContext.lookup( theName );

			//Print results
			System.out.println( theName + " is bound to: " + obj );
			System.out.println( "Object class: " + obj.getClass().getName() );
		}
		catch(Exception e)
		{					 
			System.out.println( "Exception throw. Bad Programmer!" );
			e.printStackTrace( System.out );

		}

	}
}
