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

int main(int,char**)
{
	JavaVM* jVM;
	JNIEnv* jEnv;
	ofstream log( "FindVM.log", ios::app );
	int retval = 0;

	JavaVM* vmBuf;
	long numVMs = -1;

	vmBuf = new JavaVM[10];

	JavaVMOption vm_options[1];
	vm_options[0].optionString = ".";

	//The VM Arguments 
	JavaVMInitArgs vm_args;
	vm_args.options = vm_options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	vm_args.version = JNI_VERSION_1_6;

	log << "Creating VM!" << endl;
	cout << "Creating VM!" << endl;
	//Launch the VM
	retval = JNI_CreateJavaVM( &jVM, (void**)&jEnv, &vm_args );
	log << "retval: " << retval << endl;
	cout << "retval: " << retval << endl;

	JNI_GetCreatedJavaVMs(&vmBuf, 10, &numVMs );
	log << "Number of found VMs: " << numVMs << endl;
	cout << "Number of found VMs: " << numVMs << endl;

	(jVM)->DestroyJavaVM();

	JNI_GetCreatedJavaVMs(&vmBuf, 10, &numVMs );
	log << "Number of found VMs: " << numVMs << endl;
	cout << "Number of found VMs: " << numVMs << endl;

	log.flush();
	log.close();

	return 0;
}
