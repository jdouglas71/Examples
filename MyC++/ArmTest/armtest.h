#ifndef __ARMTEST_H_
#define __ARMTEST_H_

#include <windows.h> /* For declaration of GetEnvironmentVariable() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>

#define USERNAME "USERNAME"
#define USERKEY "USERKEY"
#define FUSION_MODULE "FUSION_MODULE"
#define FINGERPRINT "FINGERPRINT"

bool ShowUserNameAndKey(void);
void ShowInfo(void);

#endif // __ARMTEST_H_
