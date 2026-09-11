#pragma once

#include "SceneBase.h"

enum class TitleState
{
	LOGO,
	MENU
};

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Init()override;
	virtual void Load()override;
	virtual void Start()override;
	virtual void Step()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Fin()override;
private:
	//状態ごとの更新
	void StepLogo();
	void StepMenu();

	//状態ごとの描画
	void DrawLogo();
	void DrawMenu();

	//中央揃いで文字を描画
	void DrawCenterString(const char* text, int y, unsigned int color,int size);

	//フェード用アルファ値を取得
	int GetFadeAlpha() const;

	TitleState m_State;

	//フェード用
	int m_FadeTimer;

	//メニューの選択位置
	int m_SelectIndex;
};
