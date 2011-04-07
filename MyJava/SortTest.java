import java.util.*;

public class SortTest
{

    /**
    * Generate a random password, used when a password validation fails to ensure that the user doesn't get saved with
    * some sort of invalid (and thus insecure) password. Also used to initialize passwords? 
    */
    public static String randomPassword()
    {
        String retval = "";
        char[] pwd = new char[12];

        Random randomGuy = new Random();

        //We only want ASCII values 40-126
        for(int i=0; i<pwd.length; i++)
        {
            pwd[i] = (char)(randomGuy.nextInt(86)+40);
        }

        retval = new String( pwd );


        return retval;
    }

	/**
	* Main
	*/
    public static void main(String[] args)
    {
		String rawStr = randomPassword();
		char[] rawChars = rawStr.toCharArray();
		char swapChar = 0;

		System.out.println( "Before: " + rawStr );
		for(int i=0; i<rawChars.length; i++)
		{
			System.out.print( (int)rawChars[i] + " " );
		}
		System.out.println( "" );

		for(int i=0; i<(rawChars.length-1); i++)
		{
   			for(int j=(i+1); j>0; j--)
			{
				if( rawChars[j] < rawChars[j-1] ) 
				{
					//System.out.println( "Swapping: " + j + " for " + (j-1) );
					swapChar = rawChars[j];
					rawChars[j] = rawChars[j-1];
					rawChars[j-1] = swapChar;
				}
			}
		}

		rawStr = new String(rawChars);

		System.out.println( "After: " + rawStr );
		for(int i=0; i<rawChars.length; i++)
		{
			System.out.print( (int)rawChars[i] + " " );
		}
		System.out.println( "" );

    }
}
