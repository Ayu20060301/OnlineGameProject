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
	NetworkPlayer& CreateNetworkPlayer(int id, bool isSelf);
	void Login(Network::ResponseLoginData data);
	void Join(Network::JoinData data);
	void Logout(Network::LogoutData data);
	void SyncServerTransform(Network::ResponseTransformData data);
	void DiePlayer(int playerID);

private:

	//生成されたプレイヤーの参照
	std::list<UniquePtr<Player>> m_Players;
};
