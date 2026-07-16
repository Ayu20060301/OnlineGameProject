#include "DxLib.h"
#include "CollisionSphere.h"
#include "../../MyMath/MyMath.h"
#include "../..\Player/PlayerManager.h"
#include "../Collision/CollisionManager.h"

// コンストラクタ
CollisionSphere::CollisionSphere()
{
	m_Id = COLLISION_SPHERE;
	m_Radius = 0.0f;
}

// デストラクタ
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Draw()
{
#if 0
	// デバッグ用の当たり判定の可視化
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);

	// プレイヤーのローカル座標に変換する
	centerPos = PlayerManager::GetInstance()->ConvertPlayerLocalPos(centerPos);

	DrawSphere3D(centerPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
#endif
}

bool CollisionSphere::CheckSphere(CollisionSphere* other)
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	float otherRadius = other->GetRadius();

	// ２つの球の中心間の距離を計算する
	VECTOR vec = MyMath::VecCreate(centerPos, otherCenterPos);
	float distance = MyMath::VecLong(vec);

	// 計算した距離が２つの球の半径の合計以下であれば当たっている
	if (distance <= m_Radius + otherRadius)
	{
		return true;
	}

	return false;
}

