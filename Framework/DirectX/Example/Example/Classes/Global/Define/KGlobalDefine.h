#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <random>
#include <tuple>
#include <numeric>
#include <future>
#include <cassert>
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>

#define NUM_DIRECTIONS						(3)
#define NAME_DEFAULT_SHADOW_MESH			("DefaultShadowMesh")

// ����
// {
#define WORLD_RIGHT_DIRECTION			(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
#define WORLD_UP_DIRECTION				(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define WORLD_FORWARD_DIRECTION			(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
// }

// ����
// {
#define GET_TIME_MANAGER()					(CTimeManager::getInstance())
#define GET_INPUT_MANAGER()					(CInputManager::getInstance())
#define GET_SOUND_MANAGER()					(CSoundManager::getInstance())
#define GET_WINDOW_MANAGER()				(CWindowManager::getInstance())
#define GET_DEVICE_MANAGER()				(CDeviceManager::getInstance())
#define GET_RESOURCE_MANAGER()				(CResourceManager::getInstance())
#define GET_SCHEDULE_MANAGER()				(CScheduleManager::getInstance())
#define GET_SCENE_MANAGER()					(CSceneManager::getInstance())
#define GET_UI_MANAGER()					(CUIManager::getInstance())

#define GET_WINDOW_APPLICATION()			(CWindowApplication::getInstance())
#define GET_DIRECT3D_APPLICATION()			(static_cast<CDirect3DApplication *>(GET_WINDOW_APPLICATION()))

#define GET_LIGHT()						(GET_DIRECT3D_APPLICATION()->getLight())
#define GET_CAMERA()					(GET_DIRECT3D_APPLICATION()->getCamera())
#define GET_SPRITE()					(GET_DIRECT3D_APPLICATION()->getSprite())
#define GET_MOUSE_WHEEL()				(GET_INPUT_MANAGER()->getMouseWheel())
#define GET_MOUSE_POSITION()			(GET_INPUT_MANAGER()->getMousePosition())

#define GET_FPS()					(GET_TIME_MANAGER()->getFPS())
#define GET_DELTA_TIME()			(GET_TIME_MANAGER()->getDeltaTime())
#define GET_RUNNING_TIME()			(GET_TIME_MANAGER()->getRunningTime())

#define GET_WINDOW_SIZE()				(GET_WINDOW_MANAGER()->getWindowSize())
#define GET_WINDOW_HANDLE()				(GET_WINDOW_MANAGER()->getWindowHandle())
#define GET_INSTANCE_HANDLE()			(GET_WINDOW_MANAGER()->getInstanceHandle())

#define GET_DEVICE()				(GET_DEVICE_MANAGER()->getDevice())
#define GET_DIRECT3D()				(GET_DEVICE_MANAGER()->getDirect3D())
#define GET_DIRECT_INPUT()			(GET_INPUT_MANAGER()->getDirectInput())
#define GET_DIRECT_SOUND()			(GET_SOUND_MANAGER()->getDirectSound())

#define GET_MESH(FILEPATH)						(GET_RESOURCE_MANAGER()->getMeshForKey((FILEPATH)))
#define GET_STATIC_MESH(FILEPATH)				(GET_RESOURCE_MANAGER()->getStaticMeshForKey((FILEPATH)))
#define GET_SKINNED_MESH(FILEPATH)				(GET_RESOURCE_MANAGER()->getSkinnedMeshForKey((FILEPATH)))
#define GET_EFFECT(FILEPATH)					(GET_RESOURCE_MANAGER()->getEffectForKey((FILEPATH)))
#define GET_TEXTURE(FILEPATH)					(GET_RESOURCE_MANAGER()->getTextureForKey((FILEPATH)))
#define GET_SPRITE_TEXTURE(FILEPATH)			(GET_RESOURCE_MANAGER()->getSpriteTextureForKey((FILEPATH)))
#define GET_CUBE_TEXTURE(FILEPATH)				(GET_RESOURCE_MANAGER()->getCubeTextureForKey((FILEPATH)))
#define GET_WAVE_SOUND(FILEPATH)				(GET_RESOURCE_MANAGER()->getWaveSoundForKey((FILEPATH)))
// }

// ����
#define CREATE_LABEL(STRING, FONT_SIZE)				(GET_UI_MANAGER()->createLabel((STRING), (FONT_SIZE)))
#define CREATE_BUTTON(FILEPATH, CALLBACK)			(GET_UI_MANAGER()->createButton((FILEPATH), (CALLBACK)))
#define CREATE_SPRITE(FILEPATH)						(GET_UI_MANAGER()->createSprite((FILEPATH)))

// ����
// {
#define SAFE_FREE(TARGET)					if((TARGET) != nullptr) { free((TARGET)); (TARGET) = nullptr; }
#define SAFE_CLOSE(TARGET)					if((TARGET) != nullptr) { fclose((TARGET)); (TARGET) = nullptr; }
#define SAFE_DELETE(TARGET)					if((TARGET) != nullptr) { delete (TARGET); (TARGET) = nullptr; }
#define SAFE_DELETE_ARRAY(TARGET)			if((TARGET) != nullptr) { delete[] (TARGET); (TARGET) = nullptr; }

#define SAFE_RELEASE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Release(); (TARGET) = nullptr; }
#define SAFE_UNACQUIRE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Unacquire(); SAFE_RELEASE((TARGET)); }
// }

// Ű���� �Է�
#define IS_KEY_DOWN(KEY_CODE)				(GET_INPUT_MANAGER()->isKeyDown((KEY_CODE)))
#define IS_KEY_PRESSED(KEY_CODE)			(GET_INPUT_MANAGER()->isKeyPressed((KEY_CODE)))
#define IS_KEY_RELEASED(KEY_CODE)			(GET_INPUT_MANAGER()->isKeyReleased((KEY_CODE)))

// ���콺 �Է�
#define IS_MOUSE_BUTTON_DOWN(MOUSE_BUTTON)				(GET_INPUT_MANAGER()->isMouseButtonDown((MOUSE_BUTTON)))
#define IS_MOUSE_BUTTON_PRESSED(MOUSE_BUTTON)			(GET_INPUT_MANAGER()->isMouseButtonPressed((MOUSE_BUTTON)))
#define IS_MOUSE_BUTTON_RELEASED(MOUSE_BUTTON)			(GET_INPUT_MANAGER()->isMouseButtonReleased((MOUSE_BUTTON)))

// ����
// {
#define PLAY_EFFECT_SOUND(FILEPATH)					(GET_SOUND_MANAGER()->playEffectSound((FILEPATH)))
#define PAUSE_EFFECT_SOUND(EFFECT_SOUND)			(GET_SOUND_MANAGER()->pauseEffectSound((EFFECT_SOUND)))
#define STOP_EFFECT_SOUND(EFFECT_SOUND)				(GET_SOUND_MANAGER()->stopEffectSound((EFFECT_SOUND)))

#define PLAY_ALL_EFFECT_SOUNDS()			(GET_SOUND_MANAGER()->playAllEffectSounds())
#define PAUSE_ALL_EFFECT_SOUNDS()			(GET_SOUND_MANAGER()->pauseAllEffectSounds())
#define STOP_ALL_EFFECT_SOUNDS()			(GET_SOUND_MANAGER()->stopAllEffectSounds())

#define PLAY_BACKGROUND_SOUND(FILEPATH)			(GET_SOUND_MANAGER()->playBackgroundSound((FILEPATH)))
#define PAUSE_BACKGROUND_SOUND()				(GET_SOUND_MANAGER()->pauseBackgroundSound())
#define STOP_BACKGROUND_SOUND()					(GET_SOUND_MANAGER()->stopBackgroundSound())
// }

//! �̱���
// {
#define DECLARE_SINGLETON(CLASS_NAME)			\
public:											\
static CLASS_NAME * getInstance(void) {			\
	static CLASS_NAME oInstance;				\
	return &oInstance;							\
}
// }

//! ����
enum class EDirection
{
	RIGHT,
	UP,
	FORWARD,
	NONE
};

//! ���콺 ��ư
enum class EMouseButton
{
	LEFT,
	RIGHT,
	MIDDLE,
	NONE
};

//! �ֽ� Ÿ��
enum class EFollowType
{
	FREE,
	FIXED,
	ROTATION,
	NONE
};

//! ��ƼŬ Ÿ��
enum class EParticleType
{
	EXPLOSION,
	EXPLOSION_OUTLINE,
	SNOW,
	NONE
};

//! �׸��� Ÿ��
enum class EShadowType
{
	CIRCLE,
	PROJECTION,
	NONE
};

//! ����� Ÿ��
enum class EDebugDrawType
{
	BOX,
	SPHERE,
	NONE
};

//! ����
struct STRay
{
	D3DXVECTOR3 m_stOrigin;
	D3DXVECTOR3 m_stDirection;
};

//! �� ���� ��� ����
struct STBoundingBox
{
	D3DXVECTOR3 m_stMinPosition;
	D3DXVECTOR3 m_stMaxPosition;
};

//! ��ü ��� ����
struct STObjectBoundingBox
{
	float m_afHelfLengths[NUM_DIRECTIONS];

	D3DXVECTOR3 m_astDirections[NUM_DIRECTIONS];
	D3DXVECTOR3 m_stCenterPosition;
};

//! ��� ��
struct STBoundingSphere
{
	float m_fRadius;
	D3DXVECTOR3 m_stCenterPosition;
};

//! ���� �޽�
struct STStaticMesh
{
	DWORD m_nNumMaterials;

	LPD3DXMESH m_pMesh;
	std::vector<D3DMATERIAL9> m_oMaterialList;
	std::vector<LPDIRECT3DTEXTURE9> m_oTextureList;
};

//! ��Ų�� �޽�
struct STSkinnedMesh
{
	DWORD m_nNumBlends;
	LPD3DXMESH m_pMesh;

	DWORD* m_pnAdjacency;
	std::vector<D3DXBONECOMBINATION> m_oBoneCombinationList;
};

//! ���̺� ����
struct STWaveSound
{
	BYTE* m_pnBytes;

	DWORD m_nNumBytes;
	WAVEFORMATEX m_stWaveFormat;
};
