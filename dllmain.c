/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>

char* wchar2char(wchar_t* wcharstring)
{
	wchar_t *WStr = wcharstring;
	size_t len = wcslen(WStr) + 1;
	size_t converted = 0;
	char *CStr;
	CStr=(char*)malloc(len*sizeof(char));
	wcstombs_s(&converted, CStr, len, WStr, _TRUNCATE);
	return CStr;
} 

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
