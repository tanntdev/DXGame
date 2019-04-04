#include "MapReader.h"
#include "Tile.h"
#include "VirtualObject.h"
#include "BackgroundEffect.h"

void GameObjectXML::Deserialize(const char *childContent)
{
	CMarkup xml(childContent);
	m_Type = atoi(xml.GetAttrib("Type").c_str());
}

void GameObjectXML::DeserializeVirtualObject(const char* childContent)
{
	CMarkup xml(childContent);
	xml.FindElem();		
	m_ID		= atoi(xml.GetAttrib("Id").c_str());
	m_Type		= atoi(xml.GetAttrib("Type").c_str());
	m_X			= atoi(xml.GetAttrib("X").c_str());
	m_Y			= atoi(xml.GetAttrib("Y").c_str());
	m_Height	= atoi(xml.GetAttrib("Height").c_str());
	m_Width		= atoi(xml.GetAttrib("Width").c_str());
}

void GameObjectXML::DeserializeTile(const char *childContent)
{
	CMarkup xml(childContent);
	xml.FindElem();
	m_ID		= atoi(xml.GetAttrib("Id").c_str());
	m_Type	= atoi(xml.GetAttrib("Type").c_str());
	m_X		= atoi(xml.GetAttrib("X").c_str());
	m_Y		= atoi(xml.GetAttrib("Y").c_str());
}

int GameObjectXML::GetID()
{
	return m_ID;
}
int GameObjectXML::GetX()
{
	return m_X;
}
int GameObjectXML::GetY()
{
	return m_Y;
}
int GameObjectXML::GetType()
{
	return m_Type;
}

int GameObjectXML::GetWidth()
{
	return m_Width;
}
int GameObjectXML::GetHeight()
{
	return m_Height;
}

MapReader* MapReader::s_Instance = 0;

MapReader* MapReader::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new MapReader();
	}
	return s_Instance;
}

void MapReader::ReadMap(const char* _filePath, list<CGameObject*>* _listObject, list<CGameObject*>* _backgroundList, list<CGameObject*>* _ledObject)
{
	CMarkup xml;
	xml.Load(_filePath);
	xml.FindElem("Objects");
	xml.IntoElem();

	while (xml.FindElem("Object"))
	{
		GameObjectXML *_GameObject;
		_GameObject = new GameObjectXML();
		_GameObject->Deserialize(xml.GetSubDoc().c_str());
		
		switch (_GameObject->GetType())
		{
		case GameObjectType::TILE_MAP:
			{
				CGameObject* temp = 0;
				_GameObject->DeserializeTile(xml.GetSubDoc().c_str());
				temp = new Tile(D3DXVECTOR3((float)(_GameObject->GetX()), (float)(_GameObject->GetY()), 0), _GameObject->GetID(), ccSpriteID::SPRITE_MAP_1);
				_backgroundList->push_back(temp);
			}
			break;
		case GameObjectType::VIRTUAL_OBJECT:
			{
				CGameObject* temp = 0;
				_GameObject->DeserializeVirtualObject(xml.GetSubDoc().c_str());
				temp = new VirtualObject(D3DXVECTOR3((float)(_GameObject->GetX()), (float)(_GameObject->GetY()), 1), _GameObject->GetWidth(), _GameObject->GetHeight(), (GameObjectID)_GameObject->GetID());
				_listObject->push_back(temp); 
			}
			break;
		case GameObjectType::STATIC_OBJECT:
			{

			}
			break;
		case GameObjectType::DYNAMIC_OBJECT:
			{

			}
			break;
		default:
			break;
		}
	}
}