#include "AABB.h"
#include <cmath>
#include "ColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../MyMath/MyMath.h"


AABB3D::AABB3D() : ColliderComponent()
{
	m_Type = ColliderType::AABB_3D;
    m_Center = {};
	m_Size = {};
}

void AABB3D::Draw()
{
	float hw = m_Size.x * 0.5f;
	float hh = m_Size.y * 0.5f;
	float hd = m_Size.z * 0.5f;

	VECTOR center = m_Owner->GetPosition() + m_Center;
	VECTOR v[8] =
	{
		VGet(center.x - hw,center.y - hh, center.z - hd),
		VGet(center.x + hw,center.y - hh, center.z - hd),
		VGet(center.x + hw,center.y + hh, center.z - hd),
		VGet(center.x - hw,center.y + hh, center.z - hd),

		VGet(center.x - hw,center.y - hh, center.z + hd),
		VGet(center.x + hw,center.y - hh, center.z + hd),
		VGet(center.x + hw,center.y + hh, center.z + hd),
		VGet(center.x - hw,center.y + hh, center.z + hd),
	};

	//12本の辺
	int edges[12][2] =
	{
		{0,1},{1,2},{2,3},{3.0}, //奥の四角
		{4,5},{5,6},{6,7},{7.4}, //手前の奥
		{0,4},{1,5},{2,6},{3.7}, //奥の⇔手前の繋ぎ
	};

	for (int i = 0; i < 12; i++) {
		DrawLine3D(
			v[edges[i][0]],
			v[edges[i][1]],
			GetColor(255, 255, 255)
		);
	}
}

CollisionResult AABB3D::CheckCollide(const ColliderComponent& other) const
{
	CollisionResult result = {};

	ColliderType type = other.GetType();
	switch (type)
	{
	case ColliderType::AABB_3D: result = CheckCollideAABB(static_cast<const AABB3D&>(other)); break;
	}

	return result;
}

CollisionResult AABB3D::CheckCollideAABB(const AABB3D& other) const
{
	CollisionResult result = {};
	VECTOR centerA = m_Owner->GetPosition();
	VECTOR centerB = other.m_Owner->GetPosition();
	centerA += m_Center;
	centerB += other.m_Center;

	float leftA = centerA.x - m_Size.x / 2.0f;
	float rightA = centerA.x + m_Size.x / 2.0f;
	float topA = centerA.y - m_Size.y / 2.0f;
	float bottomA = centerA.y + m_Size.y / 2.0f;
	float forwardA = centerA.z - m_Size.z / 2.0f;
	float backA = centerA.z + m_Size.z / 2.0f;
	float leftB = centerB.x - other.m_Size.x / 2.0f;
	float rightB = centerB.x + other.m_Size.x / 2.0f;
	float topB = centerB.y - other.m_Size.y / 2.0f;
	float bottomB = centerB.y + other.m_Size.y / 2.0f;
	float forwardB = centerB.z - other.m_Size.z / 2.0f;
	float backB = centerB.z + other.m_Size.z / 2.0f;

	if (leftA   < rightB &&
		rightA  > leftB &&
		topA    < bottomB &&
		bottomA > topB &&
		forwardA < backB &&
		backA    > forwardB)
	{
		result.isHit = true;
		result.overlapX = std::fmin(rightA, rightB) - std::fmax(leftA, leftB);
		result.overlapY = std::fmin(bottomA, bottomB) - std::fmax(topA, topB);
		result.overlapZ = std::fmin(backA, backB) - std::fmax(forwardA, forwardB);

		if (result.overlapX <= result.overlapY && result.overlapX <= result.overlapZ)
		{
			result.normalX = (m_Center.x < other.m_Center.x) ? -1.0f : 1.0f;
		}
		else if (result.overlapY <= result.overlapX && result.overlapY <= result.overlapZ)
		{
			result.normalY = (m_Center.y < other.m_Center.y) ? -1.0f : 1.0f;
		}
		else
		{
			result.normalZ = (m_Center.z < other.m_Center.z) ? -1.0f : 1.0f;
		}
	}

	return result;
}

AABB2D::AABB2D()
{
	m_Type = ColliderType::AABB_2D;
	m_Center = {};
	m_Size = {};
}

void AABB2D::Draw()
{
	VECTOR center = m_Owner->GetPosition() + m_Center;

	float left = center.x - m_Size.x / 2.0f;
	float right = center.x + m_Size.x / 2.0f;
	float top = center.y - m_Size.y / 2.0f;
	float bottom = center.y + m_Size.y / 2.0f;

	DrawBox((int)left, (int)top, (int)right, (int)bottom, GetColor(255, 255, 255), FALSE);
}

CollisionResult AABB2D::CheckCollide(const ColliderComponent& other) const
{
	CollisionResult result = {};

	ColliderType type = other.GetType();
	switch (type)
	{
	case ColliderType::AABB_2D: result = CheckCollideAABB(static_cast<const AABB2D&>(other)); break;
	}

	return result;
}

CollisionResult AABB2D::CheckCollideAABB(const AABB2D& other) const
{
	CollisionResult result = {};
	VECTOR centerA = m_Owner->GetPosition();
	VECTOR centerB = other.m_Owner->GetPosition();
	centerA += m_Center;
	centerB += other.m_Center;

	float leftA = centerA.x - m_Size.x / 2.0f;
	float rightA = centerA.x + m_Size.x / 2.0f;
	float topA = centerA.y - m_Size.y / 2.0f;
	float bottomA = centerA.y + m_Size.y / 2.0f;
	float leftB = centerB.x - other.m_Size.x / 2.0f;
	float rightB = centerB.x + other.m_Size.x / 2.0f;
	float topB = centerB.y - other.m_Size.y / 2.0f;
	float bottomB = centerB.y + other.m_Size.y / 2.0f;

	if (leftA   < rightB &&
		rightA  > leftB &&
		topA    < bottomB &&
		bottomA > topB)
	{
		result.isHit = true;
		result.overlapX = std::fmin(rightA, rightB) - std::fmax(leftA, leftB);
		result.overlapY = std::fmin(bottomA, bottomB) - std::fmax(topA, topB);

		// 押し出し向きの設定
		if (result.overlapX <= result.overlapY)
		{
			result.normalX = (m_Center.x < other.m_Center.x) ? -1.0f : 1.0f;
		}
		else
		{
			result.normalY = (m_Center.y < other.m_Center.y) ? -1.0f : 1.0f;
		}
	}

	return result;
}
