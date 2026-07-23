#include "DxLib.h"
#include "Server.h"
#include "ServerHandler.h"
#include "NetworkCommonParam.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include <vector>


using namespace Network;

Server::Server()
{

}

Server::~Server()
{
	Fin();
}

void Server::Init()
{
	//サーバー用プレイヤー管理
	PlayerManager::CreateInstance();

	//当たり判定はサーバー側でする
	CollisionManager::GetInstance()->CreateInstance();

	//接続してくるのを待つ状態にする
	int sucess = PreparationListenNetWork(PORT_NUMBER);
}

void Server::Update()
{
	//新しい接続があったらネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();

	//新しい接続があった
	if (acceptHandle != -1)
	{
		AddUserData(acceptHandle);
	}

	//切断があったらそのネットワークハンドルを得る
	int lostHandle = GetLostNetWork();

	//切断があった
	if (lostHandle != -1)
	{
		PlayerManager::GetInstance()->RemovePlayer(lostHandle);

	}

	//データ受信処理
	ReceiveData();
}

void Server::Draw()
{
	PlayerManager::GetInstance()->Draw();
	CollisionManager::GetInstance()->Draw();
}

void Server::Fin()
{
	//プレイヤー終了
	PlayerManager::DeleteInstance();

	//当たり判定終了
	CollisionManager::DeleteInstance();
}


/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	//プレイヤー生成
	Player& player = PlayerManager::GetInstance()->CreatePlayer();
	player.Init(handle);

	//参加データを送信
	ServerHandler::OnJoined(handle, player.GetID());
}

/// <summary>
/// ユーザーデータを除外
/// </summary>
void Server::ReceiveData()
{
	//接続しているクライアント全員分処理する
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		int nwHandle = player->GetNetworkHandle();

		//クライアントから送られたデータのサイズを取得
		int dataLength = GetNetWorkDataLength(nwHandle);

		//データが送られてきたかチェック
		if (dataLength > 0)
		{
			//ヘッダーのみを受信
			PacketHeader header = {};
			NetWorkRecv(nwHandle, reinterpret_cast<char*>(&header), sizeof(header));

			//パケットごとの処理
			switch (header.type)
			{
			    case PacketType::LOGIN:        ServerHandler::HandleLogin(nwHandle);    break;  //ログイン
			    case PacketType::LOGOUT:       ServerHandler::HandleLogout(nwHandle);   break;  //ログアウト
			    case PacketType::TRANSFORM:    SyncTransform(nwHandle);    break;  //トランスフォーム
			}
		}
	}
}

/// <summary>
/// トランスフォームの同期
/// </summary>
/// <param name="handle">受信したクライアントのハンドル</param>
void Server::SyncTransform(int handle)
{
	//トランスフォームデータを受信
	Network::RequestTransformData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (auto& player : players)
	{
		//IDが一致したプレイヤーのトランスフォームを更新する
		if (player->GetID() == data.playerID)
		{
			player->SetPosition(data.pos);
			player->SetRotation(data.rot);
			player->SetScale(data.scale);
			break;
		}
	}

	//当たり判定
	CheckCollision();

	//全員の座標を同期
	ServerHandler::SyncTransform();
}

/// <summary>
/// 当たり判定
/// </summary>
void Server::CheckCollision()
{
	CollisionManager::GetInstance()->CheckCollision();
}
