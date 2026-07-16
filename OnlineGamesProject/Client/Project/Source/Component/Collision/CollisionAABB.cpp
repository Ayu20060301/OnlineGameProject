#include "DxLib.h"
#include "CollisionAABB.h"
#include "../../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"

// コンストラクタ
CollisionAABB::CollisionAABB()
{
	m_Id = COLLISION_AABB;
	m_Size = VGet(0.0f, 0.0f, 0.0f);
}

// デストラクタ
CollisionAABB::~CollisionAABB()
{
}

void CollisionAABB::Draw()
{
}

bool CollisionAABB::CheckAABB(CollisionAABB* other)
{
	VECTOR pos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	VECTOR otherSize = other->GetSize();

	// 自身のボックスの各面の値
	float left = pos.x;	// 左
	float right = pos.x + m_Size.x;	// 右
	float top = pos.y;	// 上
	float bottom = pos.y + m_Size.y;	// 下

	// 対象のボックスの各面の値
	float otherLeft = otherPos.x;	// 左
	float otherRight = otherPos.x + otherSize.x;	// 右
	float otherTop = otherPos.y;	// 上
	float otherBottom = otherPos.y + otherSize.y;	// 下

	// 交差していれば当たっている
	if (left < otherRight && right > otherLeft &&
		bottom > otherTop && top < otherBottom)
	{
		return true;
	}

	return false;
}

