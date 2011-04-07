/**
* Module for GetGalaxieVersion.
* 
* Jason Douglas 1/6/05
* Copyright © 2004, 2005 S-Matrix Corporation. All rights reserved.
*/

#include <galaxieJNI.h>
#include <windows.h>

/**
* Retrieves the version of galaxie by finding galaxie.exe via the registry and extracting its version information.
*/
char* GetGalaxieVersion()
{
    VS_FIXEDFILEINFO fileInfo;
    char* fileName = "c:\\Galaxie\\Client\\galaxie.exe";
    DWORD dwHandle;
    DWORD len = GetFileVersionInfoSize( fileName, &dwHandle );
    if( len <= 0 )
    {
        return NULL;
    }

    char* versionInfo = new char[len];
    BOOL bRet = GetFileVersionInfo( fileName, dwHandle, len, versionInfo );

    UINT uLen;
    void* pBuf;
    bRet = VerQueryValue( versionInfo, "\\", &pBuf, &uLen );
    if( !bRet )
    {
        return NULL;
    }

    memcpy( &fileInfo, pBuf, sizeof(VS_FIXEDFILEINFO) );
    delete[] versionInfo;

    strstream strBuf;

    strBuf << HIWORD(fileInfo.dwFileVersionMS) << "." << 
              LOWORD(fileInfo.dwFileVersionMS) << "." <<
              HIWORD(fileInfo.dwFileVersionLS) << "." <<
              LOWORD(fileInfo.dwFileVersionLS);

    cout << "Galaxie version: " << strBuf.str() << endl;

    return strBuf.str();
}



