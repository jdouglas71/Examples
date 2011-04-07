#ifndef __KEYGENOPTS_H_
#define __KEYGENOPTS_H_

#include <iostream.h>

struct KeyGenOpts
{
	bool isDebug;    								 
	bool isPerm;
	bool isTest;
	int level;
	unsigned long hardwareId;
	char* name;
	
	KeyGenOpts()
	{
		isDebug = false;
		isPerm = true;
		isTest = false;
		level = 1;
		hardwareId = 0;
		name = "";
	}

	~KeyGenOpts()
	{
		//cout << "die die" << endl;
	}

	void dump()
	{
		cout << "isDebug: " << isDebug << endl;
		cout << "isPerm: " << isPerm << endl;
		cout << "isTest: " <<  isTest << endl;
		cout << "level: " << level << endl;
		cout << "hardwareId: " << hex << hardwareId << endl;
		cout << "name: " << name << endl;
	} 
};



#endif //__KEYGENOPTS_H_
