#include "GameTimeSpan.h"

CGameTimeSpan::CGameTimeSpan()
{
	this->m_Ticks = 0;
}
CGameTimeSpan::CGameTimeSpan(UINT64 Ticks)
{
	this->m_Ticks = Ticks;
}
CGameTimeSpan::~CGameTimeSpan()
{}
int CGameTimeSpan::getMilliseconds()
{
	return (int)(m_Ticks / TicksPerMillisecond);
}
UINT64	CGameTimeSpan::getTicks()
{
	return m_Ticks;
}

CGameTimeSpan& CGameTimeSpan::operator=(const CGameTimeSpan &Timesp)
{
	this->m_Ticks = Timesp.m_Ticks;
	return *this;
}
