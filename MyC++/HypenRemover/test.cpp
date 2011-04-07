/**
* Remove a hypen from the passed in string.
* Jason Douglas
*/
#include <string.h>
#include <iostream.h>
#include <memory.h>


int main(int argc, char* argv[])
{
    int retval = 0;
    if( argc <= 1 )
    {
        cout << "not enuf params" << endl;
        retval = -1;
    }
    else
    {
        cout << "argv[1]: " << argv[1] << endl;

        int len = strlen(argv[1]) + 1;
        char* theString = new char[len];

        memset( theString, 0, len );
        strncpy( theString, argv[1], len );

        cout << "theString: " << theString << endl;

        char* tmpStr = strchr(theString, '-');
        if( tmpStr == NULL )
        {
            cout << "No hypen in theString!" << endl;
            retval = -1;
        }
        else
        {
            int hyphenPos = tmpStr - theString;
            cout << "hypenPos: " << hyphenPos << endl;

			len = strlen(tmpStr)-1;
            strncpy( theString + hyphenPos, tmpStr+1, len );

			*(theString + hyphenPos + len) = '\0';

            cout << "theString: " << theString << endl;
        }

    }
    return retval;
}

