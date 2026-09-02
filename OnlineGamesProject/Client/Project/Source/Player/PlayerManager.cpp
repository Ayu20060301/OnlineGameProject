#include "PlayerManager.h"
#include "Player.h"
#include "NetworkPlayer.h"
#include "../Network/Client.h"

using namespace Network;

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
	Fin();
}

void PlayerManager::Init()
{
	
}

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

void PlayerManager::Update()
{
	for (auto& player : m_Players)
	{
		player->Update();
	}
}

void PlayerManager::Draw()
{
	for (auto& player : m_Players)
	{
		player->Draw();
	}
}

void PlayerManager::Fin()
{
	for (auto& player : m_Players)
	{
		player->Fin();
	}
}

/// <summary>
/// プレイヤーを生成
/// </summary>
/// <returns>生成したプレイヤーを返す</returns>
Player& PlayerManager::CreatePlayer()
{
	//生成して初期化
	UniquePtr<Player> player = MakeUnique<Player>();
	player->Init();

	//リストに追加
	m_Players.push_back(std::move(player));

	return *(m_Players.back().get());
}

/// <summary>
/// ネットワークプレイヤーを生成
/// </summary>
/// <param name="id">プレイヤーID</param>
/// <param name="isSelf">自分が操作するプレイヤーか</param>
/// <returns>追加したプレイヤーを返す</returns>
NetworkPlayer& PlayerManager::CreateNetworkPlayer(int id, bool isSelf)
{
	// ネットワークプレイヤーを生成
	UniquePtr<NetworkPlayer> player = MakeUnique<NetworkPlayer>(id, isSelf);
	
	//初期化
	player->Init();
	
	//画像のロード
	player->Load();
	
	//開始処理
	player->Start();

	//Playerリストに追加
	m_Players.push_back(std::move(player));

	return *static_cast<NetworkPlayer*>(m_Players.back().get());
}

/// <summary>
/// ログイン処理
/// </summary>
/// <param name="data">ログインデータ</param>
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

/// <summary>
/// サーバーから受信したTransormを同期
/// </summary>
/// <param name="data">サーバーから受信したTransform</param>
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

/// <summary>
/// プレイヤーを死亡させる
/// </summary>
/// <param name="playerID">志望するプレイヤーID</param>
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
