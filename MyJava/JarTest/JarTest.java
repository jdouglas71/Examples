/**
* JarTest. My example for handling jar files in Java. My goal is to be able to extract the individual files, determine their
* types based on the file extensions and create File objects that can be passed to different parts of the program for 
* processing. 
*
* Jason Douglas 8/9/05 
*/

import java.io.*;
import java.util.*;
import java.util.jar.*;

public class JarTest 
{
	private static final String MODULE_NAME 								= "JarTest.";

	private static final String TMP_DIR										= "tmpdir";


	/**
	* Main
	*/
	public static void main(String[] args)
	{
		if( args.length <= 0 ) 
		{
			System.out.println( "Need to specify a jar file." );
			return;
		}

		try
		{
			JarFile jarFile = new JarFile( args[0], true );
			int len = 0;
			byte[] buf = new byte[4096];

			Enumeration entries = jarFile.entries();
			while( entries.hasMoreElements() )
			{
				JarEntry entry = (JarEntry)entries.nextElement();
				System.out.println( entry.getName() + "\t\t" + entry.getSize() + "\t\t" + entry.getTime() );

				if( entry.isDirectory() ) 
				{
					new File( TMP_DIR + File.separatorChar + entry.getName()).mkdir();
				}
				else
				{
					FileOutputStream os = new FileOutputStream( TMP_DIR + File.separatorChar + entry.getName());
					InputStream is = jarFile.getInputStream( entry );
					while( (len = is.read(buf)) > 0 )
					{
						os.write( buf, 0, len );
					}
					os.close();
					is.close();
				}
			}

		}
		catch(Exception e)
		{
			System.out.println( "Exception Thrown!!!" );
			e.printStackTrace( System.out );
		}
	}
}
