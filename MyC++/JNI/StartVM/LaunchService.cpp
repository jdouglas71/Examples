/**
 * LaunchService. This will create the Java VM required by the various fusion applications.
 * 
* @author Jason Douglas 12/4/02
*/

#include "launch_service.h"

//Globals bad, don't care. 
SERVICE_STATUS ServiceStatus; 
SERVICE_STATUS_HANDLE hStatus; 
JNIEnv* jEnv;
JavaVM* jVM;
char* installPath;
ofstream log(LOGFILE, ios::app);


/** 
* Main Function.
* 
* @param argc int
* @param argv char**
*/
int main(int argc, char* argv[])
{
    //First Parameter is the installPath (hopefully)
	if( argc > 1 )
	{
		int len = strlen(argv[1]);
		installPath = new char[len+1];
		memset( installPath, 0, len+1 );
		strncpy( installPath, argv[1], len+1 );
	}
	else
	{
		installPath = new char[256];
		memset( installPath, 0, 256 );
		strncpy( installPath, DEFAULT_INSTALL_PATH, 256 );
	}

	log << "InstallPath: " << installPath << endl;
	cout << "InstallPath: " << installPath << endl;

	InitService();

	cout << "jvm: " << jVM << endl;
	cout << "jenv: " << jEnv << endl;

	cout << "Calling findclass" << endl;
	//jclass appClass = jEnv->FindClass("com/smatrix/FCAdmin/FCAdminFrame");
	jclass appClass = jEnv->FindClass("com/smatrix/FCAdmin/FCAdmin");
	if( appClass != NULL )
	{
		cout << "Found App class" << endl;
	}
	else
	{
		cout << "Did not find app class" << endl;
	}

	cout << "Trying other app class" << endl;
	appClass = jEnv->FindClass("com/smatrix/FusionAE/FusionAE");
	if( appClass != NULL )
	{
		cout << "Found other App class" << endl;
	}
	else
	{
		cout << "Did not find other app class" << endl;
	}

//	SERVICE_TABLE_ENTRY ServiceTable[2];
//	ServiceTable[0].lpServiceName = "FusionLaunchService";
//	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;

//	ServiceTable[1].lpServiceName = NULL;
//	ServiceTable[1].lpServiceProc = NULL;
	// Start the control dispatcher thread for our service
//	StartServiceCtrlDispatcher(ServiceTable);  

	//Dummy code to keep the console up when I need it
	char c = 0;
	do
	{
	    c = getchar();
		cout << "c = " << (int)c << endl;
	
	} while( c != 10 );   //Escape!!!

	cout << "Exiting StartVM." << endl;

	cout << "Destrory VM returns: " << (jVM)->DestroyJavaVM() << endl;

	log.flush();
	log.close();
	return 0;
}

/** 
* Main Service method. 
* 
* @param argc int
* @param argv char**
*/
#pragma argsused
void ServiceMain(int argc, char* argv[])
{
	int error; 

	ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwWin32ExitCode      = 0; 
	ServiceStatus.dwServiceSpecificExitCode = 0; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0; 

	hStatus = RegisterServiceCtrlHandler( "FusionLaunchService", (LPHANDLER_FUNCTION)ControlHandler ); 

	if (hStatus == (SERVICE_STATUS_HANDLE)0) 
	{ 
		// Registering Control Handler failed
		return; 
	}  

	log << "Inilializing service." << endl;
	// Initialize Service 
	error = InitService(); 
	if (error) 
	{
		// Initialization failed
		ServiceStatus.dwCurrentState       = SERVICE_STOPPED; 
		ServiceStatus.dwWin32ExitCode      = -1; 
		SetServiceStatus(hStatus, &ServiceStatus); 
		return; 
	}

	// We report the running status to SCM. 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
	SetServiceStatus (hStatus, &ServiceStatus);

	MEMORYSTATUS memory;
	// The worker loop of a service
	while( ServiceStatus.dwCurrentState == SERVICE_RUNNING )
	{
		char buffer[16];
		GlobalMemoryStatus(&memory);
		sprintf(buffer, "%d", memory.dwAvailPhys);
		log << buffer << endl;

		Sleep(SLEEP_TIME);
	}
	return; 

}

/**
* Initialize service. 
*/
int InitService()
{
	int retval = 0;

	//The VM Options. 
	//Classpath
	char jarPath[256];
	memset( jarPath, 0, sizeof(jarPath) );
	strncpy( jarPath, installPath, sizeof(jarPath) );
	strncat( jarPath, "\\jars", sizeof(jarPath) );

	log << "JarPath: " << jarPath << endl;
	cout << "JarPath: " << jarPath << endl;

	char* classPath;
	classPath = new char[4096];
	memset( classPath, 0, 4096 );

	sprintf( classPath, 
		     "-Djava.class.path=%s\\FusionFramework.jar;%s\\FCAdmin.jar;%s\\FusionAE.jar;%s\\OSS-infobus.jar;%s\\smatrix.jar;%s\\jama.jar;%s\\activation.jar;%s\\mail.jar;%s\\tcjavaspy2.jar;%s\\xalan.jar;%s\\xml-apis.jar;%s\\galaxieSDK.jar;%s\\CapabilityRobustness.jar;%s\\commons-math-1.1.jar;",
			 //"-Djava.class.path=\"%s\\FusionFramework.jar\";\"%s\\FCAdmin.jar\";\"%s\\FusionAE.jar\";\"%s\\OSS-infobus.jar\";\"%s\\smatrix.jar\";\"%s\\jama.jar\";\"%s\\activation.jar\";\"%s\\mail.jar\";\"%s\\tcjavaspy2.jar\";\"%s\\xalan.jar\";\"%s\\xml-apis.jar\";\"%s\\galaxieSDK.jar\";\"%s\\CapabilityRobustness.jar\";\"%s\\commons-math-1.1.jar\";\"",
			 jarPath,
			 jarPath,
			 jarPath, 
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath,
			 jarPath );

	log << " classPath option: " << classPath << endl;
	cout << " classPath option: " << classPath << endl;
	cout << "classpath length: " << strlen(classPath) << endl;

	JavaVMOption vm_options[4];
	vm_options[0].optionString = classPath;
	vm_options[1].optionString = MIN_MEMORY;
	vm_options[2].optionString = MAX_MEMORY;
	vm_options[3].optionString = FUSION_VM_KEY_OPTION;

	//TEsting
	//JavaVMOption opt[1]; 
	//opt[0].optionString = classPath;

	//The VM Arguments 
	JavaVMInitArgs vm_args;
	vm_args.options = vm_options;
	vm_args.nOptions = 4;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	vm_args.version = JNI_VERSION_1_6;
    
	log << "Creating VM!" << endl;
	cout << "Creating VM!" << endl;
	//Launch the VM
	retval = JNI_CreateJavaVM( &jVM, (void**)&jEnv, &vm_args );
	log << "retval: " << retval << endl;
	cout << "retval: " << retval << endl;
	
	return retval;
}

/** 
* Function that will be registered with the serice manager.
* 
* @param request DWORD
*/
void ControlHandler(DWORD request) 
{ 
    switch(request) 
    { 
		case SERVICE_CONTROL_STOP: 

			if( jVM != NULL )
			{
				log << "Destroying VM." << endl;
				(jVM)->DestroyJavaVM();
			}

            ServiceStatus.dwWin32ExitCode = 0; 
            ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
            SetServiceStatus (hStatus, &ServiceStatus);
			log.flush();
            return; 
 
        case SERVICE_CONTROL_SHUTDOWN: 
			if( jVM != NULL )
			{
				log << "Destroying VM." << endl;
				(jVM)->DestroyJavaVM();
			}

            ServiceStatus.dwWin32ExitCode = 0; 
            ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
            SetServiceStatus (hStatus, &ServiceStatus);
			log.flush();
            return; 
        
        default:
            break;
    } 
 
    // Report current status
    SetServiceStatus (hStatus,  &ServiceStatus);
} 

