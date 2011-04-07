#include <windows.h>
#include <iostream.h>


void perror32(char*& ptr)
{
   FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,
                  GetLastError(),
                  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                  (LPTSTR)&ptr,
                  0,
                  NULL 
                 );
}



int main(int argc, char* argv[])
{
	int retval = 0;

	HANDLE appHandle = CreateMutex( NULL, TRUE, "FusionAdministrator" );

	if( appHandle == NULL )
	{
		MessageBox( NULL, "Couldn't create Mutex", "Test", MB_OK );
	}


	return retval;
}
