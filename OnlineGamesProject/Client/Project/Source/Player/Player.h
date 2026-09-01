#pragma once

#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../GameObject/GameObject.h"

//前方宣言
class Splite;
class Controller2D;
class CollisionAABB;
class CollisionSphere;
class Block;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Load();
	void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

public:
	bool IsActive() const { return m_IsActive; }
	bool IsInvisible() const { return m_InvisibleTimer > 0; }
	bool IsBulletInterval() const { return m_BulletInterval > 0; }
	VECTOR GetPos() const { return m_Pos; }
	CollisionAABB* GetCollisionAABB() { return m_CollisionAABB; }
	CollisionSphere* GetCollisionSphere() const { return m_CollisionSphere; }
	float GetMoveSpeed() const { return m_MoveSpeed; }
	float GetBulletChargeSpeed() const { m_BulletChargeSpeed; }
	float GetBulletSpeed() const { m_BulletSpeed; }

	void SetActive(bool active) { m_IsActive = active; }
	void SetPlayerNumber(int number) { m_PlayerNumber = number; }

	void FireBullet(); //弾を発射させる処理
	void Die();

	//アニメーションの更新
	void UpdateAnimation();

protected:
	void SetDirectionForMove();

	bool m_IsActive;
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Splite* m_Splite;
	Controller2D* m_Controller;
	int m_Handle;
	int m_PlayerNumber;
	int m_InvisibleTimer;
	int m_Direction;
	int m_AnimationIndex;
	int m_AnimationTimer;
	int m_UseBulletID;
	int m_Stiffness;
	float m_BulletInterval;
	float m_BulletIntervalTime;
	float m_BulletChargeSpeed;
	float m_BulletSpeed;
	VECTOR m_Pos;
	VECTOR m_OldPos;
	VECTOR m_Move;
	CollisionAABB* m_CollisionAABB;
	CollisionSphere* m_CollisionSphere;
};
