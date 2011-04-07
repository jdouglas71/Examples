/**
* KeyGen. This application leverages the Armadillo CodeGen.DLL in order to 
* generate license key's for a given encryption template. I'm pretty much 
* just providing a command line wrapper for the CreateCode API provided
* by the DLL. In the future, I will provide a GUI and a hook for displaying
* the generated key's. (JGD NOTE: We'll be calling this from a website now).
* 
* Jason Douglas
* S-Matrix Corp.
* 2/19/02 (Happy Birthday Mom!)
*
*
* JGD NOTE: The program has been extended to create both unsigned (16 char) 
* and signed (28 char) keys (using CreateCode and CreateCode2 respectively). 
* The call will be controlled via a command line switch. 
* JGD 2/25/02
*
* JGD NOTE: Another debate I've been having with myself is where to put the 
* encryption template string, external or internal to the program. These 
* string's are the component of the key generation scheme and should be as
* inaccessible as possible. It's pretty much all you need to create a key for
* the program on your own. BUT, embedding them in the program means we have to 
* rebuild the program everytime we change the encryption template string. I
* don't think this will happen very often (almost never once we actually ship)
* so I'm going with embedding them (and putting this into version control), but
* I wanted to document this issue here. We should probably encrypt the EXE if or
* when we expose the KeyGen fuctionality to the general public via the web.
* JGD 2/25/02
*
*/

#include "KeyGen.h"

//JGD Bad programmer. Heavens forbid! A global variable to hold the options!!!
KeyGenOpts theOpts;


int main(char argc, char* argv[])
{
	ParseCommandLine( argc, argv );

	const char* theKey = GetTheKey();

	if( theKey != NULL )
	{
    	//JGD TODO: Is this the format we want to 
 		cout << "The key is: " << theKey << endl;
	}
	else
	{
		cout << "CreateCode call failed" << endl;
		return -1;
	}

	return 0;
}


/**
* Syntax: KeyGen encryption_template name hardwareId
*/	   
void PrintSyntax()
{
	cout << "KeyGen" << endl;
	cout << "[/extend] or [/perm] (DEFAULT)" << endl;
	cout << "[/debug]" << endl;
	cout << "[/name theName]" << endl;
	cout << "[/level levelNum] (DEFAULT IS 1)" << endl;
	cout << "[/hardwareid theId] (perm ONLY)" << endl;
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
	cout << "hardwareIdString: " << hardwareIdString << endl;
	//DEBUG

	retval = strtoul( hardwareIdString, NULL, 16 );

	return retval;
}


/**
* Parse the command line and update theOpts object accordingly.
*/
void ParseCommandLine(int argc, char* argv[])
{
	//DEBUG
    //Print out the given arg's
	//for(int i=0; i<argc; i++)
	//{
	//	cout << "argv[" << i << "]: " << argv[i] << endl;
	//}
	//DEBUG

	if( argc == 1 )
	{
		PrintSyntax();
		exit(-1);
	}

	for(int j=1; j<argc; j++)
	{
		char* tmp = argv[j] ;
	
		if( stricmp(tmp,EXTEND_COMMAND_SWITCH) == 0 )
		{
			theOpts.isPerm = false;
		}
		else if( stricmp(tmp,PERM_COMMAND_SWITCH) == 0 )
		{
			theOpts.isPerm = true;
		}
		else if( stricmp(tmp,DEBUG_COMMAND_SWITCH) == 0 )
		{
   			theOpts.isDebug = true;
		}
		else if( stricmp(tmp,TEST_COMMAND_SWITCH) == 0 )
		{
			theOpts.isTest = true;
		}
		else if( stricmp(tmp,LEVEL_COMMAND_SWITCH) == 0 )
		{
			j++;
			int theLevel = atoi(argv[j]);
			if( (theLevel >= 1) && (theLevel <= 4) )
				theOpts.level = theLevel;

		}
		else if( stricmp(tmp,NAME_COMMAND_SWITCH) == 0 )
		{
			j++;
			theOpts.name = argv[j];
		}
		else if( stricmp(tmp,HARDWAREID_COMMAND_SWITCH) == 0 )
		{
			j++;
			theOpts.hardwareId = GetHardwareId( argv[j] );

		}
		else
		{
			cout << "Command line parsing failed!!!!" << endl;
			PrintSyntax();
			exit(-1);
		}
	}
	

	if( theOpts.isDebug == true )
		theOpts.dump();

	//If isPerm is set, hardwareId must be non-zero and name must have a value 
	if( ((theOpts.isPerm == true) && 
		 ((theOpts.hardwareId == 0) ||
		  (strcmp(theOpts.name,"") == 0))) )
	{
		cout << "A permanent key must have a non-zero hardwareId and name value" << endl;
		PrintSyntax();
		exit(-1);
	}

}

