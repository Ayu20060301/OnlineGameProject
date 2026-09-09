#pragma once
#include "../Transform/Transform.h"
#include "../../Component/ComponentBase.h"

class Splite : public ComponentBase
{
public:
	Splite();
	~Splite();

	void Load(const char* filePath);
	void Draw();
	void Fin();

private:
	int m_Handle;
	int m_Width;
	int m_Height;
	int m_CenterX;
	int m_CenterY;

	// Ø‚èo‚·”ÍˆÍ
	int m_RectX;
	int m_RectY;
	int m_RectWidth;
	int m_RectHeight;
};
