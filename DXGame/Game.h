#ifndef __CGAME_H__
#define __CGAME_H__

#include "Camera.h"
#include "GameTime.h"
#include "DefineList.h"
#include "Input.h"
#include "Sprite.h"
#include "Surface.h"
#include "Texture.h"
#include "ContraScene.h"
#include "MenuScene.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "TestScene.h"
#include "HighscoreScene.h"
#include "LoseScene.h"
#include <d3d9.h>
#include <dsound.h>

// CGame

class CGame
{
private:
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT  message, WPARAM wParam, LPARAM lParam);

	HWND				m_handleWindow;
	LPD3DXSPRITE		m_lpSpriteDirect3DHandle;
	LPDIRECT3D9			m_lpDirect3D;
	LPDIRECT3DDEVICE9	m_lpDirect3DDevice;
	LPDIRECTSOUND8		m_lpDirectSound;

	bool				InitializeDirect3DDevice (bool isWindowed);
	bool				InitializeDirect3DEnvironment ();
	bool				InitializeDirect3DSpriteHandle ();
	bool				InitializeDirectSound();
	bool				InitializeHandleWindow (HINSTANCE);


	float				m_fps;

	char				fps[10];
public:

	CGame();

	CGame (HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode);

	bool Initialize(HINSTANCE handleInstance, bool isWindowed);

	void Load();

	void Run();

	void Exit();

	~CGame ();
};
#endif