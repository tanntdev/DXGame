#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Node.h"
#include "Collision.h"
#include "Markup.h"
#include <list>
#include <vector>
#include <map>
#include <unordered_set>

class QuadTree
{
private:
	RECT mBoundWorld;
	bool mIsFirstLoadXml;
	int mCount[100];
public:
	std::vector<int> mListObjectInView;
	std::vector<int> mListObjectCollisionInView;
	std::map<int, CGameObject*> mMapObjectInGame;
	std::map<int, CGameObject*> mMapObjectCollisionInGame;
	Node* mRootNode;
	Node* getRootNode() const { return this->mRootNode; };
	RECT getBoundWorld() const { return this->mBoundWorld; };
	QuadTree();
	void InsertObjectIntoView(RECT, Node*);
	void BuildQuadtree(const char* content, Node*& node, ccSpriteID _tile_map);
	void Update();
	void UpdateAnimation();
	void UpdateCollision(CGameObject*);
	void UpdateMovement();
	void Release(Node*);
	void Render(SPRITEHANDLE);
	~QuadTree();
};

#endif	__QUADTREE_H__