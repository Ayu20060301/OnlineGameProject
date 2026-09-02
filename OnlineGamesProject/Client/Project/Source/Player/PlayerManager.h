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

public:
	void Init(); //初期化
	void Load(); //ロード
	void Start(); //開始
	void Step(); //ステップ
	void Update(); //更新
	void Draw(); //描画
	void Fin(); //終了

public:
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
