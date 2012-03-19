
#include "BaseEntity.h"

CBaseEntity::~CBaseEntity() 
{
	if (m_pRenderer) {
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

void CBaseEntity::AttachBody(CBoundingVolume * pContactBV,
	CRigidBody * pContactRigidBody, CBoundingVolume * pFoceEnvelopeBV) {

	m_pContactBV = pContactBV;
	m_pRigidBody = pContactRigidBody;
	m_pFoceEnvelopeBV = pFoceEnvelopeBV;

	SetTransform(m_LocalTransform);
}

void CBaseEntity::DoContactCollision(CBaseEntity * pCollidingEntity)
{
	if (!m_pContactBV) return;

	Vector3F contactPoint, contactNormal;
	if (m_pContactBV->Intersect(pCollidingEntity->m_pContactBV, contactPoint, contactNormal)) {
		m_pRigidBody->ResolveCollision(*pCollidingEntity->m_pRigidBody, contactPoint, contactNormal);
	}
}

void CBaseEntity::SetTransform(Matrix4x4F & T)
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
