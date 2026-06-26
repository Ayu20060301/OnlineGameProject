#pragma once
#include "DxLib.h"


class Transform
{
public:
	Transform();
	~Transform() = default;

public:
	void SetPos(const VECTOR& pos) { m_Pos = pos; }
	void SetPos(const float& x, const float& y, const float& z) { m_Pos = VGet(x,y,z); }
	void SetRot(const VECTOR& rot) { m_Rot = rot; }
	void SetRot(const float& x, const float& y, const float& z) { m_Rot = VGet(x, y, z); }
	void SetScale(const VECTOR& scale) { m_Scale = scale; }
	void SetScale(const float& x, const float& y, const float& z) { m_Scale = VGet(x, y, z); }

	VECTOR GetPos() const { return m_Pos; }
	VECTOR GetRot() const { return m_Rot; }
	VECTOR GetScale() const { return m_Scale; }


private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};
