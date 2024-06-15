#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CQuadParticleSystem;

//! Example 33
class Example_33 : public CDirect3DApplication
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
	Example_33(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_33(void);

private:			// private �Լ�

	//! ���� ��ƼŬ �ý����� �����Ѵ�
	CQuadParticleSystem* createQuadParticleSystem(void);

private:			// private ����

	CQuadParticleSystem* m_pQuadParticleSystem = nullptr;
};
