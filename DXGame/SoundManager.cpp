#include "SoundManager.h"

SoundManager* SoundManager::s_Instace = 0;
bool CSoundSwitch::IsExit = false;
bool CSoundSwitch::IsMute = false;

SoundManager* SoundManager::getInstance()
{
	if ( s_Instace == 0 )
	{
		s_Instace = new SoundManager();
	}
	return s_Instace;
}

void SoundManager::LoadSoundBuffer(const char* fileName, ccSoundID eID, LPDIRECTSOUND8 _lpDSound)
{
	SoundBuffer* _soundbuffer = new SoundBuffer();
	_soundbuffer->LoadWaveToBuffer(_lpDSound, (char*)fileName);
	_soundbuffer->getSoundBuffer()->SetVolume(m_Volume);
	m_ListSoundBuffer[eID] = _soundbuffer;
}

void SoundManager::LoadAllSoundBuffer(LPDIRECTSOUND8 _lpDSound)
{
	this->LoadSoundBuffer("resources\\Sound\\e_broken.wav", ccSoundID::BROKEN, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\e_broken.wav", ccSoundID::THU_CUOI_SONG, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\s_Theme_S_1.wav", ccSoundID::THEME_SONG_S_1, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bullet_S_sfx.wav", ccSoundID::bullet_S_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bullet_M_sfx.wav", ccSoundID::bullet_M_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bridge_burn_sfx.wav", ccSoundID::bridge_burn_sfx, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bullet_default_sfx.wav", ccSoundID::bullet_default_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\boss_dead_sfx.wav", ccSoundID::boss_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_attacked_sfx.wav", ccSoundID::enemy_attacked_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_1up_sfx.wav", ccSoundID::rambo_1up_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_dead_sfx.wav", ccSoundID::rambo_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\bullet_L_sfx.wav", ccSoundID::bullet_L_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\rambo_step_sfx.wav", ccSoundID::rambo_step_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_dead_sfx.wav", ccSoundID::enemy_dead_sfx, _lpDSound);

	this->LoadSoundBuffer("resources\\Sound\\bridge_exploision_sfx.wav", ccSoundID::bridge_exploision_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\enemy_dead_sfx.wav", ccSoundID::enemy_dead_sfx, _lpDSound);
	this->LoadSoundBuffer("resources\\Sound\\Bomb_sfx.wav", ccSoundID::Bomb_sfx, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_s1.wav", ccSoundID::s_theme_s1, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_gameover.wav", ccSoundID::s_theme_gameover, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_them_menu.wav", ccSoundID::s_them_menu, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_s2.wav", ccSoundID::s_theme_s2, _lpDSound);
	LoadSoundBuffer("resources\\Sound\\s_theme_s3.wav", ccSoundID::s_theme_s3, _lpDSound);

}
SoundBuffer* SoundManager::getSoundBuffer(ccSoundID eID)
{
	map<ccSoundID, SoundBuffer*>::iterator i;
	i = m_ListSoundBuffer.find(eID);
	if(i == m_ListSoundBuffer.end())
		return 0;
	return i->second;
}

void SoundManager::SetVolume(long volume)
{
	if(volume < -10000)
		volume = -10000;
	if(volume > 0)
		volume = 0;
	this->m_Volume = volume;

	map<ccSoundID, SoundBuffer*>::iterator i;
	for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
		i->second->getSoundBuffer()->SetVolume(m_Volume);
}
void SoundManager::SetMute(bool isMute)
{
	CSoundSwitch::IsMute = isMute;
	map<ccSoundID, SoundBuffer*>::iterator i;
	if(isMute)
	{
		for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
			i->second->getSoundBuffer()->SetVolume(-10000);
	}
}
void SoundManager::UpVolume()
{
	if(m_Volume > -9900)
		m_Volume = -9900;
	m_Volume += 100;
	SetVolume(m_Volume);
}
void SoundManager::DownVolume()
{
	if(m_Volume < -9900)
		m_Volume = -9900;
	m_Volume -= 100;
	SetVolume(m_Volume);
}

void SoundManager::Release()
{
	map<ccSoundID, SoundBuffer*>::iterator i;
	for(i = m_ListSoundBuffer.begin(); i != m_ListSoundBuffer.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSoundBuffer.clear();
}