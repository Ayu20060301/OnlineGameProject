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
class BulletManager;


//プレイヤーのサイズ
constexpr int PLAYER_WIDTH = 40;
constexpr int PLAYER_HEIGHT = 40;

//プレイヤーアニメーション
constexpr int PLAYER_ANIM_GRAPH_NUM = 4; //アニメーション枚数
constexpr int PLAYER_CHANGE_ANIM_TIME = 5; //アニメーション切り替え時間
constexpr float PLAYER_CHANGE_DIR_MOVE_DISTANCE = 0.1f;

//無敵中の点滅間隔
constexpr int PLAYER_INVISIBLE_BLINK_TIME = 4; //無敵点滅時間

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
	
	//プレイヤーの座標を取得
	VECTOR GetPos() const { return m_Transform.GetPosition(); }
	
	float GetMoveSpeed() const { return m_MoveSpeed; }

	void SetActive(bool active) { m_IsActive = active; }

	void Die();

protected:

	bool m_IsActive; //プレイヤーが生きているか
	float m_MoveSpeed; //移動速度
	Splite* m_Splite;
	Controller2D* m_Controller; //2Dコントローラー

	//以下ネットワーク用
	bool m_UserServerTransform;
	Transform m_ServerTransform;
};
