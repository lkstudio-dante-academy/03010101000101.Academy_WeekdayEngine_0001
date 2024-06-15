#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! �ִϸ��̼� ��Ʈ�ѷ�
class CAnimationController : public IUpdateable
{
public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter, setter

	//! �ִϸ��̼� �̸��� ��ȯ�Ѵ�
	std::vector<std::string> getAnimationNameList(void);

	//! �ð� ������ �����Ѵ�
	void setTimeScale(float a_fTimeScale);

public:			// public �Լ�

	//! �ִϸ��̼��� �����Ѵ�
	void playAnimation(const std::string& a_rAnimationName, bool a_bIsLoop = false);

	//! �ִϸ��̼��� �����Ѵ�
	void stopAnimation(void);

public:			// ������

	//! ������
	CAnimationController(LPD3DXANIMATIONCONTROLLER a_pAnimationController);

	//! �Ҹ���
	virtual ~CAnimationController(void);

private:			// private �Լ�

	//! �ִϸ��̼��� �����Ѵ�
	void doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop);

private:			// private ����

	bool m_bIsLoop = false;
	bool m_bIsPlaying = false;

	float m_fTimeScale = 0.0f;
	float m_fMixedTime = 0.0f;
	float m_fLeftMixedTime = 0.0f;

	LPD3DXANIMATIONSET m_pAnimationSet = nullptr;
	LPD3DXANIMATIONSET m_pNextAnimationSet = nullptr;
	LPD3DXANIMATIONCONTROLLER m_pAnimationController = nullptr;

	std::vector<std::string> m_oAnimationNameList;
	std::unordered_map<std::string, LPD3DXANIMATIONSET> m_oAnimationSetList;
};
