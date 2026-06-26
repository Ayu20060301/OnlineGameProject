#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	PlayerManager::CreateInstance();
	Player& player = PlayerManager::GetInstance()->CreatePlayer();
}

void PlayScene::Load()
{
	PlayerManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	PlayerManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	PlayerManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
}
