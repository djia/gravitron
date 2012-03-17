
#include "DxUtRigidBodyWorld.h"
#include "DxUtTriangle.h"

namespace DxUt {

CRigidBodyWorld::CRigidBodyWorld():m_pRBObject(0)
{
}

void CRigidBodyWorld::CreateRigidBodyWorld(DWORD nHintRBs, DWORD nHintContacts)
{
	Assert(!m_rgRBObject.size(), "CRigidBodyWorld::CreateRigidBodyWorld must destroy the world before creating a new one.");
	Assert(nHintRBs > 0 && nHintContacts > 0, "CRigidBodyWorld::CreateRigidBodyWorld must enter nonzero values for the hints.");

	m_rgRBObject.reserve(nHintRBs);
	m_rgContactPoint.reserve(nHintContacts);
}

DWORD CRigidBodyWorld::AddRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, float fScale, float fMass, Vector3F & pos, Matrix4x4F & rot,
		Vector3F & linVel, Vector3F & angVel, float fElasticity, float fMu, Vector3F & force, Vector3F & torque)
{
	SRBObject rbo;
	rbo.bUsed = 0;
	rbo.bActive = 1;
	CRigidBody & r = rbo.rB;
	r.CreateRigidBody(pMesh, dwStride, fScale, fMass);
	r.m_Pos = pos;
	r.m_Rot = rot;
	r.m_LinVel = linVel;
	r.m_AngVel = angVel;
	r.m_fElasticity = fElasticity;
	r.m_fMu = fMu;
	r.m_Force = force;
	r.m_Torque = torque;

	m_rgRBObject.push_back(rbo);
	m_pRBObject = m_rgRBObject.data();

	return m_rgRBObject.size()-1;
}


void CRigidBodyWorld::DisableRigidBody(DWORD dwId) 
{
	Assert(dwId < m_rgRBObject.size(), "CRigidBodyWorld::DisableRigidBody "
		"an id was specifed which does not exist for any body.");

	m_pRBObject[dwId].bActive = 0;
}

void CRigidBodyWorld::EnableRigidBody(DWORD dwId) 
{
	Assert(dwId < m_rgRBObject.size(), "CRigidBodyWorld::EnableRigidBody "
		"an id was specifed which does not exist for any body.");

	m_pRBObject[dwId].bActive = 1;
}

DWORD CRigidBodyWorld::FindContacts()
{
	DWORD nTotalContacts = 0;
	DWORD s = m_rgRBObject.size();
	m_rgContactPoint.resize(0);

	for (DWORD i=0; i<s; i++) {/* FIX FOR NONACTIVE RIGID BODIES */
		for (DWORD j=i+1; j<s; j++) {

			DWORD						nContactsij = m_pRBObject[i].rB.DetermineCollisionConvex(
				&m_pRBObject[j].rB, (std::vector<BVTree::SContactPoint>*)&m_rgContactPoint);
			SRBContact *				rgCPi=NULL;// = &m_pRBObject[i].rgCP.back();
			Vector3F nor(0, 0, 0);
			if (nContactsij) {
				if ((i == 2 && j == 3) || (i == 3 && j == 2))
					int a=0;
				if ((i == 0 && j == 2) || (i == 2 && j == 0))
					int a=0;
				rgCPi = m_rgContactPoint.data()+nTotalContacts;
				nor = -rgCPi[0].iNor.Normalize();
			}

			for (SRBContact * pCPi=rgCPi, * pEnd=rgCPi+nContactsij; pCPi<pEnd; pCPi++, nTotalContacts++) {
				pCPi->iNor = nor;
				pCPi->rBOk = &m_pRBObject[i];
				pCPi->rBOl = &m_pRBObject[j];
			}
		}
	}
	return nTotalContacts;
}

void CRigidBodyWorld::SolveConstraints(DWORD nContacts)
{
	DWORD K = nContacts;

	MatrixNxNF A;
	A.CreateMatrix(K);
	VectorNF b;
	b.CreateVector(K);

	SRBContact * rgCP = m_rgContactPoint.data();
	for (DWORD j=0; j<K; j++) {
		SRBObject * rBOk = rgCP[j].rBOk;
		SRBObject * rBOl = rgCP[j].rBOl;
		Vector3F jthCtPoint(rgCP[j].iPos);
		Vector3F jthCtNormal(rgCP[j].iNor);

		b.c[j] = -rBOk->rB.GetVelocityAtContactPoint(jthCtPoint, jthCtNormal) +
			rBOl->rB.GetVelocityAtContactPoint(jthCtPoint, jthCtNormal);

		for (DWORD i=0, nCt=0, row=j*K; i<K; i++) {
			A.c[row+i] = 0;
			Vector3F sij(0,0,0);
			if (rgCP[i].rBOk == rBOk) {
				sij = rBOk->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, rgCP[i].iNor);

				if (rgCP[i].rBOl == rBOl)
					sij -= rBOl->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, -rgCP[i].iNor);
			}
			else if (rgCP[i].rBOk == rBOl) {
				sij = -rBOl->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, rgCP[i].iNor);

				if (rgCP[i].rBOl == rBOk)
					sij += rBOk->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, -rgCP[i].iNor);
			}
			else if (rgCP[i].rBOl == rBOk) {/* && rgCP[i].rBOk != rBOl*/
				sij = rBOk->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, -rgCP[i].iNor);
			}
			else if (rgCP[i].rBOl == rBOl) {/* && rgCP[i].rBOk != rBOk*/
				sij = -rBOl->rB.GetImpulseCoefficient(jthCtPoint, rgCP[i].iPos, -rgCP[i].iNor);
			}
			else {
				//DebugBreak();	
				int a=0;
			}

			A.c[row+i] = DotXYZ(sij, jthCtNormal);
		}
	}

	VectorNF x; x.CreateVector(K);
	memset(x.c, 0, sizeof(float)*K);
	ProjectedGaussSeidelMethod(A, x, b, 0.0001f, 500);

	SRBContact * rgCPs = m_rgContactPoint.data();
	for (DWORD t=0; t<K; t++) {
		/* If too large of impulse, discard. */
		if (x.c[t] > 1000.f)
			break;

		Vector3F nt(rgCPs[t].iNor);
		rgCPs[t].rBOk->rB.ApplyImpulse(x.c[t]*(-nt), rgCPs[t].iPos);
		rgCPs[t].rBOl->rB.ApplyImpulse(x.c[t]*(nt), rgCPs[t].iPos);
	}

	A.DestroyMatrix();
	b.DestroyVector();
	x.DestroyVector();
}

void CRigidBodyWorld::UpdateRigidBodies(FLOAT dt, Vector3F & gAcel)
{
	DWORD s = m_rgRBObject.size();
	for (DWORD i=0; i<s; i++) {
		if (!m_pRBObject[i].bActive) continue;

		m_pRBObject[i].rB.SavePosAndRot();
		m_pRBObject[i].rB.IntegratePos(dt);
	} ;

	DWORD nContacts = FindContacts();
	if (nContacts) SolveConstraints(nContacts);

	for (DWORD i=0; i<s; i++) {
		if (!m_pRBObject[i].bActive) continue;

		m_pRBObject[i].rB.RestorePosAndRot();
		m_pRBObject[i].rB.IntegratePos(dt);
		m_pRBObject[i].rB.IntegrateVel(dt, gAcel); 
		m_pRBObject[i].bUsed = 0; 
	}
}

void CRigidBodyWorld::DestroyRigidBodyWorld() 
{
	Assert(m_rgRBObject.capacity(), "CRigidBodyWorld::DestroyRigidBodyWorld "
		"cannot destroy when the world was never created.");

	DWORD s = m_rgRBObject.size();
	for (DWORD i=0; i<s; i++) {
		m_pRBObject[i].rB.DestroyRigidBody();
	}
	m_rgRBObject.clear();
	m_rgContactPoint.clear();
}


};










/*

DWORD						nContactsij = m_pRBObject[i].rB.DetermineCollision(
				&m_pRBObject[j].rB, (std::vector<BVTree::SContactPoint>*)&m_pRBObject[i].rgCP);
			SRBContact *				rgCPi=NULL;// = &m_pRBObject[i].rgCP.back();
			if (m_pRBObject[i].rgCP.size()) rgCPi = m_pRBObject[i].rgCP.data();
			std::vector<SRBContact> &	rgCPj = m_pRBObject[j].rgCP;

			for (SRBContact * pCPi=rgCPi, * pEnd=rgCPi+nContactsij; pCPi<pEnd; pCPi++, nTotalContacts++) {
				/* body i
				pCPi->dwContactPointIndex = nTotalContacts;
				pCPi->rBOl = &m_pRBObject[j];

				/* body j
				SRBContact c = {nTotalContacts, 
					&m_pRBObject[i], pCPi->iPos, -pCPi->iNor};
				rgCPj.push_back(c);

				/* all contact points 
				SRBContact cc = {0, &m_pRBObject[j], rgCPi->iPos, rgCPi->iNor};
				cc.rBOk =  &m_pRBObject[i];
				m_rgContactPoint.push_back(cc);
			}
		}
	}
	return nTotalContacts;
}

void CRigidBodyWorld::SolveConstraints(DWORD nContacts)
{
	DWORD K = nContacts;

	MatrixNxNF A;
	A.CreateMatrix(K);
	VectorNF b;
	b.CreateVector(K);

	SRBObject * rgObj = m_rgRBObject.data();
	for (DWORD k=0, nObj=m_rgRBObject.size(), t=0; k<nObj; k++) {

		SRBObject &		rBOk = rgObj[k];
		SRBContact *	rgCPk = rBOk.rgCP.data();
		DWORD			nCPsk = rBOk.rgCP.size();

		for (DWORD j=0; j<nCPsk; j++, t++) {

			SRBObject &		rBOl = *rgCPk->rBOl;
			SRBContact *	rgCPl = rBOl.rgCP.data();
			Vector3F		jthCtPoint(rgCPk[j].iPos);
			Vector3F		jthCtNormal(rgCPk[j].iNor);

			b.c[t] = rBOk.rB.GetVelocityAtContactPoint(jthCtPoint, jthCtNormal) -
				rBOl.rB.GetVelocityAtContactPoint(jthCtPoint, -jthCtNormal);

			for (DWORD i=0, nCtk=0, nCtl=0, row=t*K; i<K; i++) {
				A.c[row+i] = 0;
				if (((DWORD*)&rgCPk[nCtk])[0] == i) {
					Vector3F s(rBOk.rB.GetImpulseCoefficient(jthCtPoint, rgCPk[nCtk].iPos, rgCPk[nCtk].iNor));nCtk++;

					A.c[row+i] = DotXYZ(s, jthCtNormal);
				}
				if (((DWORD*)&rgCPl[nCtl])[0] == i) {
					Vector3F s(rBOl.rB.GetImpulseCoefficient(jthCtPoint, rgCPl[nCtl].iPos, rgCPl[nCtl].iNor));nCtl++;

					A.c[row+i] -= DotXYZ(s, jthCtNormal);
				}
			}
		}
	}

	VectorNF x; x.CreateVector(K);
	memset(x.c, 0, sizeof(float)*K);
	ProjectedGaussSeidelMethod(A, x, b, 0.001f, 90);

	SRBContact * rgCPs = m_rgContactPoint.data();
	for (DWORD t=0; t<K; t++) {
		/* If too large of impulse, discard. 
		if (x.c[t] > 1000.f)
			break;

		Vector3F nt(rgCPs[t].iNor);
		rgCPs[t].rBOk->rB.ApplyImpulse(x.c[t]*(nt), rgCPs[t].iPos);
		rgCPs[t].rBOl->rB.ApplyImpulse(x.c[t]*(-nt), rgCPs[t].iPos);
	}

	A.DestroyMatrix();
	b.DestroyVector();
	x.DestroyVector();
}
*/




	/*


			Alk.MZero();
			Vector3F & iPosL = c[l].iPos;
			Vector3F & iPosK = c[k].iPos; 

			if (c[l].i == c[k].i) 
				Alk += c[l].rBi->GetPart1(iPosL, c[k].rBi->GetPart2(iPosK));
			if (c[l].i == c[k].j) 
				Alk -= c[l].rBi->GetPart1(iPosL, c[k].rBj->GetPart2(iPosK));
			if (c[l].j == c[k].i)
				Alk -= c[l].rBj->GetPart1(iPosL, c[k].rBi->GetPart2(iPosK));
			if (c[l].j == c[k].j) 
				Alk += c[l].rBj->GetPart1(iPosL, c[k].rBj->GetPart2(iPosK));

			Vector3F v((c[l].iNor*Alk));
			A.c[col + k] = DotXYZ(v, c[k].iNor);
		}
	}

	VectorNF b; 
	b.CreateVector(K); 
	for (DWORD k=0; k<K; k++) {
		Vector3F v(c[k].rBi->GetPart3(gAcel, c[k].iPos, dt) - c[k].rBj->GetPart3(gAcel, c[k].iPos, dt));
		b.c[k] = DotXYZ(c[k].iNor, v);
	}

	VectorNF x, xL, xH; x.CreateVector(K);
	GaussSeidelMethod(A, x, b, xL, xH, 0, 90);

	float dif = x.c[0] - x.c[1];
	for (DWORD k=0; k<K; k++) {
		if (x.c[k] > 1000.f)
			break;

		Vector3F nk(c[k].iNor);
		c[k].rBi->ApplyImpulse((x.c[k]*(-nk)), c[k].iPos, gAcel, dt);
		c[k].rBj->ApplyImpulse(x.c[k]*nk, c[k].iPos, gAcel, dt);
	}

	A.Destroy();
	b.Destroy();
	x.Destroy();*/


