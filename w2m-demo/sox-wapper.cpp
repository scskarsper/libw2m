#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include "sox-wapper.h"

_TCHAR* TEMPDIR()
{
  TCHAR TempFileName[MAX_PATH];
  if(!GetTempFileName(_T(""), _T(""), 0, TempFileName)) {
      return NULL;
  }
  return TempFileName;
}
_TCHAR* _file2tdir(_TCHAR* s1)
{
  TCHAR* TEMPFILE=TEMPDIR();
  TCHAR TempFilePath[MAX_PATH];
  GetEnvironmentVariable(_T("TEMP"),TempFilePath,MAX_PATH);
  TCHAR* prefile=s1;
  TCHAR tfile[MAX_PATH];
  wcscpy(tfile,prefile);
  *wcsrchr(tfile,'.')='\0';
  TCHAR* tfilename=wcsrchr(tfile,'\\');
  if(tfilename==NULL)return NULL;
  tfilename++;
  
  TCHAR TempPath[MAX_PATH]=_T("");
  wcscpy(TempPath,TempFilePath);
  wcscat(TempPath,TEMPFILE);
  wcscat(TempPath,tfilename);
  _trmdir(TempPath);
  _tmkdir(TempPath);
  return TempPath;
}

_TCHAR* _tdir2source(_TCHAR* tdir)
{
  int bfsize=sizeof(TCHAR)*(wcslen(tdir)+12);
  TCHAR* tempsource=(TCHAR*)malloc(bfsize);
  memset(tempsource,0,bfsize);
  wcscat(tempsource,tdir);
  wcscat(tempsource,_T("\\source.wav"));
  return tempsource;
}

TCHAR* GetSoxInstance()
{
    TCHAR* tcFullPath=(TCHAR*)malloc(sizeof(TCHAR)*MAX_PATH);
    memset(tcFullPath,0,sizeof(TCHAR)*MAX_PATH);
    /** 获取当前程序的执行路径exe路径 */
    GetModuleFileName(NULL, tcFullPath, MAX_PATH);
    *wcsrchr(tcFullPath,'\\')='\0';
	wcscat(tcFullPath,_T("\\engine"));
	_wmkdir(tcFullPath);
	wcscat(tcFullPath,_T("\\sox"));
	_wmkdir(tcFullPath);
	wcscat(tcFullPath,_T("\\sox.exe"));
    return tcFullPath;
}

void ConvertChannel(TCHAR* source,TCHAR* target)
{
	int MAX_TH=MAX_PATH*3+10;
	
    TCHAR* cmd=(TCHAR*)malloc(sizeof(TCHAR)*MAX_TH);
    memset(cmd,0,sizeof(TCHAR)*MAX_TH);

	wcscat(cmd,_T("\""));
	wcscat(cmd,GetSoxInstance());
	wcscat(cmd,_T("\" \""));
	wcscat(cmd,source);
	wcscat(cmd,_T("\" -r 16000 -c 1 -t wav \""));
	wcscat(cmd,target);
	wcscat(cmd,_T("\""));


	STARTUPINFO si; 
	PROCESS_INFORMATION pi;  
    ZeroMemory(&si, sizeof(si));  
    si.cb = sizeof(si);  
	ZeroMemory(&pi, sizeof(pi));  
	LPTSTR szCmdline = _tcsdup(cmd);  
	 // Start the child process.   
	 if (!CreateProcess(NULL,   // No module name (use command line)  
					szCmdline,        // Command line  
					NULL,           // Process handle not inheritable  
					NULL,           // Thread handle not inheritable  
					FALSE,          // Set handle inheritance to FALSE  
					0,              // No creation flags  
					NULL,           // Use parent's environment block  
					 NULL,           // Use parent's starting directory   
					&si,            // Pointer to STARTUPINFO structure  
					&pi)           // Pointer to PROCESS_INFORMATION structure  
		)  
	{  
		printf("CreateProcess failed (%d).\n", GetLastError());  
		/*return 0;*/  
		exit(0);  
	}  

	// Wait until child process exits.  
	WaitForSingleObject(pi.hProcess, INFINITE);  

	// Close process and thread handles.   
	CloseHandle(pi.hProcess);  
	CloseHandle(pi.hThread);  
}
