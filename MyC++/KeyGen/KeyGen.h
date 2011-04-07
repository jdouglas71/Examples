

#ifndef __KEYGEN_H_
#define __KEYGEN_H_

#include "CodeGen.h"
#include "KeyGenOpts.h"
#include <iostream.h>										 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXTEND_DEMO_ENCRYPT_TEMPLATE "D.o.E. Fusion Professional Timebomb Plus 15"
#define PERM_ENCRYPT_TEMPLATE "D.o.E. Fusion Professional Paid in Full, Yo"

#define TEST_EXTEND_DEMO_ENCRYPT_TEMPLATE "Test Extend Demo Template"
#define TEST_PERM_ENCRYPT_TEMPLATE 		  "Test Permanent Template"

#define EXTEND_COMMAND_SWITCH "/extend"
#define PERM_COMMAND_SWITCH   "/perm"
#define DEBUG_COMMAND_SWITCH  "/debug"
#define LEVEL_COMMAND_SWITCH  "/level"
#define NAME_COMMAND_SWITCH   "/name"
#define HARDWAREID_COMMAND_SWITCH "/hardwareid"
#define TEST_COMMAND_SWITCH   "/test"

extern KeyGenOpts theOpts;


void ParseCommandLine(int,char*[]);									 
void PrintSyntax();	
const char* GetTheKey();
const char* GetTheKey1(const char*,const char*,unsigned long);
const char* GetTheKey1(const char*,const char*,unsigned long,unsigned short);
const char* GetTheKey2(const char*,const char*,unsigned long);
const char* GetTheKey2(const char*,const char*,unsigned long,int);
const char* GetTheKey2(const char*,const char*,unsigned long,int,
					   unsigned short,unsigned short,unsigned short, 
					   unsigned short,unsigned short  );
long GetHardwareId(char*);

#endif //__KEYGEN_H_
