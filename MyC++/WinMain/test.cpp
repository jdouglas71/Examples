/**
* WinMain test.
*/

#include <windows.h>


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



#pragma argsused
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char far* cmdLine, int cmdShow)
{
    int retval = 0;

	HANDLE appHandle = CreateMutex( NULL, TRUE, "Fusion Administrator" );

	int error = GetLastError();

	char* errorMsg = NULL;
	perror32( errorMsg );

    if( error == ERROR_ALREADY_EXISTS )
    {
        MessageBox( 0, "Test is already running.", "Test", MB_OK | MB_ICONEXCLAMATION );

    }
    else 
    {
        MessageBox( 0, errorMsg, "Test", MB_OK );
    }

    return retval;
}
