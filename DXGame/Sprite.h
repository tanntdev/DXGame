#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "Texture.h"
#include "Animation.h"
#include "DefaultContents.h"

class CSprite
{
private:

	CAnimation*			m_AnimationAction;
	CTexture*			m_MyTexture;

	int						m_Column;
	int						m_Row;
	int						m_Total;
	ccSpriteEffect			m_SpriteEffect;
	float					m_Scale;
	float					m_Rotate;

public:
	CAnimation*			getAnimationAction()const { return m_AnimationAction; }
	CTexture*			getMyTexture()const { return m_MyTexture; }
	ccSpriteEffect			getSpriteEffect()const { return m_SpriteEffect; }
	float					getRotate()const { return m_Rotate; }
	float					getScale()const { return m_Scale; }
	int						getColumn()const { return m_Column; }
	int						getRow()const { return m_Row; }
	int						getTotal()const { return m_Total; }
	void					setAnimationAction(CAnimation* _animationaction){ m_AnimationAction = _animationaction; }
	void					setColumn(int _column){ m_Column = _column; }
	void					setMyTexture(CTexture* _mytexture){ m_MyTexture = _mytexture; }
	void					setRotate(float _rotate){ m_Rotate = _rotate; }
	void					setRow(int _row){ m_Row = _row; }
	void					setScale(float _scale){ m_Scale = _scale; }
	void					setSpriteEffect(ccSpriteEffect _spriteeffect){ m_SpriteEffect = _spriteeffect; }
	void					setTotal(int _total){ m_Total = _total; }

							CSprite();
							CSprite(const CSprite& Sprite);
							~CSprite();
	CAnimation*			getAnimation();
	void					LoadContent(LPDIRECT3DDEVICE9 lpDirectDevice, LPCSTR fileName, int Column, int Row, int Total, D3DXCOLOR TransparentColor = 0xFFFF00FF);
	void					Release();
	void					Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffffffff);
	void					RenderWithoutTransform(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color = 0xffffffff);
	void					RenderAtFrame(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ccSpriteEffect effect, float rotateAngle, float scale, float deep, D3DCOLOR color, int frameIndex);
	void					UpdateAnimation(int timeAnimation);
	void					UpdateAnimationInverse(int timeAnimation);
};

#endif	__CSPRITE_H__