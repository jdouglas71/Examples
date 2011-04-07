/**
* Dump the environment using the _environ pointer from the RTL. Defined
* in STDLIB.H as "extern char** _environ". 
* Jason Douglas 
* S-Matrix Corp.
* 2/27/02
*/

#include "DumpEnv.h"

int main(int argc, char* argv[])
{			 
	if( _environ != NULL )
	{
	    int i = 0;
		char* tmp;
		while( tmp = *(_environ + i) ) //(i*sizeof(char*))) )
		{
			cout << tmp << endl;
			i++;
		}

	}
	return 0;
}
