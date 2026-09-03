#include "DxLib.h"
#include "Controller2D.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

VECTOR Controller2D::Move()
{
	VECTOR move = VGet(0.0f, 0.0f, 0.0f);
	if (Input::IsInputKey(KEY_UP))
	{
		move.y = -1.0f;
	}
	if (Input::IsInputKey(KEY_DOWN))
	{
		move.y = 1.0f;
	}
	if (Input::IsInputKey(KEY_LEFT))
	{
		move.x = -1.0f;
	}
	if (Input::IsInputKey(KEY_RIGHT))
	{
		move.x = 1.0f;
	}

	return MyMath::VecNormalize(move);
}

VECTOR Controller2D::Scale()
{
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);
	if (Input::IsInputKey(KEY_W))
	{
		scale.y = 1.0f;
	}
	if (Input::IsInputKey(KEY_S))
	{
		scale.y = -1.0f;
	}
	if (Input::IsInputKey(KEY_A))
	{
		scale.x = -1.0f;
	}
	if (Input::IsInputKey(KEY_D))
	{
		scale.x = 1.0f;
	}

	return MyMath::VecNormalize(scale);
}

VECTOR Controller2D::Rotate()
{
	VECTOR rotate = VGet(0.0f, 0.0f, 0.0f);
	if (Input::IsInputKey(KEY_Q))
	{
		rotate.z = -1.0f;
	}
	if (Input::IsInputKey(KEY_E))
	{
		rotate.z = 1.0f;
	}

	return MyMath::VecNormalize(rotate);
}
