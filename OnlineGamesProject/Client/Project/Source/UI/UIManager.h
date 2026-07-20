#pragma once

#include "../Singleton/Singleton.h"
#include "UIBase.h"
#include "UIParameter.h"
#include <vector>

class UIBase;

class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

public:
	void Step();
	void Update();
	void Draw();
	void Fin();
	void ClearUI();

	template <typename T>
	T* CreateUI()
	{
		T* ui = new T;

	}

	UIBase* CloneUI(UIBase* original);

private:
	std::vector<UIBase*> m_UIs;
};
