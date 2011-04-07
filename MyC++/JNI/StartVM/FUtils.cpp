
#include "FUtils.h"

/**
* Look up key to see if the FADataPath override is set. 
*/
char* getFADataPath()
{
    HKEY hKey;
    LONG lRet;
    char* buf;
    DWORD len = 256;
    char* retval = 0;

    buf = new char[len];

    lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, FUSION_REG_KEY, 0, KEY_QUERY_VALUE, &hKey );
    if( lRet == ERROR_SUCCESS ) 
    {
		lRet = RegQueryValueEx( hKey, FA_DATAPATH_KEY, NULL, NULL, (LPBYTE)buf, &len );

		if( lRet == ERROR_SUCCESS )
		{
			retval = buf;
			cout << "FADataPath: " << buf << endl;
		}
		else
		{
			cout << "FADataPath not set." << endl;
		}
    }

    return retval;
}

/**
* Look up key to see if the FAComputer key is set. 
*/
char* getFAComputer()
{
    HKEY hKey;
    LONG lRet;
    char* buf;
    DWORD len = 256;
    char* retval = 0;

    buf = new char[len];

    lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, FUSION_REG_KEY, 0, KEY_QUERY_VALUE, &hKey );
    if( lRet == ERROR_SUCCESS ) 
    {
		lRet = RegQueryValueEx( hKey, FA_COMPUTER_KEY, NULL, NULL, (LPBYTE)buf, &len );

		if( lRet == ERROR_SUCCESS )
		{
			retval = buf;
			cout << "FAComputer: " << buf << endl;
		}
		else
		{
			cout << "FAComputer not set." << endl;
		}
    }

    return retval;
}

/**
* Look up key to see if the Workstation flag is set in the InstallFlags. 
*/
bool isWorkstationVersion()
{
    HKEY hKey;
    LONG lRet;
    char* buf;
    DWORD len = 256;
    bool retval = FALSE;

    buf = new char[len];

    lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, FUSION_REG_KEY, 0, KEY_QUERY_VALUE, &hKey );
    if( lRet == ERROR_SUCCESS ) 
    {
		lRet = RegQueryValueEx( hKey, INSTALL_FLAGS, NULL, NULL, (LPBYTE)buf, &len );

		if( lRet == ERROR_SUCCESS )
		{
			cout << "InstallFlags: " << buf << endl;
			if( strstr(buf,"Workstation") != NULL )
			{
				retval = TRUE;
			}
		}
		else
		{
			cout << "Workstation not set." << endl;
		}
    }

    return retval;
}

/**
* Get a string with the current time as returned by the time function. 
* Don't hang on to the pointer returned. If you want to keep the data around, 
* copy it to your own array. 
*/
char* getCurrentTimeString()
{
	time_t rawTime;
	struct tm *timeInfo;

	time( &rawTime );
	timeInfo = localtime( &rawTime );
	return asctime( timeInfo );
}

/**
* Puts the value of the last error message in the given char*.
*/
void perror32Val(char*& ptr, DWORD errVal)
{
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL,
                   errVal,
                   MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                   (LPTSTR)&ptr,
                   0,
                   NULL 
                  );
}

/**
* Puts the value of the last error message in the given char*.
*/
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

/** 
* Write to the log file specified in the LOGFILE Define.
* 
* @param str
* 
* @return int
*/
int WriteToLog(char* str)
{
	FILE* log;
	log = fopen(LOGFILE, "a+");
	if (log == NULL)
		return -1;
	fprintf(log, "%s\n", str);
	fclose(log);
	return 0;
}
