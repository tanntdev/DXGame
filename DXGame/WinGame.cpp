#include "WinGame.h"
#include "PlayScene.h"

void WinGame::InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	m_WinSceneBG = SpriteManager::getInstance()->getSprite(ccSpriteID::SPRITE_WINSCENE);

	m_WinScenePosition.x = 0;
	m_WinScenePosition.y = SCREEN_HEIGHT / 2;
	m_WinScenePosition.z = 1;
	m_isDone = false;
}

void WinGame::HandleInput()
{
	if(m_isDone == true)
	{
		if(CInput::getInstance()->IsKeyPress(DIK_ESCAPE))
		{
			std::exit(1);
			
		}
		if(CInput::getInstance()->IsKeyPress(DIK_RETURN))
		{
			SceneManager::getInstance()->ReplaceBy(new PlayScene(ccSceneID::COTRASCENE, 1));
		}

	}
}

void WinGame::Update()
{
	Camera::getInstance()->Reset();
	if(m_WinScenePosition.x >= 0 && m_WinScenePosition.x < SCREEN_WIDTH / 2)
	{
		m_WinScenePosition.x ++;
	}
	else if(m_WinScenePosition.x == SCREEN_WIDTH / 2)
	{
		m_isDone = true;
	}
}

void WinGame::Render(LPD3DXSPRITE _lpDSpriteHandle)
{
	m_WinSceneBG->Render(_lpDSpriteHandle, D3DXVECTOR2(m_WinScenePosition.x, m_WinScenePosition.y), ccSpriteEffect::None, 0.0f, 1.0f, m_WinScenePosition.z);
}

void WinGame::Pause()
{
}
void WinGame::Resume()
{
}

void WinGame::Release()
{
	m_WinSceneBG->Release();
}
