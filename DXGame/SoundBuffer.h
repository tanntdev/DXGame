#ifndef __SOUND_BUFFER_H__
#define __SOUND_BUFFER_H__

#include <dsound.h>
#include <d3d.h>
#include <d3d9.h>
#include <string>
#include <string.h>
#include "DefineList.h"
using namespace std;

class SoundBuffer
{
private:
	LPDIRECTSOUNDBUFFER m_SoundBuffer;
public:
	SoundBuffer();
	~SoundBuffer();

	bool LoadWaveToBuffer(LPDIRECTSOUND8 _lpDSound, const char* fileName);
	LPDIRECTSOUNDBUFFER getSoundBuffer();
	void Play();
	void Repeat();
	void Stop();
	void Release();
};

#endif	__SOUND_BUFFER_H__