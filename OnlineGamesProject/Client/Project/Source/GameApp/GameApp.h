#pragma once
#include "../Singleton/Singleton.h"


class GameApp : public Singleton<GameApp>
{
public:
	GameApp();
	~GameApp();

	void Init();
	void Exec();
};
