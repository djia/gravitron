
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
	// get the current velocity
	//Vector3F vec = GetLinVel();

	//float vel = 10;
	float acc = 10;
	//float clipThreshold = 5;
	//Vector3F currentVel = GetLinVel();

	float accX = 0;
	float accZ = 0;

	//float velX = currentVel.x;
	//float velZ = currentVel.z;

	// the current state
	//bool currentUpPressed = g_KeysState[17];
	//bool currentRightPressed = g_KeysState[32];
	//bool currentDownPressed = g_KeysState[31];
	//bool currentLeftPressed = g_KeysState[30];

	// up pressed
	//if(!m_upPressed && currentUpPressed) {
	//	z += acc;
	//// up released
	//} else if(m_upPressed && !currentUpPressed) {
	//	z -= acc;
	//}

	//// down pressed
	//if(!m_downPressed && currentDownPressed) {
	//	z -= acc;
	//// down released
	//} else if(m_downPressed && !currentDownPressed) {
	//	z += acc;
	//}

	//// left pressed
	//if(!m_leftPressed && currentLeftPressed) {
	//	x -= acc;
	//// left released
	//} else if(m_leftPressed && !currentLeftPressed) {
	//	x += acc;
	//}

	//// right pressed
	//if(!m_rightPressed && currentRightPressed) {
	//	x += acc;
	//// right released
	//} else if(m_rightPressed && !currentRightPressed) {
	//	x -= acc;
	//}

	if(g_KeysState[17]) {
		//if(currentVel.z < 0 && currentVel.z > -clipThreshold) {
		//	accZ = 0;
		//	velZ = 0;
		//} else {
		//	accZ += acc;
		//}
		accZ += acc * m_ForwardVec.z;
		accX += acc * m_ForwardVec.x;
	}
	if(g_KeysState[31]) {
		//if(currentVel.z > 0 && currentVel.z < clipThreshold) {
		//	accZ = 0;
		//	velZ = 0;
		//} else {
		//	accZ -= acc;
		//}
		accZ -= acc * m_ForwardVec.z;
		accX -= acc * m_ForwardVec.x;
	}
	if(g_KeysState[30]) {
		//if(currentVel.x > 0 && currentVel.x < clipThreshold) {
		//	accX = 0;
		//	velX = 0;
		//} else {
		//	accX -= acc;
		//}
		accX -= acc * m_RightVec.x;
		accZ -= acc * m_RightVec.z;
	}
	if(g_KeysState[32]) {
		//if(currentVel.x < 0 && currentVel.x > -clipThreshold) {
		//	accX = 0;
		//	velX = 0;
		//} else {
		//	accX += acc;
		//}
		accX += acc * m_RightVec.x;
		accZ += acc * m_RightVec.z;
	}

	// space bar to change gravitySign
	bool currentSpacePressed = g_KeysState[57];
	// only change the sign if going from pressed to unpressed
	if(m_spacePressed && !currentSpacePressed) {
		gravitySign = gravitySign ? false : true;
	}
	m_spacePressed = currentSpacePressed;

	//Vector3F finalVec(vec.x + x, vec.y, vec.z + z);
	//SetLinVel(finalVec);
	Vector3F finalVec(accX, 0, accZ);
	AddToAcc(finalVec);
	//SetLinVel(Vector3F(velX, currentVel.y, velZ));

	//m_upPressed = currentUpPressed;
	//m_downPressed = currentDownPressed;
	//m_leftPressed = currentLeftPressed;
	//m_rightPressed = currentRightPressed;
}

void CRacerEntity::Draw(PhysUt::Matrix4x4F & world, DxUt::CCamera * pCam, DxUt::SLightDir & light)
{
	m_pRenderer->Draw(world*m_LocalTransform, pCam, light);
}