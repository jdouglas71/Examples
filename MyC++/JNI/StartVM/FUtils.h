#ifndef __FUTILS_H_
#define __FUTILS_H_

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

char* getFADataPath();
char* getFAComputer();
bool isWorkstationVersion();
char* getCurrentTimeString();
void perror32Val(char*& ptr, DWORD errVal);
void perror32(char*& ptr);
int WriteToLog(char* str);

#ifndef FALSE
    #define FALSE 1 
#endif //FALSE

#ifndef TRUE 
    #define TRUE 0
#endif //TRUE

//The keys
#define FUSION_REG_KEY "SOFTWARE\\S-Matrix\\FusionAE\\9.0.1"
#define FA_DATAPATH_KEY "FADataPath"
#define FA_COMPUTER_KEY "FAComputer"
#define INSTALL_FLAGS "InstallFlags"
#define LOGFILE "startvm.log"

#endif //__FUTILS_H_

