#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "SoundBuffer.h"
#include "DefineList.h"
#include "DefaultContents.h"
#include <map>

class SoundManager
{
private:
	map<ccSoundID, SoundBuffer*> m_ListSoundBuffer;
	long		m_Volume;
	bool		m_IsMute;

	SoundManager() {m_Volume = 0; m_IsMute = false;}
	static SoundManager* s_Instace;
	void LoadSoundBuffer(const char* fileName, ccSoundID eID, LPDIRECTSOUND8 _lpDSound);
public:
	static SoundManager* getInstance();
	void LoadAllSoundBuffer(LPDIRECTSOUND8 _lpDSound);

	SoundBuffer* getSoundBuffer(ccSoundID eID);

	void SetVolume(long volume);
	void SetMute(bool isMute);
	void UpVolume();
	void DownVolume();
	void Release();
};


#endif	__SOUND_MANAGER_H__