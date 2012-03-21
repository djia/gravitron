
#ifndef DXUTORBITCAMERA_H
#define DXUTORBITCAMERA_H


#include "DxUtCamera.h"
#include "RacerEntity.h"


namespace DxUt {

class COrbitCamera : public CCamera {
private:
	Vector3F m_Velocity;
	float m_fRotSpeed;
	BOOL m_bTransEnable;
	BOOL m_bRotEnable;
	CRacerEntity * m_Racer;
public:
	COrbitCamera():m_fRotSpeed(0), m_bTransEnable(1), m_bRotEnable(1) {}
	~COrbitCamera() {}

	//Create a left handded coordinate system FPCamera
	void CreateOrbitCameraLH(float fFov, UINT uiWidth, UINT uiHeight, 
		float fNearField, float fFarField, Vector3F & vel, float fRotSpeed);

	void SetOrbitCamera(Vector3F & pos, float fPhi, float fTheta);
	void SetOrbitCamera(Vector3F & vel, float fRotSpeed);
	void EnableTranslation() {m_bTransEnable = 1;}
	void DisableTranslation() {m_bTransEnable = 0;}
	void EnableRotation() {m_bRotEnable = 1;}
	void DisableRotation() {m_bRotEnable = 0;}

	void UpdateOrbitCamera(float dt);

	void OnSize() {
		CreateOrbitCameraLH(m_fFov, g_uiWndWidth, g_uiWndHeight, m_fNearField, m_fFarField, m_Velocity, m_fRotSpeed); }

	COrbitCamera operator=(COrbitCamera & ref);

	void SetRacer(CRacerEntity * racer);
};


};


#endif