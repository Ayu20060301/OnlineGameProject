#pragma once

#include "../GameObject/GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	~Wall() override;

	virtual void Init();
	virtual void Load();
	virtual void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

private:
	float m_MoveSpeed;
	int m_Direction;
};
