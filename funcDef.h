#pragma once
#include "dataDef.h"




void shellcodeEntry();
void createShellCode();
void shellCodeStart();
void shellcodeEP();
int toLowerCase(char c);
int strcmpx(const char* a, const char* b);
PVOID getProc(PCSTR funcName);
void shellCodeEnd();