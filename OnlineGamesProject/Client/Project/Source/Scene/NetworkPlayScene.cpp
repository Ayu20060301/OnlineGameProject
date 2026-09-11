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
	//ログイン
	ClientAPI::RequestLogin();

	//プレイヤー管理生成
	PlayerManager::CreateInstance();

	//弾管理生成
	BulletManager::CreateInstance();
}

void NetworkPlayScene::Load()
{

}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();

	//ネットワーク終了
	ClientAPI::Disconnect();
}
