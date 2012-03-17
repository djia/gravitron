
#ifndef DXUTMESH_H
#define DXUTMESH_H

#include "DxUtInclude.h"
#include "DxUtLight.h"
#include "DxUtMaterial.h"
#include "DxUtVertex.h"

namespace DxUt {

class CMesh {
protected:
	ID3DX10Mesh * m_pMesh;
	DWORD m_nSubsets; 

	SMaterial * m_rgMat; 
	ID3D10ShaderResourceView ** m_rgSRView;

	//Creates an empty mesh
	virtual void CreateMesh(DWORD nTri, DWORD nVert, DWORD dwOptions, 
		const D3D10_INPUT_ELEMENT_DESC * aDesc, DWORD cDesc, DWORD nSubsets);

	virtual void TextureCreationHook(char * szTexFile, DWORD i) {}
public:
	CMesh();
	virtual ~CMesh() {}

	//Loads a PNT mesh from a txt file
	virtual void LoadMeshFromFile(char * szMeshFile, DWORD dwOptions);

	//Sets the SMaterial and sRV of a subset to effect handels
	virtual void SetMatEffectHandels(ID3D10EffectVariable *& eMat,
		ID3D10EffectShaderResourceVariable *& eSRV, DWORD dwSubset);

	//For each subset sets the SMaterial and sRV to effect handels,
	//commits the changes on dwShaderPass , and draws that subset
	virtual void DrawAllSubsets(ID3D10EffectTechnique *& eTech, ID3D10EffectVariable *& eMat, 
		ID3D10EffectShaderResourceVariable *& eSRV, DWORD dwShaderPass);

	ID3DX10Mesh * GetMesh() {return m_pMesh;}
	DWORD GetNumTriangles() {return m_pMesh->GetFaceCount();}
	DWORD GetNumVertices() {return m_pMesh->GetVertexCount();}

	DWORD & GetNumSubsets() {return m_nSubsets;}
	DWORD GetNumMaterial() {return m_nSubsets;}
	SMaterial & GetMaterial(DWORD dwIndex);
	ID3D10ShaderResourceView * GetSHView(DWORD dwIndex); 

	ID3DX10Mesh *& operator->() {
		return m_pMesh; }

	virtual void DestroyMesh();
};

inline SMaterial & CMesh::GetMaterial(DWORD dwIndex)
{
	Assert(dwIndex < m_nSubsets, "CMesh::GetMaterial the material index is out of range.");

	return m_rgMat[dwIndex];
}

inline ID3D10ShaderResourceView * CMesh::GetSHView(DWORD dwIndex)
{
	Assert(dwIndex < m_nSubsets, " CMesh::GetSHView the SHView index is out of range.");

	return m_rgSRView[dwIndex];
}

inline void CMesh::SetMatEffectHandels(ID3D10EffectVariable *& eMat,
	ID3D10EffectShaderResourceVariable *& eSRV, DWORD dwSubset)
{
	Assert(dwSubset < m_nSubsets, "CMesh::SetMatEffectHandels the subset index is out of range.");

	eMat->SetRawValue(&m_rgMat[dwSubset], 0, sizeof(SMaterial));
	eSRV->SetResource(m_rgSRView[dwSubset]);
}

inline void CMesh::DrawAllSubsets(ID3D10EffectTechnique *& eTech, ID3D10EffectVariable *& eMat, 
		ID3D10EffectShaderResourceVariable *& eSRV, DWORD dwShaderPass)
{
	for (DWORD i=0; i<m_nSubsets; i++) {
		eMat->SetRawValue(&m_rgMat[i], 0, sizeof(SMaterial));
		eSRV->SetResource(m_rgSRView[i]);

		eTech->GetPassByIndex(dwShaderPass)->Apply(0);

		m_pMesh->DrawSubset(i);
	}
}

void ExtractVerticesFromMesh(ID3DX10Mesh * pMesh, Vector3F * rgVert, DWORD dwStride);

void ExtractVertexTriangleListFromMesh(ID3DX10Mesh * pMesh, Vector3F * rgVert, DWORD dwStride);

/* pMesh must have adjancey information */
void ExtractAdjanceyFromMesh(ID3DX10Mesh * pMesh, DWORD * rgAdj);


};


#endif
