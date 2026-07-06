#include "PlayerManager.h"
#include "Player.h"

PlayerManager::PlayerManager()
{
	m_Players = {};
}

void PlayerManager::Draw()
{
	//全プレイヤーの描画
	for (const auto& player : m_Players)
	{
		
	}
}

Player& PlayerManager::CreatePlayer()
{
	// TODO: return ステートメントをここに挿入します
}

void PlayerManager::RemovePlayer(int handle)
{
}
