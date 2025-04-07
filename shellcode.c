#include "funcDef.h"

void shellCodeStart()
{
	shellcodeEP();
}


void shellcodeEP()
{
	char pLoadLibraryA[] = { 'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A', '\0' };

	HMODULE(*pLoadLibrary)(LPCSTR) = getProc(pLoadLibraryA);

	char puser32[] = { 'u', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', '\0' };

	HMODULE hUser32 = pLoadLibrary(puser32);
	char pMessageBoxA[] = { 'M', 'e', 's', 's', 'a', 'g', 'e', 'B', 'o', 'x', 'A', '\0' };

	int(*targetFunc)(HWND, LPCSTR, LPCSTR, UINT) = getProc(pMessageBoxA);
	char pSUCCESS[] = {'S', 'U', 'C', 'C', 'E', 'S', 'S', '\0'};
	targetFunc(NULL, pSUCCESS, pSUCCESS, MB_OKCANCEL);
}








