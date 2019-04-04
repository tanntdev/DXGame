#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "GameScene.h"
#include "Global.h"
#include <vector>
class GameScene;

class SceneManager
{
private:
	
	SceneManager() {}
	
	~SceneManager() {}
	
	vector<GameScene*> m_ListGameScene;
	
	static SceneManager* s_Instance;
	
	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:
	
	static SceneManager* getInstance();
	
	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);
	
	void Initialize();
	
	void HandleInput();
	
	void Update();
	
	void Render(LPD3DXSPRITE _lpDSpriteHandle);
	
	void AddElement(GameScene* GameScene);
	
	void ExitState();

	void ReplaceBy(GameScene* GameScene);
	
	void ClearAll();
};

#endif	__SCENE_MANAGER_H__