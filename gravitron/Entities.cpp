
#include "Entities.h"

////////////////////////////////CPointGravityEntity////////////////////////////////
void CPointGravityEntity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	if(m_Radius <= 0 || m_ThetaVel == 0) {
		return;
	}
	float radius = m_Radius;
	float thetaVel = m_ThetaVel;
	g_SPFrame;
	// calculate the position
	// new theta
	m_Theta += thetaVel * g_SPFrame;
	if(m_Theta >= 2 * D3DX_PI) {
		m_Theta = 0;
	}
	Vector3F currentPos = m_pRigidBody->GetPos();
	float x = m_InitialPos.x + radius * cos(m_Theta);
	float y = currentPos.y;
	float z = m_InitialPos.z + radius * sin(m_Theta);
	//m_pRigidBody->SetPos(Vector3F(m_InitialPos.x + radius * cos(m_Theta), currentPos.y, m_InitialPos.z + radius * sin(m_Theta)));
	m_LocalTransform.m[0][3] = x;
	m_LocalTransform.m[1][3] = y;
	m_LocalTransform.m[2][3] = z;
	SetTransform(m_LocalTransform);
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