   
#ifndef DXUTINCLUDE_H
#define DXUTINCLUDE_H

#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10d.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "WinMM.lib")
#else
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "WinMM.lib")
#endif

#include <d3d10.h>
#include <d3dx10.h>
#include <dxgi.h>
#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>
#include <crtdbg.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include "DxUtError.h"
#include "PhysUtVector.h"
#include "PhysUtMatrix.h"

using namespace PhysUt;

#define Abs(x) ((x < 0) ? (-x) : x)

#ifndef ReleaseX
#define ReleaseX(resource)				\
{										\
	if (resource) resource->Release();	\
	resource = NULL;					\
}
#endif

template <typename T>
T * IncPointer(T * ptr, DWORD amount)
{
	return (T*)(((CHAR*)ptr)+amount);
}


namespace DxUt {

//It is a requirement that g_D3DApp be declared and initialized
//as it will initialize and maintain the global variables below
extern class CD3DApp * g_D3DApp;

//The file directory for the program
extern CHAR				g_szFileDir[MAX_PATH];

//The window
extern HWND				g_hWnd;
extern	UINT			g_uiWndWidth;
extern	UINT			g_uiWndHeight;

//The time in s since the start of the program and the fps
extern	DOUBLE			g_TimeElapsed;
extern	FLOAT			g_SPFrame;

//The state of the keyboard and the mouse
extern CHAR				g_KeysState[256];
extern DIMOUSESTATE		g_MouseState;

//Direct3D10 resources
extern IDXGISwapChain *				g_pSwapChain;		
extern ID3D10Device *				g_pD3DDevice;
extern ID3D10RenderTargetView *		g_pRenderTargetView;
extern ID3D10DepthStencilView *		g_pDepthStencilView;

//szDir and szFile in this order will be concatenated into szPath of size MAX_PATH
void InsertDirectory(CHAR * szDir, CHAR * szFile, CHAR * szPath);

//szDir and szFile in this order will be concatenated into szPath of size MAX_PATH if
//the first character of szFile is a '/' otherwise szPath will be szFile
void InsertDirectoryEx(CHAR * szDir, CHAR * szFile, CHAR * szPath);

//Resets the window's render target and depth stencil to the window's ones (global ones)
void ResetRenderTargetAndView();

};

#endif
