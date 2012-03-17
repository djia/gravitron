
#include "Renderer.h"

CPNTPhongFx * CPNTPhongRenderer::m_pPNTPhong = NULL;

CPNTPhongRenderer::CPNTPhongRenderer(CHAR * szMeshFile, DWORD dwOptions)
{
	m_Mesh.LoadMeshFromFile(szMeshFile, dwOptions);
	if (!m_pPNTPhong) CreateEffectAndLayout();
}

CPNTPhongRenderer::~CPNTPhongRenderer() 
{
	m_Mesh.DestroyMesh();
	//ReleaseX(m_pPNTPhong->GetEffect());
}

void CPNTPhongRenderer::CreateEffectAndLayout()
{
	//Create Effect
	CPNTPhongFx & shader = *(m_pPNTPhong = new CPNTPhongFx);
	shader.CreateEffect("/Shaders/PNT_Phong.fx");
	shader.eTech		= shader->GetTechniqueByIndex(0);
	shader.eWVP			= shader->GetVariableByName("g_WVP")->AsMatrix();
	shader.eWorld		= shader->GetVariableByName("g_World")->AsMatrix();
	shader.eMaterial	= shader->GetVariableByName("g_Mat");
	shader.eLight		= shader->GetVariableByName("g_Light");
	shader.eCamPos		= shader->GetVariableByName("g_CamPos");
	shader.eTexture		= shader->GetVariableByName("g_Tex")->AsShaderResource();
	shader.eTextureTile	= shader->GetVariableByName("g_TexTile")->AsScalar();

	//Input layout
	DxUt::CreateInputLayout(m_pPNTPhong->eTech, DxUt::GetVertexElementDescPNT(), 3, 0, m_pPNTPhong->eVertexLayout);
}
	
void CPNTPhongRenderer::Draw(Matrix4x4F & world, CCamera * pCam, SLightDir & light)
{
	g_pD3DDevice->IASetInputLayout(m_pPNTPhong->eVertexLayout);
	g_pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pCam->SetEffectCamPos(m_pPNTPhong->eCamPos);
	m_pPNTPhong->eLight->SetRawValue(&light, 0, sizeof(DxUt::SLightDir));

	pCam->SetEffectMatrices(world.Transpose(), m_pPNTPhong->eWVP, m_pPNTPhong->eWorld);
	m_Mesh.DrawAllSubsets(m_pPNTPhong->eTech, m_pPNTPhong->eMaterial, m_pPNTPhong->eTexture, 0);
}