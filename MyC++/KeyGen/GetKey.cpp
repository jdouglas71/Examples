/**
* Code module to contain the fuction wrappers created for the CodeGen.dll.
* There are a number of param's we're not using at this time, but may in the 
* future, so I have several function signatures for completeness.
* 
* Jason Douglas
* S-Matrix Corp
* 2/22/02
*
*/
#include "KeyGen.h"

/**
* Master GetTheKey call that uses the values in the global theOpts object
* to determine what kind of key to generate.
*/
const char* GetTheKey()
{
	if( theOpts.isPerm == true )
	{
		if( theOpts.isTest == true )
			return GetTheKey2( theOpts.name, TEST_PERM_ENCRYPT_TEMPLATE, theOpts.hardwareId, theOpts.level );
		else
		    return GetTheKey2( theOpts.name, PERM_ENCRYPT_TEMPLATE, theOpts.hardwareId, theOpts.level );
	}
	else
	{
		if( theOpts.isTest == true )
			return GetTheKey1( theOpts.name, TEST_EXTEND_DEMO_ENCRYPT_TEMPLATE, theOpts.hardwareId );
		else
			return GetTheKey1( theOpts.name, EXTEND_DEMO_ENCRYPT_TEMPLATE, theOpts.hardwareId );
	}
}


/**
* Function wrapper for the call CreateCode in the CodeGen.DLL. 
*/
const char* GetTheKey1(const char* name, const char* encrypt_template, unsigned long hardwareId)
{
	return GetTheKey1(name,encrypt_template,hardwareId,0);
}

const char* GetTheKey1(const char* name, const char* encrypt_template, unsigned long hardwareId, unsigned short extra_info)
{
	const char* retval = CreateCode( name, encrypt_template, hardwareId, extra_info );

	return retval;
}

/**
* Function wrappers for CreateCode2 call in the CodeGen.DLL
*/
const char* GetTheKey2(const char* name, const char* encrypt_template, 
					   unsigned long hardwareId)
{
	return GetTheKey2(name,encrypt_template,hardwareId,1,0,0,0,0,0);
}

const char* GetTheKey2(const char* name, const char* encrypt_template,
					   unsigned long hardwareId, int level )
{
	return GetTheKey2(name, encrypt_template, hardwareId, level,0,0,0,0,0 );
}

const char* GetTheKey2(const char* name, const char* encrypt_template,
					   unsigned long hardwareId, int level,
					   unsigned short extra_info1, unsigned short extra_info2,
					   unsigned short extra_info3, unsigned short extra_info4,
					   unsigned short extra_info5 )
{
	const char* retval = CreateCode2(level,name,encrypt_template,hardwareId,
									 extra_info1, extra_info2, extra_info3,
									 extra_info4, extra_info5 );

	return retval;
}
