#pragma once


#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../GameObject/GameObject.h"

class Splite;

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


public:
	bool IsActive() { return m_IsActive; }

	void SetActive(bool isActive) { m_IsActive = isActive; }

	void SetPosition(VECTOR pos) { m_Transform.SetPosition(pos); }

	VECTOR GetPos() const { return m_Transform.GetPosition(); }

	virtual bool IsNetworkBullet() const { return false; }

	void SetPlayerNumber(int playerNumber) { m_PlayerNumber = playerNumber; };

	void SetVelocity(VECTOR velocity) { m_Velocity = velocity; }

private:
	bool m_IsActive;
	VECTOR m_Velocity;
	int m_PlayerNumber;
	int m_FireTimer;
	Splite* m_Splite;
};
