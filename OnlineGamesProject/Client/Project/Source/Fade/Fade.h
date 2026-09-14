#pragma once


#include "DxLib.h"

enum class FadeState
{
	FadeIn,
	FadeOut,
	None
};

class Fade
{
public:
	Fade();
	~Fade();

	void StartFadeIn(float duration);
	void StartFadeOut(float duration);

	void Update();
	void Draw();

	bool IsFinished() const { return m_State == FadeState::None; }
	bool IsFadeIn() const { return m_State == FadeState::FadeIn; }
	bool IsFadeOut() const { return m_State == FadeState::FadeOut; }
private:
	FadeState m_State;

	float m_Alpha; //アルファ値
	float m_Duration; //フェード時間
	float m_ElapsedTime; //経過時\間
};
