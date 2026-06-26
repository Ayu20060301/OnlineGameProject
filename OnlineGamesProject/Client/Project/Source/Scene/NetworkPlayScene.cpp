#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/NetworkPlayer.h"
#include "../Network/Client.h"

NetworkPlayScene::NetworkPlayScene()
{
}

NetworkPlayScene::~NetworkPlayScene()
{
	Fin();
}

void NetworkPlayScene::Init()
{
	//クライアントクラス生成
	m_Client = MakeUnique<Client>();

	//サーバーに接続
	m_Client->Connect();

	//プレイヤー管理生成
	PlayerManager::CreateInstance();
}

void NetworkPlayScene::Load()
{
}

void NetworkPlayScene::Step()
{
	PlayScene::Step();

	//クライアントステップ
	m_Client->Step();

	//常に受信がないか見張る
	ReceiveData();
}

void NetworkPlayScene::Draw()
{
	PlayScene::Draw();

	if (m_Client) m_Client->Draw();
}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();
}

void NetworkPlayScene::ReceiveData()
{
	if (m_Client->CheckReceive())
	{
		//ヘッダーのみを受信
		Network::PacketHeader header = {};
		m_Client->ReceiveData(reinterpret_cast<char*>(&header), sizeof(header));

		switch (header.type)
		{
		    case Network::PacketType::LOGIN:          ReceiveLogin(); break;
		    case Network::PacketType::JOIN:           ReceiveJoin(); break;
		    case Network::PacketType::LOGOUT:         ReceiveLogout(); break;
		    case Network::PacketType::ALL_TRANSFORM:  ReceiveAllTransform(); break;
		}
	}
}

void NetworkPlayScene::ReceiveLogin()
{
	//ログインデータを受信
	Network::LoginData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	//ログイン処理
	PlayerManager::GetInstance()->Login(m_Client.get(), data);
}

void NetworkPlayScene::ReceiveJoin()
{
	//参加データを受信
	Network::JoinData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	//プレイヤー参加処理
	PlayerManager::GetInstance()->Join(data);
}

void NetworkPlayScene::ReceiveLogout()
{
	//ログアウトデータを受信
	Network::LogoutData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	//ログアウト処理
	PlayerManager::GetInstance()->Logout(data);
}

/// <summary>
/// サーバー側から全クライアントのトランスフォームを受信する
/// </summary>
void NetworkPlayScene::ReceiveAllTransform()
{
	//座標データを受信
	Network::AllTransformData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	//座標同期
	PlayerManager::GetInstance()->SyncTransform(data);
}
