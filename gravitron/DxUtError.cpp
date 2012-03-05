
#include "DxUtError.h"
#include <stdio.h>

void _DestroyProcess()
{
	DWORD exitCode = 0;					
	GetExitCodeProcess(NULL, &exitCode);
	ExitProcess(exitCode);	
}

void _SendError(CHAR * szFunction, CHAR * szError, CHAR * szFile, DWORD dwLine)
{
	DWORD dwLen = strlen(szFunction)+strlen(szError)+strlen(szFile)+100;
	char * text = new char[dwLen];

	sprintf_s(text, dwLen, "%s:\nError: %s\nFile: %s\nLine: %d", szFunction, szError, szFile, dwLine);
	MessageBoxA(0, text, 0, 0);	

#if defined (DEBUG) | defined (_DEBUG)
	if (TERMINATE_ON_DEBUG_ERROR) _DestroyProcess();	
#else
	if (TERMINATE_ON_RELEASE_ERROR) _DestroyProcess();	
#endif
}

void _SendErrorEx(CHAR * szFunction, CHAR * szError1, CHAR * szError2, CHAR * szFile, DWORD dwLine)
{
	WORD dwLen = strlen(szFunction)+strlen(szError1)+strlen(szError2)+strlen(szFile)+100;
	char * text = new char[dwLen];

	sprintf_s(text, dwLen, "%s:\nError: %s,\n       %s\nFile: %s\nLine: %d",
		szFunction, szError1, szError2, szFile, dwLine);
	MessageBoxA(0, text, 0, 0);	

#if defined (DEBUG) | defined (_DEBUG)
	if (TERMINATE_ON_DEBUG_ERROR) _DestroyProcess();	
#else
	if (TERMINATE_ON_RELEASE_ERROR) _DestroyProcess();	
#endif
}

