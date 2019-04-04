#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__

#include "DefaultContents.h"
#include "GameObject.h"

class CGlobal
{
public:
	static bool IsExit;
	static bool IsMute;
	static bool IsWindowMode;
	static D3DXVECTOR2 BillRazor_pos;
	static int	MapName;
	static bool LiveOfRambo;
};

bool IsMovementObject(GameObjectID type);
float Distance(CGameObject*, CGameObject*);

#endif __CGLOBAL_H__