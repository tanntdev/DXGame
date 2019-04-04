#include "GameObject.h"

int CGameObject::m_identifyNumber = 0;

CGameObject::CGameObject()
{

}

RECT CGameObject::getBound()
{
	RECT tempBound = RECT();

	tempBound.left		= (long)(m_Position.x - m_Sprite->getAnimation()->getFrameSize().x / 2);
	tempBound.right		= (long)(tempBound.left + m_Sprite->getAnimation()->getFrameSize().x);
	tempBound.top		= (long)(m_Position.y + m_Sprite->getAnimation()->getFrameSize().y / 2);
	tempBound.bottom	= (long)(tempBound.top - m_Sprite->getAnimation()->getFrameSize().y);

	return tempBound;
}

CGameObject::CGameObject(D3DXVECTOR3 _position, ccDirection _direction, GameObjectID _objectID)
{
	m_Position = _position;
	m_Direction = _direction;
	m_GameObjectID = _objectID;
	m_TimeChangeState = 0;
	m_TimeChangeDirectAttack = 0;
	m_ObjectIdentifyNumber = m_identifyNumber++;
}

CGameObject::~CGameObject()
{

}