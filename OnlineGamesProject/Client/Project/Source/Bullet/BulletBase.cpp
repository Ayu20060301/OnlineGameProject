#include "BulletBase.h"
#include "BulletParameter.h"
#include "BulletManager.h"
#include "../MyMath/MyMath.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Component/Collision/CollisionSphere.h"
#include "../Component/Collision/CollisionAABB.h"
#include "../Effect/SpriteAnimationManager.h"

BulletBase::BulletBase()
{
	m_Id = 0;
	m_Handle = 0;
	m_Life = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
	m_Active = false;
	m_Param = nullptr;
	m_SphereCollision = nullptr;
}

BulletBase::~BulletBase()
{
	Fin();
}

void BulletBase::Init(int id)
{
	m_Id = id;
	m_Param = BulletManager::GetInstance()->GetBulletParameter(m_Id);
}

void BulletBase::Load()
{
	// パラメータを元にロード
	m_Handle = LoadGraph(m_Param->path);
}

void BulletBase::Step()
{
	// 寿命を減らす
	m_Life--;

	if (m_Life <= 0)
	{
		m_Active = false;
		// 当たり判定も非アクティブにする
		m_SphereCollision->SetActive(false);
	}
}

void BulletBase::Fin()
{
	DeleteGraph(m_Handle);
}

void BulletBase::Fire(VECTOR pos, VECTOR vec)
{
	m_Active = true;
	m_Pos = pos;
	m_Move = MyMath::VecNormalize(vec);
	m_Move = MyMath::VecScale(m_Move, m_Param->speed);
	m_Life = m_Param->life;
	m_Radius = m_Param->radius;

	CollisionSphere* sphereCollision = CollisionManager::GetInstance()->CreateSphere();
	sphereCollision->SetRadius(m_Param->radius);
	sphereCollision->SetTargetPos(&m_Pos);
	sphereCollision->SetTag(m_Param->collisionTag);
	m_SphereCollision = sphereCollision;

	CollisionAABB* aabbCollision = CollisionManager::GetInstance()->CreateAABB();
	aabbCollision->SetSize(VGet(m_Param->sizeX, m_Param->sizeY, 0.0f));
	aabbCollision->SetTargetPos(&m_Pos);
	aabbCollision->SetTag(m_Param->collisionTag);
	m_AABBCollision = aabbCollision;
}

void BulletBase::Dead()
{
	m_Active = false;
	m_SphereCollision->SetActive(false);

	// ヒットエフェクト（とりあえDeadでOK）
	SpriteAnimationManager::GetInstance()->Play(m_Param->hitEffect, m_Pos, 1);
}

void BulletBase::HitPlayer()
{
	Dead();
}

void BulletBase::HitBlock()
{
	Dead();
}

void BulletBase::ScaleSpeed(float scale)
{
	m_Move = MyMath::VecScale(m_Move, scale);
}
