#include "SceneManager.h"

SceneManager* SceneManager::s_Instance = 0;

SceneManager* SceneManager::getInstance()
{
	if( !s_Instance )
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

void SceneManager::setDirectDevice(const LPDIRECT3DDEVICE9& _lpDirectDevice)
{
	this->m_lpDirectDevice = _lpDirectDevice;
}

void SceneManager::Initialize()
{
	if( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->InitializeState(m_lpDirectDevice);
	}
}

void SceneManager::AddElement(GameScene* GameScene)
{
	if(!m_ListGameScene.empty())
	{
		m_ListGameScene[m_ListGameScene.size() - 1]->Pause();
	}
	m_ListGameScene.push_back(GameScene);
	m_ListGameScene.back()->InitializeState(m_lpDirectDevice);
}

void SceneManager::HandleInput()
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->HandleInput();
	}
}
void SceneManager::Update()
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->Update();
	}
}
void SceneManager::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	if ( !m_ListGameScene.empty() )
	{
		m_ListGameScene.back()->Render(_lpDSpriteHandle);
	}
}
void SceneManager::ExitState()
{
	if( !m_ListGameScene.empty())
	{
		m_ListGameScene.back()->Release();
		m_ListGameScene.pop_back();
	}
}
void SceneManager::ReplaceBy(GameScene* GameScene)
{
	ExitState();
	AddElement(GameScene);
}
void SceneManager::ClearAll()
{
	while( !m_ListGameScene.empty() )
	{
		ExitState();
	}
}

