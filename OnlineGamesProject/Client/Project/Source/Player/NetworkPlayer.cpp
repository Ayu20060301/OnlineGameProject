#include "NetworkPlayer.h"
#include "Player.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/ClientAPI.h"

//これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 1.0f;
constexpr float SCALE_THRESHOLD = 0.005f;
constexpr float ROT_THRESHOLD = 0.005f;

NetworkPlayer::NetworkPlayer(int id, bool isSelf) : PlayerBase()
, m_IsSelf(isSelf)
, m_ID(id)
{
	//サーバー座標を使用する
	m_IsUserServerTransform = true;

	//前回送信した座標
	m_LastSentPos = VGet(0.0f, 0.0f, 0.0f);
}

NetworkPlayer::NetworkPlayer(const Client* client, int id, bool isSelf) : PlayerBase()
,m_IsSelf(isSelf)
,m_ID(id)
{
	//サーバー座標を使用する
	m_IsUserServerTransform = true;

	//前回送信した座標
	m_LastSentPos = VGet(0.0f, 0.0f, 0.0f);
}

NetworkPlayer::~NetworkPlayer() = default;

void NetworkPlayer::Step()
{
	// 自分自身しかステップしない
	if (!m_IsSelf) return;
	// オフラインだったらステップしない
	if (!ClientAPI::IsConnected()) return;

	// 移動
	PlayerBase::Step();

	// 動いたかどうか
	bool isMove = false;

	// 移動したらサーバーに座標を送信
	float dist = MyMath::GetDistance(GetPos(), m_LastSentPos);
	if (dist >= POS_THRESHOLD)
	{
		isMove = true;
	}

}
