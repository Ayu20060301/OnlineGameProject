#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Bullet/BulletManager.h"
#include "../GameApp/GameApp.h"
#include "../Network/ClientAPI.h"

NetworkPlayScene::~NetworkPlayScene()
{
	Fin();
}

void NetworkPlayScene::Init()
{
	//プレイヤー管理生成
	PlayerManager::CreateInstance();

	//弾管理生成
	BulletManager::CreateInstance();

	//ログイン
	ClientAPI::RequestLogin();
}

void NetworkPlayScene::Load()
{

}

void NetworkPlayScene::Fin()
{
	//ネットワーク終了
	ClientAPI::Disconnect();

	PlayScene::Fin();
}
