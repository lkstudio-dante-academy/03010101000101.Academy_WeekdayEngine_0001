#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

//! Example 35
class Example_35 : public CDirect3DApplication
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
	Example_35(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_35(void);

private:			// private �Լ�

	//! �׸��ڸ� �׸���
	void drawShadow(void);

	//! �ڽ� �޽ø� �׸���
	void drawBoxMesh(const std::string& a_rTechniqueName);

	//! ������ �޽ø� �׸���
	void drawTeapotMesh(const std::string& a_rTechniqueName);

	//! �ٴ� �޽ø� �׸���
	void drawGroundMesh(const std::string& a_rTechniqueName);

	//! �ڽ� �޽ø� �����Ѵ�
	LPD3DXMESH createBoxMesh(void);

	//! ������ �޽ø� �����Ѵ�
	LPD3DXMESH createTeapotMesh(void);

	//! �ٴ� �޽ø� �����Ѵ�
	LPD3DXMESH createGroundMesh(void);

	//! ���� Ÿ���� �����Ѵ�
	LPDIRECT3DTEXTURE9 createRenderTarget(void);

	//! ���� ���ٽ��� �����Ѵ�
	LPDIRECT3DSURFACE9 createDepthStencil(void);

private:			// private ����

	D3DXVECTOR3 m_stPosition;

	LPD3DXMESH m_pBoxMesh = nullptr;
	LPD3DXMESH m_pTeapotMesh = nullptr;
	LPD3DXMESH m_pGroundMesh = nullptr;

	LPD3DXEFFECT m_pEffect = nullptr;
	LPDIRECT3DTEXTURE9 m_pRenderTarget = nullptr;
	LPDIRECT3DSURFACE9 m_pDepthStencil = nullptr;
};
