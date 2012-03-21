
#include "GraphicsManager.h"
#include "ObjectManager.h"

using namespace DxUt;

DxUt::CD3DApp * DxUt::g_D3DApp = 0;

void CGraphicsManager::Init(HINSTANCE hInst, TCHAR * szClassName, TCHAR * szTitleText,
	WORD wWndPosX, WORD wWndPosY, WORD wWndWidth, WORD wWndHeight, VoidCallback onResizeWindowFunction)
{
	m_D3DApp = new DxUt::CD3DApp;
	g_D3DApp = m_D3DApp;

	m_D3DApp->Init(hInst, szClassName, szTitleText, 
		wWndPosX, wWndPosY, wWndWidth, wWndHeight, onResizeWindowFunction);

	m_ObjsInFrustum = m_pObjectManager->GetObjects();

	//Create camera
	//TODO: elmininate the hard coded data
	//m_Camera.CreateFPCameraLH(.5*D3DX_PI, g_uiWndWidth, g_uiWndHeight, 1.f, 500.f, PhysUt::Vector3F(.5f, .5f, .5f), .01f);
	//m_Camera.SetFPCamera(PhysUt::Vector3F(0, 15.f, -15.5f), .5*D3DX_PI, 0);
	m_Camera.CreateOrbitCameraLH(.5*D3DX_PI, g_uiWndWidth, g_uiWndHeight, 1.f, 500.f, PhysUt::Vector3F(.5f, .5f, .5f), .01f);
	m_Camera.SetOrbitCamera(PhysUt::Vector3F(0, 15.f, -15.5f), .5*D3DX_PI, 0);
}

void CGraphicsManager::BeginGraphicsLoop(VoidCallback GraphicsLoop)
{
	m_D3DApp->Loop(GraphicsLoop);
}

void CGraphicsManager::GetUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	memcpy(rKeyState.rgKeys, g_KeysState, sizeof(CHAR)*256);
	memcpy(&rMouseState, &g_MouseState, sizeof(DIMOUSESTATE));
}

void CGraphicsManager::Render()
{
	//TODO: Make update function 
	m_Camera.UpdateOrbitCamera(50.f*DxUt::g_SPFrame);

	//Update Objects in frustum
	m_ObjsInFrustum = m_pObjectManager->GetObjects();

	float color[] = {0.7f, 0.5f, 1.f, 1.0f};
	g_pD3DDevice->ClearRenderTargetView(g_pRenderTargetView, color);
	g_pD3DDevice->ClearDepthStencilView(g_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	Matrix4x4F world;
	world.MIdentity();
	CBaseEntity ** rgObject = m_ObjsInFrustum.data();
	for (UINT i=0, end=m_ObjsInFrustum.size(); i<end; i++) {
		rgObject[i]->Draw(world, &m_Camera, m_Lights[0]);
	}

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
