#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! ��ī�� �ڽ�
class CSkybox : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		UINT m_nSlices;
		UINT m_nStacks;

		float m_fRadius;
		std::string m_oEffectFilepath;
		std::string m_oCubeTextureFilepath;
	};

public:			// public �Լ�

	//! �ʱ�ȭ
	virtual void init(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

public:			// ������

	//! ������
	CSkybox(const STParameters& a_rstParameters);

	//! �Ҹ���
	virtual ~CSkybox(void);

private:			// private �Լ�

	//! �޽ø� �����Ѵ�
	LPD3DXMESH createMesh(void);

private:			// private ����

	STParameters m_stParameters;

	LPD3DXMESH m_pMesh = nullptr;
	LPD3DXEFFECT m_pEffect = nullptr;
	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture = nullptr;
};
