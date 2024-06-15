#include "CAnimationController.h"
#include "../Manager/CTimeManager.h"

CAnimationController::CAnimationController(LPD3DXANIMATIONCONTROLLER a_pAnimationController)
	:
	m_fTimeScale(1.0f),
	m_pAnimationController(a_pAnimationController)
{
	int nNumAnimationSets = a_pAnimationController->GetNumAnimationSets();

	for(int i = 0; i < nNumAnimationSets; ++i)
	{
		LPD3DXANIMATIONSET pAnimationSet = nullptr;
		a_pAnimationController->GetAnimationSet(i, &pAnimationSet);

		std::string oAnimationName = pAnimationSet->GetName();

		m_oAnimationNameList.push_back(oAnimationName);
		m_oAnimationSetList.insert(decltype(m_oAnimationSetList)::value_type(oAnimationName, pAnimationSet));
	}
}

CAnimationController::~CAnimationController(void)
{
	for(auto& rValueType : m_oAnimationSetList)
	{
		SAFE_RELEASE(rValueType.second);
	}

	SAFE_RELEASE(m_pAnimationController);
}

void CAnimationController::update(void)
{
	if(m_bIsPlaying)
	{
		float fDeltaTime = m_fTimeScale * GET_DELTA_TIME();

		// ���� �ִϸ��̼��� ���� ���
		if(m_pNextAnimationSet != nullptr)
		{
			m_fLeftMixedTime -= fDeltaTime;

			// �ִϸ��̼��� ��ȯ �� �� ���
			if(m_fLeftMixedTime > 0.0f)
			{
				float fWeightA = m_fLeftMixedTime / m_fMixedTime;
				float fWeightB = 1.0f - fWeightA;

				m_pAnimationController->SetTrackWeight(0, fWeightA);
				m_pAnimationController->SetTrackWeight(1, fWeightB);
			}
			else
			{
				bool bIsLoop = m_bIsLoop;
				auto pAnimationSet = m_pNextAnimationSet;

				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(1, &stTrackDesc);

				this->stopAnimation();
				this->doPlayAnimation(pAnimationSet, bIsLoop);

				m_pAnimationController->SetTrackPosition(0, stTrackDesc.Position);
				m_pAnimationController->SetTrackAnimationSet(0, pAnimationSet);
			}

			m_pAnimationController->AdvanceTime(fDeltaTime, NULL);
		}
		else
		{
			D3DXTRACK_DESC stTrackDesc;
			m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

			float fPercent = stTrackDesc.Position / m_pAnimationSet->GetPeriod();

			// �ִϸ��̼��� ���� �� �� ���
			if(m_bIsLoop || fPercent <= 1.0f)
			{
				m_pAnimationController->AdvanceTime(fDeltaTime, NULL);
			}
			else
			{
				this->stopAnimation();
			}
		}
	}
}

std::vector<std::string> CAnimationController::getAnimationNameList(void)
{
	return m_oAnimationNameList;
}

void CAnimationController::setTimeScale(float a_fTimeScale)
{
	m_fTimeScale = a_fTimeScale;
}

void CAnimationController::playAnimation(const std::string& a_rAnimationName, bool a_bIsLoop)
{
	auto oIterator = m_oAnimationSetList.find(a_rAnimationName);

	if(oIterator != m_oAnimationSetList.end())
	{
		this->doPlayAnimation(oIterator->second, a_bIsLoop);
	}
}

void CAnimationController::stopAnimation(void)
{
	m_bIsLoop = false;
	m_bIsPlaying = false;
	m_pAnimationSet = nullptr;
	m_pNextAnimationSet = nullptr;

	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(0, NULL);

	m_pAnimationController->SetTrackEnable(1, false);
	m_pAnimationController->SetTrackPosition(1, 0.0f);
	m_pAnimationController->SetTrackAnimationSet(1, NULL);
}

void CAnimationController::doPlayAnimation(LPD3DXANIMATIONSET a_pAnimationSet, bool a_bIsLoop)
{
	if(!m_bIsPlaying)
	{
		m_pAnimationSet = a_pAnimationSet;
		m_pNextAnimationSet = nullptr;

		m_pAnimationController->SetTrackWeight(0, 1.0f);
		m_pAnimationController->SetTrackPosition(0, 0.0f);
		m_pAnimationController->SetTrackAnimationSet(0, m_pAnimationSet);
	}
	else if(m_pNextAnimationSet != a_pAnimationSet)
	{
		m_fMixedTime = 0.15f;
		m_pNextAnimationSet = a_pAnimationSet;

		// ���� �ִϸ��̼ǰ� �ٸ� ���
		if(m_pAnimationSet != a_pAnimationSet)
		{
			m_fLeftMixedTime = m_fMixedTime;

			m_pAnimationController->SetTrackWeight(1, 0.0f);
			m_pAnimationController->SetTrackPosition(1, 0.0f);
		}
		else
		{
			// �ִϸ��̼��� ��ȯ �� �� ���
			if(m_fLeftMixedTime > 0.0f)
			{
				m_pAnimationController->SetTrackPosition(1, 0.0f);
			}
			else
			{
				D3DXTRACK_DESC stTrackDesc;
				m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

				m_pAnimationController->SetTrackPosition(1, stTrackDesc.Position);
			}

			m_fLeftMixedTime = 0.0f;
			m_pAnimationController->SetTrackWeight(1, 1.0f);
		}

		m_pAnimationController->SetTrackEnable(1, true);
		m_pAnimationController->SetTrackAnimationSet(1, m_pNextAnimationSet);
	}

	m_bIsLoop = a_bIsLoop;
	m_bIsPlaying = true;
}
