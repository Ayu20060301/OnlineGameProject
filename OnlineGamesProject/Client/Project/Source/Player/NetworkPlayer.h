#pragma once

#include "PlayerBase.h"

class Client;

/// <summary>
/// ネットワークプレイヤークラス
/// </summary>
class NetworkPlayer : public PlayerBase
{
public:
	NetworkPlayer(int id, bool isSelf);
	NetworkPlayer(const Client* client, int id, bool isSelf);
	virtual ~NetworkPlayer();

	void Step() override;

	int GetID() const { return m_ID; }

	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }
	void SetServerRotation(const VECTOR& rot) { m_ServerTransform.SetRotation(rot); }
	void SetServerScale(const VECTOR& scale) { m_ServerTransform.SetScale(scale); }

private:
	bool m_IsSelf;                //自分自身が操作するかどうか
	int m_ID;                     //識別ID
	VECTOR m_LastSentPos;          //前回送信した座標
};
