#pragma once

enum CollisionType
{
	COLLISION_AABB,
	COLLISION_SPHERE,
	COLLISION_TYPE_NONE = -1
};


//弾の当たり判定で区別を付けるためのタグ
enum CollisionTag
{
	COLLISION_TAG_PLAYER1,			// プレイヤー1
	COLLISION_TAG_PLAYER2,			// プレイヤー2
	COLLISION_TAG_PLAYER3,			// プレイヤー3
	COLLISION_TAG_PLAYER4,			// プレイヤー4
	COLLISION_TAG_NONE = -1
};
