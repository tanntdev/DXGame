#ifndef __TIMESPAN_H__
#define	__TIMESPAN_H__
#include <Windows.h>

class CGameTimeSpan
{
private:
	UINT64	m_Ticks;
public:
	
    static const UINT64 TicksPerSecond			= 10000000;
	
    static const UINT64 TicksPerMillisecond		= 10000;

	
	CGameTimeSpan();
	
	CGameTimeSpan(UINT64 Ticks);
	
	int	getMilliseconds();
	
	UINT64	getTicks();
	
	CGameTimeSpan& operator=(const CGameTimeSpan& Timesp);
	
	~CGameTimeSpan();
};

#endif	__TIMESPAN_H__