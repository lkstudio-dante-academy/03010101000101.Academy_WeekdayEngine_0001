#include "CCamera.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CDeviceManager.h"

CCamera::CCamera(float a_fAspect)
{
	this->setAspect(a_fAspect);
}

D3DXMATRIXA16 CCamera::getViewMatrix(void)
{
	return m_stViewMatrix;
}

D3DXMATRIXA16 CCamera::getProjectionMatrix(void)
{
	return m_stProjectionMatrix;
}

void CCamera::setAspect(float a_fAspect)
{
	D3DXMatrixPerspectiveFovLH(&m_stProjectionMatrix, D3DXToRadian(50.0f), a_fAspect, 0.1f, 1000.0f);
	GET_DEVICE()->SetTransform(D3DTS_PROJECTION, &m_stProjectionMatrix);
}

void CCamera::setFollowObject(CObject* a_pFollowObject, const D3DXVECTOR3& a_rstFollowOffset, EFollowType a_eFollowType)
{
	m_eFollowType = a_eFollowType;
	m_pFollowObject = a_pFollowObject;
	m_stFollowOffset = a_rstFollowOffset;
}

void CCamera::update(void)
{
	CObject::update();

	if(m_pFollowObject != nullptr)
	{
		auto stPosition = m_pFollowObject->getPosition();

		if(m_eFollowType == EFollowType::FIXED)
		{
			this->setPosition(stPosition + m_stFollowOffset);
			this->rotateByPosition(stPosition);
		}
		else
		{
			D3DXMATRIXA16 stRotation;
			D3DXMatrixIdentity(&stRotation);

			if(m_eFollowType == EFollowType::FREE)
			{
				auto stRightDirection = this->getRightDirection();
				auto stUpDirection = this->getUpDirection();
				auto stForwardDirection = this->getForwardDirection();

				CopyMemory(&stRotation(0, 0), &stRightDirection, sizeof(stRightDirection));
				CopyMemory(&stRotation(1, 0), &stUpDirection, sizeof(stUpDirection));
				CopyMemory(&stRotation(2, 0), &stForwardDirection, sizeof(stForwardDirection));
			}
			else
			{
				auto stRightDirection = m_pFollowObject->getRightDirection();
				auto stUpDirection = m_pFollowObject->getUpDirection();
				auto stForwardDirection = m_pFollowObject->getForwardDirection();

				CopyMemory(&stRotation(0, 0), &stRightDirection, sizeof(stRightDirection));
				CopyMemory(&stRotation(1, 0), &stUpDirection, sizeof(stUpDirection));
				CopyMemory(&stRotation(2, 0), &stForwardDirection, sizeof(stForwardDirection));
			}

			D3DXVECTOR3 stFollowOffset;
			D3DXVec3TransformCoord(&stFollowOffset, &m_stFollowOffset, &stRotation);

			this->setPosition(stPosition + stFollowOffset);
			this->rotateByPosition(stPosition);
		}
	}

	// �� ����� �����Ѵ�
	// {
	D3DXMatrixIdentity(&m_stViewMatrix);

	m_stViewMatrix(0, 0) = m_stRightDirection.x;
	m_stViewMatrix(1, 0) = m_stRightDirection.y;
	m_stViewMatrix(2, 0) = m_stRightDirection.z;
	m_stViewMatrix(3, 0) = -D3DXVec3Dot(&m_stPosition, &m_stRightDirection);

	m_stViewMatrix(0, 1) = m_stUpDirection.x;
	m_stViewMatrix(1, 1) = m_stUpDirection.y;
	m_stViewMatrix(2, 1) = m_stUpDirection.z;
	m_stViewMatrix(3, 1) = -D3DXVec3Dot(&m_stPosition, &m_stUpDirection);

	m_stViewMatrix(0, 2) = m_stForwardDirection.x;
	m_stViewMatrix(1, 2) = m_stForwardDirection.y;
	m_stViewMatrix(2, 2) = m_stForwardDirection.z;
	m_stViewMatrix(3, 2) = -D3DXVec3Dot(&m_stPosition, &m_stForwardDirection);

	GET_DEVICE()->SetTransform(D3DTS_VIEW, &m_stViewMatrix);
	// }
}
