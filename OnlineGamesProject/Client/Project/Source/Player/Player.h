#pragma once

#include "DxLib.h"
#include "PlayerBase.h"


/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public PlayerBase
{
public:
	Player(); //コンストラクタ
	~Player(); //デストラクタ

	void Step() override;  //ステップ

	void InputMove(); //移動入力
	void InputBullet(); //バレット入力
};
