#pragma once
#include "Transform.h"

class Splite
{
public:
	Splite();
	~Splite();

	void Load(const char* filePath);
	void Draw();
	void Fin();

	void SetTransform(Transform transform) { m_Transform = transform; }

private:
	int m_Handle;
	int m_Width;
	int m_Height;
	int m_CenterX;
	int m_CenterY;
	Transform m_Transform;
};