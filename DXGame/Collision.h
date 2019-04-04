#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DynamicObject.h"
#include "Global.h"
#include "SweptAABB.h"
#include "Box.h"
#include "DefaultContents.h"

static bool Intersect(RECT rect1, RECT rect2)
{
	if (rect1.right <= rect2.left) // rect1 bên trái rect2
		return false;
	if (rect1.left >= rect2.right) // rect1 bên trái rect2
		return false;
	if (rect1.bottom >= rect2.top) // rect1 bên trái rect2
		return false;
	if (rect1.top <= rect2.bottom) // rect1 bên trái rect2
		return false;

	return true;
}

static BOX ConvertToBox(RECT _Rect, float _vx = 0.0f, float _vy = 0.0f)
{
	BOX box(
		(float)(_Rect.left),
		(float)(_Rect.top),
		(float)(_Rect.right - _Rect.left),
		(float)(_Rect.top - _Rect.bottom),
		(float)_vx,
		(float)_vy
		);

	return box;
}

static BOX ConvertToBroadPhase(BOX _Box)
{
	return GetSweptBroadPhaseBox(_Box);
}

class DynamicObject;
class Collision 
{
public:
	float m_MoveX, m_MoveY;
public:
	Collision();
	void InitCollision();
	DirectionID CheckCollision(DynamicObject *, CGameObject *);
	~Collision();
};

#endif	__COLLISION_H__