#pragma once


enum SpriteAnimationType
{
	NONE = -1,
	ITEM_SPEED_UP,
	ITEM_RAPID_UP,
	ITEM_BULLET_SPEED_UP,
	PLAYER1_DEAD,
	PLAYER2_DEAD,
	PLAYER3_DEAD,
	PLAYER4_DEAD,
	BULLET_HIT_01,
	BULLET_HIT_02,
	BULLET_HIT_03,
	BULLET_HIT_04,
	MAX
};

struct SpriteAnimationParam
{
	const char* path; //画像パス
	int frameNum;    //フレーム数
	int frameWidth; //1コマの横幅
	int frameHeight; //1コマの縦幅
};

const SpriteAnimationParam SPRITE_ANIM_MASTER_PARAM[] =
{
	{ "Data/Play/Item/SpeedUp.png", 4, 40, 40 },
	{ "Data/Play/Item/BulletRapidUp.png", 4, 40, 40 },
	{ "Data/Play/Item/BulletSpeedUp.png", 4, 40, 40 },
	{ "Data/Play/Player/Player1Dead.png", 4, 40, 40 },
	{ "Data/Play/Player/Player2Dead.png", 4, 40, 40 },
	{ "Data/Play/Player/Player3Dead.png", 4, 40, 40 },
	{ "Data/Play/Player/Player4Dead.png", 4, 40, 40 },
	{ "Data/Play/Bullet/Effect/BulletHit01.png", 12, 40, 40 },
	{ "Data/Play/Bullet/Effect/BulletHit02.png", 12, 40, 40 },
	{ "Data/Play/Bullet/Effect/BulletHit03.png", 12, 40, 40 },
	{ "Data/Play/Bullet/Effect/BulletHit04.png", 12, 40, 40 },
};
