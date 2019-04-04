#include "Global.h"

bool CGlobal::IsWindowMode	= true;
bool CGlobal::IsExit		= false;
bool CGlobal::IsMute		= false;

D3DXVECTOR2 CGlobal::BillRazor_pos	= D3DXVECTOR2(0,0);
int CGlobal::MapName		= 0;
bool CGlobal::LiveOfRambo   = false;

bool IsMovementObject(GameObjectID id)
{
	switch(id)
	{
	case GameObjectID::ENEMY_RUN:
	case GameObjectID::SNIPER_STANDING:
	case GameObjectID::WEAPON_CAPSULE:
	case GameObjectID::BOMB:
	case GameObjectID::TANK:
	case GameObjectID::SNIPPER_WATER_HIDING:
	case GameObjectID::MAGIC_ROCK:
	case GameObjectID::STONE:
	case GameObjectID::BIG_CAPSULE_BOSS:
	case GameObjectID::ENEMY_RUN_SHOOTING:
	case GameObjectID::FIRE_BRIDGE:
	case GameObjectID::BOSS2BODY:
	case GameObjectID::GUN_ROTATING:
		return true;
	default:
		return false;
	}
	return false;
}

float Distance(CGameObject* a, CGameObject* b)
{
	float dx = abs(a->getPositionVec2().x - b->getPositionVec2().x);
	float dy = abs(a->getPositionVec2().y - b->getPositionVec2().y);

	return sqrtf(dx * dx + dy * dy);
}