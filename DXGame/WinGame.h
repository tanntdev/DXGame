#ifndef __WIN_GAME_H__
#define __WIN_GAME_H__

#include "GameScene.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "DefaultContents.h"
class WinGame : public GameScene
{
private:
	CSprite*			m_WinSceneBG;
	D3DXVECTOR3			m_WinScenePosition;
	bool m_isDone;
public:
	WinGame(ccSceneID ID) : GameScene(ID) {}
	~WinGame(){}
	void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void HandleInput();
	void Update();
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	void Pause();
	void Resume();
	void Release();
};


#endif