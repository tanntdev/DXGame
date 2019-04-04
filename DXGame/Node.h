#ifndef __NODE_H__
#define __NODE_H__

#include "GameObject.h"
#include <list>
#include <vector>
#include "Collision.h"
#include "Tile.h"
#include "VirtualObject.h"
#include "BackgroundEffect.h"
#include "Gun.h"
#include "StandSniper.h"
#include "Bridge.h"
#include "Soldier.h"
#include "HideSniper.h"
#include "BigGun.h"
#include "WeaponCapsule.h"
#include "WeaponSensor.h"
#include "Boss1Body.h"
#include "UnderWaterSniper.h"
#include "Tank.h"
#include "StoneBridge.h"
#include "Stone.h"
#include "Bomb.h"
#include "Boss3Big.h"
#include "FireBridge.h"
#include "ShootingSoldier.h"
#include "Boss2Body.h"
#include "BigGunAndSniper.h"
#include "WeaponCapsulev2.h"

class Node
{
private:
	 int mID;
	 RECT mBound;
public:
	Node* mTl;
	Node* mTr;
	Node* mBl;
	Node* mBr;
	std::vector<int> mListObject;
	std::vector<int> mListObjectCollision;

	int getID() const { return this->mID; };
	RECT getBound() const { return this->mBound; };
	std::vector<int> getListObject() const { return this->mListObject; };
	std::vector<int> getListObjectCollision() const { return this->mListObjectCollision; };

	Node* getTl() const { return this->mTl; };
	Node* getTr() const { return this->mTr; };
	Node* getBl() const { return this->mBl; };
	Node* getBr() const { return this->mBr; };

	void setTl(Node* _tl) { this->mTl = _tl;};
	Node();
	Node(int, RECT);
	~Node();
};

#endif