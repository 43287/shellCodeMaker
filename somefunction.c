#include "funcDef.h"
#include "dataDef.h"

///需要手动找函数地址
///取LoadLibrary载入函数
///
///
///
///
int toLowerCase(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + ('a' - 'A');
	}
	return c;
}

int strcmpx(const char* a, const char* b)
{
	for (size_t i = 0; !(a[i] == '\0' && b[i] == '\0'); ++i)
	{
		if (toLowerCase(a[i]) != toLowerCase(b[i]))
			return 1;
	}
	return 0;
}



PVOID getProc(PCSTR funcName)
{
#define OFFIN(a, b) (void*)((BYTE*)(a) + (a)->b)
#define OFF(a,b) (void*)((BYTE*)(a) + b)
#define TOFF(a,b,c) (void*)((BYTE*)(a) + b->c)
	PVOID res = NULL;

	PEB* pebdata = (void*)__readgsqword(0x60);
	PEB_LDR_DATA* ldr = pebdata->Ldr;
	LIST_ENTRY* moduleListEntry = ldr->InLoadOrderModuleList.Flink;
	LDR_DATA_TABLE_ENTRY* pmodule = (LDR_DATA_TABLE_ENTRY*)moduleListEntry;
	while (TRUE)
	{
		pmodule = (LDR_DATA_TABLE_ENTRY*)pmodule->InLoadOrderLinks.Flink;
		if ((void*)pmodule == (void*)moduleListEntry)
			break;

		PIMAGE_DOS_HEADER dosHeader = pmodule->DllBase;
		if (!dosHeader)
			continue;
		PIMAGE_NT_HEADERS ntHeader = OFFIN(dosHeader, e_lfanew);

		DWORD exportDirectoryRVA = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
		if (!exportDirectoryRVA)
			continue;
		PIMAGE_EXPORT_DIRECTORY exportDirectory = OFF(dosHeader, exportDirectoryRVA);
		DWORD* nameRVAArray = TOFF(dosHeader, exportDirectory, AddressOfNames);
		DWORD* functionRVAArray = TOFF(dosHeader, exportDirectory, AddressOfFunctions);
		WORD* ordinalArray = TOFF(dosHeader, exportDirectory, AddressOfNameOrdinals);

		for (DWORD i = 0; i < exportDirectory->NumberOfNames; ++i) {
			char* functionName = OFF(dosHeader, nameRVAArray[i]);
			if (!strcmpx(funcName, functionName))
			{
				DWORD functionRVA = functionRVAArray[ordinalArray[i]];
				PVOID functionAddress = OFF(dosHeader, functionRVA);
				res = functionAddress;
				goto out;
			}

		}
	}
out:
	return res;
}

void shellCodeEnd()
{

}