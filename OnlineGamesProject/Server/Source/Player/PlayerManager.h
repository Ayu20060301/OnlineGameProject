#pragma once

#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>

class Player;

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	~PlayerManager() = default;

public:
	void Draw();

	Player& CreatePlayer();
	void RemovePlayer(int handle);

	int GetPlayerCount() const { return static_cast<int>(m_Players.size()); }
	std::vector<SharedPtr<Player>> GetPlayers() const { return m_Players; }

private:
	std::vector<SharedPtr<Player>> m_Players;
};
