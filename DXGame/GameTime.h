#ifndef __GAMETIME_H__
#define	__GAMETIME_H__
#include <Windows.h>
#include "GameTimeSpan.h"

class CGameTime
{
private:
	
	static CGameTime*	s_Instance;

	CGameTimeSpan			m_ElapsedGameTime;
	
	LARGE_INTEGER			m_Query;
	
	float					m_FreQuency;
	
	LONGLONG				StartTicks;
	
	LONGLONG				LastTicks;
	
	LONGLONG				CurTicks;

	CGameTime();

	CGameTime(CGameTimeSpan& elapsedGameTime, CGameTimeSpan& totalGameTime);

public:
	
	static CGameTime* getInstance();
	
	void InitGameTime();
	void ResetLastTick();
	void UpdateGameTime();
	
	CGameTimeSpan	getElapsedGameTime();
	
	void			setElapsedGameTime(CGameTimeSpan& elapsedGameTime);
	
};
#endif	__GAMETIME_H__