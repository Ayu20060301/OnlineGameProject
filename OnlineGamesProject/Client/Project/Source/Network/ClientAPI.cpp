#include "ClientAPI.h"
#include "NetworkUtility.h"
#include "../Player/PlayerManager.h"

Client g_Client;

using namespace Network;

void ClientAPI::Connect()
{
    g_Client.Connect();
}

void ClientAPI::Disconnect()
{
    g_Client.Disconnect();
}

void ClientAPI::Step()
{
    g_Client.Step();

    if (g_Client.CheckReceive())
    {
        //ヘッダーのみを受信
        Network::PacketHeader header = {};
        g_Client.ReceiveData(reinterpret_cast<char*>(&header), sizeof(header));

        switch (header.type)
        {
            case Network::PacketType::LOGIN:             OnReceiveLogin();          break;
            case Network::PacketType::JOIN:              OnReceiveJoin();           break;
            case Network::PacketType::LOGOUT:            OnReceiveLogout();         break;
            case Network::PacketType::ALL_TRANSFORM:     OnReceiveAllTransform();   break;
            case Network::PacketType::DIE:               OnReceiveDead();           break;
        }
    }
}

void ClientAPI::Draw()
{
    g_Client.Draw();
}

bool ClientAPI::IsConnected()
{
    return g_Client.IsConnected();
}

void ClientAPI::RequestLogin()
{
    RequestLoginData data = {};

    auto packet = MakePacket<RequestLoginData>(PacketType::LOGIN, data);
    g_Client.SendData(packet.data(), (unsigned int)packet.size());
}

void ClientAPI::RequestLogout(int playerID)
{
    LogoutData data = {};
    data.playerID = playerID;

    auto packet = MakePacket<LogoutData>(PacketType::LOGOUT, data);
    g_Client.SendData(packet.data(), (unsigned int)packet.size());
}

void ClientAPI::RequestTransform(int playerID, Transform transform)
{
    RequestTransformData data = {};

    data.playerID = playerID;
    data.pos = transform.GetPosition();
    data.rot = transform.GetRotation();
    data.scale = transform.GetScale();

    std::vector<uint8_t> buf = MakePacket<RequestTransformData>(PacketType::TRANSFORM, data);
    g_Client.SendData(buf.data(), (unsigned int)buf.size());
}

void ClientAPI::OnReceiveLogin()
{
    //ログインデータを受信
    Network::ResponseLoginData data = {};
    g_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

    //ログイン処理
    PlayerManager::GetInstance()->Login(data);   
}

void ClientAPI::OnReceiveJoin()
{
    //参加データを受信
    Network::JoinData data = {};
    g_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

    //プレイヤー参加処理
    PlayerManager::GetInstance()->Join(data);
}

void ClientAPI::OnReceiveLogout()
{
    //ログアウトデータを受信
    Network::LogoutData data = {};
    g_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

    //ログアウト
    PlayerManager::GetInstance()->Logout(data);
}

void ClientAPI::OnReceiveAllTransform()
{
    //座標データを受信
    Network::ResponseTransformData data = {};
    g_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

    //座標同期
    PlayerManager::GetInstance()->SyncServerTransform(data);
}

void ClientAPI::OnReceiveDead()
{
    //死亡データを受信
    Network::DieData data = {};
    g_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

    //死亡させる
    PlayerManager::GetInstance()->DiePlayer(data.playerID);
}

void ClientAPI::Fin()
{
    g_Client.Fin();
}
