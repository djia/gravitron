
#include "RacerEntity.h"

CRacerEntity::~CRacerEntity()
{
	delete m_pRenderer;
}

void CRacerEntity::AttachRenderer(CRenderer * pRenderer)
{
	m_pRenderer = pRenderer;
}

void CRacerEntity::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	float vel = 10;
	float x = 0;
	float z = 0;
	if(g_KeysState[17]) {
		z += vel;
	}
	if(g_KeysState[31]) {
		z -= vel;
	}
	if(g_KeysState[30]) {
		x -= vel;
	}
	if(g_KeysState[32]) {
		x += vel;
	}
	Vector3F vec(x, 0, z);
	SetLinVel(vec);
}

void CRacerEntity::Draw(PhysUt::Matrix4x4F & world, DxUt::CCamera * pCam, DxUt::SLightDir & light)
{
	m_pRenderer->Draw(world*m_LocalTransform, pCam, light);
}