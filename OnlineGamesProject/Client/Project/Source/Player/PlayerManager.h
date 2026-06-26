#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include "../Network/NetworkCommonParam.h"
#include <list>

class Player;
class NetworkPlayer;
class Client;

/// <summary>
/// プレイヤーオブジェクト管理クラス
/// </summary>
class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	virtual ~PlayerManager();

	void Load();
	void Start();
	void Step();
	void Draw();

	//機能
	Player& CreatePlayer();

	//ネットワーク関係
	NetworkPlayer& CreateNetworkPlayer(const Client* client, int id, bool isSelf);
	void Login(const Client* client, Network::LoginData data);
	void Join(Network::JoinData data);
	void Logout(Network::LogoutData data);

	/// <summary>
	/// 座標を同期する
	/// </summary>
	/// <param name="data">座標データ</param>
	void SyncTransform(Network::AllTransformData data);
private:
	std::list<UniquePtr<Player>> m_Players;
};
