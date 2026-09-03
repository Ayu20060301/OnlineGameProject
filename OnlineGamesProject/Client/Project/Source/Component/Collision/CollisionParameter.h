#pragma once

//コライダーの種類
enum ColliderType
{
	NONE,
	AABB_2D,
	AABB_3D,
	CIRCLE,
	SPHERE
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


struct CollisionResult
{
	bool isHit = false;
	float overlapX = 0.0f;
	float overlapY = 0.0f;
	float overlapZ = 0.0f;
	float normalX = 0.0f;
	float normalY = 0.0f;
	float normalZ = 0.0f;
};