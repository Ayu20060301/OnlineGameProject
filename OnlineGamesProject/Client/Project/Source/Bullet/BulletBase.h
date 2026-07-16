#pragma once

#include "DxLib.h"
#include "BulletParameter.h"

class CollisionSphere;
class CollisionAABB;

class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

public:
	virtual void Init(int id);
	virtual void Load();
	virtual void Step();
	virtual void Draw() = 0;
	virtual void Fin();
	virtual BulletBase* Clone() = 0;
	virtual void Fire(VECTOR pos, VECTOR vec);

	void Dead();

public:
	bool IsActive() const { return m_Active; }
	int GetID() const { return m_Id; }
	int GetDamage() const { return m_Param->damage; }
	VECTOR GetPos() const { return m_Pos; }
	CollisionSphere* GetSphereCollision() const { return m_SphereCollision; }
	CollisionAABB* GetAABBCollision() const { return m_AABBCollision; }

	void HitPlayer();
	void HitBlock();

	void ScaleSpeed(float speed);

protected:
	bool m_Active;
	int m_Id;
	int m_Handle;
	int m_Life;
	VECTOR m_Pos;
	VECTOR m_Move;
	float m_Radius;
	const BulletParameter* m_Param;
	CollisionSphere* m_SphereCollision;
	CollisionAABB* m_AABBCollision;
};
