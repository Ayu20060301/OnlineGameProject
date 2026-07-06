#pragma once

#include "PlayScene.h"
#include "../Memory/Memory.h"

class Client;

class NetworkPlayScene : public PlayScene
{
public:
	NetworkPlayScene() = default;
	virtual ~NetworkPlayScene();

public:
	void Init() override;
	void Load() override;
	void Fin() override;
};
