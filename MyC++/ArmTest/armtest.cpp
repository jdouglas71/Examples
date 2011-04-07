/**
* My testbed for the armadillo multiple certificates concept. I'm trying to show that we can have mulitple "permanent"
* certifcates on FusionChrom.exe that will allow us to "unlock" functionality.
*
*
* Jason Douglas 3/3/04
*/

#include "armtest.h"


int main(int, char*[])
{
    int retval = 0;

    //ShowUserNameAndKey();
    ShowInfo();

    return retval;
}


/**
* Lifted from the ARM help. Note that they use the windows api GetEnvironmentVariable rather than the standard C RTL function
* getenv(). They claim that getenv() doesn't pick up changes to the environment made by ArmAccess.dll, which could be entirely
* true if the RTL is maintaining its own copy of the environment.
*/
bool ShowUserNameAndKey(void) 
{
    char name[256]="", key[256]="", display[512];
    bool retval = true;

    /* Check the USERNAME; it should always be set if the program is protected */
    if (!GetEnvironmentVariable("USERNAME", name, 255)) 
    {
        //MessageBox(0, "Is the program protected?", "Error!", MB_OK|MB_ICONERROR);
		cout << "USERNAME not in environment" << endl;
        retval = false;
        return retval;
    }

    if (!GetEnvironmentVariable("USERKEY", key, 255)) 
    {
        strcpy(key, "No key!");
    }

    if (!stricmp(name, "DEFAULT")) 
    {
        strcpy(display, "Program is using the default key; no username or key is available.");
    } 
    else 
    {
        sprintf(display, "Program is registered to %s (%s).", name, key);
    }

    //MessageBox(0, display, "Information", MB_OK|MB_ICONINFORMATION);
	cout << "Results: " << display << endl;

    return retval;
}

/**
* Show the environment info I'm intested in.
*/
void ShowInfo(void)
{
    char name[256]="", key[256]="", module[256]="", fingerprint[256];

    GetEnvironmentVariable( USERNAME, name, sizeof(name) );
    GetEnvironmentVariable( USERKEY, key, sizeof(key) );
    GetEnvironmentVariable( FUSION_MODULE, module, sizeof(module) );
    GetEnvironmentVariable( FINGERPRINT, fingerprint, sizeof(fingerprint) );

    cout << "UserName: " << name << endl;
    cout << "Userkey: " << key << endl;
    cout << "FusionModule: " << module << endl;
    cout << "Fingerprint: " << fingerprint << endl;
}



