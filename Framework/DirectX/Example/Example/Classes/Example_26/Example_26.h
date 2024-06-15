#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 26
class Example_26 : public CDirect3DApplication
{
public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

	//! ȭ���� �׸���
	virtual void draw(void) override;

	//! ���ø����̼��� �ʱ�ȭ�Ѵ�
	virtual void initApplication(void) override;

public:			// ������

	//! ������
	Example_26(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_26(void);

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

	float m_fYaw = 0.0f;
	LPD3DXEFFECT m_pEffect = nullptr;
	LPDIRECT3DCUBETEXTURE9 m_pCubeTexture = nullptr;
};
