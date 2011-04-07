/**
* C++ example of adding a datasource
* 
* Jason Douglas 7/23/03
*/
#include <windows.h>
#include <odbcinst.h>
#include <iostream.h>
#include <memory.h>
#include <stdio.h>

char sDriver[] = "Microsoft Access Driver (*.mdb)";	
char dataSrc[] = "e:\\work\\myC++\\AddDataSource\\test.mdb";

int main(int argc, char* argv[])
{
    int retval = 0;
	char buf[4096];

    memset( buf, 0, sizeof(buf) );

    //sAttributes = "DSN=" & sName & vbNullChar & "DBQ=" & sFile & vbNullChar
	sprintf( buf, "DSN=%s\0 DBQ=%s\0", "Joey", dataSrc );

	cout << "buf: " << buf << endl;

	retval = SQLConfigDataSource( NULL, ODBC_ADD_DSN, sDriver, buf );

	cout << "retval: " << retval << endl;

    return retval;
}
