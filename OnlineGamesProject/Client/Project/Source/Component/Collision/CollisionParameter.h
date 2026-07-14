#pragma once

enum class ColliderType
{
	NONE,
	AABB_2D,
	AABB_3D,
	CIRCLE,
	SPHERE
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
