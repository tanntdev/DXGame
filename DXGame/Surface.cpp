#include "Surface.h"

CSurface::CSurface()
{
	m_lpSurface = 0;
	m_lpBackBuffer = 0;
}
CSurface::CSurface(const CSurface& surface)
{
	m_lpSurface = LPDIRECT3DSURFACE9(surface.m_lpSurface);
	m_lpBackBuffer = LPDIRECT3DSURFACE9(surface.m_lpSurface);
}
CSurface::~CSurface()
{

}
void CSurface::UnLoadSurface()
{
	SAFE_RELEASE(m_lpSurface);
	SAFE_RELEASE(m_lpBackBuffer);
}
void CSurface::LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName)
{
	D3DXIMAGE_INFO _infoImage;
	HRESULT hr;

	hr = D3DXGetImageInfoFromFileA(fileName, &_infoImage);
	hr = _lpDirectDevice->CreateOffscreenPlainSurface(_infoImage.Width, _infoImage.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_lpSurface, 0);
	hr = D3DXLoadSurfaceFromFileA(
		m_lpSurface,
		0,
		0,
		fileName,
		0,
		D3DX_DEFAULT,
		ColorKey,
		0);
	hr = _lpDirectDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_lpBackBuffer);
}


void CSurface::RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT* SourceRect, RECT* DesRect)
{
	_lpDirectDevice->StretchRect(
		m_lpSurface,
		SourceRect,
		m_lpBackBuffer,
		DesRect,
		D3DTEXF_NONE);
}