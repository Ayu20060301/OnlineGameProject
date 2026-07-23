#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/ClientAPI.h"


//これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 1.0f;
constexpr float SCALE_THRESHOLD = 0.005f;
constexpr float ROT_THRESHOLD = 0.005f;

NetworkPlayer::NetworkPlayer(int id, bool isSelf) : Player()
, m_IsSelf(isSelf)
, m_ID(id)
{
	//サーバー座標を使用する
	m_UserServerTransform = true;

}

NetworkPlayer::NetworkPlayer(const Client* client, int id, bool isSelf) : Player()
,m_IsSelf(isSelf)
,m_ID(id)
{
	//サーバー座標を使用する
	m_UserServerTransform = true;
}

NetworkPlayer::~NetworkPlayer() = default;

void NetworkPlayer::Step()
{
	// 自分自身しかステップしない
	if (!m_IsSelf) return;
	// オフラインだったらステップしない
	if (!ClientAPI::IsConnected()) return;

	// 移動
	Player::Step();

	// 動いたかどうか
	bool isMove = false;

	// 移動したらサーバーに座標を送信
	float dist = MyMath::GetDistance(m_Transform.GetPosition(), m_ServerTransform.GetPosition());
	if (dist >= POS_THRESHOLD)
	{
		isMove = true;
	}

	// 動いたらトランスフォームを送信
	if (isMove)
	{
		ClientAPI::RequestTransform(m_ID, m_Transform);
	}
	
}
