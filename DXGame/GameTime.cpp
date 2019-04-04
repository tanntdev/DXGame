#include "GameTime.h"

CGameTime* CGameTime::s_Instance = 0;

CGameTime::CGameTime()
{
	this->m_ElapsedGameTime = CGameTimeSpan(1);
}

CGameTime::CGameTime(CGameTimeSpan &elapsedGameTime, CGameTimeSpan &totalGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
}

CGameTime* CGameTime::getInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new CGameTime();
	}
	return s_Instance;
}

void CGameTime::InitGameTime()
{
	QueryPerformanceFrequency(&m_Query);
	m_FreQuency = (float)m_Query.QuadPart / 10000000;
	QueryPerformanceCounter(&m_Query);
	StartTicks = LastTicks = m_Query.QuadPart;
}
void CGameTime::UpdateGameTime()
{
	QueryPerformanceCounter(&m_Query);
	CurTicks = m_Query.QuadPart;
	if( (UINT64)((float)(CurTicks - LastTicks) / m_FreQuency) < CGameTimeSpan::TicksPerMillisecond * 16)
	{
		return;
	}
	else
		{
			this->setElapsedGameTime( CGameTimeSpan( (UINT64)( (float)(CurTicks - LastTicks) / m_FreQuency ) ));
			LastTicks = CurTicks;
		}
}

void CGameTime::ResetLastTick()
{
	LastTicks = 0;
	CurTicks = 0;
}

void CGameTime::setElapsedGameTime(CGameTimeSpan &elapsedGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
}
CGameTimeSpan CGameTime::getElapsedGameTime()
{
	if (m_ElapsedGameTime.getMilliseconds() > 1000/30)
	{
		return CGameTimeSpan(1000/60);
	}
	return m_ElapsedGameTime;
}
