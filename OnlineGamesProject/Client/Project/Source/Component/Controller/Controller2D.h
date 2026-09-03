#pragma once
#include "DxLib.h"
#include "ComponentBase.h"

class Controller2D : public ComponentBase
{
public:
	Controller2D() = default;
	~Controller2D() = default;

	VECTOR Move();
	VECTOR Scale();
	VECTOR Rotate();
};
