#pragma once
#include "Wall.h"

class Client;


/// <summary>
/// ネットワーク壁クラス
/// </summary>
class NetworkWall : public Wall
{
public:
	NetworkWall();
	virtual ~NetworkWall();

	void Step() override;

	//サーバー座標を設定
	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }
};
