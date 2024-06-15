#include "Example_34.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CLight.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Object/CTerrain.h"
#include "../Global/Utility/Object/CSkinnedMesh.h"
#include "../Global/Utility/Manager/CTimeManager.h"
#include "../Global/Utility/Manager/CInputManager.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

#define SHADOW_TYPE_CIRCLE				1
#define SHADOW_TYPE_PROJECTION			2

#define SHADOW_TYPE			SHADOW_TYPE_PROJECTION

Example_34::Example_34(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_34::~Example_34(void)
{
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pSkinnedMesh);
}

void Example_34::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pTerrain = this->createTerrain();

	m_pSkinnedMesh = this->createSkinnedMesh();
	m_pSkinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	m_pSkinnedMesh->setTerrain(m_pTerrain);
	m_pSkinnedMesh->setDebugEnable(true);

#if SHADOW_TYPE == SHADOW_TYPE_CIRCLE
	m_pSkinnedMesh->setShadowEnable(true, EShadowType::CIRCLE);
#elif SHADOW_TYPE == SHADOW_TYPE_PROJECTION
	m_pSkinnedMesh->setShadowEnable(true, EShadowType::PROJECTION);
#endif			// #if SHADOW_TYPE == SHADOW_TYPE_PROJECTION

	auto oAnimationNameList = m_pSkinnedMesh->getAnimationNameList();
	m_pSkinnedMesh->playAnimation(oAnimationNameList[0], true);

	GET_CAMERA()->setFollowObject(m_pSkinnedMesh, D3DXVECTOR3(0.0f, 0.0f, -25.0f));
}

void Example_34::update(void)
{
	CDirect3DApplication::update();

	m_pTerrain->update();
	m_pSkinnedMesh->update();

	auto oAnimationNameList = m_pSkinnedMesh->getAnimationNameList();

	if(IS_MOUSE_BUTTON_PRESSED(EMouseButton::LEFT))
	{
		auto stRay = CreateRay(GET_MOUSE_POSITION());
	}

	if(IS_KEY_PRESSED(DIK_LEFT) || IS_KEY_PRESSED(DIK_RIGHT))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[2], true);
	}
	else if(IS_KEY_RELEASED(DIK_LEFT) || IS_KEY_RELEASED(DIK_RIGHT))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[0], true);
	}

	if(IS_KEY_DOWN(DIK_LEFT))
	{
		m_pSkinnedMesh->moveByXAxis(-20.0f * GET_DELTA_TIME(), false);
		m_pSkinnedMesh->setRotation(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	}
	else if(IS_KEY_DOWN(DIK_RIGHT))
	{
		m_pSkinnedMesh->moveByXAxis(20.0f * GET_DELTA_TIME(), false);
		m_pSkinnedMesh->setRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if(IS_KEY_PRESSED(DIK_SPACE))
	{
		m_pSkinnedMesh->playAnimation(oAnimationNameList[4]);
	}

	D3DXVECTOR3 stPosition = m_pSkinnedMesh->getPosition();
	stPosition.y = m_pTerrain->getHeightAtPosition(stPosition);

	m_pSkinnedMesh->setPosition(stPosition);

#if SHADOW_TYPE == SHADOW_TYPE_CIRCLE
	D3DXMATRIXA16 stShadowMatrix;
	D3DXMatrixScaling(&stShadowMatrix, 20.0f, 0.1f, 20.0f);

	m_pSkinnedMesh->setShadowMatrix(stShadowMatrix);
#elif SHADOW_TYPE == SHADOW_TYPE_PROJECTION
	float fHeight = m_pTerrain->getHeightAtPosition(stPosition);
	D3DXVECTOR4 stLightPosition(GET_LIGHT()->getPosition(), 0.0f);

	D3DXPLANE stPlane;
	D3DXPlaneFromPointNormal(&stPlane, &D3DXVECTOR3(0.0f, fHeight, 0.0f), &WORLD_UP_DIRECTION);

	D3DXMATRIXA16 stShadowMatrix;
	D3DXMatrixShadow(&stShadowMatrix, &stLightPosition, &stPlane);

	m_pSkinnedMesh->setShadowMatrix(stShadowMatrix);
#endif			// #if SHADOW_TYPE == SHADOW_TYPE_PROJECTION
}

void Example_34::draw(void)
{
	CDirect3DApplication::draw();

	m_pTerrain->draw();
	m_pSkinnedMesh->draw();
}

CTerrain* Example_34::createTerrain(void)
{
	CTerrain::STParameters stParameters = {
		0,
		0.0025f,
		"Resources/Effects/Example_28.fx",
		"Resources/Textures/HeightMap.raw",
		"Resources/Textures/SplatMap.jpg"
	};

	stParameters.m_stMapSize.cx = 513;
	stParameters.m_stMapSize.cy = 513;

	stParameters.m_stTileSize.cx = 1;
	stParameters.m_stTileSize.cy = 1;

	for(int i = 0; i < CTerrain::MAX_NUM_TEXTURES; ++i)
	{
		char szTextureFilepath[MAX_PATH] = "";
		sprintf(szTextureFilepath, "Resources/Textures/Terrain_%02d.jpg", i + 1);

		stParameters.m_oTextureFilepathList[i] = szTextureFilepath;
	}

	return CreateObject<CTerrain>(stParameters);
}

CSkinnedMesh* Example_34::createSkinnedMesh(void)
{
	CSkinnedMesh::STParameters stParameters = {
		"Resources/Meshes/WitchApprentice/WitchApprentice.x",
		"Resources/Effects/Example_29.fx",
		"Dummy_root"
	};

	return CreateObject<CSkinnedMesh>(stParameters);
}
