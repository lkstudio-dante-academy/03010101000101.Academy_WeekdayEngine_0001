#include "CSprite.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"

CSprite::CSprite(const std::string& a_rFilepath)
	:
	m_oFilepath(a_rFilepath)
{
	// Do Nothing
}

void CSprite::init(void)
{
	CUIObject::init();
	m_pTexture = GET_SPRITE_TEXTURE(m_oFilepath);

	D3DSURFACE_DESC stSurfaceDesc;
	m_pTexture->GetLevelDesc(0, &stSurfaceDesc);

	m_stTextureSize.cx = stSurfaceDesc.Width;
	m_stTextureSize.cy = stSurfaceDesc.Height;
}

SIZE CSprite::getSize(void)
{
	return m_stTextureSize;
}

void CSprite::doDrawUI(void)
{
	CUIObject::doDrawUI();

	RECT stTextureRect = {
		0, 0, m_stTextureSize.cx, m_stTextureSize.cy
	};

	auto stWorldMatrix = this->getFinalWorldMatrix();
	GET_SPRITE()->SetTransform(&stWorldMatrix);

	GET_SPRITE()->Draw(m_pTexture,
		&stTextureRect,
		&D3DXVECTOR3(stTextureRect.right / 2.0f, stTextureRect.bottom / 2.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		m_stColor);
}
