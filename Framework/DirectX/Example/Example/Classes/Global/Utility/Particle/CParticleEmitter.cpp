#include "CParticleEmitter.h"
#include "../../Function/GlobalFunction.h"
#include "../Manager/CTimeManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CParticleEmitter::CParticleEmitter(const STParameters& a_rstParameters)
	:
	m_fSkipTime(1.0f / a_rstParameters.m_nNumParticlesPerSecond),
	m_stParameters(a_rstParameters)
{
	ZeroMemory(&m_stBoundingBox, sizeof(m_stBoundingBox));
}

std::vector<CParticleEmitter::STParticle> CParticleEmitter::getParticleList(void)
{
	return m_oParticleList;
}

void CParticleEmitter::setEmitEnable(bool a_bIsEmitEnable)
{
	m_bIsEmitEnable = a_bIsEmitEnable;
}

void CParticleEmitter::setParticleType(const EParticleType a_eParticleType)
{
	m_stParameters.m_eParticleType = a_eParticleType;
}

void CParticleEmitter::setBoundingBox(const STBoundingBox& a_rstBoundingBox)
{
	m_stBoundingBox = a_rstBoundingBox;
}

void CParticleEmitter::update(void)
{
	if(m_bIsEmitEnable)
	{
		this->createParticles();
	}

	this->updateParticles();
	this->removeParticles();
}

void CParticleEmitter::createParticles(void)
{
	m_fSkipTime += GET_DELTA_TIME();

	while(m_fSkipTime >= 1.0f / m_stParameters.m_nNumParticlesPerSecond)
	{
		m_fSkipTime -= 1.0f / m_stParameters.m_nNumParticlesPerSecond;

		// ��ƼŬ ������ ���� �� ���
		if(m_oParticleList.size() < m_stParameters.m_nMaxNumParticles)
		{
			STParticle stParticle;
			ZeroMemory(&stParticle, sizeof(stParticle));

			stParticle.m_bIsActive = true;

			stParticle.m_stStartColor = D3DXCOLOR(CreateFloatRandomValue(0.0f, 1.0f),
				CreateFloatRandomValue(0.0f, 1.0f),
				CreateFloatRandomValue(0.0f, 1.0f),
				1.0f);

			stParticle.m_stEndColor = D3DXCOLOR(CreateFloatRandomValue(0.0f, 1.0f),
				CreateFloatRandomValue(0.0f, 1.0f),
				CreateFloatRandomValue(0.0f, 1.0f),
				0.1f);

			stParticle.m_stAngleVelocity = D3DXVECTOR3(CreateFloatRandomValue(90.0f, 360.0f),
				CreateFloatRandomValue(90.0f, 360.0f),
				CreateFloatRandomValue(90.0f, 360.0f));

			if(m_stParameters.m_eParticleType == EParticleType::EXPLOSION ||
				m_stParameters.m_eParticleType == EParticleType::EXPLOSION_OUTLINE)
			{
				stParticle.m_fStartSize = CreateFloatRandomValue(1.0f, 2.5f);
				stParticle.m_fEndSize = CreateFloatRandomValue(2.0f, 4.0f);

				stParticle.m_fMaxActiveTime = CreateFloatRandomValue(1.0f, 2.0f);

				if(m_stParameters.m_eParticleType == EParticleType::EXPLOSION)
				{
					stParticle.m_stVelocity = D3DXVECTOR3(CreateFloatRandomValue(-1.0f, 1.0f),
						CreateFloatRandomValue(-1.0f, 1.0f),
						CreateFloatRandomValue(-1.0f, 1.0f));
				}
				else if(m_stParameters.m_eParticleType == EParticleType::EXPLOSION_OUTLINE)
				{
					stParticle.m_stPosition = D3DXVECTOR3(CreateFloatRandomValue(-1.0f, 1.0f),
						CreateFloatRandomValue(-1.0f, 1.0f),
						0.0f);

					stParticle.m_stVelocity = stParticle.m_stPosition - D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					D3DXVec3Normalize(&stParticle.m_stPosition, &stParticle.m_stPosition);
					D3DXVec3Normalize(&stParticle.m_stVelocity, &stParticle.m_stVelocity);

					stParticle.m_stPosition *= 1.5f;
				}
			}
			else if(m_stParameters.m_eParticleType == EParticleType::SNOW)
			{
				stParticle.m_fSize = CreateFloatRandomValue(0.5f, 1.5f);
				stParticle.m_fMaxActiveTime = CreateFloatRandomValue(3.0f, 6.0f);

				stParticle.m_stPosition = D3DXVECTOR3(CreateFloatRandomValue(m_stBoundingBox.m_stMinPosition.x, m_stBoundingBox.m_stMaxPosition.x),
					m_stBoundingBox.m_stMaxPosition.y,
					CreateFloatRandomValue(m_stBoundingBox.m_stMinPosition.z, m_stBoundingBox.m_stMaxPosition.z));

				stParticle.m_stVelocity = D3DXVECTOR3(CreateFloatRandomValue(-0.2f, 0.2f),
					-1.0f,
					CreateFloatRandomValue(-0.2f, 0.2f));
			}

			D3DXVec3Normalize(&stParticle.m_stVelocity, &stParticle.m_stVelocity);

			stParticle.m_stVelocity *= CreateFloatRandomValue(3.0f, 5.0f);
			m_oParticleList.push_back(stParticle);
		}
	}
}

void CParticleEmitter::updateParticles(void)
{
	for(auto& rstParticle : m_oParticleList)
	{
		rstParticle.m_fActiveTime += GET_DELTA_TIME();

		// Ȱ�� �ð��� ������ ���
		if(rstParticle.m_fActiveTime >= rstParticle.m_fMaxActiveTime)
		{
			rstParticle.m_bIsActive = false;
		}
		else
		{
			float fActiveTimeRate = rstParticle.m_fActiveTime / rstParticle.m_fMaxActiveTime;
			rstParticle.m_stPosition += rstParticle.m_stVelocity * GET_DELTA_TIME();
			rstParticle.m_stRotation += rstParticle.m_stAngleVelocity * GET_DELTA_TIME();

			rstParticle.m_fSize = rstParticle.m_fStartSize + (rstParticle.m_fEndSize - rstParticle.m_fStartSize) * GET_DELTA_TIME();
			D3DXColorLerp(&rstParticle.m_stColor, &rstParticle.m_stStartColor, &rstParticle.m_stEndColor, fActiveTimeRate);
		}
	}
}

void CParticleEmitter::removeParticles(void)
{
	auto oIterator = m_oParticleList.begin();

	while(oIterator != m_oParticleList.end())
	{
		if(oIterator->m_bIsActive)
		{
			++oIterator;
		}
		else
		{
			oIterator = m_oParticleList.erase(oIterator);
		}
	}
}
