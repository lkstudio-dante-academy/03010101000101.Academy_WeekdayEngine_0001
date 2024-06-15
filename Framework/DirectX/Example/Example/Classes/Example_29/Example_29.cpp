#include "Example_29.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Object/CSkinnedMesh.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_29::Example_29(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_29::~Example_29(void)
{
	for(auto pSkinnedMesh : m_oSkinnedMeshList)
	{
		SAFE_DELETE(pSkinnedMesh);
	}

	SAFE_DELETE(m_pSkinnedMesh);
}

void Example_29::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pSkinnedMesh = this->createSkinnedMesh();
	m_pSkinnedMesh->setScale(D3DXVECTOR3(0.15f, 0.15f, 0.15f));

	auto oAnimationNameList = m_pSkinnedMesh->getAnimationNameList();
	m_pSkinnedMesh->playAnimation(oAnimationNameList[0], true);
}

void Example_29::update(void)
{
	CDirect3DApplication::update();
	auto oAnimationNameList = m_pSkinnedMesh->getAnimationNameList();

	if(IS_KEY_DOWN(DIK_1))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[0], true);
	}
	else if(IS_KEY_DOWN(DIK_2))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[1], true);
	}
	else if(IS_KEY_DOWN(DIK_3))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[2], true);
	}
	else if(IS_KEY_DOWN(DIK_4))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[3], true);
	}
	else if(IS_KEY_DOWN(DIK_5))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[4], true);
	}
	else if(IS_KEY_PRESSED(DIK_SPACE))
	{
		auto pSkinnedMesh = this->createSkinnedMesh();
		pSkinnedMesh->setScale(D3DXVECTOR3(0.15f, 0.15f, 0.15f));

		pSkinnedMesh->setPosition(D3DXVECTOR3(CreateIntRandomValue(-25.0f, 25.0f),
			0.0f,
			CreateIntRandomValue(-25.0f, 25.0f)));

		int nIndex = CreateIntRandomValue(0, oAnimationNameList.size() - 1);
		pSkinnedMesh->playAnimation(oAnimationNameList[nIndex], true);

		m_oSkinnedMeshList.push_back(pSkinnedMesh);
	}

	for(auto pSkinnedMesh : m_oSkinnedMeshList)
	{
		pSkinnedMesh->update();
	}

	m_pSkinnedMesh->update();
}

void Example_29::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	for(auto pSkinnedMesh : m_oSkinnedMeshList)
	{
		pSkinnedMesh->draw();
	}

	m_pSkinnedMesh->draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

CSkinnedMesh* Example_29::createSkinnedMesh(void)
{
	CSkinnedMesh::STParameters stParameters = {
		"Resources/Meshes/WitchApprentice/WitchApprentice.x",
		"Resources/Effects/Example_29.fx",
		"Dummy_root"
	};

	return CreateObject<CSkinnedMesh>(stParameters);
}
