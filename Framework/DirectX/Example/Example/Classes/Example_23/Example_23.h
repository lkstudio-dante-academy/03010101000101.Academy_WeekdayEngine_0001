#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 23
class Example_23 : public CDirect3DApplication
{
public:

	//! ����
	struct STVertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_NORMAL
		};

		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
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
	Example_23(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_23(void);

private:			// private �Լ�

	//! �ڽ� �޽ø� �׸���
	void drawBoxMesh(void);

	//! �� �޽ø� �׸���
	void drawSphereMesh(void);

	//! �䷯�� �޽ø� �׸���
	void drawTorusMesh(void);

	//! �Ǹ��� �޽ø� �׸���
	void drawCylinderMesh(void);

	//! ������ �޽ø� �׸���
	void drawTeapotMesh(void);

	//! �ڽ� �޽ø� �����Ѵ�
	LPD3DXMESH createBoxMesh(void);

	//! �� �޽ø� �����Ѵ�
	LPD3DXMESH createSphereMesh(void);

	//! �䷯�� �޽ø� �����Ѵ�
	LPD3DXMESH createTorusMesh(void);

	//! �Ǹ��� �޽ø� �����Ѵ�
	LPD3DXMESH createCylinderMesh(void);

	//! ������ �޽ø� �����Ѵ�
	LPD3DXMESH createTeapotMesh(void);

private:			// private ����

	LPD3DXMESH m_pBoxMesh = nullptr;
	LPD3DXMESH m_pSphereMesh = nullptr;
	LPD3DXMESH m_pTorusMesh = nullptr;
	LPD3DXMESH m_pCylinderMesh = nullptr;
	LPD3DXMESH m_pTeapotMesh = nullptr;

	LPD3DXEFFECT m_pEffect = nullptr;
};
