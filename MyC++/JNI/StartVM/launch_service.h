#ifndef __LAUNCH_SERVICE_H_
#define __LAUNCH_SERVICE_H_

#include <iostream.h>
#include <strstrea.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <windows.h>
#include <jni.h>
#include "FUtils.h"

/** Prototypes  */
extern "C" 
{
void ServiceMain(int argc, char* argv[]); 
void ControlHandler(DWORD request); 
int InitService();
int JLog(char*);
}

/** Defines  */
#define SLEEP_TIME 5000
#define FUSION_VM_KEY "FusionVMKey"
#define DEFAULT_INSTALL_PATH "c:\\tmp\\ReallyLongDirName"
//#define DEFAULT_INSTALL_PATH "c:\\work\\s-matrix project life cycle\\development\\binaries\\s-matrix\\common"

/** VM Options */
#define MIN_MEMORY "-Xms64m"
#define MAX_MEMORY "-Xmx256m"
#define RESTORE_MXCSR "-XX:+RestoreMXCSROnJNICalls"
#define FUSION_VM_KEY_OPTION "-DFusionVMKey=TRUE"

#endif //__LAUNCH_SERVICE_H_

