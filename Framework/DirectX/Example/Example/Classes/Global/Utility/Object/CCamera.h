#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! ī�޶�
class CCamera : public CObject
{
public:			// getter, setter

	//! �� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getViewMatrix(void);

	//! ���� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getProjectionMatrix(void);

	//! ��Ⱦ�� �����Ѵ�
	void setAspect(float a_fAspect);

	//! �ֽ� �� ��ü�� �����Ѵ�
	void setFollowObject(CObject* a_pFollowObject, const D3DXVECTOR3& a_rstFollowOffset, EFollowType a_eFollowType = EFollowType::FREE);

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// ������

	//! ������
	CCamera(float a_fAspect);

private:			// private ����

	CObject* m_pFollowObject = nullptr;
	EFollowType m_eFollowType = EFollowType::NONE;
	D3DXVECTOR3 m_stFollowOffset;

	D3DXMATRIXA16 m_stViewMatrix;
	D3DXMATRIXA16 m_stProjectionMatrix;
};
