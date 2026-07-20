#pragma once
#include "UIBase.h"

class UIImage : public UIBase
{
public:
	UIImage();
	~UIImage();

public:
	void Load(const char* path);
	void Draw() override;
	void Fin() override;
	UIBase* Clone() override;

private:
	int m_Handle;
};
