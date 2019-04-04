#include "Sprite.h"

CSprite::CSprite()
{
	m_MyTexture = 0;
	m_AnimationAction = 0;
	m_SpriteEffect = ccSpriteEffect::None;
	m_Scale = 1.0f;
	m_Rotate = 0.0f;
}

CSprite::CSprite(const CSprite& Sprite)
{
	m_MyTexture = new CTexture(*Sprite.m_MyTexture);
	m_AnimationAction = new CAnimation(*Sprite.m_AnimationAction);
	m_Column = Sprite.m_Column;
	m_Row = Sprite.m_Row;
	m_Total = Sprite.m_Total;
	m_Scale = Sprite.m_Scale;
	m_Rotate = Sprite.m_Rotate;
	m_SpriteEffect = Sprite.m_SpriteEffect;
}

CSprite::~CSprite()
{
	this->Release();
}

void CSprite::Release()
{
	if (m_AnimationAction)
	{
		m_AnimationAction->Release();
		SAFE_DELETE(m_AnimationAction);
	}
}

void CSprite::LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, int Column, int Row, int Total, D3DXCOLOR TransparentColor)
{
	m_MyTexture = new CTexture();
	m_MyTexture->LoadTextureFromFile(_lpDirectDevice, fileName, TransparentColor);
	m_Column = Column;
	m_Row = Row;
	m_Total = Total;

	m_AnimationAction = new CAnimation(m_MyTexture->m_Width / Column, m_MyTexture->m_Height / Row, Column, Total);
}

void CSprite::UpdateAnimation(int timeAnimation)
{
	m_AnimationAction->UpdateAnimation(timeAnimation);
}

void CSprite::UpdateAnimationInverse(int timeAnimation)
{
	m_AnimationAction->UpdateAnimationInverse(timeAnimation);
}

CAnimation* CSprite::getAnimation()
{
	return m_AnimationAction;
}

void CSprite::Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color)
{
	D3DXVECTOR2 m_vOrigin = D3DXVECTOR2(position.x, position.y);
	if(m_MyTexture != 0)
	{
		if(effect == ccSpriteEffect::None)
		{
			m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
		}
		else
		{
			if(effect == ccSpriteEffect::Horizontally)
			{
				m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(-scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
			}
			else
			{
				if(effect == ccSpriteEffect::Vertically)
				{
					m_MyTexture->Render(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
				}
			}
		}
	}
}

void CSprite::RenderWithoutTransform(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color)
{
	D3DXVECTOR2 m_vOrigin = D3DXVECTOR2(position.x, position.y);
	if(m_MyTexture != 0)
	{
		if(effect == ccSpriteEffect::None)
		{
			m_MyTexture->RenderWithoutTransform(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
		}
		else
		{
			if(effect == ccSpriteEffect::Horizontally)
			{
				m_MyTexture->RenderWithoutTransform(spriteHandle, position, m_vOrigin, D3DXVECTOR2(-scale, -scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
			}
			else
			{
				if(effect == ccSpriteEffect::Vertically)
				{
					m_MyTexture->RenderWithoutTransform(spriteHandle, position, m_vOrigin, D3DXVECTOR2(scale, scale), rotateAngle, color, m_AnimationAction->getSourceRect(), deep);
				}
			}
		}
	}
}

void CSprite::RenderAtFrame(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color,int frameIndex)
{
	m_AnimationAction->setSourceRectAtIndex(frameIndex);

	Render(spriteHandle, position, effect, rotateAngle, scale, deep, color);
}