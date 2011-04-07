#include <iostream.h>										 
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

									
									
long GetHardwareId(char* id_string);

int main(int argc, char* argv[])
{
	long hardwareId = 0;
	if( argc > 1 )
	{
		hardwareId = GetHardwareId(argv[1]);
		cout << "Before converting to long: " << argv[1] << endl;
		cout << "After converting: " << hex << hardwareId << endl;
	}

		
	return 0;
}

/**
* Extract the hardware Id long from the input string.
*/
long GetHardwareId(char* id_string)
{	
	long retval = 0;
	char* hardwareIdString = 0;

	//The hardware Id string must begin with "0x" since it's a hex number
	//so we add it if it's not already there
	if( strstr(id_string,"0x") != NULL )
	{
		hardwareIdString = id_string;
	}
	else
	{
		int len = strlen(id_string) + 3; //One for the terminator and two for the 0x
		hardwareIdString = new char[len];
		if( hardwareIdString != NULL )
		{										
			memset( hardwareIdString, 0, len );
			strcpy( hardwareIdString, "0x" );
			strcat( hardwareIdString, id_string );
		}
		else
		{
			//Paranoia check
			cout << "Error allocating memory. Exiting..." << endl;
   			return -1;
		}
	}

	//DEBUG
	//cout << "hardwareIdString: " << hardwareIdString << endl;
	//DEBUG

	retval = strtoul( hardwareIdString, NULL, 16 );

	return retval;
}
