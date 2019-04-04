#include "Animation.h"

CAnimation::CAnimation()
{
	this->m_columnFrame			= 0;
	this->m_rowFrame			= 0;
	this->m_heightFrame			= 0;
	this->m_index_End			= 0;
	this->m_index_Start			= 0;
	this->m_index_Current		= 0;
	this->m_sourceRect			= 0;
	this->m_timeAnimation		= 0;
	this->m_totalFrame			= 0;
	this->m_widthFrame			= 0;
	this->m_inverseNumber		= 1;
}
CAnimation::CAnimation(int width, int height, int col, int total)
{
	this->m_widthFrame				= width;
	this->m_heightFrame				= height;
	this->m_columnFrame				= col;
	this->m_rowFrame				= (int)total/col;
	this->m_totalFrame				= total;

	this->m_index_Current			= 0;
	this->m_index_Start				= 0;
	this->m_index_End				= total - 1;

	this->m_sourceRect				= new RECT();
	this->m_sourceRect->top			= 0;
	this->m_sourceRect->left		= 0;
	this->m_sourceRect->bottom		= m_heightFrame;
	this->m_sourceRect->right		= m_widthFrame;

	this->m_timeAnimation			= 0;
	this->m_inverseNumber			= 1;
}

CAnimation::CAnimation(const CAnimation& Animation)
{
	this->m_columnFrame				= Animation.m_columnFrame;
	this->m_rowFrame				= Animation.m_rowFrame;
	this->m_heightFrame				= Animation.m_heightFrame;
	this->m_index_End				= Animation.m_index_End;
	this->m_index_Start				= Animation.m_index_Start;
	this->m_index_Current			= Animation.m_index_Current;
	this->m_timeAnimation			= 0;
	this->m_totalFrame				= Animation.m_totalFrame;
	this->m_widthFrame				= Animation.m_widthFrame;


	this->m_sourceRect				= new RECT();
	this->m_sourceRect->top			= Animation.m_sourceRect->top;
	this->m_sourceRect->left		= Animation.m_sourceRect->left;
	this->m_sourceRect->right		= Animation.m_sourceRect->right;
	this->m_sourceRect->bottom		= Animation.m_sourceRect->bottom;

	this->m_inverseNumber			= Animation.m_inverseNumber;
}

CAnimation::~CAnimation()
{
	
}

void CAnimation::setIndexStart(int _start)
{
	this->m_index_Start = _start;
}

void CAnimation::setIndexEnd(int _end)
{
	this->m_index_End = _end;
}

void CAnimation::setSourceRect(RECT _rect)
{
	this->m_sourceRect->top			= _rect.top;
	this->m_sourceRect->left		= _rect.left;
	this->m_sourceRect->right		= _rect.right;
	this->m_sourceRect->bottom		= _rect.bottom;
}

void CAnimation::setCurrentFrame(int Index)
{
	this->m_index_Current = Index;
	CreateSourceRectangle();
}

RECT* CAnimation::getSourceRect()
{
	return m_sourceRect;
}

void CAnimation::NextFrame()
{
	this->m_index_Current ++;
	if(this->m_index_Current > this->m_index_End)
	{
		this->m_index_Current = this->m_index_Start;
	}
}

void CAnimation::NextFrameInverse()
{
	this->m_index_Current += m_inverseNumber;
	if(this->m_index_Current > this->m_index_End)
	{
		this->m_index_Current = this->m_index_End - 1;
		m_inverseNumber *= -1;
	}
	if(this->m_index_Current < this->m_index_Start)
	{
		this->m_index_Current = this->m_index_Start + 1;
		m_inverseNumber *= -1;
	}
}

void CAnimation::UpdateAnimation(int timeNexframe)
{
	this->m_timeAnimation += (int)CGameTime::getInstance()->getElapsedGameTime().getMilliseconds();

	if(this->m_timeAnimation > timeNexframe)
	{
		NextFrame();
		CreateSourceRectangle();
		this->m_timeAnimation = 0;
	}
}

void CAnimation::UpdateAnimationInverse(int timeNextFrame)
{
	this->m_timeAnimation += (int)CGameTime::getInstance()->getElapsedGameTime().getMilliseconds();
	if(this->m_timeAnimation > timeNextFrame)
	{
		NextFrameInverse();
		CreateSourceRectangle();
		this->m_timeAnimation = 0;
	}
}


void CAnimation::CreateSourceRectangle()
{
	m_sourceRect->top			= (m_index_Current / m_columnFrame) * m_heightFrame;
	m_sourceRect->left			= (m_index_Current % m_columnFrame) * m_widthFrame;
	m_sourceRect->bottom		= m_sourceRect->top + m_heightFrame;
	m_sourceRect->right			= m_sourceRect->left + m_widthFrame;
}


void CAnimation::setSourceRectAtIndex(int Index)
{
	m_sourceRect->top			= (Index / m_columnFrame)	* m_heightFrame;
	m_sourceRect->left			= (Index % m_columnFrame)	* m_widthFrame;
	m_sourceRect->bottom		= m_sourceRect->top			+ m_heightFrame;
	m_sourceRect->right			= m_sourceRect->left		+ m_widthFrame;
}

D3DXVECTOR2 CAnimation::getFrameSize()
{
	return D3DXVECTOR2((float)this->m_widthFrame, (float)this->m_heightFrame);
}

void CAnimation::Reset()
{
	this->m_sourceRect->top			= 0;
	this->m_sourceRect->left		= 0;
	this->m_sourceRect->bottom		= m_heightFrame;
	this->m_sourceRect->right		= m_widthFrame;

	this->m_timeAnimation			= 0;
	this->m_index_Current			= 0;
	this->m_inverseNumber			= 1;
}


void CAnimation::Release()
{
	SAFE_DELETE(m_sourceRect);
}