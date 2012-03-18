
#include "Entities.h"

CPointGravityEntity::~CPointGravityEntity()
{
	delete m_pRenderer;
}

void CPointGravityEntity::AttachRenderer(CRenderer * pRenderer)
{
	m_pRenderer = pRenderer;
}

void CPointGravityEntity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
}

void CPointGravityEntity::Draw(PhysUt::Matrix4x4F & world, DxUt::CCamera * pCam, DxUt::SLightDir & light)
{
	m_pRenderer->Draw(world*m_LocalTransform, pCam, light);
}

bool CPointGravityEntity::DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity)
{
	if (!m_pFoceEnvelopeBV) return 0;

	Vector3F cp, cn;
	if (m_pFoceEnvelopeBV->Intersect(pCollidingEntity->GetBoundingVolume(), cp, cn)) {
		//Assume the the colliding entity is a CBSphere
		Vector3F dir = ((CBSphere*)m_pContactBV)->PosW() -
			((CBSphere*)pCollidingEntity->GetBoundingVolume())->PosW();

		pCollidingEntity->SetForce(m_fGravity*20.f*dir.Normalize());
	} else {
		pCollidingEntity->SetForce(Vector3F(0, 0, 0));
	}
	return 1;
}