#pragma once

#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../GameObject/GameObject.h"

//前方宣言
class Splite;
class Controller2D;

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
