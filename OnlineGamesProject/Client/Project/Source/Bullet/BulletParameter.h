#pragma once

constexpr int STRAIGHT_BULLET_MAX = 1024;

//弾丸の識別ID
enum BulletID
{
	BULLET_ID_PLAYER_1,
	BULLET_ID_PLAYER_2,
	BULLET_ID_PLAYER_3,
	BULLET_ID_PLAYER_4
};


//発射する弾丸のカテゴリー
enum BulletCategory
{
	BULLET_CATEGORY_STRAIGHT
};

//直線弾の種類
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER_1,
	STRAIGHT_BULLET_TYPE_PLAYER_2,
	STRAIGHT_BULLET_TYPE_MAX
};

// バレットのパラメータ
struct BulletParameter
{
	char path[64];
	BulletCategory category;
	int life;
	int damage;
	int collisionTag;
	int hitEffect;
	float speed;
	float radius;
	float sizeX;
	float sizeY;
};

// 発射に必要なデータ
struct FireBulletData
{
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
};
