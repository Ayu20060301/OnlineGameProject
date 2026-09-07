#pragma once


#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../GameObject/GameObject.h"


//バレットサイズ
constexpr int BULLET_WIDTH = 20;
constexpr int BULLET_HEIGHT = 20;

//発射する弾のインターバル
constexpr int FIRE_INTERVAL = 20;

/// <summary>
/// バレットクラス
/// </summary>
class Bullet : public GameObject
{
public:
	Bullet();
	virtual ~Bullet();

	void Init();
	void Load();
	void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	void FireBullet(VECTOR playerPos); //弾を発射させる処理

public:
	bool IsActive() { return m_IsActive; }

	void SetActive(bool isActive) { m_IsActive = isActive; }

	void SetPosition(VECTOR pos) { m_Transform.SetPosition(pos); }

	VECTOR GetPos() const { return m_Transform.GetPosition(); }

private:
	float m_MoveSpeed;
	bool m_IsActive;
	VECTOR m_Velocity;
	int m_Handle;
	int m_PlayerNumber;
	int m_FireTimer;
};
