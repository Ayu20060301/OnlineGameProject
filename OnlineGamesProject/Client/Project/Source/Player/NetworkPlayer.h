#pragma once

#include "Player.h"

class Client;

/// <summary>
/// ネットワークプレイヤークラス
/// </summary>
class NetworkPlayer : public Player
{
public:
	/// <summary>
	/// ネットワークプレイヤーの生成
	/// </summary>
	/// <param name="id">プレイヤーID</param>
	/// <param name="isSelf">自分が操作するプレイヤーか</param>
	NetworkPlayer(int id, bool isSelf);

	//Clientを受け取るバージョン
	NetworkPlayer(const Client* client, int id, bool isSelf);
	virtual ~NetworkPlayer();

	void Step() override;

	//プレイヤーIDの取得
	int GetID() const { return m_ID; }

	//サーバー座標を設定
	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }
	
	//サーバー回転を設定
	void SetServerRotation(const VECTOR& rot) { m_ServerTransform.SetRotation(rot); }
	
	//サーバースケールを設定
	void SetServerScale(const VECTOR& scale) { m_ServerTransform.SetScale(scale); }
	
private:
	bool m_IsSelf;                //自分自身が操作するかどうか
	int m_ID;                     //識別ID
};
