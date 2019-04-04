#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "Sprite.h"
#include "DefaultContents.h"
#include <map>
class SpriteManager
{
private:
	std::map<ccSpriteID, CSprite*> m_ListSprite;
	SpriteManager(void);
	static 			SpriteManager* s_Instance;
	void 			LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, ccSpriteID SpriteID, int Column, int Row, int TotalFrame);
public:
	CSprite*		getSprite(ccSpriteID eID);
	void 			InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice);
	void 			Release();
	static 			SpriteManager* getInstance();
	~SpriteManager(void);
};

#endif	__SPRITE_MANAGER_H__