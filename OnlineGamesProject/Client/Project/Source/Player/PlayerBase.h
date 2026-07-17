#pragma once

#include "DxLib.h"

class CollisionAABB;
class CollisionSphere;
class Block;


class PlayerBase
{
protected:
	PlayerBase();
	virtual ~PlayerBase();


public:
	void Init();       //初期化
	void Load();       //ロード
	void Start();      //スタート
	virtual void Step();  //ステップ
	void Update();     //更新
	void Draw();       //描画
	void Fin();       //終了

public:
	bool IsActive() const { return m_IsActive; }
	bool IsInvisible() const { return m_InvisibleTimer > 0; }

protected:
	bool m_IsActive;
	int m_Handle;
	int m_PlayerNumber;
	int m_InvisibleTimer;
	int m_Direction;


};
