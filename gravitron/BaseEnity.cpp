
#include "BaseEnity.h"

void CBaseEnity::AttachForceEnvelope(CBoundingVolume * pFoceEnvelopeBV)
{
	m_pFoceEnvelopeBV = pFoceEnvelopeBV;

	SetTransform(m_LocalTransform);
}

void CBaseEnity::AttachBody(CBoundingVolume * pContactBV, CRigidBody * pContactRigidBody) {

	m_pContactBV = pContactBV;
	m_pRigidBody = pContactRigidBody;

	SetTransform(m_LocalTransform);
}

void CBaseEnity::DoContactCollision(CBaseEnity * pCollidingEnity)
{
	if (!m_pContactBV) return;

	Vector3F contactPoint, contactNormal;
	if (m_pContactBV->Intersect(pCollidingEnity->m_pContactBV, contactPoint, contactNormal)) {
		m_pRigidBody->ResolveCollision(*pCollidingEnity->m_pRigidBody, contactPoint, contactNormal);
	}
}

void CBaseEnity::SetTransform(Matrix4x4F & T)
{
	m_LocalTransform = T;
	if (m_pFoceEnvelopeBV) {
		m_pFoceEnvelopeBV->Transform(T);
	}
	if (m_pContactBV) {
		m_pContactBV->Transform(T);
		m_pRigidBody->Transform(T);
	}
}
