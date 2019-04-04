#include "VirtualObject.h"


RECT VirtualObject::getBound()
{
	RECT tempBound = RECT();

	tempBound.left		= (long)(m_Position.x - m_Width / 2);
	tempBound.right		= (long)(tempBound.left + m_Width);
	tempBound.top		= (long)(m_Position.y + m_Height / 2);
	tempBound.bottom	= (long)(tempBound.top - m_Height);

	return tempBound;
}

VirtualObject::VirtualObject()
{

}

VirtualObject::VirtualObject(D3DXVECTOR3 _position, ccDirection _direction, GameObjectID _objectID) : CGameObject(_position, _direction, _objectID)

{

}

VirtualObject::VirtualObject(D3DXVECTOR3 _position, int _width, int _height, GameObjectID _ObjectID) : CGameObject(_position, ccDirection::NONE, _ObjectID)
{
	m_TypeObject	=	GameObjectType::VIRTUAL_OBJECT;

	m_Width			=	_width;
	m_Height		=	_height;
	m_Sprite		=	0;
}

void VirtualObject::Initialize()
{

}

void VirtualObject::UpdateAnimation()
{

}


void VirtualObject::UpdateCollision(CGameObject* checkingObject)
{

}

void VirtualObject::Update()
{

}

void VirtualObject::Render(SPRITEHANDLE spriteHandle)
{

}

void VirtualObject::Release()
{
	m_Width = 0;
	m_Height = 0;
}

VirtualObject::~VirtualObject()
{

}
