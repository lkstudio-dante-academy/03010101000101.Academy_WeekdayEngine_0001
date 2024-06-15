#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 25
class Example_25 : public CDirect3DApplication
{
public:

	//! ����
	struct STVertex
	{
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR3 m_stTangent;
		D3DXVECTOR3 m_stBinormal;
		D3DXVECTOR2 m_stUV;
	};

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

public:			// ������

	//! ������
	Example_25(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_25(void);

private:			// private �Լ�

	//! �޽ø� �����Ѵ�
	LPD3DXMESH createMesh(void);

private:			// private ����

	float m_fParallax = 0.0f;

	LPD3DXMESH m_pMesh = nullptr;
	LPD3DXEFFECT m_pEffect = nullptr;

	LPDIRECT3DTEXTURE9 m_pDiffuseTexture = nullptr;
	LPDIRECT3DTEXTURE9 m_pNormalTexture = nullptr;
};
