#ifndef __GAMESCENE_H__
#define	__GAMESCENE_H__

#include "GameTime.h"

#include "DefaultContents.h"
#include "Input.h"
#include "SceneManager.h"
#include "DefineList.h"

class SceneManagerDx9;

class GameScene
{
protected:
	ccSceneID sceneID;
public:
	GameScene(ccSceneID ID){sceneID = ID;}
	virtual void HandleInput() = 0;
	virtual void InitializeState(LPDIRECT3DDEVICE9 _lpDirectDevice) = 0;
	virtual void Pause() = 0;
	virtual void Release() = 0;
	virtual void Render(LPD3DXSPRITE _lpDSpriteHandle) = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual ~GameScene() {}
};

#endif	__GAMESCENE_H__