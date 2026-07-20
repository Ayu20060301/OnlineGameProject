#pragma once

#include "DxLib.h"
#include "EffectParameter.h"

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

public:
	void Step();
	void Draw();

	void SetUp(int handle, const SpriteAnimationParam* param, VECTOR pos, int interval, bool loop = false);

public:
	bool IsActive() const { return m_IsActive; }
	bool IsHide() const { return m_IsHide; }

	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetHide(bool isHide) { m_IsHide = isHide; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetInterval(int interval) { m_Interval = interval; }

private:
	bool m_IsActive;
	bool m_IsHide;
	bool m_IsLoop;
	int m_Handle;
	int m_NowFrame;
	int m_Timer;
	int m_Interval;
	VECTOR m_Pos;
	const SpriteAnimationParam* m_Param;
};
