#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! ����
class CLight : public CObject
{
public:			// getter, setter

	//! ���� ���θ� ��ȯ�Ѵ�
	bool getLightEnable(void);

	//! �� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getViewMatrix(void);

	//! ���� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getProjectionMatrix(void);

	//! ���� ���θ� �����Ѵ�
	void setLightEnable(bool a_bIsEnable);

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// ������

	//! ������
	CLight(int a_nIndex);

private:			// private ����

	int m_nIndex = 0;
	bool m_bIsLightEnable = false;

	D3DLIGHT9 m_stLight;
	D3DXMATRIXA16 m_stViewMatrix;
	D3DXMATRIXA16 m_stProjectionMatrix;
};
