#pragma once

#include "../ComponentBase.h"

class Splite : public ComponentBase
{
public:
	Splite();
	virtual ~Splite();

	void Load(const char* filePath);
	void Draw();
	void Fin();

private:
	int m_Handle;
	int m_Width;
	int m_Height;
	int m_CenterX;
	int m_CenterY;
};
