#include "PlayerManager.h"
#include "Player.h"
#include "NetworkPlayer.h"
#include "../Network/Client.h"

using namespace Network;

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


NetworkPlayer& PlayerManager::CreateNetworkPlayer(int id, bool isSelf)
{
	// 生成して初期化～開始
	UniquePtr<NetworkPlayer> player = MakeUnique<NetworkPlayer>(id, isSelf);
	player->Init();
	player->Load();
	player->Start();

	// 末尾に格納
	m_Players.push_back(std::move(player));

	// 実は参照渡しの方が安全
	return *static_cast<NetworkPlayer*>(m_Players.back().get());
}

void PlayerManager::Login(Network::ResponseLoginData data)
{
	// 既に参加済みのプレイヤーも含め生成
	for (int i = 0; i < Network::NETWORK_PLAYER_MAX; i++)
	{
		int id = data.playerID[i];
		if (id <= 0) continue;

		bool isSelf = id == data.selfID;
		NetworkPlayer& player = CreateNetworkPlayer(id, isSelf);
		
		// スポーン位置に移動
		player.SetPosition(data.spawnPos);
		player.SetServerPosition(data.spawnPos);
		
	}
}

/// <summary>
/// プレイヤーを参加させる
/// </summary>
/// <param name="data">参加データ</param>
void PlayerManager::Join(Network::JoinData data)
{
	//参加プレイヤーを生成
	NetworkPlayer& player = CreateNetworkPlayer(data.playerID, false);
	
	player.SetPosition(data.spawnPos);
	player.SetServerPosition(data.spawnPos);
	
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

void PlayerManager::SyncServerTransform(Network::ResponseTransformData data)
{
	//全プレイヤーのトランスフォームをサーバーから受信したものにする
	int i = 0;
	for (auto& player : m_Players)
	{
		NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>(player.get());
		
		nwPlayer->SetServerPosition(data.pos[i]);
		nwPlayer->SetServerRotation(data.rot[i]);
		nwPlayer->SetServerScale(data.scale[i]);
		
		i++;
	}
}

void PlayerManager::DiePlayer(int playerID)
{
	//IDが一致したプレイヤーを死亡させる
	for (auto itr = m_Players.begin(); itr != m_Players.end(); itr++)
	{
		NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>((*itr).get());

		if (nwPlayer->GetID() == playerID)
		{
		    nwPlayer->Die();
			break;
		}
	}
}
