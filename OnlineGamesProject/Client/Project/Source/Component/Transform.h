#pragma once
#include "DxLib.h"


class Transform
{
public:
	Transform();
	~Transform() = default;

public:
	void SetPosition(const VECTOR& pos) { m_Pos = pos; }
	void SetRotation(const VECTOR& rot) { m_Rot = rot; }
	void SetScale(const VECTOR& scale) { m_Scale = scale; }
	const VECTOR& GetPosition() const { return m_Pos; }
	const VECTOR& GetRotation() const { return m_Rot; }
	const VECTOR& GetScale() const { return m_Scale; }

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};
