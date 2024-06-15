#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"
#include "../Animation/CAllocateHierarchy.h"
#include "../Animation/CAnimationController.h"

class CTerrain;

//! ��Ų�� �޽�
class CSkinnedMesh : public CRenderObject
{
public:

	enum
	{
		MAX_NUM_BLENDS = 4
	};

	//! ����
	struct STVertex
	{
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR3 m_stTangent;
		D3DXVECTOR3 m_stBinormal;
		D3DXVECTOR2 m_stUV;
		D3DXVECTOR4 m_stBlendWeight;
	};

	//! �Ű�����
	struct STParameters
	{
		std::string m_oMeshFilepath;
		std::string m_oEffectFilepath;
		std::string m_oDummyBoneName;
	};

public:			// getter, setter

	//! �⺻ ��θ� ��ȯ�Ѵ�
	std::string getBasepath(void);

	//! �ִϸ��̼� �̸� ����Ʈ�� ��ȯ�Ѵ�
	std::vector<std::string> getAnimationNameList(void);

	//! ��� ���� ����� ��ȯ�Ѵ�
	virtual D3DXMATRIXA16 getBoundingWorldMatrix(void) override;

	//! �ð� ������ �����Ѵ�
	void setTimeScale(float a_fTimeScale);

	//! ������ �����Ѵ�
	void setTerrain(CTerrain* a_pTerrain);

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ���� �ʱ�ȭ
	virtual void lateInit(void) override;

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	//! ��ü�� �׷��� ���
	virtual void postDrawObject(void) override;

	//! �׸��ڸ� �׸���
	virtual void doDrawShadow(void) override;

	//! �ִϸ��̼��� �����Ѵ�
	void playAnimation(const std::string& a_rAnimationName, bool a_bIsLoop = false);

	//! �ִϸ��̼��� �����Ѵ�
	void stopAnimation(void);

public:			// ������

	//! ������
	CSkinnedMesh(const STParameters& a_rstParameters);

	//! �Ҹ���
	virtual ~CSkinnedMesh(void);

private:			// private �Լ�

	//! ���� �׸���
	void drawBone(LPD3DXFRAME a_pstFrame, bool a_bIsDrawingShadow = false);

	//! �޽� �����̳ʸ� �׸���
	void drawMeshContainer(LPD3DXFRAME a_pstFrame, LPD3DXMESHCONTAINER a_pstMeshContainer, bool a_bIsDrawingShadow = false);

	//! ���� �����Ѵ�
	void setupBone(LPD3DXFRAME a_pstFrame);

	//! ���� �޽� �����̳ʿ� �����Ѵ�
	void setupBoneOnMeshContainer(LPD3DXMESHCONTAINER a_pstMeshContainer);

	//! �� ����� �����Ѵ�
	void updateBoneMatrix(LPD3DXFRAME a_pstFrame, const D3DXMATRIXA16& a_rstMatrix);

	//! ��Ų�� �޽ø� �����Ѵ�
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER a_pstMeshContainer, int a_nMeshContainerNumber);

	//! ��Ų�� �޽ø� �����Ѵ�
	LPD3DXMESH createSkinnedMeshFromX(const std::string& a_rFilepath);

private:			// private ����

	LPD3DXMESH m_pMesh = nullptr;
	LPD3DXEFFECT m_pEffect = nullptr;

	STParameters m_stParameters;
	STSkinnedMesh m_stSkinnedMesh;

	CTerrain* m_pTerrain = nullptr;
	CAnimationController* m_pAnimationController = nullptr;

	std::string m_oBasepath = "";
	CAllocateHierarchy::STBone* m_pstRootBone = nullptr;
	CAllocateHierarchy::STBone* m_pstDummyBone = nullptr;
	std::vector<CAllocateHierarchy::STMeshContainer*> m_oMeshContainerList;
};
