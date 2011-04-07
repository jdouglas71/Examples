/**
* Test class for JNI testing. I want to see if I can expose this class as a COM interface.
*
* Jason Douglas 5/3/02
*/


import java.util.*;

public class Tester
{
    public String getName()
    {
	return "Jason is cool";
    }

    public void setName(String str)
    {
	System.out.println("The string is " + str );
    }

    public int getNumber()
    {
	return 71;
    }

    public void setNumber(int number)
    {
	System.out.println( "The number is " + number );
    }
							 


}


