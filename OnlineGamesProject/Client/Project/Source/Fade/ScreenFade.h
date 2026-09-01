#pragma once

class ScreenFade
{
public:
	static void Step();
	static void Draw();

	static void FadeIn(float speed);
	static void FadeOut(float speed);

	static bool IsFade() { return m_State != NONE; }

private:
	enum State
	{
		NONE = -1,
		FADEIN,
		FADEOUT
	};
private:
	static float m_Value;
	static float m_Speed;
	static State m_State;

};