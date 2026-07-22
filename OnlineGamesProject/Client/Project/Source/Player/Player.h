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
	Player(); //コンストラクタ
	virtual ~Player(); //デストラクタ

	void Init();
	void Load();
	void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();

	void UpdateAnimation(); //アニメーションの更新
	void Die();

protected:
	int m_ID; 
	int m_AnimationIndex = 0;
	int m_AnimationTimer = 0;
	bool m_IsActive;
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Splite* m_Splite;
	Controller2D* m_Controller;
};
