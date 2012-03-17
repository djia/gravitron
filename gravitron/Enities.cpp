
#include "Enities.h"

CPointGravityEnity::~CPointGravityEnity()
{
	delete m_pRenderer;
}

void CPointGravityEnity::AttachRenderer(CRenderer * pRenderer)
{
	m_pRenderer = pRenderer;
}

void CPointGravityEnity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
}

void CPointGravityEnity::Draw(PhysUt::Matrix4x4F & world, DxUt::CCamera * pCam, DxUt::SLightDir & light)
{
	m_pRenderer->Draw(world*m_LocalTransform, pCam, light);
}

bool CPointGravityEnity::DoForceEnvelopeCollision(CBaseEnity * pCollidingEnity)
{
	if (!m_pFoceEnvelopeBV) return 0;

	Vector3F cp, cn;
	if (m_pFoceEnvelopeBV->Intersect(pCollidingEnity->GetBoundingVolume(), cp, cn)) {
		//Assume the the colliding enity is a CBSphere
		Vector3F dir = ((CBSphere*)m_pContactBV)->PosW() -
			((CBSphere*)pCollidingEnity->GetBoundingVolume())->PosW();

		pCollidingEnity->SetForce(pCollidingEnity->GetMass()*m_fGravity*20.f*dir.Normalize());
	} else {
		pCollidingEnity->SetForce(Vector3F(0, 0, 0));
	}
	return 1;
}