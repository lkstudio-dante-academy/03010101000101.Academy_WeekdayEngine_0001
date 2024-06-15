#pragma once

#include "../Global/Define/KGlobalDefine.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"

class CPointParticleSystem;

//! Example 32
class Example_32 : public CDirect3DApplication
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
	Example_32(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize);

	//! �Ҹ���
	virtual ~Example_32(void);

private:			// private �Լ�

	//! ����Ʈ ��ƼŬ �ý����� �����Ѵ�
	CPointParticleSystem* createPointParticleSystem(void);

private:			// private ����

	CPointParticleSystem* m_pPointParticleSystem = nullptr;
};
