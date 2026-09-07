#pragma once

#include "../GameObject/GameObject.h"
#include "DxLib.h"

class ComponentBase;


//サーバー用壁クラス
class Wall : public GameObject
{
public:
	Wall();
	~Wall() = default;

	void Init();
	void Step();
	void Draw();


	void OverlapGameObject(GameObject& other) override;

private:
	float m_MoveSpeed;
	float m_MoveDirection;
};
