#pragma once

#include "SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	virtual ~PlayScene();

public:
	virtual void Init()override;
	virtual void Load()override;
	virtual void Start()override;
	virtual void Step()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Fin()override;
};