#pragma once


class Stage
{
public:
	Stage();
	~Stage();

public:
	void Load();
	void Draw();
	void Fin();

public:
	float  GetPosX();
	float  GetPosY();

private:
	int m_Handle;
};
