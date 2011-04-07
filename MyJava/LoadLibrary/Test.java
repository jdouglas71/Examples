/**
* Testing LoadLibrary.
*
* 
* @author Jason Douglas 2/23/05
*/


public class Test
{

	static 
	{
		try
		{
			System.loadLibrary( "billy" );
		}
		catch(Throwable e)
		{
			System.out.println( "Caught it!!!" );
			e.printStackTrace( System.out );
		}
	}



	/**
	* Main
	*/
	public static void main(String args[])
	{
		System.out.println( "Running..." );
	}
}

