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
	Player(); //コンストラクタ
	virtual ~Player(); //デストラクタ

	void Init(); //初期化処理
	void Load(); //ロード
	void Start(); //スタート
	virtual void Step(); //ステップ
	virtual void Update(); //更新処理
	virtual void Draw(); //描画処理
	virtual void Fin(); //終了

public:
	//プレイヤーが生きているか
	bool IsActive() const { return m_IsActive; }

	//無敵状態か
	bool IsInvisible() const { return m_InvisibleTimer > 0; }
	
	//プレイヤーの座標を取得
	VECTOR GetPos() const { return m_Transform.GetPosition(); }
	
	
	CollisionAABB* GetCollisionAABB() { return m_CollisionAABB; }
	CollisionSphere* GetCollisionSphere() const { return m_CollisionSphere; }
	float GetMoveSpeed() const { return m_MoveSpeed; }

	void SetActive(bool active) { m_IsActive = active; }
	void SetPlayerNumber(int number) { m_PlayerNumber = number; }

	void Die();

	//アニメーションの更新
	void UpdateAnimation();

protected:

	//移動方向からプレイヤーの向きを決定
	void SetDirectionForMove();

	bool m_IsActive; //プレイヤーが生きているか
	float m_MoveSpeed; //移動速度
	
	Splite* m_Splite;
	Controller2D* m_Controller; //2Dコントローラー
	int m_Handle; //プレイヤー画像
	int m_PlayerNumber; //プレイヤー番号
	int m_InvisibleTimer; //無敵タイマー
	int m_Direction; //プレイヤーの向き
	int m_AnimationIndex; //現在のアニメーション番号
	int m_AnimationTimer; //アニメーションタイマー
	VECTOR m_OldPos; //移動前の座標
	VECTOR m_Move; //1フレームの移動量

	//当たり判定
	CollisionAABB* m_CollisionAABB;
	CollisionSphere* m_CollisionSphere;
};
