#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CTerrain;
class CSkinnedMesh;

//! Example 34
class Example_34 : public CDirect3DApplication
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
	Example_34(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_34(void);

private:			// private �Լ�

	//! ������ �����Ѵ�
	CTerrain* createTerrain(void);

	//! ��Ų�� �޽ø� �����Ѵ�
	CSkinnedMesh* createSkinnedMesh(void);

private:			// private ����

	CTerrain* m_pTerrain = nullptr;
	CSkinnedMesh* m_pSkinnedMesh = nullptr;
};
