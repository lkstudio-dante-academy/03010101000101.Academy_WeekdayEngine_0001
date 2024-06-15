#include "Example_28.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Object/CTerrain.h"
#include "../Global/Utility/Manager/CDeviceManager.h"

Example_28::Example_28(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_28::~Example_28(void)
{
	SAFE_DELETE(m_pTerrain);
}

void Example_28::initApplication(void)
{
	CDirect3DApplication::initApplication();
	m_pTerrain = this->createTerrain();
}

void Example_28::update(void)
{
	CDirect3DApplication::update();
	m_pTerrain->update();

	auto stCameraPosition = GET_CAMERA()->getPosition();
	stCameraPosition.y = m_pTerrain->getHeightAtPosition(stCameraPosition) + 10.0f;

	GET_CAMERA()->setPosition(stCameraPosition);
}

void Example_28::draw(void)
{
	CDirect3DApplication::draw();
	m_pTerrain->draw();
}

CTerrain* Example_28::createTerrain(void)
{
	CTerrain::STParameters stParameters = {
		5,
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
