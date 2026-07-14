#include "ServerHandler.h"
#include "NetworkUtility.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

using namespace Network;

/// <summary>
/// ログイン
/// </summary>
/// <param name="nwHandle"></param>
void ServerHandler::HandleLogin(int nwHandle)
{
    //ログインデータを受信
    Network::RequestLoginData request = {};
    NetWorkRecv(nwHandle, &request, sizeof(request));

    //ID設定
    ResponseLoginData response = {};
    memset(&response, -1, sizeof(response));
    int i = 0;
    auto players = PlayerManager::GetInstance()->GetPlayers();
    for (const auto& player : players)
    {
        response.playerID[i] = player->GetID();
        response.selfID = player->GetID();
        i++;
    }

    //一旦スポーン位置は固定
    response.spawnPos = VGet(100.0f, 100.0f, 0.0f);

    //ログインするクライアントに送信する
    auto buffer = MakePacket<ResponseLoginData>(PacketType::LOGIN, response);
    NetWorkSend(nwHandle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
}

void ServerHandler::HandleLogout(int nwHandle)
{
}

void ServerHandler::OnJoined(int nwHandle, int joinPlayerID)
{
}

void ServerHandler::OnDead(int deadPlayerID)
{
}

void ServerHandler::SyncTransform()
{
}
