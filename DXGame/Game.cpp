#include "Game.h"
#include <time.h>


CGame::CGame() :
	m_handleWindow(0),
	m_lpDirect3D(0),
	m_lpDirect3DDevice(0),
	m_lpSpriteDirect3DHandle(0)
{
	srand((unsigned int)time(0));
}

CGame::CGame(HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode)
{

}

CGame::~CGame()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)
	SAFE_DELETE(m_handleWindow)
}

bool CGame::InitializeHandleWindow(HINSTANCE hInstance)
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbClsExtra		= 0;
	WndcEx.cbSize			= sizeof(WNDCLASSEX);
	WndcEx.cbWndExtra		= 0;
	WndcEx.hbrBackground	= (HBRUSH)COLOR_BACKGROUND;
	WndcEx.hCursor			= LoadCursor(0, IDC_ARROW);
	WndcEx.hIcon			= 0;
	WndcEx.hIconSm			= 0;
	WndcEx.hInstance		= hInstance;
	WndcEx.lpfnWndProc		= (WNDPROC)WndProceduce;
	WndcEx.lpszClassName	= "CGame";
	WndcEx.lpszMenuName		= 0;
	WndcEx.style			= 0;

   int horizontal = GetSystemMetrics(SM_CXSCREEN);
   int vertical = GetSystemMetrics(SM_CYSCREEN);

	m_handleWindow = CreateWindowA(
		"CGame",
		GAMETITLE,
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		(horizontal - SCREEN_WIDTH)/2,
		(vertical - SCREEN_HEIGHT)/2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0,
		0,
		hInstance,
		0);

	ShowWindow(m_handleWindow, SW_SHOW);
	UpdateWindow(m_handleWindow);
	return true;
}

bool CGame::InitializeDirect3DEnvironment()
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	return true;
}

bool CGame::InitializeDirect3DDevice(bool isWindowed)
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	if (isWindowed)
	{
		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.BackBufferHeight	= SCREEN_HEIGHT;
		d3dpp.BackBufferWidth	= SCREEN_WIDTH;
		d3dpp.Windowed			= true;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	}
	else
	{
		D3DDISPLAYMODE DisPlayMode;
		ZeroMemory(&DisPlayMode, sizeof(DisPlayMode));
		m_lpDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisPlayMode);
		HRESULT handleResult;
		handleResult = m_lpDirect3D->CheckDeviceFormat(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			DisPlayMode.Format,
			D3DUSAGE_RENDERTARGET,
			D3DRTYPE_SURFACE,
			D3DFMT_A8R8G8B8);
		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.Windowed			= false;
		d3dpp.BackBufferWidth	= DisPlayMode.Width;
		d3dpp.BackBufferHeight	= DisPlayMode.Height;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	}
	m_lpDirect3D->CreateDevice(
			  D3DADAPTER_DEFAULT,
			  D3DDEVTYPE_HAL,
			  m_handleWindow,
			  D3DCREATE_HARDWARE_VERTEXPROCESSING,
			  &d3dpp,
			  &m_lpDirect3DDevice);
	return true;
}

bool CGame::InitializeDirect3DSpriteHandle()
{
	D3DXCreateSprite(m_lpDirect3DDevice, &m_lpSpriteDirect3DHandle);
	HRESULT hr;
	hr = !FAILED(m_lpSpriteDirect3DHandle);
	return true;
}

bool CGame::InitializeDirectSound()
{
	HRESULT hr;
	hr = DirectSoundCreate8(0, &m_lpDirectSound, 0);
	
	hr = m_lpDirectSound->SetCooperativeLevel(this->m_handleWindow, DSSCL_PRIORITY);
	return true;
}

#include "PlayScene.h"
bool CGame::Initialize(HINSTANCE hInstance, bool isWindowed)
{
	SetWindowTextA(m_handleWindow, "CONTRA GAME");


	this->InitializeHandleWindow(hInstance);
	this->InitializeDirect3DEnvironment();
	this->InitializeDirect3DDevice(isWindowed);
	this->InitializeDirect3DSpriteHandle();
	this->InitializeDirectSound();
	CGameTime::getInstance()->InitGameTime();
	this->m_fps = 0;


	CInput::getInstance()->InitializeInput();
	CInput::getInstance()->InitializeMouseDevice(m_handleWindow);
	CInput::getInstance()->InitializeKeyBoardDevice(m_handleWindow);
	SpriteManager::getInstance()->InitializeListSprite(m_lpDirect3DDevice);

	SoundManager::getInstance()->LoadAllSoundBuffer(m_lpDirectSound);

	SceneManager::getInstance()->setDirectDevice(m_lpDirect3DDevice);

	SceneManager::getInstance()->AddElement(new PlayScene(ccSceneID::COTRASCENE, 1));
	return true;
}

void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(!CGlobal::IsExit)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(CInput::getInstance()->IsKeyPress(DIK_ESCAPE))
			{
				PostMessage(m_handleWindow, WM_QUIT, 0, 0);
			}

			CInput::getInstance()->UpdateKeyBoard();

			CGameTime::getInstance()->UpdateGameTime();

			m_fps += CGameTime::getInstance()->getElapsedGameTime().getMilliseconds();

			static int second;
			second += CGameTime::getInstance()->getElapsedGameTime().getMilliseconds();

			if( m_fps >= 1000 / 60)
			{
				sprintf(fps, "FPS: %.3f \n", 1000.0 / m_fps);
				
				SceneManager::getInstance()->HandleInput();
				SceneManager::getInstance()->Update();

				m_lpDirect3DDevice->Clear(0 , 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

				if(m_lpDirect3DDevice->BeginScene())
				{
					D3DXMATRIX oldMatrix;
				
					m_lpSpriteDirect3DHandle->GetTransform(&oldMatrix);
					m_lpSpriteDirect3DHandle->SetTransform(&Camera::getInstance()->GetMatrixTranslate());
					m_lpSpriteDirect3DHandle->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

					SceneManager::getInstance()->Render(m_lpSpriteDirect3DHandle);
					
					m_lpSpriteDirect3DHandle->SetTransform(&oldMatrix);

					m_lpSpriteDirect3DHandle->End();
					m_lpDirect3DDevice->EndScene();
				}
				m_lpDirect3DDevice->Present(0, 0, 0, 0);
				m_fps = 0;
			}
		}
	}
}

void CGame::Exit()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)

	CInput::getInstance()->Release();
	SoundManager::getInstance()->Release();
	SpriteManager::getInstance()->Release();
	SceneManager::getInstance()->ClearAll();
}

LRESULT CALLBACK CGame::WndProceduce(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message,wParam, lParam);
}