#include "GameObject.h"

#ifndef __VIRTUAL_OBJECT_H__
#define __VIRTUAL_OBJECT_H__

class VirtualObject : public CGameObject
{
	int m_Width;
	int m_Height;
public:
	int getWidth() const{return m_Width;};
	int getHeight() const{return m_Height;};
	virtual RECT getBound();
	VirtualObject(void);
	VirtualObject(D3DXVECTOR3 _position, ccDirection _direction, GameObjectID _objectID);
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(CGameObject* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	VirtualObject(D3DXVECTOR3 _position, int _width, int _height, GameObjectID _ObjectID);
	~VirtualObject(void);
};

#endif