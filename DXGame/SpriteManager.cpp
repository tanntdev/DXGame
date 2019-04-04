#include "SpriteManager.h"

#define INCLUDE_MAP1 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.png", ccSpriteID::SPRITE_MAP_1, 42, 1, 42)
#define INCLUDE_MAP2 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\2\\2.png", ccSpriteID::SPRITE_MAP_2, 46, 1, 46)
#define INCLUDE_MAP3 LoadSpriteContent(_lpDirectDevice, "resources\\Map\\3\\3.png", ccSpriteID::SPRITE_MAP_3, 122, 1, 122)
SpriteManager* SpriteManager::s_Instance = 0;

SpriteManager::SpriteManager(void)
{

}

SpriteManager* SpriteManager::getInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new SpriteManager();
	}
	return s_Instance;
}

void SpriteManager::LoadSpriteContent(LPDIRECT3DDEVICE9 _lpDirectDevice, const char* fileName, ccSpriteID eID, int Column, int Row, int TotalFrame)
{
	CSprite* sprite = new CSprite();
	sprite->LoadContent(_lpDirectDevice, fileName, Column, Row, TotalFrame);
	m_ListSprite[eID] = sprite;
}

CSprite* SpriteManager::getSprite(ccSpriteID eID)
{
	std::map<ccSpriteID, CSprite*>::iterator i;

	i = m_ListSprite.find(eID);

	if(i == m_ListSprite.end())
		return 0;

	return i->second;
}

void SpriteManager::InitializeListSprite(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	//Load Billrazor
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_idle.png", ccSpriteID::SPRITE_BILLRAZOR_IDLE, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_lie.png", ccSpriteID::SPRITE_BILLRAZOR_LIE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_run.png", ccSpriteID::SPRITE_BILLRAZOR_RUN, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_bottom_right.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_BOTTOM_RIGHT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_run.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_RUN, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_top_right.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_TOP_RIGHT, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\rambo_shoot_up.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_UP, 2, 1, 2);
	
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Landscape\\ledframe.png", ccSpriteID::SPRITE_LED_OBJECT, 2, 1, 2);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\bullet.png", ccSpriteID::SPRITE_BULLET_BIG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\FBullet.png", ccSpriteID::SPRITE_F_BULLET, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\default_bullet_BILLRAZOR.png", ccSpriteID::SPRITE_DEFAULT_BULLET_BILLRAZOR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\fire.png", ccSpriteID::SPRITE_FIRE_BULLET_BILLRAZOR, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Rambo\\lazer.png", ccSpriteID::SPRITE_LAZE_BULLET_BILLRAZOR, 1, 2, 4);
	//End Billrazor

	// Load Map
	INCLUDE_MAP1;
	INCLUDE_MAP2;
	INCLUDE_MAP3;
	// End Map

	//Load MenuSprite
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\bg.png", ccSpriteID::SPRITE_MENUBG, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\icon.png", ccSpriteID::SPRITE_ICON, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\WinScene.png", ccSpriteID::SPRITE_WINSCENE, 1, 1, 1);
	//End MenuSprite

	LoadSpriteContent(_lpDirectDevice, "resources\\grid.png", ccSpriteID::SPRITE_GRID, 1, 1, 1);
	
	// Load Bridge

	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\BodyBridge.png", ccSpriteID::SPRITE_BRIDGE_BODY, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\HeadBridge.png", ccSpriteID::SPRITE_BRIDGE_HEAD, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\TailBridge.png", ccSpriteID::SPRITE_BRIDGE_TAIL, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\head_bridge_broken.png", ccSpriteID::SPRITE_HEAD_BREAK, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\tail_bridge_broken.png", ccSpriteID::SPRITE_TAIL_BREAK, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\BridgeExploision.png", ccSpriteID::SPRITE_BRIDGE_EXPLOISION, 5, 3, 15);
	// End Bridge

	//Load Enemy
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Exploision.png", ccSpriteID::SPRITE_EXPLOISION, 6, 1, 6);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\StandSniper\\StandSniper_bot.png", ccSpriteID::SPRITE_SNIPER_STANDING_BOT, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\StandSniper\\StandSniper_top.png", ccSpriteID::SPRITE_SNIPER_STANDING_TOP, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Sniper\\StandSniper\\StandSniper_mid.png", ccSpriteID::SPRITE_SNIPER_STANDING_MID, 2, 1, 2);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\HideSniper\\HideSniper.png", ccSpriteID::SPRITE_SNIPER_HIDING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\HideSniper\\HideSniperDead.png", ccSpriteID::SPRITE_SNIPER_HIDING_EXPLOISION, 4, 1, 4);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\UnderWaterSniper\\UnderWaterSniper_Hide.png", ccSpriteID::SPRITE_SNIPER_WATER_HIDING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\UnderWaterSniper\\UnderWaterSniper_Shoot.png", ccSpriteID::SPRITE_SNIPER_SHOOTING, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Soldier\\Soldier.png", ccSpriteID::SPRITE_ENEMY_RUN, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Soldier\\Soldier_Shoot.png", ccSpriteID::SPRITE_ENEMY_RUN_SHOOTING, 6, 1, 6);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Enemy\\Soldier\\BigGunShooting.png", ccSpriteID::SPRITE_ENEMY_WITH_BIG_GUN, 2, 1, 2);

	//Load Weapon ( Capsule)
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\WeaponSensor.png", ccSpriteID::SPRITE_WEAPON_SENSOR, 7, 1, 7);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\WeaponCapsule.png", ccSpriteID::SPRITE_WEAPON_CAPSULE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\Barrier.png", ccSpriteID::SPRITE_BARRIER, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\RapidFire.png", ccSpriteID::SPRITE_RAPID_FIRE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\SpreadGun.png", ccSpriteID::SPRITE_SPREAD_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\LaserGun.png", ccSpriteID::SPRITE_LASER_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\MachineGun.png", ccSpriteID::SPRITE_MACHINE_GUN, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Weapon\\Weaponry\\FlameGun.png", ccSpriteID::SPRITE_FLAME_GUN, 1, 1, 1);
	// End Weapon

	// Load Gun
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\Gun.png", ccSpriteID::SPRITE_GUN_ROTATING, 14, 1, 14);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\BigGun.png", ccSpriteID::SPRITE_BIG_GUN_ROATING, 3, 3, 9);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Gun\\BigGunPopup.png", ccSpriteID::SPRITE_BIG_GUN_ROTAING_POPUP, 3, 2, 6);
	// End Gun


	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\Move\\move.png", ccSpriteID::SPRITE_BILLRAZOR_MOVE_BODY, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Leg\\Move\\move.png", ccSpriteID::SPRITE_BILLRAZOR_MOVE_LEG, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\MoveUp\\top_right.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_TOP_RIGHT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\MoveDown\\bottom_right.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_BOTTOM_RIGHT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\shoot.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\up.png", ccSpriteID::SPRITE_BILLRAZOR_SHOOT_UP_BODY, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\jump.png", ccSpriteID::SPRITE_BILLRAZOR_JUMP, 4, 1, 4);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\water_bomb.png", ccSpriteID::SPRITE_BILLRAZOR_WATER_BOMB, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\climb.png", ccSpriteID::SPRITE_BILLRAZOR_CLIMB, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\dive.png", ccSpriteID::SPRITE_BILLRAZOR_DIVE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\swim.png", ccSpriteID::SPRITE_BILLRAZOR_SWIM, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\BillRazor\\Body\\dead.png", ccSpriteID::SPRITE_BILLRAZOR_BEFORE_DEAD, 5, 1, 5);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\GunBoss\\BossGun.png", ccSpriteID::SPRITE_GUN_BOSS, 2, 1, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossCenter\\BossCenter.png", ccSpriteID::SPRITE_BOSS_CENTER, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossBodyDead.png", ccSpriteID::SPRITE_BOSS_BODY_DEAD, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossBodyAlive.png", ccSpriteID::SPRITE_BOSS_BODY_ALIVE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossDie1.png", ccSpriteID::SPRITE_BOSS_DIE, 4, 2, 8);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossExploision.png", ccSpriteID::SPRITE_BOSS_EXPLOISION, 8, 5, 40);
	
	// Boss Map 2
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossBody.png", ccSpriteID::SPRITE_BOSS_MAP2_BODY_ALIVE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossDie.png", ccSpriteID::SPRITE_BOSS_MAP2_DEATH, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossHead.png", ccSpriteID::SPRITE_BOSS_HEAD, 3, 3, 9);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossBullet.png", ccSpriteID::SPRITE_BULLET_BOSS, 4, 1, 4);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossPunch.png", ccSpriteID::SPRITE_PUNCH_BOSS, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap2\\BossArm.png", ccSpriteID::SPRITE_ARM_BOSS, 1, 1, 1);
	// End Boss Map 2

	//BOSS MAP 3
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap3\\Boss3.png", ccSpriteID::SPRITE_CAPSULE_BOSS, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Boss\\BossMap3\\Boss3Big.png", ccSpriteID::SPRITE_BIG_CAPSULE_BOSS, 12, 1, 12);
	//END BOSSMAP3

	LoadSpriteContent(_lpDirectDevice, "resources\\Items\\medal.png", ccSpriteID::SPRITE_MEDAL, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\1\\1.effect", ccSpriteID::SPRITE_EFFECT_MAP1, 1, 2, 2);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\2\\2.effect", ccSpriteID::SPRITE_EFFECT_MAP2, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\3\\3.effect", ccSpriteID::SPRITE_EFFECT_MAP3, 1, 2, 2);

	//Stone
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Stone\\StoneBridge\\StoneBridge.png", ccSpriteID::SPRITE_BRIGDE_STONE, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Stone\\Stone\\Stone.png", ccSpriteID::SPRITE_BIG_STONE, 4, 1, 4);
	//EndStone

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Fire\\fire.png", ccSpriteID::SPRITE_FIRE, 2, 1, 2);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Tank\\Tank.png", ccSpriteID::SPRITE_TANK, 2, 12, 24);

	LoadSpriteContent(_lpDirectDevice, "resources\\bridge\\Bridge2\\Bridge2.png", ccSpriteID::SPRITE_FIRE_BRIDGE, 1, 1, 1);

	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bomb\\Bomb.png", ccSpriteID::SPRITE_Bomb, 1, 1, 1);
	LoadSpriteContent(_lpDirectDevice, "resources\\Character\\Bomb\\BombExploision.png", ccSpriteID::SPRITE_Bomb_EXPLOISION, 3, 1, 3);
	LoadSpriteContent(_lpDirectDevice, "resources\\Map\\MenuGame\\black.png", ccSpriteID::SPRITE_BLACK_BACKGROUND, 1, 1, 1);
}

void SpriteManager::Release()
{
	std::map<ccSpriteID, CSprite*>::iterator i;
	for(i = m_ListSprite.begin(); i != m_ListSprite.end(); i++)
	{
		i->second->Release();
		SAFE_DELETE(i->second);
	}
	m_ListSprite.clear();
}

SpriteManager::~SpriteManager(void)
{
}
