#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CSkinnedMesh;

//! Example 29
class Example_29 : public CDirect3DApplication
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
	Example_29(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_29(void);

private:			// private �Լ�

	//! ��Ų�� �޽ø� �����Ѵ�
	CSkinnedMesh* createSkinnedMesh(void);

private:			// private ����

	CSkinnedMesh* m_pSkinnedMesh = nullptr;
	std::vector<CSkinnedMesh*> m_oSkinnedMeshList;
};
