#pragma once

#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../GameObject/GameObject.h"

class Splite;
class Controller2D;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init(); //初期化
	void Load(); //ロード
	void Start(); //ステップ
	virtual void Step();
	virtual void Draw();

	void Die();

protected:
	bool m_IsActive;
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Splite* m_Splite;
	Controller2D* m_Controller;
};
