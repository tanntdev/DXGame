#ifndef __CSURFACE_H__
#define __CSURFACE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "DefineList.h"

class CSurface
{
private:
	
	LPDIRECT3DSURFACE9		m_lpSurface;
	
	LPDIRECT3DSURFACE9		m_lpBackBuffer;
public:
	
	CSurface();
	
	CSurface(const CSurface& surface);
	
	~CSurface();
	
	
	
	void LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName);
	
	
	
	void RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT* SourceRect, RECT* DesRect);
	
	void UnLoadSurface();
};

#endif __CSURFACE_H__