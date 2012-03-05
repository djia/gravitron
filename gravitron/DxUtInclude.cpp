
#include "DxUtInclude.h"
#include <shlobj.h>

namespace DxUt {

HWND						g_hWnd =				0;
UINT						g_uiWndWidth =			0;			
UINT						g_uiWndHeight =			0;			
char						g_szFileDir[MAX_PATH];

double						g_TimeElapsed =			0;
float						g_SPFrame =				0;

IDXGISwapChain *			g_pSwapChain =			NULL;
ID3D10Device *				g_pD3DDevice =			NULL;
ID3D10RenderTargetView *	g_pRenderTargetView =	NULL;
ID3D10DepthStencilView *	g_pDepthStencilView =	NULL;

CHAR						g_KeysState[256];
DIMOUSESTATE				g_MouseState;

/*
//Gets the global file directory from the registry
void InitializeDxFramework(char * nameOfRegKey, char * nameOfRegValue, char * dllPath)
{
	HKEY key;
	CHAR subKey[256];
	DWORD index = 0;
	CHAR name[256];
	DWORD nameSize = 256;
	BYTE data[MAX_PATH];
	DWORD dataSize = MAX_PATH;

	sprintf_s(subKey, "SOFTWARE\\%s", nameOfRegKey);
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &key) == ERROR_SUCCESS) {
		while (RegEnumValueA(key, index, name, &nameSize, 0, 0, 0, 0) != ERROR_NO_MORE_ITEMS) {
			if (!strcmp(name, nameOfRegValue)) {
				if (RegQueryValueExA(key, name, 0, 0, data, &dataSize) == ERROR_SUCCESS) {
					InitializeDxFramework((char*)data);
					RegCloseKey(key);
					return;
				}
				break;
			}
			index++;
		}
	}
	DxUtSendError("Could not initialize DxFramework9.");
}

//Releases the framework
void DeInitializeDxFramework()
{
}*/

//szDir and szFile in this order will be concatenated into szFileOut
//szFileOut must be of length MAX_PATH
void InsertDirectory(CHAR * szDir, CHAR * szFile, CHAR * szFileOut)
{
	if (sprintf_s(szFileOut, MAX_PATH, "%s/%s", szDir, szFile) == -1) {
		DxUtSendError("InsertDirectory could not insert the directory.");
	}
}

//szDir and szFile in this order will be concatenated into szFileOut if
//the first character of szFile is a '/' otherwise szFileOut will be szFile
//szFileOut must be of length MAX_PATH
void InsertDirectoryEx(CHAR * szDir, CHAR * szFile, CHAR * szFileOut)
{
	if (szFile[0] == '/') {
		if (sprintf_s(szFileOut, MAX_PATH, "%s%s", szDir, szFile) == -1) {
			DxUtSendError("InsertDirectoryEx could not insert the directory.");
		}
	}
	else {
		if (sprintf_s(szFileOut, MAX_PATH, "%s", szFile) == -1) {
			DxUtSendError("InsertDirectoryEx could not insert the directory.");
		}
	}
}

//Resets the render target and views to the global ones
void ResetRenderTargetAndView()
{
	g_pD3DDevice->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	D3D10_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = g_uiWndWidth;
	vp.Height   = g_uiWndHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	g_pD3DDevice->RSSetViewports(1, &vp);
}


};
