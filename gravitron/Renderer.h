
#ifndef RENDERER_H
#define RENDERER_H

#include "DxUtMesh.h"
#include "DxUtShaders.h"
#include "DxUtCamera.h"

using namespace DxUt;

class CRenderer {
protected:
	CRenderer() {}
public:
	CRenderer(CHAR * szfile, DWORD dwOptions) {}
	virtual ~CRenderer() {}
	
	//world must include its own local transform as stored in CBaseEnitiy
	virtual void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light) = 0;

	virtual ID3DX10Mesh * GetID3DX10Mesh() {return NULL; }
	virtual DWORD GetStride() {return 0; }
};


class CPNTPhongRenderer : public CRenderer {
private:
	CMesh m_Mesh;

	static CPNTPhongFx * m_pPNTPhong;

	// We need only one effect for all PNT phong meshes
	void CreateEffectAndLayout();
public:
	//TODO: if a dynamic mesh is created, the mesh will have to be recreated on a window resize
	CPNTPhongRenderer(CHAR * szfile, DWORD dwOptions);
	~CPNTPhongRenderer();
	
	void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light);

	ID3DX10Mesh * GetID3DX10Mesh() {return m_Mesh.GetMesh(); }
	DWORD GetStride() {return sizeof(FLOAT)*(3+3+2); }
};



#endif