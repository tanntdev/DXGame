#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "DefaultContents.h"
#include "DefineList.h"
#include "Camera.h"
class CTexture
{
private:	
	LPDIRECT3DTEXTURE9			m_lpTexture;
public:	
	int							m_Width;
	
	int							m_Height;
	
	CTexture();
	
	CTexture(const CTexture& Texture);
	
	~CTexture();
	
	void LoadTextureFromFile(LPDIRECT3DDEVICE9 _lpDirectdevice, LPCSTR fileName, D3DXCOLOR ColorKey = 0xffff00ff);
	
	void RenderTexture(LPD3DXSPRITE _lpDSpriteHandle, const RECT* sourceRect, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, D3DCOLOR Color = 0xFFFFFFFF);

	void Render(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR2 position, D3DXVECTOR2 Center, D3DXVECTOR2 scale, float angle, D3DCOLOR color, RECT *srcRect, float deep);

	void RenderWithoutTransform(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR2 position, D3DXVECTOR2 Center, D3DXVECTOR2 scale, float angle, D3DCOLOR color, RECT *srcRect, float deep);

	void UnLoadTexture();
};

#endif  __CTEXTURE_H__