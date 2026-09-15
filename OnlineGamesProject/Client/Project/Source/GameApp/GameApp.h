#pragma once
#include "../Singleton/Singleton.h"

class Client;
class BackGround;

enum MainState
{
	MAIN_STATE_NONE,
	MAIN_STATE_SELECT_MODE,
	MAIN_STATE_SET_IP,
	MAIN_STATE_CHAT,
	MAIN_STATE_NAME_INPUT,
};

class GameApp : public Singleton<GameApp>
{
public:
	GameApp();
	~GameApp();

	void Init();
	void Exec();

	void Update();
	void Draw();

	void UpdateSelectMode();
	void SetIP();

private:
	Client* m_Client;
	BackGround* m_BackGround;

	MainState m_State;

	//ëIëíÜÇÃçÄñ⁄
	int m_SelectIndex;

	bool m_IsRunning;
};
