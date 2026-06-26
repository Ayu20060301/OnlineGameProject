#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Init()override;
	virtual void Load()override;
	virtual void Start()override;
	virtual void Step()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Fin()override;
};
