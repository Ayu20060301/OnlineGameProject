#include "DxLib.h"
#include "ScreenFade.h"
#include "../GameSetting/GameSetting.h"

float ScreenFade::m_Value = 0.0f;
float ScreenFade::m_Speed = 0.0f;
ScreenFade::State ScreenFade::m_State = ScreenFade::NONE;

void ScreenFade::Step()
{
	if (m_State == FADEIN)
	{
		m_Value -= FADEIN;
		if (m_Value < 0.0f)
		{
			m_Value = 0.0f;
			m_State = NONE;
		}
	}
	else if (m_State == FADEOUT)
	{
		m_Value += m_Speed;
		if (m_Value > 255.0f)
		{
			m_Value = 255.0f;
			m_State = NONE;
		}
	}
}

void ScreenFade::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_Value);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScreenFade::FadeIn(float speed)
{
	m_Value = 255.0f;
	m_State = FADEIN;
	m_Speed = speed;
}

void ScreenFade::FadeOut(float speed)
{
	m_Value = 0.0f;
	m_State = FADEOUT;
	m_Speed = speed;
}
