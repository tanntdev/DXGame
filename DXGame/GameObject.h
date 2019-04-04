#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Sprite.h"
#include "Physics.h"
#include "DefaultContents.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Box.h"
#include <d3dx9.h>
#include <d3d9.h>


class CGameObject
{
protected:
	GameObjectID		m_GameObjectID;
	ccDirection		m_Direction;
	CSprite*			m_Sprite;
	GameObjectState	m_ObjectState;
	GameObjectType		m_TypeObject;
	int				m_TimeChangeState;
	int				m_TimeChangeDirectAttack;
	int				m_AttackCounter;
	static int		m_identifyNumber;
	int				m_ObjectIdentifyNumber;
	D3DXVECTOR3		m_Position;

	//bit 0 -> Update Sprite
	//bit 1 -> Update Animation
	//bit 2 -> Update Movement
	char			m_UpdateFlag;
public:
	CGameObject();
	CGameObject(D3DXVECTOR3 _position, ccDirection _direction, GameObjectID _objectID);
	CSprite*		getSprite() const { return m_Sprite; }

	int				getIdentifyNumber(){ return this->m_identifyNumber; }
	
	void			setPosition(D3DXVECTOR3 _position){ m_Position = _position; }
	void			setPositionX(float _X){ m_Position.x = _X;}
	void			setPositionY(float _Y){ m_Position.y = _Y;}
	void			setPositionZ(float _Z){ m_Position.z = _Z;}
	D3DXVECTOR3		getPositionVec3(){ return m_Position; }
	D3DXVECTOR2		getPositionVec2(){ return D3DXVECTOR2(m_Position.x, m_Position.y); }

	
	GameObjectID		getID() const { return m_GameObjectID; }
	GameObjectType		getTypeObject() const { return m_TypeObject; }

	GameObjectState	getObjectState() const {return m_ObjectState;}
	void			setObjectState(GameObjectState _state) { this->m_ObjectState = _state;};

	ccDirection		getDirection() const{ return this->m_Direction;};
	virtual RECT getBound();
	virtual void Initialize() = 0;
	virtual void UpdateAnimation() = 0;

	virtual void UpdateCollision(CGameObject* checkingObject) = 0;
	virtual void Update() = 0;
	virtual void Render(SPRITEHANDLE spriteHandle) = 0;
	virtual void Release() = 0;

	virtual ~CGameObject();
};

#endif