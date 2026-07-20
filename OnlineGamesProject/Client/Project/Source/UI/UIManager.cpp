#include "UIManager.h"
#include "UIImage.h"

UIManager::UIManager()
{
	m_UIs = {};
}

UIManager::~UIManager()
{
	Fin();
}


void UIManager::Step()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Step();
	}
}


void UIManager::Update()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Update();
	}
}

void UIManager::Draw()
{
	for (UIBase* ui : m_UIs)
	{
		if (ui->IsHide()) continue;

		ui->Draw();

	}
}

void UIManager::Fin()
{
	ClearUI();
}

/// <summary>
/// 生成中のUIをすべて削除する
/// </summary>
void UIManager::ClearUI()
{
	for (UIBase* ui : m_UIs)
	{
		delete ui;
	}

	m_UIs.clear();
	m_UIs.shrink_to_fit();
}

/// <summary>
/// 引数で渡されたUIのクローンを作る方法で生成
/// </summary>
/// <param name="original">クローン元のUI</param>
/// <returns>生成したUI</returns>
UIBase* UIManager::CloneUI(UIBase* original)
{
	for (UIBase* ui : m_UIs)
	{
		if (ui == original)
		{
			UIBase* clone = original->Clone();
			m_UIs.push_back(clone);
			return clone;
		}
	}

	return nullptr;
}
