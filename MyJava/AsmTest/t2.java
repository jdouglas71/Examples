import java.util.*;

public class t2
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
		String str;
        while( iter.hasNext() )
        {
            str = (String)iter.next();

            System.out.println( str );
        }
    }
}
