#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CSkinnedMesh;
class CRenderObject;

//! Example 30
class Example_30 : public CDirect3DApplication
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
	Example_30(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	// �Ҹ���
	virtual ~Example_30(void);

private:			// private �Լ�

	//! ��Ų�� �޽ø� �����Ѵ�
	CSkinnedMesh* createSkinnedMesh(void);

private:			// private ����

	CSkinnedMesh* m_pSkinnedMesh = nullptr;
	CRenderObject* m_pRenderObject = nullptr;
};
