
/*
	CodeGen.DLL
	Copyright 1999-2001 by Chad Nelson and the Silicon Realms Toolworks
	All rights reserved
*/

#include "ole2.h"
#include "oleauto.h"

#undef CODEGEN_API
#ifdef CODEGEN_EXPORTS
	#define CODEGEN_API __declspec(dllexport)
#else
	#define CODEGEN_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
	Name:
		CreateCode
		VBCreateCode

	Purpose:
		Generates unsigned (or V1) keys for programs protected by the Armadillo
		Software Protection System.

	Parameters:
		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo
			This is used to specify the number of days/uses for the expiration-
			in-key info, or the number of copies for copies-in-key certificates,
			or the 'extra info' number. If none of these are used, it should be
			zero. See the MakeDate() function for expires-by-date keys.

	Returns: A string containing the 16-digit hexidecimal code, separated into
		four groups of four digits each.
*/

CODEGEN_API const char *CreateCode(const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo);
CODEGEN_API BSTR __stdcall VBCreateCode(const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned long otherinfo);

/*
	Name:
		CreateCode2
		VBCreateCode2

	Purpose:
		Generates signed (or V2) keys, of any level, for programs protected by
		the Armadillo Software Protection System.

	Parameters:
		int level
			The signature level (1 through 8) specified for this certificate
			in your Armadillo project.

		const char *name
			This should be the user-name to link the key to, such as
			"Chad Nelson". It is the name the user must enter, along with the
			returned code, for proper operation.

		const char *encrypt_template
			This is the "encryption template" you chose in your Armadillo
			project. Select the encryption template for the certificate you
			want to make the key for.

		unsigned long hardwareID
			This is the "hardware fingerprint" of the machine the key is
			intended for. If you're not using hardware-locked certificates, it
			should be zero.

		unsigned short otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5
			These are used to specify the number of days/uses for the
			expiration-in-key info, the number of copies for copies-in-key
			certificates, and/or the 'extra info' number.

			The order of the parameters is:
				Expiration info (if expiration-in-key; see MakeDate() function
					for expires-by-date keys);
				Copies (if copies-in-key);
				Extra info (if desired).

			The otherinfo4 and otherinfo5 parameters are not used at present,
			and are reserved for future expansion; they should be set to zero.
			Any unused parameters must also be set to zero.

	Returns: A string containing the 16-digit hexidecimal code, separated into
		four groups of four digits each.
*/

CODEGEN_API const char *CreateCode2(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);
CODEGEN_API BSTR __stdcall VBCreateCode2(int level, const char *name, const char *encrypt_template, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5);

/*
	Most implementations can ignore the MakeDate function. It creates an
	Armadillo-formatted date, for use in the "otherinfo" parameter of CreateKey
	for expire-by-date keys. The year should be the four-digit year, the month
	should be 1 to 12, and the day should be 1 to 31. It returns 0xFFFF on
	error (bad date or date before 01Jan99).
*/

CODEGEN_API unsigned short __stdcall MakeDate(unsigned int year, unsigned int month, unsigned int day);

/*
	The following function will translate an eight-digit hexadecimal code,
	possibly with formatting, to an unsigned long. Some implementations may
	need this capability to generate hardware locked keys.
*/

CODEGEN_API unsigned long __stdcall HexToInt(const char *name);

#ifdef __cplusplus
};
#endif
