#pragma once

#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../Component/Transform.h"

class Splite;
class Controller2D;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init(); //初期化
	void Load(); //ロード
	void Start(); //ステップ
	virtual void Step();
	virtual void Draw();

	//アクセサ
	void SetPos(const VECTOR& pos) { m_Transform.SetPos(pos); }
	void SetRot(const VECTOR& rot) { m_Transform.SetRot(rot); }
	void SetScale(const VECTOR& scale) { m_Transform.SetScale(scale); }
	
protected:
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Transform m_Transform;
	UniquePtr<Splite> m_Splite;
	UniquePtr<Controller2D> m_Controller;
};
