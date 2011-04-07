import java.util.*;

public class t
{
	public static String[] vals = { "This", "is", "a", "test", "of", "the", "compiler" };
	public static ArrayList list = new ArrayList();

	public static void init() 
	{
		for(int i=0; i<vals.length; i++)
		{
			list.add( vals[i] );
		}
	}


    public static void main(String args[])
    {
		t.init();

		Iterator iter = list.iterator();
		while( iter.hasNext() )
		{
			String str = (String)iter.next();

			System.out.println( str );
		}
    }
}
