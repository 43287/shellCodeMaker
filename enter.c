#include "funcDef.h"
#pragma comment(linker,"/entry:shellcodeEntry")




void shellcodeEntry()
{
	createShellCode();
}


void createShellCode()
{
	HANDLE hFile = CreateFileA("ShellCode.bin", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "CreateFileA Error", "Error", MB_ERR_INVALID_CHARS);
		return;
	}
	DWORD dwSize = (DWORD64)shellCodeEnd - (DWORD64)shellCodeStart;
	DWORD dwWrite = 0;
	WriteFile(hFile, shellCodeStart, dwSize, &dwWrite, NULL);
	CloseHandle(hFile);
}