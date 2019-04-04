#include "QuadTree.h"
#include "PlayScene.h"

QuadTree::QuadTree()
{
	this->mRootNode = NULL;
	this->mIsFirstLoadXml = true;
}

void QuadTree::InsertObjectIntoView(RECT viewPort, Node* node)
{
	int j = 0;

	if (node == this->mRootNode)
	{
		if (this->mListObjectInView.size() > 0 && this->mListObjectCollisionInView.size() > 0)
		{
			this->mListObjectInView.clear();
			this->mListObjectCollisionInView.clear();
		}
	}

	if (CheckAABB(ConvertToBox(viewPort), ConvertToBox(node->getBound())))
	{
		for(int i = 0; i < (int)node->mListObject.size(); ++i)
		{
			mListObjectInView.push_back(node->mListObject[i]);
		}

		for(int i = 0; i < (int)node->mListObjectCollision.size(); ++i)
		{
			if(mMapObjectCollisionInGame[node->mListObjectCollision[i]]->getObjectState() != GameObjectState::STATE_DEATH && mMapObjectCollisionInGame[node->mListObjectCollision[i]]->getObjectState() != GameObjectState::STATE_BOSS_DEATH)
			{
				PlayScene::IncreaseScore();
				for( j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
				{
					if(node->mListObjectCollision[i] == mListObjectCollisionInView[j])
						break;
				}

				if(j == mListObjectCollisionInView.size())
				{
					
					mListObjectCollisionInView.push_back(node->mListObjectCollision[i]);
				}
			}
			else
			{
				node->mListObjectCollision.erase(node->mListObjectCollision.begin() + i);
			}
		}

		if (node->getBl() != NULL)
			InsertObjectIntoView(viewPort, node->getBl());
		if (node->getBr() != NULL)
			InsertObjectIntoView(viewPort, node->getBr());
		if (node->getTl() != NULL)
			InsertObjectIntoView(viewPort, node->getTl());
		if (node->getTr() != NULL)
			InsertObjectIntoView(viewPort, node->getTr());
	}
}

void QuadTree::Release(Node* node)
{
	if(node->getBl() != NULL)
	{
		// de quy
		Release(node->getBl());
		Release(node->getBr());
		Release(node->getTl());
		Release(node->getTr());
	}
	else // neu khong con node con, thi tien hanh release cac object
	{
		if(node->mListObject.empty() != true)
			node->mListObject.clear();

		if(node->mListObjectCollision.empty() != true)
			node->mListObjectCollision.clear();

		delete node;
		node = NULL;
	}

	if(this->mMapObjectInGame.size() > 0)
		this->mMapObjectInGame.clear();

	if(this->mMapObjectCollisionInGame.size() > 0)
		this->mMapObjectCollisionInGame.clear();
}

void QuadTree::BuildQuadtree(const char* content, Node*& node, ccSpriteID _tile_map)
{
	if(this->mIsFirstLoadXml == true)
	{
		CMarkup xml;
		xml.Load(content);
		
		if(xml.FindElem("Map"))
		CGlobal::MapName = atoi(xml.GetAttrib("Name").c_str());
		xml.IntoElem();
		xml.FindElem("Node");
		xml.FindElem();
		if(node == NULL)
		{
			RECT bound = RECT();
			bound.left = atoi(xml.GetAttrib("X").c_str());
			bound.top = atoi(xml.GetAttrib("Y").c_str());
			bound.bottom = bound.top - atoi(xml.GetAttrib("Height").c_str());
			bound.right = bound.left + atoi(xml.GetAttrib("Width").c_str());
			node = new Node(atoi(xml.GetAttrib("Id").c_str()), bound);
		}
		this->mIsFirstLoadXml = false;
		xml.IntoElem();
		if(xml.FindElem("Node"))
		{
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr, _tile_map);
		}
	}
	else
	{
		CMarkup xml(content);
		xml.FindElem("Node");
		xml.FindElem();
		RECT bound = RECT();
		bound.left = atoi(xml.GetAttrib("X").c_str());
		bound.top = atoi(xml.GetAttrib("Y").c_str());
		bound.bottom = bound.top - atoi(xml.GetAttrib("Height").c_str());
		bound.right = bound.left + atoi(xml.GetAttrib("Width").c_str());
		node = new Node(atoi(xml.GetAttrib("Id").c_str()), bound);
		
		xml.IntoElem();
		if(xml.FindElem("Node"))
		{
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mTr, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBl, _tile_map);
			xml.FindElem("Node");
			this->BuildQuadtree(xml.GetSubDoc().c_str(), node->mBr, _tile_map);
		}
		else
		{
			if(xml.FindElem("Objects"))
			{
				xml.IntoElem();
				std::map<int, Object*>::iterator i;
				while(xml.FindElem("Object"))
				{
					i = mMapObjectInGame.find(atoi(xml.GetAttrib("Index").c_str()));
					if(i == mMapObjectInGame.end())
					{
						if(atoi(xml.GetAttrib("Type").c_str()) == 0)
						{
							mMapObjectInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tile(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f), atoi(xml.GetAttrib("Id").c_str()),
								_tile_map);
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new VirtualObject(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								atoi(xml.GetAttrib("Width").c_str()), 
								atoi(xml.GetAttrib("Height").c_str()),
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Gun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::SNIPER_STANDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new StandSniper(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								0.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::BRIDGE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  Bridge(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f), 
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::ENEMY_RUN)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  Soldier(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::SNIPER_HIDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new  HideSniper(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::BIG_GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigGun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::WEAPON_CAPSULE)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							if(CGlobal::MapName != 2)
							{
								mMapObjectCollisionInGame[tempIndex] = new WeaponCapsule(D3DXVECTOR3(
									tempPositionX,
									tempPositionY,
									1.0f),
									ccDirection::LEFT,
									(GameObjectID)tempId,
									(GameObjectID)temp);
								mMapObjectCollisionInGame[tempIndex]->Initialize();
							}
							else
							{
								mMapObjectCollisionInGame[tempIndex] = new WeaponCapsulev2(D3DXVECTOR3(
									tempPositionX,
									tempPositionY,
									1.0f),
									ccDirection::LEFT,
									(GameObjectID)tempId,
									(GameObjectID)temp);
								mMapObjectCollisionInGame[tempIndex]->Initialize();
							}
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::WEAPON_SENSOR)
						{
							int tempIndex = atoi(xml.GetAttrib("Index").c_str());
							float tempPositionX = (float)(atoi(xml.GetAttrib("X").c_str()));
							float tempPositionY = (float)(atoi(xml.GetAttrib("Y").c_str()));
							int tempId = atoi(xml.GetAttrib("Id").c_str());
							xml.FindElem("Object");
							int temp = atoi(xml.GetAttrib("Id").c_str());
							mMapObjectCollisionInGame[tempIndex] = new WeaponSensor(D3DXVECTOR3(
								tempPositionX,
								tempPositionY,
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)tempId,
								(GameObjectID)temp);
							mMapObjectCollisionInGame[tempIndex]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::BIG_GUN_ROTATING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigGun(D3DXVECTOR3(
								(float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())),
								1.0f),
								ccDirection::LEFT,
								(GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::BIG_BOSS_1)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Boss1Body(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::SNIPPER_WATER_HIDING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new UnderWaterSniper(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::TANK)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Tank(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::MAGIC_ROCK)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new StoneBridge(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::STONE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Stone(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::Bomb)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Bomb(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::BIG_CAPSULE_BOSS)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Boss3Big(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::FIRE_BRIDGE)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new FireBridge(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::ENEMY_RUN_SHOOTING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new ShootingSoldier(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::Boss2Body)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new Boss2Body(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
						else if(atoi(xml.GetAttrib("Type").c_str()) == 4 && atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::ENEMY_BIG_GUN_SHOOTING)
						{
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())] = new BigGunAndSniper(D3DXVECTOR3((float)(atoi(xml.GetAttrib("X").c_str())),
								(float)(atoi(xml.GetAttrib("Y").c_str())), 1.0f), ccDirection::LEFT, (GameObjectID)atoi(xml.GetAttrib("Id").c_str()));
							mMapObjectCollisionInGame[atoi(xml.GetAttrib("Index").c_str())]->Initialize();
						}
					}

					if(atoi(xml.GetAttrib("Type").c_str()) == (int)GameObjectType::TILE_MAP)
					{
						node->mListObject.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
					else if(atoi(xml.GetAttrib("Type").c_str()) == (int)GameObjectType::VIRTUAL_OBJECT || atoi(xml.GetAttrib("Type").c_str()) == (int)GameObjectType::DYNAMIC_OBJECT)
					{
						if(atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_BARRIER
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_FLAME_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_LASER_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_MACHINE_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_RAPID_GUN
							|| atoi(xml.GetAttrib("Id").c_str()) == (int)GameObjectID::OBJECT_SPREAD_GUN)
						node->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()) - 1);
						else
						node->mListObjectCollision.push_back(atoi(xml.GetAttrib("Index").c_str()));
					}
				}
			}
		}
	}
}

void QuadTree::Update()
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->Update();
	}
}

void QuadTree::UpdateAnimation()
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateAnimation();
	}
}

void QuadTree::UpdateCollision(CGameObject* checkingObject)
{
	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->UpdateCollision(checkingObject);
	}
}

void QuadTree::UpdateMovement()
{	for(int i = 0; i < (int)mListObjectCollisionInView.size(); ++i)
	{
		if(IsMovementObject(mMapObjectCollisionInGame[mListObjectCollisionInView[i]]->getID()))
		{
			DynamicObject* tempObject = (DynamicObject*)mMapObjectCollisionInGame[mListObjectCollisionInView[i]];
			tempObject->UpdateMovement();
		}
	}
}

void QuadTree::Render(SPRITEHANDLE spriteHandler)
{
	for(int i = 0; i < (int)mListObjectInView.size(); ++i)
	{
		mMapObjectInGame[mListObjectInView[i]]->Render(spriteHandler);
	}

	for(int j = 0; j < (int)mListObjectCollisionInView.size(); ++j)
	{
		mMapObjectCollisionInGame[mListObjectCollisionInView[j]]->Render(spriteHandler);
	}
}

QuadTree::~QuadTree()
{

}
