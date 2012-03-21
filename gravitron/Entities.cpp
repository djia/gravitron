
#include "Entities.h"

////////////////////////////////CPointGravityEntity////////////////////////////////
void CPointGravityEntity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
}

bool CPointGravityEntity::DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity)
{
	if (!m_pFoceEnvelopeBV) return 0;

	Vector3F cp, cn;
	if (m_pFoceEnvelopeBV->Intersect(pCollidingEntity->GetContactBV(), cp, cn)) {
		//Assume the the colliding entity is a CBSphere
		Vector3F dir = ((CBSphere*)m_pContactBV)->PosW() -
			((CBSphere*)pCollidingEntity->GetContactBV())->PosW();

		if(gravitySign != pCollidingEntity->gravitySign) {
			pCollidingEntity->AddToForce(m_fGravity*dir.Normalize());
		} else {
			pCollidingEntity->AddToForce(-m_fGravity*dir.Normalize());
		}
	}

	return 1;
}

////////////////////////////////CBoxGravityEntity////////////////////////////////
void CDirectionalGravityEntity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	/*if (m_pFoceEnvelopeBV->Intersect(pCollidingEntity->GetBoundingVolume(), cp, cn)) {
		m_fGravity = -m_fGravity;
	}*/
}

bool CDirectionalGravityEntity::DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity)
{
	if (!m_pFoceEnvelopeBV) return 0;

	Vector3F cp, cn;
	if (m_pFoceEnvelopeBV->Intersect(pCollidingEntity->GetContactBV(), cp, cn)) {
		m_pFoceEnvelopeBV->Intersect(pCollidingEntity->GetContactBV(), cp, cn);
		pCollidingEntity->AddToForce(m_fGravity*m_GravityDir.Normalize());
	}
	return 1;
}