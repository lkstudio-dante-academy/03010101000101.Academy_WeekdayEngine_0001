#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! ��ƼŬ �߻���
class CParticleEmitter : public IUpdateable
{
public:

	//! ��ƼŬ
	struct STParticle
	{
		bool m_bIsActive;

		float m_fActiveTime;
		float m_fMaxActiveTime;

		float m_fSize;
		float m_fStartSize;
		float m_fEndSize;

		D3DXCOLOR m_stColor;
		D3DXCOLOR m_stStartColor;
		D3DXCOLOR m_stEndColor;

		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stVelocity;

		D3DXVECTOR3 m_stRotation;
		D3DXVECTOR3 m_stAngleVelocity;
	};

	//! �Ű�����
	struct STParameters
	{
		int m_nMaxNumParticles;
		int m_nNumParticlesPerSecond;

		EParticleType m_eParticleType;
	};

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter, setter

	//! ��ƼŬ ����Ʈ�� ��ȯ�Ѵ�
	std::vector<STParticle> getParticleList(void);

	//! ��ƼŬ ���� ������ �����Ѵ�
	void setEmitEnable(bool a_bIsEmitEnable);

	//! ��ƼŬ Ÿ���� �����Ѵ�
	void setParticleType(const EParticleType a_eParticleType);

	//! ��� ������ �����Ѵ�
	void setBoundingBox(const STBoundingBox& a_rstBoundingBox);

public:			// ������

	//! ������
	CParticleEmitter(const STParameters& a_rstParameters);

private:			// private �Լ�

	//! ��ƼŬ�� �����Ѵ�
	void createParticles(void);

	//! ��ƼŬ�� �����Ѵ�
	void updateParticles(void);

	//! ��ƼŬ�� �����Ѵ�
	void removeParticles(void);

private:			// private ����

	bool m_bIsEmitEnable = false;
	float m_fSkipTime = 0.0f;

	STParameters m_stParameters;
	STBoundingBox m_stBoundingBox;

	std::vector<STParticle> m_oParticleList;
};
