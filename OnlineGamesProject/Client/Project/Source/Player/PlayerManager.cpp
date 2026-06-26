#include "PlayerManager.h"
#include "Player.h"
#include "NetworkPlayer.h"
#include "../Network//Client.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager() = default;

void PlayerManager::Load()
{
	for (auto& player : m_Players)
	{
		player->Load();
	}
}

void PlayerManager::Start()
{
	for (auto& player : m_Players)
	{
		player->Start();
	}
}

void PlayerManager::Step()
{
	for (auto& player : m_Players)
	{
		player->Step();
	}
}

void PlayerManager::Draw()
{
	for (auto& player : m_Players)
	{
		player->Draw();
	}
}

/// <summary>
/// プレイヤーを生成
/// </summary>
/// <returns></returns>
Player& PlayerManager::CreatePlayer()
{
	//生成して初期化
	UniquePtr<Player> player = MakeUnique<Player>();
	player->Init();

	//末尾に格納
	m_Players.push_back(std::move(player));

	return *(m_Players.back().get());
}

/// <summary>
/// ネットワークプレイヤーの生成
/// </summary>
/// <param name="client">通信に使われているクライアントクラス</param>
/// <param name="id">ID</param>
/// <param name="isSelf"></param>
/// <returns></returns>
NetworkPlayer& PlayerManager::CreateNetworkPlayer(const Client* client, int id, bool isSelf)
{
	//生成して初期化～開始
	UniquePtr<NetworkPlayer> player = MakeUnique<NetworkPlayer>(client, id, isSelf);
	player->Init();
	player->Load();
	player->Start();

	//末尾に格納
	m_Players.push_back(std::move(player));

	return *static_cast<NetworkPlayer*>(m_Players.back().get());
}

/// <summary>
/// プレイヤーを追加する
/// </summary>
/// <param name="client">通信に使われているクライアントクラス</param>
/// <param name="data">ログインデータ</param>
void PlayerManager::Login(const Client* client, Network::LoginData data)
{
	//既に参加済みのプレイヤーも含め生成
	for (int i = 0; i < NETWORK_PLAYER_MAX; i++)
	{
		int id = data.playerID[i];
		if (id < 0) return;

		bool isSelf = id == data.selfID;
		CreateNetworkPlayer(client, id, isSelf);
	}
}

/// <summary>
/// プレイヤーを参加させる
/// </summary>
/// <param name="data">参加データ</param>
void PlayerManager::Join(Network::JoinData data)
{
	//参加プレイヤーを生成
	CreateNetworkPlayer(nullptr, data.playerID, false);
}

/// <summary>
/// プレイヤーを退出させる
/// </summary>
/// <param name="data">ログアウトデータ</param>
void PlayerManager::Logout(Network::LogoutData data)
{
	//IDが一致したプレイヤーはログアウトするので削除
	for (auto itr = m_Players.begin(); itr != m_Players.end(); itr++)
	{
		const NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>((*itr).get());

		if (nwPlayer->GetID() == data.playerID)
		{
			m_Players.erase(itr);
			break;
		}
	}
}

/// <summary>
/// 座標を同期する
/// </summary>
/// <param name="data">座標データ</param>
void PlayerManager::SyncTransform(Network::AllTransformData data)
{
	//全プレイヤーのトランスフォームをサーバーから受信したものにする
	int i = 0;
	for (auto& player : m_Players)
	{
		NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>(player.get());
		nwPlayer->SetServerPos(data.pos[i]);
		nwPlayer->SetServerRot(data.rot[i]);
		nwPlayer->SetServerScale(data.scale[i]);
		i++;
	}
}
