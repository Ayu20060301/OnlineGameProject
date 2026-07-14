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
    // ログアウトデータを受信
    Network::LogoutData request = {};
    NetWorkRecv(nwHandle, &request, sizeof(request));

    // 通信データサイズ
    size_t dataSize = sizeof(PacketHeader) + sizeof(LogoutData);

    PacketHeader header = {};
    header.type = PacketType::LOGOUT;
    header.size = sizeof(LogoutData);

    // ID設定
    LogoutData data = {};
    data.playerID = request.playerID;

    // 全クライアントに送信する
    auto buffer = MakePacket<LogoutData>(PacketType::LOGOUT, data);
    auto players = PlayerManager::GetInstance()->GetPlayers();
    for (const auto& player : players)
    {
        NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
    }
}

void ServerHandler::OnJoined(int nwHandle, int joinPlayerID)
{
    // 通信データサイズ
    size_t dataSize = sizeof(PacketHeader) + sizeof(JoinData);

    PacketHeader header = {};
    header.type = PacketType::JOIN;
    header.size = sizeof(JoinData);

    // データ設定
    JoinData data = {};
    data.playerID = joinPlayerID;
    data.spawnPos = VGet(100.0f, 100.0f, 0.0f);

    // 参加するクライアント以外の全クライアントに送信する
    auto buffer = MakePacket<JoinData>(PacketType::JOIN, data);
    auto players = PlayerManager::GetInstance()->GetPlayers();
    for (const auto& player : players)
    {
        if (player->GetID() != joinPlayerID)
        {
            NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
        }
    }
}

void ServerHandler::OnDead(int deadPlayerID)
{
    // 通信データサイズ
    size_t dataSize = sizeof(PacketHeader) + sizeof(DieData);

    PacketHeader header = {};
    header.type = PacketType::DIE;
    header.size = sizeof(DieData);

    // ID設定
    DieData data = {};
    data.playerID = deadPlayerID;

    // 全クライアントに送信
    auto buffer = MakePacket<DieData>(PacketType::DIE, data);
    auto players = PlayerManager::GetInstance()->GetPlayers();
    for (const auto& player : players)
    {
        NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
    }
}

void ServerHandler::SyncTransform()
{
    // 通信データサイズ
    size_t dataSize = sizeof(PacketHeader) + sizeof(ResponseTransformData);

    PacketHeader header = {};
    header.type = PacketType::ALL_TRANSFORM;
    header.size = sizeof(ResponseTransformData);

    // データ設定
    ResponseTransformData data = {};
    int i = 0;
    auto players = PlayerManager::GetInstance()->GetPlayers();
    for (const auto& player : players)
    {
        data.pos[i] = player->GetPosition();
        data.rot[i] = player->GetRotation();
        data.scale[i] = player->GetScale();;
        i++;
    }

    // 全クライアントに送信する
    auto buffer = MakePacket<ResponseTransformData>(PacketType::ALL_TRANSFORM, data);
    for (const auto& player : players)
    {
        NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
    }
}
