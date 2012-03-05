
#include "GraphicsManager.h"

using namespace DxUt;

DxUt::CD3DApp * DxUt::g_D3DApp = 0;

void CGraphicsManager::Init(HINSTANCE hInst, TCHAR * szClassName, TCHAR * szTitleText,
	WORD wWndPosX, WORD wWndPosY, WORD wWndWidth, WORD wWndHeight, VoidCallback onResizeWindowFunction)
{
	g_D3DApp = m_D3DApp;
			
	m_D3DApp = new DxUt::CD3DApp(hInst, szClassName, szTitleText, 
		wWndPosX, wWndPosY, wWndWidth, wWndHeight, onResizeWindowFunction);
}

void CGraphicsManager::BeginGraphicsLoop(VoidCallback GraphicsLoop) 
{
	m_D3DApp->Loop(GraphicsLoop);
}

void CGraphicsManager::GetUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	memcpy(&rKeyState, g_KeysState, sizeof(CHAR)*256);
	memcpy(&rMouseState, &g_MouseState, sizeof(DIMOUSESTATE));
}

void CGraphicsManager::Render()
{
	float color[] = {0.7f, 0.5f, 1.f, 1.0f};

	g_pD3DDevice->ClearRenderTargetView(g_pRenderTargetView, color);
	g_pD3DDevice->ClearDepthStencilView(g_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	g_pSwapChain->Present(0, 0);
}

void CGraphicsManager::OnResize()
{

}

void CGraphicsManager::Destroy() 
{
	m_D3DApp->DestroyD3DApp();
	delete m_D3DApp;
}
