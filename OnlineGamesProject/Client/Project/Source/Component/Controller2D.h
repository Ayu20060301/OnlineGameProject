#pragma once
#include "DxLib.h"

class Controller2D
{
public:
	Controller2D() = default;
	~Controller2D() = default;

	VECTOR Move();
	VECTOR Scale();
	VECTOR Rotate();
};
