#include "Fade.h"

Fade::Fade()
{
	m_State = FadeState::None;
	m_Alpha = 0.0f;
	m_Duration = 1.0f;
	m_ElapsedTime = 0.0f;
}

Fade::~Fade()
{
}

void Fade::StartFadeIn(float duration)
{
	m_State = FadeState::FadeIn;

	m_Alpha = 255.0f;
	m_Duration = duration;
	m_ElapsedTime = 0.0f;
}

void Fade::StartFadeOut(float duration)
{
	m_State = FadeState::FadeOut;

	m_Alpha = 0.0f;
	m_Duration = duration;
	m_ElapsedTime = 0.0f;
}

void Fade::Update()
{
	if (m_State == FadeState::None) return;

	m_ElapsedTime += 1.0f / 60.0f;

	float rate = m_ElapsedTime / m_Duration;

	if (rate >= 1.0f)
	{
		rate = 1.0f;
	}

	if (m_State == FadeState::FadeIn)
	{
		//•‚©‚ç“§–¾
		m_Alpha = 255.0f * (1.0f - rate);
	}
	else if (m_State == FadeState::FadeOut)
	{
		//“§–¾‚©‚ç•
		m_Alpha = 255.0f * rate;
	}

	if (m_ElapsedTime >= m_Duration)
	{
		m_State = FadeState::None;
	}
}

void Fade::Draw()
{
	if (m_Alpha <= 0.0f) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_Alpha));

	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
