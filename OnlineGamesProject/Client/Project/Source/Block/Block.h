#pragma once

#include "DxLib.h"

class CollisionAABB;

class Block
{
public:
	Block();
	~Block();

public:
	void Load();   //ロード
	void Start();   //開始
	void Draw();   //描画
	void Fin();   //終了

public:
	Block* Clone();  //クローン

	bool IsActive() const { return m_IsActive; }
	CollisionAABB* GetCollision() const { return m_Collision; }
	VECTOR GetPos() const { return m_Pos; }

	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	bool m_IsActive;   
	int m_Handle;     //画像ハンドル
	VECTOR m_Pos;     //座標
	CollisionAABB* m_Collision;  //当たり判定
};
